#include<iostream>
using std::cout; using std::endl; using std::cin;
#include<cmath>
using std::pow; using std::floor;

/* yw, updated 1/22/18
section1
proj02 juggler sequence
*/

int main(){
    long value1, value2, value3, sequence, count_digits=0, longest_sequence,longest_start_number=0,biggest_sequence=0, biggest_start_number=0;
    // three integer typed values for input
    cin>>value1>>value2>>value3;
    // error message
    if (value2 < value1){
        cout<<"Error"<<endl;
        return 0;
    }
    if( value2<2 || value1<2){
        cout<<"Error"<<endl;
        return 0;
    }

    // the first value is the lower range and the second value is the upper range
    if (value2 >= value1){
        while (value1 <= value2){
            // count the number of sequence, initialize 0
            count_digits=0;
            // set the first number be value1's value
            sequence = value1;
            // if value3==1, print following message
            if (value3==1){
                cout<< value1<<": ";
            }
            //sequence eventually ends in the value 1
            while(sequence!=1){
                // sequence is even number
                if (sequence%2==0){
                    sequence= floor(pow(sequence,0.5));
                    
                }
                // sequence is odd number
                else if (sequence%2 ==1)
                    sequence= floor(pow(sequence,1.5));
                // update the biggest number in sequence
				if (sequence>biggest_sequence){
				    biggest_sequence=sequence;
				    biggest_start_number= value1;
				}
				//the number of number +1
				++count_digits;
				// print sequence
				if (value3==1){
				    if (sequence!=1)
				        cout<<sequence<<',';
				    else
				        cout<<sequence<<endl;
				    
				}
				    
			
            }
            // to get the information of the longest length of sequence
			if (longest_sequence < count_digits){
			    longest_start_number=value1;
			    longest_sequence = count_digits;
			    
			}
            // increasing the value of value1 until it equals value2
            ++value1;
        }

	}
	//print the starting number and the length of the sequence 
	cout<<longest_start_number<<", "<<longest_sequence<<endl;
	//print the starting number and the biggest number in that sequence
	cout<<biggest_start_number<<", "<<biggest_sequence<<endl;

    return 0;
}


