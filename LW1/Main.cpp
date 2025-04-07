#include "CLIController.h"
#include <iostream>


int main()
{
    setlocale(LC_ALL, "RU");

    LW1::Controllers::CLIController().beginWork();

    system("PAUSE");
    return EXIT_SUCCESS;
}
