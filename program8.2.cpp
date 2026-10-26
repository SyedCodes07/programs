#include<iostream>
using namespace std;
class Base{
    public:
    void normal(){
        cout<<"Base:normal(early binding)\n";
    }
    virtual void special(){
        cout<<"Base::special\n";
    }
};
class Derived:public Base{
    public:
    void normal(){
        cout<<"Derived::normal\n";
    }
    void special() override{
        cout<<"Derived::special(late binding)\n";
    }
};
int main(){
    Derived d;
    Base* b=&d;
    b->normal();
    b->special();
    return 0;
}