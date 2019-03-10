#include<iostream>
using std::cout; using std::endl; using std::fixed;using std::cin;
#include<iomanip>
using std::setprecision;
#include<cmath>
using std::pow;

/* yw, updated 1/16/18
section1
proj01 calculate monthly payment
*/

int main(){
// initialize variables
double carprice, salestaxrate, downpayment,title_fees, yearly_interest_rate, number_of_months, salestax,monthly_interest_rate, monthly_payment, cost_of_car;

// Take as input six double values
cin >> carprice;
cin >> salestaxrate;
cin >> downpayment;
cin >> title_fees;
cin >> yearly_interest_rate;
cin >> number_of_months;

//Floating point numbers will have 2 values after the decimal point and will be rounded
cout<< fixed<< setprecision(2);

// multiply the car price times the sales tax
salestax = carprice*salestaxrate;
// add to the price the sales_tax amount plus the titles and fees and remove any downpayment from the total cost
cost_of_car= salestax + carprice - downpayment + title_fees;
// take the yearly interest rate and turn it into the monthly_rate by dividing by 12.0
monthly_interest_rate= yearly_interest_rate/12.0;
// calculate the monthly payment using the compound interest formula
monthly_payment= cost_of_car*(monthly_interest_rate*pow((1+monthly_interest_rate),number_of_months))/
((pow((1+monthly_interest_rate),number_of_months))-1);

// Print a single result, monthly payment
cout<< monthly_payment<<endl;

return 0;
}
