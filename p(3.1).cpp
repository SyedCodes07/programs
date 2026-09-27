#include<iostream>
using namespace std;
class BankAcc{
    private:
    string owner;
    double balance;
    public:
    void open(const string &ownername,double initial){
        owner=ownername;
        balance = (initial > 0) ? initial : 0;
    }
    void deposit(double amount){
        if(amount>0){
            balance+=amount;
        }
    
}

bool withdraw(double amount){
    if(amount>0 && amount<=balance){
        balance-=amount;
        return true;
    }
    return false;
}
double getBalance() const{
    return balance;
}
string getOwner() const{
    return owner;
}

};
int main(){
    BankAcc a;
a.open("John Doe",1000);
a.deposit(500);
if(!a.withdraw(2000)){
cout<<"Insufficient funds"<<endl;

}
a.withdraw(300);
cout<<"Owner: "<<a.getOwner()<<"Balance :" << a.getBalance()<<endl;
return 0;
}
