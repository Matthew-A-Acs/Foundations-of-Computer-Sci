// -----------------------------------------------------------------------------
// ******* ASSIGNMENT 6 NURSERY_INV3 *******
// Student: Matthew Acs Z23536012
// Total Possible Points: 20
// Due Date: 7/7/2020
// Course: COP 3014 
// Assignment: Assignment 6
// Professor: Dr. Bullard
// Description: The program reads the plant name, county name, unit price, 
// and quantity from a data file named nursery_stock.txt and outputs the 
// plant name, county name, unit price, quantity, net cost, tax rate, purchase
// tax, discount, and total cost to a text file named nursery_run_results.txt.
// The program also outputs the average total cost to the screen.
// -----------------------------------------------------------------------------

// Include directives for libraries
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Declaration of a constant integer
const int CAPACITY = 100;

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
void input(order_record STR[ ], int& count);
void process(order_record STR[ ], const int& count);
void output(const order_record STR[ ], const int& count);
double count_inventory(const order_record STR[ ], const int& count);

// -----------------------------------------------------------------------------
// Name: input
// Precondition: order_record array STR and integer count have been declared
// Postcondition: plant_name, county_name, plant_cost, and quantity have been
// input into the array from a data file. Count is also equal to the number of 
// indexes used.
// Description: The function initializes plant_name, county_name, plant_cost,
// and quantity of the array with inputs from the data file and sets count equal to the number
// of indexes used in the array.
// -----------------------------------------------------------------------------

void input(order_record STR[ ], int& count)
{
    // Declaration of an input file stream in
    ifstream in;
    
    // Binds in to nursery_stock.txt
    in.open("nursery_stock.txt");
    
    // If the file failed to open the program will stop and output an error message
    if (in.fail())
    {
    cout << "Input file did not open correctly";
    exit(1);
    }
    
    // While there is still input in the file, the input stream will give inputs
    // to the array
    while( (!in.eof()) && (count < CAPACITY) )
    {
        in >> STR[count].plant_name;
        in >> STR[count].county_name;
        in >> STR[count].plant_cost;
        in >> STR[count].quantity;
        
        // Count is incremented so that the number of indexes used is recorded
        count++;
    }
    
    // Closes the input file stream
    in.close();
}

// -----------------------------------------------------------------------------
// Name: process
// Precondition: Plant_name, county_name, plant_cost, and quantity have been initialized.
// Count is also equal to the number of indexes used.
// Postcondition: plant_name, county_name, plant_cost, and quantity have been
// used to calculate purchase_tax, tax_rate, net_cost, discount, and total_cost
// for every index in the array
// Description: The function uses the inputs from the data file to calculate
// the purchase_tax, tax_rate, net_cost, discount, and total_cost
// -----------------------------------------------------------------------------
void process(order_record STR[ ], const int& count)
{
    // Loops until every used index is calculated
    for(int i=0; i<count; i++)
    {
        
        // Calculates net cost
        STR[i].net_cost = STR[i].quantity * STR[i].plant_cost;
   
        // Calculates tax rate and purchase tax based on county name 
        if((STR[i].county_name == "dade") || (STR[i].county_name == "Dade"))
        {
            STR[i].purchase_tax = STR[i].net_cost * 0.065;
            STR[i].tax_rate = 0.065;
        }
        else if ((STR[i].county_name == "broward") || (STR[i].county_name == "Broward"))
        {
            STR[i].purchase_tax = STR[i].net_cost * 0.06; 
            STR[i].tax_rate = 0.06;
        }
        else if ((STR[i].county_name == "palm") || (STR[i].county_name == "Palm"))
        {
            STR[i].purchase_tax = STR[i].net_cost * 0.07;
            STR[i].tax_rate = 0.07;
        }

        // Calculates discount based on net cost and quantity      
        if(STR[i].quantity==0)
        {
            STR[i].discount = STR[i].net_cost * 0;
        }
        else if ((1 <= STR[i].quantity) && (STR[i].quantity <= 5))
        {
            STR[i].discount = STR[i].net_cost * 0.01;
        }
        else if ((6 <= STR[i].quantity) && (STR[i].quantity <= 11))
        {
            STR[i].discount = STR[i].net_cost * 0.03;
        }
        else if ((12 <= STR[i].quantity) && (STR[i].quantity <= 20))
        {
            STR[i].discount = STR[i].net_cost * 0.05;
        }
        else if ((21 <= STR[i].quantity) && (STR[i].quantity <= 50))
        {
            STR[i].discount = STR[i].net_cost * 0.08;
        }
        else if (STR[i].quantity > 50)
        {
            STR[i].discount = STR[i].net_cost * 0.12;
        }
      
        // Calculates total cost
        STR[i].total_cost = (STR[i].net_cost + STR[i].purchase_tax - STR[i].discount);
    
    }
}

