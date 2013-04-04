//
// ECE3090 Program 1 - Complex Number Class implementation
// Mac Clayton
// complex.cc

#include <iomanip>
#include <iostream>
#include <string>
#include <math.h>
#include "complex.h"

using namespace std;

//Complex default constructor:
Complex::Complex() {
    real = 0;
    imag = 0;
    NaN = false;
}

// Alternate constructor with two doubles:
Complex::Complex(const double& r, const double& i) {
    real = r;
    imag = i;
    NaN = false;
}

// Alternate constructor with one double:
Complex::Complex(const double& r) {
    real = r;
    imag = 0;
    NaN = false;
}

//Implement member functions:
//Magnitude Calctulator:
double Complex::magCalc() const {
    double mag = sqrt( pow(real, 2) + pow(imag, 2)); //uses the math.h library to take the square root of the sum of the squares of the real and imaginary parts.
    return mag;
}

//Angle Calculator:
double Complex::angleCalc() const {
    double angle = atan2(imag, real); //arctan(y/x) for the angle  
    angle = angle * 180.0 / M_PI;
    return angle;
}

Complex Complex::conjCreate() const {
    Complex A;
    A.real = real;
    A.imag = (-1) * imag;
    return A;
}

//Print Member function:
void Complex::Print() const {
    if (NaN == false) {
        if (imag == 0) {
            cout << " = " << real << endl;
        }else {
            cout << " = (" << real << "," << imag << ")" << endl;
        }
    }else {
        cout << " = NaN" << endl;
    }
}

//Implement operator overloads:

ostream& operator << (ostream &os, const Complex& c)
{ // Should also check NaN and print "NaN" if so.
    os << "(" << scientific << setprecision(6)
    << c.real << "," << c.imag << ")";
    return os;
}

Complex Complex::operator+(const Complex& rhs) {
    Complex rTemp;
    rTemp.NaN = NaN || rhs.NaN;
    rTemp.real = real + rhs.real;
    rTemp.imag = imag + rhs.imag;
    return rTemp;
}

Complex Complex::operator-(const Complex& rhs) {
    Complex rTemp;
    rTemp.NaN = NaN || rhs.NaN;
    rTemp.real = real - rhs.real;
    rTemp.imag = imag - rhs.imag;
    return rTemp;
}

Complex Complex::operator*(const Complex& rhs) {
    Complex rTemp;
    rTemp.NaN = NaN || rhs.NaN;
    rTemp.real = real * (rhs.real) - (imag * rhs.imag);
    rTemp.imag = (imag * rhs.real) + (real * rhs.imag);
    return rTemp;
}

Complex Complex::operator/(const Complex& rhs) {
    Complex B = rhs;
    Complex A;
    Complex t1;
    A.real = real;
    A.imag = imag;
    A.NaN = NaN || rhs.NaN;
    double temp = B.magCalc();
    if (temp == 0) {
        A.NaN = true;
    }else {
        Complex C = A * B.conjCreate();
        t1 = B * B;
        double m = t1.magCalc();
        A.real = C.real / m;
        A.imag = C.imag / m;
    }
    return A;
}

