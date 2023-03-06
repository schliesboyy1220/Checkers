# Checkers

This code prints a 8x8 grid for a checker board. Instead of White and Black, the pieces are X's and O's.
This game plays against and AI, which is currently on the bottom instead of the top. 
The game takes into account illegal moves, and will not allow the user to select anything other than it's own piece, "o".
The program works by taking the selected user input coordinates, and determining using matrix math whether, based on whether the piece is "x", "o", "Kx", or "Ko" if
the move can be done (ex. regulars cannont move "backwards" or non-diagonal.)
it then runs the move through rules. If valid move, it replaces the piece in the array to give the appearance that it has moved. 
The AI will do the same, instead it will calculate possible moves, attempt the move, then rank how many net spaces it controls. If it can jump, it will create
a separate array of only jump moves and rank those. If moves are equal, it will decide based on left to right.

CHANGES
currenlty, the possible moves for AI will not consider kings. This will be added
there is not home page or undo. If an invalid move is made, it will make you restart the move.
stretch implementations: 
change settings (x on top, make user on top or bottom, turn on or off AI)
user menu
