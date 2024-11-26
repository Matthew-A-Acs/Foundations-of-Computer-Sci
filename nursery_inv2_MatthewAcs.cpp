/******* ASSIGNMENT 2 NURSERY_INV2 *******/
// Student: Matthew Acs Z23536012
// Total Possible Points: 20
// Due Date: 6/7/2020
// Course: COP 3014 
// Assignment: Assignment 2
// Professor: Dr. Bullard
// Description: This program calculates the net cost, discount, tax, and total
// cost of a purchase given a purchase order text file

// Include directives for libraries
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Declaration of order_record class
class order_record
{
    public:
        string plant_name;
        string county_name;
        double plant_cost;
        int quantity;
        double purchase_tax;
        double net_cost;
        double discount;
        double total_cost;
};

// Function prototypes
void input(ifstream&, order_record&);
void process(order_record&);
void output(const order_record&);

// Name: input
// Precondition: Data file is open and plant_name, county_name, plant_cost, and 
// quantity have not been initialized
// Postcondition: plant_name, county_name, plant_cost, and quantity have been
// initialized with inputs from the data file
// Description: The function initializes Plant_name, county_name, plant_cost,
// and quantity with inputs from the data file

void input(ifstream& in, order_record& record)
{
    // Accepts inputs from input file stream and stores them in variables
   in >> record.plant_name;
   in >> record.county_name;
   in >> record.plant_cost;
   in >> record.quantity;
}

// Name: process
// Precondition: Data file is open and plant_name, county_name, plant_cost, and 
// quantity have been initialized
// Postcondition: plant_name, county_name, plant_cost, and quantity have been
// used to calculate purchase_tax, net_cost, discount, and total_cost
// Description: The function uses the inputs from the data file to calculate
// the purchase_tax, net_cost, discount, and total_cost
void process(order_record& record)
{
    // Calculates net cost
   record.net_cost = record.quantity * record.plant_cost;
   
   // Calculates purchase tax
   if((record.county_name == "dade") || (record.county_name == "Dade"))
      {
        record.purchase_tax = record.net_cost * 0.065;
      }
      else if ((record.county_name == "broward") || (record.county_name == "Broward"))
      {
        record.purchase_tax = record.net_cost * 0.06; 
      }
      else if ((record.county_name == "palm") || (record.county_name == "Palm"))
      {
        record.purchase_tax = record.net_cost * 0.07;
      }
      
    // Calculates discount
    if(record.quantity==0)
      {
        record.discount = record.net_cost * 0;
      }
      else if ((1 <= record.quantity) && (record.quantity <= 5))
      {
        record.discount = record.net_cost * 0.01;
      }
      else if ((6 <= record.quantity) && (record.quantity <= 11))
      {
        record.discount = record.net_cost * 0.03;
      }
      else if ((12 <= record.quantity) && (record.quantity <= 20))
      {
        record.discount = record.net_cost * 0.05;
      }
      else if ((21 <= record.quantity) && (record.quantity <= 50))
      {
        record.discount = record.net_cost * 0.08;
      }
      else if (record.quantity > 50)
      {
        record.discount = record.net_cost * 0.12;
      }
      
    // Calculates total cost
    record.total_cost = (record.net_cost + record.purchase_tax - record.discount);
}

// Name: output
// Precondition: purchase_tax, net_cost, discount, and total_cost have been
// calculated
// Postcondition: plant_name, county_name, plant_cost, quantity, 
// purchase_tax, net_cost, discount, and total_cost have been formated to
// two decimal places and outputed
// Description: The function uses the variables plant_name, county_name,
// plant_cost, quantity, purchase_tax, net_cost, discount, and total_cost
// to output the results of the processing of the data file
void output(const order_record& record)
{
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout.setf(ios::fixed);
    
    cout << record.plant_name << "\t";
    cout << record.county_name << "\t";
    cout << record.plant_cost << "\t";
    cout << record.quantity << "\t";
    cout << record.net_cost << "\t";
    cout << record.discount << "\t";
    cout << record.purchase_tax << "\t";
    cout << record.total_cost << "\t" << endl;
    
}

int main()
{
    // declares purchase_record of class order_record
    order_record purchase_record;
    
    // declares input file stream in
    ifstream in;
    
    // opens input file stream
    in.open("nursery_stock.txt");
    
    if(in.fail())
    {
        cout << "Input file did not open correctly" << endl;
    }
    else
    {
        // While the file input stream is not at the end of the file
        while (!in.eof())
        {
            // Function calls
            input(in, purchase_record);
            process(purchase_record);
            output(purchase_record);
        }
    }
    
    // Close input file stream
    in.close();
    
    return 0;
}

