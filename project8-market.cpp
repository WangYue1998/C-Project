#include<iostream>
using std::cout; using std::endl;
#include<algorithm>
using std::copy;
#include<iterator>
using std::ostream_iterator;
#include<sstream>
using std::ostringstream; using std::istringstream;
#include<iomanip>
using std::boolalpha; using std::fixed; using std::setprecision;
#include<cassert>
#include<map>
using std::map;
#include<vector>
using std::vector;
#include<string>
using std::string; using std::stod; using std::stol; using std::to_string;
#include<utility>
using std::pair;
#include<fstream>
using std::ifstream;
#include<set>
using std::set;
#include "proj08_market.h"


/* yw  section1 updated 3/19/2018
   Project 08
   a simple stock market simulation
*/

// constructor of 1 argument
Market::Market(string file_name){
	// format  in the file is date value of stock
	// open file
    ifstream in_file(file_name);
	string line;
	// read the line
	while( getline(in_file, line ) ){
        // get date
		istringstream iss(line);
		long time;
		iss >> time;
		double item;
		vector<double> elems;
		// extract the price by empty space
		while(iss>>item){
		 // add each items in vector
         elems.push_back(item);
        }                           
	   stocks[time]=elems;
   }
}

//returns the price of the stock on the date 
double Market::get_price(string stock, long date) const {
	// returns -1.0 otherwise
	double price= -1.0;
    // if the date is a valid date
	auto iter = stocks.find(date); 
	if( iter != stocks.end() ){
		// price list for 30 stocks
		vector<double> price_list = iter-> second;
		// the stock symbol is a valid stock symbol 
		auto mark = find(symbol_list.begin(), symbol_list.end(), stock);
		if (mark!= symbol_list.end()){
			int indx;
			// get the index of stock in symbol list
			indx = distance(symbol_list.begin(), mark );
			for(auto itr=price_list.begin(); itr != price_list.end(); ++itr){
				int i;
				// check the index of price list
				i= distance(price_list.begin(), itr);
				// get the price of that stock
				if( i== indx){
					price=*itr;
					}
		    }
	    }	
	}
	return price;	
}

// Returns as a pair the high and low values (in that order) for that stock for the provided year
pair<double, double>  Market:: high_low_year(long year, string symbol){
	// if the year or the symbol does not exist, returns the pair {-1.0, -1.0}
	pair< double, double> result= {-1.0,-1.0};
	// initialize 
	long month;
	long day;
	string date;
	string m;
	string d;
	set<double> allprice;
	// get each date of a year 20120831 is interpreted as 08/31/2012
	for( month=1; month<=12; month++){
		if(month<10){
			m ='0'+to_string(month);
		}
		else{
			m= to_string(month);
		}
		for( day=1; day<=31; day++){
			if(day<10){
				d ='0'+to_string(day);
			}
			else{
				d= to_string(day);
		    }
		    // get date as a string
		    date=to_string(year)+m+d;
		    // get the price of that stock
		    double price= Market::get_price(symbol, stol(date));
		    // if valid
		    if (price!= -1.0){
				// allprice as an ordered set
				allprice.insert(price);
			}
		}	
	}
	if(!allprice.empty() ){
		// lowest price
		auto iter=allprice.begin();
		// last element as highest price
		auto i=allprice.rbegin();
		double low= *iter;
		double high=*i;
		// change the pair returned
		result.first= high;
		result.second= low;
    }
	return result;
}

