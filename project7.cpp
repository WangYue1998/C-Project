#include<iostream>
using std::cout; using std::endl; using std::ostream;
#include<fstream>
using std::ifstream; 
#include<string>
using std::string; 
#include<iostream>
using std::cout; using std::endl; 
#include<string>
using std::string;
#include<sstream>
using std::istringstream; using std::ostringstream;
#include<algorithm>
using std::set_intersection; using std::set_symmetric_difference;
using std::find; using std::sort;
#include<iterator>
using std::ostream_iterator;
#include<utility>
using std::pair;
#include<map>
using std::map;
#include<set>
using std::set;
#include<stdexcept>
using std::domain_error; using std::invalid_argument;
#include<iterator>
using std::back_inserter; using std::ostream_iterator; 
#include<vector>
using std::vector;

#include "proj07_functions.h"

/* yw  section1 updated 3/11/2018
   Project 07
   manage a list of computer servers, where each server hosts multiple users. 
   write functions that add a user to a server, disconnect a user from a server,
   balance the server load, etc
*/


//  server data is stored as an associative data structure type called 
//   ServerData which is an STL map<string, set<string>>
// This function tries to connect the user un to the server sn.
bool AddConnection(ServerData & sd, ServerName sn, UserName un){
	// keys represent server names, and the values associated with  
	// the names of users on that server.
	
	map<string, set<string>>::iterator iter = sd.find(sn); 
	// If the server exists, it adds un to that server.
	if (iter != sd.end() ){
		pair<set<string>::iterator,bool> result;
		result = iter->second.insert(un);
		if(result.second){
			return true;
		}
		// If the user un is already connected to the server sn, 
		else{
			return false;
		}
	}
	// If the server does not exist, it is created (added to sd) and 
	// the user un is added to that server. 
    else{
		sd[sn].insert(un);
		return true;
	}
}

// This function tries to disconnect the user un from the server sn 
bool DeleteConnection(ServerData & sd, ServerName sn, UserName un){
	bool s= false;
	// leave increment to the body loop
	for( auto iter = sd[sn].begin(); iter != sd[sn].end(); ){
		// If the user un is not connected to the server sn
		if ( (*iter) == un){
			// iter return the next element in sequence
			iter = sd[sn].erase(iter);
		    s= true;
	    }
	    // If the user un is not connected to the server sn
	    else
	    ++iter;
	}
	return s;	
}

ServerData ParseServerData(const std::string &fname){                    
	ServerData sd;
		// fname is the name of text where each line consists of 
		//  three strings, each space separated.
		  ifstream in_file(fname); 
		  if (!in_file.is_open()){
			  throw invalid_argument("cannot open file");
			  }                                     
		  string line, word, un,sn;

		  // from input file to put on the line(string)
		  while(in_file){ 
			  getline(in_file, line); 
			  if(line=="") continue;                             
			  istringstream iss(line);
			  // extract word space separated extraction
			  iss>>un;
			  iss>>word;
			  iss>>sn;
			  // if the 2nd string is join, then add user_name to server_name.
			  if(word=="join"){
				   AddConnection(sd, sn, un);	  
			  }
			  // if the 2nd string is leave, then remove user_name to server_name.
			  else if(word=="leave"){
				  DeleteConnection(sd, sn, un);
			  }
			  // if any of the input lines has a command other than 
			  //leave or join, the function throws a domain_error exception
			  else{
				  throw domain_error("invalid word");                                 
			  }		   
		}

    return sd;
}

// Prints the contents of sd to out (not cout, the passed ostream out). 
// Format is: server_name : user_name user_name ... user_name
void PrintAll(std::ostream &out, const ServerData & sd){
	 ostringstream oss;  
	 string result;
	for (auto i = sd.cbegin(); i != sd.cend(); ++i){	//map< string, set<string> >::iterator i;                                                  
		// serve rname
		oss << i->first << " : ";
		// user_name
		for(const string& element : i->second){
			oss << element << " ";
			}
		// There is a '\n' after each line including the last	
		result += oss.str().substr(0,oss.str().size()-1) + "\n";
		// completely clean oss
		oss.str("");
		oss.clear();
	}
	out<<result;
}

//Returns a set<string> which is the set of all servers in the sd
set<string> AllServers(const ServerData & sd){
	// initialize set
	set<string> allservers;
	for(pair<string,set<string>> element : sd){
		// inset server name
		  allservers.insert(element.first);
	}
	return allservers;
}

