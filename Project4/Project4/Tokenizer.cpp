//
//  Tokenizer.cpp
//  Project4
//
//  Created by Devyan Biswas on 3/10/18.
//  Copyright © 2018 Devyan Biswas. All rights reserved.
//

#include <string>
#include <vector>
#include <iostream>


class Tokenizer
{
public:
    Tokenizer(std::string separators){
        for(int i = 0; i < separators.size(); i++){
            m_charToken.push_back(separators[i]);
        }
    }
    std::vector<std::string> tokenize(const std::string& s) const{ //If there is a splicer character at the end of the string, then there is another empty value. Keep in mind.
        std::string holderboi;
        std::vector<std::string> wordList;
        int i = 0;
        while(i < s.size()){
            std::vector<char>::const_iterator itr = m_charToken.begin();
            while(itr != m_charToken.end()){
                if(*itr == s[i]){
                    if(holderboi.size() != 0){
                        wordList.push_back(holderboi);
                    }
                    holderboi.clear();
                    itr = m_charToken.begin();
                    i++;
                }
                else{
                    itr++;
                }
            }
            if(i < s.size()){
                holderboi += s[i];
                i++;
            }
        }
        if(holderboi != ""){
            wordList.push_back(holderboi);
        }
        return wordList;
    }
private:
    std::vector<char> m_charToken;
};
