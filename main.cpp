#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include "Catalog.h"

using namespace std;

vector<vector<string>> readCsv(string filename)
{
    vector<vector<string>> result;
    vector<string> row;
    string line, word;

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file '" + filename + "'");
    }

    if (!file.good()) {
        throw runtime_error("Could not read file '" + filename + "'");
    }

    while (getline(file, line)) {
        stringstream ss(line);

        row.clear();
        while (getline(ss, word, ',')) {
            row.push_back(word);
        }

        result.push_back(row);
    }

    file.close();

    return result;
}

void rewriteFile(string filename, string content)
{
    fstream file;
    file.open(filename, fstream::in | fstream::out | fstream::trunc);

    if (!file.is_open()) {
        throw runtime_error("Could not open catalog file '" + filename + "'");
    }

    if (!file.good()) {
        throw runtime_error("Could not read catalog file '" + filename + "'");
    }

    file << content;

    file.close();
}

bool isDouble(string numberString)
{
    istringstream iss(numberString);
    double f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}

Catalog parseCsv(string filename)
{
    vector<vector<string>> data = readCsv(filename);
    vector<Movie> movies;

    string catalogName = data[0][1];
    int catalogSize(stoi(data[0][2]));
    Catalog catalog(catalogName, catalogSize);

    for (size_t i = 1; i < data.size(); i++) {
        vector<string> row = data[i];

        if (row.size() != 3) {
            throw runtime_error("Invalid CSV format. Number of columns must be 3.");
        }

        string name = row[0];
        if (name == "") {
            throw runtime_error("A movie must not have an empty name.");
        }

        string production = row[1];
        if (name == "") {
            throw runtime_error("A movie must not have an empty production.");
        }

        if (!isDouble(row[2])) {
            throw runtime_error("Rating is not a valid number.");
        }
        double rating = stof(row[2]);

        Movie movie = {
            name,
            production,
            rating
        };

        movies.push_back(movie);
    }

    catalog += movies;

    return catalog;
}

