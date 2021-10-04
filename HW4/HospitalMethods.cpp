// Author   : Wie Lie Sie.
// Class    : CSC 402 - Advanced Programming Languages.
// Project  : Hospital Application.
// Date     : 4/25/2021.

#ifndef HW4_HOSPITALMETHODS
#define HW4_HOSPITALMETHODS

#include <queue>
#include <algorithm>
#include "CompareByPriority.cpp"
#include "Patient.h"
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "logger.h"
#include <string>

using namespace std;

class HospitalMethods
{

public:
    /*****************Functions for Doctor role:*****************/

    //Treat patient in triaged order
    static void treatPatient(priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> &triagedList,
                             vector<Patient> &treatedList)
    {
        Patient temp;
        string patientID, fullName;
        try
        {
            temp = triagedList.top();
            patientID = to_string(temp.getPatientId());
            fullName = temp.getFirstName() + " " + temp.getMiddleName() + " " + temp.getLastName() + " " +
                       temp.getSuffix();
            logger.log("Treating patient with ID: " + patientID);
            temp.toString();
            logger.log("...patient is under treatment...");
            int random = rand() % 3 + 1;
            sleep(random);
            triagedList.pop();
            treatedList.push_back(temp);
            logger.log("Patient ID: " + patientID + ", " + fullName + " was under care for " + to_string(random) +
                       " seconds and has been successfully treated\n");
        } catch (exception &ex)
        {
            logger.log(ex.what());
            logger.log("treatPatient has failed");
        }
    }

    //Print patients from treated list
    static void printTreated(const vector<Patient> &treatedList)
    {
        try
        {
            for (Patient patient: treatedList)
            {
                patient.toString();
            }
        } catch (exception &ex)
        {
            logger.log(ex.what());
            logger.log("printTreated function has failed");
        }
    }

    //Print next patient from triaged list
    static void printNext(const priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> &triagedList)
    {
        try
        {
            Patient patient = triagedList.top();
            patient.toString();
        } catch (exception &ex)
        {
            logger.log(ex.what());
            logger.log("printNext function has failed !");
        }
    }

    //Print all patients
    static void printAll(priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> triagedList,
                         const vector<Patient> &treatedList)
    {
        Patient patient;
        try
        {
            logger.log("##########PATIENT TRIAGED LIST##########");
            while (!triagedList.empty())
            {
                patient = triagedList.top();
                patient.toString();
                triagedList.pop();
            }
            logger.log("###########END OF TRIAGED LIST##########\n\n");
            logger.log("##########PATIENT TREATED LIST##########");
            for (Patient patient: treatedList)
            {
                patient.toString();
            }
            logger.log("###########END OF TREATED LIST##########\n");
        } catch (exception &ex)
        {
            logger.log(ex.what());
            logger.log("printAll function has failed");
        }
    }


    /*****************Functions for Nurse role:*****************/

    //Add patients to the system - triaged list
    static void addPatient(priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> &triagedList,
                           vector<Patient> &treatedList)
    {
        string firstName, middleName, lastName, suffix, doctor, strAilments, temp;
        int treated, priority = 1000;
        vector<string> ailmentsList;
        Patient patient;
        bool quitAdding = true;
        try
        {
            while (quitAdding)
            {
                cin.ignore(1, '\n');
                logger.log("Patient's First Name: ");
                getline(cin, firstName);
                logger.log("Patient's Middle Name: ");
                getline(cin, middleName);
                logger.log("Patient's Last Name: ");
                getline(cin, lastName);
                logger.log("Patient's Suffix: ");
                getline(cin, suffix);
                logger.log("Doctor's Name: ");
                getline(cin, doctor);
                logger.log("Is Patient treated ? 0 - NOT treated, 1 - treated: ");
                cin >> treated;
                logger.log("Patient's Priority ? enter integer value (default is 1000): ");
                cin >> priority;
                cin.ignore(1, '\n');
                logger.log("Patient's ailments ? - enter each ailments separated by a comma (ex: cough, fever 101): ");
                getline(cin, strAilments);
                patient.setFirstName(firstName);
                patient.setMiddleName(middleName);
                patient.setLastName(lastName);
                patient.setSuffix(suffix);
                patient.setDoctor(doctor);
                patient.setTreatedStatus(treated);
                patient.setPriority(priority);
                //add ailments to the vector of ailments
                for (int i = 0, j = 0; i < strAilments.size(); i++)
                {
                    if (strAilments.at(i) == ',' || strAilments.at(i) == '\0')
                    {
                        ailmentsList.push_back(strAilments.substr(j, i - j)); //pushing the sub string
                        j = i + 1;
                    }
                }
                patient.setAilments(ailmentsList);
                if (patient.getTreatedStatus() == 1)
                {
                    treatedList.push_back(patient);
                } else
                {
                    triagedList.push(patient);
                }
                logger.log("Add Next Patient ? (N/Y)");
                cin >> temp;
                transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                if (temp == "n")
                {
                    quitAdding = false;
                }
                ailmentsList.clear();
                strAilments.clear();
            }
        } catch (exception &ex)
        {
            logger.log(ex.what());
            logger.log("addPatient function has failed !");
        }
    }

    /*****************Functions for System Admin role:*****************/

    //Switch to debug mode
    static void debugMode()
    {
        logger.setDebugMode(true);
    }

