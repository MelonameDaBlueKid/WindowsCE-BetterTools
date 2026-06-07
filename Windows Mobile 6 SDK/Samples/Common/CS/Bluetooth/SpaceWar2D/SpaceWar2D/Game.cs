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


    class Game
    {
        /// <summary>
        /// The maximum game coordinate.  The minimum is -MaxPosition.
        /// </summary>
        public const int MaxPosition = 1 << 24;

        private Ship friendlyShip;
        private Ship enemyShip;
        
        /// <summary>
        /// Info about how and where to draw the game.
        /// </summary>
        private DrawingInfo draw;

        public Game()
        {
            // Create the two ships
            friendlyShip = new Ship(new Vector(MaxPosition/2, 0));
            enemyShip    = new Ship(new Vector(-MaxPosition / 2, 0));
            friendlyShip.OtherShip = EnemyShip;
            enemyShip.OtherShip = FriendlyShip;
        }

        public Ship FriendlyShip
        {
            get { return friendlyShip; }
        }

        public Ship EnemyShip
        {
            get { return enemyShip; }
        }

        public void Update(int ticks)
        {
            friendlyShip.Update(ticks);
            // We don't update the enemy ship.  Its updates comes across the
            // Bluetooth stream.
        }

        public void Paint(Graphics g)
        {
            // Fill in any areas outside the square
            draw.BackBuffer.Clear(Color.Gray);
            // Fill the square with the blackness of space
            draw.BackBuffer.FillRectangle(draw.BlackBrush, draw.Square);

            // Draw enemy's score
            draw.BackBuffer.DrawString(FriendlyShip.DamageCount.ToString(),
                                       draw.Font,
                                       draw.GrayBrush,
                                       draw.Width / 8,
                                       2);

            // Draw friendly's score
            draw.BackBuffer.DrawString(EnemyShip.DamageCount.ToString(),
                                       draw.Font,
                                       draw.GrayBrush,
                                       draw.Width * 7 / 8,
                                       2);

            // Draw Sun
            draw.BackBuffer.FillEllipse(draw.YellowBrush,
                                        draw.GameToScreenX(-Game.MaxPosition / 40),
                                        draw.GameToScreenY(-Game.MaxPosition / 40),
                                        (Game.MaxPosition / 20) / draw.ScaleFactor, 
                                        (Game.MaxPosition / 20) / draw.ScaleFactor );

            // Draw ships
            FriendlyShip.Paint();
            EnemyShip.Paint();

            // Blt the backing buffer to the screen
            g.DrawImage(draw.Bitmap, 0, 0);
         }


        /// <summary>
        /// Tells the game the size of the window that it will draw into.
        /// </summary>
        /// <param name="width">Width of the window, in pixels.</param>
        /// <param name="height">Height of the window, in pixels.</param>
        public void SetWindowSize(int width, int height)
        {
            draw = new DrawingInfo(width, height);
            
            // Pass along the drawing info to the ships.
            FriendlyShip.Draw = draw;
            EnemyShip.Draw = draw;
        }
           
    }
}
