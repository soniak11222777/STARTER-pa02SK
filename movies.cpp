#include "movies.h"

#include <iostream>
using std::cout;

Movie::Movie(string n, double r) : movieName(n) , movieRating(r){}


Movie::~Movie(){}

bool Movie::operator<(const Movie& f) const{
    if (movieName==f.movieName){
        return movieRating<f.movieRating;
    }
    return movieName<f.movieName;
}


ostream& operator<<(ostream &out, const Movie& m){
    out << m.movieName << ", " << m.movieRating ;
return out;
}