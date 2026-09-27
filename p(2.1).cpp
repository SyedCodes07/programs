#include<iostream>
using namespace std;
void logMsg(string msg,int level=1){
    const string tag[] = { " ","INFO","WARN","ERROR"};
cout<<"["<<tag[level]<<"]"<<endl;

}
double interest (double principal,double years,double rate = 7.5){
    return principal*rate*years/100.0;
}
int main(double principal ,double years){
    cout<<"give principal amount:"<<endl;
    cin>>principal;
    cout<<"give number of years"<<endl;
    cin>>years;
    cout<<"Interest:"<<interest(principal,years)<<endl;
    return 0;
}
