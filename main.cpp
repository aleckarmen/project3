#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Movie.h"


using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    fstream file("C://Users//Alec//Downloads//archive");

    if (file.is_open())
    {
        string nul;
        getline(file,nul);
        string line;



        while(getline(file, line))
        {
            Movie currentMovie;
            istringstream s(line);



            string titleID;
            getline(s, titleID,','); //need something for strings and ints?
            currentMovie.setImdb_title_id(titleID);

            string title;
            getline(s, title,',');
            currentMovie.setTitle(title);
            //...etc



        }

    }
    file.close();



    return 0;
}
