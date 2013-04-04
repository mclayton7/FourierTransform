// Class for managing the Discrete FFT transformation
// Mac Clayton, 2012
// ECE 3090

#include <iostream>
#include <vector>

class Complex;
    
class FFT {
public:
    FFT(const std::vector<Complex>&);   // Construct from vector of data
    void DumpH(std::ostream&);          // Debug..dump H array to an output stream
    void Dumph(std::ostream&);          // Debug..dump h array to an output stream
    void DumpW(std::ostream&);          // Debug..dump W arrary to an output stream
    void LoadWeights();                 // Calculate the W values
    void Transform();                   // Do the transform efficiently
    void TransformSimple();             // Transform with inefficient nested loops
    void BitReverseElements();          // Perform the Cooley-Tukey bit reversal
    
private:
    unsigned ReverseBits(unsigned);     // Reverse the bits in an integer
    
public:
  // Read data file
    static bool ReadInputs(char*, std::vector<Complex>&);
    
private:
    Complex* h;     // Points to the data elements to convert
    Complex* H;     // Points to transformed array (simple method)
    Complex* W;     // Weights (Calculated once)
    unsigned N;     // Size of array
};
