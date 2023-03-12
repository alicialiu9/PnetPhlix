#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream> // CHECK !!!


using namespace std;

UserDatabase::UserDatabase()
{
    // Replace this line with correct code.
}

bool UserDatabase::load(const string& filename)
{
    // use getline
    
    std::ifstream file(filename);
       if (!file.is_open()) {
           return false;
       }

    string line;
    string name;
    string email;
    std::vector<std::string> watch_history;
    
    
//       while (getline(input, line)) {
//          stringstream ss(line);
//          string name, email;
//           int num_movies;
//           ss >> name >> email >> num_movies;
//           if (!email.empty()) {
//               User user(name, email);
//               for (int i = 0; i < num_movies; i++) {
//                   std::string movie_id;
//                   ss >> movie_id;
//                   user.add_movie(movie_id);
//               }
//               m_users.insert(email, user);
//           }
//       }
    
    User* user = new User(name, email, watch_history);
    m_user_database.insert(email, user);
//
//       file.close();
//       return true;
    
    
    
    return false;  // Replace this line with correct code.
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
