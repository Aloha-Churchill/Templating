#include "Counter.hpp"
#include <iostream>

int main(){
    Counter <int> c1;

    std::vector<int> vec1 = {1,2,3,4,5};
    Counter <int> c2(vec1);

    std::cout << "Count of C2 is: " << c2.Count() << std::endl;
    c2.Remove(3);
    c2.Increment(2);
    c2.Increment(1,3);
    c2.Decrement(5);
    c2.Decrement(1,1);

    std::cout << "Count of C2 1 is: " << c2.Count(1) << std::endl;
    std::cout << "Count of c2 [1-3) is: " << c2.Count(1,3) << std::endl;
    
    std::cout << "Most Common Type is: " << c2.MostCommon() << std::endl;

    std::set<int> keys = c2.Keys();
    std::vector<int> vals = c2.Values();

    for(int k: keys){
        std::cout << k << ", ";
    }
    std::cout << "\n ---------- \n";
    for(int v: vals){
        std::cout << v << ", ";
    }
    std::cout << "\n ---------- \n";
    std::cout << "Top 2 most common: ";
    std::vector<int> mc = c2.MostCommon(2);
    for(int m: mc){
        std::cout << m << ",";
    }
    std::cout << "\n ---- -- ---- \n";

    std::cout << "Least Common Type  is: " << c2.LeastCommon() << std::endl;

    std::cout << "Top 2 least common: ";
    std::vector<int> lc = c2.LeastCommon(2);
    for(int l: lc){
        std::cout << l << ",";
    }
    std::cout << "\n ---------- \n";

    std::map<int, double> norm = c2.Normalized();
    
    for(int v: vals){
        std::cout << norm[v] << ", ";
    }

    std::cout << "\n - -- --- ---- \n";
    
    
    std::cout << c1;
    std::cout << c2;
    


    std::cout << "End of main" << std::endl;
}