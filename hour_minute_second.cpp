#include <iostream>
using namespace std;

int main(){
    int input_seconds, num_hours, num_minutes, num_seconds;
    
    cout<<"Total second? : ";
    cin>>input_seconds;

    num_hours=input_seconds/3600;
    num_minutes=(input_seconds-(num_hours*3600))/60;
    num_seconds=(input_seconds-(num_hours*3600)-(num_minutes*60));
    cout<<"Hour : "<<num_hours<<"\tmin : "<<num_minutes<<"\tsec : "<<num_seconds<<endl;
}