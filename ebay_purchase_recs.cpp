/******* ASSIGNMENT 3 EBAY_PURCHASE_RECS *******/
// Student: Matthew Acs Z23536012
// Total Possible Points: 20
// Due Date: 6/14/2020
// Course: COP 3014 
// Assignment: Assignment 3
// Professor: Dr. Bullard
// Description: This program gets an input of a cell phone number, item number, 
// quantity, cost, and processing plant number and calculates the net cost,
// tax rate, tax, and total cost. After calculating these fields, the program
// outputs all fields.

// Include directives for libraries
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Declaration of ebay_purchase_order class
class ebay_purchase_order
{
  public:
    string cell_number;
    string item_number;
    int quantity;
    double cost; 
    int processing_plant_number;
    double tax_rate;
    double net_cost;
    double tax;
    double total_cost;
};

// Function prototypes
void input(ebay_purchase_order&, ifstream&);
void process(ebay_purchase_order&);
void output(const ebay_purchase_order&);
void order_tax(ebay_purchase_order&);

int main()
{
    // Declares input file stream file
    ifstream file;
    
    // Declares customer_order of class ebay_purchase_order
    ebay_purchase_order customer_order;
    
    // Opens input file stream
    file.open("ebay_purchase_data.txt");
    
    if (file.fail())
    {
        cout << "Input file did not open correctly << endl";
    }
    else
    {
        // While the input stream is not at the end of the file
        while (!file.eof())
        {
            // Function calls
            input(customer_order, file);
            process(customer_order);
            output(customer_order);
        }
    }
    
    // Close input file stream
    file.close();
    
    return 0;
}


// Name: input
// Precondition: Data file is open and cell_number, item_number, quantity, cost, 
// and processing_plant_number have not been initialized
// Postcondition: cell_number, item_number, quantity, cost, and
// processing_plant_number have been initialized with inputs from file
// Description: The function initializes cell_number, item_number, quantity, cost, 
// and processing_plant_number with inputs from the file
void input(ebay_purchase_order& order, ifstream& in)
{
    // Gets inputs from file
    in >> order.cell_number;
    in >> order.item_number;
    in >> order.quantity;
    in >> order.cost;
    in >> order.processing_plant_number;
}


// Name: process
// Precondition: cell_number, item_number, quantity, cost, and
// processing_plant_number have been initialized with inputs from file
// Postcondition: net_cost, tax_rate, tax, and total_cost have been calculated
// Description: The function calculates net_cost, tax_rate, tax, and total_cost
// using the inputs from the file
void process(ebay_purchase_order& order)
{
    // Calculates net cost
    order.net_cost = order.quantity * order.cost;
    
    // Function call
    order_tax(order);
    
    // Calculates tax
    order.tax = order.net_cost * (order.tax_rate/100.0);
    
    // Calculates total cost
    order.total_cost = order.net_cost + order.tax;
}


// Name: output
// Precondition: net_cost, tax_rate, tax, and total_cost have been calculated
// Postcondition: cell_number, item_number, quantity, cost, processing_plant_number
// net_cost, tax_rate, tax, and total_cost are outputed to two decimal places
// Description: The function outputs all fields to two decimal places with
// left justification and a width of 12
void output(const ebay_purchase_order& order)
{
    // "Magic Formula", sets outputs to two decimal places
    cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);
    
    // Outputs variables
    cout << setw(12) << left << order.cell_number;
    cout << setw(12) << left << order.item_number;
    cout << setw(12) << left << order.quantity;
    cout << setw(12) << left << order.cost;
    cout << setw(12) << left << order.processing_plant_number;
    cout << setw(12) << left << order.tax_rate/100.0;
    cout << setw(12) << left << order.tax;
    cout << setw(12) << left << order.net_cost;
    cout << setw(12) << left << order.total_cost << endl;
}


// Name: order_tax
// Precondition: All inputs are recieved from the file and net_cost is calculated
// Postcondition: The tax_rate is calculated
// Description: The function uses the processing_plant_number to calculate the tax_rate
void order_tax(ebay_purchase_order& order)
{
    // Calculates tax rate based on processing plant number
    if ((order.processing_plant_number>=0) && (order.processing_plant_number<=100))
    {
        order.tax_rate = 6;
    }
    else if ((order.processing_plant_number>=101) && (order.processing_plant_number<=200))
    {
        order.tax_rate = 7;
    }
    else if ((order.processing_plant_number>=201) && (order.processing_plant_number<=250))
    {
        order.tax_rate = 8;
    }
    else if ((order.processing_plant_number>=251) && (order.processing_plant_number<=400))
    {
        order.tax_rate = 9;
    }
    else if (order.processing_plant_number>400)
    {
        order.tax_rate = 12;
    }
}