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

Catalog::Catalog(size_t catalogSize)
{
    _catalogSize = catalogSize;
}

size_t Catalog::moviesRegistered()
{
    return this->_movies.size();
}
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
        throw runtime_error("Catalog already at maximum size.");
    }

    for (auto movie: movies) {
        checkMovieRegistered(movie.name, this);
        checkMovieHasAllProperties(movie);
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

