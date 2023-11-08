#include "interpreter.h"

using namespace std;

int main()
{
    Interpreter interpreter;

    interpreter.loadFile("../Data/flowscript_test1.dot");
    interpreter.parse();

    cout << interpreter.getErrorMessage() << endl;

    return 0;
}