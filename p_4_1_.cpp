#include<iostream>
using namespace std;
class Tracer
{int id;
public:
    Tracer(int i): id(i){
        cout<<"construct #"<<id<<endl;
    }
    ~Tracer(){
        cout<<"Destruct#"<<id<<endl;
    }
};
int main(){
    cout <<"enter block\n";
    {
        Tracer a(1),b(2);
        cout<<"--Working--\n";
    }
    cout<<"left block\n";
    return 0;
}
