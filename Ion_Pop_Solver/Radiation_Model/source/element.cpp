// ****
// *
// * Element Class Function Bodies for Radiative Emission Model
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 14/06/2005
// *
// ****


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#include "element.h"
#include "../../source/file.h"
#include "../../source/fitpoly.h"


CElement::CElement( int iZ, char *szRangesFilename, char *szRatesFilename, char *szIonFracFilename )
{
Initialise( iZ, szRangesFilename, szRatesFilename, szIonFracFilename );
}

CElement::~CElement( void )
{
FreeAll();
}

void CElement::Initialise( int iZ, char *szRangesFilename, char *szRatesFilename, char *szIonFracFilename )
{
// Set the atomic number of the element
Z = iZ;

// Open the data files and initialise the element
OpenRangesFile( szRangesFilename );
OpenRatesFile( szRatesFilename );
OpenIonFracFile( szIonFracFilename );
}

void CElement::OpenRangesFile( char *szRangesFilename )
{
FILE *pFile;
int i;
char buffer;

// Open the ranges file
pFile = fopen( szRangesFilename, "r" );

// Read the comment line
buffer = 0;
while( buffer != '.' )
	fscanf( pFile, "%c", &buffer );

// Get the number of temperature and density values
fscanf( pFile, "%i", &NumTemp );
fscanf( pFile, "%i", &NumDen );

// Allocate arrays to hold the log_10 temperature and density values
pTemp = (double*)malloc( sizeof(double) * NumTemp );
pDen = (double*)malloc( sizeof(double) * NumDen );

// Read the comment line
buffer = 0;
while( buffer != '.' )
	fscanf( pFile, "%c", &buffer );

// Get the log_10 temperature values
for( i=0; i<NumTemp; i++ )
	ReadDouble( pFile, &(pTemp[i]) );

// Read the comment line
buffer = 0;
while( buffer != '.' )
	fscanf( pFile, "%c", &buffer );

// Get the log_10 density values
for( i=0; i<NumDen; i++ )
    ReadDouble( pFile, &(pDen[i]) );

fclose( pFile );
}

void CElement::OpenRatesFile( char *szRatesFilename )
{
FILE *pFile;
int i, j;
char buffer[8];

// Allocate arrays to hold the pointers to the rates for each ion
ppIonRate = (double**)malloc( sizeof(double) * Z );
ppRecRate = (double**)malloc( sizeof(double) * Z );

// Open the rates file
pFile = fopen( szRatesFilename, "r" );

// Get the ionisation rates

for( i=0; i<Z; i++ )
{
	// Read the rates into memory
		
	ppIonRate[i] = (double*)malloc( sizeof(double) * NumTemp );
			
	fscanf( pFile, "%s", buffer );
		
	for( j=0; j<NumTemp; j++ )
		ReadDouble( pFile, &(ppIonRate[i][j]) );
}

// Get the recombination rates

for( i=0; i<Z; i++ )
{
	// Read the rates into memory
	
	ppRecRate[i] = (double*)malloc( sizeof(double) * NumTemp );

	fscanf( pFile, "%s", buffer );
		
	for( j=0; j<NumTemp; j++ )
		ReadDouble( pFile, &(ppRecRate[i][j]) );
}

fclose( pFile );
}

void CElement::OpenIonFracFile( char *szIonFracFilename )
{
FILE *pFile;
double fTemp;
int i, j;

// Allocate arrays to hold the pointers to the fractional populations for each ion
ppIonFrac = (double**)malloc( sizeof(double) * ( Z + 1 ) );

// Allocate an array for each ion to contain the fractional population of that ion as
// a function of temperature
for( i=0; i<=Z; i++ )
	ppIonFrac[i] = (double*)malloc( sizeof(double) * NumTemp );

pFile = fopen( szIonFracFilename, "r" );

// Get the fractional populations

for( i=0; i<NumTemp; i++ )
{
	// Read the log10 temperature value
    ReadDouble( pFile, &fTemp );

	for( j=0; j<=Z; j++ )
	        ReadDouble( pFile, &(ppIonFrac[j][i]) );
}

fclose( pFile );
}

void CElement::FreeAll( void )
{
int i;

free( pTemp );
free( pDen );

for( i=0; i<Z; i++ )
{
	free( ppIonRate[i] );
	free( ppRecRate[i] );
}

for( i=0; i<=Z; i++ )
	free( ppIonFrac[i] );

free( ppIonRate );
free( ppRecRate );
free( ppIonFrac );
}

void CElement::GetRates( int iIon, double flog_10T, double *pfIonRate, double *pfRecRate )
{
double x[5], Ion_y[5], Rec_y[5], error;
int i, j;

if( !iIon || iIon > Z )
{
	*pfIonRate = 0.0;
	*pfRecRate = 0.0;

	return;
}

// Select the required ion
i = iIon - 1;

// Select the four temperature values, ionisation and recombination rates surrounding 
// the desired one

// If the temperature is out of range then return
if( flog_10T < pTemp[0] || flog_10T > pTemp[NumTemp-1] ) return;

for( j=0; j<NumTemp; j++ )
	if( pTemp[j] >= flog_10T ) break;

// Deal with the special cases where there aren't two values either side of the
// desired one
if( j < 2 ) j = 2;
else if( j == NumTemp-1 ) j = NumTemp-2;

x[1] = pTemp[j-2];
x[2] = pTemp[j-1];
x[3] = pTemp[j];
x[4] = pTemp[j+1];

Ion_y[1] = ppIonRate[i][j-2];
Ion_y[2] = ppIonRate[i][j-1];
Ion_y[3] = ppIonRate[i][j];
Ion_y[4] = ppIonRate[i][j+1];

Rec_y[1] = ppRecRate[i][j-2];
Rec_y[2] = ppRecRate[i][j-1];
Rec_y[3] = ppRecRate[i][j];
Rec_y[4] = ppRecRate[i][j+1];

// Perform the polynomial interpolation
FitPolynomial( x, Ion_y, 4, flog_10T, pfIonRate, &error );
FitPolynomial( x, Rec_y, 4, flog_10T, pfRecRate, &error );

// Check rates are physically realistic
if( *pfIonRate < 0.0 ) *pfIonRate = 0.0;
if( *pfRecRate < 0.0 ) *pfRecRate = 0.0;
}

