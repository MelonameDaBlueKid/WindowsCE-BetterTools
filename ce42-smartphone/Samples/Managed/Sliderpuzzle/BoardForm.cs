/*=====================================================================
  File:      BoardForm.cs

  
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
using System.Drawing;
using System.Collections;
using System.Windows.Forms;

namespace SliderPuzzle
{
	/// <summary>
	/// Puzzle board form window. Owns the puzzle model and holds the tile
	/// controls that represent the view of the puzzle. Handles resizing of
	/// tile controls when board is resized. Processes keypresses to handle
	/// arrow key support.
	/// </summary>
	public class BoardForm : System.Windows.Forms.Form
	{
		/// <summary>
		/// Main menu tree.
		/// </summary>
		private System.Windows.Forms.MainMenu BoardFormMenu;
        
		/// <summary>
		/// Tray to hold game tiles.
		/// </summary>
		private System.Windows.Forms.Panel m_TileTray;

		/// <summary>
		/// Full source image, read from SliderPuzzle.jpg (or null if file
		/// is not found).
		/// </summary>
		private String m_SourceImageFileName = "SliderPuzzle.jpg";
		private Image  m_SourceImage;

		/// <summary>
		/// The optional puzzle image that appears in mosaic on the puzzle
		/// tiles. If null, tiles have a solid background color.
		/// </summary>
		private Image m_PuzzleImage;
		private Brush m_FillBrush;
        
		/// <summary>
		/// If true, tiles should show their identity, that is, their position,
		/// left-to-right, top-to-bottom in solved order. Upper-left is position
		/// is 0 and is assumed to be empty in the solved configuration.
		/// </summary>
		private bool  m_LabelTiles = false;
		private Font  m_LabelFont;
		private Brush m_LabelBrush;
    
		/// <summary>
		/// Collection of board tiles indexed by their "solved" position
		/// on the board (left-to-right, top-to-bottom).
		/// </summary>
		private SliderPuzzle.Tile[] m_Tiles;

		/// <summary>
		/// Width and Height in pixels of the board tiles. Depends on the size
		/// of the form client area.
		/// </summary>
		private int m_TileSize = 0;
		private System.Windows.Forms.MenuItem OptionsMenu;
		private System.Windows.Forms.MenuItem Options5x5;
		private System.Windows.Forms.MenuItem Options3x3;
		private System.Windows.Forms.MenuItem GameNew;
		private System.Windows.Forms.MenuItem GameExit;
		private System.Windows.Forms.MenuItem GameSolve;

		/// <summary>
		/// Model of puzzle board
		/// </summary>
		private SliderPuzzle.Puzzle m_ThePuzzle;

		public BoardForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			// Load the source image from the file system:
			try
			{
				String CodePath =
					System.Reflection.Assembly.GetExecutingAssembly().GetName().CodeBase;

				CodePath = CodePath.Substring(0, CodePath.LastIndexOf(@"\"));
                
				m_SourceImageFileName =
					CodePath + @"\" + m_SourceImageFileName;
                
				m_SourceImage = new Bitmap(m_SourceImageFileName);
			}
			catch ( System.IO.IOException )
			{
				m_SourceImage = null;
			}

			// Biggie size the label font:
			m_LabelFont  = new System.Drawing.Font("Verdana", 24F, FontStyle.Regular);
			m_LabelBrush = new System.Drawing.SolidBrush(Color.AliceBlue);
			m_FillBrush  = new System.Drawing.SolidBrush(Color.LightGray);

			// Create a model of the puzzle board of the default dimension:
			m_ThePuzzle = new Puzzle(Puzzle.DefaultDimension);
		//	Options4x4.Checked = true;

			CreateTiles();
			SyncBoardView(Tile.Animate.None, true);
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.BoardFormMenu = new System.Windows.Forms.MainMenu();
			this.GameExit = new System.Windows.Forms.MenuItem();
			this.OptionsMenu = new System.Windows.Forms.MenuItem();
			this.Options3x3 = new System.Windows.Forms.MenuItem();
			this.Options5x5 = new System.Windows.Forms.MenuItem();
			this.GameNew = new System.Windows.Forms.MenuItem();
			this.GameSolve = new System.Windows.Forms.MenuItem();
			this.m_TileTray = new System.Windows.Forms.Panel();
			// 
			// BoardFormMenu
			// 
			this.BoardFormMenu.MenuItems.Add(this.GameExit);
			this.BoardFormMenu.MenuItems.Add(this.OptionsMenu);
			// 
			// GameExit
			// 
			this.GameExit.Text = "Exit";
			this.GameExit.Click += new System.EventHandler(this.GameExit_Click);
			// 
			// OptionsMenu
			// 
			this.OptionsMenu.MenuItems.Add(this.Options3x3);
			this.OptionsMenu.MenuItems.Add(this.Options5x5);
			this.OptionsMenu.MenuItems.Add(this.GameNew);
			this.OptionsMenu.MenuItems.Add(this.GameSolve);
			this.OptionsMenu.Text = "Options";
			// 
			// Options3x3
			// 
			this.Options3x3.Text = "3x3";
			this.Options3x3.Click += new System.EventHandler(this.Options3x3_Click);
			// 
			// Options5x5
			// 
			this.Options5x5.Text = "5x5";
			this.Options5x5.Click += new System.EventHandler(this.Options5x5_Click);
			// 
			// GameNew
			// 
			this.GameNew.Text = "New";
			this.GameNew.Click += new System.EventHandler(this.GameNew_Click);
			// 
			// GameSolve
			// 
			this.GameSolve.Text = "Solve";
			this.GameSolve.Click += new System.EventHandler(this.GameSolve_Click);
			// 
			// m_TileTray
			// 
			this.m_TileTray.BackColor = System.Drawing.Color.White;
			this.m_TileTray.Size = new System.Drawing.Size(188, 208);
			// 
			// BoardForm
			// 
			this.BackColor = System.Drawing.Color.FromArgb(((System.Byte)(64)), ((System.Byte)(64)), ((System.Byte)(64)));
			this.Controls.Add(this.m_TileTray);
			this.Menu = this.BoardFormMenu;
			this.Text = "Slider Puzzle";
			this.Resize += new System.EventHandler(this.BoardForm_Resize);
			this.Load += new System.EventHandler(this.BoardForm_Load);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>

		static void Main() 
		{
			Application.Run(new BoardForm());
		}

		/// <summary>
		/// If true, label the tiles with their position in solved order.
		/// </summary>
		public bool LabelTiles
		{
			get { return m_LabelTiles; }
			set
			{
				if ( m_LabelTiles != value )
				{
					m_LabelTiles = value;
					SyncBoardView(Tile.Animate.None, true);
				}

			//	this.OptionsShowLabels.Checked = value;
			}
		}

		/// <summary>
		/// The file name of the source image to be diced up into the puzzle mosaic.
		/// </summary>
		public String PuzzleImage
		{
			get { return m_SourceImageFileName; }
			set
			{
				if ( m_SourceImageFileName != value )
				{
					Image si = null;

					// Load the new source image from the file system:
					try
					{ si = new Bitmap(value); }
					catch ( ArgumentException )
					{ return; }
					catch ( System.IO.IOException )
					{ return; }

					m_SourceImageFileName = value;
					m_SourceImage = si;
					SyncBoardView(Tile.Animate.None, true);
				}
			}
		}

		public int PuzzleDimension
		{
			get { return m_ThePuzzle.Dimension; }
			set
			{
				if ( m_ThePuzzle.Dimension != value )
				{
					// Modify puzzle model dimension, but if we can't set the
					// model dimension, there is nothing left to do here, so
					// bail on argument exceptions:
					try
					{ m_ThePuzzle.Dimension = (ushort) value; }
					catch ( ArgumentException )
					{ return; }

					// Make menu reflect new PuzzleDimension setting. Each menu
					// item Checked property is set or cleared based on new
					// PuzzleDimension property value:
					Options3x3.Checked = (value == 3);
			//		Options4x4.Checked = (value == 4);
				//	Options5x5.Checked = (value == 5);

					this.m_PuzzleImage = null;

					CreateTiles();
					SyncBoardView(Tile.Animate.None, true);
				}
			}
		}

		/// <summary>
		/// Create puzzle tiles and place them on form.
		/// </summary>
		void CreateTiles()
		{
			int m_TileSize =
				System.Math.Min(ClientSize.Width, ClientSize.Height) / m_ThePuzzle.Dimension;
          
			// Remove any existing tiles:
			if ( m_Tiles != null )
				foreach ( Tile t in m_Tiles )
					this.m_TileTray.Controls.Remove(t);

			// Create a new set of tiles:
			this.m_Tiles = new Tile[m_ThePuzzle.NumberOfSquares-1];

			for ( int tid = 1; tid <= m_ThePuzzle.NumberOfSquares-1; ++tid )
			{
				Tile newTile = new Tile();

				newTile.TileId = tid;
				newTile.Size   = new System.Drawing.Size(m_TileSize, m_TileSize);
                
				newTile.Click +=
					new System.EventHandler(this.Tile_Clicked);
				
				this.m_Tiles[tid-1] = newTile;
				this.m_TileTray.Controls.Add(newTile);
			}
		}

		/// <summary>
		/// Move tiles so that their positions on form match the board model
		/// </summary>
		void SyncBoardView( Tile.Animate animate, bool forceNewImage )
		{
			// Calculate the target tile size given the current client area of
			// the form:

			int newTileSize =
				System.Math.Min(ClientSize.Width, ClientSize.Height)
				/ m_ThePuzzle.Dimension;
            
			// If tiles are the wrong size, resize them and the tile tray they
			// sit in:

			if ( m_TileSize != newTileSize || forceNewImage )
			{
				// Resize the tile tray:
				int newTraySize = newTileSize * m_ThePuzzle.Dimension;
                
				Size s = new Size(newTraySize, newTraySize);
				m_TileTray.Size = s;

				// Resize the puzzle image:
				m_PuzzleImage = new Bitmap(s.Width, s.Height);
				Graphics g = System.Drawing.Graphics.FromImage(m_PuzzleImage);

				// If puzzle source image is available, rescale it into the
				// puzzle image bitmap; otherwise fill with a solid color:
				if ( m_SourceImage != null )
				{
					Rectangle dRect =
						new Rectangle(0, 0, newTraySize, newTraySize);

					Rectangle sRect =
						new Rectangle(0, 0, m_SourceImage.Width, m_SourceImage.Height);
					g.DrawImage(m_SourceImage, dRect, sRect, System.Drawing.GraphicsUnit.Pixel);
				}
				else
					g.FillRectangle(m_FillBrush, 0, 0, s.Width, s.Height);

				// Resize each of the tiles and reset the origin of the tile
				// in the mosaic:

				m_TileSize = newTileSize;
				s.Width = s.Height = newTileSize;
				Point p = new Point(0, 0);
                
				foreach ( Tile t in m_Tiles )
				{
					t.Size = s;
					t.FullImage = m_PuzzleImage;
                    
					p.X = m_TileSize * (t.TileId % m_ThePuzzle.Dimension);
					p.Y = m_TileSize * (t.TileId / m_ThePuzzle.Dimension);
					t.TileOrigin = p;

					if ( m_LabelTiles || m_SourceImage == null )
					{
						p.X += s.Width / 2;
						p.Y += s.Height / 2;

						String labelString = t.TileId.ToString();
						SizeF  labelSize   = g.MeasureString(labelString, m_LabelFont);

						g.DrawString( labelString,
							m_LabelFont,
							m_LabelBrush,
							p.X - (labelSize.Width / 2.0F),
							p.Y - (labelSize.Height / 2.0F) );
					}
				}
			}

			// Clean up the screen before we start sliding tiles around:
			if ( animate != Tile.Animate.None )
				Update();

			// Move each out-of-place tile to its proper location on the board:
			for ( int sqRow = 0; sqRow < m_ThePuzzle.Dimension; ++sqRow )
				for ( int sqCol = 0; sqCol < m_ThePuzzle.Dimension; ++sqCol )
				{
					int tileId = m_ThePuzzle[sqRow, sqCol];

					// Skip the empty square:
					if ( tileId == 0 )
						continue;

					// Compute location in board view of this square:
					Point tileLoc = new Point(m_TileSize * sqCol, m_TileSize * sqRow);

					// Move the tile if necessary:
					Tile tile = m_Tiles[tileId-1];

					if ( tile.Location != tileLoc )
						tile.MoveTo(tileLoc, animate);
				}
		}

		/// <summary>
		/// Respond to clicking on a tile. If tile is free, allow it
		/// to move into empty position; otherwise reject click.
		/// </summary>
        
		private void Tile_Clicked( object sender, EventArgs e )
		{
			Tile theTile = ((Tile)sender);

			if ( m_ThePuzzle.MoveTile(theTile.TileId) )
			{
				SyncBoardView(Tile.Animate.Slow, false);

				if ( m_ThePuzzle.IsSolved() )
				{
					System.Windows.Forms.MessageBox.Show(
						"Congratulations!\nYou solved the puzzle!",
						"Game Over",
						MessageBoxButtons.OK,
						MessageBoxIcon.Asterisk,
						MessageBoxDefaultButton.Button1);
				}
			}
		}
	


		// Handle Navigation Keypresses (for keyboard navigation)
		/// <summary>
		/// Override form's navigation key behavior. Up/down/left/right now
		/// cause tiles to move into the empty square. Tab, return, and escape
		/// do nothing.
		/// </summary>
		protected override void OnKeyDown( KeyEventArgs e )
		{
			Puzzle.Move move = Puzzle.Move.None;

			switch ( e.KeyCode )
			{
				case Keys.Up:
					move = Puzzle.Move.Down;
					break;
				case Keys.Down:
					move = Puzzle.Move.Up;
					break;
				case Keys.Left:
					move = Puzzle.Move.Right;
					break;
				case Keys.Right:
					move = Puzzle.Move.Left;
					break;
				case Keys.Tab:
				case Keys.Return:
				case Keys.Escape:
					// Do nothing when these keys are pressed.
					e.Handled = true;
					break;
			}

			if ( move != Puzzle.Move.None )
			{
				e.Handled = true;

				Puzzle.SquareIndex selectedSquare =
					m_ThePuzzle.EmptySquare + move;
                
				if ( m_ThePuzzle.SquareIsOnBoard(selectedSquare)
					&& m_ThePuzzle.MoveTile(m_ThePuzzle[selectedSquare]) )
				{
					SyncBoardView(Tile.Animate.Slow, false);

					if ( m_ThePuzzle.IsSolved() )
					{
						System.Windows.Forms.MessageBox.Show(
							"Congratulations!\nYou solved the puzzle!",
							"Game Over",
							MessageBoxButtons.OK,
							MessageBoxIcon.Asterisk,
							MessageBoxDefaultButton.Button1);
					}
				}
			}

			base.OnKeyDown(e);
		}

		private void BoardForm_Resize(object sender, System.EventArgs e)
		{
			if ( m_ThePuzzle != null )
				SyncBoardView(Tile.Animate.None, false);
		}

		private void GameNew_Click(object sender, System.EventArgs e)
		{
			m_ThePuzzle.NewGame(m_ThePuzzle.NumberOfSquares * 10);
			SyncBoardView(Tile.Animate.Fast, false);
		}

		private void GameSolve_Click(object sender, System.EventArgs e)
		{
			m_ThePuzzle.Reset();
			SyncBoardView(Tile.Animate.Slow, false);
			m_Tiles[0].Focus();
		}

		private void GameExit_Click(object sender, System.EventArgs e)
		{
			Application.Exit();
		}


		private void Options3x3_Click(object sender, System.EventArgs e)
		{
			PuzzleDimension = 3;
		}

		private void Options4x4_Click(object sender, System.EventArgs e)
		{
			PuzzleDimension = 4;
		}

		private void Options5x5_Click(object sender, System.EventArgs e)
		{
			PuzzleDimension = 5;
		}

	

	

		private void BoardForm_Load(object sender, System.EventArgs e)
		{
		
		}

	
	
	}
}

