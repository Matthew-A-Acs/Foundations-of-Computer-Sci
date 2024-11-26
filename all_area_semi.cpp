/******* ASSIGNMENT 4 ALL_AREA_SEMI *******/
// Student: Matthew Acs Z23536012
// Total Possible Points: 10
// Due Date: 6/23/2020
// Course: COP 3014 
// Assignment: Assignment 4
// Professor: Dr. Bullard
// Description: This program gets an input of three side lengths of a triangle
// and determines the area and semiperimeter. It also tells the user if the
// side lengths do not make a triangle, in which the computation is not completed.

// Include directives for libraries
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Declaration of triangle class
class triangle
{
    public:
        double a, b, c, semi, area;
};

// Function prototypes
void title();
void input(triangle&);
bool is_triangle(const triangle&);
void compute(triangle&);
void output(const triangle&);
bool repeat();

int main()
{
    // Declares t of class triangle
    triangle t;
    
    // Function call
    title();
    
    // Do while loop keeps iterating as long as fucntion repeat() returns true
    do
    {
        // Function call
        input(t);
    
        // If the side lengths make a triangle the computations are done
        // and the results are outputed
        if (is_triangle(t))
        {
            // Function calls
            compute(t);
            output(t);
        }
    
    } while (repeat());
    
    return 0;
}

// Name: input
// Precondition: triangle t has been declared and function title has been called
// Postcondition: a, b, and c are initialized with user inputs
// Description: The function initializes a, b, and c with user inputs
void input(triangle& t)
{
    // Prompts user
    cout << "\nWhat is the length of the three sides of your triangle?\n";
    cout << "(Input three values seperated by spaces then press enter)\n\n";
    
    // Accepts three inputs
    cin >> t.a >> t.b >> t.c;
}

// Name: is_triangle
// Precondition: a, b, and c are initialized with user inputs
// Postcondition: Either returns 1 or it tells the user that the inputs
// cannot make a triangle and returns 0
// Description: The function determines if the users inputs can make a triangle
bool is_triangle(const triangle& t)
{
    // If the sum of any two sides is greater than the third side, the function 
    // returns 1. Otherwise, it tells the user that it is not a triangle and it
    // returns 0.
    if ( ((t.a + t.b) > t.c) && ((t.c + t.b) > t.a) && ((t.a + t.c) > t.b) )
    {
        return 1;
    }
    else
    {
        cout << "\nMeasurements do not create a triangle!\n\n";
        return 0;
    }
}

// Name: compute
// Precondition: a, b, and c are initialized with user inputs and is_triangle returned 1
// Postcondition: semi and area are calculated
// Description: The function calculates semi and area based on a, b, and c
void compute(triangle& t)
{
    // Computes the semiperimeter of the triangle
    t.semi = (t.a + t.b + t.c) / 2.0;
    
    // Computes the area of the triangle
    t.area = sqrt(t.semi * (t.semi - t.a) * (t.semi - t.b) * (t.semi - t.c));
}

// Name: output
// Precondition: semi and area are calculated
// Postcondition: a, b, c, semi, and area are outputed to two decimal places
// Description: The function outputs the inputs and results to two decimal places
void output(const triangle& t)
{
    // Magic Formula sets outputs to two decimal places
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout.setf(ios::fixed);
    
    // Outputs results of calculations and inputs
    cout << endl << setw(12) << left << "Side a";
    cout << setw(12) << left << "Side b";
    cout << setw(12) << left << "Side c";
    cout << setw(17) << left << "Semiperimeter";
    cout << setw(12) << left << "Area" << endl;
    
    cout << "-----------------------------------------------------------";
    
    cout << endl << setw(12) << left << t.a;
    cout << setw(12) << left << t.b;
    cout << setw(12) << left << t.c;
    cout << setw(17) << left << t.semi;
    cout << setw(12) << left << t.area << endl << endl;
}

// Name: repeat
// Precondition: a, b, c, semi, and area are outputed to two decimal places
// Postcondition: Either outputs 1 if the user enters y or 0 if the user enters n
// Description: The function determines if the user wants to make another calculation
bool repeat()
{
    // Prompts user
    cout << "Would you like to do another calculation? (y or n)\n";
    
    char input;
    
    // Gets input from user
    cin >> input;
    
    // If the input is y, return 1, else, return 0
    if ((input == 'y') || (input == 'Y'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Name: title
// Precondition: triangle t has been declared
// Postcondition: Title has been output
// Description: The funciton outputs a title for the program
void title()
{
    // Outputs a title for the program
    cout << "TRIANGLE AREA CALCULATOR" << endl;
    cout << "------------------------" << endl;
}
