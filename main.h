//
//  main.h
//  entropy
//
//  Created by Mick Vaites on 11/12/2022.
//

#ifndef main_h
#define main_h

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <iostream>

using namespace std;

#define    SYMBOLS8        256
#define    SYMBOLS16       65536

double  shannon_8bit_entropy( uint8_t *, uint64_t ,uint32_t *);
double  shannon_16bit_entropy( uint16_t *, uint64_t ,uint32_t * );
void    display_barchart( uint32_t *, uint32_t );

void    dft( uint32_t *, uint32_t, FILE *, uint8_t );
void    octave_fft( uint32_t *, uint32_t, FILE    *, uint8_t );

extern    uint32_t    total_buckets;
extern    uint8_t     max_bucket_val;
extern    uint32_t    crop_bucket_top_val;
extern    uint32_t    crop_bucket_bottom_val;
extern    uint32_t    crop_lowest_symbol;
extern    uint32_t    crop_highest_symbol;
extern    bool        sort_yn;

#endif /* main_h */
