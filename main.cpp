#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include "Movie.h"
#include "Hash_Int.h"
#include "BST.h"
using namespace std;


void trim(string &str);
vector<string> SplitString(string s);

set<string> uniques;

int main()
{

    ifstream file("MovieListRatings.csv");//filepath from local files


    vector<movie> movieCollection;

    int count = 0;
    if (file.is_open())
    {
        cout << "File is open" << endl;
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
            for (int i = 0; i < genreVect.size(); i++)
            {
                if (uniques.find(genreVect[i]) == uniques.end()) //if not in uniques, add it
                {
                    uniques.insert(genreVect[i]);
                }
            }

            string durationString;
            getline(s,durationString,',');
            trim(durationString);
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

    cout << "#unique genres " << uniques.size() << endl;

    cout << "Count: " << count << endl;
    int movieNum = 3;
    for (int i = 0; i < movieCollection[movieNum].getGenreVect().size(); i++)
    {
        cout << movieCollection[movieNum].getGenreVect()[i] << endl;
    }
    cout << "First movie genre list:" << movieCollection[1].getGenreVect()[0] << endl;
    cout << "Last movie in list:" << movieCollection[movieCollection.size()-1].getGenre() << endl;


    Hash_Int tempHash = Hash_Int(50, 50);

    for (int i = 0; i < count; i++ )
    {
        tempHash.Insert( movieCollection[i]);
    }
    //tempHash.displayHash();


    cout << "Size: " << tempHash.getSize() << endl;

/*
    cout << "What is the oldest movie (minimum)" << endl;
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
    cout << "All movies made past this date are: " << endl;
    for (int i = 0; i< minMovieVect.size();i++)
    {
        cout << minMovieVect[i].getTitle() << ",made: " << minMovieVect[i].getYear() << endl;
    };
*/

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


void trim(string &str)
{
    size_t startpos = str.find_first_not_of(" \t");
    if( string::npos != startpos )
    {
        str = str.substr( startpos );
    }
}
