#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "resourceManagement.h"

void testData( char *testData[], int testDataSize, double budget, int testNumber );

int main( int argc, char *argv[] )
{
  char *testFiles1[] = {
            "./TestCase1/Department-ComputerScience.txt",
            "./TestCase1/Department-Mathematics.txt",
						"./TestCase1/Department-Chemistry.txt",
            "./TestCase1/Department-PhysicsAndAstronomy.txt"};

  char *testFiles2[] = {
            "./TestCase2/Department-DeptA.txt",
            "./TestCase2/Department-DeptB.txt",
						"./TestCase2/Department-DeptC.txt",
            "./TestCase2/Department-DeptD.txt",
            "./TestCase2/Department-DeptE.txt",
						"./TestCase2/Department-DeptF.txt",
            "./TestCase2/Department-DeptG.txt"};
                                                
  int testFilesSize1 = 4;
	int testFilesSize2 = 7;
	double budget1 = 41850.00;
  double budget2 = 27961.10;
	
	if( argc==2 ){
		printNames( );
		if( argv[1][0]=='1' )
			testData( testFiles1, testFilesSize1, budget1, 1 );
		if( argv[1][0]=='2' )
			testData( testFiles1, testFilesSize1,    0.01, 2 );
		if( argv[1][0]=='3' )
			testData( testFiles2, testFilesSize2, budget2, 3 );
		printNames( );
	}	
	else{
		printNames( );
		testData( testFiles1, testFilesSize1, budget1, 1 );
		testData( testFiles1, testFilesSize1,    0.01, 2 );
		testData( testFiles2, testFilesSize2, budget2, 3 );
		printNames( );
	}


    return 0;
}

void testData( char *testData[], int testDataSize, double budget, int testNumber )
{
	char budgetString[21];
  printf( "\n\n------------ START OF TEST #%d ------------\n\n", testNumber );

  //Call ResourceManagement on the inputs 
	sprintf( budgetString, "$%.2lf", budget );
	printf( "TESTING with budget = %20s\n\n", budgetString );
  ResourceManagement( testData, testDataSize, budget );
  printf( "\n" );
  
  printf( "------------ END OF TEST #%d ------------\n", testNumber );
}