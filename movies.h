#include <iostream>

using namespace std;
class Movie{

public:
string movieName;
double movieRating;

Movie(string n = " ", double r  = 0.0);
~Movie();

bool operator<(const Movie& f) const;

//private:

};
ostream& operator<<(ostream &out, const Movie& m);