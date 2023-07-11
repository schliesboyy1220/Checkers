// Checkers.cpp : This file contains the 'main' function. Program execution begins and ends there. 
// remember to initialize arrays inside of the function. I spend hours trying to debug random errors in choosing all because an array was initialized
// outside of the function, and there for if the next array was smaller, it would not overwrite previous data. Initialize to zero
// tips to change: use vectors to make the arrays dynamic (recommended by AI), also replace each x and o with a constant to make it neater.
// latest update -------------------------06-MAR-2023------------------------------------------------------------
// ------------------------------------------v_1.0: Basic - kings do not work, ending not verified---------------
// --------------------------------------DEBUG NOTES---------------------------------------------------------
// game end check has not been verified. Online compiler ended before finishing game.
// does not look at Kx when considering possible moves

// currently, I have removed the implementation that forces the user to jump if they can for the user. reference "jump" and "col/row between"
// need to add condition in which if you can jump, you move-must ** works with AI by ranking jumps as highest score.
// need to add condition in which if you jump and can jump again (double jump), you must (but it promps you to do it and gives you another turn). May be able to use 
// similar functionality as the AI by creating an array of possible jumps. However, it would not consider if double jumping would be a worthy sacrifice if it would 
// be jumped
// need to fix when king jumping. If jumping up when o on top as Ko or jumping down when x as Kx, does not recognize backwards jump, despite allowing it to move (does not remove x or o jumped)
// I should add an implementation that allows you to choose a side (top or bottom) as well as x or o. This would require some matrix math since it is specific


#include <iostream>
#include <limits>
#include <vector>
using namespace std;


int i = 0;
int j = 0;
int diff;
int diffRow;
int rowBetween;
int colBetween;
string O = "_o_|";
string X = "_x_|";
string Blank = "_ _|"; // this and the 2 before can be replaced with a constant Blank or O or X and shorten the code. If you can get this to work. do so
string King_O = "_Ko|";
string King_X = "_Kx|";
string board[11][11];
string prevBoard[11][11];
string Jump;
// Sorc Col, Sorce Row, Dest Col, Dest, Row    x   20 possible moves. use vector here for dynamic array -------------------------------------------
int A;
int B;
int E;
int F;
int canJump;
int error = 0;
bool AITurn = false;
//create a matrix of strings. The strings consist of a "square" with either an "o" or " " to signify an empty square
void setup ()			// startup sequence
{
  for (int j = 2; j <= 9; ++j)	// create vertical rows
    {
      for (int i = 2; i <= 9; ++i)	// create horizontal rows
	{
	  if (j % 2 != 0 && i % 2 != 0 && (j <= 4))	//
	    {
	      // establish checkers starting positions
	      board[i][j] = O;
	      cout << O;	// put "o" for the top team odd
	    }
	  else if (j % 2 == 0 && i % 2 == 0 && (j <= 4))	//
	    {
	      board[i][j] = O;
	      cout << O;	// fill in team 1's even
	    }
	  else if (j % 2 != 0 && i % 2 != 0 && (j >= 7))	//
	    {
	      // establish checkers starting positions
	      board[i][j] = X;
	      cout << X;	// put "x" for the bottom team odd
	    }
	  else if (j % 2 == 0 && i % 2 == 0 && (j >= 7))	//
	    {
	      board[i][j] = X;
	      cout << X;	// fill in team 2's variables even
	    }
	  else
	    {
	      board[i][j] = Blank;
	      cout << Blank;	// fill in "blank spots"
	    }
	}
      cout << "\n";		// go to next line to create board or matrix
    }
}

// function to reprint board when succesful move is done
void updateMatrix ()
{
  //canJump = 0;
  for (int R = 2; R <= 9; ++R)
    {
      for (int C = 2; C <= 9; ++C)
	{
	  cout << board[C][R];
	}
      cout << "\n";		//go to next row to make square
    }
}

