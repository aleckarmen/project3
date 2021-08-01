#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>


#include <map> //this is for assessing the data I wont use a map in our final implementation
#include "Hash_Genre.h"
#include "Movie.h"
#include "Hash_Int.h"
using namespace std;

int findAsciiSum(string str);
void trimBack(std::string &s);
void trimFront(string &str);
void delSpaces(string &str);
int findMax(set<int> my_set);
vector<string> SplitString(string s);

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
    int sum = 0;
    cout << "# of unique genres " << uniques.size() << endl;
    for(auto f : uniques) {
        sum+=f.second;
        cout << f.first << " has " << f.second <<  " occurences. "  << endl;

    }

    cout << "total genres: " << sum << endl;
    cout << "specific unique combos from : " << uniqueCombos.size() <<"total."<< endl;

    /*for(auto f : uniqueCombos)
    {

        cout << f << endl;
        uniqueSums.insert(findAsciiSum(f));

    }*/


    cout << "number of unique sums for hashing from unique combos(hopefully 1257 is all, half would erase repitition): " << uniqueSums.size() << endl;
    cout << "These sums are: " << endl;
    int lastsum =0;
    for(auto f : uniqueSums)
    {

        cout << f << endl;

    }


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
    cout << "Table of everything by year Size: " << tempHash.getSize() << endl;







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


    auto it = findMax(uniqueSums);
    int lastVal = it;

    cout << "Last val: " << lastVal << endl;
    Hash_Genre genreHash = Hash_Genre(lastVal); //it will have uniqueSums# of buckets this unique sums might have to be based on new list of movies after thinning out via year


    cout << "TESTTTTT" << endl << endl;

    for (int i = 0; i < minMovieVect.size(); i++)
    {
        genreHash.Insert(minMovieVect[i]);
    }
    cout << "Movies after " << minYear <<" in genre hash table..." << endl;
    //genreHash.displayHash();

    cout << "What single genre are you interested in?" << endl;
    string inputGenre;
    cin >> inputGenre;
    vector<movie> desiredGenreVect; //we will end up with a vector of all movies past that date
    for (int i = minYear; i <= 2020; i++)
    {
        vector<movie> tempVect = genreHash.searchMoviesFromGenre(inputGenre);

        for (int i = 0; i < tempVect.size(); i++ )
        {
            desiredGenreVect.push_back(tempVect[i]);
        }

    }

    cout << "I reccomend this movie!: " << desiredGenreVect[0].getTitle();





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
