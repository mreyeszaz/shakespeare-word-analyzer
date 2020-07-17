// File Name: vectorList.cpp
// 
// Contains the functions needed to implement the VectorList
// 
// Mario Reyes, July 2020

#include "vectorList.h"
#include <iostream>
#include <algorithm>

using namespace std;


/**
    Inserts a word in the form of a Node* into the wordExistence structure.
    @param wordToInsert The word to insert into wordExistence.
    @return N/A.
*/
void VectorList::insertExistence(string wordToInsert){
    Node *to_add = new Node;
    to_add->word = wordToInsert;
    
    wordExistence[wordToInsert] = to_add;
}

/**
    Custom comparator to sort Node pointers by frequency and then lexicographically if tied.
    @param n1, n2 The Node pointers to be sorted.
    @return bool Boolean that states whether n1 comes before n2 or not.
*/
bool compareNodes(const Node* n1, const Node* n2)
{ 
    return n1->frequency > n2->frequency ||
        (n1->frequency == n2->frequency && n1->word < n2->word);
} 

/**
    Transfers all Node pointers from wordExistence into vectorList and finally sorts then Node pointers.
    @param N/A.
    @return bool Boolean that states whether n1 comes before n2 or not.
*/
void VectorList::sortValues(){
    for(auto i : wordExistence){
        vectorList[i.first.length()].push_back(i.second);
    }

    for (pair<int, vector<Node*>> wordList : vectorList)
    {
        sort(vectorList[wordList.first].begin(), vectorList[wordList.first].end(), compareNodes);
    }   
}

/**
    Finds a word in the wordExistence structure, if it exists.
    @param wordToFind The word to find in the wordExistence structure.
    @return Pointer to the node containing the word.
*/
Node* VectorList::findExistence(string wordToFind){
    unordered_map<std::string,Node*>::const_iterator found = wordExistence.find(wordToFind);

    if(found == wordExistence.end())
        return NULL;
    else
        return found->second;
}

/**
    Gets the size of the VectorList a.k.a. the number of word lengths.
    @param N/A.
    @return Number of word lengths present in the VectorList.
*/
int VectorList::length(){
    return vectorList.size();
}

/**
    Gets the length of thelongest word found in vectorList
    @param N/A.
    @return Longest word length
*/
int VectorList::getLongestLength(){
    int longest = 0;
    for(auto i : vectorList){
        if(longest < i.first)
            longest = i.first;
    }
    return longest;
}

/**
    Gets the number of words found in a vector.
    @param index The index of the unordered map. 
    @return Size of the vector of words for that index.
*/
int VectorList::getRankSize(int index){
    int rankSize = vectorList[index].size();
    return rankSize;
}

/**
    Gets the string at the indicated rank number.
    @param l,r The length to access the correct vector and rank to get the string.
    @return String of the node found at the provided rank.
*/
pair<string, int> VectorList::getInfo(int l, int r){
     string word = vectorList[l][r]->word;
     int frequency = vectorList[l][r]->frequency;
     return make_pair(word, frequency);
}

/**
    Prints all words found of the specific length.
    @param wordLength The length of the words to be printed to cout.
    @return N/A.
*/
void VectorList::printLength(int wordLength){
    cout << "PRINTING WORDS OF LENGTH " << wordLength << " :" << endl;
    for(auto i : vectorList[wordLength]){
        cout << i->word << "     " << "Frequency: " << i->frequency << endl;
    }
    
}