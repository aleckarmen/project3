#pragma once
#include <vector>
#include <string>
using namespace std;

class movie
{
private:
    int year, duration;
    string title, genre, date, country;
public:
    //Constructors
    movie();
    movie(string title, string genre, string date, string country, int duration, int year);
    //Getters
    string getDate();
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

movie::movie(string title_, string genre_, string date_, string country_, int duration_, int year_)
{
    title = title_;
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

string movie::getGenre()
{
    return genre;
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
