//
//  entropy.cpp
//  entropy
//
//  Created by Mick Vaites on 11/12/2022.
//
#include "entropy.h"

double  shannon_8bit_entropy( uint8_t   *buffer,
                              uint64_t  buffer_len,
                              uint32_t  *symbols ) {

    double          entropy;
    double          efficiency;
    double          p;

    for(uint64_t i=0; i < SYMBOLS8; i++) symbols[i] = 0;

    // printf( "Loading Symbols\n" );
    for (uint64_t i=0; i < buffer_len; i++ ) {
        symbols[buffer[i]]++;
    }

    // printf( "Calculating Entropy\n" );
    entropy = 0;
    for(uint64_t i=0; i < SYMBOLS8; i++){
        if (symbols[i]) {
            p = ((double)symbols[i]/(double)buffer_len);
            entropy -= p*log2(p);
        }
    }

    efficiency = entropy / 8.0 * 100.0;
    printf( "8bit Entropy = %3.9f (Symbol Count = %lld) Efficiency (%3.9f%%)\n",
           entropy,
           buffer_len,
           efficiency );

    return entropy;
}

double  shannon_16bit_entropy( uint16_t  *buffer,
                               uint64_t  buffer_len,
                               uint32_t  *symbols ) {

    double          entropy;
    double          efficiency;
    double          p;

    for(uint64_t i=0; i<SYMBOLS16; i++) symbols[i] = 0;

    // printf( "Loading Symbols\n" );
    for (uint64_t i=0; i < buffer_len; i++ ) {
        symbols[buffer[i]]++;
    }

    // printf( "Calculating Entropy\n" );
    entropy = 0;
    for(uint64_t i=0; i < SYMBOLS16; i++){
        if (symbols[i]) {
            p = ((double)symbols[i]/(double)buffer_len);
            entropy -= p*log2(p);
        }
    }

    efficiency = entropy / 16.0 * 100.0;
    printf( "16bit Entropy = %3.9f (Symbol Count = %lld) Efficiency (%3.9f%%)\n",
           entropy,
           buffer_len,
           efficiency );

    return entropy;
}
