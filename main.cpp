#include <iostream>
#include "Catalog.h"

int main(int argc, char const *argv[])
{
    vector<Movie> movies;
    Catalog catalog(100);

    Movie hp = {
        "Harry Potter",
        "Warner",
        8.1
    };
    catalog += hp;

    catalog += Movie {
        "Amelie",
        "Francesa",
        4.2
    };

    catalog += Movie {
        "Star Wars",
        "Disney",
        6.2
    };

    cout << catalog;
    cout << "---" << endl;

    catalog -= Movie { "Star Wars" };

    cout << catalog;

    Movie* search = catalog("Harry Potter");
    cout << search;

    return 0;
}
