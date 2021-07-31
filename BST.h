#pragma once
#include <vector>

#include "Movie.h"

struct Node
{
    movie movie;
    Node* left;
    Node* right;

    Node(movie& m)
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
        insert(m, n->left);
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