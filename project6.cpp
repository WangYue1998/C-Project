#include<iostream>
using std::cout; using std::endl; using std::ostream;
#include<string>
using std::string; 
#include<vector>
using std::vector;
#include<sstream>
using std::ostringstream;
#include<cmath>
using std::pow;

#include "proj06_functions.h"

/* yw  section1 updated 02/25/2018
   Project 06
   Fibonacci n-step sequences  and Fibonacci n-step sequences 
*/


string vec_2_str(const vector<long>& v){
  ostringstream oss;
  for(auto iter=v.cbegin(); iter!=v.cend(); ++iter){
	// each element in the string is separated by a ","
    oss << *iter << ",";
  }
  string result = oss.str();
  //returns a string that represents the values in the vector
  //  each element in the string is separated by a ","
  return result.substr(0, result.size() - 1);
}


// generates a vector containing the nstep sequence
vector<long> gen_nstep_vector (long limit, long nstep){
	vector<long> v;
	// first seed number always be 1
	v.push_back(1);
	// generalize to Fibonacci n-step numbers where i represents the 
	// number of seeds needed, the value is 2^i
	for( int i=0; i< nstep-1; i++){
		v.push_back(pow(2, i));
	}
	//the last element of that vector should be the biggest long less 
	//  than or equal to the limit parameter
	for( int i=0; *(v.end() - 1) <= limit; ++i){
	    long new_last=0;
	    // the number of previous values that are added to create the 
	    //  next number in the sequence
	    for(auto iter=v.begin()+i; iter!=v.end(); ++iter){
			new_last+=*iter ;	
		}
		v.push_back(new_last);
    }
    v.pop_back();
    return v;
}


string num_to_nstep_coding(long num, long nstep){
	// uses gen_nstep_vector
	vector<long> v = gen_nstep_vector(num, nstep);
    // index 0 of the generated vector is not used 
    // (it is redundant, as index 1 already represents the value of 1)
	v.erase(v.begin());
	// copy the value of v to the binary_v
    vector<long> binary_v = v;
    long limit= num;
    // greedy algorithm
    for(auto iter= binary_v.rbegin(); iter!=binary_v.rend()-1; ++iter){
		// find the biggest number less than or equal limit number
		if (*iter< limit){
			// subtract the value found from limit number, update limit number
			limit=limit-*iter;
			// change the value be 1
			*iter=1;
		}
		else if(*iter>limit){
			// the number greater than limit number, change the value be 0
			*iter=0;
		}
		else if(*iter==limit){
			// if the number equal limit number, chnage the value be 1
			*iter=1;
			// the value before number update to 0
			for(auto i= binary_v.rend()-1; i!=iter; --i){
				*i=0;
			}
			// the result of subtract number form limit is zero, done
			break;
		}
	}
	// returns a binary string which represents num as the nstep sequence.
	ostringstream oss;
	for(auto iter=binary_v.cbegin(); iter!=binary_v.cend(); ++iter){
		oss << *iter ;
	}
	string binary_s = oss.str();
	return binary_s;
}

// converts the nstep coded binary string to a long
long nstep_coding_to_num(const string& coding, const vector<long>& nstep_sequence){
	long num=0;
	vector<char> coding_v;
	// adding each charater in string to a vector
	for( char ch:coding){
		coding_v.push_back(ch);
	}
	auto itr1 = coding_v.begin(); 
	auto itr2 = nstep_sequence.begin()+1; 
	// check to vectors value at the same time
	while( itr1 != coding_v.end() && itr2 != nstep_sequence.end()){
		// if binary number equal 1, add the number in nstep_sequence
		if(*itr1=='1'){
			long n= *itr2;
			num+= n;
		}
		itr1++;
		itr2++;
	}
	return num;
}
