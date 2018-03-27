# Multithreaded Sudoku Solution Validator

A Sudoku puzzle uses a 9 × 9 grid in which each column and row, as well as
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
