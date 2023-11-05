#include "interpreter.h"

void Interpreter::loadFile(std::string filename)
{
    std::ifstream myfile(filename);
    std::string line;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            // Delete double spaces
            std::size_t doubleSpace = line.find("  ");
            while (doubleSpace != std::string::npos)
            {
                line.erase(doubleSpace, 1);
                doubleSpace = line.find("  ");
            }
            // Append line to code lines
            codeLines.push_back(line);
        }
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
}

void Interpreter::parse()
{
    int lineNumber;
    // For every line of code
    for (int i = 0; i < codeLines.size(); i++)
    {
        // std::cout << codeLines[i] << ": ";
        // Increment the line number
        lineNumber = i + 1;
        // Split each character
        std::string leftToken = "";
        std::string rightToken = "";
        bool left = true;

        // For each character
        for (int j = 0; j < codeLines[i].size(); j++)
        {
            char c = codeLines[i][j];
            // std::cout << c << ": ";
            // Syntax Error
            if (std::isdigit(c) && leftToken.size() == 0)
            {
                std::cout << "ERROR" << std::endl;
                errorCode = 1;
                errorMessage = "Process cannot start with digit";
                errorLine = lineNumber;
                return;
            }

            // Process name
            else if (std::isalnum(c))
                if (left)
                    leftToken += c;
                else
                    rightToken += c;

            // Argument list
            else if (c == '[')
            {
                // Get argument
                std::string arg = codeLines[i].substr(j + 1, codeLines[i].find("]") - codeLines[i].find("[") - 1);
                std::cout << arg << std::endl;

                // SPLIT ARG INTO TOKENS (BY SPACE)

                if (arg == "shape=\"square\"")
                {
                }
                else if (arg == "shape=\"diamond\"")
                {
                }
                else if (arg == "shape=\"trapezium\"")
                {
                }
                else if (arg == "shape=\"point\"")
                {
                }

                if (arg == "style=\"dashed\"")
                {
                }

                // Skip to the end of the argument
                j += arg.size() + 1;
                // STATEMENT SHOULD END AFTER THIS (EVERYTHING ELSE IS IGNORED)
                break;
            }

            // Dependency (Arrow)
            else if (c == '-' && codeLines[i][j + 1] == '>')
            {
                // Change side
                left = !left;
                j++;
                // std::cout << "arrow ";
                // STATE DEPENDENCY HERE (IF LEFT TOKEN != "")
            }
            // std::cout << leftToken << "|" << rightToken << std::endl;
        }
    }
}