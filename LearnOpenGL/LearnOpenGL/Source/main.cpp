#include "..\Include\Program.h"

#include <iostream>

int main()
{
	Program::CreateDefault();

    Program::Instance().StartMainLoop();

	return 0;
}