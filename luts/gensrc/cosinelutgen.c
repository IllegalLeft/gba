// Example cosine lut generator
#include <stdio.h>
#include <math.h>

#define M_PI 3.1415926535f
#define COS_SIZE 512
#define COS_FP 12

int main()
{
    int ii;
    FILE *fp= fopen("coslut.c", "w");
    unsigned short hw;

    fprintf(fp, "//\n// Cosine lut; %d entries, %d fixeds\n//\n\n", 
        COS_SIZE, COS_FP);
    fprintf(fp, "const short cos_lut[%d]=\n{", COS_SIZE);
    for(ii=0; ii<COS_SIZE; ii++)
    {
        hw= (unsigned short)(cos(ii*2*M_PI/COS_SIZE)*(1<<COS_FP));
        if(ii%8 == 0)
            fputs("\n\t", fp);
        fprintf(fp, "0x%04X, ", hw);
    }
    fputs("\n};\n", fp);

    fclose(fp);
    return 0;
}
