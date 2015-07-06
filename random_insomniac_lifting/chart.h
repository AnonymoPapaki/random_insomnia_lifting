#include <iostream>

using namespace std;

class ship;

class chart{

bool isPort;
int weather;
int treasure;
ship* shipPtr;

public:
    chart(){isPort=false; weather=0; treasure=0; shipPtr=NULL;}
    
    bool getPort(){return isPort;}
    int getWeather(){return weather;}
    int getTreasure(){return treasure;}
    ship* getShip(){return shipPtr;}

    void setPort(bool port){isPort=port;}
    void setWeather(int weath){weather=weath;}
    void setTreasure(int treas){treasure=treas;}
    void setShip(ship* shp){shipPtr=shp;}
};
