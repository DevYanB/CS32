//
//  main.cpp
//  Project4
//
//  Created by Devyan Biswas on 3/8/18.
//  Copyright © 2018 Devyan Biswas. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "MyHash.h"
#include "Tokenizer.cpp"
#include "provided.h"
using namespace std;

int main(int argc, const char * argv[]) {
    WordList wl;
    if ( ! wl.loadWordList("/Users/devyanbiswas/Desktop/CS32/Project4/Project4/wordlist.txt"))
    {
        cout << "Unable to load word list" << endl;
        return 1;
    }
    if (wl.contains("onomatopoeia"))
        cout << "I found onomatopoeia!" << endl;
    else
        cout << "Onomatopoeia is not in the word list!" << endl;
    string cipher = "xyqbbq";
    string decodedSoFar = "?r????";
    vector<string> v = wl.findCandidates(cipher, decodedSoFar);
    if (v.empty())
        cout << "No matches found" << endl;
    else
    {
        cout << "Found these matches:" << endl;
        for (size_t k = 0; k < v.size(); k++)
            cout << v[k] << endl; // writes grotto and troppo
    }
    /*
    WordList wordboi;
    wordboi.loadWordList("/Users/devyanbiswas/Desktop/CS32/Project4/Project4/wordlist.txt");
    if(wordboi.contains("$$$")){
        cout << "GOT IT" << endl;
    }
    else{
        cout << "DONT GOT IT" << endl;
    }
    
    MyHash<char, int> hashtester(0.6);
    hashtester.associate('A' , 32);
    hashtester.associate('C' , 2);
    hashtester.associate('C', 23);
    cout << *hashtester.find('C') << endl;
    
    cout << hashtester.getNumItems() << endl;
    cout << hashtester.getLoadFactor() << endl;
    hashtester.reset();
    cout << hashtester.getNumItems() << endl;
    cout << hashtester.getLoadFactor() << endl;
    cout << "Hello World first test" << endl;
    MyHash<char, char> hasheronie(0.6);
    hasheronie.associate('A','B');
    hasheronie.associate('A', 'C');
    MyHash<char, int> hasher(0.3);
    hasher.associate('B', 3);
    MyHash<string, int> haterboi(0.4);
    haterboi.associate("Apples", 6);
    haterboi.associate("Apples", 4);
    cout << haterboi.getNumItems() << endl;
    cout << hasher.getNumItems() << endl;
    cout << hasheronie.getNumItems() << endl;
    hasheronie.reset();
    cout << "Hello World second test" << endl;
    
    Tokenizer tokenboi(" ,!.$#");
    vector<string> vectorTest = tokenboi.tokenize("Rishab, you are, like, a sexy $$ beast!! #swag");
    for(vector<string>::iterator itr = vectorTest.begin(); itr != vectorTest.end(); itr++){
        cout << *itr << endl;
    }
    */
}
