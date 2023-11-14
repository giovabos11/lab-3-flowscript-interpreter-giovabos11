#include "interpreter.h"

using namespace std;

// Example Job 1
string sortString(string a)
{
    int i, key, j, n = a.size();
    for (i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
    return a;
}

// Example Job 2
string crazyCase(string a)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (i % 2 == 0)
        {
            a[i] = toupper(a[i]);
        }
        else
        {
            a[i] = tolower(a[i]);
        }
    }
    return a;
}

int main(int argc, char **argv)
{
    // Create a new interpreter object
    Interpreter interpreter;

    // Load flowscript file
    interpreter.loadFile("../Data/flowscript_test1.dot");

    // Register all jobs
    interpreter.registerJob("sortString", new Job(sortString, 1));
    interpreter.registerJob("crazyCase", new Job(crazyCase, 1));

    // Pass the input
    interpreter.setInput("jdrbwk4iuyueiojrsgdklfkjdb");

    // Parse flowscript file
    interpreter.parse();

    // If no error code, run flowscript
    if (interpreter.getErrorCode() == 0)
    {
        cout << "Output: " << interpreter.run() << endl;
    }
    // Otherwise, print error details
    else
    {
        cout << "Couldn't compile flowscript: " << endl;
        cout << interpreter.getErrorMessage() << endl;
        cout << "Error line: " << interpreter.getErrorLine() << endl;
    }

    return 0;
}