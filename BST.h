#pragma once
#include <vector>

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
        searchTitle(title_, node->left);
    else if (title_ > node->movie.getTitle())
        searchTitle(title_, node->right);
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
