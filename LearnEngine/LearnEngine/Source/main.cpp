#include <iostream>

#include <Engine\Program\Program.h>

int main()
{
    Engine::Program::Create();

    Engine::Program::Instance().StartMainLoop();

    Engine::Program::Delete();

    return 0;
}