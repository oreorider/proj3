#include<iostream>
#include<string>
#include<vector>
using namespace std;

class ComplexNumber{
public:
    ComplexNumber(){};
    ComplexNumber(double real_, double imag_): real(real_), imag(imag_){};
    friend ostream& operator <<(ostream& outStream, const ComplexNumber& c){
        outStream << c.real << " + " << c.imag << "j";
		return outStream;
    }
    const friend ComplexNumber operator+ (const ComplexNumber& c1, const ComplexNumber& c2){
        return ComplexNumber(c1.real+c2.real, c1.imag+c2.imag);
    }


private:
    double real, imag;
};

template <class T1, class T2>
class vector2 {
public:
    vector2(): T1(0), T2(0){}
    vector2(const T1& a, const T2& b): elem1(a), elem2(b){}

    vector2<T1, T2>& operator+(const vector<T1, T2>& v1){
        return vector2<T1, T2>(elem1+v1.elem1, elem2+v1.elem2);
    }

    friend ostream& operator<<(ostream& outputStream, const vector2<T1, T2> v){
        outputStream<<v.elem1<<", "<<v.elem2;
        return outputStream;
    }
    /*
    vector<T1, T2> operator+(const vector<T1, T2> v) const{
        return vector2(elem1+v.elem1, elem2+v.elem2);
    }*/

private:
	T1 elem1;
    T2 elem2;
};
/*
template<class T1, class T2>
vector2<T1, T2> operator+(const vector<T1, T2>& v1, const vector<T1, T2>& v2){
    return vector2<T1, T2>(v1.elem1+v2.elem1, v1.elem2+v2.elem2);
}*/


/*
template<class T1, class T2>
vector2<T1, T2> vector<T1, T2>::operator+(const vector<T1, T2>v1, const vector<T1, T2>v2){
    return vector2(v1.getFirst()+v2.getFirst(), v1.getSecond()+v2.getSecond());
}*/


int main(){
    ComplexNumber c1(0.5, 0.4), c2(2, 1);
    vector2<ComplexNumber, ComplexNumber> vec_c(c1, c2);
    vector2<string, string> vec_cc("A", "B");
    vector2<int, int> vec_int(2, 4);
    cout<<vec_int+vec_int<<endl;
    //cout<<vec_c;
    
    //cout << vec_c + vec_c << endl;
    //cout << vec_cc + vec_cc << endl;
    return 0;
}
