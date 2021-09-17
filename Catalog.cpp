#include <vector>
#include <iostream>
#include <algorithm>
#include "Catalog.h"

using namespace std;

void checkMovieRegistered(string movieName, Catalog* catalog)
{
    bool movieRegistered = catalog->operator()(movieName) != NULL;
    if (movieRegistered) {
        throw runtime_error("Movie \"" + movieName + "\" already registered.");
    }
}

void checkMovieHasAllProperties(Movie movie)
{
    if (movie.name == "" || movie.production == "" || movie.rating == 0) {
        throw runtime_error("Movie must have all properties initialized");
    }
}

Catalog::Catalog(string name, size_t catalogSize)
{
    _name = name;
    _catalogSize = catalogSize;
}

size_t Catalog::moviesRegistered()
{
    return this->_movies.size();
}

Movie* Catalog::rename(string oldName, string newName)
{
    Movie* oldMovie = this->operator()(oldName);
    if (oldMovie == NULL) {
        return NULL;
    }

    Movie newMovie {
        newName,
        oldMovie->production,
        oldMovie->rating
    };

    this->operator-=(oldMovie->name);
    this->operator+=(newMovie);

    return this->operator()(newName);
}

Movie* Catalog::bestRatedMovie()
{
    if (this->moviesRegistered() == 0) {
        return NULL;
    }

    Movie* bestRatedMovie = &this->_movies[0];
    double highestRatring = bestRatedMovie->rating;
    for (auto movie: this->_movies) {
        if (movie > highestRatring) {
            highestRatring = movie.rating;
            bestRatedMovie = &movie;
        }
    }

    return bestRatedMovie;
}

string Catalog::toCsv()
{
    string content = "meta," + this->_name + "," + to_string(this->_catalogSize) + "\n";
    for (auto movie: this->_movies) {
        content += movie.name + "," + movie.production + "," + to_string(movie.rating) + "\n";
    }

    return content;
}

void Catalog::operator+=(Movie movie)
{
    size_t newSize = this->moviesRegistered() + 1;
    if (newSize > this->_catalogSize) {
        throw runtime_error("Catalog already at maximum size.");
    }

    checkMovieRegistered(movie.name, this);
    checkMovieHasAllProperties(movie);

    _movies.push_back(movie);

    sort(_movies.begin(), _movies.end());
}

void Catalog::operator+=(vector<Movie> movies)
{
    size_t newSize = movies.size() + this->moviesRegistered();
    if (newSize > this->_catalogSize) {
        throw runtime_error("Additions will extrapolate catalog size.");
    }

    for (size_t i = 0; i < movies.size(); i++) {
        checkMovieRegistered(movies[i].name, this);
        checkMovieHasAllProperties(movies[i]);

        for (size_t j = 0; j < movies.size(); j++) {
            if (i == j) {
                continue;
            }

            if (movies[i] == movies[j]) {
                throw runtime_error("Duplicated movies are not allowed.");
            }
        }
    }

    _movies.insert(_movies.end(), movies.begin(), movies.end());

    sort(_movies.begin(), _movies.end());
}

void Catalog::operator-=(const string deletedMovie)
{
    for (auto it = _movies.begin(); it != _movies.end(); it++) {
        if (deletedMovie == it->name) {
            _movies.erase(it);
            break;
        }
    }

    return;
}

Movie* Catalog::operator()(string movieName)
{
    for (auto it = _movies.begin(); it != _movies.end(); it++) {
        if (it->name == movieName) {
            return &(*it);
        }
    }

    return NULL;
}

Movie* Catalog::operator()(string movieName, string newProduction)
{
    Movie* movie = this->operator()(movieName);
    if (movie == NULL) {
        return NULL;
    }

    movie->production = newProduction;

    return movie;
}

Movie* Catalog::operator()(string movieName, double newRating)
{
    Movie* movie = this->operator()(movieName);
    if (movie == NULL) {
        return NULL;
    }

    movie->rating = newRating;

    return movie;
}

ostream& operator<<(ostream& out, const Catalog& catalog)
{
    int i = 0;
    for (auto movie: catalog._movies) {
        out << ++i << ". ";
        out << movie;
    }

    return out;
}
