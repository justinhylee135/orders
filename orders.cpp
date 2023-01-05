/*
  File: orders.cpp
  Created by: Justin Lee
  Creation Date: Dec. 2, 2022
  Synopsis: Program reads, stores, and displays customer order. 
  Orders consist of ID, price, quantity, and time of order.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Time
{
   private:
     int hours;
	  int minutes;
	  int seconds;
	  string twoDigits(const int num) const;

   public:
	  void setHours(const int hrs);
	  void setMinutes(const int mins);
	  void setSeconds(const int secs);
	  int getHours() const;
	  int getMinutes() const;
	  int getSeconds() const;
	  string toString() const;
};

class Order
{
   private:
     double price;
    int quantity;
    string id;
    Time time;
  
  public:
    void setPrice(const double cost);
    void setQuantity(const int quant);
    void setID(const string ident);
    void setTime(const Time t);
    double getPrice() const;
    int getQuantity() const;
    string getID() const;
    Time getTime() const;
    void display() const;
};

// FUNCTION PROTOTYPES GO HERE:
void Read_Orders (vector <Order>& orders,  const int& MAX);
string Read_Valid_Id (vector <Order>& orders);
bool Lower_Case_Or_Digit (const char& character);
bool Id_Used (const vector <Order>& orders, const string& id); 
double Read_Price (const double& MAX_PRICE);
int Read_Quantity ();
Time Read_Military_Time ();
void Display_Orders (const vector <Order>& orders);
void Display_Graph (const vector <Order>& orders, const int& MAX);

int main()
{
	// Declare constant
	const int MAX_PRICE = 100; //constant variable for max price

	vector<Order> orders; //vector to hold orders

	// Call the function in TASK 6
	Read_Orders(orders, MAX_PRICE); //fill orders vector
	
	// Write code to call the functions in TASK 13 and TASK 14
	Display_Orders (orders);
	Display_Graph (orders, MAX_PRICE);
   
   return 0;
}
			 
// CLASS MEMBER FUNCTION DEFINITIONS GO HERE:
//set private variable hours to hr
void Time::setHours(const int hrs)
{
	hours = hrs;
}

//set private variable minutes to mins
void Time::setMinutes(const int mins)
{
	minutes = mins;
}

//set private variable seconds to secs
void Time::setSeconds(const int secs)
{
	seconds = secs;
}

//return private var hours
int Time::getHours() const 
{
	return hours;
}

//return private var minutes
int Time::getMinutes() const 
{
	return minutes;
}

//return private var seconds
int Time::getSeconds() const 
{
	return seconds;
}

//Convert digits to string in a two digit format
string Time::twoDigits(const int num) const
{
  string output; //variable to hold output
  if (num >= 10){ //if number has two digits
     output = to_string(num); //return string of number
  }
  else{ //if number has one digit
      output = "0" + to_string(num); //add 0 infront of string number  
  }
  
  return output; //return output
}

//converts time int to string for output
string Time::toString() const
{
  string output, hours, minutes, seconds; //declare variables for output and time
  
  //convert time to string by calling twoDigits()
  hours = twoDigits(getHours());
  minutes = twoDigits(getMinutes());
  seconds = twoDigits(getSeconds());
  
  //set output to combination of time strings
  output = hours + ":" + minutes + ":" + seconds;
  
  return output; //return output
}
 
//set private variable price to cost
void Order::setPrice(const double cost) 
{
  price = cost;
}

//return private variable price
double Order::getPrice() const
{
  return price;
}
  
//set private variable quantity to quant
void Order::setQuantity(const int quant) 
{
  quantity = quant;
}

//return private var quantity
int Order::getQuantity() const
{
  return quantity;
}

//set private variable id to ident
void Order::setID(const string ident)
{
  id = ident;
}

//return private variable id
string Order::getID() const
{
  return id;
}
 
//set private variable time to t
void Order::setTime(const Time t)
{
  time = t;
}

//return private variable time
Time Order::getTime() const
{
  return time;
}

//displays order properties   
void Order::display() const
{
  cout << "Order " << getID() << ", "; //order ID
  cout << getQuantity() << " units, "; //order quantity
  cout << "costs $" << getPrice() << ", "; //order cost
  cout << "taken @ " << getTime().toString() << endl; //order time taken
}

// FUNCTION DEFINITIONS GO HERE:
//Read_Orders fills the pass by ref orders vector with user-inputs
//parameter also includes MAX val
void Read_Orders (vector <Order>& orders,  const int& MAX){
  //Statement
  cout << "Enter today's orders:" << endl;
  
  //declare relevant order variables
  int orderNum(1); //keep track of order num
  string id; //order ID
  double price(0); //order price
  int quantity(0);  //order quant
  Time time; //time holder
  
  while (id.compare("stop") != 0 && id.compare("STOP") != 0 || orderNum == 1){ //while id input is not empty
     cout << "Order #" << orderNum << " -" << endl; //Header
     cout << "Enter 'stop' to end orders" << endl;
     cout << "Enter 1 letter and 1 number for ID" << endl;
     //Fill variables
     id = Read_Valid_Id(orders); //get user-id from user
     if (id.compare("stop") != 0 && id.compare("STOP") != 0){
       orders.resize(orderNum + 1); //resizes order with each new order
       orders.at(orderNum).setID(id); //add id to vector
       price = Read_Price(MAX); //input price
       orders.at(orderNum).setPrice(price); //add price to vector
       quantity = Read_Quantity(); //input quantity
       orders.at(orderNum).setQuantity(quantity); //add quantity to vector
       time = Read_Military_Time();
       orders.at(orderNum).setTime(time); //set time to orders vector
     
       //display to values to user
       cout << "Order " << id << ", ";
       cout << "$" << fixed << setprecision(2) << price << ", ";
       cout << quantity << " units, ";
       cout << "costs $" << price * quantity << ", ";
       cout << "taken @ " << time.toString() << endl;
       cout << endl;    
     }
     orderNum++; //increment order num
  }
}

//Read_Valid_Id returns a valid id string from user-input
//parameters include pass by ref orders vectors
string Read_Valid_Id (vector <Order>& orders){
   string id; //string for id
   bool valid(false);
   cout << "ID: ";
   cin >> id; //input id
   while (!valid){
      if(id.compare("stop") == 0 || id.compare("STOP") == 0){
         return id;
      }
      else if(id[1] == '\0'){
         valid = false;
         cout << "Invalid id, try again." << endl; //reprompt
         cout << "ID: ";
         cin >> id; //input    
      }
      else if (id[2] != '\0'){
         valid = false;
         cout << "Invalid id, try again." << endl; //reprompt
         cout << "ID: ";
         cin >> id; //input 
      }
      else if (Lower_Case_Or_Digit(id[0]) && Lower_Case_Or_Digit(id[1]) && !Id_Used(orders, id)){
         valid = true;    
      }
      else{
         cout << "Invalid id, try again." << endl; //reprompt
         cout << "ID: ";
         cin >> id; //input    
      }
   }
   
   return id;  //return id
}  

//Lower_Case_Or_Digit checks if a character is a lower case letter or a digit
//parameter is a constant pass by reference character
bool Lower_Case_Or_Digit (const char& character){
   //if character is a lower case letter or a digit
   if (islower(character) || isdigit(character)){
     return true; //return true
   }
   else{ //if not
     return false; //return false  
   }
}

//Id_Used checks if an id has been used before
//parameters include orders vector and id
bool Id_Used (const vector <Order>& orders, const string& id){
   for (int i = 0; i < orders.size(); ++i){ //check every orders elemnt
      if (orders.at(i).getID()[0] == id[0] && orders.at(i).getID()[1] == id[1]){ //if ID is eqaul to id 
         return true;  //return true
      }
   }
   
   return false; //return false
}

//Read_Price gets a price value from user input
//Parameters include highest price value as a constant pass by ref double
double Read_Price (const double& MAX_PRICE){
   double price(0); //variable to hold price
   cout << "Price: "; //prompt
   cin >> price; //input 
   while (price <= 0 || price > MAX_PRICE){ //while price is negative or greater than max price
      cout << "Invalid price, try again." << endl; //reprompt
      cout << "Price: ";
      cin >> price; //re-input
   }
   
   return price; //return price 
}

//Gets a quantity value from user
int Read_Quantity (){
   int quant(0); //int to hold quantity value
   cout << "Quantity: "; //prompt
   cin >> quant; //input
   while (quant < 1){ //while quant is negative
      cout << "Invalid quantity, try again." << endl; //repropmt
      cout << "Quantity: ";
      cin >> quant; //input
   }
   
   return quant; //return quantity value
}

//Read time values from user and return Time
Time Read_Military_Time (){
   cout << "Time (hrs, min, sec): "; //prompt
   Time time; //time variable
   int hours(0), minutes(0), seconds(0); //order times
   bool valid(false);
   cin >> hours >> minutes >> seconds; //input time
   while (!valid){
        if ((hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60) && (seconds >= 0 && seconds < 60)){
            valid = true;    
        }
        else{
            cout << "Invalid time, try again." << endl;
            cout << "Time (hrs, min, sec): "; //prompt
            cin >> hours >> minutes >> seconds; //input time
        }
   }
   time.setHours(hours); //set hours to time
   time.setMinutes(minutes); //set minutes to time   >> seconds; //input time
   time.setSeconds(seconds); //set seconds to time   
   
   return time;
}

//Display_Orders outputs all orders and their properties
//Parameters include orders pass by ref
void Display_Orders (const vector <Order>& orders){
   int size = orders.size(); //orders vector size
   if (size > 0){ //if elements exist in orders
      cout << endl; //new line
      cout << "Orders:" << endl; //statement
      for (int i = 1; i < orders.size(); ++i){ //irate through each orders element
         //display to values to user
         cout << "Order " << orders.at(i).getID() << ", "; //orders
         cout << "$" << fixed << setprecision(2) << orders.at(i).getPrice() << ", "; //price
         cout << orders.at(i).getQuantity() << " units, "; //quantity
         cout << "costs $" << orders.at(i).getPrice() * orders.at(i).getQuantity() << ", "; //cost
         cout << "taken @ " << orders.at(i).getTime().toString() << endl; //time taken
      }
      cout << endl; //newline
   }
}

//Display_Graph displays a bar graph with prices 
//Parameters hold constant pass by ref orders list and MAX price value
void Display_Graph (const vector <Order>& orders, const int& MAX){
   if (orders.size() > 0){ //checks there is an element in orders
      cout << "Price Histogram: " << endl; //statement
      vector <int> ranges; //int vec to hold price ranges
      
      //add ranges to list
      double orderSize = orders.size();
      for (double i = 1.0; i < orderSize; ++i){
         //finds range of price
         bool found (false);
         for (double j = MAX; j <= MAX && j >= 0 && !found; j -= 20){
            double price = orders.at(i).getPrice();
            if (price > j){
               ranges.push_back(j + 20);  
               found = true;
            }
         }
      }
      
      int rangesSize = ranges.size();
      if (rangesSize > 0){
         for (int i = 20; i <= MAX; i += 20){
         cout << right << setw(3) << i << ": ";  
            for (int j = 0; j < rangesSize; ++j){
                if (ranges.at(j) == i){
                cout << "$";  
                }
            }
         
             cout << endl;   
        }
      }
      
   }
}