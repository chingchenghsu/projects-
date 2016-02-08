//**************************************************************//
//        Ching-Cheng Hsu 
//        sunny.reis@googlemail.com 
//        Fifth version,  July, 2015 
//         
//        Purpose: Calculate the anagrams of one article 
//        Promise: Ouput the anagrams of an article 
//        Filename: my_ana.cc 
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
#include<set> 

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

typedef multimap<map<char,int>,string> mm; 
typedef map<map<char,int>,set<string>> ms; 

ms convert(const mm& m)
{   
    ms r;
    for (mm::const_iterator it = m.begin(); it != m.end(); ++it)
    {   
        set<string>& s(r[it->first]);
        s.insert(it->second);
    }   
    return r;
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
        mm  my_words_mmap;
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
/* Following loop is used for de-bugging purpose */
			for (it_p = word_tmp_map.begin(); it_p != word_tmp_map.end(); it_p++)		{
			cout << it_p->first << "  " << it_p->second <<endl;
			}
			my_words_mmap.insert(std::pair<map<char,int>,string>(word_tmp_map,word));
			}  // loop while 
        infile.close();

// print out individual anagrams, we ignored repeated strings, just consider them as only one.  
	ms s(convert(my_words_mmap)); 
	for (ms::iterator it_s = s.begin(); it_s != s.end(); ++it_s) 
	{
		set<string> &st(it_s->second); 
		copy(st.begin(), st.end(), ostream_iterator<string>(cout, ", "));
		cout << " ----- anagram happens " << st.size()    << " times ";
        	cout << endl;

		}
        myfile.close();
        }   // if(infile) 
        else
        {
        cout << "problem with file: not exist " <<endl;
        } // else no file  


 


}  // main 