// -----------------------------------------------------------------------------
// Name: output
// Precondition: purchase_tax, tax_rate, net_cost, discount, and total_cost have been
// calculated
// Postcondition: plant_name, county_name, plant_cost, quantity, 
// purchase_tax, tax_rate, net_cost, discount, and total_cost have been formated to
// two decimal places (three for tax rate) and outputed to nursery_run_results.txt
// Description: The function uses the variables plant_name, county_name,
// plant_cost, quantity, purchase_tax, tax_rate, net_cost, discount, and total_cost
// to output the results of the processing of the inputs. The results are outputed
// to a text file called nursery_run_results.txt
// -----------------------------------------------------------------------------
void output(const order_record STR[ ], const int& count)
{
    // Declares an output file stream called out
    ofstream out;
    
    // Binds a file named nursery_run_results.txt to the output file stream
    out.open("nursery_run_results.txt");
    
    // Sets output to two decmial places in floating point notation with a decimal point
    out.setf(ios::showpoint);
    out.precision(2);
    out.setf(ios::fixed);
    
    // Outputs data for all indexes by using a loop
    for(int i=0; i<count; i++)
    {
        // Writes outputs to file with specified width and justification
        out << setw(15) << left << STR[i].plant_name;
        out << setw(10) << left << STR[i].county_name;
        out << setw(7) << right << STR[i].plant_cost;
        out << setw(6) << right << STR[i].quantity;
        out << setw(8) << right << STR[i].net_cost;
    
        // If the tax_rate is 0.065, the output is written to three decimal places
        if (STR[i].tax_rate == 0.065)
            out.precision(3);
    
        // Writes output to file with specified width and justification
        out << setw(6) << right << STR[i].tax_rate;
    
        // Sets output to two decimal places
        out.precision(2);
    
        // Writes outputs to file with specified width and justification
        out << setw(7) << right << STR[i].purchase_tax;
        out << setw(7) << right << STR[i].discount;
        out << setw(9) << right << STR[i].total_cost << endl;
    }
    
    // Closes the output file stream
    out.close();
}

// -----------------------------------------------------------------------------
// Name: count_inventory
// Precondition: plant_name, county_name, plant_cost, quantity, 
// purchase_tax, tax_rate, net_cost, discount, and total_cost have been formated to
// two decimal places (three for tax rate) and outputed to nursery_run_results.txt
// Postcondition: The average total cost is returned
// Description: The function uses the order_record array and int count to
// find the average total cost and then returns this value
// -----------------------------------------------------------------------------
double count_inventory(const order_record STR[ ], const int& count)
{
    // Variable declaration
    double average;
    
    // The loop sums the total cost of each index used in the array 
    for (int i=0; i<count; i++)
    {
        average = STR[i].total_cost+average;
    }
    
    // The sum (which is stored in variable average) is divided by the number of
    // indexes used
    average/=count;
    
    // The average is returned
    return average;
}

int main()
{
    // Declares array STR of type order_record with a size of CAPACITY
    order_record STR[CAPACITY];
    
    // Declares integer count
    int count;
 
    // Function calls
    input(STR, count);
    process(STR, count);
    output(STR, count);
    
    // Sets output to two decmial places in floating point notation with a decimal point
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout.setf(ios::fixed);
    
    // Outputs the average total order cost to the console
    cout << "Average Total Order Cost = " << count_inventory(STR, count) << endl;
    
    return 0;
}

