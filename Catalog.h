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
};

class Catalog
{
    friend ostream& operator<<(ostream& out, const Catalog& catalog);
    private:
        vector<Movie> _movies;
    public:
        Catalog(size_t catalogSize);
        void operator+=(Movie movie);
        void operator+=(vector<Movie> movies);
        void operator-=(Movie movie);
        Movie* operator()(string movieName);
        Movie* operator()(string movieName, string newProduction);
        Movie* operator()(string movieName, double newRating);
};
#endif
