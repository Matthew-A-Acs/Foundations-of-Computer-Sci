#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "order_class.h"

using namespace std;

/*************************************************************************************************************************************************/
//Name: default constructor
//Precondition: A new object is declared of the class type
//Postcondition: Dynamic order_record array contains inputs from the file and count is equal to the number of indexes used and size is equal to array size
//Decription: Reads the data file of purchase order information (plant name, county name, plant cost and quantity) into the dynamic array of order records, 
//STR. If the count become equal to the size the function double_size is called and the memory allocated to STR is doubled.
/***********************************************************************************************************************************************/
order_class::order_class()
{
    count = 0;
    size = 1;
    
    STR = new order_record[size];
    
    // Declares input file stream in and binds it to file nursery_stock.txt
    ifstream in;
    in.open("nursery_stock.txt");
    
    // While not at end of file...
    while(!in.eof())
    {
        // If STR is full then the function calls double_size
        if(is_full())
        {
            double_size();
        }
        
        // Inputs are recieved from the file
        in >> STR[count].pname;
        in >> STR[count].cname;
        in >> STR[count].plant_cost;
        in >> STR[count].quantity;
        
        // count is incremented
        count++;
    }
    
    // The file is closed
    in.close();
    
	cout << "The default constructor has been called\n";

}

/************************************************************************************************************************************/
//Name: copy constructor
//Precondition: An argument is used as a call by value parameter of the class type
//Postcondition: A deep copy of the formal parameter is made.
//Description:  The function performs a deep copy of the formal parameter org. 
/************************************************************************************************************************************/
order_class::order_class(const order_class& org)
{
    // Count and size are copied
    count = org.count;
    size = org.size;
    
    // Assigns STR to point to a dynamic array of the same size as the call by value parameter
    STR = new order_record[size];
    
    // The for loop copies every element of org.STR into STR
    for(int i=0; i<size; i++)
    {
        STR[i] = org.STR[i];
    }
}


