#pragma once
#include <vector>
#include <stack>
#include <algorithm>
#include "Movie.h"

struct Node
{
    movie movie;
    Node* left;
    Node* right;

    Node(::movie& m)
    {
        movie = m;
        left = right = nullptr;
    }
};

class BST
{
public:
    Node* root;
    int size;
    BST();
    movie* getMovie();
    void insert(movie& m, Node*& n);
    movie searchTitle(string title_, Node*& n);
    void searchGenre(string genre, Node*& n, vector<movie>& movieGenres);
    void searchYear(int year, Node*& n, vector<movie>& v);
    void inorderPrint(Node*& n);
    void searchGenreMinYear(string genre, int year, Node*& n, vector<movie>& m);
    bool contains(vector<movie>& v, movie& m);
    vector<movie> topFilms(vector<string> criteria, int minYear, Node*& n, int numMovies);
};

BST::BST()
{
    root = nullptr;
    size = 0;
}

void BST::insert(movie& m, Node*& n) // recursive BST insert based on movie titles
{
    if (n == nullptr)
    {
        n = new Node(m);
        size++;
    }

    else if (m.getTitle() < n->movie.getTitle())
        insert(m, n->left);
    else if (m.getTitle() >= n->movie.getTitle())
        insert(m, n->right);
}

movie BST::searchTitle(string title_, Node*& n)
{
    Node* node = n;

    if (title_ == node->movie.getTitle())
        return node->movie;

    else if (title_ < node->movie.getTitle())
        return searchTitle(title_, node->left);

    return searchTitle(title_, node->right);

}

void BST::searchGenre(string genre, Node*& n, vector<movie>& movieGenres)//finds movies with a given genre using an inorder traversal
{
    if (n == nullptr)
        return;
    searchGenre(genre, n->left, movieGenres);

    for(int i = 0; i < n->movie.getGenreVect().size(); i++){
        if(n->movie.getGenreVect().at(i) == genre){
            movieGenres.push_back(n->movie);
        }
    }
    searchGenre(genre, n->right, movieGenres);
}

void BST::searchYear(int year, Node*& n, vector<movie>& v)
{
    if (n == nullptr)
        return;

    searchYear(year, n->left, v);

    if(n->movie.getYear() == year)
        v.push_back(n->movie);

    searchYear(year, n->right, v);
}

void BST::inorderPrint(Node *&n) {//used for testing
    if (n == nullptr)
        return;

    inorderPrint(n->left);

    cout << n->movie.getTitle() << endl;

    inorderPrint(n->right);

}

void searchGenreMinYear(string genre, int year, Node*& n, vector<movie>& m)
{
    if(n == nullptr)
        return;

    searchGenreMinYear(genre, year,n->left,m);

    if(n->movie.getYear() == year){
        for(int i = 0; i < n->movie.getGenreVect().size(); i++){
            if(n->movie.getGenreVect().at(i) == genre)
                m.push_back(n->movie);
        }
    }
    searchGenreMinYear(genre, year, n->right,m);
}

bool BST::contains(vector<movie>& v, movie& m)
{
    for (auto i : v)
        if (i == m) return true;
    return false;
}

vector<movie> BST::topFilms(vector<string> criteria, int minYear, Node*& n, int numMovies)
{
    vector<movie> topFilms_; // vector of all movies matching genre/year criteria
    stack<Node*> s;
    Node* node = n;
    while (node || !s.empty()) // iterative inorder traversal
    {
        while (node)
        {
            s.push(node);
            node = node->left;
        }
        node = s.top();
        s.pop();
        movie m = node->movie;
        if (m.getYear() >= minYear) // if minYear criteria is met
        {
            int count = 0;
            vector<string> genres = m.getGenreVect(); // vector of genres for this node
            for (int i = 0; i < genres.size(); i++)
            {
                if (find(criteria.begin(), criteria.end(), genres[i]) != criteria.end()) // iterate thru node's list of genres
                    count++;    // iterate count for every one of node's genre that matches a criteria genre
            }
            if (count == criteria.size() && genres.size() == count && m.getYear() >= minYear) // if node meets all criteria
            {
                if (topFilms_.size() < numMovies) // if vector hasn't been filled, add node's movie
                    topFilms_.push_back(m); 
                else if (topFilms_.size() == numMovies) // if vector is full
                {
                    float min = 10.1;
                    int minIndex;                   
                    for (int i = 0; i < topFilms_.size(); i++) // iterate thru current topFilms_ and find lowest rated movie
                    {
                        if (min > topFilms_[i].getAverageVotes())
                        {
                            min = topFilms_[i].getAverageVotes();
                            minIndex = i;
                        }
                    }
                    if (m.getAverageVotes() > topFilms_[minIndex].getAverageVotes()) // check to see if node's movie is higher rated than lowest rated 
                    {
                        if (!contains(topFive, m))
                            topFilms_[minIndex] = m;        // replace lowest rated movie with node
                    }
                }
            }
        }
        node = node->right;
    }

    return topFive;
}
