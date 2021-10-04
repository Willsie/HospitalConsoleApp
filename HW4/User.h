// Author   : Wie Lie Sie.
// Class    : CSC 402 - Advanced Programming Languages.
// Project  : Hospital Application.
// Date     : 4/25/2021.

#ifndef HW4_USER_H
#define HW4_USER_H

#include <string>

using namespace std;

//User class that contains a private in roleID
//and setter, getters method for role ID and role name
class User
{

private:
    int roleId;
    string userName;

public:
    User();

    int getRoleId() const;

    void setRoleId(int id);

    void setUserName(const string &userNameInput);

    string getRoleName() const;

    const string &getUserName() const;
};

#endif //HW4_USER_H
