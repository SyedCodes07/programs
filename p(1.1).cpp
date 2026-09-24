#include<iostream>
using namespace std;
void swap_ref(int &a, int &b){
    int t = a;
    a = b;
    b = t;
}
void swap_ptr(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}
int main(){
    int x = 10,y= 20;
    swap_ref(x, y);
    cout <<"After Swap Ref:x="<<x<<"y="<<y<<endl;
    swap_ptr(&x, &y);
    cout<<"after swap ref:x="<<x<<"y="<<y<<endl;
    int alias = x;
    alias = 99;
    cout<<"x via alias="<<x<<endl;
    return 0;
}
