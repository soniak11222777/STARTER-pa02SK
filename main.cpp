// Winter'24
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    vector<Movie> movieList;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            movieList.push_back(Movie(movieName, movieRating));
            //cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
    }

    movieFile.close();
    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
            sort(movieList.begin(), movieList.end());
            for(auto& e : movieList ){
                cout << e << endl;
            }
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    vector<Movie> totals;
    vector<pair<string, Movie>> h_ratings;
sort(movieList.begin(), movieList.end());
    for (int i = 0; i<prefixes.size();i++){
        Movie a(prefixes[i], 0.0);
       vector<Movie>::iterator it = lower_bound(movieList.begin(),movieList.end(), a);
       if (it == movieList.end() || it->movieName.find(prefixes[i]) != 0){
        cout << "No movies found with prefix "<< prefixes[i] << endl;
       }
       else {
       while(it != movieList.end() && it->movieName.find(prefixes[i]) == 0){
        totals.push_back(*it);
      it++;
       }
       sort(totals.begin(), totals.end() , [] (const Movie& a, const Movie&b) {
        if (a.movieRating != b.movieRating){
		return a.movieRating > b.movieRating; 
        }
        return a.movieName < b.movieName; 
        });
        for (Movie a: totals){
        cout << a << endl;
       }
        h_ratings.push_back({prefixes[i], totals[0]});
        cout << endl;
        totals.clear();
    }
    }

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
 
    for (auto& each : h_ratings ){
    cout << "Best movie with prefix " << each.first << " is: " << each.second.movieName << " with rating " << std::fixed << std::setprecision(1) << each.second.movieRating << endl;
}
 return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

/*
Time Complexity
The parameters that affect this runtime are n,m,k, and l. 
We begin sorting, which looks at l name length and sorts each element alphabetically for 
nlogn making it L * NlogN time. Afterwards we loop M times over the prefixes, each time finding
the first instance using an iterator found by function lower_bound (logN- utilizes binary search) and
the dummy Movie object (L length string) so we get LlogN. In the while loop we check K times for 
name L lengths, so K*L, and by calling the lambda altered sort function which adjusts for the rating 
numerical value for K instances it operates KlogK times. Subsequently printing the values for each 
prefix is K times L for the string in each so K*L again with L cost to push back again. Since we 
iterate through every prefix in the final result printing the name/values it is M*L.

 All of this being in the for loop means the total time is

O(L *NlogN + M(LlogN + 2K*L + KlogK + L) +ML)
but due to the constained length of movie titles making L somewhat constant
it can be simplified as O(M(logN + KlogK))

times
input_20_random.csv, prefix_large.txt: 0.062
input_100_random.csv, prefix_large.txt: 0.398
input_1000_random.csv, prefix_large.txt: 0.068
input_76920_random.csv, prefix_large.txt: 1.405

Space Complexity
The primary affecting parameters are M, K, and L.
We begin assuming n and m are already stored but when we traverse and store into the vector and vector
pair, we get O(L*M) for the highest ratings because each prefix has a rating present, and we get O(L*K)
for totals as it clears following the print out of the values for each individual prefix.

Combined this simplifies to O((M+K)*L)

I was trying to design for low time complexity, close to implementation 3 of about MlogN, and wasn't 
necessarily prioritizing space complexity though it happened to become smaller than the time complexity.
I knew we would have to iterate at least M times and planned on using either a bst or any available
pre-provided function utilizing binary search to get log N as the factor.

I was able to achieve a decently low time complexity though the algorithm used more traversals than I
intially anticipated, though they were smaller in range.

Similarly, the space complexity is ok too as while I didn't anticipate creating multiple output vectors
they do not compare to the size of the movieList N vector which I didnt have to copy or include in the
space complexity.

Time complexity was much harder to achieve than space complexity.
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}

