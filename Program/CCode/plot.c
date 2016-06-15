/* Plot Module

This module takes the output values produced and plots them using
GNUplot, and outputs the plots to a png file.

Authors: Thulasi Jegatheesan, Spencer Smith, Ned Nedialkov, and Brooks
MacLachlan

Date Last Revised: June 10, 2016

State Variables: none

Environment Variables: the file associated with the filename

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plot.h"

void plot(float time[], float tempW[], float tempP[], float eW[], float eP[], struct parameters params, int sizeOfResults, char outputFilename[]){

    int i;
    char filenamePrefix[strlen(outputFilename)-2];
    for(i = 0; i < strlen(outputFilename); i++){
        filenamePrefix[i] = outputFilename[i];
        if(outputFilename[i] == '.'){
            break;
        }
    }

    FILE *gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "set terminal png enhanced font 'Verdana,8'\n");
    fprintf(gnuplot, "set output '%spng'\n", filenamePrefix);
    fprintf(gnuplot, "set style data lines\n");
    fprintf(gnuplot, "set key left box\n");
    fprintf(gnuplot, "set xtics 0,10000,50000\n");
    fprintf(gnuplot, "set multiplot\n");
    fprintf(gnuplot, "set size 0.5, 1\n");
    fprintf(gnuplot, "set origin 0.0, 0.0\n");
    fprintf(gnuplot, "set title \"Temperature Profiles\"\n");
    fprintf(gnuplot, "set xlabel \"Time (seconds)\"\n");
    fprintf(gnuplot, "set ylabel \"Temperature (Celsius)\"\n");
    fprintf(gnuplot, "plot \"%s\" every ::34 using 1:2 title 'Water', \"%s\" every ::34 using 1:3 title 'PCM'\n", outputFilename, outputFilename);
    fprintf(gnuplot, "set origin 0.5, 0.0\n");
    fprintf(gnuplot, "set title \"Energy Profiles\"\n");
    fprintf(gnuplot, "set xlabel \"Time (seconds)\"\n");
    fprintf(gnuplot, "set ylabel \"Energy (J)\"\n");
    fprintf(gnuplot, "plot \"%s\" every ::34 using 1:4 title 'Water', \"%s\" every ::34 using 1:5 title 'PCM'\n", outputFilename, outputFilename);
    fprintf(gnuplot, "unset multiplot");
    fflush(gnuplot);

    return;
}
