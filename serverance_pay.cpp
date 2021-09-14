#include <iostream>
using namespace std;

int main(){
    const int avgWage=1800000;
    int working_days, amount;

    cout<<"working days : ";
    cin>>working_days;

    amount=avgWage*30*(working_days/365.0);
    cout<<"amount before rounding : "<<amount<<endl;

    if(amount%1000 >= 500){//round up
        amount+=(1000-(amount%1000));
        cout<<"amount rounded up to : "<<amount<<endl;
    }
    else if(amount%1000 < 500){//round down
        amount-=(amount%1000);
        cout<<"amount rounded down to : "<<amount<<endl;
    }

    cout<<"severance pay is : "<<amount<<endl;



}