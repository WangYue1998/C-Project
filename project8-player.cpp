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

#include "proj08_player.h" 

/* yw  section1 updated 3/19/2018
   Project 08
   a simple stock market simulation
*/



// An attempt to buy a stock by the player from the Market on the specified date. 
bool Player::buy(Market &m, string stock, long date, long quantity){
	// if false return,no action taken
	bool s=false;
	// get the price of stock
	double price= m.get_price(stock, date);
	// the stock symbol is one of the valid 30 symbols
	//  and the date is valid (within the range of dates stored in Market)
	if(price != -1.0){
		// get the purchase price
		double purchase= quantity * price;
		// has enough cash to make the purchase
		if( cash >= purchase){
			// returns true
			s= true;
			// if true,purchase is made and the player info is updated
			// cash reduced
			cash = cash - purchase;
			//  stocks updated 
			// get interator
			map<string, long>::iterator iter = stocks.find(stock); 
			// if already have that stock
			if (iter != stocks.end() ){
				iter->second= iter->second +quantity;
			}
			else{
				// update stocks
				stocks[stock] = quantity;
			}
		}
	}
	return s;
} 


bool Player::sell (Market &m, string stock, long date, long quantity){
	// if false,no action taken
	bool s=false;
	// get the price of that date
	double price= m.get_price(stock, date);
	if (price != -1.0){
		// has the stock to sell (can't sell what you don't have)
		auto it= stocks.find(stock);
		if(it != stocks.end()){
			// get the number of stocks you have
			long num = it->second;
			// has the stock to sell (can't sell what you don't have)
			if( quantity <= num){
				// returns true
				s= true;
				// sell price
				 double sell= quantity *price;
				 // if true,player info is updated
				 // cash is increased, stocks updated
				 cash= cash+ sell;
				 it->second= it->second - quantity; 
			}
		 }
	}
	return s;
}

// returns a string representation of the player
string Player::to_str(){
	string result;
	ostringstream  c;
	// always prints the cash value(even if 0.00)
	c<< fixed<< setprecision(2)<< cash;
	result= c.str();
	string temp;
	ostringstream oss;
	// numeric output is fixed,setprecision(2)
	oss << fixed << setprecision(2);
	// but only prints stocks(symbol:quant)if there are indeed any key:value pairs in stocks.
	if( !stocks.empty() ){
		// each pair in stock
		for (auto p : stocks){
			// format is: cash,symbol:quantity,symbol:quantity... 
			oss << p.first <<":"<< p.second<<",";
		}
		// get string
		temp = oss.str();
		// delete last comma
		temp = temp.substr(0, temp.size()-1);
		 result +="," + temp ;
    }
    return result;
}


Player Player::combine(Player &b){
	//create a new palyer
	Player p;
	// update new player's cash which is sum of two players
	p.cash=cash+ b.cash;
	// set two players' cash be 0
	cash= 0;
	b.cash=0;
	// copy map from stocks to b.stocks
	for (auto iter = stocks.begin(); iter != stocks.end(); ++iter){
		// get the information of stock and it's quantity of the player
		string stock= iter->first;
		long n= iter-> second;
		// chack if the other player also have that stock
		auto it= b.stocks.find(stock);
		// if have
		if(it != b.stocks.end()){
			// update the quantity of that stock
			it->second= it->second+n;
		}
		else{
			// insert
			b.stocks[stock]=n;
		}
	}
	// copy form b.stocks to p.stocks(new player)
	p.stocks = b.stocks;
	// clear two players' stocks
	stocks.clear();
	b.stocks.clear();
	// returns a new Player that has,as a combination,
	// all the cash and stocks of the two players:the caller and the argument.
	return p;
}
