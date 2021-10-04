// Author   : Wie Lie Sie.
// Class    : CSC 402 - Advanced Programming Languages.
// Project  : Hospital Application.
// Date     : 4/25/2021.

#include "logger.h" //include logger header file
#include <iostream> //insert filename I/O stream
#include <fstream>
#include <chrono>

// Logger class is a singleton class that is being shared

using namespace std;    //import classes from namespace std / using directive to ask the compiler to check the std namespace when resolving identifiers with no prefix

Logger::Logger()
{}

// static method that returns pointer to logger
Logger &Logger::getLogger()
{
    static Logger logger;
    return logger;
}

// logger method that prints message to console
void Logger::log(string message)
{
    if (debugMode)
    {
        cout << message << endl;
    } else
    {
        try
        {
            ofstream myFile("log.txt", std::fstream::app);
            myFile << message + "\n";
        } catch (exception &ex)
        {
            cout << ex.what() << endl;
            cout << "Failed to log into \"log.txt\"" << endl;
        }
    }
}

void Logger::setDebugMode(bool value)
{
    if (value == true)
    {
        logger.log("Switching to debug mode");
    } else
    {
        logger.log("Switching to normal mode");
    }
    Logger::debugMode = value;
}

bool Logger::getDebugMode()
{
    return debugMode;
}

Logger &logger = Logger::getLogger();




