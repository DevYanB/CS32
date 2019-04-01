
#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    //Swap Check
    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  && m2.size() == 1  &&  m2.contains("Fred"));

    Map m;  // maps strings to doubles
    assert(m.empty());
    ValueType v = -1234.5;
    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
    m.insert("xyz", 9876.5);
    assert(m.size() == 1);
    KeyType k = "hello";
    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);

    //General Insert Check
    Map m3;
    m3.insert("A", 10);
    m3.insert("B", 44);
    m3.insert("C", 10);
    string all;
    double total = 0;
    for (int n = 0; n < m3.size(); n++)
    {
        string k;
        double v;
        m3.get(n, k, v);
        all += k;
        total += v;
    }
    cout << all << total << endl;

    //Repetitivity Check for Insert
    Map gpas;
    gpas.insert("Fred", 2.956);
    gpas.insert("Ethel", 3.538);
    double y;
    string k1;
    assert(gpas.get(1,k1,y)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
    string k2;
    assert(gpas.get(1,k2,y)  &&  k2 == k1);

    //Empty String Test for Insert
    Map gps;
    gps.insert("Fred", 2.956);
    assert(!gps.contains(""));
    gps.insert("Ethel", 3.538);
    gps.insert("", 4.000);
    gps.insert("Lucy", 2.956);
    assert(gps.contains(""));
    gps.erase("Fred");
    assert(gps.size() == 3  &&  gps.contains("Lucy")  &&  gps.contains("Ethel")  &&
           gps.contains(""));

    //Update check
    Map tester;
    tester.insert("Doggo" , 45.5);
    assert(tester.contains("Doggo"));
    tester.update("Doggo" , 10);
    double x;
    assert(tester.get("Doggo" , x) && x == 10);

    //Subtract Check
    Map tester1;
    tester1.insert("Fred", 2.956);
    tester1.insert("Ethel", 3.538);
    tester1.insert("Lucy", 2.956);
    Map tester2;
    tester2.insert("Ethel", 3.538);
    tester2.insert("Lucy", 2.956);
    tester2.insert("Jacob" , 3.224);
    Map resultant;
    subtract(tester1,tester2,resultant);
    assert(resultant.contains("Fred") && resultant.size() == 1);
    subtract(tester2,tester1,resultant);
    assert(resultant.contains("Jacob") && !resultant.contains("Fred"));

    //Combine Check
    Map tester3;
    tester3.insert("Fred", 2.956);
    tester3.insert("Ethel", 3.538);
    tester3.insert("Lucy", 2.56);
    Map tester4;
    tester4.insert("Lucy", 2.956);
    tester4.insert("Ricky", 4.0);
    Map resulting;
    combine(tester3,tester4,resulting);
    assert(!resulting.contains("Lucy"));
    combine(tester4,tester3,resulting);
    assert(resulting.size() == 3);

    cout << "Passed all tests!" << endl;
}