/***********************************************************************************************************************************/
//Name: is_Empty 
//Precondition: count is initialized
//Postcondition: returns true if STR is empty
//Decription: returns true if STR is empty
/**********************************************************************************************************************************/
bool order_class::is_Empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: count and size are initialized
//Postcondition: returns true if STR is full
//Decription: returns true if STR is full
/*********************************************************************************************************************************/
bool order_class::is_full()
{
	return count == size;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: STR and count are initialized
//Postcondition: location of key in STR is returned or -1 if it is not there
//Decription: locates key in STR if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int order_class::search(const string key)
{
	// Loop cycles through every index in the array
    for(int i=0; i<count; i++)
    {
        // If the plant name stored in the array is equal to the key, the index is returned
        if(STR[i].pname == key)
            return i;
    }
    
    // If there are no matches, return -1
    return -1;
}

/*********************************************************************************************************************************/
//Name: add
//Precondition: STR, count, and size must be initialized
//Postcondition: an order_record is added to STR and count is increased. If size had to be increased double_size was called.
//Decription: adds a new record to STR; if STR is full, double_size is called to increase the capacity of STR.
/********************************************************************************************************************************/
void order_class::add( )
{
    // If the array is full, double_size is called
    if(is_full())
    {
        double_size();
    }
    
    // Recieves inputs from the user
	cout << "\nEnter plant name: ";
    cin >> STR[count].pname;
    cout << endl;
    cout << "Enter county name: ";
    cin >> STR[count].cname;
    cout << endl;
    cout << "Enter plant cost: ";
    cin >> STR[count].plant_cost;
    cout << endl;
    cout << "Enter plant quantity: ";
    cin >> STR[count].quantity;
    cout << endl;
	  
	// count is incremented
	count ++;
	
	// function call to process
    process();
}

/********************************************************************************************************************************/
//Name: operator-
//Precondition: STR and count are initialized
//Postcondition: removes order_records that contain key. Also returns the order_class object that it modified
//Decription: removes all order records in STR with a plant name field that matches key, if it is there.
/*******************************************************************************************************************************/
order_class& order_class::operator-(const string key)
{
    // If the array is not empty...
    if(!is_Empty())
    {
        // If the array does not contain key, print a message
        if(search(key) == -1)
        {
            cout << key << " can't be removed because it can't be found.\n";
            return *this;
        }
        
        // While the key is in the array
	    while(search(key) != -1)
	    {
	        // i is equal to the index of the record with the key
	        int i = search(key);
	    
	        // Remove the record from the array
	        for(i; i<count; i++)
	        {
	            STR[i] = STR[i+1];
	        }
	    
	        // Decrement count
	        count-=1;
	    }
    }
    
    // Returns current object
    return *this;
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition: order_record, count, and size must be initialized
//Postcondition: doubles the capacity of STR
//Decription: doubles the size (capacity) of STR
/******************************************************************************************************************************/
void order_class::double_size()
{
	// Size is multipied by two
	size *= 2;
	
	// Dynamic array temp is declared and initialized with the size equal to double the size of STR
	order_record *temp = new order_record[size];
	
	// Elements of STR are copied into their respective indexes in temp
	for(int i=0; i<count; i++)
	{
	    temp[i] = STR [i];
	}
	
	// STR is de-allocated
	delete [] STR;
	
	// STR now points to the same dynamic array as temp
	STR = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition: STR is initialized by inputs from a file or the user
//Postcondition: net cost, tax rate, order tax, discount, and total cost is calculated for every order record in STR.
//Decription: calculate the net cost, tax rate, order tax and total cost for every order record in STR.
/*****************************************************************************************************************************/
void order_class::process()
{
    // Loops until every used index is calculated
    for(int i=0; i<count; i++)
    {
        
        // Calculates net cost
        STR[i].net_cost = STR[i].quantity * STR[i].plant_cost;
   
        // Calculates tax rate and purchase tax based on county name 
        if((STR[i].cname == "dade") || (STR[i].cname == "Dade"))
        {
            STR[i].purchase_tax = STR[i].net_cost * 0.065;
            STR[i].tax_rate = 0.065;
        }
        else if ((STR[i].cname == "broward") || (STR[i].cname == "Broward"))
        {
            STR[i].purchase_tax = STR[i].net_cost * 0.06; 
            STR[i].tax_rate = 0.06;
        }
        else if ((STR[i].cname == "palm") || (STR[i].cname == "Palm"))
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


/****************************************************************************************************************************/
//Name: operator<<
//Precondition: Fields in STR are calculated
//Postcondition: prints the fileds of the order records of STR to the screen. Also returns the ostream object
//Decription: prints every field of every order_record in STR formatted to the screen.
/***************************************************************************************************************************/
ostream& operator<<(ostream& out, order_class & org)
{
	// Static integer run is declared and initialized
	static int run = 1;
	
	// Sets output to two decmial places in floating point notation with a decimal point
    out.setf(ios::showpoint);
    out.precision(2);
    out.setf(ios::fixed);
    
    // Outputs data for all indexes by using a loop
    for(int i=0; i<org.count; i++)
    {
        // Writes outputs to file with specified width and justification
        out << setw(15) << left << org.STR[i].pname;
        out << setw(10) << left << org.STR[i].cname;
        out << setw(7) << right << org.STR[i].plant_cost;
        out << setw(6) << right << org.STR[i].quantity;
        out << setw(8) << right << org.STR[i].net_cost;
    
        // If the tax_rate is 0.065, the output is written to three decimal places
        if (org.STR[i].tax_rate == 0.065)
            out.precision(3);
    
        // Writes output to file with specified width and justification
        out << setw(6) << right << org.STR[i].tax_rate;
    
        // Sets output to two decimal places
        out.precision(2);
    
        // Writes outputs to file with specified width and justification
        out << setw(7) << right << org.STR[i].purchase_tax;
        out << setw(7) << right << org.STR[i].discount;
        out << setw(9) << right << org.STR[i].total_cost << endl;
    }
    
    // Static integer is output and incremented
	out << "****************************\n";
	out << "*********end of run " << run << "****" << endl;
	out << "*******************************\n";
	run++;
	
	// Returns ostream object
	return out;
}


/****************************************************************************************************************************/
//Name: destructor
//Precondition: STR, count, and size are initialized
//Postcondition: count and size are set to zero and the space allocated to STR is freed up
//Decription: de-allocates all memory allocated to STR.  This should be the last function to be called before the program
//is exited.
/***************************************************************************************************************************/
order_class::~order_class()
{
    // count and size are set to zero while STR is de-allocated
    count = 0;
    size = 0;
    delete [ ] STR;
    
	cout << "The destructor has been called\n";
}