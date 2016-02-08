###########################################################################################################
#
#   Program name :  anagram_finder.py 
#   Author : Ching-Cheng Hsu 
#            sunny.reis@googlemail.com   
#   Goal:    Given a word, try to find all the anagrams of this word in the given document called WORD.LST 
#   Data:    August 6th 2015          
#
#############################################################################################################  
import sys
from collections import defaultdict

def annograms(word):
#    mymap={}
    dic_list=[]
    word_list=[]
    inputmap=defaultdict(int)
    for chara in word.strip():
        inputmap[chara] +=1

    for w in open('WORD.LST'):
        mymap=defaultdict(int)
        for character in w.rstrip():
            mymap[character] +=1
        dic_list.append(mymap)
        word_list.append(w.strip())

    anagram_list=[]
    i=0
    for x in dic_list:
        if x ==inputmap:
            anagram_list.append(word_list[i])
        i=i+1

    return anagram_list
if __name__ == "__main__":
    print annograms("aahed")
    print '--'
