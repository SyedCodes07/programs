#include<iostream>
using namespace std;
class Car{
    int speed=0;
    friend class DashBoard;
    public:
    void accelerate(){
        speed+=10;
    }
};
class DashBoard{
    public:
    void display(const Car &c){
        cout<<"speed:"<<c.speed<<"km/hr"<<endl;
    }};
int main(){
    Car c;
    
   c.accelerate();
    c.accelerate();
     DashBoard().display(c);
     return 0;
    }