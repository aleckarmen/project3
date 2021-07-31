#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Hash_Int.h"
#include "Movie.h"


using namespace std;


void trim(string &str);
vector<string> SplitString(string s);

int main()
{


    cout << "hello world" << endl;



    fstream open("NewMovieList.csv", ios::out | ios::app);
    fstream file("NewMovieList.csv");//filepath from local files


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


            /*
            int quoteCount = 0;
            vector<string> genreVect;
            while (quoteCount <2)
            {

                string genre;
                getline(s,genre,',');//HERE WE NEED TO FIGURE OUT COMMA IN STRING PREVENTING OUR DELIMITER
                if(genre.find('"') != string::npos) //if theres a quote in this genre pulled
                {
                    quoteCount++;
                    //trim the quote out
                }
                cout << "genre: "<<genre << endl;
                genreVect.push_back(genre);




            }
*/

            vector<string> genreVect;

            string genres;
            getline(s,genres,',');


            genreVect = SplitString(genres);


            //cout << "genres: " <<genre << endl;




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
    int movieNum = 3;
    for (int i = 0; i < movieCollection[movieNum].getGenreVect().size(); i++)
    {
        cout << movieCollection[movieNum].getGenreVect()[i] << endl;
    }
    cout << "First movie genre list:" << movieCollection[1].getGenreVect()[1] << endl;
    cout << "Last movie in list:" << movieCollection[movieCollection.size()-1].getGenre() << endl;

    Hash_Int tempHash = Hash_Int(50, 2000);
    for (int i = 0; i < 800; i++ )
    {
        tempHash.Insert( movieCollection[i*10]);
    }
    tempHash.displayHash();


    //cout << "What "



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
