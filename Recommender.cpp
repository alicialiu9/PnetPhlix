#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <map>

#include<iostream>

using namespace std;


Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_user_database = &user_database;
    m_movie_database = &movie_database; 
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    std::map<std::string, int> scores;
    
    // get user and watch history
    User* u = m_user_database->get_user_from_email(user_email);
    vector<string> watch_hist = u->get_watch_history();
    
    for (int i = 0 ; i < watch_hist.size(); i++ )
    {
        cerr << watch_hist[i] << endl; 
    }
    
    //iterate through watch history
    for (int i = 0 ; i < watch_hist.size(); i++ )
    {
        Movie* m = m_movie_database->get_movie_from_id(watch_hist[i]);
        
        //get directors of this movie
        vector<string> d = m->get_directors();
        // iterate through directors
        for (int i = 0; i < d.size(); i++)
        {
            vector<Movie*> movies_with_dir = m_movie_database->get_movies_with_director(d[i]);
            // go through each movie with this director
            for (int i = 0 ; i < movies_with_dir.size(); i++)
            {
                scores[movies_with_dir[i]->get_id()] += 20;
            }
        }
        
        //get actors of this movie
        vector<string> a = m->get_actors();
        
        // iterate through actors
        for (int i = 0; i < a.size(); i++)
        {
            vector<Movie*> movies_with_actor = m_movie_database->get_movies_with_actor(a[i]);
            // go through each movie with this actor
            for (int i = 0 ; i < movies_with_actor.size(); i++)
            {
                scores[movies_with_actor[i]->get_id()] += 30;
            }
        }
        
        //get genres of this movie
        vector<string> g = m->get_genres();
        
        // iterate through genres
        for (int i = 0; i < g.size(); i++)
        {
            vector<Movie*> movies_with_genre = m_movie_database->get_movies_with_genre(g[i]);
            // go through each movie with this genre
            for (int i = 0 ; i < movies_with_genre.size(); i++)
            {
                scores[movies_with_genre[i]->get_id()] += 1;
            }
        }
        
    }
    
    
    //iterate through watch history
    for (int i = 0 ; i < watch_hist.size(); i++)
    {
        // delete map elements that match
        map<string, int>::iterator it = scores.begin();
        while (it != scores.end())
        {
            if (watch_hist[i] == it->first)
                it = scores.erase(it);
            else
                it++;
        }
    }
    
    
    std::cerr << scores.size()  << std::endl;
    // test first
    // Movie* c = m_movie_database->get_movie_from_id(m_id);
    

    // map has all possible candidates

    
    
    
    // movie_count = N
    
    // (*m_movie_database)
    // TreeMultimap<std::string,int>::Iterator it = tmm.find("carey");
    
    
    return vector<MovieAndRank>();  // Replace this line with correct code.
}
