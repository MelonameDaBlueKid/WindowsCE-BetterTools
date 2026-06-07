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
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Net.Sockets;
using Microsoft.WindowsMobile.SharedSource.Bluetooth;

namespace SpaceWar2D
{
    public partial class SpaceWarForm : Form, IGameStateChangeSink
    {
        /// <summary>
        ///  An opcode that is sent across the Bluetooth stream.
        /// </summary>
        enum GameStateChangeOpCode
        {
            Move = 0xF000,
            Damage,
            Thrust,
            Rotate,
            MissileMove,
            MissileGone,
            OtherShipsMissileGone,
            Disconnect,
            DisconnectAcknowledge,
        };
        
        /// <summary>
        /// Manages the Bluetooth connection
        /// </summary>
        ConnectionManager connectionMgr;

        /// <summary>
        /// The entire state of the SpaceWar game
        /// </summary>
        Game game;


        /// <summary>
        /// Is the game paused?
        /// </summary>
        private bool paused = false;

        /// <summary>
        /// The last time the game was updated.
        /// </summary>
        private int lastUpdateTime;

        /// <summary>
        /// Are we about to quit the application?
        /// </summary>
        private bool exitting = false;

        #region Timing instrumentation
#if INSTRUMENT
        private int samplesCount = 0;
        private int samplesTotal = 0;
#endif
        #endregion

        public SpaceWarForm()
        {
            InitializeComponent();
        }
            
        private void SpaceWarForm_Load(object sender, EventArgs e)
        {
            connectionMgr = new ConnectionManager(
                new Guid("{54C12AE8-160C-4422-8550-4900EC1C4ACD}"), 
                new ThreadStart(StreamProcessor));

            game = new Game();
            game.SetWindowSize(this.Size.Width, this.Size.Height);
            lastUpdateTime = Environment.TickCount;
        }

        private void SetMenuToDisconnect(object sender, EventArgs e)
        {
            menuConnect.Text = "Disconnect";
        }

        private void SetMenuToConnect(object sender, EventArgs e)
        {
            menuConnect.Text = "Connect";
        }


        /// <summary>
        /// The callback function that reads and processes data from the 
        /// Bluetooth Stream.  This function starts when a connection is 
        /// established, and ends when the connection goes away.
        /// </summary>
        private void StreamProcessor()
        {
            bool disconnected = false;

            // Now that we are connected, let the user disconnect.
            Invoke(new EventHandler(SetMenuToDisconnect));

            BinaryReader reader = connectionMgr.Reader;
            BinaryWriter writer = connectionMgr.Writer;

            // Set up to receive notifications from the friendly ship.
            game.FriendlyShip.Sink = (IGameStateChangeSink)this;

            // Start processing notifications from the remote enemy ship
            // and forward them to the local enemy ship.
            try
            {
                while (!disconnected)
                {
                    GameStateChangeOpCode change = (GameStateChangeOpCode)reader.ReadInt32();
                    switch (change)
                    {
                        case GameStateChangeOpCode.Damage:
                            game.EnemyShip.OnShipDamage(reader.ReadBoolean());
                            break;

                        case GameStateChangeOpCode.MissileGone:
                            game.EnemyShip.OnMissileGone(reader.ReadInt32());
                            break;

                        case GameStateChangeOpCode.MissileMove:
                            game.EnemyShip.OnMissileMove(reader.ReadInt32(),
                                                         new Vector(reader.ReadInt32(), reader.ReadInt32()));
                            break;

                        case GameStateChangeOpCode.Move:
                            game.EnemyShip.OnShipMove(new Vector(reader.ReadInt32(), reader.ReadInt32()));
                            break;

                        case GameStateChangeOpCode.OtherShipsMissileGone:
                            game.EnemyShip.OnOtherShipsMissileGone(reader.ReadInt32());
                            break;

                        case GameStateChangeOpCode.Rotate:
                            game.EnemyShip.OnShipRotate(reader.ReadInt32());
                            break;

                        case GameStateChangeOpCode.Thrust:
                            game.EnemyShip.OnShipThrust(reader.ReadBoolean());
                            break;

                        case GameStateChangeOpCode.Disconnect:
                            // Ack the disconnect. 
                            writer.Write((int)GameStateChangeOpCode.DisconnectAcknowledge);
                            // Break out of the loop
                            disconnected = true;
                            break;

                        case GameStateChangeOpCode.DisconnectAcknowledge:
                            // Break out of the loop
                            disconnected = true;
                            break;

                        default:
                            throw new Exception("Bad stream opcode");
                    }
                }
            }
            catch (System.IO.EndOfStreamException)
            {
                // Lost the connection.  So, we're disconnected now.
            }

            OnDisconnect();
        }


        /// <summary>
        /// Do the necessary cleanup once there is no more data to be read or 
        /// written, either because the normal disconnect handshake has been 
        /// completed or because of a forced disconnect (a thrown exception).
        /// </summary>
        private void OnDisconnect()
        {
            // Stop receiving notifications from the friendly ship.
            game.FriendlyShip.Sink = null;

            // Disconnect the bluetooth stream
            connectionMgr.Disconnect();

            if (!exitting)
            {
                // Now that we are disconnected, let the user connect again.
                Invoke(new EventHandler(SetMenuToConnect));
            }
        }

        
        #region IGameStateChangeSink
        // These methods implement IGameStateChangeSink, and notify the 
        // remote enemy ship of changes to the state of the game.

