This folder contains the MatLab implementation of the SWHS software.

MISNotes.txt contains notes about the mapping of the MIS to the Matlab implementation.

The Testing folder contains all of the required files for the testing of this software.

To run the software in MatLab:

- Launch MatLab

- Navigate to the directory containing all of the .m files that can be found in
this folder.

- Prepare a text file containing the input parameters for the software. The input
parameters must appear in the correct order, and comments must be denoted with a
"#". See the "test.in" file for an example.

- Run the following command in MatLab:

  main('test.in')

  where test.in should be replaced by the name of the file containing the input
  parameters that you want to use.

- A file containing the output data, as well as files containing graphs of the
water and PCM temperature and energy over the simulation time will be written to
the current directory.

__Note for users without Matlab installed__

You may be able to SSH to a computer with MatLab, and then run Matlab from the command line.

MatLab can be run from the command line of a computer with Matlab installed simply by running the command `matlab`.

Users from McMaster University with CAS login credentials can SSH to mills.cas.mcmaster.ca using their CAS login credentials. Matlab can then be run from the command line.