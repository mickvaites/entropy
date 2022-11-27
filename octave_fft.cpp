/*
 * octave_fft.cpp
 *
 *  Created on: 30 Oct 2015
 *      Author: mick
 */


#include "entropy.h"


void    octave_fft( uint32_t *symbols, uint32_t total_symbols, FILE    *fp, uint8_t figure ) {

    uint32_t    i;            // General counters
    int n, k;                 // indices for time and frequency domains

    float *x;               // discrete-time signal, x

    printf( "FFT: total_symbols=%d\n", total_symbols );

    k = sizeof( float ) * total_symbols;

    x = (float *)malloc( k );

    for( i=0; i < total_symbols; i++ ) {
        x[i] = (float)(symbols[i]);
    }

    fprintf(fp, "N = %d;\n", total_symbols );
    fprintf(fp, "Fs = 1;\n" );
    fprintf(fp, "x = [ ");
    for (n=0 ; n<total_symbols ; ++n) {
        fprintf(fp, "%f ", x[n]);
    }
    fprintf(fp, "];\n");
    fprintf(fp, "figure (%d);\ngrid on;\nN1 = [ 0 : N - 1] / N;\nN1 = N1 * Fs;\nY = fft( x , N);\n", figure );
    fprintf(fp, "subplot( 2, 1, 1);\nplot( N1, x);\nsubplot( 2, 1, 2);\nplot( N1, abs(Y));\n" );
    fprintf(fp, "title (\"FFT for %d Symbols\");\n", total_symbols );
}
