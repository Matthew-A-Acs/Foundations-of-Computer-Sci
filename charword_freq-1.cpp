// -----------------------------------------------------------------------------
// ******* ASSIGNMENT 7 charword_freq *******
// Student: Matthew Acs Z23536012
// Total Possible Points: 10
// Due Date: 7/14/2020
// Course: COP 3014 
// Assignment: Assignment 7
// Professor: Dr. Bullard
// Description: The program reads an input of a block of text from a file and 
// outputs how many words the file contains and how many of each letter is in the file
// -----------------------------------------------------------------------------

// Library include directives
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cctype>
#include <iomanip>

using namespace std;

// Function prototypes
void input(vector<string>& data, int& count);
void process(vector<string>& data, const int& count, int alphabet[]);
void output(const vector<string>& data, const int count, const int alphabet[]);

int main()
{
    // Declaration of integer array alphabet and initialization of every element to zero
    int alphabet[26];
    for(int z=0; z<26; z++)
    {
        alphabet[z] = 0;
    }
    
    // Declaration of int count and initialization to zero
    int count = 0;
    
    // Declaration of vector data with base type string
    vector<string> data;
    
    // Function calls
    input(data, count);
    process(data, count, alphabet);
    output(data, count, alphabet);
    
    return 0;
}

// -----------------------------------------------------------------------------
// Name: input
// Precondition: alphabet, count, and data have been declared and alphabet and count
// are initialized
// Postcondition: data recieves inputs from word_data.txt and count is equal to the 
// number of words in the text file
// Description: The function initializes data with inputs from the text file and 
// count is equal to the number of words in the file
// -----------------------------------------------------------------------------
void input(vector<string>& data, int& count)
{
    string temp;
    
    // Declares and opens input file stream in
    ifstream in;
    in.open("word_data.txt");
    
    // If the file stream fails to open, exit the program with an error message
    if(in.fail())
    {
        cout << "Input file did not open correctly! \n";
        exit(1);
    }
    
    // While the file still has input, give the vector input from the file
    while(!in.eof())
    {
        in >> temp;
        data.push_back(temp);
        
        // Increments count for every word that is added to the vector
        count++;
    }
    
    // closes file
    in.close();
}

// -----------------------------------------------------------------------------
// Name: Process
// Precondition: Vector data recieved inputs from the file and count is equal to 
// the number of words in the file
// Postcondition: All characters become lower case and array alphabet contains the 
// number of times each character appears in indexes 0-25 relative to a-z
// Description: The function changes all characters in the vector to lower case
// and counts the number of times each character appears
// -----------------------------------------------------------------------------
void process(vector<string>& data, const int& count, int alphabet[])
{
    int length;
    
    // Loop iterates as many times as there are indexes in the vector
    for(int i=0; i < count; i++)
    {
        // length is equal to the length of the string stored in the index
        length = data[i].length();
        
        // Loop iterates as many times as there are characters in the string
        for(int x=0; x<length; x++)
        {
            // If the element is a character...
            if (isalpha(data[i][x]))
            {
                // It becomes lower case
                data[i][x] = static_cast<char>(tolower(data[i][x]));
                
                // And array alphabet is incremented at the index corresponding
                // to the character
                alphabet[ static_cast<int>(data[i][x]) - 97 ]++;
            }
        }
    }
}

// -----------------------------------------------------------------------------
// Name: output
// Precondition: All character elements of data are lower case and the number
// of times each character appears is stored in alphabet
// Postcondition: The number of words and the number of times each character
// appears is output
// Description: The function outputs the number of times each character appears
// in the file as well as how many words were in the file
// -----------------------------------------------------------------------------
void output(const vector<string>& data, const int count, const int alphabet[])
{
    // Outputs the total number of words in the file
    cout << "Total Words: " << count << endl;
    
    // Loop outputs the character and how many times the character appears
    // in the text file
    for(int i=0; i<26; i++)
    {
        if(alphabet[i]>0)
        {
            cout << setw(3) << right << alphabet[i];
            cout << setw(3) << right << static_cast<char>(i + 97) << endl;
        }
    }
}