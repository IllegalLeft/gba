// Example sine lut generator
#include <stdio.h>
#include <math.h>

#define M_PI 3.1415926535f
#define SIN_SIZE 512
#define SIN_FP 12

int main()
{
    int ii;
    FILE *fp= fopen("sinlut.c", "w");
    unsigned short hw;

    fprintf(fp, "//\n// Sine lut; %d entries, %d fixeds\n//\n\n", 
        SIN_SIZE, SIN_FP);
    fprintf(fp, "const short sin_lut[%d]=\n{", SIN_SIZE);
    for(ii=0; ii<SIN_SIZE; ii++)
    {
        hw= (unsigned short)(sin(ii*2*M_PI/SIN_SIZE)*(1<<SIN_FP));
        if(ii%8 == 0)
            fputs("\n\t", fp);
        fprintf(fp, "0x%04X, ", hw);
    }
    fputs("\n};\n", fp);

    fclose(fp);
    return 0;
}
