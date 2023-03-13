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


bool Recommender::islessthanfunc(MovieAndRank me, MovieAndRank other) const
{
    //std::string movie_id;
   // int compatibility_score;
    if (me.compatibility_score < other.compatibility_score)
        return true;
    if (me.compatibility_score == other.compatibility_score)
    {
        float my_rating = (m_movie_database->get_movie_from_id(me.movie_id))->get_rating();
        float other_rating = (m_movie_database->get_movie_from_id(other.movie_id))->get_rating();
        
        if (my_rating < other_rating)
            return true;
        
        else if (my_rating == other_rating)
        {
            string my_title = (m_movie_database->get_movie_from_id(me.movie_id))->get_title();
            string other_title = (m_movie_database->get_movie_from_id(other.movie_id))->get_title();
            
            return my_title > other_title;
        }
    
    }
    return false;
}

void Recommender::merge_sort_MovieRank(vector<MovieAndRank> data, int begin, int end) const
{
    if (data.size() <= 1)
        return;
    
   size_t mid = data.size()/2;

    merge_sort_MovieRank(data, begin, mid);
    merge_sort_MovieRank(data, mid + 1, end);
   // 5. Merge the two halves using our merge function
    // n1 = size of left , n2 = size of right
    merge(data,mid-begin,end-mid);


//auto mid = begin + (end - begin) / 2;
//mergeSort(array, begin, mid);
//mergeSort(array, mid + 1, end);
//merge(array, begin, mid, end);
}

void Recommender::merge (vector<MovieAndRank>& data, int n1, int n2) const
 //(int data[], int n1, int n2, int temp[])
{
  int i1=0, i2=0, k=0;
    
   vector<MovieAndRank>::iterator A1 = data.begin();
    vector<MovieAndRank>::iterator A2 = data.begin();
    for (int i = 0; i<n1;i++)
    {
        A2++;
    }
   
 vector<MovieAndRank> temp;
    
  while (i1 < n1 || i2 < n2)
  {
    if (i1 == n1)
    temp[k++] = A2[i2++];
    else if (i2 == n2)
    temp[k++] = A1[i1++];
    else if (islessthanfunc(data[i1], A2[i2])) //(data[i1] <= A2[i2])
    temp[k++] = A1[i1++];
    else
    temp[k++] = A2[i2++];
  }
  for (int i=0;i<n1+n2;i++)
    data[i] = temp[i];
}


vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    std::map<std::string, int> scores;
    
    // get user and watch history
    User* u = m_user_database->get_user_from_email(user_email);
    vector<string> watch_hist = u->get_watch_history();
    
    cerr << "watch history: " << endl;
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
    vector<MovieAndRank> candidate_sort;
    
    map<string, int>::iterator it = scores.begin();
    while (it != scores.end())
    {
        MovieAndRank temp(it->first, it->second);
        cerr << it->first << endl;
        candidate_sort.push_back(temp);
        it++;
    }
    
    std::cerr << "size of movieandrank candidate vector: "  << candidate_sort.size()  << std::endl;

   //sort (candidate_sort.begin(), candidate_sort.end(), islessthanfunc);
    
    // quicksort 
    
    // Movie* c = m_movie_database->get_movie_from_id(m_id);
    merge_sort_MovieRank(candidate_sort, 0, candidate_sort.size());
    

    vector<MovieAndRank> recs;
    for(int i = 0 ; i < movie_count; i++)
    {
        recs[i] = candidate_sort[i];
    }
    
    return recs;
    
}
