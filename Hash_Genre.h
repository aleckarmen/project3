#ifndef BESTFLIX_HASH_GENRE_H
#define BESTFLIX_HASH_GENRE_H
#endif //BESTFLIX_HASH_GENRE_H
#include "Movie.h"
#include <string>
#include <algorithm>
using namespace std;

class Hash_Genre
{
private:
    int numBuckets;
    int size;
    vector<movie> *table;  //points to array that contains buckets

public:
    void displayHash(); //delete later

    Hash_Genre(int buckets);
    void delSpaces_(string &str)
    {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    }
    int findAsciiSum_(string str)
    {
        int sum = 0;

        for (char c : str)
            sum += c;
        return sum;
    }
    int getSize();
    int getBuckets();
    void Insert(movie m);
    int hashify(string genres);
    vector<movie> searchMoviesFromGenre(string genre); //returns all movies made in that year
};

Hash_Genre::Hash_Genre(int buckets) //int hash constructors
{
    size = 0;
    numBuckets = buckets+1;
    table = new vector<movie>[numBuckets];
}

int Hash_Genre::getSize()
{
    return size;
}

void Hash_Genre::Insert(movie m)
{
    string genreString = "";
    for (int i = 0; i< m.getGenreVect().size(); i++)
    {
        genreString += (m.getGenreVect()[i]);
    }

    int placeToPutIt = hashify(genreString);
    table[placeToPutIt].push_back(m);
    size++;
}

int Hash_Genre::getBuckets()
{
    return numBuckets;
}

int Hash_Genre::hashify(string genres) // can be one or more genres in form "A" or "A B C..."
{
    delSpaces_(genres);
    int sum = findAsciiSum_(genres);

    return sum;
}

vector<movie> Hash_Genre::searchMoviesFromGenre(string genres) //can be one or more genres will get them via hashify number returned
{
    vector<movie> movieswithDesiredGenres; //genre(s) in this case
    vector<movie> temp = table[hashify(genres)]; //temp is a vector containing movies in that genre sum category

    for(int i = 0; i< temp.size(); i++)
    {
        movieswithDesiredGenres.push_back(temp[i]); //push back a vector of movies with that genre
    }

    return temp;
}

void Hash_Genre::displayHash() //remove later
{
    for (int i = 0; i < numBuckets; i++)
    {
        cout << i;
        for (auto x : table[i])
            cout << " --> " << x.getTitle();
        cout << endl << endl;
    }
}

void delSpaces_(string &str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}
int findAsciiSum_(string str)
{
    int sum = 0;

    for (char c : str)
        sum += c;
    return sum;
}
