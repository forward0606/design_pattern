#include<iostream>
#include<vector>
using namespace std;

class QuackBehavior{
public:
    void virtual quack()=0;
};

class Quack: public QuackBehavior{
    void quack(){
        cout<<"quack quack!"<<endl;
    }
};
class Squeak: public QuackBehavior{
    void quack(){
        cout<<"squeak squeak!"<<endl;
    }
};

class MuteQuack: public QuackBehavior{
    void quack(){
        cout<<"<<slience>>"<<endl;
    }
};

class RobotQuack:public QuackBehavior{
    void quack(){
        cout<<"bibo bibo"<<endl;
    }
};

class FlyBehavior{
public:
    void virtual fly()=0;
};

class Fly: public FlyBehavior{
    void fly(){
        cout<<"I can fly!"<<endl;
    }
};

class NoFly: public FlyBehavior{
    void fly(){
        cout<<"I can't fly QwQ"<<endl;
    }
};

class RocketFly: public FlyBehavior{
    void fly(){
        cout<<"I can fly with rocket!!!"<<endl;
    }
};


class Duck{
    QuackBehavior *qb;
    FlyBehavior *fb;
public:
    Duck(QuackBehavior *_qb, FlyBehavior *_fb):qb(_qb), fb(_fb){};
    ~Duck(){
        delete qb;
        delete fb;
    }
    void virtual display()=0;
    void performFly(){
        fb->fly();
    }
    void performQuack(){
        qb->quack();
    }
    void setQuack(QuackBehavior *newqb){
        delete qb;
        qb = newqb; // cause memory leak ?!
    }
    void setFly(FlyBehavior *newfb){
        delete fb;
        fb = newfb; // cause memory leak ?!
    }
};

class MallarDuck: public Duck{
public:
    MallarDuck():Duck(new Quack, new Fly){}
    void display(){
        cout<<"I am a mallar duck!"<<endl;
    }
};

class RedHeadDuck: public Duck{
public:
    RedHeadDuck():Duck(new Quack, new Fly){}
    void display(){
        cout<<"I am a red head duck!"<<endl;
    }
};

class RubberDuck: public Duck{
public:
    RubberDuck():Duck(new Squeak, new NoFly){};
    void display(){
        cout<<"I am a rubber duck!"<<endl;
    }
};

class WoodenDuck: public Duck{
public:
    WoodenDuck():Duck(new MuteQuack, new NoFly){};
    void display(){
        cout<<"I am a wooden duck!"<<endl;
    }
};

class RobotDuck: public Duck{
public:
    RobotDuck():Duck(new RobotQuack, new NoFly){};
    void display(){
        cout<<"I am a robot duck!"<<endl;
    }
};

int main(){
    vector<Duck*> v;
    v.emplace_back(new MallarDuck);
    v.emplace_back(new RedHeadDuck);
    v.emplace_back(new RubberDuck);
    v.emplace_back(new WoodenDuck);
    v.emplace_back(new RobotDuck);
    
    for(auto p:v){
        p->display();
        p->performQuack();
        p->performFly();
    }
    
    // update the fly method in execution time
    v.back()->setFly(new RocketFly);
    
    for(auto p:v){
        p->display();
        p->performQuack();
        p->performFly();
    }

    for(auto p:v){
        delete p;
    }
    return 0;
}