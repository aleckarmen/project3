#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <vector>
#include "Movie.h"
#include "Hash_Int.h"
#include "BST.h"
#include "Hash_Genre.h"
using namespace std;
using namespace std::chrono;

void trim(string &str);
vector<string> SplitString(string s);
void dataInsertionBST(string filepath, BST& tree);
int findLowestRatedMovieIndex(vector<movie> movieVect);
vector<movie> findBestMovies(vector<movie> movieList, int numMoviesToSuggest);
void sortAverageVote(vector<movie>& m);
void insertGenreHash(Hash_Genre &Hash);
int findAsciiSum(string str);
vector<movie> findDesiredMoviesByGenre(Hash_Genre &genreHash, string inputGenres);
void trimBack(std::string &s);
void trimFront(string &str);
void delSpaces(string &str);
void printMovieVect(vector<movie>& m);
void insertAllToHash(Hash_Int &durationHash);
vector<string> parseGenreInput(string input);
void dataInsertionBST(string filepath, BST& tree);


int main(){

    BST movieTree;
    Hash_Genre genreHash = Hash_Genre(2804); // NEED TO FIGURE OUT HOW TO CHANGE THIS TO GET ASCII STUFF
    Hash_Int durationHash = Hash_Int(50, 50);

    string file = "MovieListRatings.csv";
    cout << "Welcome to BESTFLIX Movie Recommender!" << endl;
    cout << "--------------------------------------" << endl;

    auto startBST = high_resolution_clock::now();
    dataInsertionBST(file,movieTree);
    auto stopBST = high_resolution_clock::now();

    std::chrono::duration<double> elapsedBST = stopBST - startBST;
    cout << "Inserting all movies into the BST took " << elapsedBST.count() << " seconds" << endl;
    cout << endl;

    auto startMap = high_resolution_clock::now();
    insertAllToHash(durationHash);
    auto stopMap = high_resolution_clock::now();

    std::chrono::duration<double> elapsedHashYear = stopMap - startMap;
    cout << "Inserting all movies into the Year Hash Table took " << elapsedHashYear.count() << " seconds" << endl;
    cout << endl;

    auto startGenreHash = high_resolution_clock::now();
    insertGenreHash(genreHash);
    auto stopGenreHash = high_resolution_clock::now();

    std::chrono::duration<double> elapsedGenreHash = stopGenreHash - startGenreHash;
    cout << "Inserting all movies into the Genre Hash Table took " << elapsedGenreHash.count() << " seconds" << endl;
    cout << endl;

    int option = 0;
    cout << "Which Data Structure would you like to use to recommend a movie?" << endl;
    cout << "1. Binary Search Tree" << endl;
    cout << "2. Year Hash Table" << endl;
    cout << "3. Genre Hash Table" << endl;
    cout << "4. Exit" << endl;
    cin >> option;

    cout << "How many movies?" << endl;
    int numMovies = 0;

    cin >> numMovies;

    if(option == 4){
        cout << "Thanks for using BestFlix!" << endl;
        return 0;
    }//close program

    int year = 0;

    if(option == 1 || option == 3)
    {
        cout << "What is the year of the oldest movie you want to watch? (Minimum year)" << endl;
        cin.ignore();
        cin >> year;
        cin.ignore();
    }
    else if(option == 2){
        cout << "Please enter the year you want movies from!" << endl;
        cin >> year;
    }

    string genreInput = "";
    if(option == 1 || option == 3)
    {
        cout << "What genre would you like to watch?" << endl;
        getline(cin,genreInput);
    }

    cout << "Here are the top " << numMovies <<" movies that follow the specified criteria: " << endl;
    if(option == 1)
    {//if user picks BST use BST search for top five
        vector<string> genres = SplitString(genreInput);
        auto bstTimerS = high_resolution_clock::now();
        vector<movie> bstSearch = movieTree.topFiveByGenre(genres,year,movieTree.root, numMovies);
        auto bstTimerE = high_resolution_clock::now();
        sortAverageVote(bstSearch);

        printMovieVect(bstSearch);
        auto bstDuration = duration_cast<microseconds>(bstTimerE - bstTimerS);
        cout << endl;
        cout << "BST search took " << bstDuration.count() << " microseconds!" << endl;
    }
    else if(option == 2)
    {//if users picks Year Hash Table then search using that
        vector<movie> IntHashMovies;
        auto IntHashS = high_resolution_clock::now();
        IntHashMovies = durationHash.searchMoviesFromYear(year);

        vector<movie> bestMovies = findBestMovies(IntHashMovies, numMovies);

        auto IntHashE = high_resolution_clock::now();

        sortAverageVote(bestMovies);
        printMovieVect(bestMovies);
        auto yearDuration = duration_cast<microseconds>(IntHashE - IntHashS);

        cout << endl;
        cout << "Year Hash Table search took " << yearDuration.count() << " microseconds!"  << endl;
    }

    else if(option == 3)
    {
        vector<movie> minMovieVect; //we will end up with a vector of all movies past that date
        //auto genreHashS = high_resolution_clock::now();
        for (int i = year; i <= 2020; i++)
        {
            vector<movie> tempVect = durationHash.searchMoviesFromYear(i);

            for (int j = 0; j < tempVect.size(); j++ )
            {
                minMovieVect.push_back(tempVect[j]);
            }
        }

        Hash_Genre newGenreHash = Hash_Genre(2804);

        for (int i = 0; i < minMovieVect.size(); i++)
        {
            newGenreHash.Insert(minMovieVect[i]);
        }

        auto genreHashS = high_resolution_clock::now();
        vector<movie> desiredGenreVect;

        desiredGenreVect = newGenreHash.searchMoviesFromGenre(genreInput);
        vector<movie> bestMovies = findBestMovies(desiredGenreVect, numMovies);
        auto genreHashE = high_resolution_clock::now();

        auto genreDuration = duration_cast<microseconds>(genreHashE -genreHashS);
        sortAverageVote(bestMovies);
        printMovieVect(bestMovies);

        cout << endl;
        cout << "Genre Hash Table search took " << genreDuration.count() << " microseconds!" << endl;
    }
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

void trim(string &str)
{
    size_t startpos = str.find_first_not_of(" \t");
    if( string::npos != startpos )
    {
        str = str.substr( startpos );
    }
}

void dataInsertionBST(string filepath, BST& tree) {
    ifstream file(filepath);//filepath from local files

    vector<movie> movieCollection;

    int count = 0;
    if (file.is_open()) {
        //cout << "File is open" << endl;
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
            trim(durationString);

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

    }
}

vector<movie> findBestMovies(vector<movie> movieList, int numMoviesToSuggest)  //returns top 5 movies of lowest rated out of our list
{
    vector<movie> topMovies;

    if (movieList.size() < numMoviesToSuggest)
    {
        return movieList;
    }

    for (int i = 0; i < numMoviesToSuggest; i++)//fill top movies with first 5 available
    {
        topMovies.push_back(movieList[i]);
    }

    int lowestIndex = 0;
    for (int i = 0; i < topMovies.size(); i++) // find index of lowest rate one
    {
        if (topMovies[i].getAverageVotes() < topMovies[lowestIndex].getAverageVotes())
        {
            lowestIndex = i;
        }
    }

    for(int i = numMoviesToSuggest; i < movieList.size(); i++) //loop through all movies and assign higher ones into top movies
    {
        if(movieList[i].getAverageVotes() > topMovies[lowestIndex].getAverageVotes()) //if this movie in question is better rated
        {
            topMovies[lowestIndex] = movieList[i]; //replace lowest movie in topmovies with it
            lowestIndex = findLowestRatedMovieIndex(topMovies); //set lowest index  to next lowest after switch
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

void sortAverageVote(vector<movie>& m){

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

            istringstream s(line);

            string title;
            getline(s, title,',');

            string stringYear;
            getline(s,stringYear,',');

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

            string durationString;
            getline(s,durationString,',');
            trimFront(durationString);

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

void insertGenreHash(Hash_Genre &Hash)
{

    ifstream file("MovieListRatings.csv");//filepath from local files

    if (file.is_open())
    {
        string nul;
        getline(file,nul);//gets rid of header
        string line;

        while(getline(file, line))
        {
            istringstream s(line);

            string title;
            getline(s, title,',');


            string stringYear;
            getline(s,stringYear,',');

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

            string durationString;
            getline(s,durationString,',');
            trimFront(durationString);

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

            Hash.Insert(currentMovie);

        }

    }
}

void delSpaces(string &str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

void trimFront(string &str)
{
    size_t startpos = str.find_first_not_of(" \t");
    if( string::npos != startpos )
    {
        str = str.substr( startpos );
    }
}

void printMovieVect(vector<movie>& m){
    for(int i = 0; i < m.size(); i++)
    {
        m.at(i).printMovie();
    }
}
