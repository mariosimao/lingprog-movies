#ifndef CATALOG_H
#define CATALOG_H
#include <string>
#include <vector>
#include <iostream>
#include "Movie.h"

using namespace std;

class Catalog
{
    /** List all movies */
    friend ostream& operator<<(ostream& out, const Catalog& catalog);
    private:
        string _name;
        size_t _catalogSize;
        vector<Movie> _movies;
    public:
        Catalog(string name, size_t catalogSize);
        /** Counts how many movies have been registered */
        size_t moviesRegistered();
        Movie* rename(string oldName, string newName);
        Movie* bestRatedMovie();
        string toCsv();
        /** Add movie */
        void operator+=(Movie movie);
        /** Add multiple movies */
        void operator+=(vector<Movie> movies);
        /** Remove movie */
        void operator-=(string movieName);
        /** Search movie by name */
        Movie* operator()(string movieName);
        /** Update movie production */
        Movie* operator()(string movieName, string newProduction);
        /** Update movie rating */
        Movie* operator()(string movieName, double newRating);
};
#endif
