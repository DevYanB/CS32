#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;
using namespace std;


class Actor: public GraphObject
{
public:
    Actor(int ID, double x, double y, StudentWorld* students, int dir, double size, int depth)
    :GraphObject(ID, x, y, dir, size, depth), s(students), isAlive(true) {};
    //~Actor();
    virtual void doSomething() = 0;
    virtual void setAliveState(bool result) { isAlive = result; }
    virtual bool alive() { return isAlive; }
    virtual StudentWorld* instanceSW(){ return s;}
    double euclidean_dist(double x1, double y1, double x2, double y2){
        double x = x1 - x2; //calculating number to square in next step
        double y = y1 - y2;
        double dist;
        
        dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
        dist = sqrt(dist);
        
        return dist;
    }
    virtual void torpedoDamage() {};
    virtual void sufferDamage(){};
    virtual bool isDamageable(){return false;}
private:
    bool isAlive;
    StudentWorld* s;
};

class DamageableObj: public Actor
{
public:
    DamageableObj(int ID, double x, double y, StudentWorld* s, int dir, double size, int depth,
                  int hp, int cp) : Actor(ID, x, y, s, dir, size, depth), hitPoints(hp), cEnergyPoints(cp) {};
    virtual int getHpoints() { return hitPoints;}
    virtual void setHpoints(int hpoints) { hitPoints = hpoints;}
    virtual int getEpoints() { return cEnergyPoints;}
    virtual void setEpoints(int epoints) { cEnergyPoints = epoints;}
    virtual bool isDamageable(){return true;}
    virtual void sufferDamage(){hitPoints = hitPoints - 2;}
    virtual void torpedoDamage() {hitPoints = hitPoints - 8; }
    //virtual void doSomething() = 0;
private:
    int hitPoints;
    int cEnergyPoints;
};

class Alien: public DamageableObj {
public:
    Alien(int ID, double x, double y, StudentWorld* s, int h, int p, int dir = 0, double size = 1.5, int depth = 1)
    : DamageableObj(ID, x, y, s, dir, size, depth, h, p), travelSpeed(2.0), m_fPlan(0) {};
    virtual void setTravelSpeed(double s) { travelSpeed = s;}
    virtual double getTravelSpeed() { return travelSpeed;}
    virtual void setFlightPlan(int plan) { m_fPlan = plan;}
    virtual int flightPlan() { return m_fPlan; }
    virtual void setTravelDirec(string s) { travelDirec = s;}
    virtual string travelDirection() { return travelDirec;}
    //virtual void doSomething() = 0;
private:
    double travelSpeed;
    int m_fPlan;
    string travelDirec;
    
};

class Explosion: public Actor {
public:
    Explosion(double x, double y,StudentWorld* s, int ticker, int dir = 0, double size = 1, int depth = 0)
    : Actor(IID_EXPLOSION, x, y, s, dir, size, depth) {
        ticks = ticker;
    };
    virtual void doSomething();
private:
    int ticks;
};

class Goodie: public Actor {
public:
    Goodie(int ID, double x, double y, StudentWorld* s, int dir = 0, double size = 0.5, int depth = 1)
    :Actor(ID, x, y, s, dir, size, depth) {};
    virtual void doSomething() = 0;
};

class ExtraLifeGoodie: public Goodie {
public:
    ExtraLifeGoodie(double x, double y, StudentWorld* s)
    : Goodie(IID_LIFE_GOODIE, x, y, s) {};
    virtual void doSomething();
};

class RepairGoodie: public Goodie {
public:
    RepairGoodie(double x, double y, StudentWorld* s)
    :Goodie(IID_REPAIR_GOODIE, x, y, s) {};
    virtual void doSomething();
};

class TorpedoGoodie: public Goodie {
public:
    TorpedoGoodie(double x, double y, StudentWorld* s)
    : Goodie(IID_TORPEDO_GOODIE, x, y, s) {};
    virtual void doSomething();
};

class Smallgon: public Alien {
public:
    Smallgon(double x, double y, StudentWorld* s, int h, int p);
    virtual void doSomething();
};

class Smoregon: public Alien {
public:
    Smoregon(double x, double y, StudentWorld* s, int h , int p);
    virtual void doSomething();
};

class Snagglegon: public Alien {
public:
    Snagglegon(double x, double y, StudentWorld* s, int h, int p);
    virtual void doSomething();
};

class Projectile: public Actor {
public:
    Projectile(int ID, double x, double y, StudentWorld* s, int dir = 0, double size = 0.5, int depth = 1)
    :Actor(ID, x, y, s, dir, size, depth) {};
};

class Cabbage: public Projectile {
public:
    Cabbage(double x, double y, StudentWorld* s)
    : Projectile(IID_CABBAGE, x, y, s) {};
    virtual void doSomething();
};

class Turnip: public Projectile {
public:
    Turnip(double x, double y, StudentWorld* s)
    :Projectile(IID_TURNIP, x, y, s) {};
    virtual void doSomething();
};

class Torpedo: public Projectile {
public:
    Torpedo(double x, double y, StudentWorld* s, int dir = 0)
    : Projectile(IID_TORPEDO, x, y, s, dir) {};
};

class PlayerLaunchedTorpedo: public Torpedo {
public:
    PlayerLaunchedTorpedo(double x, double y, StudentWorld* s, int dir = 0)
    : Torpedo(x, y, s, dir) {};
    virtual void doSomething();
};

class AlienLaunchedTorpedo: public Torpedo {
public:
    AlienLaunchedTorpedo(double x, double y, StudentWorld* s, int dir = 180)
    : Torpedo(x,y,s, dir) {};
    virtual void doSomething();
};

class NachenBlaster: public DamageableObj
{
public:
    NachenBlaster(StudentWorld*s, double x = 0, double y = 128, double size = 1, int dir = 0, int depth = 0)
    :DamageableObj(IID_NACHENBLASTER, x, y, s, dir, size, depth,50,30), torpedo_count(0){
        // setEpoints(30);
        //setHpoints(50);
    };
    virtual void doSomething();
    int getTorpedoCount() { return torpedo_count; }
    void addTorpedoCount() { torpedo_count+=5; }
private:
    int torpedo_count;
};

/* It must have a limited version of a doSomething() method that lets the
 user pick a direction by hitting a directional key. If the NachenBlaster
 hits a directional key during the current tick and this will not cause the
 NachenBlaster to move off of the space field, it updates the
 NachenBlaster’s location appropriately. All this doSomething()
 method has to do is properly adjust the NachenBlaster’s x,y
 coordinates, and our graphics system will automatically animate its
 movement it around the space field!*/


class Star: public Actor
{
public:
    Star(double x, double y, StudentWorld*s, double size, int dir = 0, int depth = 3)
    :Actor(IID_STAR, x, y, s, dir, size, depth) {};
    //~Star();
    virtual void doSomething();
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
