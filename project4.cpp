#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string; using std::to_string;
#include<cmath>

const string the_chars = "0123456789abcdef";

/* yw, updated 2/4/18
section1
proj04 
look for numbers in various bases that are both prime and palindromes.
*/

//returns a new string which reverses the order of the argument string.
string reverse_string(string str){
	string rev = "";
    for (int i = str.size()-1 ; i >= 0 ; --i){
    rev += str[i];
  }
  return rev;
}
//returns true or false, is the string a palindrome
bool is_palindrome(string n){
	string rnum = reverse_string(n);
	return (n == rnum);
}

//Converts the provided long into a string, where the string represents
// the long converted to the provided base.
string long_to_base(long num, long base){
	long remainder;
	string chara = "";
	string result="";
	while (num>0){
		remainder=num % base;//find the remainder of dividing num by the base 
		num=num/base; // after divide num by the base , update num
		chara= the_chars[remainder];//he index of the symbol in the_chars is its integer equivalent.
		result+=chara;//add the character that remainder represents to the result		
	}
	return reverse_string(result);//reverse result
	
}
//Return is true/false, is the provided argument prime
bool is_prime(long n){
	bool isprime=true;
	// a prime number is a number that is only divisible by itself and 1. 
	for (long i=2;i<= (n/2);++i){
		if (n%i==0){
			isprime=false;
			break;
		}
	}
	return isprime;
}
//determine if the long argument is both prime and a palindrome in 
// one of three bases: binary, decimal or hexadecimal
string is_pal_prime(long n){
	string binary="binary-pal-prime";// base 2
	string decimal="decimal-pal-prime";// base 10
	string hex="hex-pal-prime";//base 16
	string no="not-pal-prime";
	// if is a prime number
	if (is_prime(n)){
		// convert number to string
		string binary_string= long_to_base(n,2);
		string decimal_string= long_to_base(n,10);
		string hex_string= long_to_base(n,16);
		// if binary-pal-prime
		if (is_palindrome(binary_string)){
			return binary;
		}
		//if decimal-pal-prime
		else if (is_palindrome(decimal_string)){
			return decimal;
		}
		//if hex-pal-prime
		else if (is_palindrome(hex_string)){
			return hex;
		}
		// if prime but not palindrom
		else{
			return no;
		}			
	}
	// if not prime
	else{
		return no;
	}
} 

int main (){
  long test_num;
  cin >> test_num;
  cout << boolalpha;

  switch(test_num) {

  case 1: {
    string input;
    cin >> input;
    cout << reverse_string(input);
    break;
  }

  case 2:{
    string input;
    cin >> input;
    cout << is_palindrome(input);
    break;
  }

  case 3:{
    long n, base;
    cin >> n >> base;
    cout << long_to_base(n,base);
    break;
  }
  
  case 4:{
    long n;
    cin >> n;
    cout << is_prime(n);
    break;
  }

  case 5:{
    long n;
    cin >> n;
    cout << is_pal_prime(n);
    break;
  }
    
  } // of switch
}  // of main
  

