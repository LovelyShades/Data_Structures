#include "department.h"

/* printDepartment
 * input: a pointer to a Department
 * output: none
 *
 * Prints the Department.
 */
void printDepartment( Department *d )
{
  printf( "Department Name = \"%s\"\n", d->name );
	printf( "Total Spent     = $%.2lf\n", d->totalSpent );
	printf( "Items Desired   = " );
	printQueue( d->itemsDesired );
	printf( "Items Received  = " );
	printQueue( d->itemsReceived );
	printf( "Items Removed   = " );
	printQueue( d->itemsRemoved );
	printf( "\n" );
}