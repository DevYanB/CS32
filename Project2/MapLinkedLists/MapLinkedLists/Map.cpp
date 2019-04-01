//
//  Map.cpp
//  MapLinkedLists
//
//  Created by Devyan Biswas on 1/26/18.
//  Copyright © 2018 Devyan Biswas. All rights reserved.
//

#include "Map.h"

//---Implementation of Map Class members---
Map::Map() : head(nullptr), m_size(0){};
    //tail = nullptr; //is tail really needed???

Map::~Map(){ //Go through the elements of the list, keeping track of next, and deleting as you go along.
    Node* ptr = head;
    while(ptr != nullptr){
        Node *hold = ptr->next;
        delete ptr;
        ptr = hold;
    }
    m_size = 0;
}

Map::Map(const Map& cpyMap){ //Build a new map based on the features of the cpyMap
    this->m_size = 0;
    head = nullptr;
    //tail = nullptr;
    for(int i = 0; i < cpyMap.m_size; i++){
        KeyType k;
        ValueType v;
        cpyMap.get(i,k,v);
        insert(k,v);
    }
}

Map& Map::operator= (const Map& cpyMap){ //returns the new, changed map, which sets the left hand side to it
    if(this == &cpyMap){
        return *this;
    }
    //swap(cpyMap); //Cant do this, because this involves altering a constant
    Map temp = cpyMap;
    swap(temp);
    return *this;
}

bool Map::contains(const KeyType& key) const{
    Node* ptr = head;
    while(ptr != nullptr){
        if(ptr->m_key == key){
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

bool Map::empty() const{
    return m_size == 0;
}

int Map::size() const{
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value){ //Adds to the start of the list. Doesn't matter the order! If insert was overloaded for insertion at different locations in the list, then tail would be useful.
    if(contains(key)){
        return false;
    }
    Node* newNode = new Node;
    newNode->m_key = key;
    newNode->m_value = value;
    if(empty()){
        newNode->next = nullptr;
        newNode->prev = nullptr;
        head = newNode;
        m_size++;
        return true;
    }
    newNode->next = head;
    newNode->prev = nullptr;
    head->prev = newNode;
    head = newNode;
    m_size++;
    return true;
    
}

bool Map::update(const KeyType& key, const ValueType& value){
    if(!contains(key)){
        return false;
    }
    Node* ptr = head;
    while(ptr != nullptr){
        if(ptr->m_key == key){
            ptr->m_value = value;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    if(update(key , value)){
        return true;
    }
    return insert(key , value);
}

bool Map::erase(const KeyType& key){ //This is function will benefit from including a tail pointer becasue removal from the end could be done quicker. This also where previous will come in handy
    
    //key not within list
    if(!contains(key)){
        return false;
    }
    //empty list
    if(head == nullptr || size() == 0){
        return false;
    }
    //Remove if 1 element OR first element
    if(head->m_key == key){
        Node* nodeToDelete = head;
        head = head->next;
        if(head != nullptr){ //if there is another element after, have to set the previoud to null
            head->prev = nullptr;
        }
        delete nodeToDelete;
        m_size--;
        return true;
    }
    
    //Remove if last OR middle element
    Node* ptr = head;
    while(ptr != nullptr ){
        if(ptr->m_key == key){ //if the mathing node value
            //Do deletion
            ptr->prev->next = ptr->next;
            if(ptr->next != nullptr){ //if there is something after the deletion element, you have to set the previous pointer of that element to be the previoud pointer of the deletion element
                ptr->next->prev = ptr->prev;
            }
            delete ptr;
            m_size--;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const{
    Node* ptr = head;
    while(ptr != nullptr){
        if(ptr->m_key == key){
            value = ptr->m_value;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const{
    if(i < 0 || i >= size()){
        return false;
    }
    Node* ptr = head;
    for(int place = 0; place < i; place++){ //will go through n elements. Remember that it cannot be equal to size(), as that is for the programmer's ease, the actual value is one less, so have it start at 0 and go till < i, as that is how we will be callign this function
        ptr = ptr->next;
    }
    key = ptr->m_key;
    value = ptr->m_value;
    return true;
}

void Map::swap(Map& other){ //flip the sizes, then flip the heads. This means each map's head will be pointing to the other map, adn the sizes will also be switched accordingly
    
    int tempS = other.m_size; //temp integer for switching
    Node* tempN = other.head; //temp node for swtiching
    
    other.m_size = this->m_size;
    other.head = this->head;
    
    this->m_size = tempS;
    this->head = tempN;
    
}
//---Implementation of Map Algorithms---

bool combine(const Map& m1, const Map& m2, Map& result){
    bool hold = true;
    result = m1; //we will do things based off of m1's values; could use m2, then we would be iterating up till the size of m1 in next step!
    for(int i = 0; i < m2.size(); i++){
        KeyType k;
        ValueType v;
        ValueType vCheck;
        m2.get(i,k,v); //this is to be able to add the value of m2 to m1
        if(result.contains(k)){
            m1.get(k,vCheck); //This step checks wether with the corresponding k value i, v and vCheck are different or not; this will tell us wether to remove or simply comtinue through the loop
            if(v != vCheck){
                result.erase(k);
                hold = false;
            }
            continue;
        }
        result.insert(k,v);
    }
    return hold;
}

void subtract(const Map& m1, const Map& m2, Map& result){
    Map holder;
    result = holder; //holder now holds result, and result is empty. don't do holder = result, since that doesn't affect result. could do holder.swap(result) as that would set result to an empty map
    for(int i = 0; i < m1.size(); i++){
        KeyType k;
        ValueType v;
        m1.get(i,k,v);
        if(!m2.contains(k)){ //if there is a similar k between the two, don't add it to the result!
            result.insert(k,v);
        }
    }
}
