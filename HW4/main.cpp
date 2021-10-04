// Author   : Wie Lie Sie.
// Class    : CSC 402 - Advanced Programming Languages.
// Project  : Hospital Application.
// Date     : 4/25/2021.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Patient.h"
#include "HospitalMethods.cpp"
#include "User.h"

using namespace std;

//Main class that run the Hospital App Program

//Function definitions
void switchRole(User &user);            //switch to a role
string toLowerCase(const string &str);  //convert string to lowerCase, return a string result
string stringInputFunc();               //ask user to enter a string, return a string result
int integerInputFunc();                 //ask user to enter an integer, return an integer result
void displayMenu(int roleID);           //display the menu options base on the role ID
//Menu function that will invoke methods based on user selection
void menuAction(User &user, const string &menuSelection,
                priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> &triagedList,
                vector<Patient> &treatedList);

//main part of the program that will start the program
int main()
{
    User user;
    bool quit = false;
    string stringInput;
    vector<Patient> patientList, treatedList;
    priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> triagedList;   //function Object here that implement function call Comparator>;
    logger.log("\n**************Welcome to the 402-Hospital App**************");
    logger.log("         Hospital App Starting...entering debug mode");
    logger.log("Please login as System Admin and switch to debug mode if necessary");
    try
    {
        switchRole(user);
        if (user.getRoleId() == 0)
        {
            logger.log("User exit the system...");
            exit(0);
        }
    } catch (const exception &ex)
    {
        logger.log("failed getting Role ID from user !");
        logger.log(ex.what());
    }

    while (!quit)
    {
        displayMenu(user.getRoleId());
        stringInput = stringInputFunc();                        //get user input string to select an option
        logger.log(user.getRoleName() + " selected: " + stringInput);
        logger.log("Press enter to start menu option...");
        menuAction(user, stringInput, triagedList,
                   treatedList); //execute user selection for action item such as treatPatient, etc
    }
    //return 0;
}

//convert string to all lower case
string toLowerCase(const string &str)
{
    string str_lowerCase;
    str_lowerCase = str;
    transform(str_lowerCase.begin(), str_lowerCase.end(), str_lowerCase.begin(), ::tolower);
    return str_lowerCase;
}

//return a string after asking user for a string input
string stringInputFunc()
{
    string str, str_lowerCase;
    logger.log("...entering string input...(enter help to display menu) ");
    getline(cin, str);
    str_lowerCase = toLowerCase(str);
    if (str_lowerCase == "quit")
    {
        logger.log("User exit the program...");
        exit(0);
    } else if (str_lowerCase == "help")
    {
        return str_lowerCase;
    } else
    {
        while (str_lowerCase == "")
        {
            getline(cin, str);
            str_lowerCase = toLowerCase(str);
        }
        return str;
    }
}

//return an integer after asking user for an integer input
int integerInputFunc()
{
    int integerInput;
    logger.log("...entering integer input...");
    try
    {
        cin >> integerInput;
    } catch (const exception &ex)
    {
        logger.log(ex.what());
    }
    return integerInput;
}

