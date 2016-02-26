// ****
// *
// * Radiation Class Function Bodies for Radiative Emission Model
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 04/05/2006
// *
// ****


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "radiation.h"


CRadiation::CRadiation( char *szFilename, double safety_atomic, double cutoff_ion_fraction )
{
Initialise( szFilename, safety_atomic, cutoff_ion_fraction );
}

CRadiation::~CRadiation( void )
{
FreeAll();
}

void CRadiation::Initialise( char *szFilename, double safety_atomic, double cutoff_ion_fraction )
{
FILE *pFile;
char buffer1[16];
char szRangesFilename[256], szRatesFilename[256], szIonFracFilename[256];
int i;

pFile = fopen( szFilename, "r" );

// Get the range definition filename
fscanf( pFile, "%s", buffer1 );
sprintf( szRangesFilename, "Radiation_Model/atomic_data/ranges/%s.rng", buffer1 );

// Get the number of elements from the file
fscanf( pFile, "%i", &NumElements );

// Allocate sufficient memory to hold the pointers to each element object
ppElements = (PPELEMENT)malloc( sizeof( CElement ) * NumElements );

// Allocate sufficient memory to hold the list of atomic numbers
pZ = (int*)malloc( sizeof(int) * NumElements );

for( i=0; i<NumElements; i++ )
{
	// Get the element symbol
	fscanf( pFile, "%s", buffer1 );
	
	// Get the atomic number
	fscanf( pFile, "%i", &(pZ[i]) );
	
	// Construct the filenames
	sprintf( szRatesFilename, "Radiation_Model/atomic_data/rates/%s.rts", buffer1 );
	sprintf( szIonFracFilename, "Radiation_Model/atomic_data/balances/%s.bal", buffer1 );

	// Instantiate each element object
	ppElements[i] = new CElement( pZ[i], szRangesFilename, szRatesFilename, szIonFracFilename, safety_atomic, cutoff_ion_fraction );
}

fclose( pFile );
}

void CRadiation::FreeAll( void )
{
int i;

for( i=0; i<NumElements; i++ )
	delete ppElements[i];
	
free( ppElements );
free( pZ );
}

int* CRadiation::pGetAtomicNumbers( int *iNumElements )
{
*iNumElements = NumElements;
return pZ;
}

void CRadiation::GetEquilIonFrac( int iZ, double *pni, double flog_10T )
{
double fTotal = 0.0;
int i, j;

// Find the required element
for( i=0; i<NumElements; i++ )
	if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

// Get the set of equilibrium ion fractional populations for the specified element

for( j=0; j<=iZ; j++ )
{
	pni[j] = ppElements[i]->GetEquilIonFrac( j+1, flog_10T );
	fTotal += pni[j];
}

// Normalise the sum total of the ion fractional populations to 1
Normalise( iZ, pni, fTotal );
}

void CRadiation::WriteEquilIonFracToFile( void *pFile, int iZ, double flog_10T )
{
int i, j;

// Find the required element
for( i=0; i<NumElements; i++ )
	if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

for( j=0; j<=iZ; j++ )
    fprintf( (FILE*)pFile, "\t%.8e", ppElements[i]->GetEquilIonFrac( j+1, flog_10T ) );

fprintf( (FILE*)pFile, "\n" );
}

void CRadiation::WriteAllEquilIonFracToFile( void *pFile, double flog_10T )
{
int i, j;

for( i=0; i<NumElements; i++ )
{
    fprintf( (FILE*)pFile, "\n%i", pZ[i] );

    for( j=0; j<=pZ[i]; j++ )
	    fprintf( (FILE*)pFile, "\t%.8e", ppElements[i]->GetEquilIonFrac( j+1, flog_10T ) );
}

fprintf( (FILE*)pFile, "\n" );
}

void CRadiation::Normalise( int iZ, double *pni, double fTotal )
{
int i;

for( i=0; i<=iZ; i++ )
	pni[i] = pni[i] / fTotal;
}

void CRadiation::Getdnibydt( int iZ, double flog_10T, double flog_10n, double *pni, double *pdnibydt, double *pTimeScale )
{
int i;

// Find the required element
for( i=0; i<NumElements; i++ )
	if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

ppElements[i]->Getdnibydt( flog_10T, flog_10n, pni, pdnibydt, pTimeScale );
}

void CRadiation::GetAlldnibydt( double flog_10T, double flog_10n, double **ppni, double **ppdnibydt, double *pTimeScale )
{
double TimeScale, SmallestTimeScale;
int i;

SmallestTimeScale = LONG_TIME_SCALE;

for( i=0; i<NumElements; i++ )
{
    ppElements[i]->Getdnibydt( flog_10T, flog_10n, ppni[i], ppdnibydt[i], &TimeScale );

	if( TimeScale < SmallestTimeScale )
		SmallestTimeScale = TimeScale;
}

*pTimeScale = SmallestTimeScale;
}