// this function creates a copy of the current board when called
void createPrevBoard ()
{
  for (int Rprev = 2; Rprev <= 9; ++Rprev)
    {
      for (int Cprev = 2; Cprev <= 9; ++Cprev)
	{
	  prevBoard[Cprev][Rprev] = board[Cprev][Rprev];
	}
    }
}

// each move is filtered through this function. There are many unique conditions, so it can be rather long. If illegal move, it spits out error and does not move the piece
// this is done instead of an "undo" move. however, if I can figure out a way to utilize "previous board" and make this smaller, I would do it.
void rules ()
{
  error = 0;
  // ex. if jumped and another move, jump again, if on opposite side king-me, illegal move: blocked by piece, non-king cannot move backwards
  if (board[B][A] == Blank)
    {
      cout <<
	"---------illegal move-must select a checker piece-----------------\n";
      error = 1;
    }
  else if (board[B][A] == "")
    {
      cout <<
	"---------illegal move-must select a checker piece-----------------\n";
      error = 1;

      // this may not be necessary if I can get the code at the bottom to work, requiring the inputs to be between 1 and 8
      //----------------------------------------------------------------------------
    }
  else if ((board[B][A] == X || board[B][A] == King_X ) && AITurn == false) // if you select the AI's piece
    {
      cout <<
	"---------illegal move-must select a your own piece-----------------\n";
      error = 1;

      // this may not be necessary if I can get the code at the bottom to work, requiring the inputs to be between 1 and 8
      //----------------------------------------------------------------------------
    }
  else // if piece is a valid selection
    {
      if (board[F][E] == Blank)	// if destination is an unoccupied spot
	{
	  rowBetween = abs (F + B) / 2;	//test example, A = 3, B = 1, E = 5, F = 3; 2
	  colBetween = abs (E + A) / 2;
	  Jump = board[rowBetween][colBetween];	//"Jump" is the value of the space that the player is attempting to jump over
	  diff = E - A;		//column
	  diffRow = F - B;	//test example, A = 3, B = 1, E = 4, F = 1
	  
	  
	  
	  ///----------ILLEGAL MOVES---------------------
	  if (board[B][A] == O && ((F - B) > 2))
	    {			//(F-B)<0 ||else if
	      cout <<
		"-----illegal move-cannot travel more than 2 spaces-----\n";
	      error = 1;
	    }
	  else if (board[B][A] == X && ((E - A) < -2))
	    {			//(E-A)>0 ||
	      cout <<
		"-----illegal move-cannot travel more than 2 spaces-----\n";
	      error = 1;
	    }
	  else if (board[B][A] == X && diff == -2 && Jump == Blank)
	    {
	      cout << "------illegal move-cannot move 2 spaces w/o jump!------\n";	//if "x" team jump is over nothing, give error
	      error = 1;
	    }
	  else if (board[B][A] == O && diff == 2 && Jump == Blank)
	    {			//if "o" team jump is over nothing, give error
	      cout <<
		"------illegal move-cannot move 2 spaces w/o jump!------\n";
	      error = 1;
	    }
	  else if ((diff == 0 && abs (diffRow) > 0)
		   || (diffRow == 0 && abs (diff) > 0))
	    {			//if move is U,D,L,R, gives error
	      cout <<
		"--------illegal move-must move diagonally--------------\n";
	      error = 1;
	    }
	  else if (board[B][A] == King_O && ((F - B) > 2))
	    {			//(F-B)<0 ||
	      cout <<
		"-----illegal move-cannot travel more than 2 spaces-----\n";
	      error = 1;
	    }
	  else if (board[B][A] == King_X && ((E - A) < -2))
	    {			//(E-A)>0 ||
	      cout <<
		"-----illegal move-cannot travel more than 2 spaces-----\n";
	      error = 1;
	    }
	  else if (board[B][A] == King_X && diff == -2 && Jump == Blank)
	    {
	      cout << "------illegal move-cannot move 2 spaces w/o jump!------\n";	//if "x" team jump is over nothing, give error
	      error = 1;
	    }
	  else if (board[B][A] == King_O && diff == 2 && Jump == Blank)
	    {			//if "o" team jump is over nothing, give error
	      cout <<
		"------illegal move-cannot move 2 spaces w/o jump!------\n";
	      error = 1;
	    }
	  else if (board[B][A] == O && (E - A) < 0)
	    {
	      cout << "------illegal move-cannot move backwards!------\n";
	      error = 1;
	    }
	  else if (board[B][A] == X && (A - E) < 0)
	    {
	      cout << "------illegal move-cannot move backwards!------\n";
	      error = 1;
	    }
	  ///-----------FORCED MOVE-----------------
	  else if (board[B][A] == X && abs (diff) == 1 && canJump == 1
		   && board[F][E] == Blank)
	    {			// if the source is x and at attempt to move to a blank spot
	      //(moving 2 or U,D,L,R is already accounted for), while there is a "possible" jump (corners of 3x3 square are surrounded by at least 1 5x5 blank spot to jump),
	      //then it will give an error.
	      cout << "------illegal move-you must jump!------\n";
	      error = 1;
	    }
	  else if (board[B][A] == O && abs (diff) == 1 && canJump == 1
		   && board[F][E] == Blank)
	    {			// if the source is x and at attempt to move to a blank spot
	      //(moving 2 or U,D,L,R is already accounted for), while there is a "possible" jump (corners of 3x3 square are surrounded by at least 1 5x5 blank spot to jump),
	      //then it will give an error.
	      cout << "------illegal move-you must jump!------\n";
	      error = 1;
	    }
	  ///----------SPECIAL MOVES---------------------
	  else if (board[B][A] == O && diff == 2 && (Jump == X || Jump == King_X) && E != 9)
	    {			//if "o" team jump is over other team, remove it
	      board[rowBetween][colBetween] = Blank;
	      board[F][E] = board[B][A];	// if pass, Destination = source
	      board[B][A] = Blank;	// if pass, source = blank
	    }
	  else if (board[B][A] == O && diff == 2 && (Jump == X || Jump == King_X) && (E == 9))
	    {			//if "o" team jump is over other team to end, jump and king me
	      board[rowBetween][colBetween] = Blank;
	      board[F][E] = King_O;	// if pass, Destination = king
	      board[B][A] = Blank;	// if pass, source = blank
	    }
	  else if (board[B][A] == X && diff == -2 && (Jump == O || Jump == King_O) && E != 2)
	    {
	      board[rowBetween][colBetween] = Blank;
	      board[F][E] = board[B][A];	// if pass, Destination = source
	      board[B][A] = Blank;	// if pass, source = blank
	    }
	  else if (board[B][A] == X && diff == -2 && (Jump == O || Jump == King_O) && (E == 2))
	    {			//if "x" team jump is over other team to end, jump and king me
	      board[rowBetween][colBetween] = Blank;	//remove piece
	      board[F][E] = King_X;	// if pass, Destination = king
	      board[B][A] = Blank;	// if pass, source = blank
	    }
	  else if (board[B][A] == King_O && diff == 2 && (Jump == X || Jump == King_X))
	    {			//if "o" team jump is over other team, remove it
	      board[rowBetween][colBetween] = Blank;
	      board[F][E] = board[B][A];	// if pass, Destination = source
	      board[B][A] = Blank;	// if pass, source = blank
	    }
	  else if (board[B][A] == King_X && diff == -2 && (Jump == O || Jump == King_O))
	    {			//if "x" team jump is over other team
	      board[rowBetween][colBetween] = Blank;	// remove piece
	      board[F][E] = board[B][A];	// if pass, Destination = source
	      board[B][A] = Blank;	// if pass, source = blank
	    }
	  else if (board[B][A] == O && (E == 9) && diff != 2)
	    {			//if destination of player 1 is at the bottom, king-me
	      board[F][E] = King_O;
	      board[B][A] = Blank;	// if pass, source = blank
	    }
	  else if (board[B][A] == X && (E == 2) && diff != -2)
	    {			//if source of player 2 is on the bottom, king-me
	      board[F][E] = King_X;
	      board[B][A] = Blank;	// if pass, source = blank
	    }
	  else
	    {
	      board[F][E] = board[B][A];	// if pass, Destination = source
	      board[B][A] = Blank;	// if pass, source = blank
	    }
	}
      else			//occupied space
	{
	  cout <<
	    "-------------illegal move, try again--------------------\n";
	  error = 1;
	}
    }
}


