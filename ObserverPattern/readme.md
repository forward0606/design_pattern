# Observer pattern

適用時機：有多個物件(observer)會根據一個物件(subject)的 status 做反應，且不知道 subject 何時會改變，且 observer 隨時可以決定要不要繼續觀察 subject 的狀態

當 subject 改變時，通知 observer
- 在 subject 中維護一個 observer list
- observer 皆維護一個 update() 介面，以讓 subject 通知它
- 對於 subject 而言，他不知道 observer 的實作細節，但她知道自己可以透過 update 通知 observer 自己有修改
- observer 也不用知道 subject 何時會做修改，但她知道 subject 有修改則一定會通知他


## example
氣象觀測系統
- weatherData(**subject**): 產生氣象資料
- CurrentConditionDisplay, StaticDisplay(**observer**): 根據 weatherData display 資訊給 user


## debug
以下寫法是錯的
```cpp
class StaticDisplay: public Observer{
    WeatherData weatherData;
    double minTemperature, maxTemperature;
public:
    StaticDisplay(WeatherData &wd){
        weatherData = wd;
        weatherData.registObserver(this);
        ...
    }
    ~StaticDisplay(){
        ...
    }
    void update(){
        ...
    }
};
```

weatherData 的型態必須是 pointer 否則在 weatherData = wd 時會 call copy constructor，導致產生兩個不同的 subject