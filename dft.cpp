/*
 * dft.cpp
 *
 *  Created on: 30 Oct 2015
 *      Author: mick
 */

#include    "entropy.h"

#define PI2 6.2832

void    dft( uint32_t *symbols, uint32_t total_symbols, FILE *fp, uint8_t figure ) {

    uint32_t    i;            // General counters
    int n, k;                 // indices for time and frequency domains

    float *x;               // discrete-time signal, x

    float *Xre, *Xim;         // DFT of x (real and imaginary parts)
    float *P;               // power spectrum of x

    printf( "Dft: total_symbols=%d\n", total_symbols );

    k = sizeof( float ) * total_symbols;

    x = (float *)malloc( k );
    Xre = (float *)malloc( k );
    Xim = (float *)malloc( k );
    P = (float *)malloc( k );

    for( i=0; i < total_symbols; i++ ) {
        x[i] = (float)(symbols[i]);
        Xre[i] = 0;
        Xim[i] = 0;
        P[i] = 0;
    }


    // Calculate DFT of x using brute force
    for (k=0 ; k<total_symbols ; ++k) {
        // Real part of X[k]
        Xre[k] = 0;
        for (n=0 ; n<total_symbols ; ++n) {
            Xre[k] += x[n] * cos(n * k * PI2 / total_symbols);
        }

        // Imaginary part of X[k]
        Xim[k] = 0;
        for (n=0 ; n<total_symbols ; ++n) {
            Xim[k] -= x[n] * sin(n * k * PI2 / total_symbols);
        }

        // Power at kth frequency bin
        P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k];
    }

    // Output results to MATLAB / Octave M-file for plotting
    fprintf(fp, "n = [0:%d];\n", total_symbols-1);
    fprintf(fp, "x = [ ");
    for (n=0 ; n<total_symbols ; ++n) {
        fprintf(fp, "%f ", x[n]);
    }
    fprintf(fp, "];\n");
    fprintf(fp, "Xre = [ ");
    for (k=0 ; k<total_symbols ; ++k) {
        fprintf(fp, "%f ", Xre[k]);
    }
    fprintf(fp, "];\n");
    fprintf(fp, "Xim = [ ");
    for (k=0 ; k<total_symbols ; ++k) {
        fprintf(fp, "%f ", Xim[k]);
    }
    fprintf(fp, "];\n");
    fprintf(fp, "P = [ ");
    for (k=0 ; k<total_symbols ; ++k) {
        fprintf(fp, "%f ", P[k]);
    }
    fprintf(fp, "];\n");
    fprintf(fp, "figure(%d);\n", figure );
    fprintf(fp, "title (\"DFT for %d Symbols\");\n", total_symbols );
    fprintf(fp, "subplot(3,1,1)\nplot(n,x)\n");
    fprintf(fp, "xlim([0 %d])\n", total_symbols-1);
    fprintf(fp, "subplot(3,1,2)\nplot(n,Xre,n,Xim)\n");
    fprintf(fp, "xlim([0 %d])\n", total_symbols-1);
    fprintf(fp, "subplot(3,1,3)\nstem(n,P)\n");
    fprintf(fp, "xlim([0 %d])\n", total_symbols-1);
    printf( "Dft Output complete\n" );
}
