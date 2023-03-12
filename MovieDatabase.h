#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;
   // ~MovieDatabase()

  private:
    // map IDs, directors, actors, and genres to movies
    TreeMultimap <std::string, Movie*> m_movie_db_id;
    TreeMultimap <std::vector<std::string>, Movie*> m_movie_db_dir;
    TreeMultimap <std::vector<std::string>, Movie*> m_movie_db_actor;
    TreeMultimap <std::vector<std::string>, Movie*> m_movie_db_genre;
    
    // to delete the dynamically allocated movies
    std::vector<Movie*> m_movies;

};

#endif // MOVIEDATABASE_INCLUDED
