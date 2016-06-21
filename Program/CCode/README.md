This folder contains the C language implementation of the SWHS software.

This implementation uses the CVODE 2.8.2 solver by Sundials to solve the ODEs in the problem.
It uses the gnuplot 5.0.3 software to generate the graphs of the results.

The software writes a file containing the output data and a PNG file containing the graphs of the water and PCM temperature and energy over the simulation time.

Before running the program, the CVODE and gnuplot libraries must be installed.

To install CVODE:

- Download the CVODE software at http://computation.llnl.gov/projects/sundials-suite-nonlinear-differential-algebraic-equation-solvers/sundials-software

- The downloaded package contains an installation guide with specific instructions depending on your system's environment

To install gnuplot:

- Download either a self-installer or the source files from https://sourceforge.net/projects/gnuplot/files/

- If using a self-installer, simply follow the on screen prompts to install

- If building from source files, follow the instructions in the INSTALL file included in the download

The SWHS software is run using make. In order to ensure that the makefile will work, one of the following must be done:

- In this directory, create a "lib" subdirectory and fill it with both the CVODE libraries and gnuplot libraries, or

- Edit the Makefile "LIB_DIRS" variable with the paths to the CVODE and gnuplot libraries

Regardless of which of the above options you choose, you must also add the paths to the CVODE and gnuplot libraries to your system's PATH variable.

Once all of this has been successfully completed, the program can be run from this directory using either of the following commands:

- make

- make -f Makefile.txt

The software testing for SWHS uses the Unity C testing framework. To run the tests on the software, execute either of the following commands from this directory:

- make tests

- make -f Makefile.txt tests