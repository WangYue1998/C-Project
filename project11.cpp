#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<sstream>
using std::ostringstream;
#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<utility>
using std::swap;


/* yw  section1 updated 4/17/2018
   Project 11
   practice creating a combination data structure, MapSet
*/

//
// Node
//
template<typename K, typename V>
struct Node {
  K first;
  V second;
  Node *next = nullptr;
  
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


//
// MapSet
// 
template<typename K, typename V>
class MapSet{
 private:
  Node<K,V>* head_ = nullptr;
  Node<K,V>* tail_ = nullptr;  
  size_t sz_ = 0;
  Node<K,V>* find_key(K);

 public:
  MapSet()=default;
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
    //The formatting should have each pair colon (:) separated
	//and each pair comma + space separated (', ')      
	ostringstream oss;
    Node<K,V> *ptr;
    for(ptr = ms.head_; ptr != nullptr; ptr = ptr->next){
		oss << *ptr << ", ";
	}
    string s = oss.str();
    out << s.substr(0,s.size()-2);
	return out;
  }  
};

template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){
	//initializer_list constructor Create an singly linked list of size initializer_list.size().
	//Copy each Node from the list and place in the array.
	for (auto e : il){
		// The initializer_list does not have to be in sorted order 
		//   but the array should be sorted after add all the elements.
		add(e);
	}
}

template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){
	//copy constructor
	if (ms.head_ == nullptr){
		head_ = nullptr;
		tail_ = nullptr;
    }
    else{
		head_ = new Node<K,V>(ms.head_->first, ms.head_->second);
		tail_ = head_;
		Node<K,V>* ms_ptr = ms.head_->next;
		Node<K,V>* new_node;
		while (ms_ptr != nullptr){
			new_node = new Node<K,V>(ms_ptr->first, ms_ptr->second);
			tail_->next = new_node;
			ms_ptr = ms_ptr->next;
			tail_ = new_node;
		}
    }
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet ms){
	//operator=
	swap(head_, ms.head_);
    swap(tail_, ms.tail_);
    return *this;
}	

// walk down the list, moving head_ but remember it in to_del
// delete each node in turn, the set head_ and tail_
template<typename K, typename V>
MapSet<K,V>::~MapSet(){
	//destructor
	Node<K,V>* to_del = head_;
    while (to_del !=nullptr){
		head_ = head_->next;                                    
		delete to_del;
		to_del = head_;
    }
    head_ = nullptr;
    tail_ = nullptr;
}


template<typename K, typename V>
size_t MapSet<K,V>::size(){
	// size of the MapSet (number of Nodes)	   
	size_t i=0;
	for (auto itr = head_; itr != nullptr; itr = itr->next){
		i++;
	}
	return i;
}


template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key){
	//  returns a pointer to a Node<K,V> lowerbound behavior
    for(auto itr = head_; itr!=nullptr; itr = itr->next){
		if (itr->first >= key) {
		 return itr;
		}
	}
	return nullptr;
}

template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){
	//if the n.first as a key is in the MapSet, do nothing and return false.
	bool b= false;
	K key = n.first;
	auto itr= find_key( key );

	
	// Otherwise, the key isn't in list
	
	// insert in a empty list
	if( itr == nullptr && head_ == nullptr ){
	    Node<K,V> *m = new Node<K,V>(n);
		head_= m;
		tail_= m;
		b = true;
		return b;
	}
	// insert at the end of list
	if( itr == nullptr && tail_!= nullptr ){
	    Node<K,V> *m = new Node<K,V>(n);
		tail_->next= m;
		tail_ = m;
		b =true;
		return b;
	}
	
	if ( itr != nullptr && itr->first != key){
	    Node<K,V> *m = new Node<K,V>(n);
	    // append node n to the front of the list
	    if( itr == head_ ){ 
				    m->next = head_;
				    head_ = m;
		}		 
				 
	    // append node n before the end of the list
		else if( itr== tail_ ){
			swap( itr->first, m->first );
			swap( itr->second, m->second );
			swap( itr->next, m->next );
			itr->next = m;
		    tail_ = m;
		  
			}
	
		// append node n to the somewhere middleof the list
		else{
			swap( itr->first, m->first );
			swap( itr->second, m->second );
			swap( itr->next, m->next );
			itr->next = m;
		   }
		   
	    b =true; 
	    return b;
	}
			
	return b;
}


