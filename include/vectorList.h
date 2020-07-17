// Filename: vectorList.h
// 
// Header file for the class VectorList that represents a vector of
// Node pointers within an unordered_map, indexed by word lengths
// 
// Mario Reyes, July 2020

#ifndef LIST_H
#define LIST_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node{
    string word;
    int frequency = 1;

};

class VectorList{
    private:
        unordered_map<std::string, Node*> wordExistence; // Initial data structure that keeps track of repetitions
        unordered_map<int, vector<Node*>> vectorList; // Final data structure where the Node* are ordered by frequency


    public:
        void   insertExistence(string); // Inserts node into existence for faster lookup
        Node*  findExistence(string);   // Sees if a word already exists in wordExistence, returns the node or NULL
        void   sortValues();            // Transfers nodes from wordExistence to vectorList and sorts them  
        int    length();                // Gets the number of vectors in vectorList
        int    getLongestLength();      // Get the length of the longest word in vectorList
        int    getRankSize(int);        // Finds the number of words of the specific word length provided
        pair<string, int> getInfo(int, int);          // Finds the word and frequency of the word length and rank provided
        void   printLength(int);        // Prints the words of the specific word length provided  

};

#endif
