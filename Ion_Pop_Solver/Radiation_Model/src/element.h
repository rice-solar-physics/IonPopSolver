// ****
// *
// * Element Class Definition for Radiative Emission Model
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 14/06/2005
// *
// ****


#define CUTOFF_ION_FRACTION	1e-300
#define ZERO_BELOW_CUTOFF

// The maximum (log_10) density above which the plasma is not optically thin
#define MAX_OPTICALLY_THIN_DENSITY 12.0
#define EQUIL_ABOVE_MAX_OPTICALLY_THIN_DENSITY

#define LONG_TIME_SCALE 1e300

#define ATOMIC_TIME_SCALE
#define SAFETY_ATOMIC 0.1


class CElement {

	private:

	// The atomic number of the element
	int Z;

	// The number of ions and their spectroscopic numbers
	int NumIons;
	
	// The number of temperature and density values
	int NumTemp, NumDen;
	
	// The temperature and density values in log_10 form
	double *pTemp, *pDen;
		
	// Pointers to two arrays of pointers.  One points to the total ionisation rate
	// and the other to the total recombination rate of each ion at a specified
	// temperature
	double **ppIonRate, **ppRecRate;
	
	// Pointer to an array of pointers, each pointing to the fractional
	// population of an individual ion at a specified temperature
	double **ppIonFrac;
	
	// Function to open and read the ranges data file
	void OpenRangesFile( char *szRangesFilename );

	// Function to open and read the total ionisation and recombination rates file
	void OpenRatesFile( char *szRatesFilename );

	// Function to open and read the ionisation balance file
	void OpenIonFracFile( char *szIonFracFilename );

	// Function to free all allocated memory
	void FreeAll( void );

	public:
	
	// Constructor
	CElement( int iZ, char *szRangesFilename, char *szRatesFilename, char *szIonFracFilename );
	
	// Destructor
	~CElement( void );

    // Function to initialise the element object
    void Initialise( int iZ, char *szRangesFilename, char *szRatesFilename, char *szIonFracFilename );

	// Function to return the total ionisation and total recombination rate
	// for a particular ion at a specified temperature
	void GetRates( int iIon, double flog_10T, double *pfIonRate, double *pfRecRate );

	// Function to return the fractional population of a particular ion at a 
	// specified temperature in equilibrium
	double GetEquilIonFrac( int iIon, double flog_10T );

	// Function to calculate the rate of change with respect to time of the fractional population of the ions and the characteristic time-scale
	void Getdnibydt( double flog_10T, double flog_10n, double *pni, double *pdnibydt, double *pTimeScale );

};

typedef CElement* PELEMENT;
typedef CElement** PPELEMENT;
