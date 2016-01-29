#Ion\_Pop\_Solver
Here is the code for the ion population solver (in the attached .zip file). The 'build.bat' file contains the g++ command line needed to compile/link it. An example of an input file is given in T(t)_n(t)_1.txt (other examples are in the 'Test_Profiles' directory). The file structure is simply the number of entries in the file, then the first column is the time, the second column is the temperature (electron), and the final column is the number density.

Upon running the code you are also asked to supply the atomic number of the element to solve for and the ion range. These inputs can be 26 (iron) and 1 to 27 (neutral to fully ionized iron).

The output file format is time, Te, T_eff, number density, ionization states...

##TODO:
 + Move RadiationModel to submodule that is shared with HYDRAD; ensures that we are 
treating radiation the same way in both codes
 + Move atomic database out of radiation model. Use apolloDB
 + Can it handle more than one element?
 + XML config files
