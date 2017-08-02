#include "..\Include\Program\Program.h"

#include <iostream>

int main()
{
    Program::Create();

    Program::Instance().StartMainLoop();

    Program::Delete();

    return 0;
}