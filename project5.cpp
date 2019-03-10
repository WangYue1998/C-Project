#include<iostream>
using std::cout; using std::endl; using std::ostream;
#include<string>
using std::string;
#include<vector>
using std::vector;

#include "proj05_functions.h"

/* yw, updated 2/18/18
section1
proj05 
Foursquare Cipher
*/


//returns a new string that is all lowercase and consists of only alphabetic characters in s
string clean_string(string s){
	string lowercase_s;
	// for each character in s
	for (auto chr:s){
	    // if it is a character
		if(isalpha(chr)){
		    // change it to lowercase
			lowercase_s+=tolower(chr);
		}
	}
	return lowercase_s;
}

string create_encoding(string key){
    //minus the letter q
	string  alphabetical_order="abcdefghijklmnoprstuvwxyz";
	string keyword="";
	// only 1 occurrence of each letter is represented
	for (char chr:key){
		auto found=keyword.find(chr);
		// update keyword except letter'q'
		if (found== string::npos && chr!='q'){
			keyword+=chr;
		}
	}
	//Subsequently all the letters that are not represented are place in the block in alphabetical order
	for (char ch:keyword){
		auto pos = alphabetical_order.find(ch);  // string::size_type
		if(pos != string::npos) {
		    // delete the letters have been ocured in keyword
			alphabetical_order.erase(pos,1);
		}
	}
	return keyword+alphabetical_order;
}

//converts the digraph string dg to its encoded digraph
string encode_digraph(string dg, string block1, string block2){
    //takes in the two keyword blocks as encoded by create_encoding above
	string b1 = create_encoding(block1);
	string b3 = create_encoding(block2);
	string b0= create_encoding("abcdefghijklmnoprstuvwxyz");
	string b2= create_encoding("abcdefghijklmnoprstuvwxyz");
	// two original letters
	char first_char_in_b0= dg[0];
	char second_char_in_b2=dg[1];
	
	//row = index / 5 (using integer division)
	//col = index % 5 (modulus)
	//index = row * 5 + col
	
	// first original letter's row and column
	auto first_index= b0.find(first_char_in_b0);
	int first_row= first_index/5;
	int first_col= first_index%5;
	// second original letter's row and column
	auto second_index= b2.find(second_char_in_b2);
	int second_row= second_index/5;
	int second_col= second_index%5;
	// encoded digraph's index
	int ans_index_b1=first_row*5+second_col;
	int ans_index_b3= second_row*5+first_col;
    //convert index to encoded digraph
    string ans="";
	char ans_b1= b1[ans_index_b1];
	char ans_b3= b3[ans_index_b3];
	ans+=ans_b1;
	ans+=ans_b3;
	return ans;
}

//converts the encoded digraph string dg to its original digraph
string decode_digraph(string dg, string block1, string block2){
    //takes in the two keyword blocks as encoded by create_encoding above
	string b1 = create_encoding(block1);
	string b3 = create_encoding(block2);
    // letters in encoded digraph
	char char_in_b1= dg[0];
	char char_in_b3= dg[1];
	// first encoded letter's row and column
	auto first_index= b1.find(char_in_b1);
	int first_row= first_index/5;
	int first_col= first_index%5;
	// second encoded letter's row and column
	auto second_index=b3.find(char_in_b3);
	int second_row= second_index/5;
	int second_col= second_index%5;
	// original digraph's index
	int index_in_b0=first_row*5+second_col;
	int index_in_b2=second_row*5+first_col;
	
	string b0= create_encoding("abcdefghijklmnoprstuvwxyz");
	string b2= create_encoding("abcdefghijklmnoprstuvwxyz");
	//convert index to origina digraph
	string ans="";
	char ans_b0= b0[index_in_b0];
	char ans_b2= b2[index_in_b2];
	ans+=ans_b0;
	ans+=ans_b2;
	return ans;	
}

//takes in the message to encode and the two keywords used for encoding
string encode(string msg, string key1, string key2){
    //takes in the two keyword blocks as encoded by create_encoding above
	string b1 = create_encoding(key1);
	string b3 = create_encoding(key2);
	string lower_msg = clean_string(msg);
	string ans = "";
	//if the original message has an odd number of letters, 'x' is added to the end
	if(lower_msg.size()/2 !=0){
		msg+='x';
	}
	string encode_msg="";
	// continuously choose pairs of digraph string to convert to encoding digraph
	for( auto i=0; i<(lower_msg.size()-1);i+=2){
		string dg="";
		dg= lower_msg.substr(i,2);
		encode_msg+= encode_digraph(dg, key1, key2);
	}
	return encode_msg;
}

//takes in the encoded message to decode and the two keywords used for decoding
string decode(string msg, string key1, string key2){
	string decode_msg="";
	// choose pairs to convert 
	for( auto i=0; i<(msg.size()-1);i+=2){
		string dg="";
		dg= msg.substr(i,2);
		//convert to original message 
		decode_msg+= decode_digraph(dg, key1, key2);
	}
	return decode_msg;
}
