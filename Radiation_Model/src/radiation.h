// ****
// *
// * Radiation Class Definition for Radiative Emission Model
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 04/05/2006
// *
// ****


#include "symbols.h"
#include "element.h"


class CRadiation {

	private:
	
	// The number of elements for which ion fractional populations are available
	int NumElements;
	
	// Pointer to an array of pointers of type PELEMENT
	PPELEMENT ppElements;
	
	// Pointer to an array containing each element's atomic number.  The offset
	// of the atomic number corresponds to the offset of the element object in
	// the ppElements array
	int *pZ;
	
	// Function to initialise the radiation object with a set of elements
	void Initialise( char *szFilename, char *atomic_db, double safety_atomic, double cutoff_ion_fraction );

	// Function to free all allocated memory
	void FreeAll( void );
	
	public:

	// Constructor
	CRadiation( char *szFilename, char *atomic_db, double safety_atomic, double cutoff_ion_fraction );
	
	// Destructor
	~CRadiation( void );

    int *pGetAtomicNumbers( int *iNumElements );

	// Function to return the ion fractional populations of a particular element at a 
	// specified temperature in equilibrium
	void GetEquilIonFrac( int iZ, double *pni, double flog_10T );

    // Functions to write either a given set of ion fractional populations or all
	// fractional populations to a data file
    void WriteEquilIonFracToFile( void *pFile, int iZ, double flog_10T );
	void WriteAllEquilIonFracToFile( void *pFile, double flog_10T );

	// Function to normalise the sum total of the ion fractional populations to 1
	void Normalise( int iZ, double *pni, double fTotal );

	// Functions to calculate the rate of change with respect to time of the fractional
	// populations of the ions and the characteristic time-scale
    void Getdnibydt( int iZ, double flog_10T, double flog_10n, double *pni, double *pdnibydt, double *pTimeScale );
    void GetAlldnibydt( double flog_10T, double flog_10n, double **ppni, double **ppdnibydt, double *pTimeScale );

};

typedef CRadiation* PRADIATION;