        public void OnShipMove(Vector vPos)
        {
            connectionMgr.Writer.Write((int)GameStateChangeOpCode.Move);
            connectionMgr.Writer.Write(vPos.X);
            connectionMgr.Writer.Write(vPos.Y);
            connectionMgr.Writer.Flush();
        }

        public void OnShipDamage(bool isDamaged)
        {
            connectionMgr.Writer.Write((int)GameStateChangeOpCode.Damage);
            connectionMgr.Writer.Write(isDamaged);
            connectionMgr.Writer.Flush();
        }

        public void OnShipThrust(bool isThrusting)
        {
            connectionMgr.Writer.Write((int)GameStateChangeOpCode.Thrust);
            connectionMgr.Writer.Write(isThrusting);
            connectionMgr.Writer.Flush();
        }

        public void OnShipRotate(int rotation)
        {
            connectionMgr.Writer.Write((int)GameStateChangeOpCode.Rotate);
            connectionMgr.Writer.Write(rotation);
            connectionMgr.Writer.Flush();
        }

        public void OnMissileMove(int iMissile, Vector vPos)
        {
            connectionMgr.Writer.Write((int)GameStateChangeOpCode.MissileMove);
            connectionMgr.Writer.Write(iMissile);
            connectionMgr.Writer.Write(vPos.X);
            connectionMgr.Writer.Write(vPos.Y);
            connectionMgr.Writer.Flush();
        }

        public void OnMissileGone(int iMissile)
        {
            connectionMgr.Writer.Write((int)GameStateChangeOpCode.MissileGone);
            connectionMgr.Writer.Write(iMissile);
            connectionMgr.Writer.Flush();
        }

        public void OnOtherShipsMissileGone(int iMissile)
        {
            connectionMgr.Writer.Write((int)GameStateChangeOpCode.OtherShipsMissileGone);
            connectionMgr.Writer.Write(iMissile);
            connectionMgr.Writer.Flush();
        }
        #endregion



        private void menuConnect_Click(object sender, EventArgs e)
        {
            MenuItem menuItem = (MenuItem)sender;
            paused = true;
            if (menuItem.Text == "Connect")
            {
                this.connectionMgr.Connect();
            }
            else
            {
                System.Diagnostics.Debug.Assert(menuItem.Text == "Disconnect");
                Disconnect();
            }
            paused = false;
            // Reset the clock so the game won't have continued while we were paused.
            lastUpdateTime = Environment.TickCount;
        }


        private void Disconnect()
        {
            // Stop receiving notifications from the friendly ship, so we'll
            // immediately stop sending data to the enemy ship.
            game.FriendlyShip.Sink = null;

            if (connectionMgr.Writer != null)
            {
                // Tell the enemy we are disconnecting.
                // This starts the chain of events that disconnects.
                connectionMgr.Writer.Write((int)GameStateChangeOpCode.Disconnect);
            }
        }
        
        protected override void OnPaintBackground(PaintEventArgs e)
        {
            // Do nothing
        }

        [System.Runtime.InteropServices.DllImport("coredll.dll")]
        private static extern void SystemIdleTimerReset(); 

        protected override void OnKeyDown(KeyEventArgs e)
        {
            // Keep screen on.
            SystemIdleTimerReset();

            switch (e.KeyCode)
            {
                case Keys.Left:
                case Keys.D4:
                    game.FriendlyShip.Rotation -= 10;
                    break;

                case Keys.Right:
                case Keys.D6:
                    game.FriendlyShip.Rotation += 10;
                    break;

                case Keys.Down:
                case Keys.D8:
                case Keys.D5:
                    game.FriendlyShip.Thrusting = true;
                    break;

                case Keys.Up:
                case Keys.D2:
                    game.FriendlyShip.LaunchMissile();
                    break;
            }
        }


        protected override void OnKeyUp(KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Down:
                case Keys.D5:
                case Keys.D8:
                    game.FriendlyShip.Thrusting = false;
                    break;
            }
        }


        private void SpaceWarForm_Paint(object sender, PaintEventArgs e)
        {
            int ticksSinceLastTime = 0;

            if (!paused)
            {
                // Update the state of the game
                int now = Environment.TickCount;
                ticksSinceLastTime = now - lastUpdateTime;
                try
                {
                    game.Update(ticksSinceLastTime);
                }
                catch (System.IO.IOException)
                {
                    // Connection was dropped.
                    OnDisconnect();
                }
                lastUpdateTime = now;

                #region Timing instrumentation
#if INSTRUMENT
            samplesCount++;
            samplesTotal += ticksSinceLastTime;
            if (samplesCount % 100 == 0)
            {
                System.Diagnostics.Debug.WriteLine("Average fps = " + 1000 / (samplesTotal / samplesCount));
            }
#endif
                #endregion
            }

            // Paint the game
            game.Paint(e.Graphics);

            if (!paused)
            {
                // This slows down the game so Bluetooth can keep up.
                if (ticksSinceLastTime < 100)
                    System.Threading.Thread.Sleep(100 - ticksSinceLastTime);

                this.Invalidate();
            }
        }


        private void menuExit_Click(object sender, EventArgs e)
        {
            exitting = true;
            connectionMgr.Exit();
            Disconnect();
            while (connectionMgr.Connected)
            {
                Thread.Sleep(200);
            }
            Close();
        }
    }
}