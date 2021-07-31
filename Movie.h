#pragma once
#include <vector>
#include <string>
using namespace std;

class movie
{
private:
    int year, duration;
    string title, date, country, genre;
    vector<string> genres;
public:
    //Constructors
    movie();
    movie(string title, string genre, string date, string country, int duration, int year, vector<string> genres_);
    //Getters
    string getDate();
    vector<string> getGenreVect();
    string getTitle();
    string getGenre();
    string getCountry();
    int getYear();
    int getDuration();

};

movie::movie()
{
    title = "";
}

movie::movie(string title_, string genre_, string date_, string country_, int duration_, int year_, vector<string> genres_)
{
    title = title_;
    genres = genres_;
    genre = genre_;
    date = date_;
    country = country_;
    duration = duration_;
    year = year_;
}

string movie::getTitle()
{
    return title;
}

string movie::getDate()
{
    return date;
}


string movie::getCountry()
{
    return country;
}

int movie::getYear()
{
    return year;
}

int movie::getDuration()
{
    return duration;
}

string movie::getGenre()
{
    return genre;
}

vector<string> movie::getGenreVect()
{
    return genres;
}

