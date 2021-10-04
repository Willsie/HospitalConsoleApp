// Author   : Wie Lie Sie.
// Class    : CSC 402 - Advanced Programming Languages.
// Project  : Hospital Application.
// Date     : 4/25/2021.

#ifndef HW3_LOGGER_H
#define HW3_LOGGER_H

#include <string>   //insert string class from library
#include <iostream> //insert filename I/O stream

using namespace std;    //import classes from namespace std / using directive to ask the compiler to check the std namespace when resolving identifiers with no prefix

class Logger
{

private:
    Logger();

    bool debugMode = true;

public:
    // static method that returns pointer to logger
    static Logger &getLogger();

    // logger method that prints message to console
    void log(string);

    void setDebugMode(bool);

    bool getDebugMode();

};

extern Logger &logger;

#endif //HW3_LOGGER_H