void AItest ()
{
  int spacesCount = 0;
  int Col;
  int Row;
  int highVal = -1000;		// placeholder so that the program can assign a "best move"
  int posMoveIter = 1;		// the index for cycleing thourhg each move to test
  int moveScore[20];		// array of scores for each possible move
  int moveIter;
  int ColGrid = 1;		// index to check all spaces in 5x5 grid around move for column
  int RowGrid = 1;		// index to check all spaces in 5x5 grid around move for row
  int numberOfPossibleMoves = 0;	// length value before replaced with vector. This will be deleted eventually ------------------------------------------
  int possibleJumps[10] = {};	// array of possible jumps to list before assigning scores to them. This is so it knows what to rank the highest (must jump)
  int highValindex = 0;		// index to cycle through each score to evaluate if it is better or worse than the placeholder
  int manIter = 0;		// This may be unnecesary now and only for debugging-----------------------------------------
  int posJmpIter = 1;		// index for cycling though each jump
  int possibleMove[4][20] = {};	// array of all possible moves including 4 elements of Row, Col, Destination Row, Destination Col
  AITurn = true;
  // first, find all pieces that belong to AI, in this case, x. I may eventually allow the user to choose.
  for (Row = 2; Row <= 9; ++Row)
    {
      for (Col = 2; Col <= 9; ++Col)
	{
	  // find valid pieces. "x"
	  if (board[Col][Row] == X)	// this whole section can by copied to an "else if" of Kx with an added RowGrid section since Kx can go up or down-----------------------------------
	    {			// current check belongs to AI

	      // now that it found its piece, it looks for valid spaces to move
	      int testIter = 0;	// this may get deleted and only for debug -------------------------------------------------------
	      for (ColGrid = -1; ColGrid < 3; ColGrid = ColGrid + 2)
		{		// does not check spaces below, since it can only move forward if "x"
		  if (board[Col + ColGrid][Row - 1] == O)
		    {
		      // if piece is to the left
		      if (ColGrid < 0 && (board[(Col - 1) + ColGrid][Row - 2] == Blank))	// since there is an opponent on left. check if it can jump
			{	//this is a potential move, store it somewhere to test later
			  possibleMove[0][posMoveIter] = Row;	// [collumn][row]. row is iteration, collumn is data. Type is Source row
			  possibleMove[1][posMoveIter] = Col;	// Type is Source Col
			  possibleMove[2][posMoveIter] = (Row - 2);	//Type is Destination Row
			  possibleMove[3][posMoveIter] = Col + ColGrid - 1;	//Type is Destination collumn
			  possibleJumps[posJmpIter] = posMoveIter;
			  
			  // debug only -------------------------------------------------
			  cout << "\n";
			  cout << possibleMove[0][posMoveIter];	// [collumn][row]. row is iteration, collumn is data. Type is Source row
			  cout << possibleMove[1][posMoveIter];	// Type is Source col
			  cout << possibleMove[2][posMoveIter];	//Type is Destination Row
			  cout << possibleMove[3][posMoveIter];	//Type is Destination Col
			  cout << "\n";
			  // debug only -------------------------------------------------
			  
			  posJmpIter += 1;
			  posMoveIter += 1;	//after storing info, increase the slot for the next possible move


			  //this condition is highest priority, if it can jump, it must. but it can compare between other possibilities                                 
			}	// the else statment just does nothing and leaves if statment. Not a valid move/cannot jump

		      else if (ColGrid >= 0 && (board[(Col + 1) + ColGrid][Row - 2] == Blank))
			{
			  //this is a potential move, store it somewhere to test later
			  possibleMove[0][posMoveIter] = Row;	// [collumn][row]. row is iteration, collumn is data. Type is Source row
			  possibleMove[1][posMoveIter] = Col;	// Type is Source col
			  possibleMove[2][posMoveIter] = (Row - 2);	//Type is Destination Row
			  possibleMove[3][posMoveIter] = Col + ColGrid + 1;	//Type is Destination Col
			  possibleJumps[posJmpIter] = posMoveIter;
			  
			  // debug only -------------------------------------------------
			  //cout << "\n";
			  //cout << possibleMove[0][posMoveIter];	// [collumn][row]. row is iteration, collumn is data. Type is Source row
			  //cout << possibleMove[1][posMoveIter];	// Type is Source col
			  //cout << possibleMove[2][posMoveIter];	//Type is Destination Row
			  //cout << possibleMove[3][posMoveIter];	//Type is Destination Col
			  //cout << "\n";
			  // debug only -------------------------------------------------
			  
			  posJmpIter += 1;
			  posMoveIter += 1;	//after storing info, increase the slot for the next possible move
			  //this condition is highest priority, if it can jump, it must. but it can compare between other jump possibilities

			}	// the else statment just does nothing and leaves if statment. Not a valid move/cannot jump
		      testIter += 1;
		    }
		  // end of possible jump

		  else if (board[Col + ColGrid][Row - 1] == Blank)
		    {
		      //this is a potential move, store it somewhere to test later
		      //cout << "\n"
		      possibleMove[0][posMoveIter] = Row;	// [collumn][row]. row is iteration, collumn is data. Type is Source Col
		      possibleMove[1][posMoveIter] = Col;	// Type is Source Row
		      possibleMove[2][posMoveIter] = (Row - 1);	//Type is Destination Collumn
		      possibleMove[3][posMoveIter] = Col + ColGrid;	//Type is Destination Row
		      
		      // debug only -------------------------------------------------
			  //cout << "\n";
			  //cout << possibleMove[0][posMoveIter];	// [collumn][row]. row is iteration, collumn is data. Type is Source row
			  //cout << possibleMove[1][posMoveIter];	// Type is Source col
			  //cout << possibleMove[2][posMoveIter];	//Type is Destination Row
			  //cout << possibleMove[3][posMoveIter];	//Type is Destination Col
			  //cout << "\n";
			  // debug only -------------------------------------------------
			  
		      posMoveIter += 1;	//after storing info, increase the slot for the next possible move 
		    }
		  else
		    {
		      //not a valid move do nothing. Either off the board or its own piece
		    }
		}		// end of ColGrid for loop
	      //this is after it has looked at a piece, created a 5x5 and computed the spaces count
	    }
	}
    }



  // ---------------------------------------------------------------
// test a move

  for (int moveIter = 1; moveIter < 20; ++moveIter)	//cycle through each element in the possible positions
    {				// need to reset
      createPrevBoard ();	// stores current board in separate memory before changing the board.
      //// --------------------------------
      A = possibleMove[0][moveIter];	//Src row
      B = possibleMove[1][moveIter];	//Src col
      E = possibleMove[2][moveIter];	//Dest row
      F = possibleMove[3][moveIter];	//Dest col

      if (A == 0)
	{
	  numberOfPossibleMoves = moveIter;
	  break;
	}
      rules ();			//execute the move if possible, which are all possible moves. Beware of forced jumps

      //if there are multiple, need to take score+possible jump
      // now that we have the "possible moves" above, we can test each one and assign a rating
      spacesCount = 0;
      for (int RowRate = -2; RowRate < 3; ++RowRate)
	{
	  for (int ColRate = -2; ColRate < 3; ++ColRate)
	    {
	      if (board[F + ColRate][E + RowRate] == X)
		{
		  spacesCount += 1;
		}
	      else if (board[F + ColRate][E + RowRate] == O)
		{
		  spacesCount -= 1;
		}
	      else
		{
		  spacesCount += 0;
		}
	    }
	}
      moveScore[moveIter] = spacesCount;	//Dest col

      
      

      for (int jmpIter = 1; jmpIter <= posJmpIter; ++jmpIter)
	{
	  if (possibleJumps[jmpIter] == moveIter)
	    {
	      moveScore[moveIter] += 1100;
	    }
	}
	// this code above does not seem to rank properly every time. debug ------------------------------------------------
	
	
	// debug only -----------------------------------------------------------
	//cout << moveIter<< "moveiter\n";
    //cout << spacesCount<< "score\n";
    //cout << possibleMove[0][moveIter];	// [collumn][row]. row is iteration, collumn is data. Type is Source row
    //cout << possibleMove[1][moveIter];	// Type is Source col
	//cout << possibleMove[2][moveIter];	//Type is Destination Row
	//cout << possibleMove[3][moveIter];	//Type is Destination Col
	//cout << "\n\n\n";
	// debug only -----------------------------------------------------------
	

      for (int ii = 2; ii <= 9; ++ii)
	{
	  for (int jj = 2; jj <= 9; ++jj)
	    {
	      board[jj][ii] = prevBoard[jj][ii];
	    }
	}
    }
  for (int iii = 1; iii < numberOfPossibleMoves; ++iii)
    {
      if (moveScore[iii] > highVal)
	{
	  highVal = moveScore[iii];
	  highValindex = iii;
	}
    }
  A = possibleMove[0][highValindex];	//Src row
  B = possibleMove[1][highValindex];	//Src col
  E = possibleMove[2][highValindex];	//Dest row
  F = possibleMove[3][highValindex];	//Dest col
  
  // debug only  ------------------------------------------------
  //cout << "\n";
  //cout << A;
  //cout << B;
  //cout << E;
  //cout << F;
  //cout << "\n";
  
  // debug only -------------------------------------------------

  rules ();
  cout << "\n\n\n\n";
  updateMatrix ();
  AITurn = false;
}


