#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 50

int main()
{
    FILE *fp;
    FILE *gp;

    double f1[MAXN+1],f2[MAXN+1],f3[MAXN+1],f4[MAXN+1];
    double f5[MAXN+1],f6[MAXN+1],f7[MAXN+1],f8[MAXN+1];
    double f9[MAXN+1],f10[MAXN+1],f11[MAXN+1],f12[MAXN+1];

    double m1=0,m2=0,m3=0,m4=0,m5=0,m6=0,m7=0,m8=0,m9=0,m10=0,m11=0,m12=0;

    int n;

    /* Calculate all values and maxima */

    for(n=2;n<=MAXN;n++)
    {
        f1[n]=n*log2(n);
        f2[n]=12*sqrt(n);
        f3[n]=1.0/n;
        f4[n]=pow(n,log2(n));
        f5[n]=100*n*n+6*n;
        f6[n]=pow(n,0.51);
        f7[n]=n*n-324;
        if(f7[n]<0) f7[n]=0;      // avoid negative values
        f8[n]=50*sqrt(n);
        f9[n]=2*pow(n,3);
        f10[n]=pow(3,n);
        f11[n]=pow(2,32)*n;
        f12[n]=log2(n);

        if(f1[n]>m1)m1=f1[n];
        if(f2[n]>m2)m2=f2[n];
        if(f3[n]>m3)m3=f3[n];
        if(f4[n]>m4)m4=f4[n];
        if(f5[n]>m5)m5=f5[n];
        if(f6[n]>m6)m6=f6[n];
        if(f7[n]>m7)m7=f7[n];
        if(f8[n]>m8)m8=f8[n];
        if(f9[n]>m9)m9=f9[n];
        if(f10[n]>m10)m10=f10[n];
        if(f11[n]>m11)m11=f11[n];
        if(f12[n]>m12)m12=f12[n];
    }

    fp=fopen("growth.dat","w");

    for(n=2;n<=MAXN;n++)
    {
        fprintf(fp,"%d %.6lf %.6lf %.6lf %.6lf %.6lf %.6lf %.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n",
                n,
                f1[n]/m1,
                f2[n]/m2,
                f3[n]/m3,
                f4[n]/m4,
                f5[n]/m5,
                f6[n]/m6,
                (m7>0)?f7[n]/m7:0,
                f8[n]/m8,
                f9[n]/m9,
                f10[n]/m10,
                f11[n]/m11,
                f12[n]/m12);
    }

    fclose(fp);

    printf("\nIncreasing Order of Growth:\n\n");
    printf("1/n\n");
    printf("< log2(n)\n");
    printf("< 12sqrt(n)\n");
    printf("< 50sqrt(n)\n");
    printf("< n^0.51\n");
    printf("< 2^32*n\n");
    printf("< nlog2(n)\n");
    printf("< n^2-324\n");
    printf("< 100n^2+6n\n");
    printf("< 2n^3\n");
    printf("< n^(log2n)\n");
    printf("< 3^n\n");

    gp=popen("gnuplot -persistent","w");

    fprintf(gp,"set title 'Normalized Growth Comparison'\n");
    fprintf(gp,"set xlabel 'n'\n");
    fprintf(gp,"set ylabel 'Normalized Value'\n");
    fprintf(gp,"set yrange [0:1.05]\n");
    fprintf(gp,"set grid\n");
    fprintf(gp,"set key outside\n");

    fprintf(gp,
    "plot "
    "'growth.dat' u 1:2 w l lw 2 title 'nlog2(n)',"
    "'growth.dat' u 1:3 w l lw 2 title '12sqrt(n)',"
    "'growth.dat' u 1:4 w l lw 2 title '1/n',"
    "'growth.dat' u 1:5 w l lw 2 title 'n^(log2n)',"
    "'growth.dat' u 1:6 w l lw 2 title '100n^2+6n',"
    "'growth.dat' u 1:7 w l lw 2 title 'n^0.51',"
    "'growth.dat' u 1:8 w l lw 2 title 'n^2-324',"
    "'growth.dat' u 1:9 w l lw 2 title '50sqrt(n)',"
    "'growth.dat' u 1:10 w l lw 2 title '2n^3',"
    "'growth.dat' u 1:11 w l lw 2 title '3^n',"
    "'growth.dat' u 1:12 w l lw 2 title '2^32*n',"
    "'growth.dat' u 1:13 w l lw 2 title 'log2(n)'\n");

    fflush(gp);
    pclose(gp);

    return 0;
}