/*
This is the header file for the templated Counter class. 
It also includes all method implementations of the Counter class.
This counter has a map that keeps track of count
as it's private instance variable and through it's methods, can tell the user
things about the map such as the total count, most common element, etc. (Run make all in the terminal
to run main.cpp)  
*/

//header guard
#ifndef COUNTER
#define COUNTER

#include <vector>
#include <map>
#include <iostream>
#include <set>
#include <algorithm>
#include <climits>

/*
templated counter class
*/
template <typename T> 
class Counter{
    public:
        Counter();
        Counter(std::vector<T> vals); 

        int Count();
        int Count(T key);
        int Count(T min, T max);

        void Remove(T key);
        void Increment(T key);
        void Increment(T key, int n);
        void Decrement(T key);
        void Decrement(T key, int n);

        std::set<T> Keys();
        std::vector<int> Values();
        static bool sortByValue(const std::pair<T, int> &a, const std::pair<T, int> &b);
        static bool sortByHighestValue(const std::pair<T, int> &a, const std::pair<T, int> &b); 
        
        T MostCommon();
        std::vector<T> MostCommon(int n);
        T LeastCommon();
        std::vector<T> LeastCommon(int n);

        std::map<T, double> Normalized();
        std::map<T, int> getMap();

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const Counter<U> &n);
        

    private:
        std::map<T, int> dictionary;

};


#endif

// -------------------------------------- IMPLEMENTATIONS OF METHODS -----------------------------------------

/*
Default constructor for Counter, initializes map with no elements
*/
template <typename T>
Counter<T>::Counter(){
    this->dictionary = {};
}

/*
Overloaded constructor for counter, intializes all elements to count = 0
*/
template <typename T>
Counter<T>::Counter(std::vector<T> vals){
    for(int i=0; i< (int)vals.size(); i++){
        this->dictionary[vals[i]] = 0;
    }
}

/*
Returns the sum of all of the counts across the objects
*/
template <typename T>
int Counter<T>::Count(){
    int sum = 0;

    typename std::map<T, int>::iterator it;
    for(it = this->dictionary.begin(); it != this->dictionary.end(); it++){

        sum += it->second;
    }
    return sum;
}

/*
Overloaded function for count -- gives sum of count of specific objects
*/
template <typename T>
int Counter<T>::Count(T key){
    int sum = 0;

    typename std::map<T, int>::iterator it;
    for(it = this->dictionary.begin(); it != this->dictionary.end(); it++){
        if(it->first == key){
            sum += it->second;
        } 
    }
    return sum;
}

/*
Overloaded function for count -- gives sum of count of range of objects
*/
template <typename T>
int Counter<T>::Count(T min, T max){
    int sum = 0;

    typename std::map<T, int>::iterator it;
    for(it = this->dictionary.begin(); it != this->dictionary.end(); it++){
        if(it->first >= min && it->first < max){
            sum += it->second;
        } 
    }
    return sum;
}

/*
Removes key value pair from map in Counter 
*/
template <typename T>
void Counter<T>::Remove(T key){
    this->dictionary.erase(this->dictionary.find(key));    
}

/*
Increments count of certain key by 1 
*/
template <typename T>
void Counter<T>::Increment(T key){
    this->dictionary[key]++;    
}


/*
Increments count of certain key by n 
*/
template <typename T>
void Counter<T>::Increment(T key, int n){
    std::cout << key << " , " << this->dictionary[key] << "\n";
    this->dictionary[key] = this->dictionary[key] + n;
}

/*
Decrements count of certain key by 1 
*/
template <typename T>
void Counter<T>::Decrement(T key){
    if(this->dictionary[key] > 0){
        this->dictionary[key]--;
    }
    else{
        std::cout << "Count cannot be below zero" << std::endl;
    }
        
}

/*
Decrements count of certain key by n. If this makes it negative, then it sets this key's count = 0; 
*/
template <typename T>
void Counter<T>::Decrement(T key, int n){
    if(this->dictionary[key] >= n){
        this->dictionary[key] = this->dictionary[key] - n;
    }
    else{
        std::cout << "Count cannot be below zero" << std::endl;
        this->dictionary[key] = 0;    
    }
    
}

/*
returns set of all keys
*/
template <typename T>
std::set<T> Counter<T>::Keys(){
    std::set<T> keys;
    typename std::map<T, int>::iterator it;
    for(it = this->dictionary.begin(); it != this->dictionary.end(); it++){
        keys.insert(it->first);
    }
    return keys;
}

/*
returns vector of all values
*/
template <typename T>
std::vector<int> Counter<T>::Values(){
    std::vector<int> vals;
    typename std::map<T, int>::iterator it;
    for(it = this->dictionary.begin(); it != this->dictionary.end(); it++){
        vals.push_back(it->second);
    }
    return vals;
}

/*
Returns key of most common (object with highest count) in map.
Throws domain error if empty.
Initializes highest_count at -1 because all objects have to have a count of at least zero
Then iterates through to find highest. 
*/
template <typename T>
T Counter<T>::MostCommon(){
    
    if(this->dictionary.empty()){
        throw std::domain_error("Domain Error");    
    }
    
    int highest_count = -1;
    T highest_type;
    typename std::map<T, int>::iterator it;
    for(it = this->dictionary.begin(); it != this->dictionary.end(); it++){
        if(it->second > highest_count){
            highest_type = it->first;
            highest_count = it->second;
            
        } 
    }
    return highest_type; 
}

template <typename T>
bool Counter<T>::sortByHighestValue(const std::pair<T, int> &a, const std::pair<T, int> &b) 
{ 
    return (a.second > b.second); 
} 

