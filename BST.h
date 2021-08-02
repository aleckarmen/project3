#pragma once
#include <vector>
#include <stack>
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
    
private:


public:
    
    Node* root;

    BST();
    movie* getMovie();
    void insert(movie& m, Node*& n);
    movie searchTitle(string title_, Node*& n);
    void searchGenre(string genre, Node*& n, vector<movie>& movieGenres);
    void searchYear(int year, Node*& n, vector<movie>& v);
    void inorderPrint(Node*& n);
    void searchGenreMinYear(string genre, int year, Node*& n, vector<movie>& m);
    bool contains(vector<movie*>& v, movie*& m);
    vector<movie*> topFiveByGenre(string genre, int minYear, Node*& n);
};

BST::BST()
{
    root = nullptr;
}

void BST::insert(movie& m, Node*& n)
{
    if (n == nullptr)
        n = new Node(m);

    else if (m.getTitle() < n->movie.getTitle())
        insert(m, n->left);
    else if (m.getTitle() >= n->movie.getTitle())
        insert(m, n->right); // changed from left to right
}

movie BST::searchTitle(string title_, Node*& n)
{
    // if (n == nullptr)
    //     return nullptr;
    Node* node = n;

    if (title_ == node->movie.getTitle())
        return node->movie;
    else if (title_ < node->movie.getTitle())
        return searchTitle(title_, node->left);
    else if (title_ > node->movie.getTitle())
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

bool BST::contains(vector<movie*>& v, movie*& m)
{
    for (auto i : v)
        if (i == m) return true;
    return false;
}

vector<movie*> BST::topFiveByGenre(string genre, int minYear, Node*& n)
{
    vector<movie*> topFive;
    stack<Node*> s;
    Node* node = n;
    while (node || !s.empty()) 
    {
        while (node) 
        {
            s.push(node);
            node = node->left;
        }
        node = s.top();
        s.pop();
        movie* m = &node->movie;
        if (m->getYear() >= minYear && m->getGenre() == genre) //m->getGenre().find(genre) != string::npos)
        {
            if (topFive.size() < 5)
                topFive.push_back(m);
            else if (topFive.size() == 5)
            {
                float min = 10.1;
                int minIndex;
                for (int i = 0; i < topFive.size(); i++)
                {
                    if (min > topFive[i]->getAverageVotes())
                    {
                        min = topFive[i]->getAverageVotes();
                        minIndex = i;
                    }
                    if (m->getAverageVotes() > topFive[minIndex]->getAverageVotes())
                    {
                        if (!contains(topFive, m))
                            topFive[minIndex] = m;
                    }
                }
            }   
        }
        node = node->right;
    }
    return topFive;
}
