/*
 * bar_chart.cpp
 *
 *  Created on: 30 Oct 2015
 *      Author: mick
 */

#include    "bar_chart.h"

void    display_barchart( uint32_t  *symbols, uint32_t total_symbols ) {

    uint32_t        *buckets;      // Values for each of the buckets
    uint32_t        *indexes;      // These will carry the indexes of the buckets
    uint32_t        i, j, t, s;
    uint32_t        m, c, k, w;
    uint32_t        ts,sc;
    double          l;

    ts = crop_highest_symbol - crop_lowest_symbol;
    if( ts < total_buckets ) {
        total_buckets = ts;
        w = 1;
    } else {
        w = ts / total_buckets;            // Width or range of a bucket
    }
    
    printf( "Barchart: buckets=%d, max value=%d, cropped (top=%d, bottom=%d), symbol range (%d to %d)\n",
           total_buckets,
           max_bucket_val,
           crop_bucket_top_val,
           crop_bucket_bottom_val,
           crop_lowest_symbol,
           crop_highest_symbol);
    
    k = sizeof( uint32_t) * total_buckets;
    buckets = (uint32_t *)malloc( k );
    indexes = (uint32_t *)malloc( k );

    for( i=0,sc=crop_lowest_symbol; i < total_buckets; i++ ) {
        buckets[i] = 0;
        indexes[i] = sc;
    }

    for( i=0,sc=crop_lowest_symbol; i < total_buckets; i++ ) {
        for(j = (sc*w); j < ((sc+1)*w)-1; j++ ) {
            buckets[i] += symbols[j];
        }
    }

    m = 0;
    for(i=0; i<total_buckets; i++) {
        if( buckets[i] > m ) {
            m = buckets[i];
        }
        buckets[i] -= crop_bucket_bottom_val;
    }
    printf("Max value = %d ", m );
    if( m > crop_bucket_top_val ) {
        m = crop_bucket_top_val;
        printf("cropped to = %d ", m );
    }

    if( sort_yn ) {
        for(uint32_t i=0; i < total_buckets; ++i) {
            for(uint32_t j=i + 1; j < total_buckets; ++j ) {
                if( buckets[i] > buckets[j] ) {
                    uint32_t t = buckets[i];
                    uint32_t s = indexes[i];
                    buckets[i] = buckets[j];
                    indexes[i] = indexes[j];
                    buckets[j] = t;
                    indexes[j] = s;
                }
            }
        }
    }

/*    l = (double)max_bucket_val/(double)m;
    for( i=0; i<total_buckets; i++) {
        j = buckets[i];
        c = l * j;
        printf( "[%02x - %02x][%06x]", (uint8_t)(indexes[i] * w), (uint8_t)(((indexes[i] + 1) * w) - 1), j );
        for( k=0; k<c; k++ ) {
            printf( "#" );
        }
        printf( "\n" );
    }
*/
    // multiplier actual value to barchart height
    l = (double)max_bucket_val/(double)(m - crop_bucket_bottom_val);
    printf( " max_bucket_val = %d, multiplier = %f\n", max_bucket_val, l );
    printf( "\n");
    for( i=max_bucket_val; i>0; i-- ) {
        k = (i * (m - crop_bucket_bottom_val)) / max_bucket_val;
        if( i % 3 == 0 ) {
            printf( "%07d -|", k + crop_bucket_bottom_val );
           } else {
            printf( "        -|" );
           }
        for( j=0; j < total_buckets; j++ ) {
            c = (double)(l * buckets[j]);            // calculate the amount
            if( c >= i ) {
                printf("#");
            } else {
                printf( " ");
            }
        }
        printf("\n");
    }
    printf( "         " );
    for(i=0; i < total_buckets; i++ ) {
        printf( "-" );
    }
    printf("\n" );
    printf("         ");

    for(i=0; i < total_buckets; i++ ) {
        if( i % 8 ) {
            printf( " " );
        } else {
            printf( "|" );
        }
    }
    printf("\n         ");
    for(i=0; i < total_buckets; i += 8 ) {
        printf( "%04X    ", i * w );
    }
    printf("\n\n");
    free( buckets );
    free( indexes );
}
