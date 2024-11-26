/******* ASSIGNMENT 5 NURSERY_INV3 *******/
// Student: Matthew Acs Z23536012
// Total Possible Points: 10
// Due Date: 6/30/2020
// Course: COP 3014 
// Assignment: Assignment 5
// Professor: Dr. Bullard
// Description: This program calculates the net cost, discount, tax, tax_rate, and total
// cost of a purchase given a purchase order text file. The calcluations are output
// to a text file called sells_results.txt

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
        double tax_rate;
        double discount;
        double total_cost;
};

// Function prototypes
void input(ifstream&, order_record&);
void process(order_record&);
void output(ofstream&, const order_record&);

// Name: input
// Precondition: Data file is open and plant_name, county_name, plant_cost, and 
// quantity have not been initialized
// Postcondition: plant_name, county_name, plant_cost, and quantity have been
// initialized with inputs from the data file
// Description: The function initializes plant_name, county_name, plant_cost,
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
// used to calculate purchase_tax, tax_rate, net_cost, discount, and total_cost
// Description: The function uses the inputs from the data file to calculate
// the purchase_tax, tax_rate, net_cost, discount, and total_cost
void process(order_record& record)
{
    // Calculates net cost
   record.net_cost = record.quantity * record.plant_cost;
   
   // Calculates purchase tax and tax rate
   if((record.county_name == "dade") || (record.county_name == "Dade"))
      {
        record.purchase_tax = record.net_cost * 0.065;
        record.tax_rate = 0.065;
      }
      else if ((record.county_name == "broward") || (record.county_name == "Broward"))
      {
        record.purchase_tax = record.net_cost * 0.06; 
        record.tax_rate = 0.06;
      }
      else if ((record.county_name == "palm") || (record.county_name == "Palm"))
      {
        record.purchase_tax = record.net_cost * 0.07;
        record.tax_rate = 0.07;
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
// Precondition: purchase_tax, tax_rate, net_cost, discount, and total_cost have been
// calculated
// Postcondition: plant_name, county_name, plant_cost, quantity, 
// purchase_tax, tax_rate, net_cost, discount, and total_cost have been formated to
// two decimal places and outputed to sells_results.txt
// Description: The function uses the variables plant_name, county_name,
// plant_cost, quantity, purchase_tax, tax_rate, net_cost, discount, and total_cost
// to output the results of the processing of the data file. The results are outputed
// to a text file called sells_results.txt
void output(ofstream& out, const order_record& record)
{
    // Sets output to two decmial places in floating point notation with a decimal point
    out.setf(ios::showpoint);
    out.precision(2);
    out.setf(ios::fixed);
    
    // Writes outputs to file with specified width and justification
    out << setw(15) << left << record.plant_name;
    out << setw(10) << left << record.county_name;
    out << setw(7) << right << record.plant_cost;
    out << setw(6) << right << record.quantity;
    out << setw(8) << right << record.net_cost;
    
    // If the tax_rate is 0.065, the output is written to three decimal places
    if (record.tax_rate == 0.065)
    out.precision(3);
    
    // Writes output to file with specified width and justification
    out << setw(6) << right << record.tax_rate;
    
    // Sets output to two decimal places
    out.precision(2);
    
    // Writes outputs to file with specified width and justification
    out << setw(7) << right << record.purchase_tax;
    out << setw(7) << right << record.discount;
    out << setw(9) << right << record.total_cost << endl;
    
}

int main()
{
    // declares purchase_record of class order_record
    order_record purchase_record;
    
    // declares input file stream in and output file stream out
    ifstream in;
    ofstream out;
    
    // opens input file stream and output file stream
    in.open("nursery_stock.txt");
    out.open("sells_results.txt");
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
            output(out, purchase_record);
        }
    }
    
    // Close file streams
    in.close();
    out.close();
    
    return 0;
}

