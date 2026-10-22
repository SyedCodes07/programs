#include<iostream>
using namespace std;
class Stream{
public:
    Stream(){cout<<"Stream ctor\n";}
    void open(){cout<<"Stream open\n";}
};
class inStream:virtual public Stream{};
class outStream:virtual public Stream{};
class IOStream:public inStream,public outStream{};
int main(){
IOStream io;
io.open();
return 0;
}