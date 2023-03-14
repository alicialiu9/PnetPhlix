#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include<iostream>

using namespace std;


Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_user_database = &user_database;
    m_movie_database = &movie_database; 
}


bool Recommender::comp(MovietoCompare me, MovietoCompare other)
{
    if (me.m_rank.compatibility_score > other.m_rank.compatibility_score)
        return true;
    
    if (me.m_rank.compatibility_score == other.m_rank.compatibility_score)
    {
        if (me.movie_rating > other.movie_rating)
            return true;
        
        else if (me.movie_rating == other.movie_rating)
        {
            return me.movie_title < other.movie_title;
        }
        
    }
    return false;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    std::map<std::string, int> scores;
    
    // get user and watch history
    User* u = m_user_database->get_user_from_email(user_email);
    vector<string> watch_hist = u->get_watch_history();
    
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
    
    std::cerr << "size of candidate map before deleting matches: "  << scores.size()  << std::endl;


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
            {
                it++;
            }
        }
    }
    
    // map has all possible candidates
    std::cerr << "size of candidate map: "  << scores.size()  << std::endl;
    
    // put as MovieAndRank objects
    vector<MovieAndRank> candidates;
    
    map<string, int>::iterator it = scores.begin();
    while (it != scores.end())
    {
        MovieAndRank temp(it->first, it->second);
        candidates.push_back(temp);
        it++;
    }
    
    std::cerr << "size of movieandrank candidate vector: "  << candidates.size()  << std::endl;
    
    vector <MovietoCompare> candidates_to_sort;
    for (int i = 0; i < candidates.size();i++)
    {
        string id = candidates[i].movie_id;
        string title = m_movie_database->get_movie_from_id(id)->get_title();
        float rating = m_movie_database->get_movie_from_id(id)->get_rating();
        MovietoCompare temp(title, rating, candidates[i]);
        candidates_to_sort.push_back(temp);
    }

   sort (candidates_to_sort.begin(), candidates_to_sort.end(), comp);

    
    int num_recs_to_give = 0;
    if (movie_count > candidates_to_sort.size())
        num_recs_to_give = candidates_to_sort.size();
    else
        num_recs_to_give = movie_count;
    
    vector<MovieAndRank> recs;
    for(int i = 0 ; i < num_recs_to_give; i++)
    {
        recs.push_back(candidates_to_sort[i].m_rank);
    }
    
    return recs;

}
