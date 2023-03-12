// Basics - Exercise 1
// Within the main function, add the statements necessary to request a person's first name (type string) and age (type int)
// and display the values as confirmation on a single line.
// Use the variables "name" and "age" and delcare them as local variables within the main function.

// Basics - Exercise 2
// Extends exercise 1 by defining a constant to store the number of days in a year
// (assume it is always 365) and use it to calculate how many days old the person is.
// This should be output to the screen.

// Basics - Exercise 3
// Extend exercise 2 by defining a pointer (named pAge) to an integer type
// and assign it the address of the variable age. Output the address contained
// within the pointer to the screen

// Basics - Exercise 4
// Extend exercise 3 by defining a reference to an integer type named rAge
// and assign it the variable age

#include <iostream>

using namespace std;

int main()
{
    string name;
    int age;
    // exercise 2
    int daysInAge;
    // exercise 3
    // pointer : memory address for variable
    int *pAge = &age;
    // exercise 4
    // reference : alias for variable
    int &rAge = age;

    cout << "Please enter your name: ";
    cin >> name;

    cout << "Please enter your age: ";
    cin >> age;

    daysInAge = age * 365;

    cout << "Hello, " << name << " age of " << age << " who lived " << daysInAge << " days.";

    cout << " Age Pointer" << pAge;

    cout << " Age Reference" << rAge;

    // system("pause") = prompt press any key to continue
}