// Kristina Kolesar
// CS 2305
// Lab 31

#include <iostream>
#include <fstream>                   // For file I/O
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream fin;                      // Logical name of input file
	ofstream fout;                     // Logical name of output file

	if (argc != 3)         // Check to see if pgm was invoked correctly
	{
		// No; print error msg and terminate program
		cerr << "Usage:  " << argv[0] << " InputFileName OutputFileName" << endl;
		exit(EXIT_FAILURE);
	}

	fin.open(argv[1]);     // Attempt to open input file
	if (!fin)              // Was it opened? Check the status of the I/O stream
	{
		// No; print error msg and terminate program
		cerr << "Unable to open input file:  " << argv[1] << endl;
		exit(EXIT_FAILURE);
	}

	fout.open(argv[2]);    // Attempt to open output file
	if (!fout)             // Was it opened? Check the status of the I/O stream
	{
		// No; print error msg and terminate program
		cerr << "Unable to open output file:  " << argv[2] << endl;
		exit(EXIT_FAILURE);
	}

	vector<string> fileNames;
	vector<string>::iterator i;
	string inputLine;
	int f, longest, columns, rows, width;
  
	longest = 0;
	
	// output a horizontal line to the output file
	fout << setfill('-') << setw(60) << '-' << setfill(' ') << endl;
  
	// read in unknown number of filenames from the input file
	while (getline(fin, inputLine))
	{
		// figure out L while doing this
		if(static_cast<int>(inputLine.length()) > longest)
			longest = inputLine.length();
	
		fileNames.push_back(inputLine);
	}

	f = fileNames.size();
	sort(fileNames.begin(), fileNames.end());
	columns = (60-longest)/(longest + 2) + 1;
	rows = f/columns;
	if (f % columns != 0)
		rows +=1;
	columns = f/rows;
	if (f - columns * rows !=0) // increment columns if f does not divide evenly
		columns++;
	
	
	for (int rowCount = 0; rowCount < rows; rowCount++)
	{
		i = fileNames.begin() + rowCount;
		for (int colCount = 0; i < fileNames.end() && colCount < columns; i+=rows, ++colCount)
		{
			if (colCount < columns - 1)
				width = longest + 2;
			else
				width = longest;
			fout << left << setw(width) << *i;
		}
		fout << endl;
	}
	
	// Close the input & output files
	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}

//F = 10
//L = 19
//C = (60-L)/(L + 2) + 1; to determine columns

//assume width of window is 60 ch;

//				60 ch
//<-------------------------------->
//					  <----L------->
//<-----21----><----19---><---20--->

//if doesn't divide evenly, add 1 to row
//Rows = F/C;
//10/2 = 5

//^
//|	0		5 (0+R)		10 (0+2R (0+R+R)
//|	1		6 (1+R)		11 (1+R+R)
//R	2		7 (2+R)		12 (2+R+R)
//|	3		8 (3+R)		13 ( )
//|	4(R-1)	9 (2R-1)
//v

// output 60 hyphens at beginning

// run this by typing "lab31 01.dat my.out" or similar

// rows must be filled maximally left to right! so C = F/R
// if rows would not be filled normally
// only the right most column can be shorter than the others