//Display menu options based on user role id and selection
void displayMenu(int roleID)
{
    string debugMode = to_string(logger.getDebugMode());
    if (debugMode == "1")
    {
        debugMode = "DEBUG MODE";
    } else
    {
        debugMode = "NORMAL MODE";
    }
    cout << "...current mode: " + debugMode << endl;
    switch (roleID)
    {
        case 1:     //if it is a system admin
            cout << ("     MENU:\n"
                     "         \"add\" - bulk add patients into the system from a file\n"
                     "         \"normal\" - switch to normal mode (log all operations of the system by each user to a file)\n"
                     "         \"debug\" - switch to debug mode (log all operations of the system by each user to a file)\n"
                     "         \"switch\" - switch user role\n"
                     "         \"help\" - display menu options\n"
                     "         \"quit\" - exit program") << endl;
            break;
        case 2:     //if it is a nurse
            cout << ("     MENU:\n"
                     "         \"add\" - add patient to the system\n"
                     "         \"switch\" - switch user role\n"
                     "         \"help\" - display menu options\n"
                     "         \"quit\" - exit program") << endl;
            break;
        case 3:     //if it is a doctor
            cout << ("     MENU:\n"
                     "         \"treat\" - treat a patient in triaged order\n"
                     "         \"printAll\" - display a patient's information as a report\n"
                     "         \"printTreated\" - display the report of all treated patients\n"
                     "         \"printNext\" - display the next patient to be treated\n"
                     "         \"switch\" - switch user role\n"
                     "         \"help\" - display menu options\n"
                     "         \"quit\" - exit program") << endl;

            break;
        case 4:     //if it is a hospital admin
            cout << ("     MENU:\n"
                     "         \"printTriage\" - display the report of all patients in triage\n"
                     "         \"treatAll\" - treat all patients\n"
                     "         \"printByDoctor - display patient names by doctor\n"
                     "         \"switch\" - switch user role\n"
                     "         \"help\" - display menu options\n"
                     "         \"quit\" - exit program") << endl;
            break;
        default:
            logger.log("Invalid Menu Option");
    }
}

//Function to switch user role or log in as other user
void switchRole(User &user)
{
    logger.log("\n0.Exit the program\n1.System Admin\n2.Nurse\n3.Doctor\n4.Hospital Admin\n");
    logger.log("Select your role number from above selection");
    user.setRoleId(integerInputFunc());
    logger.log("Enter your user name: ");
    user.setUserName(stringInputFunc());
    logger.log("User entered role ID: " + to_string(user.getRoleId()) + ", user name: " + user.getUserName());
    if (user.getRoleId() == 0)
    {
        logger.log("User exit the program...");
        exit(3);
    }
    logger.log("User logged in as " + user.getRoleName());
}

//Method will execute actions based on user input selection
void menuAction(User &user, const string &menuSelection,
                priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> &triagedList,
                vector<Patient> &treatedList)
{

    string doctorName;
    Patient patient;

    if (menuSelection == "help")
    {
        displayMenu(user.getRoleId());
    } else if (menuSelection == "switch")
    {
        switchRole(user);
    }
    switch (user.getRoleId())
    {
        case 1:      //if it is system admin
            if (menuSelection == "add")
            {
                HospitalMethods::addPatientsFromFile(triagedList, treatedList);       //add bulk patients from file
            } else if (menuSelection == "debug")
            {
                HospitalMethods::debugMode();                               //switch to debug mode
            } else if (menuSelection == "normal")
            {
                HospitalMethods::normalMode();                              //switch to normal mode
            }
            break;
        case 2:     //if it is a nurse
            if (menuSelection == "add")
            {
                HospitalMethods::addPatient(triagedList, treatedList);  //add patients from console
            }
            break;
        case 3:     //if it is a doctor
            if (menuSelection == "treat")
            {
                HospitalMethods::treatPatient(triagedList, treatedList);       //treat a patient in triaged order
            } else if (menuSelection == "printTreated")
            {
                HospitalMethods::printTreated(treatedList);                 //display the report of all treated patients
            } else if (menuSelection == "printNext")
            {
                HospitalMethods::printNext(triagedList);
            } else if (menuSelection == "printAll")
            {
                HospitalMethods::printAll(triagedList, treatedList);
            }
            break;
        case 4:      //if it is hospital admin
            if (menuSelection == "printTriage")
            {
                HospitalMethods::printTriage(triagedList, treatedList);       //treat a patient in triaged order
            } else if (menuSelection == "treatAll")
            {
                HospitalMethods::treatAllPatients(triagedList, treatedList);        //treat all patients
            } else if (menuSelection == "printByDoctor")
            {
                logger.log("Please enter doctor's name: ");
                doctorName = stringInputFunc();
                HospitalMethods::printPatientByDoctor(doctorName, triagedList, treatedList); //print patients by doctor
            }
            break;
        default:
            logger.log("Invalid Role");
    }
}




