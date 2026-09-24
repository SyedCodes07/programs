#include<iostream>
using namespace std;
inline double  sqr(double x){
    return x*x;
}
double area (int r){
    return 3.14159*r*r;
}
double area (int l,int b){
    return l^b;
}
double area (double a,double b){
    return (0.5)*a*b;
}
int main(){
    cout<<"square of 5="<<sqr(5.21)<<endl;
    cout<<"area of circle="<<area(5)<<endl;
    cout<<"area of rectangle="<<area(3,4)<<endl;
    cout<<"area of triangle="<<area(3.5,5.5)<<endl;
return 0;
}