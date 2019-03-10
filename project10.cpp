#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::sort; using std::lower_bound;
#include<sstream>
using std::ostringstream;
#include<algorithm>
using std::copy; using std::swap; using std::lower_bound;
#include<iterator>
using std::ostream_iterator; using std::distance;

/* yw  section1 updated 4/8/2018
   Project 10
   practice creating a combination data structure, MapSet
*/


// Node

template<typename K, typename V>
struct Node {
  K first;
  V second;
  Node() = default;
  Node(K,V);
  bool operator<(const Node&) const;
  bool operator==(const Node&) const;
  friend ostream& operator<<(ostream &out, const Node &n){
    // It should print "first:second" to the ostream, 
    //     whatever the values of first and second are.
    out<< n.first<<":"<<n.second;
    return out;
  }
  
};

template<typename K, typename V>
Node<K,V>::Node(K key, V value){
	//2 arg constructor
	first = key;
	second = value;
}

template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const{
	// Compares two Node instances based on the first values
	bool b= false;
	if ( first < n.first){
		b= true;
	}
	return b;
}

template<typename K, typename V>
bool Node<K,V>::operator==(const Node &n) const{
	// two Node instances are equal if their two first values are equal
	bool r= false;
	if ( first ==  n.first){
		r= true;
	}
	return r;

}



// MapSet
 
template<typename K, typename V>
class MapSet{
 private:
  Node<K,V>* ary_;
  size_t last_;
  size_t capacity_;
  Node<K,V>* find_key(K);
  void grow ();
 public:
  MapSet(int sz = 2);
  MapSet(initializer_list< Node<K,V> >);
  MapSet (const MapSet&);
  MapSet operator=(MapSet);
  ~MapSet();
  size_t size();
  bool remove (K);  
  bool add(Node<K,V>);
  Node<K,V> get(K);
  bool update(K,V);  
  int compare(MapSet&);
  MapSet mapset_union (MapSet&);
  MapSet mapset_intersection(MapSet&);

  friend ostream& operator<<(ostream &out, const MapSet &ms){
    ostringstream oss;
    for(size_t i=0; i< ms.last_; ++i){
		//The formatting should have each pair colon (:) separated
		//and each pair comma + space separated (', ')                          
		oss<< ( ms.ary_[i] ).first <<':'<< ( ms.ary_[i] ).second<< ", ";	
	}
	//erase the last comma and space
	string s= oss.str();
	s= s.substr(0,s.size()-2);
	//Returns the ostream after writing the MapSet to the ostream.
	out<<s;
    return out;
  }  
};

template<typename K, typename V>
MapSet<K,V>::MapSet(int capacity){
	//1 arg constructor (default value for size). 
	//The sz parameter also is the is the capacity_ of the MapSet. 
	capacity_ = capacity;
	//last_ is set to 0 (the first open index).
	last_ =0;
	//Creates an array of size sz (the parameter) of type Node using the new operator.
	ary_ = new Node<K,V>[capacity];
}

template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){
	//initializer_list constructor Create an array of size initializer_list.size().
	capacity_ = il.size();
	ary_ = new Node<K,V>[capacity_];
	last_ = 0;
	//Copy each Node from the list and place in the array.
	for (auto e : il){
		// The initializer_list does not have to be in sorted order 
		//   but the array should be sorted after add all the elements.
		add(e);
	}
}



template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key){
	auto it = lower_bound(ary_, ary_+last_, key, 
        []( const Node<K,V>& a,  K key ) 
        {  return a.first < key; }
        );
     //  returns a pointer to a Node<K,V>
    return it;
}

template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){
   
	//if the n.first as a key is in the MapSet, do nothing and return false.
	bool b= false;
	// Otherwise, the key isn't in ary_
	K key = n.first;

	auto it= find_key( key );//push_back
		 if( it == ary_+last_){
			ary_[last_]= n;
		    b= true; 
		    last_+=1;                                                   
		}
		else {
			if ( (*it).first != key ){
				b= true;
				Node<K,V>* new_ary = new Node<K,V>[capacity_+1];
			    // for insert: make a new array that has: 
		        //copy of the old array up to to insert point + new element 
		        //        + the old array after the insert point.
		        
		        copy(ary_, it, new_ary);
		        size_t i= distance( ary_, it);
		        new_ary[i] = n;
		        copy(it, ary_+last_, new_ary+i+1);
		        swap (new_ary, ary_);
		        delete [] new_ary;
		        last_+=1; 

		    }
			
		}
	 if (last_ == capacity_ ){
			grow();
	    }
	return b;
}

template<typename K, typename V>
size_t MapSet<K,V>::size(){
	// size of the MapSet (number of Nodes)	   
	return last_;
}

