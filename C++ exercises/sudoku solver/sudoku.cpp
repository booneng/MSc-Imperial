#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

/*function to check if board is complete*/
bool is_complete(const char board[9][9])
{
  /*define indexes for the for loops*/
  int i,j;
  for( i=0 ; i<9 ; i++)
    {
      for (j=0 ; j<9 ; j++)
	{
	  /*return false if a non-digit is found*/
	  if (!isdigit(board[i][j]))
	    return false;
	}
    }
  /*return true if no non-digits found*/
  return true;
}

/*function to make a move*/
bool make_move(const char position[2], const char digit,char board[9][9])
{
  int row, column;
  int i,j;
  int boxrow, boxcol;
  row = position[0] - 65;
  column = position[1] - 49;
  /*check if position is out of bounds*/
  if (row<0 || column<0 || row>8 || column>8)
    return false;
  /* check row for same digit*/
  for (i=0; i<9 ; i++)
    {
      if (board[row][i] == digit && i!=column)
	return false;
    }
  /*check column for same digit*/
  for (i=0; i<9 ; i++)
    {
      if (board[i][column] == digit && i!=row)
	return false;
    }
  /*check box for same digit */
  /*set boxrow and boxcol to be first element of box*/
  boxrow = (row/3)*3;
  boxcol = (column/3)*3;
  for (i=boxrow; i<boxrow+3; i++)
    {
      for (j=boxcol; j<boxcol+3; j++)
	{
	  if (board[i][j] == digit && i!=row && j!=column)
	    return false;
	}
    }
  board[row][column] = digit;
  return true;
}	   

/*function to save board*/
bool save_board(const char *filename, const char board[9][9])
{
  ofstream out(filename);
  int row = 0;
  if (!out)
    cout << "Failed!" << endl;
  assert(out);
  /*copy elements of board to out*/
  while (out && row<9)
    {
      for (int n=0; n<9 ; n++)
	{
	  out << board[row][n];
	}
      row++;
      out << endl;
    }
  out.close();
  /*make sure it has gone through all rows*/
  return (row == 9) ? true:false;
}

/*function to solve board*/
bool solve_board(char board[9][9])
{
  /*check if board is complete*/
  if (is_complete(board))
    return true;
  /*check through all positions where there is only one possible value first*/
  for(int i=0; i<9; i++)
    {
      for(int j=0; j<9; j++)
	{
	  if (!isdigit(board[i][j]))
	    {
	      char position[2];
	      position[0] = i+65;
	      position[1] = j+49;
	      for(char k='1'; k<='9'; k++)
		{
		  /*if a move is possible, check if another digit works*/
		  if (make_move(position, k, board))
		    {
		      for (char m=k+1; m<='9'; m++)
			{
			  /*if another digit works set it back to '.' and break out of loop*/
			  if (make_move(position, m, board))
			    {
			      board[i][j] = '.';
			      break;
			    }
			}
		      break;
		    }
		}
	      /*if digit does not work, set it back to '.' and return false*/
	      if (isdigit(board[i][j]) && !solve_board(board))
		{
		  board[i][j] = '.';
		  return false;
		}
	    }
	}
    }

  /*now check through each box with each possible digit*/
  for (int i=0; i<9; i++)
    {
      for(int j=0; j<9; j++)
	{
	  if (!isdigit(board[i][j]))
	    {
	      char position[2];
	      /*change position to corresponding char for input into make_move*/
	      position[0] = i+65;
	      position[1] = j+49;
	      /*run a for loop for all possible digits*/
	      for (char k='1'; k<='9'; k++)
		{
		  if (make_move(position,k,board))
		    {
		      /* check if the move works*/
		      /*if it works, return true if not set it back to '.'*/
		      if (solve_board(board))
			return true;
		      else
			board[i][j] = '.';
		    }
		}
	      /*if board[i][j] is still not a digit, no moves are possible so return false*/
	      if (!isdigit(board[i][j]))
		  return false;	
	    }
	}
    }
  /*if function completes for loops without exiting, return true*/
  return true;
}

/*solve_board function that counts the number of recursions*/
bool solve_board(char board[9][9], int &recursions)
{
  recursions++;
  if(is_complete(board))
    return true;
  for(int i=0; i<9; i++)
    {
      for(int j=0; j<9; j++)
	{
	  if (!isdigit(board[i][j]))
	    {
	      char position[2];
	      position[0] = i+65;
	      position[1] = j+49;
	      for(char k='1'; k<='9'; k++)
		{
		  if (make_move(position, k, board))
		    {
		      for (char m=k+1; m<='9'; m++)
			{
			  if (make_move(position, m, board))
			    {
			      board[i][j] = '.';
			      break;
			    }
			}
		      break;
		    }
		}
	      if (isdigit(board[i][j]) && !solve_board(board, recursions))
		{
		  board[i][j] = '.';
		  return false;
		}
	    }
	}
    }
		    
  for(int i=0; i<9; i++)
    {
      for (int j=0; j<9; j++)
	{
	  if(!isdigit(board[i][j]))
	    {
	      char position[2];
	      position[0] = i+65;
	      position[1] = j+49;
	      for(char k='1'; k<='9'; k++)
		{
		  if (make_move(position, k, board))
		    {
		      if (solve_board(board, recursions))
			return true;
		      else
			board[i][j] = '.';
		    }
		}
	      if (!isdigit(board[i][j]))
		return false;
	    }
	}
    }
  return true;
}
