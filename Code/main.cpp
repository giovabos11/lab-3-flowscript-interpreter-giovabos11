#include "interpreter.h"

using namespace std;

int main()
{
    Interpreter interpreter;

    interpreter.loadFile("../Data/test1.flowscript");
    interpreter.parse();

    return 0;
}