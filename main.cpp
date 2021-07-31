#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Movie.h"
using namespace std;


void trim(string &str);
vector<string> SplitString(string s);

int main() {

    
    ifstream file("MovieListRatings.csv");//filepath from local files

    vector<movie> movieCollection;

    int count = 0;
    if (file.is_open())
    {
        cout << "File is open" << endl;
        string nul;
        getline(file,nul);//gets rid of header
        getline(file,nul);
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

    cout << "Count: " << count << endl;
//
//    cout << movieCollection[1].getGenreVect().size() << " is the size" << endl;
//    cout << "First movie genre in list:" << movieCollection[1].getGenreVect()[4] << endl;
//    for (int i = 0; i < movieCollection[3].getGenreVect().size(); i++)
//    {
//        cout << movieCollection[3].getGenreVect()[i] << endl;
//    }
//    cout << "First movie genre list:" << movieCollection[1].getGenreVect()[1] << endl;
//
//
//
//    cout << "Last movie in list:" << movieCollection[movieCollection.size()-1].getGenre() << endl;
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
            i++;
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
