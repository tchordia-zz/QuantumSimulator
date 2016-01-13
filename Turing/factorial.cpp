//
//  factorial.cpp
//  Turing
//
//  Created by Tanmay Chordia on 1/3/16.
//  Copyright © 2016 Dots. All rights reserved.
//

#include <stdio.h>
#include <cmath>
#include <iostream>
#include <complex>
#include <vector>
#include "Eigen/Core"
#include "unsupported/Eigen/KroneckerProduct"

using namespace std;
using namespace Eigen;
class Qubit{
    
private:
    complex<double> val;
    Matrix<complex<double>, Dynamic, 1> vals;
    Matrix<complex<double>, 2, 2> had;
    Matrix<complex<double>, 2, 2> n;

    int numBits = 1;

    void  applyMat(Matrix<complex<double>, Dynamic, Dynamic> m)
    {
//        cout << "cols" << m.cols() <;
        if(!m.isUnitary())
        {
            cout << "not unitary";
            return;
        }
//        if(!(m.cols() == vals.rows()))
//        {
//            cout << "wrong size";
//            return;
//        }
        
        vals = m * vals;
    }
    
   
public:
    
    complex<double> ONE;
    complex<double> ZERO;
    Qubit(): ONE(1,0), ZERO(0,0), vals(2,1){
        
    
        complex<double> o(1,0);
        complex<double> z(0,0);
        vals(0,0) = ONE;
        vals(1,0) = ZERO;
        
        
        
        had << ONE, ONE,
        ONE,-ONE;
        
        had = had / sqrt(2);

        
        n << ZERO, ONE,
        ONE, ZERO;
        
        
    }
    
    void h(){
        trans(had);
        
    }
    void h(int num)
    {
        trans(num, had);
    }
    
    
    void trans(int num, Matrix<complex<double>, 2, 2> mat){
        
        
        Matrix<complex<double>, Dynamic, Dynamic> temp;
        Matrix<complex<double>, Dynamic, Dynamic> doub;
        
        Matrix<complex<double>, 2, 2> iden;
        iden = temp.Identity(2, 2);
        
        cout << "here we go " << numBits << "\n";
        int p = (int)pow(2,num);

       
        doub = kroneckerProduct(mat, temp.Identity(p,p) );
        cout << "passed first half! " << doub.cols() << "\n";
        
        p = (int)pow(2,numBits - num - 1);
        temp = kroneckerProduct(temp.Identity(p,p), doub );
            
        
        cout << "passed second half! \n";
        cout << temp << "\n";
        
        applyMat(temp);
    }
    
    void trans(Matrix<complex<double>, 2, 2> mat)
    {
        int n = numBits;
        
        Matrix<complex<double>, Dynamic, Dynamic> temp;
        Matrix<complex<double>, Dynamic, Dynamic> doub;
        
        temp = mat;
        while(n > 1)
        {
            int p = pow(temp.rows(), 2);
            doub.resize(p, p);
            doub = kroneckerProduct(temp, temp);
            
            
            if(n%2 != 0)
            {
                temp.resize(p * 2,p * 2);
                temp = kroneckerProduct(doub, mat);
            }
            else{
                temp.resize(p,p);
                temp = doub;
            }
            
            n = n/2;
        }
        cout << temp << "\n";

        applyMat(temp);
    }
    
    
    void no(int num)
    {
        trans(num, n);
    }
    
    void no()
    {
        trans(n);
    }
    
    void cnot(int a, int b)
    {
        Matrix<complex<double>, Dynamic, Dynamic> temp;
        Matrix<complex<double>, Dynamic, Dynamic> doub;
          Matrix<complex<double>, Dynamic, Dynamic> fin;
        int rr = 0;
        if(a > b)
        {
            h(a);
            h(b);
            
            rr = a;
            a = b;
            b = rr;
            rr = 1;
            
            
        }
        
        
        cout << "here we go " << numBits << "\n";
        int p = (int)pow(2,b-a);
        
        
        doub.setIdentity(p*2, p*2);
        
        for(int i = 0; i < p*2; i++){
            if(i + 1 > p)
            {
                doub(i,i) = 0;
                doub(i, i + 2*((i + 1)%2) - 1) = 1;
            }
        }
        cout << "part 1 \n" << doub << "\n";
        
        
        p = (int)pow(2,a);
        temp = kroneckerProduct(doub, temp.Identity(p,p) );
        
        
        
        p = (int)pow(2,numBits - b - 1);
        fin = kroneckerProduct(temp.Identity(p,p), temp);
        
        
        
        cout << "passed second half! \n";
        cout << fin << "\n";
        
        applyMat(fin );
        if(rr)
        {
            h(a);
            h(b);
            
        }
    }
    
    
    void r(){
        Matrix<complex<double>, 2, 2> temp;
        
        temp << ZERO, ONE,
        ONE,ZERO;
        
        
        applyMat(temp);
        

        
    }
    
    void printState(){
        
//        cout << vals(0,0) << " |0> + " << vals(1,0) << " |1>" ;
        

        for(int i = 0; i < vals.rows(); i++)
        {
            cout <<  vals(i,0) << " |" << to_string(i) << ">\n";
        }

        
    }
   
    
    void setBits(int a)
    {
        numBits = a;
        vals.resize((int)pow(2,a), 1);
        for(int i = 0; i < vals.rows(); i++)
        {
            vals(i,0) = ZERO;
            
        }
        vals(0,0) = ONE;
        
    }

    
    
};


int main()
{
    Qubit q;
    q.setBits(3);
    q.no(2);
    q.h();
    q.cnot(2,0);
//    q.h();
    q.printState();
    
//    q.n();
//    q.h();
//    q.printState();
    
    
    
}