//
//  MyHash.h
//  Project4
//
//  Created by Devyan Biswas on 3/9/18.
//  Copyright © 2018 Devyan Biswas. All rights reserved.
//
// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
//#ifndef MYHASH_INCLUDED
//#define MYHASH_INCLUDED

#include <unordered_map>  // YOU MUST NOT USE THIS HEADER IN CODE YOU TURN IN
#include <algorithm>

// In accordance with the spec, YOU MUST NOT TURN IN THIS CLASS TEMPLATE,
// since you are not allowed to use any STL containers, and this
// implementation uses std::unordered_map.

// This code is deliberately obfuscated.

// If you can not get your own MyHash class template working, you may use
// this one during development in order to let you proceed with implementing
// the other classes for this project; you can then go back to working on
// fixing your own MyHash class template.
/*
template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
    using O=KeyType;using maxloadfactor=float;using O10=int;void reset(){
        maxloadfactor max_1oad_factor=l01.max_load_factor();l01.clear();l01.
        max_load_factor(max_1oad_factor);l01.rehash(doub1e+doub1e);}using String=
    double;using l0=ValueType;using l1O=O10 const;MyHash(String d0uble=doub1e/10):
    l01(doub1e+doub1e){l01.max_load_factor(std::min<maxloadfactor>(doub1e/5/5,
                                                                   std::max<maxloadfactor>((double)doub1e/(doub1e+doub1e),d0uble)));}using l10=O
    const;using Const=MyHash<O,l0>;String getLoadFactor()const{return l01.
        load_factor();}using ll0=l0 const;O10 getNumItems()const{return l01.size(
            );}using l00=Const const;void associate(l10&Using,ll0&first){l01[Using]=
                first;}using l1=std::unordered_map<O,l0>;ll0*find(l10&l11)const{auto first(l01.
                                                                                           find(l11));return(first!=l01.end()?&first->second:0);}l0*find(l10&l01){return(
                                                                                                                                                                         l0*)(*(l00*)(this)).find(l01);}private:static l1O doub1e{50};l1 l01;
};
*/
//#endif // MYHASH_INCLUDED

#ifndef MyHash_h
#define MyHash_h
#include <iostream>
#include <functional>

template <class KeyType, class ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key,const ValueType& value);
    const ValueType* find(const KeyType& key) const;
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }
    int getNumItems() const;
    double getLoadFactor() const;
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
private:
    struct HashNode{
        HashNode(KeyType key, ValueType val, HashNode* n){
            m_key = key;
            m_val = val;
            m_next = n;
        }
        HashNode* getNext(){
            return m_next;
        }
        KeyType getKey(){
            return m_key;
        }
        ValueType getValue(){
            return m_val;
        }
        void setValue(ValueType val){
            m_val = val;
        }
        KeyType m_key;
        ValueType m_val;
        HashNode* m_next;
        
    };
    HashNode **m_HashTable;
    int currentItems; //This is the number of items currently initialized into the map.
    double m_maxLoad; //This, will tell us the max load, in range from 0 to 2.
    int m_numBuckets; //This is the number of slots/buckets in the dynamic array.
    // int //m_maxItems; //This is the result of multiplying the number of buckets with the load, giving us the max items that can be placed in the table.
};

template <class KeyType,class ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor){
    m_numBuckets = 100;
    m_HashTable = new HashNode*[m_numBuckets];
    for(int i = 0; i < m_numBuckets; i++){
        m_HashTable[i] = nullptr;
    }
    if(maxLoadFactor <= 0){
        m_maxLoad = 0.5;
    }
    else if( maxLoadFactor > 2.0){
        m_maxLoad = 2.0;
    }
    else{
        m_maxLoad = maxLoadFactor;
    }
    currentItems = 0;
    //m_maxItems = (int)(m_numBuckets * m_maxLoad);
    //std::cout << //m_maxItems << std::endl;
    //std::cout << m_maxLoad << std::endl;
    //std::cout << m_numBuckets << std::endl;
    //std::cout << currentItems << std::endl;
}

