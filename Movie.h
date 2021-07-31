#pragma once
#include <vector>
#include <string>
using namespace std;

class movie
{
private:
    int year, duration;
    string title, date, country;
    vector<string> genres;
public:
    //Constructors
    movie();
    movie(string title, vector<string> genres, string date, string country, int duration, int year);
    //Getters
    string getDate();
    string getTitle();
    vector<string> getGenre();
    string getCountry();
    int getYear();
    int getDuration();

};

movie::movie()
{
    title = "";
}

movie::movie(string title_, vector<string> genres_, string date_, string country_, int duration_, int year_)
{
    title = title_;
    genres = genres_;
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

vector<string> movie::getGenre()
{
    return genres;
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
