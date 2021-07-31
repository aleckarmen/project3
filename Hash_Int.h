//
// Created by Alec on 7/31/2021.
//

#ifndef BESTFLIX_HASH_H
#define BESTFLIX_HASH_H
#include "Movie.h"

#endif //BESTFLIX_HASH_H

using namespace std;

class Hash_Int
{

private:
    int numBuckets;

    vector<movie> *table;  //points to array that contains buckets

public:
    void displayHash(); //delete later

    Hash_Int(int tables);

    void Insert(movie m);

    // void delete(int key);

    int hashify(int value);

};


Hash_Int::Hash_Int(int buckets) //int hash constructors
{
    numBuckets = buckets;
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