    //Switch to normal mode
    static void normalMode()
    {
        logger.setDebugMode(false);
    }

    //Adding patients from file
    static void addPatientsFromFile(priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> &triagedList,
                                    vector<Patient> &treatedList)
    {
        string fileName, lineIn, tempStr, ailmentInput, inputKey;
        int delimiterLoc, tempInt;
        vector<string> ailments;
        bool validInputFound;

        ifstream fileIn;
        try
        {
            //do-while loop that will keep asking user to enter correct file name or type exit to exit the program
            do
            {
                logger.log("Enter file name: ");
                cin >> fileName;
                if (fileName == "quit")
                {
                    logger.log("User exit the program: ");
                    exit(3);
                }
                fileIn.open(fileName);
                logger.log("Opening file: " + fileName);
            } while (!fileIn);

            validInputFound = false;
            //while if validInputFound is false loop to get input from file input
            //and assign the value of input values to a patient object
            //then add patient object to either a treated list or triaged list
            //if there is any exception occur, it will display exception notification and close the file stream

            while (!validInputFound)
            {
                getline(fileIn, lineIn);
                if (lineIn.empty())
                {
                    getline(fileIn, lineIn);
                }
                if (fileIn.eof())
                {
                    cout << "EOF before reading line input" << endl;
                    break;
                } else if (fileIn.fail())
                {
                    fileIn.clear();
                }

                delimiterLoc = lineIn.find(":");
                inputKey = lineIn.substr(0, delimiterLoc);
                tempStr = lineIn.substr(delimiterLoc + 1);
                if (inputKey == "firstName")
                {
                    Patient patient;
                    patient.setFirstName(tempStr);
                    getline(fileIn, lineIn);
                    delimiterLoc = lineIn.find(":");
                    inputKey = lineIn.substr(0, delimiterLoc);
                    while (!lineIn.empty() && !inputKey.empty())
                    {
                        tempStr = lineIn.substr(delimiterLoc + 1);
                        if (inputKey == "middleName")
                        {
                            patient.setMiddleName(tempStr);
                        } else if (inputKey == "lastName")
                        {
                            patient.setLastName(tempStr);
                        } else if (inputKey == "suffix")
                        {
                            patient.setSuffix(tempStr);
                        } else if (inputKey == "ailment")
                        {
                            patient.addAilments(tempStr);
                        } else if (inputKey == "doctor")
                        {
                            patient.setDoctor(tempStr);
                        } else if (inputKey == "treated")
                        {
                            patient.setTreatedStatus(stoi(tempStr));
                        } else if (inputKey == "priority")
                        {
                            patient.setPriority(stoi(tempStr));
                        } else
                        {
                            break;
                        }
                        getline(fileIn, lineIn);
                        if (fileIn.eof())
                        {
                            validInputFound = true;
                            break;
                        }
                        delimiterLoc = lineIn.find(":");
                        inputKey = lineIn.substr(0, delimiterLoc);
                    }
                    if (patient.getTreatedStatus() == 1) {
                        treatedList.push_back(patient);
                    } else {
                        triagedList.push(patient);
                    }
                }
            }
        } catch (exception &ex)
        {
            fileIn.close();
            logger.log("Closing file input stream after an exception occurred...");
            logger.log(ex.what());
        }
        fileIn.close();
        logger.log("Closing file input stream...");
    }

    /*****************Functions for System Admin role:*****************/
    //Print out a report of all the patients in triage.
    static void printTriage(priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> triagedList,
                            const vector<Patient> &treatedList)
    {
        Patient patient;
        try
        {
            logger.log("##########PATIENT TRIAGED LIST##########");
            while (!triagedList.empty())
            {
                patient = triagedList.top();
                patient.toString();
                triagedList.pop();
            }
            logger.log("###########END OF TRIAGED LIST##########\n\n");
        } catch (exception &ex)
        {
            logger.log(ex.what());
            logger.log("printTriage function has failed");
        }
    }

    //Treat all patients.
    static void treatAllPatients(priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> &triagedList,
                                 vector<Patient> &treatedList)
    {
        Patient patient;
        try
        {
            logger.log("###########Treating All Patients###########");
            while (!triagedList.empty())
            {
                treatPatient(triagedList, treatedList);
            }
            logger.log("###########All Patients are Treated###########");
        } catch (exception &ex)
        {
            logger.log(ex.what());
            logger.log("treatAllPatients function has failed");
        }
    }

    //Print out of all patients by doctor.
    static void printPatientByDoctor(const string &doctor,
                                     const priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> &triagedList,
                                     const vector<Patient> &treatedList)
    {
        priority_queue<Patient, vector<Patient>, CompareByPriority<Patient>> triagedListTemp = triagedList;
        Patient patient;
        try
        {
            logger.log("#####PATIENT LIST under Dr. " + doctor + "#####");
            while (!triagedListTemp.empty())
            {
                patient = triagedListTemp.top();
                if (patient.getDoctor() == doctor)
                {
                    patient.toString();
                }
                triagedListTemp.pop();
            }
            for (Patient patient: treatedList)
            {
                if (patient.getDoctor() == doctor)
                {
                    patient.toString();
                }
            }
            logger.log("###########END OF PATIENT LIST##########\n\n");
        } catch (exception &ex)
        {
            logger.log(ex.what());
            logger.log("printPatientByDoctor function has failed");
        }
    }
};

#endif //HW4_HOSPITALMETHODS