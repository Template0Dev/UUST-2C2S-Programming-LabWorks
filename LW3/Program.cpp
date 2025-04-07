#include "CLIController.h"
#include <iostream>


int main()
{
    setlocale(LC_ALL, "RU");

    try
    {
        LW3::Controllers::CLIController().beginWork();
    }
    catch (...)
    {
        std::cout << std::endl << std::endl << "В процессе исполнения возникла ошибка. Исполнение прервано." << std::endl;
    }

    system("PAUSE");
    return EXIT_SUCCESS;
}
