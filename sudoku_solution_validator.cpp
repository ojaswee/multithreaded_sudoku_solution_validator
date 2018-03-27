/*A Sudoku puzzle uses a 9 × 9 grid in which each column and row, as well as
each of the nine 3 × 3 sub grids, must contain all of the digits 1 · · · 9.This project consists of designing a multithreaded application that determines whether the solution to
a Sudoku puzzle is valid.

Rules are as follows: 
1) sub grid of 3X3 must contain all of the digits 1 · · · 9.
2) any given row and column cannot have repeated numbers

Program executes in following order
1) First we get an input of grid as txt file
2) validate rows,
3) validate columns and
4) 3X3 sub grid 

If at any point program validation fails, it will terminate. For example if row validation fails, no need to check column and 3X3 sub square validation.

*/

#include <iostream>
#include <random>
#include <fstream>
#include <omp.h>

using namespace std; 

#define NUM_THREADS 8
int grid[9][9];

void printGrid() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << grid[i][j] <<" ";
		}
		cout << endl;
	}
}

//third we validate 3X3 subgrid
void validator_3X3() {
	int temp, count;
	bool isUnique= true; // Initially assume subsquare is unique
	omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				//shift temp to the correct location within the subsquare
				temp = grid[j + (i / 3) * 3][k + (i % 3) * 3];
				count = 0;
				for (int m = 0; m < 3; m++) {
					for (int n = 0; n < 3; n++) {
						// Divided by 3, times three cancels for the row in the next line
						if (grid[m + (i / 3) * 3][n + (i % 3) * 3] == temp) count++;
						if (count > 1) {
							cout << "Subsquare " << i+1 << " is invalid." << endl;
							isUnique = false;
							n = m = k = j = 3; i = 9;
						}
					}
				}
			}
		}
	}
	if (isUnique) {
		cout << "\nThis sodoku is correct\n\n";
	}
}

//second we validate the column
void validator_col() {
	bool isUnique = true;
	omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for
	for (int j = 0; j < 9; j++)
		for (int i = 0; i < 9; i++){
			int temp = grid[i][j];
			for (int k = i + 1; k < 9; k++)
				if (grid[k][j] == temp) {
					cout << "Same digit at " << i + 1 << "," << j + 1
						<< " and " << k + 1 << "," << j + 1  << endl;
					isUnique = false;
					j = 9; i = 9; k = 9;
				}
		}
	if (isUnique) {
		cout << "\nColumn test passed\n";
		validator_3X3();
	}
}

//first we want to validate row
void validator_row() {
	bool isUnique = true;
	omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for 
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			int temp = grid[i][j];
			for (int k = j + 1; k < 9; k++)
				if (grid[i][k] == temp) {
					cout << "Incorrect same digit at " << i + 1 <<","<< j + 1 
						<<" and "<<i+1<<","<<k+1<< endl;
					isUnique = false;
					j = 9; i = 9;
				}
		}
	if (isUnique) {
		cout << "\nRow test passed\n";
		validator_col();
	}
}
//input the txt file
void createGrid() {
	ifstream input ("correct_sudoku.txt"); 
	if (input.is_open()){
		cout << "Given sodoku is: \n";
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				input >> grid[i][j];
		printGrid();
		validator_row();
		//validator_col();
		//validator_3X3();
	}
	else cout << "Unable to open file\n";
}


//Entry point for program execution
void main() {
	createGrid();
	system("pause");
}

