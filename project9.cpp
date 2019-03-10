#include<iostream>
using std::cout; using std::endl;
#include<algorithm>
using std::lower_bound;
#include<iterator>
using std::ostream_iterator;
#include<sstream>
using std::ostringstream; using std::istringstream;
#include<iomanip>
using std::boolalpha; using std::fixed; using std::setprecision;
#include<vector>
using std::vector; 
#include<string>
using std::string; 
#include<utility>
using std::pair;
#include<fstream>
using std::ifstream;
#include<initializer_list>
using std::initializer_list;
#include "proj09_mapset.h" 

/* yw  section1 updated 4/1/2018
   Project 09
   practice creating a combination data structure, MapSet
*/


vector< pair <string, long> >::iterator MapSet::find_key(string s){
    //Returns an iterator pointing to the first element in the range 
    // which does not compare less than s.
	auto it = lower_bound(v_.begin(), v_.end(), s, 
        []( const pair<string, long>& a,  string x ) 
        {  return a.first < x; }
        );
    return it;
      
}


bool MapSet::add ( pair<string, long> p ){
	//if the string as a key is in the MapSet, do nothing and return false.
	bool b= false;
	// Otherwise
	string s =p.first;
	auto it= find_key( s );
	if (it== v_.end() ){
		v_.push_back( p );
		b=true;
	}
	else{
		if( it->first != s){
		    b= true;
		    //create a pair with the argument values and insert the new pair into the vector,in sorted order,
		    v_.insert(it, p );
		    }
	}
	return b;
}


MapSet::MapSet( initializer_list< pair<string,long> > l ){
	//Take each pair and place in the vector.   
	for( auto element :l ){
		//The initializer_list does not have to be in sorted order but the vector should be after add all the elements.
		add(element);		
	}
}


size_t MapSet::size(){
	// size of the MapSet (number of pairs)
	return v_.size();
}

pair<string,long> MapSet::get(string s){
	// a pair with default values (that is, a pair<string,long> with the value {"",0}).
	pair< string, long> p;
	for( auto ele: v_){
		// returns a pair<string,long> that is a copy of the pair that has the string as a key 
		if ( ele.first == s){
			p= ele;
		}
	}
	return p;
}

bool MapSet::update(string s,long l){
	// If the key is not in MapSet, do nothing and return false.
	bool b= false;
	for( auto i= v_.begin(); i!= v_.end(); i++){
		//if the string as a key is in the MapSet,
		if ( i->first == s){
			// update the key-value pair to the value of the long.
			i->second= l;
			//Return true. 
			b= true;
		}
	}
	return b;
}

bool MapSet::remove (string s){
	// string as the key is not in the MapSet do nothing and return false.
	bool b= false;
	for( auto i= v_.begin(); i!= v_.end(); i++){
		// if the string as a key is in the MapSet, 
		if ( i->first == s){
			//remove the associated pair
			v_.erase(i);
			//and return true.
			b= true;
			break;
		}
	}
	return b;
}

// return E.g., Ann:1234, Bob:3456, Charlie:5678
ostream& operator<<(ostream& out, MapSet& c){
	ostringstream oss;
    for( auto e: c.v_){
		//The formatting should have each pair colon (:) separated
		//and each pair comma + space separated (', ')
		oss<< e.first <<':'<<e.second<< ", ";	
	}
	//erase the last comma and space
	string s= oss.str();
	s= s.substr(0,s.size()-2);
	//Returns the ostream after writing the MapSet to the ostream.
	out<<s;
    return out;
}

//compare the two MapSets lexicographically 
int MapSet::compare(MapSet& a){
	// If the argument MapSet is greater,return -1.
	int result=-1;
	for(size_t i = 0; i< this->size(); ++i){
		//using the string-key of the pairs as comparison values
		if( ( v_[i] ).first > ( a.v_[i] ).first ){
			//If the calling MapSet is greater,return 1.
			result =1;
			//  The first difference that occurs determines the compare result.
			break;
		}
		//If all of the comparable pairs are equal but one MapSet is bigger 
		if ( i== a.size()-1 ){
			if( (v_[i] ).first == ( a.v_[i] ).first){
				//then the longer determines the return value 
				if( a.size() < this->size()){
					result=1;
					break;
				}
				// if same size
			    else if( a.size() == this->size()){
				    result=0;
				    break;
			    }
		    }
		    else if( (v_[i] ).first > ( a.v_[i] ).first){
				result =1;
				break;
			}
			// cannot continue compare
			else{
				break;
			}
	     }
	 }
	return result;
}



MapSet MapSet::mapset_union (MapSet& d){
	// Return a new MapSet that is a union of the two MapSets being called.
	MapSet r= MapSet();
	// if the two MapSets have the same key but different values
	//then the key-value of the calling MapSet is the one that is used.
	for( auto e: v_){
		// There is an order here, using add function will solve the sorting problem
		r.add(e);
	}
	for( auto ele: d.v_){
		r.add(ele);
	}
	return r;
}


MapSet MapSet::mapset_intersection(MapSet& f){
	// Return a new MapSet that is the intersection of the two MapSets being called.
	MapSet m= MapSet();
	//If the two MapSets have the same key but different values
	for( pair<string, long> element: v_ ){
		for( pair<string, long> e: f.v_ ){
			// comparison on whether an element is in the MapSet is based on the key.
			if( element.first == e.first ){
				//the key-value of the calling MapSet is the one that is used.
				m.add(element);
			}
		}
	}
	return m;
}

