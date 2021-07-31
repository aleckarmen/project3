//
// Created by Alec on 7/30/2021.
//

#ifndef BESTFLIX_MOVIE_H
#define BESTFLIX_MOVIE_H

#endif //BESTFLIX_MOVIES_H
//
// Created by Alec on 7/30/2021.
//

#include <vector>
#include <string>
#pragma once
using namespace std;

class Movie
{
public:

private:
    int year,duration,budget,votes;
    string imdb_title_id,title,original_title;
    double avg_vote,usa_gross_income,worlwide_gross_income,metascore;






public:
    movie();
    movie(string title_, string imdb_title_id_);


    string getImdb_title_id();
    void setImdb_title_id(string imdb_title_id_);

    string getTitle();
    void setTitle(string title_);








};

movie::movie()
{
    title = "";

}

movie::movie(string title_, string imdb_title_id_)
{
    title = title_;




}






string movie::getTitle()
{
    return title;
}
void movie::setTitle(string title_)
{
    this->title = title_;
}


string movie::getImdb_title_id()
{
    return imdb_title_id;
}
void movie::setImdb_title_id(string imdb_title_id_)
{
    this->imdb_title_id = imdb_title_id_;
}



