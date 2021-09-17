#include <vector>
#include <iostream>
#include <algorithm>
#include "Catalog.h"

using namespace std;

Catalog::Catalog(size_t catalogSize)
{
    _movies = vector<Movie>(catalogSize);
}

void Catalog::operator+=(Movie movie)
{
    bool movieRegistered = operator()(movie.name) != NULL;
    if (movieRegistered) {
        throw runtime_error("Movie \"" + movie.name + "\" already registered.");
    }

    _movies.push_back(movie);

    sort(_movies.begin(), _movies.end());
}

void Catalog::operator+=(vector<Movie> movies)
{
    for (auto movie: movies) {
        bool movieRegistered = operator()(movie.name) != NULL;
        if (movieRegistered) {
            throw runtime_error("Movie \"" + movie.name + "\" already registered.");
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
    Movie* movie = operator()(movieName);
    if (movie == NULL) {
        return NULL;
    }

    movie->production = newProduction;

    return movie;
}

Movie* Catalog::operator()(string movieName, double newRating)
{
    Movie* movie = operator()(movieName);
    if (movie == NULL) {
        return NULL;
    }

    movie->rating = newRating;

    return movie;
}

ostream& operator<<(ostream& out, const Catalog& catalog)
{
    for (auto movie: catalog._movies) {
        out << movie.name << "\n";
    }

    return out;
}

