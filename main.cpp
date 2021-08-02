#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <chrono>

#include <map> //this is for assessing the data I wont use a map in our final implementation
#include "Hash_Genre.h"
#include "Movie.h"
#include "Hash_Int.h"
#include "BST.h"
using namespace std;
using namespace std::chrono;

int findAsciiSum(string str);
vector<movie> findDesiredMoviesByGenre(Hash_Genre &genreHash, string inputGenres);
void trimBack(std::string &s);
void trimFront(string &str);
void delSpaces(string &str);
void sortAverageVote(vector<movie>& m);
int findMax(set<int> my_set);
vector<string> SplitString(string s);
int findLowestRatedMovieIndex(vector<movie> movieVect);
vector<movie> findBestMovies(vector<movie> movieList, int numMoviesToSuggest);
void insertAllToHash(Hash_Int &durationHash);
vector<string> parseGenreInput(string input);
void dataInsertionBST(string filepath, BST& tree);


set<int>uniqueSums;
map<string,int> uniques;
set<string> uniqueCombos;

int main()
{

    ifstream file("MovieListRatings.csv");//filepath from local files


    vector<movie> movieCollection;

    int count = 0;
    if (file.is_open())
    {

        string nul;
        getline(file,nul);//gets rid of header
        string line;



        while(getline(file, line))
        {
            //cout <<"Line #: " << count << endl;
            istringstream s(line);

            string title;
            getline(s, title,',');
            //cout << "Movie title(s) :" <<title <<"_" << endl;

            string stringYear;
            getline(s,stringYear,',');
            //cout << "String year:" <<stringYear <<"_" << endl;
            int year = stoi(stringYear);

            string date;
            getline(s,date,',');

            vector<string> genreVect;
            string genres;
            getline(s,genres,',');



            genreVect = SplitString(genres);


            string builder = "";
            for (int i = 0; i < genreVect.size();i++)
            {
                delSpaces(genreVect[i]);
                builder+=genreVect[i];

            }

            uniqueCombos.insert(builder);


            for (int i = 0; i < genreVect.size(); i++)
            {
                if (uniques.find(genreVect[i]) == uniques.end()) //if not in uniques, add it
                {
                    uniques[genreVect[i]] = 1; //this is the first occurence of this genre
                }
                else
                {
                    uniques[genreVect[i]] = uniques[genreVect[i]] +1;
                }
            }

            //find a way to insert into unique combos without space character in anything



            string durationString;
            getline(s,durationString,',');
            trimFront(durationString);
            //cout << "durationString:" << durationString << "_" << endl;
            int duration = stoi(durationString);

            string country;
            getline(s,country,',');

            string averageVotes;
            getline(s,averageVotes,',');
            float avgVotes = stof(averageVotes);

            string totVotes;
            getline(s,totVotes,',');
            int totalVotes = stoi(totVotes);



            movie currentMovie = movie(title,genres,date,country,duration,year, genreVect, totalVotes, avgVotes);
            count++;


            movieCollection.push_back(currentMovie);//vector that stores the movie objects
            //we can switch this with any insertion of a data structure I just have it at vector for now

        }

    }


    Hash_Int durationHash = Hash_Int(100, 50);


    auto start = high_resolution_clock::now();

    insertAllToHash(durationHash);

    auto stop = high_resolution_clock::now();


    auto duration = duration_cast<microseconds>(stop - start);

    cout <<"Duration to run this Hash Table Code: " <<duration.count() << endl << endl << endl;


    //durationHash.displayHash();





    int sum = 0;
    cout << "# of unique genres " << uniques.size() << endl;
    for(auto f : uniques) {
        sum+=f.second;

    }

    //cout << "specific unique combos from : " << uniqueCombos.size() <<"total."<< endl;

    for(auto f : uniqueCombos)
    {

        //cout << f << endl;
        uniqueSums.insert(findAsciiSum(f));

    }


    //cout << "number of unique sums for hashing from unique combos(hopefully 1257 is all, half would erase repitition): " << uniqueSums.size() << endl;
    //cout << "These sums are: " << endl;
    int lastsum =0;
/*
    for(auto f : uniqueSums)
    {
        cout << f << endl;
    }
*/

    cout << "Number of movies stored: " << count << endl;


    Hash_Int tempHash = Hash_Int(50, 50);

    for (int i = 0; i < count; i++ )
    {
        tempHash.Insert( movieCollection[i]);
    }
    //tempHash.displayHash();
    cout << "Table of everything by year Size: " << tempHash.getSize() << endl;





    cout << "What is the year of the oldest movie you would watch?(minimum)" << endl;
    int minYear;
    cin >> minYear;
    vector<movie> minMovieVect; //we will end up with a vector of all movies past that date
    for (int i = minYear; i <= 2020; i++)
    {
        vector<movie> tempVect = tempHash.searchMoviesFromYear(i);

        for (int i = 0; i < tempVect.size(); i++ )
        {
            minMovieVect.push_back(tempVect[i]);
        }

    }
    /*
    cout << "All movies made past this date are: " << endl;
    for (int i = 0; i< minMovieVect.size();i++)
    {
        cout << minMovieVect[i].getTitle() << ",made: " << minMovieVect[i].getYear() << endl;
    };
    */

    auto it = findMax(uniqueSums);
    int lastVal = it;

    cout << "Last val: " << lastVal << endl;
    Hash_Genre genreHash = Hash_Genre(lastVal); //it will have uniqueSums# of buckets this unique sums might have to be based on new list of movies after thinning out via year


    for (int i = 0; i < minMovieVect.size(); i++)
    {
        genreHash.Insert(minMovieVect[i]);
    }


    //genreHash.displayHash();

    cout << "What single genre(s) are you interested in? Ex: Comedy,or Comedy Romance Action" << endl;
    string inputGenre = "Comedy";
    cin.ignore();
    getline(cin, inputGenre);

    cout << "inputGenre: " <<inputGenre<< endl;
    vector<string> genresWanted;
    genresWanted = SplitString(inputGenre);


    //cout << "our genres too look for are" << endl;
    for (int i = 0; i < genresWanted.size();i++)
    {
        cout << genresWanted[i] << endl;
    }


    vector<movie> desiredGenreVect; //we will end up with a vector of all movies past that date


    desiredGenreVect = genreHash.searchMoviesFromGenre(inputGenre);//temp vect will be the vector returned of all movies in a certain genre's bucket


    //make a vector of the top 5 best rated movies, first initialize to the first 5.
    vector<movie> topMovies;
    /*
    for (int i = 0; i < 5; i++)
    {
        topMovies.push_back(desiredGenreVect[i]);
    }
*/

/*
    for (int i = 0; i<desiredGenreVect.size(); i++)
    {
        cout << desiredGenreVect[i].getTitle() << ", rating: "<< desiredGenreVect[i].getAverageVotes() << endl;
    }
*/

    vector<movie> bestMovies;
    bestMovies = findBestMovies(desiredGenreVect, 5); //will find top 5 movies from indicated vector

    cout << "I reccomend these movies!: " << endl; //
    //maybe sort by rating first?
    sortAverageVote(bestMovies);

    for (int i = 0; i < bestMovies.size(); i++)
    {
        bestMovies[i].printMovie();
    }





    return 0;
}




