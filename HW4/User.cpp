// Author   : Wie Lie Sie.
// Class    : CSC 402 - Advanced Programming Languages.
// Project  : Hospital Application.
// Date     : 4/25/2021.

#include "User.h"

//Default user constructor
User::User()
{
}

//set user role id
void User::setRoleId(const int id)
{
    roleId = id;
}

//Return user role id
int User::getRoleId() const
{
    return roleId;
}

//Return current user role name
string User::getRoleName() const
{
    int roleID = roleId;
    string roleName;
    switch (roleID)
    {
        case 1:
            roleName = "System Admin";
            break;
        case 2:
            roleName = "Nurse";
            break;
        case 3:
            roleName = "Doctor";
            break;
        case 4:
            roleName = "Hospital Admin";
            break;
    }
    return roleName;
}

//Return current user name
const string &User::getUserName() const
{
    return userName;
}

//Set current user name
void User::setUserName(const string &userNameInput)
{
    userName = userNameInput;
    userName[0] = toupper(userName[0]);
}



