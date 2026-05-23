/*=====================================================================
  File:      Tile.cs

  
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
using System.Windows.Forms;

namespace SliderPuzzle
{
    public class Tile : System.Windows.Forms.Control
    {
        public enum Animate
        {
            None = 0,
            Slow = 1,
            Fast = 2
        }

        static private System.Drawing.Pen s_ShadowPen =
            new System.Drawing.Pen(Color.DarkGray);

        // Tile id--its sequential position, left-to-right, top-to-bottom in
	// solved position:

        private int       m_TileId;


        // Reference to the full puzzle image:

        private Image     m_FullImage;


        // Used by OnPaint to source this tile's area in the full image:

        private Rectangle m_ImageSrcRect;


        public Tile()
        {
            m_TileId       = -1;
            m_FullImage    = null;
            m_ImageSrcRect = new Rectangle(0, 0, 0, 0);
			this.Enabled = false;
        }

        /// <summary>
        /// Numeric id of this tile
        /// </summary>
        public int TileId
        {
            get { return m_TileId;  }
            set { m_TileId = value; }
        }

        public Image FullImage
        {
            get { return m_FullImage; }
            set
            {
                m_FullImage = value;

                if ( Parent != null )
                    Invalidate();
            }
        }

        /// <summary>
        /// The point of origin of this tile in the full untiled image
        /// </summary>
        public Point TileOrigin
        {
            get { return m_ImageSrcRect.Location; }
            set
            {
                m_ImageSrcRect.Location = value;

                if ( Parent != null )
                    Invalidate();
            }
        }

        /// <summary>
        /// Animate and move this tile from its current screen location
	/// to the newLocation
        /// </summary>
        /// <param name="newLocation">Parent coordinates of destination</param>
        /// <param name="speed">Speed of animation (enum)</param>

        public void MoveTo( System.Drawing.Point newLocation, Animate speed )
        {
            BringToFront();
	    
            if ( speed != Animate.None )
            {
                Point startLoc = Location;
                Point newLoc   = Location;

                int dX = newLocation.X - startLoc.X;
                int dY = newLocation.Y - startLoc.Y;

                for ( int step = 1; step < 10; ++step )
                {
                    int factor = step * step;
                    System.Threading.Thread.Sleep(speed == Animate.Fast ? 1 : 5);

                    newLoc.X = startLoc.X + (dX * factor)/100;
                    newLoc.Y = startLoc.Y + (dY * factor)/100;
                    Location = newLoc;
                    
                    Parent.Update();
                }
            }

            Location = newLocation;
            
            if ( speed != Tile.Animate.None )
                Parent.Update();
        }

        protected override void OnPaint( PaintEventArgs e )
        {
            base.OnPaint(e);

            if ( m_FullImage != null )
	    {
                e.Graphics.DrawImage( m_FullImage,
				      ClientRectangle,
				      m_ImageSrcRect,
				      GraphicsUnit.Pixel );
	    }

            e.Graphics.DrawRectangle(s_ShadowPen, ClientRectangle);

        }

        protected override void OnPaintBackground( PaintEventArgs e )
        {
            if ( m_FullImage == null )
                base.OnPaintBackground(e);
        }
        
        protected override void OnResize( EventArgs e )
        {
            base.OnResize(e);
            m_ImageSrcRect.Size = ClientRectangle.Size;
        }
   }
}