vector<string> SplitString(string s)
{


    vector<string> v;
    string temp = "";
    for(int i=0;i<s.length();++i){

        if(s[i]==' ')
        {
            v.push_back(temp);
            temp = "";
        }
        else
        {
            temp.push_back(s[i]);//temp is item
        }

    }
    v.push_back(temp); //push item

    return v;
}
void trimFront(string &str)
{
    size_t startpos = str.find_first_not_of(" \t");
    if( string::npos != startpos )
    {
        str = str.substr( startpos );
    }
}

void trimBack(std::string &s)  //trim function from https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
{
    string temp = s;
    temp.erase(std::find_if(temp.rbegin(), temp.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), temp.end());
}

void delSpaces(string &str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}


int findAsciiSum(string str)
{
    int sum = 0;

    for (char c : str)
        sum += c;
    return sum;
}

int findMax(set<int> my_set) // https://www.geeksforgeeks.org/find-maximum-and-minimum-element-in-a-set-in-c-stl/
{

    // Get the maximum element
    int max_element;
    if (!my_set.empty())
        max_element = *(my_set.rbegin());

    // return the maximum element
    return max_element;
}

vector<movie> findBestMovies(vector<movie> movieList, int numMoviesToSuggest)  //returns top 5 movies of lowest rated out of our list
{
    vector<movie> topMovies;


    for (int i = 0; i < numMoviesToSuggest; i++)//fill top movies with first 5 available
    {
        topMovies.push_back(movieList[i]);
        //cout << "Starting movie#" << i << ": "<< movieList[i].getTitle() << endl;
    }
    int lowestIndex = findLowestRatedMovieIndex(topMovies); //find in dex of lowest rating movie in our list so far

    for(int i = numMoviesToSuggest; i < movieList.size(); i++) //loop through all movies and assign higher ones into top movies
    {
        if(movieList[i].getAverageVotes() > topMovies[lowestIndex].getAverageVotes() || (movieList[i].getAverageVotes() == topMovies[lowestIndex].getAverageVotes() && movieList[i].getNumVotes() > topMovies[lowestIndex].getNumVotes())) //if this movie in question is better rated
        {
            topMovies[lowestIndex] = movieList[i]; //replace lowest movie in topmovies with it
            lowestIndex = findLowestRatedMovieIndex(topMovies); //update lowest index  to next lowest after switch
        }
    }

    return topMovies;
}