template<typename K, typename V>
bool MapSet<K,V>::remove(K key){
	// string as the key is not in the MapSet do nothing and return false.
	bool b= false;
	for(size_t i=0;i<last_;i++ ){
		// if the key as a key is in the MapSet, 
		if ( ary_[i].first == key){
			//remove the associated node
			Node<K,V>* new_ary = new Node<K,V>[capacity_];
		    copy(ary_, ary_+i, new_ary);
		    copy(ary_+i+1, ary_+capacity_, new_ary+i);
		    swap (new_ary, ary_);
		    delete [] new_ary;
			//and return true.
			b= true;
			last_-=1;
			break;
		}
	}

	return b;
}

template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){
	// a node with default values (that is, a pair<string,long> with the value {"",0}).
	Node<K,V> p("",0);
	for( size_t i=0;i<last_;i++){
		// returns a Node<K,V>that is a copy of the node that has the string as a key 
		if ( ary_[i].first == key){
			p= ary_[i];
		}
	}
	return p;
}

template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){
	// If the key is not in MapSet, do nothing and return false.
	bool b= false;
	for( size_t i=0;i<last_;i++){
		//if the string as a key is in the MapSet,
		if ( ary_[i].first == key){
			// update the key-value pair to the value of the long.
			ary_[i].second= value;
			//Return true. 
			b= true;
		}
	}
	return b;
}

template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){
	// If the argument MapSet is greater,return -1.
	int result=-1;
	for(size_t i = 0; i< last_; ++i){
		//using the string-key of the node as comparison values
		if( ( ary_[i] ).first > ( ms.ary_[i] ).first ){
			//If the calling MapSet is greater,return 1.
			result =1;
			//  The first difference that occurs determines the compare result.
			break;
		}
		if( ( ary_[i] ).first < ( ms.ary_[i] ).first ){
			break;
		}
		//If all of the comparable pairs are equal but one MapSet is bigger 
		if ( i== last_-1 ){
			if( (ary_[i] ).first == ( ms.ary_[i] ).first){
				//then the longer determines the return value 
				if( ms.size() < this->size()){
					result=1;
					break;
				}
				// if same size
			    else if( ms.last_ ==  last_){
				    result=0;
				    break;
			    }
		    }
		    else if( (ary_[i] ).first > ( ms.ary_[i] ).first){
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

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){
	// Return a new MapSet that is a union of the two MapSets being called.
	MapSet r= MapSet();
	// if the two MapSets have the same key but different values
	//then the key-value of the calling MapSet is the one that is used.
	for( size_t i=0; i< last_; ++i){
		// There is an order here, using add function will solve the sorting problem
		auto e= ary_[i];
		r.add(e);
	}


	for( size_t it=0; it< ms.last_; ++it){
		auto ele = ms.ary_[it];
		r.add(ele);
	}
	return r;
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){
	// Return a new MapSet that is the intersection of the two MapSets being called.
	MapSet m= MapSet();
	//If the two MapSets have the same key but different values
	for( size_t i=0; i< last_; ++i ){
		auto element = ary_[i];
		for( size_t it=0; it< ms.last_; ++it ){
			auto e= ms.ary_[it];
			// comparison on whether an element is in the MapSet is based on the key.
			if( element.first == e.first ){
				//the key-value of the calling MapSet is the one that is used.
				m.add(element);
			    
			}
		}
	}
	
	return m;
}

template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){
	//copy constructor
	capacity_ = ms.capacity_;
    last_ = ms.last_;
    ary_= new Node<K,V>[ms.capacity_];
    copy(ms.ary_, ms.ary_+ms.capacity_, ary_);
}

// copy and swap
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet<K,V> ms){
	//operator=
	// just did the swap here
    swap(this->capacity_, ms.capacity_);
    swap(this->last_, ms.last_);
    swap(this->ary_, ms.ary_);
    return *this;
}

template<typename K, typename V>
MapSet<K,V>::~MapSet(){
	//destructor
	delete [] ary_;
}

template<typename K, typename V>
void MapSet<K,V>::grow(){
	//This method doubles the capacity of the underlying array. 
	Node<K,V>* new_ary;
	if (capacity_ == 0){
		new_ary = new Node<K,V>[1]{};
		capacity_ = 1;
		// ary_ empty, just assign
		ary_ = new_ary;
	}
	else{
		//create a new array of twice the capacity
		// use {} to init to default
		new_ary = new Node<K,V>[capacity_ * 2]{};
		//copies the content of the old array into the new
		copy(ary_, ary_+capacity_, new_ary);
		//update capacity_ and ary_,delete the old array
		capacity_ *= 2;
		// std swap
		swap (new_ary, ary_);
		delete [] new_ary;
	 }

}

#endif
  
