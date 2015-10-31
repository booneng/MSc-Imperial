#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  cout << "====================== Question 1 ======================" << endl << endl;

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  cout << "====================== Question 2 ======================" << endl << endl;

  load_board("easy.dat", board);
  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

	// write more tests
  
  cout << "====================== Question 3 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat",board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;
  
  cout << "====================== Question 4 ======================" << endl << endl;

 load_board("easy.dat", board);
 if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
 cout << endl;

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  } else 
      cout << "A solution cannot be found." << endl;
    cout << endl;  

  cout << "====================== Question 5 ======================" << endl << endl;

  char whichboard[80];
  cout << "Enter board(e.g 'mystery1.dat'): ";
  cin.getline(whichboard,80);
  load_board(whichboard, board);
  int recursions = 0;
  if (solve_board(board, recursions))
    {
      cout << "The board has a solution: " << endl;
      cout << "The number of recursions is " << recursions << endl;
      display_board(board);
    }
  else
    cout << "A solution could not be found" << endl;
  cout << endl;
  return 0;
}