int findLowestRatedMovieIndex(vector<movie> movieVect)
{
    int lowestIndex = 0;
    for (int i = 0; i < movieVect.size(); i++) // find index of lowest rate one
    {
        if (movieVect[i].getAverageVotes() < movieVect[lowestIndex].getAverageVotes())
        {
            lowestIndex = i;
        }
    }
    return lowestIndex;
}

void insertAllToHash(Hash_Int &durationHash)
{

    ifstream file("MovieListRatings.csv");//filepath from local files

    if (file.is_open())
    {
        string nul;
        getline(file,nul);//gets rid of header
        string line;



        while(getline(file, line))
        {
            //cout <<"Line #: " << count << endl;
            istringstream s(line);

            string title;
            getline(s, title,',');
            //cout << "Movie title(s) :" <<title <<"_" << endl;

            string stringYear;
            getline(s,stringYear,',');
            //cout << "String year:" <<stringYear <<"_" << endl;
            int year = stoi(stringYear);

            string date;
            getline(s,date,',');

            vector<string> genreVect;
            string genres;
            getline(s,genres,',');



            genreVect = SplitString(genres);


            string builder = "";
            for (int i = 0; i < genreVect.size();i++)
            {
                delSpaces(genreVect[i]);
                builder+=genreVect[i];

            }

            uniqueCombos.insert(builder);


            for (int i = 0; i < genreVect.size(); i++)
            {
                if (uniques.find(genreVect[i]) == uniques.end()) //if not in uniques, add it
                {
                    uniques[genreVect[i]] = 1; //this is the first occurence of this genre
                }
                else
                {
                    uniques[genreVect[i]] = uniques[genreVect[i]] +1;
                }
            }

            //find a way to insert into unique combos without space character in anything



            string durationString;
            getline(s,durationString,',');
            trimFront(durationString);
            //cout << "durationString:" << durationString << "_" << endl;
            int duration = stoi(durationString);

            string country;
            getline(s,country,',');

            string averageVotes;
            getline(s,averageVotes,',');
            float avgVotes = stof(averageVotes);

            string totVotes;
            getline(s,totVotes,',');
            int totalVotes = stoi(totVotes);



            movie currentMovie = movie(title,genres,date,country,duration,year, genreVect, totalVotes, avgVotes);

            durationHash.Insert(currentMovie);

        }

    }
}


void sortAverageVote(vector<movie>& m)
{

    for(int i = 0; i < m.size(); i++)
    {
        for(int j = 0; j < m.size() - i - 1; j++)
        {
            if(m.at(j) < m.at(j+1)){
                movie temp = m.at(j);
                m.at(j) = m.at(j+1);
                m.at(j+1) = temp;
            }
        }
    }
}

void dataInsertionBST(string filepath, BST& tree) {//make filepath = "MovieListRatings.csv" !!!
    ifstream file(filepath);//filepath from local files

    vector<movie> movieCollection;

    int count = 0;
    if (file.is_open()) {
        cout << "File is open" << endl;
        string nul;
        getline(file, nul);//gets rid of header
        string line;

        while (getline(file, line)) {
            istringstream s(line);

            string title;
            getline(s, title, ',');


            string stringYear;
            getline(s, stringYear, ',');
            int year = stoi(stringYear);

            string date;
            getline(s, date, ',');

            vector<string> genreVect;
            string genres;
            getline(s, genres, ',');

            genreVect = SplitString(genres);

            string durationString;
            getline(s, durationString, ',');
            trimFront(durationString);

            int duration = stoi(durationString);

            string country;
            getline(s, country, ',');

            string averageVotes;
            getline(s, averageVotes, ',');
            float avgVotes = stof(averageVotes);

            string totVotes;
            getline(s, totVotes, ',');
            int totalVotes = stoi(totVotes);

            movie currentMovie = movie(title, genres, date, country, duration, year, genreVect, totalVotes, avgVotes);
            tree.insert(currentMovie, tree.root);
            count++;
        }
        cout << "Amount of Movies in the BST: " << count << endl;
    }
}