// Returns a set<string> which is the set of all users on any server in the sd
set<string> AllUsers(const ServerData & sd){
	// initialize set
	set<string> allusers;
	for(pair<string,set<string>> element : sd){
		for(const string& s : element.second){
			// inser user name
			allusers.insert(s);
		}
	}
	return allusers;
}

// This function returns a set<string> of all the server names in sd 
// that the user un is currently connected to.
set<string> HasConnections(const ServerData &sd, UserName un){
	set<string> u;
	for(pair<string,set<string>> element : sd){
		set<string> userset= element.second;
		// check if un in the user set
		auto iter = userset.find(un);
		// if user in that server's user set
		if (iter != userset.end()){
			// insert server name
			u.insert(element.first);
		}   
  }
  return u;
}

//This function returns a set<string> of all the user names in the server 
// sn that are currently connected in sn. 
set<string> HasUsers(const ServerData &sd, ServerName sn){
	set<string> s;
	auto iter = sd.find(sn);
	if (iter != sd.end() ){// cannot be find return end interator
		// updated s be the user set in that server
		s = iter->second ;
    }
  return s;
}

//This function tries to balance the number of users that are connected to server sn1 and sn2.
void BalanceServers(ServerData &sd, ServerName sn1, ServerName sn2){
	// get the user list  who conncet sn1
	auto iter1 = sd.find(sn1);
	set<string> user1= iter1->second ;
	// get the user list  who conncet sn2
	auto iter2 = sd.find(sn2);
	set<string> user2= iter2->second ;

	vector<string>  newuser, commonuser;                                      

	// the users only connect sn1 or sn2
	set_symmetric_difference(user1.begin(), user1.end(),
			   user2.begin(), user2.end(),
			   back_inserter(newuser));
			   
	// Intersection 
	set_intersection(user1.begin(), user1.end(),
		   user2.begin(), user2.end(),
		   back_inserter(commonuser));
		   
		   
	// get number of users		   
	long length= distance( newuser.begin(), newuser.end() );               
	long half= length/2;
	// sort vector                                                  
	sort(newuser.begin(), newuser.end());

	// These users are sorted alphabetically by their name, 
	//  and the first half are moved to server sn1,  and the other half 
	//    are moved to server sn2. 
	
	vector<string> news1;
	vector<string> news2;
	// total number of user is odd, N/2 +1 users are moved to sn1.
	if (length%2){
		for(int i = 0; i < half+1; i ++)
		{// move half+1 to first server
			news1.push_back(newuser[i]);
		}
        for(int i = half+1; i < length; i ++)
		{// move half to second server
			news2.push_back(newuser[i]);
		}
		
	}
	// total number is even
	else{
		for(int i = 0; i < half; i ++)
		{// move half to first server
			news1.push_back(newuser[i]);
		}
        for(int i = half; i < length; i ++)
		{// move half to second server
			news2.push_back(newuser[i]);
		}
		
	}	
	// If a user is connected to both servers, then they are not moved.
	for(string element : commonuser){
		news1.push_back(element);
		news2.push_back(element);
	}
	// clear the map and update new value
	sd[sn1].clear(); 
	sd[sn2].clear(); 
	
	// update map's value after balance                                                         
	for (auto elemnt:news1){
		sd[sn1].insert(elemnt);	
		}        
	for (auto ele:news2){
		sd[sn2].insert(ele);	
		}                                                   
}


void CleanAndBalance(ServerData & sd){
	// remove duplicate users
	set<string> un= AllUsers(sd);

	set<string> sn;
	vector<string> vec_sn;
	
	// All the user names and server names are sorted alphabetically
	for(pair<string,set<string>> element : sd){
		sn.insert(element.first);
		vec_sn.push_back(element.first);
	}
	// clear key's value in map
    for(auto ele: sn){
		sd[ele].clear();
	}
	
    int number= sn.size();
    int n= un.size();
    
    // The users are distributed to servers in a round-robin fashion 
	// in alphabetical order of server and user names
	
    set<string>::iterator iter = un.begin();
    for( auto i = 0; i != n; i++ ){
		// update user
		string user= *(iter);
		iter++;
		// get index
		int indx= i%number;
		// get server by index
		string key= vec_sn[indx];
		sd[key].insert(user);
	}	
}    	
