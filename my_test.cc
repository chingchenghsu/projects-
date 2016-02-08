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
class foo {
public:
  int a, b, c;
  double val;
  foo(int aa) { a=aa, b=aa,c=aa; }
  bool operator<(const foo &other) const
  { return a < other.a && b < other.b && c < other.c; }
};


int main()
{
  std::map<foo, double> mymap;

  foo fa(2);
  foo fb(4);
  foo fc(10);

	cout << fa.a <<endl;
	cout << fa.b <<endl;
	cout << fa.c <<endl;
  mymap[fa] = 10.0;
  mymap[fb] = 15.0;
  mymap[fc] = 25.0;

  auto it = mymap.find(foo(2));
	cout << it->second <<endl;
  auto it2 = mymap.find(foo(4));
	cout << it2->second <<endl;
  auto it3 = mymap.find(foo(10));
	cout << it3->second <<endl;
}
