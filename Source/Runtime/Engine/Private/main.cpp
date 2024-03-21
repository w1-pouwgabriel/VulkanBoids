#include "Engine.h"
#include <iostream>

int main()
{
    std::cout << "!!!START YOUR ENGINES!!!\n";
    system("pause");

    Engine* vroem = new Engine();

    system("pause");
    delete vroem;

    return 0;
}