template<typename K, typename V>
bool MapSet<K,V>::remove(K key){
	// string as the key is not in the MapSet do nothing and return false.
	bool b= false;
	for (auto itr = head_; itr != nullptr; itr = itr->next){
		// if the key as a key is in the MapSet, 
		if ( itr->first == key){		
			//return true.
			b= true;
			//remove the associated node
			
			// at front
			if( itr == head_){
				Node<K,V>* to_del = head_;
				head_ = head_->next; 
				delete to_del;
			}
			// at  back
			else if ( itr== tail_){
                Node<K,V>* new_tail;
				for( auto it = head_; it != tail_; it = it->next){
					new_tail = it;
				}
				Node<K,V>* to_del = tail_;
				tail_= new_tail;
				tail_->next = nullptr;
				delete to_del;
			}
			
			// middle of list                                             
			else{
				auto m = *(itr->next);
				Node<K,V> *a = new Node<K,V>(m);
				swap( itr->first, a->first );
			    swap( itr->second, a->second );
			    swap( itr->next, a->next );
                delete a;
                     
			}
        break;
		}	
	}
	return b;
}


template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){
	// a node with default values (that is, a pair<string,long> with the value {"",0}).
	Node<K,V> p("",0);                     
	for (auto itr = head_; itr != nullptr; itr = itr->next){
		// returns a Node<K,V>that is a copy of the node that has the string as a key 
		if ( itr->first == key){
			p= *(itr);
		}
	}
	return p;
}


template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){
	// If the key is not in MapSet, do nothing and return false.
	bool b= false;
	for (auto itr = head_; itr != nullptr; itr = itr->next){
		//if the string as a key is in the MapSet,
		if ( itr->first == key){
			// update the key-value pair to the value of the long.
			itr->second= value;
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
	int cnt = 0;
	for (auto itr = head_; itr != nullptr; itr = itr->next){
		auto it = ms.head_;
		for (auto i = 0; i < cnt; i++) {
			 it = it->next;
			 }
		//using the string-key of the node as comparison values
		if( (itr->first) >  it->first ){
			//If the calling MapSet is greater,return 1.
			result =1;
			//  The first difference that occurs determines the compare result.
			break;
		}
		if( itr->first < it->first ){                                  
			break;
		}
		//If all of the comparable pairs are equal but one MapSet is bigger 
		if( it== ms.tail_ || itr == tail_){
			if( itr->first == it->first){
				//then the longer determines the return value 
				if( ms.size() < this->size() ){
					result=1;
					break;
				}
				// if same size
			    else if( ms.size() == this->size() ){
				    result=0;
				    break;
			    }
		    }
		    else if( (itr->first) > it->first ){
				result =1;
				break;
			}
			// cannot continue compare
			else{
				break;
			}
	     }
	     cnt++;
	 }
	return result;
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){
	// Return a new MapSet that is a union of the two MapSets being called.
	// if the two MapSets have the same key but different values
	
	//then the key-value of the calling MapSet is the one that is used.
	MapSet r= *this;
	
	
	for (auto it = ms.head_; it != nullptr; it = it->next){
		auto ele = *it;	
		r.add(ele);
	}
	return r;
}


template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){
	// Return a new MapSet that is the intersection of the two MapSets being called.
	
	//If the two MapSets have the same key but different values
	//the key-value of the calling MapSet is the one that is used.
	MapSet a= *this;
	for (auto itr = a.head_; itr != nullptr; itr = itr->next){
		auto key = itr->first;
		auto i= ms.find_key(key) ; 
		// comparison on whether an element is in the MapSet is based on the key.
	    if ( i != nullptr && i->first != key){
			a.remove(key);
		}
		if( i== nullptr){
			a.remove(key);
		}
	}
	
	return a;
}

#endif
  
