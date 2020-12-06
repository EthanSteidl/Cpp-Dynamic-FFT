#include <vector>
#include <complex>
#include <vector>
#include <algorithm> 
#include <fstream>
#include "FFT.h"
#include <chrono>
using namespace std;

void test();


/*
FFT based off code on page 911 of the class textbook

*/
int main(int argc, char **argv)
{


    test();
    
    FFT f = FFT(argv[1]);
    f.calculate();
    f.print();

    return 0;
}

void test()
{
    //file used for testing
    
    //char infile[20] = "test-n2a.txt";
    char infile[20] = "test-n2a.txt";
    FFT f = FFT(infile);
    f.calculate();
    f.print();


    //char infile[20] = "test-n2a.txt";
    char infile1[20] = "test-n2b.txt";
    f = FFT(infile1);
    f.calculate();
    f.print();
    //cout << f.solve_frequency() << endl;

    //char infile[20] = "test-n2a.txt";
    char infile2[20] = "test-n4a.txt";
    f = FFT(infile2);
    f.calculate();
    f.print();


    //char infile[20] = "test-n2a.txt";
    char infile3[20] = "test-n4b.txt";
    f = FFT(infile3);
    f.calculate();
    f.print();


    //char infile[20] = "test-n2a.txt";
    char infile4[20] = "test-n8a.txt";
    f = FFT(infile4);
    f.calculate();
    f.print();


    //char infile[20] = "test-n2a.txt";
    char infile5[20] = "test-n8b.txt";
    f = FFT(infile5);
    f.calculate();
    f.print();

    char infile7[20] = "test-n16.txt";
    f = FFT(infile7);
    f.calculate();
    f.print();


    char infile8[20] = "test-n20.txt";
    f = FFT(infile8);
    f.calculate();
    f.print();

    
    //char infile[20] = "test-n2a.txt";
    char infile6[20] = "test-long.txt";
     f = FFT(infile6);
     auto start = chrono::high_resolution_clock::now();
    f.calculate();
    auto stop = chrono::high_resolution_clock::now();
    f.print();

    cout << "Duration: " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << endl;;

    
    char infilel2[20] = "test-long2.txt";
    f = FFT(infilel2);
    start = chrono::high_resolution_clock::now();
    f.calculate();
    stop = chrono::high_resolution_clock::now();
    f.print();
    cout << "Duration: " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << endl;;
}

