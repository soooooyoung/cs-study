// Exercise 6 & 7
// Add a new file to your project named "MyVars.h"
// Define a variable named surname of type string within the file.
// Within main function, display the following information
// 1. The number of letters in your surname.
// 2. The first character.
// 3. The last character

#include <iostream>
#include "MyVars.h"

using namespace std;

int main()
{
    cout << "size:" << surname.size();
    cout << "first character: " << surname[0];
    cout << "last character: " << surname[surname.size() - 1];

    return 0;
}