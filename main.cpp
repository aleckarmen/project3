#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Movie.h"


using namespace std;


int main() {


    fstream file("C://Users//Alec//Downloads//archive");//change filepath 

    if (file.is_open())
    {
        string nul;
        getline(file,nul);//gets rid of header
        string line;
        vector<movie> movieCollection;


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

            string genre;
            getline(s,genre,',');

            string durationString;
            getline(s,durationString,',');
            int duration = stoi(durationString);

            string country;
            getline(s,country,',');

            movie currentMovie(title,genre,date,country,duration,year);

            movieCollection.push_back(currentMovie);//vector that stores the movie objects
            //we can switch this with any insertion of a data structure I just have it at vector for now

        }

    }

    return 0;
}
