#include <iostream>

#include <Engine\Program\Program.h>

int main()
{
    Program::Create();

    Program::Instance().StartMainLoop();

    Program::Delete();

    return 0;
}