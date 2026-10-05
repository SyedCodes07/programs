#include<iostream>
#include<cstring>
using namespace std;
class MyString{
    char *data;
    public:
    MyString(const char *str){
        data = new char[strlen(str)+1];
        strcpy(data,str);
    }
    MyString(const MyString &o){
        data = new char[strlen(o.data)+1];
        strcpy(data,o.data);
    }
    ~MyString(){
        delete [] data;
    }
    void print() const{
        cout<<data<<endl;
    }
};
int main(){
    MyString s1("software");
    MyString s2 = s1;
    s1.print(); 
    s2.print();
    return 0;
}