#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<cmath>
using std::sqrt;
#include<string>
using std::to_string; using std::string;

/* yw, updated 1/31/18
section1
proj03 friendly and solitary numbers
A friendly number is a number that has at least one other integer number
that shares the same abundancy index. 
If the number shares its abundancy index with no other number, then it is solitary.
*/

string abIndex_friend(long ab_numerator, long ab_denominator, long f_pair){
  return to_string(ab_numerator) + "/" + to_string(ab_denominator) +
    ":" + to_string(f_pair);
}

// take an integer and add up all the divisors of a number, 
// including 1 (which is a divisor of every number) and the number itself.
long divisor_sum( long num ){
	long sum=0;
	long i;
	// all divisors will less than the square root of number
	for (i=1;i<=sqrt(num);++i){
		if (num%i==0){
			// if both divisors are same
			if (i== num/i){
				sum+=i;
			}
			// else add both
			else
				sum+=(i+num/i);			
		}
	}
	return sum;
}

long gcd(long number1, long number2){
    //the GCD of x and y is y if x mod y is 0
    //otherwise the GCD is the GCD of y and the remainder of x/y
    if (number2==0){
        return number1;
    }
    else{
        return gcd(number2,number1%number2);
    }
}

// the greatest common divisor of both is 1, then it is a solitary number.
bool is_solitary(long numb){
	long divisorsum;
	long g;
	divisorsum = divisor_sum(numb);
	g = gcd(divisorsum, numb);
	if (g ==1){
		//Check if the numb and its divisor sum have as their gcd 1.
		return true;
	}
	else{
		return false;
	}
}
// Takes two numbers: the first an integer to check 
//and the second the upper limit of the other integers to check against 
//the first number to see if they have the same abundancy index
string friendly_check(long checkint,long upperlimit){
	long abundancy_index, numerator, i_numerator, denominator, i_denominator; 
	long sum, common_divisor, lowest_ratio,i, abundancy,ratio,sumi,divisor;
	//find the abundancy index of the integer to check. 
	sum= divisor_sum(checkint);
	//The abundancy index of a number is a ratio, divisor_sum(n)/n . 
	abundancy_index= sum/checkint;
    //Reduce that ratio to lowest terms using gcd
	common_divisor=gcd(sum,checkint);
	lowest_ratio= abundancy_index/common_divisor;
	// simplify numerator and denominator
	numerator= sum/common_divisor;
	denominator= checkint/common_divisor;	
	// for every number from 2 up to the limit
	for(i=2; i<= upperlimit;++i){
	    // i cannot be checkint
		if (i == checkint){
			continue;
		}
		//find the abundancy index of the range number. 
		sumi= divisor_sum(i);
		abundancy = sumi/i;
		divisor= gcd (sumi, i);
		//Reduce that ratio to its lowest terms using gcd
		ratio= abundancy/divisor;
		i_numerator =sumi/divisor;
		i_denominator= i/divisor;
		// two numbers are a friendly pair
		if (i_numerator== numerator && i_denominator== denominator){
			return abIndex_friend(numerator, denominator, i);
		}
	}
	// do not find a friend in the range from 2 to the limit
	if (i_numerator!= numerator || i_denominator!= denominator){
			return abIndex_friend(numerator, denominator, -1);
		}
}

int main (){
  cout << boolalpha;   // print true or false for bools
  int test;
  cin >> test;
  switch (test) {
  case 1 : {   // divisor sum test
    long input;
    cin >> input;
    cout << divisor_sum(input) << endl;
    break;
  } // of case 1

  case 2:{    // gcd test
    long first, second;
    cin >> first >> second;
    cout << gcd(first, second) << endl;
    break;
  } // of case 2

  case 3: {    // is_solitary test
    long input;
    cin >> input;
    cout << is_solitary(input) << endl;
    break;
  } // of case 3

  case 4: {
    // friend check. Make sure the return value is the
    // result of calling abIndex_friend, a string!
    long input, limit;
    cin >> input >> limit;
    cout << friendly_check(input, limit) << endl;
    break;
  } // of case 4
    
  } // of switch
} // of main
