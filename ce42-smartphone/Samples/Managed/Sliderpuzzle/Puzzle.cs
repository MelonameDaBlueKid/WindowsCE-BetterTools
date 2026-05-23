/*=====================================================================
  File:      Puzzle.cs

  
  ---------------------------------------------------------------------
   Copyright (C) Microsoft Corporation.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
=====================================================================*/

using System;

namespace SliderPuzzle
{
    public class Puzzle
    {
        // Default board size:
        public static readonly ushort DefaultDimension = 4;

        // Maximum number of reverse steps NewGame will take to randomize
        // the board configuration starting from the solution:
        public static readonly ushort MaxEntropy = 1000;

        // Rank and file linear dimensions:
        private ushort m_Dimension;

        // Each board square holds a tile id:
        //  1..(m_Dimension**2 - 1) or 0 == empty
        private int[][] m_Squares;

        // Table holding the current square index for each tile:
        private SquareIndex[] m_Tiles;

        // Number of rows and columns on board, Board is always square:
        public ushort Dimension
        {
            get { return m_Dimension; }
            
            set
            {
                if ( value < 2 )
                    throw new ArgumentOutOfRangeException();

                if ( m_Dimension != value )
                {
                    m_Dimension = value;
                    m_Squares   = new int[m_Dimension][];
                    m_Tiles     = new SquareIndex[NumberOfSquares];

                    for ( int i = 0; i < m_Dimension; ++i )
                        m_Squares[i] = new int[m_Dimension];    

                    Reset();
                }
            }
        }

        // Number of squares on board:
        public ushort NumberOfSquares
        {
            get { return (ushort)(Dimension * Dimension); }
        }

        // Board location of the empty square:
        public SquareIndex EmptySquare
        {
            get { return m_Tiles[0]; }
        }

        // Board square index:
        public class SquareIndex
        {
            private int m_Row;
            private int m_Col;

            /// <summary>
            /// Construct a square index given row and column values.
            /// </summary>

            public SquareIndex( int row, int col )
            {
                m_Row = row;
                m_Col = col;
            }

            /// <summary>
            /// Row coordinate accessor.
            /// </summary>

            public int Row
            {
                get { return m_Row; }
                set { m_Row = value; }
            }

            /// <summary>
            /// Column coordinate accessor.
            /// </summary>

            public int Col
            {
                get { return m_Col; }
                set { m_Col = value; }
            }

            /// <summary>
            /// Calculate movement required to get from square a to square b.
            /// </summary>

            public static Move operator -( SquareIndex a, SquareIndex b )
            {
                return new Move(a.m_Row - b.m_Row, a.m_Col - b.m_Col);
            }

            /// <summary>
            /// Apply movement to a square index to get a new square index.
            /// </summary>

            public static SquareIndex operator +( SquareIndex selectedSquare, Move move )
            {
                return new
		    SquareIndex(
			selectedSquare.Row + move.DeltaRow,
			selectedSquare.Col + move.DeltaCol  );
            }
        }

        public class Move
        {
            private int m_dRow;	// row displacement
            private int m_dCol;	// column displacement

            /// <summary>
            /// Construct a movement given row and column displacements.
            /// </summary>

            public Move( int dRow, int dCol )
            {
                m_dRow = dRow;
                m_dCol = dCol;
            }

            /// <summary>
            /// Row displacement accessor.
            /// </summary>

            public int DeltaRow
            {
                get { return m_dRow; }
            }

            /// <summary>
            /// Column displacement accessor.
            /// </summary>

            public int DeltaCol
            {
                get { return m_dCol; }
            }

            /// <summary>
            /// Two moves are equal if their displacements are identical.
            /// </summary>

            public static bool operator ==( Move a, Move b )
            {
                return a.m_dRow == b.m_dRow && a.m_dCol == b.m_dCol;
            }
            /// <summary>
            /// Two moves are equal if their displacements are identical.
            /// </summary>

            public static bool operator !=( Move a, Move b )
            {
                return !(a == b);
            }

            /// <summary>
            /// Produce vector sum of two moves.
            /// </summary>

            public static Move operator +( Move a, Move b )
            {
                return new Move(a.m_dRow + b.m_dRow, a.m_dCol + b.m_dCol);
            }

            /// <summary>
            /// Produce vector difference of two moves.
            /// </summary>

            public static Move operator -( Move a, Move b )
            {
                return new Move(a.m_dRow - b.m_dRow, a.m_dCol - b.m_dCol);
            }

            /// <summary>
            /// Two moves are inverse if their displacements sum to zero.
            /// </summary>

            public bool IsInverse( Move other )
            {
                return (this + other) == Move.None;
            }

            /// <summary>
            /// Generate the inverse of this move
            /// </summary>

            public Move Inverse()
            {
                return Move.None - this;
            }

            /// <summary>
            /// Predefined moves.
            /// </summary>

            public static readonly Move None  = new Move( 0,  0);
            public static readonly Move Up    = new Move(-1,  0);
            public static readonly Move Down  = new Move( 1,  0);
            public static readonly Move Left  = new Move( 0, -1);
            public static readonly Move Right = new Move( 0,  1);
            
            /// <summary>
            /// All possible moves that are orthogonal single steps. That is,
	    /// the list of moves that take a single step either vertically
	    /// or horizontally, but not both at once:
            /// </summary>

