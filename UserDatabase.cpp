#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream> // CHECK !!!
#include <iostream>
using namespace std;

UserDatabase::UserDatabase()
{
    // Replace this line with correct code.
}

bool UserDatabase::load(const string& filename)
{
    ifstream infile(filename);    // infile is a name of our choosing
    if (!infile )              
    {
        cerr << "Error: Cannot open data.txt!" << endl;
        return false;
    }
    
    string line;
    string name;
    string email;
    int num_movies;
    std::vector<std::string> watch_history;
    
   while (getline(infile, line)) {
       
       if ( ! infile)
       {
           cerr << "End of file when trying to read a string" << endl;
           break;
       }
       if (line.empty())
       {
           continue;
       }
       name = line;
       getline(infile, email);
       infile >> num_movies;
       infile.ignore(10000, '\n');
       while (getline(infile, line) && !(line.empty()))
       {
           watch_history.push_back(line);
       }
       User* user = new User(name, email, watch_history);
       m_users.push_back(user);
       m_user_database.insert(email, user);
       watch_history.clear();

    }
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap <std::string, User*>::Iterator it = m_user_database.find(email);
    if (it.is_valid())
    {
        return (it.get_value());
    }
    return nullptr;
}

UserDatabase::~UserDatabase()
{
    for (vector<User*>::iterator it = m_users.begin(); it != m_users.end();it++)
    {
        delete *it;
    }
}
