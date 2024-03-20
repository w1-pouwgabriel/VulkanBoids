#define ENABLE_VALIDATION_LAYER 1

#include "Engine.h"
#include <iostream>

int main()
{
    std::cout << "!!!START YOUR ENGINES!!!\n";
    system("pause");

    Engine* vroem = new Engine();

    delete vroem;

    return 0;
}