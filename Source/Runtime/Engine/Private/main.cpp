#include "Engine.h"

int main()
{
    Engine* vroem = new Engine();

    vroem->Run();
    
    delete vroem;

    system("pause");
    return 0;
}