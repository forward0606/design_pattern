#include<iostream>
#include<set>
using namespace std;

class Subject;
class Observer{
public:
    virtual void update()=0;
};

class Subject{
    set<Observer *> observers;
public:
    void registObserver(Observer *o){
        observers.insert(o);
    }
    void removeObserver(Observer *o){
        observers.erase(o);
    }
    void notifyObservers(){
        for(Observer *it:observers){
            it->update();
        }
    }
};



class WeatherData:public Subject{
    double temperature;
    double humidity;
    double pressure;
public:
    WeatherData():temperature(25), humidity(65), pressure(30.4){}
    double getTemperature(){
        return temperature;
    }
    double getHumidity(){
        return humidity;
    }
    double getPressure(){
        return pressure;
    }
    void setTemperature(double newTemparature){
        temperature = newTemparature;
        measureUpdate();
    }
    void setHumidity(double newHumidity){
        humidity = newHumidity;
        measureUpdate();
    }
    void setPressure(double newPressure){
        pressure = newPressure;
        measureUpdate();
    }
    void measureUpdate(){
        notifyObservers();
    }
};

class CurrentCondictionDisplay: public Observer{
    WeatherData *weatherdata;
public:
    CurrentCondictionDisplay(WeatherData *wd){
        weatherdata = wd;
        weatherdata->registObserver(this);
    }
    ~CurrentCondictionDisplay(){
        weatherdata->removeObserver(this);
    }
    void update(){
        double temperature = weatherdata->getTemperature();
        double pressure = weatherdata->getPressure();
        double humidity = weatherdata->getHumidity();
        cout<<"Current Weather: "<<temperature<<"/"<<pressure<<"/"<<humidity<<endl;
    }
};

class StaticDisplay: public Observer{
    WeatherData *weatherData;
    double minTemperature, maxTemperature;
public:
    StaticDisplay(WeatherData *wd){
        weatherData = wd;
        weatherData->registObserver(this);
        minTemperature = 25, maxTemperature = 25;
    }
    ~StaticDisplay(){
        weatherData->removeObserver(this);
    }
    void update(){
        double temperature = weatherData->getTemperature();
        minTemperature = min(minTemperature, temperature);
        maxTemperature = max(maxTemperature, temperature);
        cout<<"Static Weather: "<<minTemperature<<"/"<<maxTemperature<<endl;
    }
};

int main(){
    WeatherData weather;
    CurrentCondictionDisplay *c = new CurrentCondictionDisplay(&weather);
    StaticDisplay *s = new StaticDisplay(&weather);
    weather.setTemperature(30);
    weather.setTemperature(10);
    delete s;       // test for remove function
    weather.setPressure(25);
    delete c;
    return 0;
}