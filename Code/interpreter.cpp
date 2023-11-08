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

void Interpreter::generateError(int errorCode, std::string errorMessage, int errorLine)
{
    std::cout << "ERROR!" << std::endl;
    this->errorCode = errorCode;
    this->errorMessage = errorMessage;
    this->errorLine = errorLine;
    return;
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
                generateError(1, "Process cannot start with digit", lineNumber);
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
                // Syntax errors
                if (codeLines[i].find("]") == std::string::npos)
                {
                    generateError(1, "Missing closing bracket", lineNumber);
                    return;
                }
                if (codeLines[i].find("]") < j)
                {
                    generateError(1, "Closing bracket before opening bracket", lineNumber);
                    return;
                }

                // Get argument
                std::string arg = codeLines[i].substr(j + 1, codeLines[i].find("]") - codeLines[i].find("[") - 1);
                // std::cout << arg << std::endl;

                // Handle process
                if (arg.find("shape=\"square\"") != std::string::npos)
                {
                    std::cout << "square" << std::endl;
                }
                // Handle conditional (if statement)
                else if (arg.find("shape=\"diamond\"") != std::string::npos)
                {
                    std::cout << "diamond" << std::endl;
                }
                // Handle conditional (switch statement)
                else if (arg.find("shape=\"trapezium\"") != std::string::npos)
                {
                    std::cout << "trapezium" << std::endl;
                }
                // Handle branching (multi-process)
                else if (arg.find("shape=\"point\"") != std::string::npos)
                {
                    std::cout << "point" << std::endl;
                }

                // Handle branching process (multi-process)
                if (arg.find("style=\"dashed\"") != std::string::npos)
                {
                    std::cout << "multi" << std::endl;
                }

                // Handle label
                if (arg.find("label=\"") != std::string::npos)
                {
                    // Get label
                    std::string label = "";
                    for (int x = arg.find("label=\"") + 7; x < arg.size(); x++)
                    {
                        if (arg[x] != '\"')
                        {
                            label += arg[x];
                        }
                        else
                        {
                            break;
                        }
                    }
                    std::cout << label << std::endl;
                }

                // Skip to the end of the argument
                j += arg.size() + 1;
                // STATEMENT SHOULD END AFTER THIS (EVERYTHING ELSE IS IGNORED)
                break;
            }

            // Dependency (Arrow)
            else if (c == '-' && codeLines[i][j + 1] == '>')
            {
                // std::cout << "arrow ";
                // STATE DEPENDENCY HERE
                if (rightToken != "")
                {
                    std::cout << rightToken
                              << " depends on "
                              << leftToken << std::endl;
                    leftToken = rightToken;
                    rightToken = "";
                }
                else
                    // Change side
                    left = !left;
                // Skip over the > symbol
                j++;
            }
            // Invalid character
            else if (c != ' ' && c != '{' && c != '}')
            {
                generateError(1, "Unknown symbol", lineNumber);
                return;
            }
            // std::cout << leftToken << "|" << rightToken << std::endl;

            // Keep checking if token is reserved word
            // for (int x = 0; x < 4; x++)
            // {
            //     if (keywords[x] == leftToken)
            //         std::cout << leftToken << std::endl;
            //     if (keywords[x] == rightToken)
            //         std::cout << rightToken << std::endl;
            // }
        }

        // STATE DEPENDENCY HERE TOO
        if (rightToken != "")
        {
            std::cout << rightToken
                      << " depends on "
                      << leftToken << std::endl;
        }
    }
}
