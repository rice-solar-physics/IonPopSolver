#IonPopSolver
IonPopSolver solves the time-dependent ionization equations for a particular element given tabulated values of the plasma electron temperature and density. These tabulated values can be the solutions of an analytical model, the output from a numerical simuation, or a set of observational measurements. A full description of the numerical model and relevant physics can be found in [Bradshaw (2009)](http://adsabs.harvard.edu/abs/2009A%26A...502..409B).
##Dependencies
IonPopSolver has been successfully tested and run on Mac OS X, Linux (Ubuntu 14.04), and Windows. It is recommended that Windows users use the Unix environment provided by <a href="https://www.cygwin.com/">Cygwin</a>. This will make installing the relevant dependencies and compiling the code much more simple. The following are required dependencies for compiling and running IonPopSolver:
 
<table>
  <tr>
    <th align="center" rowspan="2">Name</th>
    <th align="center" rowspan="2">Description</th>
	<th align="center" colspan="3">Installation</th>
  </tr>
  <tr>
    <th align="center">Mac OS X</th>
	<th align="center">Linux</th>
	<th align="center">Windows</th>
  </tr>
  <tr>
	  <td><a href="https://git-scm.com/"><tt>git</tt></a></td>
	  <td>Version control system; for downloading and updating</td>
	  <td>included</td>
	  <td>included</td>
	  <td><a href="https://www.cygwin.com/">Cygwin</a></td>
  </tr>
  <tr>
	  <td><a href="http://scons.org/"><tt>scons</tt></a></td>
	  <td>Software construction tool; Pythonic alternative to Make</td>
	  <td><a href="https://www.macports.org/">Macports</a>, <a href="https://www.continuum.io/downloads">Anaconda</a>, <a href="http://scons.org/pages/download.html">tarball</a></td>
	  <td><tt>apt-get</tt>, <a href="https://www.continuum.io/downloads">Anaconda</a>, <a href="http://scons.org/pages/download.html">tarball</a></td>
	  <td><a href="https://www.cygwin.com/">Cygwin</a></td>
  </tr>
  <tr>
	  <td><a href="http://www.boost.org/">Boost Libraries</a></td>
	  <td>Open-source C++ libraries; used for command line parsing (the <tt>program_options</tt> module)</td>
	  <td><a href="https://www.macports.org/">Macports</a></td>
	  <td><tt>apt-get</tt></td>
	  <td>install from source (see below)</td>
  </tr>
</table>
 
### Installing Boost on Windows
While the Boost libraries can be downloaded using the Cygwin package installer, building and linking has proved difficult. The best and simplest way for Windows users to acquire the Boost libraries is just to download the source code and build the one needed library, <tt>program_options</tt>.

+ First, download the Boost libraries tarball from [source](http://www.boost.org/users/history/version_1_55_0.html). Download the `.tar.gz` file for the Unix platform into a convenient directory `$DOWNLOADS`.

+ Untar/unzip the compressed source
```Shell
    cd $DOWNLOADS
    tar xvzf boost_1_55_0.tar.gz
```

+ Change directories into the now uncompressed Boost directory.
> `cd boost_1_55_0`

+ Next we need to build and install the libraries. To show the available libraries (but not install anything yet), run
> `./bootstrap.sh --show-libraries`

+ You should see `program_options` under the part that says "The Boost libraries requiring separate building and installation are:".
+ Now its time to setup our installation. Run,
> `./bootstrap.sh --with-libraries=program_options --prefix=/usr/local`

+ Next we need to actually install the libraries in the right place
> `./b2 link=static install` 
