#ifndef CATALOG_H
#define CATALOG_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Movie {
    string name;
    string production;
    double rating;

    bool operator==(const Movie& movie) const
    {
        return name == movie.name;
    }

    bool operator<(const Movie& movie) const
    {
        return name < movie.name;
    }

    bool operator>(const Movie& movie) const
    {
        return name > movie.name;
    }

    friend ostream& operator<<(ostream& out, const Movie& movie)
    {
        out << movie.name << endl;
        out << movie.production << endl;
        out << movie.rating << endl;

        return out;
    }

    friend istream& operator>>(istream& input, Movie& movie)
    {
        input >> movie.name;

        return input;
    }
};

class Catalog
{
    /** List all movies */
    friend ostream& operator<<(ostream& out, const Catalog& catalog);
    private:
        vector<Movie> _movies;
        size_t _catalogSize;
    public:
        Catalog(size_t catalogSize);
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
