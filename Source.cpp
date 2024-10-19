/*
TODO:
        1. Beautify the code
*/
#include "Header.h"
#include "Functions.h"

int main()
{
    LoadData(); // loads data at the start of program

    std::cout << "******************** WELCOME ********************\n\n";

    int choice = Input(); // calls input function to get what the user wants to do

    // takes them to the next step from here
    if (choice == 1)
        ShowData(); // shows data of classes and attendance
    else
        Customize(); // lets the user customize their classes and attendance

    SaveData(); // saves data at the end of each run

    // some signature stuff
    std::cout << "\nMade by an ordinary college student who is always detained :)\n";

    std::cout << "Press Enter To Exit";

    // adds so that it wont exit terminal unless they press enter or cuts out of it
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cin.get();

    return 0;
}