#include "Functions.h"

int Input() {

    int choice;

    std::cout << "What Would You Like To Do?\n"
        << "Show Data (1)\n"
        << "Customize Subjects (2)\n"
        << "What Would It Be?: ";

    while (true) // error handling loop
    {
        std::cin >> choice;

        // if the number is not a string and rather a number or special char this statement will trigger
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Oops! That wasn't a number. Let's try again, shall we?\n"
                << "Choices are:\n"
                << "1. Show Data\n"
                << "2. Customize Subjects\n"
                << "Please enter 1 or 2: ";

            continue;
        }

        // checks if the number is in range 1-2
        if (choice >= 1 && choice <= 2)
        {
            return choice;
        }
        else
        {
            std::cout << "Oops! That wasn't a number. Let's try again, shall we?\n"
                << "Choices are:\n"
                << "1. Show Data\n"
                << "2. Customize Subjects\n"
                << "Please enter 1 or 2: ";
            continue;
        }
    }

}

void ShowData() {

    // loop through the file and print all the values
    for (int i = 0; i < Subjects.size(); i++) {

        float per = (static_cast<float>(total_attendance.at(i)) / classes_held.at(i)) * 100;

        std::cout << "Subject: " << Subjects.at(i) << "\n"
            << "Classes Held: " << classes_held.at(i) << "\n"
            << "Your Attendance: " << total_attendance.at(i) << "\n"
            << "Percentage: " << std::fixed << std::setprecision(2) << per << "%" << "\n\n";
    }
}

void Customize()
{
    int respo;

    while (true)
    {
        respo = getIntInput("What Would You Like To Do?\nCustomize Subjects (1)\nCustomize attendance (2)\nYour Choice: ");
        if (respo == 1 || respo == 2)
            break;
        else
            continue;
    }

    // if the user wantes to customize subject this will trigger
    if (respo == 1) {
        int action;
        std::cout << "Subjects List:\n";

        printsubjects();

        std::cout << "What Would You Like To Do?\n"
            << "Add Subject (1)\n"
            << "Delete Subject (2)\n"
            << "What Would It Be?: ";

        while (true) {
            std::cin >> action;
            if (action == 1 || action == 2)
                break;
            else {
                std::cout << "Invalid Input, Try Again\n"
                    << "Add Subject (1)\n"
                    << "Delete Subject (2)\n"
                    << "What Would It Be?: ";
            }
        }

        // Adding a subject
        if (action == 1) {
            std::string temp;
            std::cout << "Enter The Name Of Subject You Would Like To Add: ";

            while (true) {
                std::cin >> temp;
                if (temp.empty() || temp.find_first_not_of(' ') == std::string::npos) {
                    std::cout << "Empty or invalid input. Try Again: ";
                    continue;
                }
                else if (std::any_of(temp.begin(), temp.end(), ::isdigit)) {
                    std::cout << "Input contains numbers. Try Again: ";
                }
                else {
                    Subjects.push_back(temp);
                    std::cout << "Subject Added Successfully.\n";
                    break;
                }
            }
        }
        // Deleting a subject
        else if (action == 2) {
            int subject_choice;
            std::cout << "Subjects List:\n";

            printsubjects();

            std::cout << "Which Subject Would You Like To Delete? Enter The Serial Number: ";

            while (true) {
                std::cin >> subject_choice;
                if (subject_choice >= 1 && subject_choice <= Subjects.size()) {
                    Subjects.erase(Subjects.begin() + subject_choice - 1);
                    std::cout << "Subject Deleted Successfully.\n";
                    break;
                }
                else {
                    std::cout << "Invalid Input, Try Again: ";
                }
            }
        }
    }

    else if (respo == 2) {
        // if the user chose to change attendances
        std::cout << "Subjects List With Attendance";

        printsubjects();

        int action = 0; // stores users choice

        // error handling loop
        while (true) {

            action = getIntInput("What Would You Like To Do?\nChange Classes Attended? (1)\nChange Total Classes Held (2)\nWhat Would It be?: ");
            if (action == 1 || action == 2) // error handling
                break;
            else {
                std::cout << "What Would You Like To Do?\n"
                    << "Change Classes Attended? (1)\n"
                    << "Change Total Classes Held (2)\n"
                    << "What Would It be?: ";
            }
        }

        if (action == 1) {
            // if they want to change the total attendance.

            int subject_choice = 0;

            printsubjects();
            int new_attendance;

            while (true)
            {
                subject_choice = getIntInput("For Which Subject Would You Like To Edit Your Attendance For?, Enter Serial Number for it");
                if (subject_choice > 0 || subject_choice <= Subjects.size())
                    break;
                else {
                    std::cout << "Invalid Input Try again\n";
                    continue;
                }
            }

            while (true)
            {
                new_attendance = getIntInput("To What Would You Like To Change It To?: ");
                if (subject_choice > 0 || subject_choice <= Subjects.size())
                    break;
                else {
                    std::cout << "Invalid Input Try again\n";
                    continue;
                }
            }
            std::cin >> new_attendance;

            total_attendance.at(subject_choice - 1) = new_attendance;


        }
        else if(action == 2)
        { // if the user wants to change classes held
            int subject_choice;
            printsubjects();
            while (true)
            {
                subject_choice = getIntInput("For which subject would you like to edit the classes held for? enter serial number from the list: ");
                if (subject_choice > 0 || subject_choice <= Subjects.size())
                    break;
                else{
                    std::cout << "Invalid Input Try again\n";
                    continue;
                }
            }

            int new_value;

            std::cout << "TO what would you like to change the value to?";
            std::cin >> new_value;

            classes_held.at(subject_choice - 1) = new_value;
        }

    }

    else { std::cout << "Invalid Output"; }
}

void printsubjects() {

    for (int i = 0; i < Subjects.size(); i++) {
        std::cout << i + 1 << ". " << Subjects.at(i) << " - Attended: "
            << total_attendance.at(i) << " / Held: "
            << classes_held.at(i) << std::endl;
        // printing subjects
    }
}

int getIntInput(const std::string& prompt) {
    int input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear(); // clears the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input, please enter an integer.\n";
        }
        else {
            return input;
        }
    }
}

void SaveData()
{ // saves the data to file
    std::ofstream file("attendance_data.txt"); // if file is not available it makes a new one
    if (file.is_open())
    {
        for (int i = 0; i < Subjects.size(); i++)
        {
            file << total_attendance.at(i) << " " << classes_held.at(i) << "\n";
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
    std::ifstream file("attendance_data.txt"); // called at the start of program if file is not available makes a new one
    if (file.is_open())
    {
        for (int i = 0; i < Subjects.size(); i++)
        {
            file >> total_attendance.at(i) >> classes_held.at(i);
        }
        file.close();
    }
    else
    {
        std::cout << "No previous data found, starting fresh.\n";
    }
}