#include<iostream>
using namespace std;
class Widget{
    int id;
    static int count;
    public:
    Widget(){ id=++count; cout<<"created w"<<id<<endl; }
~Widget(){--count; cout<<"destroyed w"<<id<<endl; }
static int alive(){ return count; }    
};
int Widget::count=0;
int main(){
    cout<<"alive"<<Widget::alive()<<endl;
{Widget c;cout<<"alive"<<Widget::alive()<<endl;}
cout<<"alive"<<Widget::alive()<<endl;
    return 0;
}