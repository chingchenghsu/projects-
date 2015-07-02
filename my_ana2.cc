//**************************************************************//
//        Ching-Cheng Hsu 
//        sunny.reis@googlemail.com 
//        First version,  March 20, 2015 
//         
//        Purpose: Calculate the median of the word numbers in sentences
//        Promise: Ouput the median statistics to an output file 
//        Filename: cchsu_median_cal.cc
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
using namespace std;
bool IsNotWord(char & s){
                        return (s==',' || s=='.'|| s=='-' || s=='\'');
                }

int main (int argc, char* argv[]) {
    using namespace std;
// open the file and read words into 
    if (argc < 2)
                { cout << " No Input File " <<endl;
                        exit(0);
                }
        ifstream infile(argv[1]);
        ofstream myfile(argv[2]);
        map<string,int> mymap;
        vector<map<char, int>> words_v;
	string::iterator it;	

        if (infile)
        {
		stringstream  mystring;
		string word;
		mystring << infile.rdbuf();
	        while(mystring >> word){ 
			map<char, int> word_tmp_map;  
			cout << word <<endl;
			word.erase(remove_if(word.begin(),word.end(),IsNotWord), word.end());
			for (int n= 0; n != word.length(); n++)
			{
				cout << word[n] <<endl;		
				word_tmp_map[word[n]]++; 
			}
			map<char, int>::iterator it_p;
			for (it_p = word_tmp_map.begin(); it_p != word_tmp_map.end(); it_p++)		{
			cout << it_p->first << "  " << it_p->second <<endl;
			}
			words_v.push_back(word_tmp_map);
			}
        infile.close();
	
        myfile.close();
        }   // if(infile) 
        else
        {
        cout << "problem with file: not exist " <<endl;
        } // else no file  


	vector<map<string, int> > mywords_v;
 


/*
    map<string,string> a, b;

    a["Foo"] = "0";
    a["Bar"] = "1";
    a["Frob"] = "2";
    a["Frob2"] = "3";

    b["Foo"] = "0";
    b["Bar"] = "1";
    b["Frob"] = "2";

    cout << "a == b? " << map_compare (a,b) << " (should be 1)\n";
    b["Foo"] = "1";
    cout << "a == b? " << map_compare (a,b) << " (should be 0)\n";

    map<string,string> c;
    cout << "a == c? " << map_compare (a,c)  << " (should be 0)\n";

//    multimap<vector<int>, int>  c100, d100;
//	vector<int> c99={1,2};
//	c100.insert(std::pair<vector<int>, int> (c99,10));
        multimap<map<string,string>, int>  c100, d100;
	c100.insert(std::pair<map<string,string>, int> (a,10));
*/
}



