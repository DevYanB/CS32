//
//  StudentWorld.hpp
//  NachenBlaster
//
//  Created by enika biswas on 2/28/18.
//  Copyright © 2018 David Smallberg. All rights reserved.
//

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <sstream>
#include <iostream>
#include <string>
#include <list>

class NachenBlaster;
class Actor;
class Cabbage;
class Smallgon;


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld(); //virtual or not??
    virtual void collElement(Actor* cab);
    virtual void collTorpedo(Actor* c);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    virtual void setDestroyedAlienCount() { killedAlienShipCount++;}
    virtual unsigned long size() { return result.size();}
    virtual void addTo(Actor* act){
        result.push_back(act);
    }
    virtual int getETicks(){ return expTicks;}
    virtual int getTicks() { return m_ticks;}
    virtual NachenBlaster* getPlayer() {
        return player;
    }
    double ed(double x1, double y1, double x2, double y2);
    
private:
    int m_ticks;
    int expTicks;
    int killedAlienShipCount;
    double alienHealthSmallgon;
    double alienHealthSnagglegon;
    int totalTillNext;
    int remainingShips;
    int maxOnScreen;
    int onScreen;
    int maxShips;
    //ostringstream res;
    std::list<Actor*> result;
    NachenBlaster* player;
};

#endif/* StudentWorld_hpp */