int main ()
{
  bool gameRunning = true;

  setup ();			//call the setup function
  while (gameRunning)
    {
      int GameOverCheck_X = 0;	//declares varaible and resets to 0 each move for X count
      int GameOverCheck_O = 0;	//declares variable and resets to 0 each move for O count
      // the following counts the x's and o's to see if either are 0
      for (int RowCheckEnd = 2; RowCheckEnd <= 9; ++RowCheckEnd)
	{
	  for (int ColCheckEnd = 2; ColCheckEnd <= 9; ++ColCheckEnd)
	    {
	      if (board[RowCheckEnd][ColCheckEnd] == X)
		{
		  GameOverCheck_X += 1;
		}
	      else if (board[RowCheckEnd][ColCheckEnd] == O)
		{
		  GameOverCheck_O += 1;

		}
	      //else if (iteration == one that can jump
	      else
		{
		}
	    }
	}

      // if there is either 0 o's or 0 x's, the game will end and break the loop
      if (GameOverCheck_X == 0 || GameOverCheck_O == 0)
	{
	  gameRunning = false;
	  cout << "GameOver!!";
	  break;
	}

      // input the desired piece and where you want to move it to

      cout << "\n";
      cout << "select Row number to move from...\n";
      cin >> A;
      A += 1;
      cout << "select Column number to move from...\n";
      cin >> B;
      B += 1;
      cout << "select Row number to move to...\n";
      cin >> E;
      E += 1;
      cout << "select Column number to move to...\n";
      cin >> F;
      F += 1;
      cout << "\n";


      // if the input is invalid (is a letter or special character), the program will handle the crash and ignore it and continue.
      if (cin.fail ())
	{
	  cout << "Error: Invalid input." << endl;
	  cin.clear ();		// clear the error state
	  cin.ignore (numeric_limits < streamsize >::max (), '\n');	// ignore any additional input
	}

      rules ();			// call rules 
      updateMatrix ();		// update the matrix if successful. This may not need to run unless there is no error, so it could go in the if statment below and it may
      //save processor time?

      // if the user has an error, do not run the AI turn
      if (error != 1)
	{
	  AItest ();
	}
    }
}
