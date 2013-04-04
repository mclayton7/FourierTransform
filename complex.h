// Complex Number Class decaration
// Mac Clayton, 2012

#include <iostream>
#include <string>

class Complex {
public:
    
    //Default Constructor
    Complex();
    //Double Constructor
    Complex(const  double& r, const double& i);
    Complex(const double& r);

    //Member functions:
    double magCalc() const;   //Gives the magnitude of the two numbers
    double angleCalc() const; //Gives the angle between the real and imaginary
    void Print() const; //Print the complex number
    Complex conjCreate() const; //Create the complex conjugate
    
    //Plus and minus overload operators:
    Complex operator+(const Complex& rhs);
    Complex operator-(const Complex& rhs);
    
    //Multiplication and division operators:
    Complex operator*(const Complex& rhs);
    Complex operator/(const Complex& rhs);
    
public:
    double real;
    double imag;
    bool NaN;
};

// Overload  << operator
std::ostream& operator << (std::ostream &os, const Complex& c);
