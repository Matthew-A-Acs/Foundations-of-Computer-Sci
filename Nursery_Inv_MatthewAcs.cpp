/******* ASSIGNMENT 1 NURSERY_INV *******/
// Student: Matthew Acs Z23536012
// Total Possible Points: 10
// Due Date: 5/31/2020
// Course: COP 3014 
// Assignment: Assignment 1
// Professor: Dr. Bullard
// Description: This program calculates the net cost, discount, tax, and total
// cost of a purchase given an input of plant name, quantity, and county

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main ()
{
    // Makes outputs display to two decimal places
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    
    // Variable declarations
    string plant_name, county_name, controll;
    int quantity;
    double plant_cost, net_cost, total_cost, discount, tax, discount_rate, tax_rate;
      
      // Outputs text that explains the program to the user
      cout << "----- Plant Cost Calculator -----\n\n";
      cout << "This calculator tells you how much you\n";
      cout << "need to pay based on what plant you are buying,\n";
      cout << "how many plants, the cost of the plant,\n";
      cout << "and what county you live in.\n\n";
      cout << "TYPE YES AND PRESS ENTER TO PROCEED\n\n";
      cin >> controll;
      
      // If user enters anything other than yes, the program stops
      if(!((controll == "YES") || (controll == "Yes") || (controll == "yes")))
      {
          return 0;
      }
      
    do 
    {
      // Prompts user to enter inputs and accepts inputs
      cout << endl << "What plant are you purchasing?\n";
      cin >> plant_name;
      cout << endl << "How much does each plant cost?\n";
      cin >> plant_cost;
      cout << endl << "How many are you buying?\n";
      cin >> quantity;
      cout << endl << "In what county?\n";
      cin >> county_name;
      
      // Calculates net cost
      net_cost = plant_cost * quantity;
      
      // Decides which county is entered and uses the tax rate of that county
      // to determine the tax on the purchase
      if((county_name == "dade") || (county_name == "Dade"))
      {
        tax = net_cost * 0.065;
        tax_rate = 6.5;
      }
      else if ((county_name == "broward") || (county_name == "Broward"))
      {
        tax = net_cost * 0.06; 
        tax_rate = 6;
      }
      else if ((county_name == "palm") || (county_name == "Palm"))
      {
        tax = net_cost * 0.07;
        tax_rate = 7;
      }
      else
      {
          cout << "\nIncorrect County Name Entered!";
          return 0;
      }
      
      // Decides what quantity is entered and calculates discount based
      // on the quantity
      if(quantity==0)
      {
        discount = net_cost * 0;
        discount_rate = 0;
      }
      else if ((1 <= quantity) && (quantity <= 5))
      {
        discount = net_cost * 0.01;
        discount_rate = 1;
      }
      else if ((6 <= quantity) && (quantity <= 11))
      {
        discount = net_cost * 0.03;
        discount_rate = 3;
      }
      else if ((12 <= quantity) && (quantity <= 20))
      {
        discount = net_cost * 0.05;
        discount_rate = 5;
      }
      else if ((21 <= quantity) && (quantity <= 50))
      {
        discount = net_cost * 0.08;
        discount_rate = 8;
      }
      else if (quantity > 50)
      {
        discount = net_cost * 0.12;
        discount_rate = 12;
      }
      else
      {
          cout << "\nIncorrect Quantity Entered!";
          return 0;
      }
      
      // Calculates total cost
      total_cost = (net_cost + tax - discount);
      
      // Outputs results
      cout << endl << "----- RESULTS -----\n\n";
      cout << "Plant Name\t\t" << plant_name << endl;
      cout << "County Name\t\t" << county_name << endl;
      cout << "Plant Cost\t\t" << plant_cost << endl;
      cout << "Plant Quantity\t\t" << quantity << endl;
      cout << "Net Cost\t\t" << net_cost << endl;
      cout << "Tax\t\t\t" << tax << endl;
      cout << "Tax Rate\t\t" << tax_rate << "\%" << endl;
      cout << "Discount\t\t" << discount << endl;
      cout << "Discount Rate\t\t" << discount_rate << "\%" << endl;
      cout << "Total Cost\t\t" << total_cost << endl;
      
      // Prompts an input from the user to indicate if they want to do another
      // calculation
      cout << "\nDo you want to do another calculation? (yes or no)\n";
      cin >> controll;
      
    } while ((controll == "YES") || (controll == "yes") || (controll == "Yes"));
    
    return 0;
}
    
