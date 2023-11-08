#include <fstream>

#include "./lib/jobsysteminterface.h"

class Interpreter
{
private:
    // DECLARE FLOWSCRIPT RESERVED KEYWORDS
    std::string keywords[4] = {"digraph",
                               "input",
                               "output",
                               "split"};
    std::vector<std::string> codeLines;

    std::string input;
    std::string output;
    std::vector<std::string> processes;

    int errorCode;
    std::string errorMessage;
    int errorLine;

    void generateError(int errorCode, std::string errorMessage, int errorLine);

public:
    Interpreter()
    {
        errorCode = 0;
        errorMessage = "";
        errorLine = -1;
    }

    int getErrorCode() { return errorCode; }
    std::string getErrorMessage() { return errorMessage; }
    int getErrorLine() { return errorLine; }

    void loadFile(std::string filename);
    void parse();
};