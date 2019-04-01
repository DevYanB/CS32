#include "provided.h"

#include <string>

#include <vector>

#include <functional>

#include <iostream>

#include <fstream>

#include "MyHash.h"

using namespace std;



class WordListImpl

{
    
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash<std::string, vector<std::string>> wordList;
    string convertPattern(string s) const {
        std::string result = s;
        for(int i = 0; i < result.size()-1; i++) {
            char var = 'A' + i;
            
            if(isupper(result[i])) {
                
                continue;
                
            }
            
            for(int j = i+1; j < s.size(); j++) {
                
                if(result[i] == result[j])
                    
                    result[j] = var;
                
            }
            
            result[i] = var;
            
        }
        
        return result;
        
    }
    
    
    
};







bool WordListImpl::loadWordList(string filename)

{
    
    ifstream infile(filename);
    
    if( !infile)
        
        return false;
    
    std::string s;
    
    bool checker = true;
    
    while(getline(infile, s)) {
        
        checker = true;
        
        for(int i = 0; i < s.size(); i ++){
            
            if(!isalpha(s[i]) && !(s[i] == '\'')){
                
                checker = false;
                
                break;
                
            }
            
        }
        
        if(checker){
            
            string y = convertPattern(s);
            
            if(wordList.find(y) == nullptr) {
                
                vector<std::string> x;
                
                x.push_back(s);
                
                wordList.associate(y, x);
                
            }
            
            else {
                
                
                
                wordList.find(y)->push_back(s);
                
            }
            
            //store as y = call the function to turn into pattern
            
            //call find == nullptr {
            
            //   push s into vector
            
            //    associate (y, l)
            
            // else { find(f(s)) vector push s;
            
            /*wordList.associate(s, 0); */
            
            //std::cout << s << std::endl;
            
        }
        
    }
    
    /*
     
     std::vector<std::string> *holder = wordList.find("abba");
     
     std::cout << holder->size() << std::endl;
     
     
     
     for(int j = 0; j < (holder->size()); j++) {
     
     std::cout << (*holder)[j] << std::endl;
     
     }
     
     */
    
    return true;
    
}  // This compiles, but may not be correct

//xyqbbq

bool WordListImpl::contains(string word) const

{
    
    if((wordList.find(convertPattern(word))) != nullptr)
        
    {
        
        vector<string> h = *(wordList.find(convertPattern(word)));
        
        for(int i = 0; i < h.size(); i++) {
            
            if(h[i] == word)
                
                return true;
            
        }
    }
    return false;
    //return wordList.find(convertPattern(word)) != nullptr; // This compiles, but may not be correct
    
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    vector<string> h = *(wordList.find(convertPattern(cipherWord)));
    for(int j = 0; j < currTranslation.size();j++){
        if(currTranslation[j] == '?'){ //!isalpha
            continue;
        }
        else {
            vector<string>::iterator it = h.begin();
            while(it != h.end()) {
                if((*it)[j] == currTranslation[j])
                    it++;
                else
                    it = h.erase(it);
            }
        }
    }
    return h;  // This compiles, but may not be correct
}



//***** hash functions for string, int, and char *****



unsigned int hash(const std::string& s)

{
    
    return std::hash<std::string>()(s);
    
}



unsigned int hash(const int& i)

{
    
    return std::hash<int>()(i);
    
}



unsigned int hash(const char& c)

{
    
    return std::hash<char>()(c);
    
}



//******************** WordList functions ************************************



// These functions simply delegate to WordListImpl's functions.

// You probably don't want to change any of this code.



WordList::WordList()

{
    
    m_impl = new WordListImpl;
    
}



WordList::~WordList()

{
    
    delete m_impl;
    
}



bool WordList::loadWordList(string filename)

{
    
    return m_impl->loadWordList(filename);
    
}



bool WordList::contains(string word) const

{
    
    return m_impl->contains(word);
    
}



vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const

{
    
    return m_impl->findCandidates(cipherWord, currTranslation);
    
}


