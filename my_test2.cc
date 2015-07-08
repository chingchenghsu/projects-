//**************************************************************//
//        Ching-Cheng Hsu 
//        sunny.reis@googlemail.com 
//        First version,  March 20, 2015 
//         
//        Purpose: Test the behavoir of STL map  
//                 Test if the key of the map is a class, how to find the 
//		   correct key of the corresponding map. 
//        Filename: my_test.cc 
//**************************************************************//

#include <iostream>
#include <utility>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include<fstream>
#include<sstream>
#include<iterator>


using namespace std;

template <typename Map>
bool map_compare (Map const &lhs, Map const &rhs) {
    // No predicate needed because there is operator== for pairs already.
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(),
                      rhs.begin());
}

class foo {
public:
  int a, b, c;
  double val;
  foo(int aa) { a=aa, b=aa,c=aa; }
  bool operator<(const foo &other) const
  { return a < other.a && b < other.b && c < other.c; }
  bool operator==(const foo &other) const
  { return a == other.a && b == other.b && c == other.c; }
};


int main()
{
  std::map<foo, double> mymap;
  std::map<foo, double> mymap2;
  std::vector<map<foo, double>> mymap_vec;

  foo fa(2);
  foo fb(4);
  foo fc(10);

	cout << fa.a <<endl;
	cout << fa.b <<endl;
	cout << fa.c <<endl;
  mymap[fa] = 10.0;
  mymap[fb] = 15.0;
  mymap[fc] = 25.0;
	
  mymap2[fa] = 10.0;
  mymap2[fb] = 15.0;
  mymap2[fc] = 25.0;

  auto it = mymap.find(foo(2));
	cout << it->second <<endl;
  auto it2 = mymap.find(foo(4));
	cout << it2->second <<endl;
  auto it3 = mymap.find(foo(10));
	cout << it3->second <<endl;
	mymap_vec.push_back(mymap);
	mymap_vec.push_back(mymap2);
/*
	To print out the elements in vectors of maps 
*/
	  std::vector<map<foo, double>>:: iterator it_v, it_v2; 
	for (it_v =mymap_vec.begin(); it_v !=mymap_vec.end(); it_v++)
	{
  		std::map<foo, double>:: iterator it_m; 
		auto it_mm = (*it_v).find(foo(4));
	 cout << "------------------------------------------- " << endl;
		 cout << it_mm->second <<endl;

		for (it_v2 =mymap_vec.begin(); it_v2 !=mymap_vec.end(); it_v2++)
		{
			if (map_compare((*it_v),(*it_v2)) && (it_v)!=(it_v2) ) {
				cout << " yes ! this is what we want " <<endl;
				cout << " yes ! this is the inner loop" <<endl; } 

			}
// loop over all the elements in the vector of maps 		
//		for (it_m = it_v->begin(); it_m !=it_v->end(); it_m++) 
//			cout << (it_m->second) << endl;
		
		}	
}
