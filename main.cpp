//============================================================================
// Name        : entropy.cpp
// Author      :
// Version     :
// Copyright   : Mick Vaites (c) 2015 (updated to Xcode 2022)
// Description : Calculate 8 and 16 bit entropy and plot distribution bar chart
//============================================================================

#include    "main.h"

FILE        *octave_fp = 0;

uint64_t    fsize( uint8_t    *fn ) {

    struct    stat    st;

    if( stat( (const char *)fn, &st ) == 0 ) {
        return    st.st_size;
    }
    return    0;
}


void    args() {
    printf( "args:\n\n");
    printf( "entropy <filename> [-s] [-c len] [-b qty] [-m val] [-ct val] [-cb val] [-8] [-16]\n");
    printf( " -s             Sort assending\n");
    printf( " -c  <len>      Load len bytes (defautl load all)\n");
    printf( " -b  <qty>      Number of barchart buckets (default/max 128)\n");
    printf( " -m  <val>      Max value for barchart items (default 20)\n");
    printf( " -ct <val>      Crop bucket at top value (default = 2000000)\n");
    printf( " -cb <val>      Crop bucket at bottom value (default = 0)\n");
    printf( " -ls <val>      Crop chart to display lowest symbol (default = 0)\n");
    printf( " -hs <val>      Crop chart to display highest symbol (default = max for 8bits or 16bits)\n");
    printf( " -8             Calculate 8 bit entropy (default)\n");
    printf( " -16            Calculate 16 bit entropy\n");
    printf( " -o  <octave.m> Octave filename for dft and fft plotting\n");
    printf( "\n");
    exit(0);
}

int main( int argc, char *argv[] ) {

    FILE        *fp;
    uint64_t    len, read_len, i;
    uint8_t     *data;
    uint32_t    *symbols;
    uint32_t    total_symbols = SYMBOLS8;

    printf( "\n" );
    printf( "Entropy and distribution bar chart by Mick Vaites (c) 2022\n\n" );

    if( argc < 2 ) {
        args();
    }

    len = fsize( (uint8_t *)argv[1] );
    if( len == 0 ) {
        printf( "Bad file %s\n", argv[1]);
        exit(0);
    }

    fp = fopen( argv[1], "rb" );
    if( !fp ) {
        printf( "Failed to open file %s\n", argv[1] );
        exit(0);
    }

    i = 2;
    while(i < argc) {
        if(strcasecmp(argv[i], "-s") == 0) {
            i++;
            sort_yn = 1;
        } else if(strcasecmp(argv[i], "-c") == 0) {
                i++;
                if( i < argc ) {
                    read_len = atoi(argv[i]);
                    if(read_len && read_len < len ) {
                        len = read_len;
                    }
                    i++;
                } else {
                    printf( "Missing count \n");
                    exit(0);
                }
        } else if(strcasecmp(argv[i], "-b") == 0) {
                i++;
                if( i < argc ) {
                    total_buckets = atoi(argv[i]);
                    i++;
                } else {
                    printf( "Missing param \n");
                    exit(0);
                }
        } else if(strcasecmp(argv[i], "-m") == 0) {
                i++;
                if( i < argc ) {
                    max_bucket_val = atoi(argv[i]);
                    i++;
                } else {
                    printf( "Missing param \n");
                    exit(0);
                }
        } else if(strcasecmp(argv[i], "-o") == 0) {
                i++;
                if( i < argc ) {
                    octave_fp = fopen( argv[i], "w");
                    if( octave_fp == 0 ) {
                        printf("Failed to open %s for output\n", argv[i] );
                        exit(0);
                    }
                    i++;
                } else {
                    printf( "Missing filename \n");
                    exit(0);
                }
        } else if(strcasecmp(argv[i], "-ct") == 0) {
                i++;
                if( i < argc ) {
                    crop_bucket_top_val = atoi(argv[i]);
                    i++;
                } else {
                    printf( "Missing count \n");
                    exit(0);
                }
        } else if(strcasecmp(argv[i], "-cb") == 0) {
                i++;
                if( i < argc ) {
                    crop_bucket_bottom_val = atoi(argv[i]);
                    i++;
                } else {
                    printf( "Missing count \n");
                    exit(0);
                }
        } else if(strcasecmp(argv[i], "-ls") == 0) {
                i++;
                if( i < argc ) {
                    crop_lowest_symbol = atoi(argv[i]);
                    i++;
                } else {
                    printf( "Missing count \n");
                    exit(0);
                }
        } else if(strcasecmp(argv[i], "-hs") == 0) {
                i++;
                if( i < argc ) {
                    crop_highest_symbol = atoi(argv[i]);
                    i++;
                } else {
                    printf( "Missing count \n");
                    exit(0);
                }
        } else if(strcasecmp(argv[i], "-8") == 0) {
            total_symbols = 256;
            i++;
        } else if(strcasecmp(argv[i], "-16") == 0) {
            total_symbols = 65536;
            i++;
        } else if(strcasecmp(argv[i], "-h") == 0) {
            args();
            i++;
        } else {
            i++;
        }
    }
    data = (uint8_t *)malloc( len );
    fread( data, 1, len, fp );
    fclose( fp );

    symbols = (uint32_t *)malloc( total_symbols );

    printf( "Analysis of %s (File size %lld in bytes) %s\n",
           argv[1],
           len,
           sort_yn ? "[Sorted]" : "" );

    if( total_symbols == 256 ) {
        shannon_8bit_entropy( (uint8_t*)data,
                               len,
                               symbols );
    } else {
        shannon_16bit_entropy( (uint16_t*)data,
                               (len / 2),
                               symbols );
    }
    display_barchart( symbols, total_symbols );
}
