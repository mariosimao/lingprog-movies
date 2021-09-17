#include <iostream>
#include "Movie.h"

bool Movie::operator == (Movie movie)
{
    return name == movie.name;
}

bool Movie::operator < (Movie movie)
{
    return name < movie.name;
}

bool Movie::operator > (Movie movie)
{
    return name > movie.name;
}

bool Movie::operator > (double comparedRating)
{
    return rating > comparedRating;
}

ostream& operator << (ostream& out, const Movie& movie)
{
    out << movie.name << " - " << movie.production << " - " << movie.rating << endl;

    return out;
}

istream& operator >> (istream& input, Movie& movie)
{
    string name, production, rating;

    cout << "Add movie to catalog" << endl;

    cout << "* Name: ";
    getline(input, name);
    movie.name = name;

    cout << "* Production: ";
    getline(input, production);
    movie.production = production;

    cout << "* Rating: ";
    getline(input, rating);
    try {
        movie.rating = stod(rating);
    } catch(const std::exception& e) {
        throw runtime_error("Rating must be a number.");
    }

    return input;
}