//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace SpaceWar2D
{
    /// <summary>
    ///  Information about how to draw the game.
    /// </summary>
    class DrawingInfo
    {
        /// <summary>
        /// The width of the  window that the game will draw itself into.
        /// </summary>
        private int width;

        public int Width
        {
            get { return width; }
        }

        /// <summary>
        /// The height of the  window that the game will draw itself into.
        /// </summary>
        private int height;

        public int Height
        {
            get { return height; }
        }

        private Font font;

        public Font Font
        {
            get { return font; }
        }

 
        /// <summary>
        /// The square that the game will draw itself into.  
        /// May be smaller than the rectangle defined by width and height.
        /// </summary>
        private Rectangle square;

        public Rectangle Square
        {
            get { return square; }
        }

        /// <summary>
        /// The factor to divide by to convert from game coordinates to screen coordinates.
        /// </summary>
        private int scaleFactor;

        public int ScaleFactor
        {
            get { return scaleFactor; }
        }

        private SolidBrush blackBrush = new SolidBrush(Color.Black);

        public SolidBrush BlackBrush
        {
            get { return blackBrush; }
        }

        private SolidBrush yellowBrush = new SolidBrush(Color.Yellow);

        public SolidBrush YellowBrush
        {
            get { return yellowBrush; }
        }

        private SolidBrush grayBrush = new SolidBrush(Color.LightGray);

        public SolidBrush GrayBrush
        {
            get { return grayBrush; }
        }

        private Pen whitePen = new Pen(Color.White);

        public Pen WhitePen
        {
            get { return whitePen; }
        }

        private Pen damagedPen = new Pen(Color.Red);

        public Pen DamagedPen
        {
            get { return damagedPen; }
        }


        /// <summary>
        /// The bitmap of the backing buffer.
        /// </summary>
        private Bitmap bitmap;

        public Bitmap Bitmap
        {
            get { return bitmap; }
        }

        /// <summary>
        /// The backing buffer used for drawing.
        /// </summary>
        private Graphics backBuffer;

        public Graphics BackBuffer
        {
            get { return backBuffer; }
            set { backBuffer = value; }
        }


        /// <summary>
        /// Creates a new instance of a DrawingInfo 
        /// </summary>
        /// <param name="width">The width of the window to draw into.</param>
        /// <param name="height">The height of the window to draw into.</param>
        public DrawingInfo(int width, int height)
        {
            this.width = width;
            this.height = height;
            // Calculate the square that the game will use
            if (this.width < this.height)
            {
                this.square = new Rectangle(0, (this.height - this.width) / 2, this.width, this.width);
            }
            else
            {
                this.square = new Rectangle((this.width - this.height) / 2, 0,
                                        this.height, this.height);
            }

            // Create back buffer
            this.bitmap = new Bitmap(width, height);
            this.backBuffer = Graphics.FromImage(bitmap);

            // Calculate scale factor
            this.scaleFactor = 2 * Game.MaxPosition / this.square.Width;

            this.font = new Font(FontFamily.GenericSansSerif, 7, FontStyle.Regular);
        }

        /// <summary>
        /// Convert a game X-coordinate to a screen coordinate.
        /// </summary>
        /// <param name="d">The game coordinate</param>
        /// <param name="draw">Drawing info</param>
        /// <returns></returns>
        public int GameToScreenX(double d)
        {
            return (((int)Math.Round(d)) / scaleFactor)
                    // account for gray margin
                    + square.Left
                    // account for zero being in the middle of the screen
                    + square.Width / 2;
        }

        /// <summary>
        /// Convert a game Y-coordinate to a screen coordinate.
        /// </summary>
        /// <param name="d">The game coordinate</param>
        /// <param name="draw">Drawing info</param>
        /// <returns></returns>
        public int GameToScreenY(double d)
        {
            return (((int)Math.Round(d)) / scaleFactor)
                   + square.Top
                   + square.Height / 2;
        }
    }

}
