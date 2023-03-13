#include "MovieDatabase.h"
#include "Movie.h"

#include <fstream>
#include <iostream>
using namespace std;

MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
}

void load_list(string list, vector<string>& v){
    string temp;
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i] != ',')
            temp += list[i];
        
        else
        {
            v.push_back(temp);
            temp = "";
        }
    }
    // add last one in list
    v.push_back(temp);
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);    // infile is a name of our choosing
    if (!infile )
    {
        cerr << "Error: Cannot open data.txt!" << endl;
        return false;
    }
    
    string line;
    
    string movie_id;
    string title;
    string release_year;
    vector<string> directors;
    vector<string> actors;
    vector<string> genres;
    float rating;
    
   while (getline(infile, line)) {
       
       if (!infile)
       {
           cerr << "End of file when trying to read a string" << endl;
           break;
       }
       if (line.empty())
       {
           continue;
       }
       movie_id = line;
       getline(infile, title);
       getline(infile, release_year);
       
       // get each director and put into directors vector
       string director_list;
       string unique_dir;
       getline(infile, director_list); // director list is now dir1, dir2, dir3
       
       load_list(director_list, directors);
       
       
       //get each actor
       string actor_list;
       string unique_actor;
       getline(infile, actor_list); // actor list is now actor1, actor2, actor3...
       load_list(actor_list, actors);
    
       //get each genre
       string genre_list;
       string unique_genre;
       getline(infile, genre_list); // gnere list is now genre1, genre2, genre3..
       load_list(genre_list, genres);
       
       infile >> rating;
       infile.ignore(10000, '\n');
    
       Movie* movie = new Movie(movie_id, title, release_year, directors, actors, genres, rating);
       m_movies.push_back(movie);
       m_movie_db_id.insert(movie_id, movie);
       
       // insert into director, actor, genre tree
       for (int i = 0; i < directors.size(); i++)
       {
           m_movie_db_dir.insert(directors[i],movie);
       }
       
       for (int i = 0; i < actors.size(); i++)
       {
           m_movie_db_actor.insert(actors[i],movie);
       }
       
       for (int i = 0; i < genres.size(); i++)
       {
           m_movie_db_genre.insert(genres[i],movie);
       }
       directors.clear();
       actors.clear();
       genres.clear();

    }
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap <string, Movie*>::Iterator it = m_movie_db_id.find(id);
    if (it.is_valid())
    {
        return (it.get_value());
    }
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
//    TreeMultimap <std::vector<std::string>, Movie*>::Iterator it = m_movie_db_dir.find(director);
//    if (it.is_valid())
//    {
//        return (it.get_value());
//    }
//    return nullptr;
    
     return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

// MovieDatabase::~MovieDatabase() {}
