//
//  bar_chart.h
//  entropy
//
//  Created by Mick Vaites on 11/12/2022.
//

#ifndef bar_chart_h
#define bar_chart_h

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

uint32_t    total_buckets = 128;
uint8_t     max_bucket_val = 20;
uint32_t    crop_bucket_top_val = 2000000;
uint32_t    crop_bucket_bottom_val = 0;
uint32_t    crop_lowest_symbol = 0;
uint32_t    crop_highest_symbol = 0;
bool        sort_yn = 0;

#endif /* bar_chart_h */
