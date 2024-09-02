#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream> // Required for file I/O

int Input();
void Adding_values();
void SaveData();
void LoadData();

std::string Subjects[15] = {"DS Lecture", "DS Tut", "DS Lab", "CPI Lecture", "MATHS-III Lecture", "DE Lecture", "DE Tut", "DE Lab", "DOS Lecture",
                            "IT Lab", "MOP Lecture"};

int total_attendance[15] = {0};
int classes_held[15] = {0};

int main()
{
    LoadData(); // Load previous data from file

    std::cout << "******************** WELCOME ********************\n\n";

    Adding_values();

    SaveData();

    std::cout << "\nMade by an ordinary college student who is always detained :)\n";

    std::cout << "Press Enter To Exit";

    std::cin.ignore();
    
    std::cin.get();

    return 0;
}

// int Input()
// {
//     int choice;
//     std::cout << "What would you like to do?"
//               << "Show stats(1)\n"
//               << "Add values(2)\n"
//               << "Customize values(3)\n"
//               << "What would it be?: ";

//     std::cin >> choice;
//     return choice;
// } // work in progress

void Adding_values()
{
    int respo;
    std::cout << "For which subject would you like to add values for?\n"
              << "DS lecture(1)\n"
              << "DS TUT(2)\n"
              << "DS LAB(3)\n"
              << "CPI lecture(4)\n"
              << "Maths-III lecture(5)\n"
              << "DE LECTURE(6)\n"
              << "DE TUT(7)\n"
              << "DE LAB(8)\n"
              << "DOS lecture(9)\n"
              << "IT lab(10)\n"
              << "MOP lecture(11)\n"
              << "Your answer: \n";
    std::cin >> respo;

    if (respo >= 1 && respo <= 11)
    {
        int new_attended, new_held;

        std::cout << "How many new classes have been held for " << Subjects[respo - 1] << " since last time?: ";
        std::cin >> new_held;

        std::cout << "How many of these new classes did you attend?: ";
        std::cin >> new_attended;

        total_attendance[respo - 1] += new_attended;
        classes_held[respo - 1] += new_held;

        float percentage = (static_cast<float>(total_attendance[respo - 1]) / classes_held[respo - 1]) * 100;

        std::string state;

        if (percentage == 100)
        {
            state = "Congrats you have full attendance";
        }
        else if (percentage <= 99 && percentage >= 80)
        {
            state = "You have a very good attendance percentage";
        }
        else if (percentage <= 79 && percentage >= 75)
        {
            state = "You made it through";
        }
        else if (percentage <= 74 && percentage >= 60)
        {
            state = "You can still make it";
        }
        else if (percentage <= 59 && percentage >= 40)
        {
            state = "A Medical is the only thing that can save you now";
        }
        else if (percentage <= 39)
        {
            state = "What were you doing the whole semester? only god can save you now";
        }

        std::cout << "Your attendance in " << Subjects[respo - 1] << " is: "
                  << std::fixed << std::setprecision(2) << percentage << "% - " << state << std::endl;
    }
    else
    {
        std::cout << "Invalid input";
    }
}

void SaveData()
{
    std::ofstream file("attendance_data.txt");
    if (file.is_open())
    {
        for (int i = 0; i < 11; i++)
        {
            file << total_attendance[i] << " " << classes_held[i] << "\n";
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file for saving data.\n";
    }
}

void LoadData()
{
    std::ifstream file("attendance_data.txt");
    if (file.is_open())
    {
        for (int i = 0; i < 11; i++)
        {
            file >> total_attendance[i] >> classes_held[i];
        }
        file.close();
    }
    else
    {
        std::cout << "No previous data found, starting fresh.\n";
    }
}
