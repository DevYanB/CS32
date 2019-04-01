//
//  Actor.cpp
//  NachenBlaster
//
//  Created by Devyan Biswas on 2/28/18.
//  Copyright © 2018 David Smallberg. All rights reserved.
//

#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
#include <iostream>
class Cabbage;


void Explosion::doSomething() {
    setSize(1.2 * getSize());
    if(instanceSW()->getTicks() - ticks == 4){
        setAliveState(false);
    }
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
void Star::doSomething() {
    if(getX() <= -1)
        setAliveState(false);
    else
        moveTo(getX()-1, getY());
}

Smoregon::Smoregon(double x, double y, StudentWorld* s, int h, int p)
: Alien(IID_SMOREGON, x, y, s, h, p) {
    setHpoints(h);
    setTravelSpeed(2.0);
    setEpoints(0);
}

Smallgon::Smallgon(double x, double y, StudentWorld* s, int h , int p)
: Alien(IID_SMALLGON, x, y, s, h, p){
    setHpoints(h);
    setEpoints(10);
    setTravelSpeed(2.0);
}

Snagglegon::Snagglegon(double x, double y, StudentWorld* s, int h , int p)
: Alien(IID_SNAGGLEGON, x, y, s, h, p) {
    setHpoints(h);
    //setTravelDirec("DL");
    setEpoints(10);
    setTravelSpeed(1.75);
}


//double Actor::euclidean_dist(int x1, int y1, int x2, int y2) {

//}


void Snagglegon::doSomething() {
    string arr[] = {"DL", "UL", "L"};
    if(getX() <= -1){
        setAliveState(false);
    }
    if(!alive())
        return;
    if(getHpoints() <= 0){
        if(randInt(1,6) == 1) {
            ExtraLifeGoodie* exLG = new ExtraLifeGoodie(getX(), getY(), instanceSW());
            instanceSW()->addTo(exLG);
        }
        instanceSW()->setDestroyedAlienCount();
        instanceSW()->increaseScore(1000);
        setAliveState(false);
        return;
    }
    else{
        //Step 3:
        if(euclidean_dist(getX(), getY(), instanceSW()->getPlayer()->getX(), instanceSW()->getPlayer()->getY())
           < .75 * (getRadius() + instanceSW()->getPlayer()->getRadius())) {
            instanceSW()->getPlayer()->setHpoints(instanceSW()->getPlayer()->getHpoints() - 15);
            setAliveState(false);
            if(randInt(1,6) == 1) {
                ExtraLifeGoodie* exLG = new ExtraLifeGoodie(getX(), getY(), instanceSW());
                instanceSW()->addTo(exLG);
            }
            instanceSW()->setDestroyedAlienCount();
            instanceSW()->increaseScore(1000);
            instanceSW()->playSound(SOUND_DEATH);
            //Explosion* explo = new Explosion(getX(), getY(), instanceSW());
        }
        if((flightPlan() == 0) || (getY() >= VIEW_HEIGHT) || (getY() < 0)){
            if(getY() >= VIEW_HEIGHT -1){
                setTravelDirec("DL");
            }
            else if(getY() <= 0){
                setTravelDirec("UL"); }
            else if(flightPlan() == 0){
                string randDirec = arr[randInt(0, 2)];
                setTravelDirec(randDirec);
            }
            setFlightPlan(randInt(1,32));
            
            //random selection of directions
        }
        //Step 5
        if((instanceSW()->getPlayer()->getX() < getX()) &&
           (abs(instanceSW()->getPlayer()->getY() - getY()) <= 4)){
            int x = randInt(1, ((15/(instanceSW()->getLevel()))+10));
            if(x == 1){
                AlienLaunchedTorpedo* alienTorpedo = new AlienLaunchedTorpedo(getX() -14, getY(), instanceSW());
                instanceSW()->addTo(alienTorpedo);
                instanceSW()->playSound(SOUND_TORPEDO);
                return;
            }
        }
        //Step6:
        if( travelDirection() == "DL"){
            moveTo(getX() - getTravelSpeed(), getY() - getTravelSpeed());
            setFlightPlan(flightPlan() -1);
        }
        
        else if( travelDirection() == "UL"){
            moveTo(getX() - getTravelSpeed(), getY() + getTravelSpeed());
            setFlightPlan(flightPlan() -1);
        }
        else if( travelDirection() == "L"){
            moveTo(getX() - getTravelSpeed(), getY());
            setFlightPlan(flightPlan() -1);
        }
    }
}

void Smoregon::doSomething() {
    if(getX() <= -1)
        setAliveState(false);
    if(getHpoints() <= 0){
        if(randInt(1,3) == 1) {
            int x = randInt(1,2);
            if(x == 1){
                RepairGoodie* repG = new RepairGoodie(getX(), getY(), instanceSW());
                instanceSW()->addTo(repG);
            }
            else if(x==2){
                TorpedoGoodie* torpedoG = new TorpedoGoodie(getX(), getY(), instanceSW());
                instanceSW()->addTo(torpedoG);
            }
        }
        instanceSW()->setDestroyedAlienCount();
        instanceSW()->increaseScore(250);
        setAliveState(false);
        return;
    }
    else {
        string arr[] = {"DL", "UL", "L"};
        if(euclidean_dist(getX(), getY(), instanceSW()->getPlayer()->getX(), instanceSW()->getPlayer()->getY())
           < .75 * (getRadius() + instanceSW()->getPlayer()->getRadius())) {
            instanceSW()->getPlayer()->setHpoints(instanceSW()->getPlayer()->getHpoints() - 5);
            setAliveState(false);
            if(randInt(1,3) == 1) {
                int x = randInt(1,2);
                if(x == 1){
                    RepairGoodie* repG = new RepairGoodie(getX(), getY(), instanceSW());
                    instanceSW()->addTo(repG);
                }
                else if(x==2){
                    TorpedoGoodie* torpedoG = new TorpedoGoodie(getX(), getY(), instanceSW());
                    instanceSW()->addTo(torpedoG);
                }
            }
            instanceSW()->setDestroyedAlienCount();
            instanceSW()->increaseScore(250);
            instanceSW()->playSound(SOUND_DEATH);
            //Explosion* explo = new Explosion(getX(), getY(), instanceSW());
            //goodie
        }
        if((flightPlan() == 0) || (getY() >= VIEW_HEIGHT) || (getY() < 0)){
            if(getY() >= VIEW_HEIGHT -1){
                setTravelDirec("DL");
            }
            else if(getY() <= 0)
                setTravelDirec("UL");
            else if(flightPlan() == 0){
                string randDirec = arr[randInt(0, 2)];
                setTravelDirec(randDirec);
            }
            setFlightPlan(randInt(1,32)); //random selection of directions
        }
        //Step 5
        if((instanceSW()->getPlayer()->getX() < getX()) &&
           (abs(instanceSW()->getPlayer()->getY() - getY()) <= 4)) {
            int x = randInt(1, ((20/(instanceSW()->getLevel()))+5));
            if(x == 1){
                Turnip* turn = new Turnip(getX() -14, getY(), instanceSW());
                instanceSW()->addTo(turn);
                instanceSW()->playSound(SOUND_ALIEN_SHOOT);
                return;
            }
            //int y = randInt(1, ((20/(instanceSW()->getLevel()))+5));
            if(x == 2) {
                setTravelDirec("L");
                setFlightPlan(VIEW_WIDTH);
                setTravelSpeed(getTravelSpeed() + 5);
            }
        }
        if( travelDirection() == "DL"){
            moveTo(getX() - getTravelSpeed(), getY() - getTravelSpeed());
            setFlightPlan(flightPlan() -1);
        }
        else if( travelDirection() == "UL"){
            moveTo(getX() - getTravelSpeed(), getY() + getTravelSpeed());
            setFlightPlan(flightPlan() -1);
            
        }
        else if( travelDirection() == "L"){
            moveTo(getX() - getTravelSpeed(), getY());
            setFlightPlan(flightPlan() -1);
        }
        
    }
}
void Smallgon::doSomething() {
    string arr[] = {"DL", "UL", "L"};
    if(getX() <= -1){
        setAliveState(false);
        return;
    }
    if(getHpoints() <= 0){
        instanceSW()->setDestroyedAlienCount();
        instanceSW()->increaseScore(250);
        setAliveState(false);
        return;
    }
    //cout << getHpoints() << endl;
    if(!alive())
        return;
    else{
        //Step 3:
        if(euclidean_dist(getX(), getY(), instanceSW()->getPlayer()->getX(), instanceSW()->getPlayer()->getY())
           < .75 * (getRadius() + instanceSW()->getPlayer()->getRadius())) {
            instanceSW()->getPlayer()->setHpoints(instanceSW()->getPlayer()->getHpoints() -5);
            setAliveState(false);
            instanceSW()->setDestroyedAlienCount();
            instanceSW()->increaseScore(250);
            instanceSW()->playSound(SOUND_DEATH);
            //Explosion* explo = new Explosion(getX(), getY(), instanceSW());
        }
        if((flightPlan() == 0) || (getY() >= VIEW_HEIGHT) || (getY() < 0)){
            if(getY() >= VIEW_HEIGHT -1){
                setTravelDirec("DL");
            }
            else if(getY() <= 0){
                setTravelDirec("UL"); }
            else if(flightPlan() == 0){
                string randDirec = arr[randInt(0, 2)];
                setTravelDirec(randDirec);
            }
            setFlightPlan(randInt(1,32));
            
            //random selection of directions
        }
        //Step 5
        if((instanceSW()->getPlayer()->getX() < getX()) &&
           (abs(instanceSW()->getPlayer()->getY() - getY()) <= 4)){
            int x = randInt(1, ((20/(instanceSW()->getLevel()))+5));
            if(x == 1){
                Turnip* turn = new Turnip(getX() -14, getY(), instanceSW());
                instanceSW()->addTo(turn);
                instanceSW()->playSound(SOUND_ALIEN_SHOOT);
                return;
            }
        }
        //Step6:
        if( travelDirection() == "DL"){
            moveTo(getX() - getTravelSpeed(), getY() - getTravelSpeed());
            setFlightPlan(flightPlan() -1);
        }
        
        else if( travelDirection() == "UL"){
            moveTo(getX() - getTravelSpeed(), getY() + getTravelSpeed());
            setFlightPlan(flightPlan() -1);
        }
        else if( travelDirection() == "L"){
            moveTo(getX() - getTravelSpeed(), getY());
            setFlightPlan(flightPlan() -1);
        }
    }
}

void NachenBlaster::doSomething() {
    if(alive()){
        int ch;
        if(getCPoints() < 30){
            setEpoints(getCPoints() + 1);
        }
        if(getHpoints() <= 0)
            setAliveState(false);
        if(((instanceSW()->getKey(ch)))) {
            switch(ch){
                case KEY_PRESS_SPACE:
                    if(getCPoints() >= 5){
                        Cabbage* cab = new Cabbage(getX() + 12, getY(), instanceSW());
                        instanceSW()->addTo(cab);
                        setEpoints(getCPoints() -5);
                        instanceSW()->playSound(SOUND_PLAYER_SHOOT);//set sound
                    }
                    break;
                case KEY_PRESS_UP:
                    if((getY() +6) < VIEW_HEIGHT)
                        moveTo(getX(), getY()+6);
                    break;
                case KEY_PRESS_TAB:
                    if(torpedo_count != 0) {
                        PlayerLaunchedTorpedo* torpedo = new PlayerLaunchedTorpedo(getX()+12, getY(), instanceSW());
                        instanceSW()->addTo(torpedo);
                        torpedo_count--;
                        instanceSW()->playSound(SOUND_TORPEDO);
                    }
                    break;
                case KEY_PRESS_DOWN:
                    if(getY() -6 >= 0)
                        moveTo(getX(), getY() -6);
                    break;
                case KEY_PRESS_LEFT:
                    if(getX()-6 >= 0)
                        moveTo(getX()-6, getY());
                    break;
                case KEY_PRESS_RIGHT:
                    if(getX()+6 < VIEW_WIDTH)
                        moveTo(getX()+6, getY());
                    break;
                default: ;
            }
        }
    }
    return;
    
}
//FIRST : do the euclidean with nachenbalster
void Turnip::doSomething() {
    if(getX() < 0)
        setAliveState(false);
    if(!alive())
        return;
    else {
        if(euclidean_dist(getX(), getY(), instanceSW()->getPlayer()->getX(), instanceSW()->getPlayer()->getY())
           < .75 * (getRadius() + instanceSW()->getPlayer()->getRadius())) {
            instanceSW()->getPlayer()->setHpoints(instanceSW()->getPlayer()->getHpoints() - 2);
            instanceSW()->playSound(SOUND_BLAST);
            setAliveState(false);}
        //Explosion* explo = new Explosion(getX(), getY(), instanceSW());
        //delete explo;
        //continue; }
        moveTo(getX() - 6, getY());
        setDirection(getDirection() - 20);
    }
}

void PlayerLaunchedTorpedo::doSomething() {
    if((getX() < 0) || (getY() >= VIEW_WIDTH))
        setAliveState(false);
    if(!alive())
        return;
    else {
        moveTo(getX() +8, getY());
        instanceSW()->collTorpedo(this);//get snagglegon ship and check if collide
    }
}

void AlienLaunchedTorpedo::doSomething() {
    if((getX() < 0) || (getY() >= VIEW_WIDTH))
        setAliveState(false);
    if(!alive())
        return;
    else {
        moveTo(getX() -8, getY());
        if(euclidean_dist(getX(), getY(), instanceSW()->getPlayer()->getX(), instanceSW()->getPlayer()->getY())
           < .75 * (getRadius() + instanceSW()->getPlayer()->getRadius()))
        {
            instanceSW()->getPlayer()->setHpoints(instanceSW()->getPlayer()->getHpoints() - 8);
            instanceSW()->playSound(SOUND_BLAST);
            setAliveState(false);
            return;
        }
        //get snagglegon ship and check if collide
        
    }
}
//SECOND : Do the goodies
void ExtraLifeGoodie::doSomething() {
    if((getX() >= VIEW_WIDTH) || (getX() < 0))
        setAliveState(false);
    if(!alive())
        return;
    if(euclidean_dist(getX(), getY(), instanceSW()->getPlayer()->getX(), instanceSW()->getPlayer()->getY())
       < .75 * (getRadius() + instanceSW()->getPlayer()->getRadius())) {
        instanceSW()->increaseScore(100);
        setAliveState(false);
        instanceSW()->playSound(SOUND_GOODIE);
        instanceSW()->incLives();
        return; }
    moveTo(getX() - 0.75, getY() - 0.75);
}

void RepairGoodie::doSomething() {
    if((getX() >= VIEW_WIDTH) || (getX() < 0))
        setAliveState(false);
    if(!alive())
        return;
    if(euclidean_dist(getX(), getY(), instanceSW()->getPlayer()->getX(), instanceSW()->getPlayer()->getY())
       < .75 * (getRadius() + instanceSW()->getPlayer()->getRadius()))
    {
        instanceSW()->increaseScore(100);
        setAliveState(false);
        instanceSW()->playSound(SOUND_GOODIE);
        if((instanceSW()->getPlayer()->getHpoints()+ 10) <= 50)
            instanceSW()->getPlayer()->setHpoints(instanceSW()->getPlayer()->getHpoints()+10);
        return; }
    moveTo(getX() - 0.75, getY() - 0.75);
    //while loop
    
}

void TorpedoGoodie::doSomething() {
    if((getX() >= VIEW_WIDTH) || (getX() < 0))
        setAliveState(false);
    if(!alive())
        return;
    if(euclidean_dist(getX(), getY(), instanceSW()->getPlayer()->getX(), instanceSW()->getPlayer()->getY())
       < .75 * (getRadius() + instanceSW()->getPlayer()->getRadius()))
    {
        instanceSW()->increaseScore(100);
        instanceSW()->getPlayer()->addTorpedoCount();
        setAliveState(false);
        instanceSW()->playSound(SOUND_GOODIE);
        //flatulance torpedos
        return; }
    moveTo(getX() - 0.75, getY() - 0.75);
    
}
//Cabbage needs to move continously
void Cabbage::doSomething() {
    instanceSW()->collCab(this);
    moveTo(getX() + 8, getY());
    setDirection(getDirection() + 20);
    if(getX() >= VIEW_WIDTH)
        setAliveState(false);
    if(!alive())
        return;
}
