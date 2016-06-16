This folder contains the C language implementation of the SWHS software.

This implementation uses the CVODE 2.8.2 solver by Sundials to solve the ODEs in the problem.
It uses the gnuplot 5.0 software to generate the graphs of the results.

The software writes a file containing the output data and a PNG file containing the graphs of the water and PCM temperature and energy over the simulation time.

The program can be run using make. Ensure that your input parameters file ends with .in and is in the same directory as the Makefile and SWHS software. Also be sure to add the lib folder to your system's PATH. Either of the following commands should run the program:

- make

- make -f Makefile.txt

Software testing and makefile updates are planned to be added later.