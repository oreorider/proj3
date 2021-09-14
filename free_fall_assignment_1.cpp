#include <iostream>
#include <cmath>
using namespace std;

int main(){
    const double gravity=9.81;
    int initial_height;

    cout<<"your initial altitude (in meters) : ";
    cin>>initial_height;

    double time_to_fall=sqrt((2*initial_height)/gravity);

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout<<"Time (sec) : "<<time_to_fall<<endl;


}