//
//  StudentWorld.cpp
//  NachenBlaster
//
//  Created by Devyan Biswas on 2/28/18.
//  Copyright © 2018 David Smallberg. All rights reserved.
//

#include "StudentWorld.h"
#include "Actor.h"
#include <iostream>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
}

StudentWorld::~StudentWorld(){
    cleanUp();
}

double StudentWorld::eud(double x1, double y1, double x2, double y2){
    double x = x1 - x2; //calculating number to square in next step
    double y = y1 - y2;
    double dist;
    
    dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
    dist = sqrt(dist);
    
    return dist;
}
void StudentWorld::collCab(Actor* cab) {
    
    list<Actor*>::iterator it = result.begin();
    while(it != result.end()) {
        if((*it)->isDamageable()){
            if(eud(cab->getX(),cab->getY(),(*it)->getX(),(*it)->getY())
               < 0.75 * (cab->getRadius() + (*it)->getRadius())){
                (*it)->sufferDamage();
                cab->setAliveState(false);
                //Explosion* explo = new Explosion(cab->getX(),cab-> getY(), this);
                playSound(SOUND_BLAST);
                break;
            }
        }
        it++;
    }
}

void StudentWorld::collTorpedo(Actor* c) {
    list<Actor*>::iterator it = result.begin();
    while(it != result.end()) {
        if((*it)->isDamageable()){
            if(eud(c->getX(),c->getY(),(*it)->getX(),(*it)->getY())
               < 0.75 * (c->getRadius() + (*it)->getRadius())){
                (*it)->torpedoDamage();
                c->setAliveState(false);
                //Explosion* explo = new Explosion(cab->getX(),cab-> getY(), this);
                playSound(SOUND_BLAST);
            }
        }
        it++;
    }
}

int StudentWorld::init()
{
    alienHealthSmallgon = 5*(1+(this->getLevel()-1)*0.1);
    alienHealthSnagglegon =  10*(1+(this->getLevel()-1)*0.1);
    //cout << alienHealthSmallgon << endl;
    totalTillNext = 6 + 4*(getLevel());
    //cout << totalTillNext << endl;
    maxOnScreen = 4 +(0.5*getLevel());
    onScreen = 0; //OR 4 
    killedAlienShipCount = 0;
    m_ticks = 0;
    player = new NachenBlaster(this);
   // result.push_back(new Smallgon(VIEW_WIDTH-1,randInt(0,VIEW_HEIGHT-1), this,alienHealthSmallgon, 0));
    //result.push_back(new Smallgon(VIEW_WIDTH-1,randInt(0,VIEW_HEIGHT-1), this,alienHealthSmallgon, 0));
  //  result.push_back(new Smallgon(VIEW_WIDTH-1,randInt(0,VIEW_HEIGHT-1), this,alienHealthSmallgon, 0));
    //result.push_back(new Smoregon(256,160, this));
    // result.push_back(new Smoregon(256, 45, this));
    //result.push_back(new Snagglegon(VIEW_WIDTH-1,randInt(0,VIEW_HEIGHT-1), this,alienHealthSnagglegon, 0));
    //while the level hasn't ended yet
    for(int s = 0; s < 30; s++){
        int i = randInt(0,256);
        int j = randInt(0,256);
        double z = (randInt(5, 50))/100.0;
        result.push_back(new Star(i,j,this, z));
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    ostringstream res;
    res << "Lives: " << getLives();
    res << "  Health: " << (int)((player->getHpoints()/50.0) * 100) << "%";
    res << " Score: " << getScore();
    res << "  Level: " << getLevel();
    res << "  Cabbages: " <<(int)((player->getCPoints() / 30.0) * 100)<< "%";
    res << "  Torpedos: " << player->getTorpedoCount();
    string s = res.str();
    setGameStatText(s);
    //setGameStatText(s)
    //  res << "Lives: " << getLives() << " Health: " << (player->getHpoints()/50.0) * 100 << "% ";
    remainingShips = totalTillNext - killedAlienShipCount;
    //cout<< killedAlienShipCount << endl;
    //int holder = randInt(1, 6);
    player->doSomething();
    if(!(player->alive())){
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    if(killedAlienShipCount == totalTillNext){
        return GWSTATUS_FINISHED_LEVEL;
    }
    list<Actor*>::iterator it;
    it = result.begin();
    while(it != result.end()){
        if((*it)->alive()){
            (*it)->doSomething();
            it++;
        }
        else {
            if((*it)->isDamageable()){
                onScreen--;
                if((*it)->getX() > 1){
                    result.push_back(new Explosion((*it)->getX(), (*it)->getY(), this, m_ticks));
                    playSound(SOUND_BLAST);
                    expTicks = m_ticks;
                }
                //cout <<  killedAlienShipCount << endl;
            }
            delete (*it);
            it = result.erase(it);
        }
    }
    if(randInt(1,15) == 1) {
        int j = randInt(0,256);
        double z = (randInt(5,50))/100.0;
        result.push_back(new Star(VIEW_WIDTH-1,j,this,z));
    }
    if(onScreen < min(maxOnScreen, remainingShips)){
        //result.push_back(new Smallgon(256, randInt(1,256),this,alienHealthSmallgon,0));
        int s1 = 60; int s2 =20 + getLevel()*5 ; int s3 =5 + getLevel()*10;
        int s = s1+s2+s3;
        int probability = randInt(0,s);
        if(probability <= s1 ){
            result.push_back(new Smallgon(VIEW_WIDTH-1, randInt(0,VIEW_HEIGHT-1),this,alienHealthSmallgon,0));
        }
        else if (probability > s1 && probability <= (s1 + s2)){
            result.push_back(new Smoregon(VIEW_WIDTH-1, randInt(0,VIEW_HEIGHT-1),this,alienHealthSmallgon,0));
        }
        else if(probability > (s2+s1) && probability <= (s1+s1+s3)){
            result.push_back(new Snagglegon(VIEW_WIDTH-1, randInt(0,VIEW_HEIGHT-1),this,alienHealthSnagglegon,0));
        }
        onScreen++;
    }
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    m_ticks++;
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    list<Actor*>::iterator it;
    it = result.begin();
    while(it != result.end()) {
        delete (*it);
        //result.erase(it);
        it++;
    }
    delete player;
    player = nullptr;
    result.clear();
}