            public static readonly Move[]
                OrthogonalSteps =
                    { Move.Up, Move.Down, Move.Left, Move.Right };
        }

        /// <summary>
        /// Construct a puzzle and place tiles in the solved configuration.
        /// </summary>

        public Puzzle( ushort dimension )
        {
            Dimension = dimension;
        }

        /// <summary>
        /// Is specified square on the board.
        /// </summary>

        public bool SquareIsOnBoard( SquareIndex selectedSquare )
        {
            if ( selectedSquare.Row >= 0 && selectedSquare.Row < Dimension
              && selectedSquare.Col >= 0 && selectedSquare.Col < Dimension )
                return true;
            
            return false;
        }

        /// <summary>
        /// Access a board square.
        /// </summary>

        public int this[ SquareIndex selectedSquare ]
        {
            get
            {
                return m_Squares[selectedSquare.Row][selectedSquare.Col];
            }
            set
            {
                m_Squares[selectedSquare.Row][selectedSquare.Col] = value;
                m_Tiles[value] = selectedSquare;
            }
        }

        /// <summary>
        /// Access board by row and column.
        /// </summary>

        public int this[ int row, int col ]
        {
            get
            {
                SquareIndex selectedSquare = new SquareIndex(row, col);
                return this[selectedSquare];
            }
            set 
            {
                SquareIndex selectedSquare = new SquareIndex(row, col);
                this[selectedSquare] = value;
            }
        }

        /// <summary>
        /// Serial board accessor: left-to-right, then top-to-bottom
        /// </summary>

        public int this[ int index ]
        {
            get
            {
                SquareIndex selectedSquare =
                    new SquareIndex(index / Dimension, index % Dimension);

                return this[selectedSquare];
            }
            set
            {
                SquareIndex selectedSquare =
                    new SquareIndex(index / Dimension, index % Dimension);

                this[selectedSquare] = value;
            }
        }

        /// <summary>
        /// Get the current square index of a specific tile
        ///

        public SquareIndex GetSquareIdxOfTile( int tileId )
        {
            return m_Tiles[tileId];
        }

        /// <summary>
        /// Exchange contents of two squares.
        /// </summary>

        public void ExchangeTiles( SquareIndex aSquare, SquareIndex bSquare )
        {
            int tileId = this[aSquare];
            this[aSquare] = this[bSquare];
            this[bSquare] = tileId;
        }

        /// <summary>
        /// Place tiles on board in the "solved" configuration.
        /// </summary>

        public void Reset()
        {
            // Place each tile on its sequentially correct square
            // assuming left-to-right, top-to-bottom order:
            for ( int index = 0; index < NumberOfSquares; ++index )
                this[index] = index;    // tileId is square index
        }

        /// <summary>
        /// Place tiles on board such that resulting configuration is solvable
        /// and that the number of moves required to reach the solution is
        /// proportional to the specified "entropy" value:
        /// </summary>

        public void NewGame( int entropy )
        {
            if ( entropy <= 0 || entropy > MaxEntropy )
                throw new ArgumentOutOfRangeException();

            // Place tiles in solved positions:
            Reset();

            // Randomize the tile positions by "moving" the empty square
            // about the board without retracing steps:

            Random randGen = new Random();
            
            Move lastMove = Move.None;
            Move[] possibleMoves = new Move[Move.OrthogonalSteps.Length];
                
            for ( int e = entropy; e != 0; --e )
            {
                // Find all possible moves from current square that are single
		// orthogonal steps that lead to on-board squares and that do
		// not retrace the last move:

                int maxPossibleMoves = 0;

                for ( int stepIdx = 0; stepIdx < possibleMoves.Length; ++stepIdx )
                {
                    Move possibleMove = Move.OrthogonalSteps[stepIdx];
                    
                    if ( !SquareIsOnBoard(EmptySquare + possibleMove)
                        || possibleMove.IsInverse(lastMove) )
                        continue;

                    possibleMoves[maxPossibleMoves++] = possibleMove;
                }

                // Select a possible move at random and move the empty square:
                Move randomMove =
		    possibleMoves[randGen.Next(0, maxPossibleMoves)];

                ExchangeTiles(EmptySquare + randomMove, EmptySquare);
                
                lastMove = randomMove;
            }
        }

        /// <summary>
        /// Move the specified tile from its current square to the empty square;
        /// returns true if the tile moves, false if tile can't be moved.
        /// </summary>

        public bool MoveTile( int tileId )
        {
            // Can't move the "empty" tile:
            if ( tileId == 0 )
                return false;

            // Find specified tile:
            SquareIndex selectedSquare = m_Tiles[tileId];

            // Calculate required movement from current square
            // to the empty square:
            Move movement = EmptySquare - selectedSquare;

            // See if movement is an orthogonal step:
            foreach ( Move orthogonalStep in Move.OrthogonalSteps )
                if ( movement == orthogonalStep )
                {
                    ExchangeTiles(selectedSquare, EmptySquare);
                    return true;
                }

            // Can't move the tile from the specified square
            // to the empty square in a single orthogonal step:
            return false;
        }

        /// <summary>
        /// Returns true if all tiles are in their reset or "solved" positions.
        /// </summary>

        public bool IsSolved()
        {
            for ( int index = 0; index < NumberOfSquares; ++index )
                if ( index != this[index] )
                    return false;	// Fail if tileId does not equal index
            
            return true;
        }
    }
}
