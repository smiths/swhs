This folder contains the Python implementation of the SWHS software.

The software writes a file containing the output data and a PNG file containing the graphs of water and PCM temperature and energy over the simulation time.

energy.py holds the Energy Equations Module.

event.py and temperature.py hold the Temperature ODEs Module.

load_params.py holds the Input Format Module.

main.py holds the Control Module.

output.py holds the Output Format Module.

parameters.py holds the Input Parameters Module.

plot.py holds the Plotting Module.

test.in is a sample input parameters file.

verify_output.py holds the Output Verification Module.

verify_params.py holds the Input Verification Module.

This implementation uses PyDSTool software by Rob Clewley, which requires NumPy and SciPy. This implementation also uses matplotlib to generate graphs of the results.

The PyDSTool software is available from its GitHub page: https://github.com/robclewley/pydstool

PyDSTool is also available at SourceForge. However, at the time of this writing, the latest version of PyDSTool from SourceForge did not work for the SWHS software when tested using Python 3.5. For that reason, it is recommended that the latest version of PyDSTool be obtained by cloning the GitHub repository and installing.

Instructions for obtaining NumPy and SciPy can be found here: http://scipy.org/scipylib/download.html

Instructions for installing matplotlib can be found here: http://matplotlib.org/users/installing.html

Once everything is installed, move the input parameters files to this directory. Note that the input parameter files must have comments denoted with the  '#' character. They must also end with the extension '.in'. The SWHS software can be run using:

`make`

All generated files can be removed using:

`make clean`

Software testing will be added in the future.
