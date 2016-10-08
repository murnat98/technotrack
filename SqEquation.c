#include <stdio.h>
#include <math.h>
#include <stdlib.h>


const int INF_ROOTS = -1;
const double EPS = 1E-6;

int welcome ( double *, double *, double * );
int SqEquation ( double, double, double, double * , double * );
int LinearEquation ( double, double, double * );
int PrintRoots ( int, double, double );
int IsZero ( double );


int main()
{
	double a = 0, b = 0, c = 0;
	welcome ( &a, &b, &c );


	double x1 = 0, x2 = 0;
	int nRoots = SqEquation ( a, b, c, &x1, &x2 );


	if ( !PrintRoots ( nRoots, x1, x2 ) )
		return 1;

	return 0;
}

int welcome ( double * a, double * b, double * c )
{
	printf ( "SqEquation v1.0\n" );
	printf ( "Enter a, b, c:\n" );
	scanf ( "%lg%lg%lg", a, b, c );
	return 0;
}

int PrintRoots ( int roots, double x1, double x2 )
{
	switch ( roots )
	{
	case 2:
		printf ( "x1 = %lg\n", x1 );
		printf ( "x2 = %lg\n", x2 );
		break;
	case 1:
		printf ( "x = %lg\n", x1 );
		break;
	case 0:
		printf ( "No roots\n" );
		break;
	case INF_ROOTS:
		printf ( "Infinity roots\n" );
		break;
	default:
		printf ( "Error!!!\nroots = %d\n", roots );	
		return 1;
	}
	return 0;
}

int SqEquation ( double a, double b, double c, double * x1, double * x2 )
{
	if ( IsZero ( a ) )
		return LinearEquation ( b, c, x1 );
	double D = b * b - 4 * a * c;
	if ( D < 0 )
		return 0;
	else
	{
		if ( IsZero ( D ) )
		{
			*x1 = - b / ( 2 * a );
			return 1;	
		}
		if ( D > 0 )
		{
			*x1 = ( -b + sqrt ( D ) ) / ( 2 * a );
			*x2 = ( -b - sqrt ( D ) ) / ( 2 * a );
			return 2;
		}
	}
}
int LinearEquation ( double b, double c, double * x )
{
	if ( IsZero ( b ) && IsZero ( c ) )
		return INF_ROOTS;
	if ( IsZero ( b ) && !IsZero ( c ) )
		return 0;
	if ( !IsZero ( b ) && !IsZero ( c ) )
	{
		*x = -c / b;
		return 1;	
	}
	if ( !IsZero ( b ) && IsZero ( c ) )
	{
		*x = 0;
		return 1;
	}
}
int IsZero ( double a )
{
	if ( fabs ( a ) < EPS )
		return 1;
	else
		return 0;
}
