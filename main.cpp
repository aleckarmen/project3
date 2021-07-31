#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Movie.h"


using namespace std;


void trim(string &str);

int main() {


    cout << "hello world" << endl;



    fstream open("Movies.txt", ios::out | ios::app);
    fstream file("Movies.txt");//change filepath


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
            cout <<"Line #: " << count << endl;
            istringstream s(line);

            string title;
            getline(s, title,',');

            string stringYear;
            getline(s,stringYear,',');
            cout << "String year:" <<stringYear <<"_" << endl;
            int year = stoi(stringYear);

            string date;
            getline(s,date,',');

            string genre;
            vector<string> genres;
            while (!isdigit(stream.peek()))
            {
                getline(s,genre,',');  //HERE WE NEED TO FIGURE OUT COMMA IN STRING PREVENTING OUR DELIMITER
                
                if (genre[0] == '\"')
                    genre.erase(genre[0]);
                if (genre[genre.size() - 1] == '\"')
                    genre.erase(genre[genre.size() - 1]);

                genres.push_back(genre);
            }
            cout << "genre(s): ";
            for (auto i : genres)
                cout << i << " ";

            string durationString;
            getline(s,durationString,',');
            trim(durationString);
            cout << "durationString:" << durationString << "_" << endl;
            int duration = stoi(durationString);

            string country;
            getline(s,country,',');


            movie currentMovie(title,genres,date,country,duration,year);
            count++;


            movieCollection.push_back(currentMovie);//vector that stores the movie objects
            //we can switch this with any insertion of a data structure I just have it at vector for now

        }




    }

    cout << "Count: " << count << endl;

    cout << "First movie in list:" << movieCollection[0].getTitle() << endl;



    cout << "Last movie in list:" << movieCollection[movieCollection.size()-1].getTitle() << endl;
    return 0;
}

void trim(string &str)
{
    size_t startpos = str.find_first_not_of(" \t");
    if( string::npos != startpos )
    {
        str = str.substr( startpos );
    }
}