double CElement::GetEquilIonFrac( int iIon, double flog_10T )
{
double x[5], y[5], IonFrac, error;
int i, j;

if( !iIon || iIon > Z+1 )
	return 0.0;

// Select the required ion
i = iIon - 1;

// Select the four temperature values and fractional populations surrounding
// the desired one

// If the temperature is out of range then return 0.0
if( flog_10T < pTemp[0] || flog_10T > pTemp[NumTemp-1] ) return 0.0;

for( j=0; j<NumTemp; j++ )
	if( pTemp[j] >= flog_10T ) break;

// Deal with the special cases where there aren't two values either side of the
// desired one
if( j < 2 ) j = 2;
else if( j == NumTemp-1 ) j = NumTemp-2;

x[1] = pTemp[j-2];
x[2] = pTemp[j-1];
x[3] = pTemp[j];
x[4] = pTemp[j+1];

y[1] = ppIonFrac[i][j-2];
y[2] = ppIonFrac[i][j-1];
y[3] = ppIonFrac[i][j];
y[4] = ppIonFrac[i][j+1];

// Perform the polynomial interpolation
FitPolynomial( x, y, 4, flog_10T, &IonFrac, &error );

#ifdef ZERO_BELOW_CUTOFF

// Ensure the minimum ion fraction remains above the cut-off and is physically realistic
if( IonFrac < CUTOFF_ION_FRACTION )
	IonFrac = 0.0;

#else // ZERO_BELOW_CUTOFF

// Ensure the ion fraction is physically realistic
if( IonFrac < 0.0 )
	IonFrac = 0.0;

#endif // ZERO_BELOW_CUTOFF

return IonFrac;
}

void CElement::Getdnibydt( double flog_10T, double flog_10n, double *pni, double *pdnibydt, double *pTimeScale )
{
double ne, IonRate[2], RecRate[2], term2, term3, term4, term5, delta_t1, delta_t2, TimeScale, SmallestTimeScale;
int iIndex, iSpecNum;

// Calculate the electron number density
ne = pow( 10.0, flog_10n );

// Initialise the characteristic time-scales
TimeScale = SmallestTimeScale = LONG_TIME_SCALE;

#ifdef EQUIL_ABOVE_MAX_OPTICALLY_THIN_DENSITY

if( flog_10n >= MAX_OPTICALLY_THIN_DENSITY )
	for( iIndex=0; iIndex<=Z; iIndex++ )
    {
		pni[iIndex] = GetEquilIonFrac( iIndex+1, flog_10T );
        pdnibydt[iIndex] = 0.0;
    }
else

#endif // EQUIL_ABOVE_MAX_OPTICALLY_THIN_DENSITY

for( iIndex=0; iIndex<=Z; iIndex++ )
{
	// Reset the rates
    IonRate[0] = IonRate[1] = 0.0;
    RecRate[0] = RecRate[1] = 0.0;

    iSpecNum = iIndex + 1;

	if( iSpecNum > 1 )
	{
        GetRates( iSpecNum-1, flog_10T, &IonRate[0], &RecRate[0] );
        term2 = pni[iIndex-1] * IonRate[0];
    }
	else
        term2 = 0.0;
	
	if( iSpecNum < Z+1 )
	{
        GetRates( iSpecNum, flog_10T, &IonRate[1], &RecRate[1] );
		term3 = pni[iIndex+1] * RecRate[1];
	}
	else
        term3 = 0.0;
	
	term4 = - pni[iIndex] * ( IonRate[1] + RecRate[0] );

	term5 = ne * ( term2 + term3 + term4 );

	pdnibydt[iIndex] = term5;

#ifdef ATOMIC_TIME_SCALE
	if( term5 && pni[iIndex] > CUTOFF_ION_FRACTION )
	{
		term5 = fabs( term5 );

		// epsilon_d = 0.1;
		delta_t1 = SAFETY_ATOMIC * ( 0.1 / term5 );

		// epsilon_r = 0.6
		// |(10^-epsilon_r - 1.0)| = 0.748811357
		// 10^epsilon_r - 1.0 = 2.981071706
		// 0.748811357 + 2.981071706 = 3.729883062
		// 0.5 * 3.729883062 = 1.864941531
		delta_t2 = SAFETY_ATOMIC * 1.864941531 * ( pni[iIndex] / term5 );

		TimeScale = min( delta_t1, delta_t2 );
	}
	else
		TimeScale = LONG_TIME_SCALE;

	if( TimeScale < SmallestTimeScale )
		SmallestTimeScale = TimeScale;
#endif // ATOMIC_TIME_SCALE
}

*pTimeScale = SmallestTimeScale;
}
