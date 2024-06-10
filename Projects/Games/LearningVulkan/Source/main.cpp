#include "Engine.h"

// main is the entry point for cross-platform applications
int main(int argc, char* argv[]) 
{
    Engine* vroem = new Engine();

    vroem->Run();
    
    delete vroem;

    system("pause");
    return 0;
}