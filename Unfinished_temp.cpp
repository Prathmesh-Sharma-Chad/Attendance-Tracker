#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>

// This is a temporary file and will be delete later. i made this file as a backup because my ssd got corrupted. these features will be integrated fully in the future. i m open to suggestions. Thank You


// Functions intialization
int Input();
void Customize();
void ShowData();
bool is_digit(std::string& str);
void SaveData();
void LoadData();

// Gloabla Var's
std::string Subjects[15]; // subjects list
int n = sizeof(Subjects) / sizeof(Subjects[0]); // number of subjects
int total_attendance[15] = { 0 }; // classes attended by user
int classes_held[15] = { 0 }; // classes held so far

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
    for (int i = 0; i < n; i++) {

        float per = (static_cast<float>(total_attendance[i]) / classes_held[i]) * 100;

        std::cout << "Subject: " << Subjects[i] << "\n"
            << "Classes Held: " << classes_held[i] << "\n"
            << "Your Attendance: " << total_attendance[i] << "\n"
            << "Percentage: " << std::fixed << std::setprecision(2) << per << "%" << "\n\n";
    }
}

bool is_digit(std::string& str)
{
    // to check if a string contains a digit, custom function.
    for (char ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
        else
        {
            return true;
        }
    }
}

void Customize()
{
    int respo;
    std::cout << "What Would You Like To Do?\n" << "Customize Subjects (1)\n" << "Customize attendance (2)\n" << "Your Choice: ";
    std::cin >> respo;

    // if the user wantes to customize subject this will trigger
    if (respo == 1)
    {
        int action;
        std::cout << "Subjects List:\n";

        // prints the subject list for the user
        for (int i = 0; i < n; i++) {
            std::cout << Subjects[i] << std::endl;
        }

        std::cout << "What Would You Like To Do?\n" << "Add Subject (1)\n" << "Delete Subject (2)\n" << "What Would It Be?: ";
        while (true) // error handling loop
        {
            std::cin >> action;
            if (action == 1 || action == 2)
            {
                break;
            }
            else {
                std::cout << "Invalid Input, Try Again " << "Your Options are: \n" 
                    << "Add Subject (1)\n"
                    << "Delete Subject (2)\n" 
                    << "What Would It Be?: ";
                continue;
            }
        }

        // triggers if the user wants to add subject to the list
        if (action == 1) {
            std::string temp; // temperarly adds the subject to the string

            std::cout << "Enter The Name Of Subject You Would Like To Add Or Press Enter: ";
            
            // error handling loop
            while (true)
            {
                std::cin >> temp;

                if (temp != " ") {
                    std::cout << "Invalid (space)\n" << temp;
                    std::cout << "Try Again: ";

                    continue;
                }
                else if(temp.empty())
                {
                    std::cout << "Empty Input\n" << " Try Again: ";
                    continue;
                }
                else if (is_digit(temp)) {
                    std::cout << "Contains numbers" << temp << "\nTry Again: ";
                }
                else
                {
                    Subjects->append(temp);
                    std::cout << "Subject Added Succefully. You Can Add More Subjects Or Exit By Pressing Enter: ";
                }

            }
        }
        else if(action == 2)
        {
            int subject_action; // for selecting the subject
            int subject_choice; // for action on the subject
            int add_remove_action; // for action after user chooses either they wanna add or remove atendance

            std::cout << "Subjects List:\n";

            // prints the subject list with attendance for the user
            for (int i = 0; i < n; i++) {
                std::cout << i+1 << ". " << Subjects[i] << total_attendance[i] << classes_held[i] << std::endl;
            }

            std::cout << "Which Subjects Attendace Would You Like To Customize? Enter Their Serial Number From The List: ";
            std::cin >> subject_choice;

            std::cout << "Would You Like To Add (1) OR Remove (2) Attendance From The Subject?";
            std::cin >> subject_action;

            std::cout << "Add Your Attendance? (1) OR Add Classes Held (2): ";
            std::cin >> add_remove_action;

            std::cout << "Remove Your Attendance (1) OR Remove Classes Held (1): ";
            std::cin >> add_remove_action;


        }


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
{ // saves the data to file
    std::ofstream file("attendance_data.txt"); // if file is not available it makes a new one
    if (file.is_open())
    {
        for (int i = 0; i < n; i++)
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
    std::ifstream file("attendance_data.txt"); // called at the start of program if file is not available makes a new one
    if (file.is_open())
    {
        for (int i = 0; i < n; i++)
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