template <class KeyType,class ValueType> //REIMPLEMENT WITH FIND FUNCTION TO GET TO O(N) TIME
MyHash<KeyType, ValueType>::~MyHash(){
    //int count = 0;
    for(int i = 0; i < m_numBuckets; i++){
        if(m_HashTable[i] != nullptr){
            HashNode *previous = nullptr;
            HashNode *curr = m_HashTable[i];
            while(curr != nullptr){
                previous = curr;
                curr = curr->getNext();
                delete previous;
            }
        }
        //std::cout << count << std::endl;
        //count++;
    }
    delete [] m_HashTable;
    //std::cout << "Shit..." << std::endl;
}

template <class KeyType,class ValueType>
void MyHash<KeyType, ValueType>::reset(){
    for(int i = 0; i < m_numBuckets; i++){
        if(m_HashTable[i] != nullptr){
            HashNode *previous = nullptr;
            HashNode *curr = m_HashTable[i];
            while(curr != nullptr){
                previous = curr;
                curr = curr->getNext();
                delete previous;
            }
        }
    }
    delete [] m_HashTable;
    m_numBuckets = 100;
    m_HashTable = new HashNode*[m_numBuckets];
    for(int i = 0; i < m_numBuckets; i++){
        m_HashTable[i] = nullptr;
    }
    currentItems = 0;
    //m_maxItems = (int)(m_numBuckets * m_maxLoad);
}

template <class KeyType, class ValueType>
void MyHash<KeyType,ValueType>::associate(const KeyType& key,const ValueType& value){
    unsigned int hash(const KeyType& k);
    unsigned int index = hash(key) % m_numBuckets;
    if(getLoadFactor() >= m_maxLoad){
        int tBucks = m_numBuckets * 2;
        HashNode** temp = new HashNode*[tBucks];
        for(int i = 0; i < tBucks; i++){
            temp[i] = nullptr;
        }
        for(int i = 0; i < m_numBuckets; i++){
            if(m_HashTable[i] != nullptr){
                unsigned int newIndex = hash(m_HashTable[i]->m_key) % tBucks;
                temp[newIndex] = m_HashTable[i];
            }
        }
        delete [] m_HashTable;
        m_HashTable = temp;
        m_numBuckets = tBucks;
    }
    //If the current value of load exceeds the max load, then re-allocate to a new, larger one: TODO
    if(m_HashTable[index] == nullptr){
        m_HashTable[index] = new HashNode(key,value,nullptr);
        currentItems++;
        return;
    }
    else{
        if(key == m_HashTable[index]->getKey()){
            //std::cout << "It went through the identical key thing" << std::endl;
            m_HashTable[index]->setValue(value);
            return;
        }
        m_HashTable[index] = new HashNode(key,value,m_HashTable[index]);
        currentItems++;
    }
    
    //std::cout << key << std::endl;
    //std::cout << h << std::endl;
}

template <class KeyType, class ValueType>
const ValueType* MyHash<KeyType,ValueType>::find(const KeyType &key) const{
    unsigned int hash(const KeyType& k);
    unsigned int index = hash(key) % m_numBuckets;
    if(m_HashTable[index] != nullptr){
        HashNode *previous = nullptr;
        HashNode *curr = m_HashTable[index];
        while(curr != nullptr){
            if(curr->m_key == key){
                return &m_HashTable[index]->m_val;
            }
            previous = curr;
            curr = curr->getNext();
        }
        //if(&m_HashTable[index]->m_key == key){
        //return (&m_HashTable[index]->m_val);
        //}
        //else{
        //}
    }
    return nullptr;
}

template <class KeyType, class ValueType>
int MyHash<KeyType,ValueType>::getNumItems() const{
    return currentItems;
}


template <class KeyType,class ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const{
    return (double)currentItems / (double)m_numBuckets;
}

#endif /* MyHash_h */
