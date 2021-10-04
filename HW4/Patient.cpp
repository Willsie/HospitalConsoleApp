// Author   : Wie Lie Sie.
// Class    : CSC 402 - Advanced Programming Languages.
// Project  : Hospital Application.
// Date     : 4/25/2021.

#include "Patient.h"
#include <string>
#include "logger.h"

using namespace std;

int Patient::patientIdCounter = 0;  //unique patientID

Patient::Patient()
{                 //default constructor that will assign unique patientID to
    patientId = patientIdCounter++;
}

//toString method that will display patient information
void Patient::toString()
{
    string treatedStatus;
    if (treated == 1)
    {
        treatedStatus = "Already Treated";
    } else
    {
        treatedStatus = "Not Treated";
    }
    logger.log("\n*******PATIENT INFORMATION*******");
    logger.log("Patient ID: " + to_string(patientId));
    logger.log("First name: " + firstName);
    logger.log("Middle name: " + middleName);
    logger.log("Last name: " + lastName);
    logger.log("Suffix: " + suffix);
    for (string const &ailments : ailmentsList)
    {
        logger.log("Ailments: " + ailments);
    }
    logger.log("Doctor: " + doctor);
    logger.log("Treated Status: " + treatedStatus);
    logger.log("Priority: " + to_string(priority));
    logger.log("*********************************\n");
}

//overloaded < operator that compare rhs.priority with lhs.priority
bool Patient::operator<(const Patient &rhs) const
{
    return priority > rhs.priority;
}

string Patient::getFirstName() const
{
    return firstName;
}

void Patient::setFirstName(const string &firstNameInput)
{
    firstName = firstNameInput;
    firstName[0] = toupper(firstName[0]);
}


string Patient::getMiddleName() const
{
    return middleName;
}

void Patient::setMiddleName(const string &middleNameInput)
{
    middleName = middleNameInput;
    middleName[0] = toupper(middleName[0]);

}

string Patient::getLastName() const
{
    return lastName;
}

void Patient::setLastName(const string &lastNameInput)
{
    lastName = lastNameInput;
    lastName[0] = toupper(lastName[0]);
}

string Patient::getSuffix() const
{
    return suffix;
}

void Patient::setSuffix(const string &suffixInput)
{
    suffix = suffixInput;
    suffix[0] = toupper(suffix[0]);
}

vector<string> Patient::getAilments() const
{
    return ailmentsList;
}

//Methods that will add ailments description to patient
void Patient::setAilments(const vector<string> &myAilment)
{
    ailmentsList.clear();
    for (string const &ailment : myAilment)
    {
        ailmentsList.push_back(ailment);
    }
}

string Patient::getDoctor() const
{
    return doctor;
}

void Patient::setDoctor(const string &doctorInput)
{
    int delimiterLoc = doctorInput.find(" ");
    doctor = doctorInput;
    lastName[0] = toupper(lastName[0]);
    lastName[delimiterLoc + 1] = toupper(lastName[delimiterLoc + 1]);
}

int Patient::getTreatedStatus() const
{
    return treated;
}

void Patient::setTreatedStatus(const int treatedInput)
{
    treated = treatedInput;
}

int Patient::getPriority() const
{
    return priority;
}

void Patient::setPriority(const int priorityInput)
{
    priority = priorityInput;
}

int Patient::getPatientId() const
{
    return patientId;
}

void Patient::addAilments(const string &myAilment)
{
    ailmentsList.push_back(myAilment);
}

