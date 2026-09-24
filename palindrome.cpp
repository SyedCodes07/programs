#include<iostream>
using namespace std;
string s;
int main(){
cout<<"enter string"<<endl;
cin>>s;
bool pal = true;
for (size_t i = 0,j=s.size(); i <s.size()-1,j>0; ++i,j--)
{if (s[i] != s[j])
{
    pal = false;
    break;
}
}
cout<<s<<(pal ? "Is":"Is not ")<<"palindrome"<<endl;
return 0;


}