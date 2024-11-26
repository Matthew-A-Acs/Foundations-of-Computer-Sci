// -----------------------------------------------------------------------------
// ******* ASSIGNMENT 8 NURSERY_DYNAMIC *******
// Student: Matthew Acs Z23536012
// Total Possible Points: 10
// Due Date: 7/21/2020
// Course: COP 3014 
// Assignment: Assignment 8
// Professor: Dr. Bullard
// Description: The program gives a dynamic array of order records inputs from
// a file and then calculates the net cost, tax rate, purchase tax, discount, and total cost.
// The program also adds and deletes records from the array, adjusting the size of the
// array as neccesary.
// -----------------------------------------------------------------------------

// Include directives
#include <iostream>
#include <string>
#include <fstream>  
#include <iomanip>
using namespace std;

// Declaration of order_record class
class order_record
{
public:
	string pname;
	string cname;
	double plant_cost;
	int quantity;
	double net_cost;
	double tax_rate;
	double purchase_tax;
	double discount;
	double total_cost;
};

// Function prototypes
void initialize(order_record*& STR, int& count, int& size);
bool is_Empty(int count);
bool is_Full(int count, int size);
int search(order_record* STR, int  count, string key);
void add(order_record*& STR, int& count, int& size);
void remove(order_record* STR, int& count, string key);
void double_size(order_record*& STR, int  count, int& size);
void process(order_record* STR, int count);
void print(const order_record* STR, const int  count);
void destory_STR(order_record* STR, int& count, int& size);

/*************************************************************************************************************************************************/
//Name: initialize
//Precondition: dynamic order_record array STR is declared and count is initialized to 0 and size is initialized to 1
//Postcondition: dynamic order_record contains inputs from the file and count is equal to the number of indexes used and size is equal to array size
//Decription: Reads the data file of call information (cell number, item_number, quantity, price, and processing_plant) into the dynamic 
//array of call record, STR. If the count because equal to the size the function double_size is called and the memory allocated to STR is doubled.
/***********************************************************************************************************************************************/
void initialize(order_record*& STR, int& count, int& size)
{
    // Declares input file stream in and binds it to file nursery_stock.txt
    ifstream in;
    in.open("nursery_stock.txt");
    
    // While not at end of file...
    while(!in.eof())
    {
        // If STR is full then the function calls double_size
        if(is_Full(count, size))
        {
            double_size(STR, count, size);
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
}

/**********************************************************************************************************************************/
//Name: is_Empty 
//Precondition: count is initialized
//Postcondition: returns true if STR is empty
//Decription: returns true if STR is empty
/*********************************************************************************************************************************/
bool is_Empty(int count)
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: Is_full 
//Precondition: count and size are initialized
//Postcondition: returns true if STR is full
//Decription: returns true if STR is full
/*********************************************************************************************************************************/
bool is_Full(int count, int size)
{
	return count == size;
}


/**********************************************************************************************************************************/
//Name: search
//Precondition: STR and count are initialized
//Postcondition: location of key in STR is returned or -1 if it is not there
//Decription: locates key in STR if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int search(order_record* STR, int  count, string key)
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
void add(order_record*& STR, int& count, int& size)
{
    // If the array is full, double_size is called
    if(is_Full)
    {
        double_size(STR, count, size);
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
    process(STR,count);
}


/********************************************************************************************************************************/
//Name: Remove
//Precondition: STR and count are initialized
//Postcondition: removes order_records that contain key
//Decription: remove all occurences of key from STR if it is there.
/*******************************************************************************************************************************/
void remove(order_record* STR, int& count, string key)
{
    // If the array is not empty...
    if(!is_Empty(count))
    {
        // While the key is in the array
	    while(search(STR, count, key) != -1)
	    {
	        // i is equal to the index of the record with the key
	        int i = search(STR, count, key);
	    
	        // Remove the record from the array
	        for(i; i<count; i++)
	        {
	            STR[i] = STR[i+1];
	        }
	    
	        // Decrement count
	        count-=1;
	    }
    }
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition: order_record, count, and size must be initialized
//Postcondition: doubles the capacity of STR
//Decription: doubles the size (capacity) of STR
/******************************************************************************************************************************/
void double_size(order_record*& STR, int  count, int& size)
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
void process(order_record* STR, int count)
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
//Name: print
//Precondition: Fields in STR are calculated
//Postcondition: prints the fileds of the order records of STR to the file
//Decription: prints every field of every order_record in STR formatted to the screen.
/***************************************************************************************************************************/
void print(const order_record* STR, const int  count)
{
    // Opens output file stream out and binds it to a file to append the data
	ofstream out;
	out.open("nursery_result20.txt", fstream::app);
	
	// Static integer run is declared and initialized
	static int run = 1;
	
	// Sets output to two decmial places in floating point notation with a decimal point
    out.setf(ios::showpoint);
    out.precision(2);
    out.setf(ios::fixed);
    
    // Outputs data for all indexes by using a loop
    for(int i=0; i<count; i++)
    {
        // Writes outputs to file with specified width and justification
        out << setw(15) << left << STR[i].pname;
        out << setw(10) << left << STR[i].cname;
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
    
    // Static integer is output and incremented
	out << "****************************\n";
	out << "*********end of run " << run << "****" << endl;
	out << "*******************************\n";
	run++;
	out.close();
}



/****************************************************************************************************************************/
//Name: destroy_STR
//Precondition: STR, count, and size are initialized
//Postcondition: count and size are set to zero and the space allocated to STR is freed up
//Decription: de-allocates all memory allocated to STR.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
void destory_STR(order_record* STR, int& count, int& size)
{
    // count and size are set to zero while STR is de-allocated
    count = 0;
    size = 0;
    delete [ ] STR;
}

//Here is your driver to test the program
int main()
{
	int count = 0; //intializating count
	int size = 1;
	order_record* STR = new order_record[1];

	cout << "**********************************************************************\n";
	cout << "Test 1: Testing initialize, double_size, process, is_full and print " << endl;
	initialize(STR, count, size);
	process(STR, count);
	print(STR, count);
	cout << "End of Test 1" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";
	//Test 2:
	//void add(order_record * & STR, int & count, int & size);
	cout << "Test 2: Testing add, double_size, process, is_full, and print " << endl;
	add(STR, count, size);
	print(STR, count);
	cout << "End of Test 2" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";
	//Test 3:
	//void remove(order_record * STR, int & count, string key);
	cout << "Test 3: Testing remove, is_Empty, search and print " << endl;
	cout << "Removing rose\n";
	remove(STR, count, "rose");
	print(STR, count);
	cout << "Removing rose\n";
	remove(STR, count, "owl");
	print(STR, count);
	cout << "End of Test 3" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";
	//Test 4:
	//void add(order_record * & STR, int & count, int & size);
	cout << "Test 4: Testing add, double_size, process, is_full, and print " << endl;
	add(STR, count, size);
	print(STR, count);
	cout << "End of Test 4" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";
	//void destroy_STR(order_record  * STR, int & count, int & size);*/
	cout << "Test 5: destroy_STR and print " << endl;
    destory_STR(STR, count, size);
	cout << "size = " << size << endl;
	cout << "count = " << count << endl;
	cout << "End of Test 5" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";
	return 0;
}