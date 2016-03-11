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
 
## Dependencies
### Boost

 + Download the Boost libraries tarball from [source](http://www.boost.org/doc/libs/1_55_0/more/getting_started/unix-variants.html). Get the Mac/Linux version since we are working in Cygwin.
 + Untar/unzip the compressed source
 > `tar xvzf boost_1_55_0.tar.gz`
 + Change directories into the now uncompressed Boost directory.
 > `cd boost_1_55_0`
 + Next we need to build and install the libraries. To show the available libraries (but not install anything yet), run
 > `./bootstrap.sh --show-libraries`
 + You should see `program_options` under the part that says "The Boost libraries requiring separate building and installation are:".
 + Now its time to setup our installation. Run,
 > `./bootstrap.sh --with-libraries=program_options --prefix=/usr/local`
 + Next we need to actually install the libraries in the right place
 > `./b2 link=static install` 
