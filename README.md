#IonPopSolver
IonPopSolver solves the time-dependent ionization equations for a particular element given tabulated values of the plasma electron temperature and density. These tabulated values can be the solutions of an analytical model, the output from a numerical simuation, or a set of observational measurements. A full description of the numerical model and relevant physics can be found in [Bradshaw (2009)](http://adsabs.harvard.edu/abs/2009A%26A...502..409B).
##Dependencies
The following are required dependencies for compiling and running IonPopSolver:
 
<table>
  <tr>
    <td rowspan="2">Name</td>
    <td rowspan="2">Description</td>
	<td colspan="3">Installation</td>
  </tr>
  <tr>
    <td>Mac OS X</td>
	<td>Linux</td>
	<td>Windows</td>
  </tr>
  <tr>
	  <td><tt>`git`</tt></td>
	  <td>Version control system; for downloading and updating</td>
	  <td>included</td>
	  <td>included</td>
	  <td><a href="https://www.cygwin.com/">Cygwin</a></td>
  </tr>
  <tr>
	  <td><a href="http://scons.org/"><tt>`scons`</tt></a></td>
	  <td>Software construction tool; Pythonic alternative to Make</td>
	  <td><a href="https://www.macports.org/">Macports</a>, <a href="https://www.continuum.io/downloads">Anaconda</a>, <a href="http://scons.org/pages/download.html">tarball</a></td>
	  <td>`apt-get`, <a href="https://www.continuum.io/downloads">Anaconda</a>, <a href="http://scons.org/pages/download.html">tarball</a></td>
	  <td><a href="https://www.cygwin.com/">Cygwin</a></td>
  </tr>
</table>
 
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
