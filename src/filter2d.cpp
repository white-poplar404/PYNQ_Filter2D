#include <iostream>
using namespace std;
#include <math.h>
#include "filter2d.h"

void filter2d_accel(DTYPE* img_in, DTYPE* kernel, DTYPE* img_out, int rows, int cols)
{
#pragma HLS INTERFACE axis port=img_in
#pragma HLS INTERFACE axis port=img_out
#pragma HLS INTERFACE axis port=kernel
#pragma HLS INTERFACE s_axilite port=rows  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=cols  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL
    int sum = 0;
    int count = 0;
    for(int x=0;x<rows-2;x++){
#pragma HLS LOOP_TRIPCOUNT min=1 max=126
        for(int y=0;y<cols-2;y++){
#pragma HLS LOOP_TRIPCOUNT min=1 max=126
#pragma HLS pipeline
            int sum = 0;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    sum += img_in[128*(x+i)+(y+j)] * kernel[x*3+y];
                }
            }
            img_out[count++] = sum;
        }
    }
}
