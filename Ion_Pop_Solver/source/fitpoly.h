// ****
// *
// * Include file for routines from Numerical Recipes in C to perform
// * polynomial interpolation in one and two dimensions. Also contains
// * some of my own functions for linear interpolation and finding
// * maxima and minima
// *
// * Dr. Stephen J. Bradshaw
// *
// * Date last modified: 12/04/2007
// *
// ****


// ** Routine to perform a linear interpolation / extrapolation **
void LinearFit( double xa[], double ya[], double x, double *y );

// ** Routine to calculate the degree N-1 polynomial fit to N data points **
void FitPolynomial( double xa[], double ya[], int n, double x, double *y, double *dy );

// ** Routine to perform a two dimensional interpolation using the above routine **
void FitPolynomial2D( double x1a[], double x2a[], double **ya, int m, int n, double x1, double x2, double *y, double *dy );

// ** Routine to calculate the degree N-1 polynomial fit to N data points for which the result MUST be positive definite **
void FitPolynomial_PositiveDefinite(double xa[], double ya[], int n, double x, double *y, double *dy);

// ** Routine to find the larger of two values **
double max( double a, double b );

// ** Routine to find the smaller of two values **
double min( double a, double b );
