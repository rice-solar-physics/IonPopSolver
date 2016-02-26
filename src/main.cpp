// ****
// *
// * A code to solve the ionisation / recombination 
// * equations for any given T(t) and n(t)
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 26/03/2010
// *
// ****

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#include "boost/program_options.hpp"

#include "../Radiation_Model/src/ionfrac.h"
#include "../src/fitpoly.h"
#include "../src/file.h"

#define STEPS		1		// Minimum number of integration steps to take between time intervals of sample

int main(int argc, char **argv)
{
double fGet_Teff( PRADIATION pRadiation, double *pNonEquil_ni, int iZ );

PRADIATION pRadiation;
PIONFRAC pIonFrac;

FILE *pFile;
double ft, fdt, fmaxdt, fT, fn;
double *pft, *pfT, *pfn;
double x[3], y[3], pstep;
double **ppni, **ppdnibydt;
double *pNonEquil_ni;
char szFilename[256],szFilename_out[256];
int iZ, iSpec_from, iSpec_to, iSpec;
int i, iNumSteps;
double safety_atomic,cutoff_ion_fraction;

//Read command line options using Boost command line parsing library
namespace po = boost::program_options;
po::options_description description("A code to solve the ionisation / recombination equations for any given T(t) and n(t)\n\n(c) Dr. Stephen J. Bradshaw\n\nDate last modified: 26/03/2010\n\nUsage");
description.add_options()
	("help,h","The help message")
	("safety_atomic,s",po::value<double>(&safety_atomic)->default_value(0.1),"Step size limit in atomic calculation")
	("cutoff_ion_fraction,c",po::value<double>(&cutoff_ion_fraction)->default_value(1e-300),"Minimum ion fraction before being set to 0.")
	("element,Z",po::value<int>(&iZ)->required(),"Atomic number of element")
	("spec_from,f",po::value<int>(&iSpec_from)->required(),"Spectroscopic number of element (from)")
	("spec_to,t",po::value<int>(&iSpec_to)->required(),"Spectroscopic number of element (to)")
	("input_file,I",po::value<std::string>()->required(),"Data file containing T(t) and n(t)")
	("output_file,O",po::value<std::string>(),"File to print results to.");
po::variables_map vm;
po::store(po::command_line_parser(argc,argv).options(description).run(), vm);
if(vm.count("help"))
{
	std::cout << description;
	return 0;
}
po::notify(vm);
std::strcpy(szFilename,vm["input_file"].as<std::string>().c_str());

// Read the values from the date file containing T(t) and n(t)
pFile = fopen( szFilename, "r" );
fscanf( pFile, "%i", &iNumSteps );

// Allocate sufficient memory for t, T(t) and n(t)
pft = (double*)malloc( sizeof(double) * iNumSteps );
pfT = (double*)malloc( sizeof(double) * iNumSteps );
pfn = (double*)malloc( sizeof(double) * iNumSteps );

for( i=0; i<iNumSteps; i++ )
{
	ReadDouble( pFile, &(pft[i]) );
	ReadDouble( pFile, &(pfT[i]) );
	ReadDouble( pFile, &(pfn[i]) );
}

fclose( pFile );

// Create the radiation object
pRadiation = new CRadiation( "Radiation_Model/config/elements.cfg", safety_atomic, cutoff_ion_fraction );

// Initialise the fractional populations of the ions
pIonFrac = new CIonFrac( NULL, "Radiation_Model/config/elements.cfg", pRadiation, log10( pfT[0] ), cutoff_ion_fraction );
ppni = pIonFrac->ppGetIonFrac();
ppdnibydt = pIonFrac->ppGetdnibydt();
pNonEquil_ni = pIonFrac->pGetIonFrac( iZ );

// Open the data file for output
if(!vm.count("output_file"))
{
	sprintf( szFilename_out, "Z%i.txt", iZ );	
}
else
{
	std::strcpy(szFilename_out,vm["output_file"].as<std::string>().c_str());
}
pFile = fopen( szFilename_out, "w" );

// Progress bar
pstep = 10.0;
printf( "0%%|         |100%%\n");
printf ( "  |" );

i = 1;

ft = 0.0;
fmaxdt = ( pft[i] - pft[i-1] ) / STEPS;

fT = pfT[0];
fn = pfn[0];

while( ft < pft[iNumSteps-1] )
{
	// Get the populations, time-derivatives and time-scale for integration
	pRadiation->GetAlldnibydt( log10( fT ), log10( fn ), ppni, ppdnibydt, &fdt );
	// Make sure that at least STEPS time steps are taken during this phase
	// It may be necessary to alter the value of SAFETY_ATOMIC in element.h to
	// check for convergence
	if( fdt > fmaxdt )
		fdt = fmaxdt;

	// Write data to output file
	if( ft == pft[i-1] )
	{
		fprintf( pFile, "%g\t%g", ft, fT );

		// Get the effective ionisation temperature
		fprintf( pFile, "\t%g", fGet_Teff( pRadiation, pNonEquil_ni, iZ ) );

		fprintf( pFile, "\t%g", fn );

		for( iSpec=iSpec_from; iSpec<=iSpec_to; iSpec++ )
			fprintf( pFile, "\t%g", pNonEquil_ni[iSpec-1] );
			
		fprintf( pFile, "\n" );
	}

	if( ft + fdt > pft[i] )
	{
		fdt = pft[i] - ft;
		ft = pft[i];

		i++;

		if( i > iNumSteps - 1 )
			i = iNumSteps - 1;

		fmaxdt = ( pft[i] - pft[i-1] ) / STEPS;
	}
	else
		ft += fdt;
	
	// Time-step the ion populations
	pIonFrac->IntegrateAllIonFrac( fdt );

	// Get the correct temperature and density at the current time

	x[1] = pft[i-1];
	x[2] = pft[i];
	
	y[1] = pfT[i-1];
	y[2] = pfT[i];
	LinearFit( x, y, ft, &fT );

	y[1] = pfn[i-1];
	y[2] = pfn[i];
	LinearFit( x, y, ft, &fn );

	// Progress bar
	if( 100.0*(ft/pft[iNumSteps-1]) >= pstep )
	{
		printf( "|" );
		pstep += 10.0;
	}
}

// Write data to output file
fprintf( pFile, "%g\t%g", ft, fT );

// Get the effective ionisation temperature
fprintf( pFile, "\t%g", fGet_Teff( pRadiation, pNonEquil_ni, iZ ) );

fprintf( pFile, "\t%g", fn );

for( iSpec=iSpec_from; iSpec<=iSpec_to; iSpec++ )
	fprintf( pFile, "\t%g", pNonEquil_ni[iSpec-1] );
			
fprintf( pFile, "\n" );

fclose( pFile );

delete pIonFrac;
delete pRadiation;

free( pfn );
free( pfT );
free( pft );

printf( "\n\n" );

return 0;
}

double fGet_Teff( PRADIATION pRadiation, double *pNonEquil_ni, int iZ )
{
double *pEquil_ni, flog10_Teff, fDiff, fminDiff, flog10_T;
int iSpec;

pEquil_ni = (double*)malloc( sizeof(double) * ( iZ + 1 ) );

flog10_Teff = 4.0;
fminDiff = 1e300;
for( flog10_T=4.0; flog10_T<=8.0; flog10_T+=0.01 )
{
	pRadiation->GetEquilIonFrac( iZ, pEquil_ni, flog10_T );

	fDiff = 0.0;
	for( iSpec=1; iSpec<=iZ+1; iSpec++ )
		fDiff+= fabs( pEquil_ni[iSpec-1] - pNonEquil_ni[iSpec-1] );

	if( fDiff < fminDiff )
	{
		fminDiff = fDiff;
		flog10_Teff = flog10_T;
	}
}

free( pEquil_ni );

return pow( 10.0, flog10_Teff );
}
