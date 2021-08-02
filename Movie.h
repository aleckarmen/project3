#pragma once
#include <vector>
#include <string>
using namespace std;

class movie
{
private:
    int year, duration,votes;
    string title, date, country, genre;
    vector<string> genres;
    float averageVotes;
public:
    //Constructors
    movie();
    movie(string title, string genre, string date, string country, int duration, int year, vector<string> genres_ , int votes_, float averageVotes);
    //Getters
    string getDate();
    vector<string> getGenreVect();
    string getTitle();
    string getGenre();
    string getCountry();
    int getYear();
    int getDuration();
    int getNumVotes();
    float getAverageVotes();
    void printMovie();
    bool operator>(movie& rhs);
    bool operator==(movie& rhs);
    bool operator<(movie &rhs);
};

movie::movie()
{
    title = "";
}

movie::movie(string title_, string genre_, string date_, string country_, int duration_, int year_, vector<string> genres_, int votes_, float averageVotes_)
{
    title = title_;
    genres = genres_;
    genre = genre_;
    date = date_;
    country = country_;
    duration = duration_;
    year = year_;
    votes = votes_;
    averageVotes = averageVotes_;
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

int movie::getNumVotes()
{
    return votes;
}

float movie::getAverageVotes()
{
    return averageVotes;
}

void movie::printMovie()
{
    cout << "---------------------------------------"<< endl;
    cout << "Title: \t\t" << title << endl;
    cout << "Year: \t\t" << year << endl;
    cout << "Genre(s): \t";
    for (int i = 0; i < genres.size(); i++)
    {
        cout << genres[i];
        if (i != genres.size() - 1)
            cout << ", ";
    }
    cout << endl;
    cout << "Country: \t" << country << endl;
    cout << "Duration: \t" << duration << endl;
    cout << "Total Votes: \t" << votes << endl;
    cout << "Average Vote: \t" << averageVotes << endl;
    cout << "---------------------------------------"<< endl;
}

bool movie::operator==(movie& rhs)
{
    if (this->title == rhs.getTitle())
        return true;
    else
        return false;
}

bool movie::operator>(movie &rhs) {
    if(this->averageVotes > rhs.getAverageVotes())
        return true;
    else
        return false;
}

bool movie::operator<(movie &rhs) {
    if(this->averageVotes < rhs.getAverageVotes())
        return true;
    else
        return false;
}
