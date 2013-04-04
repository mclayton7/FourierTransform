// Class for managing the Discrete FFT transformation
// Mac Clayton, 2012
// ECE3090 Lab 2
// Platform Used: Linux/Unix (OSX 10.8.3)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "complex.h"
#include "fft.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Constructors
FFT::FFT(const vector<Complex>& inputs) 
{ 
    // Construct an FFT object with data from the inputs vector
    N = inputs.size();      // N is the number of input elements
    h = new Complex[N];     // Input time domain array
    H = new Complex[N];     // Fourier transform of h
    W = new Complex[N/2];   // Weights (see writeup)
    for (unsigned i = 0;i <= N; i++) 
    {
        h[i] = inputs[i];   // Copy inputs into h[]
    }
}

void FFT::Dumph(ostream& os)
{   
    // Iterates through vector h and sends each element (and endl) to ostream
    for (unsigned i = 0; i < N; i++) 
    {
        if (fabs(h[i].real) < (1e-12)) 
        {
            h[i].real = 0.0;
        }
        else if (fabs(h[i].imag) < (1e-12)) 
        {
            h[i].imag = 0.0;
        }
        os << i << " - " << h[i] << endl;
    }
}

void FFT::DumpH(ostream& os)
{ 
    // Write the H array to the specified file
    for (unsigned i = 0; i < N; i++)
    {
        if (fabs(H[i].real) < (1e-12))
        {
            H[i].real = 0;
        }
        else if (fabs(H[i].imag) < (1e-112))
        {
            H[i].imag = 0;
        }
        os << i << " - " << H[i] << endl;
    }
}

void FFT::DumpW(ostream& os)
{ 
    // Write the W array to the specified fle
    for (unsigned i = 0; i < N/2; i++)
    {
        os << i << " - " << W[i] << endl;
    }
}

void FFT::LoadWeights()
{ 
    // Compute the needed W values
    // Generates weights based on EQ
    for (unsigned i = 0; i < N/2; i++)
    {
        W[i].real = cos(2*M_PI*i/N);
        W[i].imag = -sin(2*M_PI*i/N);
    }
}

void FFT::BitReverseElements()
{ // Shuffle the h elements per the Cooley-Tukey bit-reverse algorithm
    for ( unsigned i = 0; i < N; i++)
    {
        unsigned reverse = ReverseBits(i);
        // Makes sure bits don't get reversed twice
        if (i < reverse)
        {
            Complex temp = h[i];
            h[i] = h[reverse];
            h[reverse] = temp;
        }
    }
}

void FFT::Transform()
{   
    // Danielson/Lanczos approach (efficient)    
    LoadWeights();
    // Bit reverse elements of h for Tukey algorithm;
    BitReverseElements();
    cout << "After bit reverse" << endl;
    Dumph(cout);
    // Temporary variable to allow editing of h array only
    Complex temp;
    // Print the weights
    cout << "Weights are" << endl;
    DumpW(cout);
    // Begin the fast method:
    for( unsigned points = 2; points <= N; points = points * 2)
    {
        // 2 point, 4 point, 8 point, ...
        cout << "After transform length " << points << endl;
        for (unsigned i = 0; i < N/points; i++)
        {
            // traverse each partial FFT grouping
            for(unsigned k = 0; k < (points / 2); k++)
            {
                // Store h[k + points *i] in a temporary variable because it's needed in equation #2
                temp = h[k + points * i];
                // Transform part #1
                h[k + points * i] = h[k + points * i] + W[k * N / points] * h[k + points / 2 + points * i];
				// Transfrom part #2
                h[k + points / 2 + points * i] = temp - W[k * N / points] * h[k + points / 2 + points * i];
            }
        }
        // Print the transformed arrays after each 2,4,8,... transform
        Dumph(cout);
    }

    // Print final transform (stored in h[])
    cout << "Final Transformed Values" << endl;
    Dumph(cout);
}

void FFT::TransformSimple()
{ 
    // Print the inital h[] array
    cout << "Initial Data Points" << endl;
    Dumph(cout);
    // Simple (Slow) FFT Transform:
    for ( unsigned n = 0; n < N; n++)
    {
        for (unsigned k = 0; k < N; k++)
        {
            // Iterates trhough and calculates the W values and the transform
            H[n].real = H[n].real + h[k].real * cos(2*M_PI*k*n/N);
            H[n].imag = H[n].imag - h[k].real * sin(2*M_PI*k*n/N);
        }
    }
    cout << "Final Tranformed Array" << endl;
    DumpH(cout);
}

// Private functions
unsigned FFT::ReverseBits(unsigned v)
{ 
    unsigned n = N; // Size of array (which is even 2^k value)
    unsigned r = 0; // Return value
    for (--n; n > 0; n >>= 1)
    {
        r <<= 1;        // Shift return value
        r |= (v & 0x1); // Merge in next bit
        v >>= 1;        // Shift reversal value
    }
    return r;
}

bool FFT::ReadInputs(char* fn, vector<Complex>& data)
{ 
    // Read inputs from a file, store in the "data" vector
    ifstream f(fn);
    if (!f)
    {
        cout << "Can't open input data file " << fn << endl;
        return false;
    }
    while(f)
    {
        string line;
        getline(f, line);
        if (line.length() == 0) continue; // empty
        if (line[0] == '#')     continue; // comment
        data.push_back(Complex(atof(line.c_str()))); // Add to data vector
    }
    return true; // Read correctly
}


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cout << "Usage: fft filename" << endl;
        exit(1);
    }
    bool simple = false;
    if (argc > 2) simple = true;
    vector<Complex> inputs;            // Holds the time domain samples
    FFT::ReadInputs(argv[1], inputs);  // Reads the samples from the input file
    cout << "Found " << inputs.size() << " input samples" << endl;
    FFT f(inputs);                     // Creates the FFT object
    if (simple)
    {
        f.TransformSimple();           // Do the transform (simple, inefficient)
    }
    else
    {
        f.Transform();                  // Do the transform
    }
}