int main(int argc, char const *argv[])
{
    try {
        vector<string> args(argv, argv + argc);
        map<string, int> commands = {
            { "help", 0 },
            { "create", 1 },
            { "add", 2 },
            { "bulk-add", 3 },
            { "list", 4 },
            { "search", 5 },
            { "best", 6 },
            { "rename", 7 },
            { "update-production", 8 },
            { "update-rating", 9 },
            { "remove", 10 }
        };

        if (
            argc <= 1 ||
            args[1] == "help"
        ) {
            cout << "Usage: catalog <catalog-name> <command> [<args>]" << endl;
            cout << endl;
            cout << "Available commands:" << endl << endl;
            cout << "\t" << "help"                                      << "\t\t\t\t\t\t" << "Display this help page" << endl;
            cout << "\t" << "create <size>"                             << "\t\t\t\t\t"   << "Create a catalog" << endl;
            cout << "\t" << "add"                                       << "\t\t\t\t\t\t" << "Insert a single movie" << endl;
            cout << "\t" << "bulk-add <amount-of-movies>"               << "\t\t\t"       << "Insert multiple movies" << endl;
            cout << "\t" << "list"                                      << "\t\t\t\t\t\t" << "List all movies" <<  endl;
            cout << "\t" << "search <movie-name>"                       << "\t\t\t\t"     << "Search a single movie by name" << endl;
            cout << "\t" << "best"                                      << "\t\t\t\t\t\t" << "Find the movie with highest rating" << endl;
            cout << "\t" << "rename <old-name> <new-name>"              << "\t\t\t"       << "Rename a movie" << endl;
            cout << "\t" << "update-production <name> <new-production>" << "\t"           << "Update a movie production" << endl;
            cout << "\t" << "update-rating <name> <new-rating>"         << "\t\t"         << "Update a movie rating" << endl;
            cout << "\t" << "remove <movie-name>"                       << "\t\t\t\t"     << "Remove a movie" << endl;
            cout << endl;
            return 0;
        }

        if (argc < 3) {
            throw runtime_error("Missing argument. Use 'catalog help' for usage information.");
        }

        string catalogName = args[1];
        string filename = catalogName + ".csv";
        string command = args[2];

        if (!commands.count(command)) {
            throw runtime_error("Command not found. Use 'catalog help' for usage information.");
        }
        int commandKey = commands.at(command);
        switch (commandKey) {
            case 1: { // Create catalog
                if (argc < 4) {
                    throw runtime_error("Missing catalog size.");
                }

                size_t size;
                try {
                    size = stoi(args[3]);
                } catch(const std::exception& e) {
                    throw runtime_error("Catalog size must be a number.");
                }
                Catalog catalog(catalogName, size);

                string content = catalog.toCsv();

                rewriteFile(filename, content);
                break;
            }
            case 2: { // Add one movie
                Catalog catalog = parseCsv(filename);

                Movie movie;
                cin >> movie;

                catalog += movie;

                rewriteFile(filename, catalog.toCsv());
                break;
            }
            case 3: { // Add multiple movies
                if (argc < 4) {
                    throw runtime_error("Missing amount of movies to be inserted");
                }

                int amount;
                try {
                    amount = stoi(args[3]);
                } catch(const std::exception& e) {
                    throw runtime_error("Amount of movies must be a number.");
                }

                Catalog catalog = parseCsv(filename);

                vector<Movie> movies;
                for (int i = 0; i < amount; i++) {
                    Movie movie;
                    cin >> movie;
                    movies.push_back(movie);
                }

                catalog += movies;
                rewriteFile(filename, catalog.toCsv());
                break;
            }
            case 4: { // Print catalog
                Catalog catalog = parseCsv(filename);

                cout << catalog;
                break;
            }
            case 5: { // Search movie
                if (argc < 4) {
                    throw runtime_error("Missing movie name.");
                }

                string movieName = args[3];

                Catalog catalog = parseCsv(filename);

                Movie* movie = catalog(movieName);
                if (movie == NULL) {
                    throw runtime_error("Movie not found.");
                }

                cout << *movie;
                break;
            }
            case 6: { // Print movie with highest rating
                Catalog catalog = parseCsv(filename);
                Movie* movie = catalog.bestRatedMovie();

                cout << "Movie with highest rating:" << endl;
                cout << *movie;
                break;
            }
            case 7: { // Rename movie
                if (argc < 5) {
                    throw runtime_error("Missing arguments. Old and new name should be provided");
                }

                string oldName = args[3];
                string newName = args[4];

                Catalog catalog = parseCsv(filename);
                Movie* result = catalog.rename(oldName, newName);
                if (result == NULL) {
                    throw runtime_error("Movie not found.");
                }

                rewriteFile(filename, catalog.toCsv());

                cout << "Movie successfully renamed." << endl;
                break;
            }
            case 8: { // Update movie production
                if (argc < 5) {
                    throw runtime_error("Missing arguments. Movie name and new production should be provided.");
                }

                string name = args[3];
                string newProduction = args[4];

                Catalog catalog = parseCsv(filename);

                Movie* result = catalog(name, newProduction);
                if (result == NULL) {
                    throw runtime_error("Movie not found.");
                }

                rewriteFile(filename, catalog.toCsv());
                break;
            }
            case 9: { // Update movie rating
                if (argc < 5) {
                    throw runtime_error("Missing arguments. Movie name and new rating should be provided.");
                }

                string name = args[3];
                double newRating;
                try {
                    newRating = stod(args[4]);
                } catch(const std::exception& e) {
                    throw runtime_error("New rating should be a valid number.");
                }
                Catalog catalog = parseCsv(filename);

                Movie* result = catalog(name, newRating);
                if (result == NULL) {
                    throw runtime_error("Movie not found.");
                }

                rewriteFile(filename, catalog.toCsv());
            }
            case 10: { // Remove move
                if (argc < 4) {
                    throw runtime_error("Missing movie name.");
                }

                string name = args[3];
                Catalog catalog = parseCsv(filename);

                catalog -= name;

                rewriteFile(filename, catalog.toCsv());
            }
        }

        return 0;
    } catch(const std::exception& e) {
        cerr << "\u001b[31m[ERROR] \u001b[0m" << e.what() << endl;
        return 1;
    }
}
