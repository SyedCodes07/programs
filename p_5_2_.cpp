#include<iostream>
using namespace std;
class Distance{
    int feet,inch;
    public:
    Distance(int f=0,int i=0):feet(f),inch(i){}
    friend Distance add(const Distance &a,const Distance &b);
    void show() const{
        cout<<feet<<"ft "<<inch<<"in\n";
    }
};
Distance add(const Distance &a,const Distance &b){
    int totalInch=(a.feet+b.feet)*12+a.inch+b.inch;
    return Distance(totalInch/12,totalInch%12);
}
int main(){
    Distance a(5,8),b(3,7);
    Distance c=add(a,b);
    c.show();
    return 0;}