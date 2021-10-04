// Author   : Wie Lie Sie.
// Class    : CSC 402 - Advanced Programming Languages.
// Project  : Hospital Application.
// Date     : 4/25/2021.

#include <string>
#include <vector>

#ifndef HW4_PATIENT_H
#define HW4_PATIENT_H

using namespace std;

// Patient class that has patient information
class Patient
{

private:
    //Private variables related to patient's information
    string firstName, middleName, lastName, suffix, doctor;
    int treated = 0, priority = 1000, patientId;
    vector<string> ailmentsList;

public:

    //public methods that consist of setters and getters method as well as constructor
    //and overloaded < comparison
    Patient();

    int getPatientId() const;

    void toString();

    bool operator<(const Patient &rhs) const;

    string getFirstName() const;

    void setFirstName(const string &firstName);

    string getMiddleName() const;

    void setMiddleName(const string &middleNameInput);

    string getLastName() const;

    void setLastName(const string &lastName);

    string getSuffix() const;

    void setSuffix(const string &suffix);

    vector<string> getAilments() const;

    void setAilments(const vector<string> &ailment);

    string getDoctor() const;

    void setDoctor(const string &doctorInput);

    int getTreatedStatus() const;

    void setTreatedStatus(int treated);

    int getPriority() const;

    void setPriority(int priority);

    static int patientIdCounter;

    void addAilments(const string &ailment);
};

#endif //HW4_PATIENT_H
