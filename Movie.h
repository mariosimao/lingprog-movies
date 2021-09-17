#ifndef MOVIE_h
#define MOVIE_h
#include <string>

using namespace std;

struct Movie {
    string name;
    string production;
    double rating;
    bool operator == (Movie movie);
    bool operator < (Movie movie);
    bool operator > (Movie movie);
    bool operator > (double comparedRating);
    friend ostream& operator << (ostream& out, const Movie& movie);
    friend istream& operator >> (istream& input, Movie& movie);
};
#endif
