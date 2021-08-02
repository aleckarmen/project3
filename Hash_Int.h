#ifndef BESTFLIX_HASH_H
#define BESTFLIX_HASH_H
#include "Movie.h"
#endif //BESTFLIX_HASH_H
using namespace std;

class Hash_Int
{
private:
    int numBuckets;
    int modFactor;
    int size;
    vector<movie> *table;  //points to array that contains buckets
public:
    void displayHash();
    Hash_Int(int buckets, int modFactor);
    int getSize();
    void Insert(movie m);
    int hashify(int value);
    vector<movie> searchMoviesFromYear(int year); //returns all movies made in that year

};

Hash_Int::Hash_Int(int buckets, int modFactor_) //int hash constructors
{
    size = 0;
    numBuckets = buckets;//can vary around for best performance
    modFactor = modFactor_;
    table = new vector<movie>[numBuckets];
}

int Hash_Int::getSize()
{
    return size;
}

void Hash_Int::Insert(movie m)
{
    int placeToPutIt = hashify(m.getYear());//determine index of hash table by running hashify
    table[placeToPutIt].push_back(m); //push it at that index
    size++;
}

int Hash_Int::hashify(int year)
{
    return (year % numBuckets);
}

vector<movie> Hash_Int::searchMoviesFromYear(int year)
{
    vector<movie> moviesInDesiredYear;
    vector<movie> temp = table[hashify(year)]; //assign the ones that match to this

    for(int i = 0; i< temp.size(); i++)
    {
        if (temp[i].getYear() == year)
        {
            moviesInDesiredYear.push_back(temp[i]);//this is where the checking for collisions happends i.e. 2019 and 1919 would be distinguished
        }
    }
    return moviesInDesiredYear;
}


void Hash_Int::displayHash() //
{
    for (int i = 0; i < numBuckets; i++)
    {
        cout << i;
        for (auto x : table[i])
            cout << " --> " << x.getTitle();
        cout << endl << endl;
    }
}
