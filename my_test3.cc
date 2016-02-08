//**************************************************************//
//        Ching-Cheng Hsu 
//        sunny.reis@googlemail.com 
//        First version,  March 20, 2015 
//         
//        Purpose: Test the behavoir of STL map  
//                 Test if the key of the multimap is a map, how to find the 
//		   same keys inside the multimap. 
//        Filename: my_test3.cc 
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
  bool operator<<(const foo &other) const 
  {
	return other.a; 
	}

};


int main()
{
  typedef map<foo, double> inner_map;  
  std::map<foo, double> mymap;
  std::map<foo, double> mymap2;
  std::map<foo, double> mymap3;
  std::vector<map<foo, double>> mymap_vec;
  std::multimap<map<foo, double>, int> mymap_map;

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
  mymap2[fc] = 26.0;

  mymap3[fa] = 10.0;
  mymap3[fb] = 15.0;
  mymap3[fc] = 25.0;

  auto it = mymap.find(foo(2));
	cout << it->second <<endl;
  auto it2 = mymap.find(foo(4));
	cout << it2->second <<endl;
  auto it3 = mymap.find(foo(10));
	cout << it3->second <<endl;
	mymap_vec.push_back(mymap);
	mymap_vec.push_back(mymap2);

	mymap_map.insert(std::pair<map<foo,double>,int>(mymap,3));
	mymap_map.insert(std::pair<map<foo,double>,int>(mymap2,1));
	mymap_map.insert(std::pair<map<foo,double>,int>(mymap3,10));

	std::multimap<map<foo, double>, int>:: iterator it_m;
	cout << " counts with the mymap: "  << mymap_map.count(mymap) <<endl; 
	cout << " counts with the mymap2: "  << mymap_map.count(mymap2) <<endl; 

	std::pair <std::multimap<map<foo,double>,int>::iterator, std::multimap<map<foo,double>,int>::iterator> ret;
// the iterator will return the components which have the same keys (which is map) here 
    ret = mymap_map.equal_range(mymap); 
  
// print out the components where you have the same keys 

	for (std::multimap<map<foo,double>,int>::iterator it=ret.first; it!=ret.second; ++it)
		{
		std::cout << ' ' << it->second << endl;

// print out the components where the contents of the maps 
		for (auto it_mm = it->first.begin();  it_mm != it->first.end(); it_mm++)
		{
			cout << it_mm->second <<endl;
			}
		}
}