/*
Returns vector of keys of most common objects (objects with highest counts) in map.
Throws domain error if there is less than n elements. See inline comments for more details.
*/
template <typename T>
std::vector<T> Counter<T>::MostCommon(int n){
    if((int)this->dictionary.size()<n){
        throw std::domain_error("Domain Error");    
    }
    
    std::vector<T> highest_types;

    std::vector<std::pair<T, int>> vec;

	// copy key-value pairs from the map to the vector
    typename std::map<T, int>::iterator it2;
    for (it2=this->dictionary.begin(); it2!=this->dictionary.end(); it2++) 
    {
        vec.push_back(std::make_pair(it2->first, it2->second));
    }

    std::sort(vec.begin(), vec.end(), sortByHighestValue); 

    for(int i = 0; i<n; i++){
        highest_types.push_back(vec[i].first);
    }

    return highest_types;



    /*
     //init lowest_types to return
    std::vector<int> highest_vals; //init lowest_values associated with those types
    
    std::vector<T> keys; //getting keys in vector format
    typename std::map<T, int>::iterator it;
    for(it = this->dictionary.begin(); it != this->dictionary.end(); it++){
        keys.push_back(it->first);
    }

    std::vector<int> vals = this->Values();
    
    //loading in first n values
    for(int i=0; i<n; i++){
        highest_types.push_back(keys[i]);
        highest_vals.push_back(vals[i]);
    }

    //comparing to rest of values
    for(int other_vals = n; other_vals< (int)vals.size(); other_vals++){
        for(int lv = n-1; lv>0; lv--){
            if(vals[other_vals] > highest_vals[lv]){
                highest_types[lv] = keys[other_vals];
                highest_vals[lv] = vals[other_vals];
                break;
            }
        }
    }

    return highest_types;
    */
}

/*
Returns key of least common (object with lowest count) in map.
Throws domain error if empty.
Initializes highest_count at INT_MAX because all objects have a count lower than this
Then iterates through to find lowest. 
*/

template <typename T>
bool Counter<T>::sortByValue(const std::pair<T, int> &a, const std::pair<T, int> &b) 
{ 
    return (a.second < b.second); 
} 

template <typename T>
T Counter<T>::LeastCommon(){
    
    if(this->dictionary.empty()){
        throw std::domain_error("Domain Error");    
    }
    
    int lowest_count = INT_MAX;
    T lowest_type;
    typename std::map<T, int>::iterator it;
    for(it = this->dictionary.begin(); it != this->dictionary.end(); it++){
        if(it->second < lowest_count){
            lowest_type = it->first;
            lowest_count = it->second;
            
        } 
    }
    return lowest_type; 
}



/*
Returns vector of keys of least common objects (objects with lowest counts) in map.
Throws domain error if there is less than n elements. See inline comments for more details.
*/
template <typename T>
std::vector<T> Counter<T>::LeastCommon(int n){
    if((int)this->dictionary.size()<n){
        throw std::domain_error("Domain Error");    
    }

    std::vector<T> lowest_types; //init lowest_types to return
    std::vector<std::pair<T, int>> vec;

	// copy key-value pairs from the map to the vector
    typename std::map<T, int>::iterator it2;
    for (it2=this->dictionary.begin(); it2!=this->dictionary.end(); it2++) 
    {
        vec.push_back(std::make_pair(it2->first, it2->second));
    }

    std::sort(vec.begin(), vec.end(), sortByValue); 

    for(int i = 0; i<n; i++){
        lowest_types.push_back(vec[i].first);
    }

    return lowest_types;


    /*
    
    std::vector<int> lowest_vals; //init lowest_values associated with those types
    
    std::vector<T> keys; //getting keys in vector format
    typename std::map<T, int>::iterator it;
    for(it = this->dictionary.begin(); it != this->dictionary.end(); it++){
        keys.push_back(it->first);
    }

    std::vector<int> vals = this->Values();
    
    //comparing to rest of values
    int count = 0;
    for(int other_vals = 0; other_vals< (int)vals.size(); other_vals++){
        for(int lv = 0; lv < count; lv++){
            if(vals[other_vals] < lowest_vals[lv]){
                lowest_types[lv] = keys[other_vals];
                lowest_vals[lv] = vals[other_vals];
                break;
            }
        }
        if(count < n){
            lowest_types[count] = keys[other_vals];
            lowest_vals[count] = vals[other_vals];
            count ++;
        }
    }

    return lowest_types;
    */

}

/*
Returns map of normalized counts ie proportional (like a percentage) to total count
For each key, the value will be value/total_count in order to normalize
Sum of all values = 1;
*/
template <typename T>
std::map<T, double> Counter<T>::Normalized(){
    std::map<T, double> norm;

    int total_count = this->Count();
    if(total_count == 0){
        typename std::map<T, int>::iterator it;
        for(it = this->dictionary.begin(); it != this->dictionary.end(); it++){
            norm[it->first] = 0.0;
        }
        return norm;   
    }

    typename std::map<T, int>::iterator it;
    for(it = this->dictionary.begin(); it != this->dictionary.end(); it++){
        norm[it->first] = (double)it->second/(double)total_count;
    }

    return norm;    
}

/*
provides access to map/dictionary
*/
template <typename T>
std::map<T, int> Counter<T>::getMap(){
    return this->dictionary;
}

/*
<< operator overloader for Counter class. Prints out all key and value (count of key) pairs.
*/
template <typename U>
std::ostream& operator<<(std::ostream& os, const Counter<U> &n){
    os << "{";
    typename std::map<U, int>::const_iterator it;
    for(it = n.dictionary.begin(); it != n.dictionary.end(); it++){
        os << it->first << ":" << it->second << ",";
    }
    os << "}\n";
    return os;
}



