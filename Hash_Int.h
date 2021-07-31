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

    vector<movie> *table;  //points to array that contains buckets

public:
    void displayHash(); //delete later

    Hash_Int(int buckets, int modFactor);

    void Insert(movie m);

    // void delete(int key);

    int hashify(int value);

    vector<movie> searchMoviesFromYear(int year); //returns all movies made in that year



};


Hash_Int::Hash_Int(int buckets, int modFactor_) //int hash constructors
{
    numBuckets = buckets;
    modFactor = modFactor_;
    table = new vector<movie>[numBuckets];
}

void Hash_Int::Insert(movie m)
{
    int placeToPutIt = hashify(m.getYear());
    table[placeToPutIt].push_back(m);

    //if hash table is at load factor, increase

}

int Hash_Int::hashify(int year)
{
    return (year % numBuckets);
}

vector<movie> Hash_Int::searchMoviesFromYear(int year)
{
    vector<movie> toReturn = table[hashify(year)];
    return toReturn;
}


void Hash_Int::displayHash() //remove later
{
    for (int i = 0; i < numBuckets; i++)
    {
        cout << i;
        for (auto x : table[i])
            cout << " --> " << x.getTitle();
        cout << endl << endl;
        }
}
