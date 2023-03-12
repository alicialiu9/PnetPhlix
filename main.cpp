#include "UserDatabase.h"
#include "User.h"
#include "Movie.h"
#include <iostream>
#include <string>


#include "treemm.h"
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

int main()
{
	UserDatabase udb;
	if (!udb.load("users.txt"))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << "users.txt" << "!" << endl;
		return 1;
	}
	for (int i = 0 ;i<5; i++)
	{
		cout << "Enter user email address (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;
		User* u = udb.get_user_from_email(email);
		if (u == nullptr)
			cout << "No user in the database has that email address." << endl;
		else
        {
            cout << "Found " << u->get_full_name() << endl;
//            cout << "Watch History: " << endl;
//            vector<string>user_WH =  u->get_watch_history();
//            for (int i = 0; i< user_WH.size(); i++)
//            {
//                cout << user_WH[i] << endl;
//            }
        }
	}
    
    vector<string> a (5, "hello");

    User me("alicia", "alicia.liu04gmail.com", a);
    
    assert(me.get_full_name() == "alicia");
    assert(me.get_email() == "alicia.liu04gmail.com");
 
    vector <string> ab = me.get_watch_history();
    for (int i = 0 ; i <a.size(); i++)
    {
        assert(ab[i] == "hello");
    }
    
    cout << "Passed" << endl;

    vector<string> d (2, "cool director");
    vector<string> actors (2, "cool actor");
    vector<string> g (1, "romcom");
    
    Movie yes("ID00001", "lols", "2050",d, actors, g, 5);

    assert(yes.get_id() == "ID00001");
    assert(yes.get_title() == "lols");

    for (int i = 0 ; i <yes.get_directors().size(); i++)
    {
        assert(yes.get_directors()[i]  == "cool director");
    }
    
    for (int i = 0 ; i <yes.get_actors().size(); i++)
    {
        assert(yes.get_actors()[i] == "cool actor");
    }
    
    for (int i = 0 ; i <yes.get_genres().size(); i++)
    {
        assert(yes.get_genres()[i] == "romcom");
    }
    
    assert(yes.get_rating() == 5);
    
    cout << "Passed" << endl;
    cout << "\n";
    

    
    TreeMultimap<int,int>::Iterator i; // doesn't point to any value
    if (!i.is_valid()) std::cout << "This will print!\n";
    
    
    TreeMultimap<std::string, int> tmm;
    tmm.insert("carey", 5);
    tmm.insert("carey", 6);
    tmm.insert("carey", 7);
    tmm.insert("david", 25);
    tmm.insert("david", 425);
    
    TreeMultimap<std::string,int>::Iterator it = tmm.find("carey");
    
//    while (it.is_valid()) {
//    std::cout << it.get_value() << std::endl;
//             it.advance();
//    }
    assert(it.is_valid());
    it.advance();
    assert(it.is_valid());
    it.advance();
    assert(it.is_valid());
    it.advance();
    assert(!it.is_valid());

    
    it = tmm.find("laura");
    assert(!it.is_valid());
    
    it = tmm.find("hello");
    assert(!it.is_valid());

    TreeMultimap<int, int> tmm2;
    tmm2.insert(2,45);
    tmm2.insert(2,4);
    tmm2.insert(2,4);
    tmm2.insert(2,45);
    tmm2.insert(42,45);
    tmm2.insert(42,1);
    tmm2.insert(42,1);
    tmm2.insert(0,1);
    tmm2.insert(0,3);
    

    TreeMultimap<int,int>::Iterator it2 = tmm2.find(42);
    assert(it2.is_valid());
    TreeMultimap<int,int>::Iterator it3 = tmm2.find(2);
    assert(it3.is_valid());
    TreeMultimap<int,int>::Iterator it4 = tmm2.find(3);
    assert(!it4.is_valid());
    
    // should print 45, 1, 1
    while (it2.is_valid()) {
    std::cout << it2.get_value() << std::endl;
             it2.advance();
            }

    
    
    cout << "Passed" << endl;
}
    
    



