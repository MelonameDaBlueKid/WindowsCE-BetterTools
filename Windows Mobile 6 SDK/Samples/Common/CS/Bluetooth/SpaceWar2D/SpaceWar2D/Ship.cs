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
    class Ship : PhysicalObject, IGameStateChangeSink
    {
        /// <summary>
        /// The maximum allowed speed
        /// </summary>
        private const int maxSpeed = 40000;

        /// <summary>
        /// The initial speed of the missile, relative to the ship. 
        /// In other words, the "firing speed" of the missile.
        /// </summary>
        private const int missileRelativeSpeed = 11000;

        /// <summary>
        /// The acceleration the thrusters provide.
        /// </summary>
        private const int thrustAcceleration = 10;

        /// <summary>
        /// The size of the ship
        /// </summary>
        private const int shipRadius = Game.MaxPosition / 20;


        /// <summary>
        /// The maximum number of missiles that can be launched at one time.
        /// </summary>
        private const int maxMissiles = 5;

        /// <summary>
        /// How long the ship stays damaged.
        /// </summary>
        private const int damageLifetime = 2000;

        /// <summary>
        /// The ship's missiles, both launched and unlaunched.
        /// </summary>
        private Missile[] missiles;

        /// <summary>
        /// The other ship.
        /// </summary>
        private Ship otherShip;

        /// <summary>
        /// The sink by which the player's ship notifies the enemy ship of changes.
        /// Will be null if this is an enemy ship.
        /// </summary>
        private IGameStateChangeSink sink;

        /// <summary>
        /// Is the ship damaged?
        /// </summary>
        private bool damaged = false;

        /// <summary>
        /// Is the ship firing its thrusters?
        /// </summary>
        private bool thrusting = false;

        /// <summary>
        /// The direction the ship is pointing.
        /// </summary>
        private int rotation;
                
        /// <summary>
        /// When the damage will be fixed.
        /// </summary>
        private int damageTimeout;

        /// <summary>
        /// The number of times the ship has been damaged.  
        /// In other words, the score.
        /// </summary>
        private int damageCount;

        /// <summary>
        /// Information about how to draw.
        /// </summary>
        private DrawingInfo draw;


        public Ship(Vector vPos) :
            base(vPos, Vector.Null, shipRadius)
        {
            missiles = new Missile[maxMissiles];
            for (int i = 0; i < maxMissiles; i++)
            {
                missiles[i] = new Missile();
            }
        }


        /// <summary>
        /// The number of times the ship has been damaged.  
        /// In other words, the score.
        /// </summary>
        public int DamageCount
        {
            get { return damageCount; }
        }

        /// <summary>
        /// Information about how to draw.
        /// </summary>
        public DrawingInfo Draw
        {
            get { return draw; }
            set { draw = value; }
        }

        /// <summary>
        /// The other ship.
        /// </summary>
        public Ship OtherShip
        {
            get { return otherShip; }
            set { otherShip = value; }
        }

        /// <summary>
        /// The sink by which the friendly ship notifies the enemy of its state.
        /// </summary>
        public IGameStateChangeSink Sink
        {
            get { return sink; }
            set 
            { 
                sink = value;
                if (sink != null)
                {
                    // This means a connection was just established with the 
                    // other ship.

                    // Tell the sink our rotation because otherwise it won't know 
                    // until the next time the ship rotates.
                    sink.OnShipRotate(rotation);
                    // Reset the score.
                    damageCount = 0;
                    otherShip.damageCount = 0;
                }
            }
        }

        /// <summary>
        /// The ship's missiles
        /// </summary>
        public Missile[] Missiles
        {
            get { return missiles; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the ship is firing its thrusters.
        /// </summary>
        public bool Thrusting
        {
            get { return thrusting; }
            set
            {
                if (!Damaged)
                {
                    thrusting = value;
                    if (thrusting)
                    {
                        Acceleration = new Vector((int)(thrustAcceleration * Cos(Rotation)),
                                                  (int)(thrustAcceleration * Sin(Rotation)));
                    }
                    else
                    {
                        Acceleration = Vector.Null;
                    }
                    if (sink != null)
                    {
                        sink.OnShipThrust(thrusting);
                    }
                }
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the ship is damaged.
        /// </summary>
        public bool Damaged
        {
            get { return damaged; }

            set 
            {
                if (damaged == value)
                {
                    // No change
                    return;
                }
                if (value)
                {
                    // Wasn't damaged before, but is now, so start timer.
                    damageTimeout = Environment.TickCount + damageLifetime;
                    // Disable thrusters.
                    thrusting = false;
                    // Keep score.
                    damageCount++;
                }
                damaged = value;
                if (sink != null)
                {
                    sink.OnShipDamage(damaged);
                }
            }
        }

        /// <summary>
        /// Update the ship's state.
        /// </summary>
        /// <param name="ticks">The amount of time that has passed since the last update.</param>
        public new void Update(int ticks)
        {
            // Let PhysicalObject update our position.
            base.Update(ticks);

            // Enforce a speed limit
            Vector v = Velocity;
            if (v.Magnitude > maxSpeed)
            {
                v.SetMagnitude(maxSpeed);
                Velocity = v;
            }

            // Notify the enemy.
            if (sink != null)
            {
                sink.OnShipMove(Position);
            }

            // Check if any damage has been fixed yet.
            if (damaged && Environment.TickCount > damageTimeout)
            {
                Damaged = false;
            }

            // Check if the two ships collided.
            if ((Position - OtherShip.Position).Magnitude < Radius + otherShip.Radius)
            {
                Damaged = true;
            }

            // Update each friendly missile
            for (int i = 0; i < maxMissiles; i++)
            {
                Missile m = missiles[i];
                if (m.Launched)
                {
                    m.Update(ticks);

                    // Notify the enemy.
                    if (sink != null)
                    {
                        sink.OnMissileMove(i, m.Position);
                        m.SinkThinksItIsLaunched = true;
                    }

                    if (m.CheckForCollision(this))
                    {
                        // The ship was hit by its own missile.
                        Damaged = true;
                        if (sink != null)
                        {
                            sink.OnMissileGone(i);
                            m.SinkThinksItIsLaunched = false;
                        }
                    }
                }
                else
                {
                    System.Diagnostics.Debug.Assert(!m.Launched);
                    if (sink != null && m.SinkThinksItIsLaunched)
                    {
                        sink.OnMissileGone(i);
                        m.SinkThinksItIsLaunched = false;
                    }
                }
            }

            // Check enemy missiles
            for (int i = 0; i < maxMissiles; i++)
            {
                Missile m = OtherShip.Missiles[i];
                if (m.Launched)
                {
                    if (m.CheckForCollision(this))
                    {
                        // The friendly ship was hit by an enemy missile.
                        Damaged = true;
                        if (sink != null)
                        {
                            sink.OnOtherShipsMissileGone(i);
                        }
                    }
                }
            }
        }

        public void LaunchMissile()
        {
            if (Damaged)
            {
                return;
            }
            for (int i = 0; i < maxMissiles; i++)
            {
                Missile m = Missiles[i];
                if (!m.Launched)
                {
                    // Found one to launch.

                    // Missile starts off at the tip of the ship's nose.
                    Vector missilePosition = new Vector(Position.X + (int)(Radius * Cos(Rotation) * 1.1),
                                                        Position.Y + (int)(Radius * Sin(Rotation) * 1.1));

                    // Missile's velocity relative to the ship
                    Vector missileRelativeVelocity = new Vector((int)(missileRelativeSpeed * Cos(Rotation)),
                                                                (int)(missileRelativeSpeed * Sin(Rotation)));

                    m.Launch(missilePosition, this.Velocity + missileRelativeVelocity);
                    break;
                }
            }
        }


        /// <summary>
        /// The angle the ship is pointing.
        /// </summary>
        public int Rotation
        {
            get
            {
                return rotation;
            }
            set
            {
                if (!Damaged)
                {
                    rotation = value;
                    if (rotation < 0)
                    {
                        rotation += 360;
                    }
                    else if (rotation >= 360)
                    {
                        rotation -= 360;
                    }
                    if (sink != null)
                    {
                        sink.OnShipRotate(rotation);
                    }
                }
            }
        }



        /// <summary>
        /// Returns the sine of the angle.
        /// </summary>
        /// <param name="angle">The angle in degrees.</param>
        /// <returns></returns>
        private double Sin(int angle)
        {
            return Math.Sin(angle * Math.PI / 180);
        }

        /// <summary>
        /// Returns the cosine of the angle.
        /// </summary>
        /// <param name="angle">The angle in degrees.</param>
        /// <returns></returns>
        private double Cos(int angle)
        {
            return Math.Cos(angle * Math.PI / 180);
        }



        /// <summary>
        /// Paint the ship.
        /// </summary>
        /// <param name="g">The Graphics object.</param>
        public void Paint()
        {
            Point[] pts = new Point[3];
          
            // An arbitary angle that determines the pointy-ness of the ship
            const int shipShapeAngle = 36;

            // Nose
            pts[0].X = Draw.GameToScreenX(Position.X + Radius * Cos(Rotation));
            pts[0].Y = Draw.GameToScreenY(Position.Y + Radius * Sin(Rotation));

            // Left fin
            pts[1].X = Draw.GameToScreenX(Position.X + Radius * Cos(Rotation + 180 + shipShapeAngle));
            pts[1].Y = Draw.GameToScreenY(Position.Y + Radius * Sin(Rotation + 180 + shipShapeAngle));

            // Right fin
            pts[2].X = Draw.GameToScreenX(Position.X + Radius * Cos(Rotation + 180 - shipShapeAngle));
            pts[2].Y = Draw.GameToScreenY(Position.Y + Radius * Sin(Rotation + 180 - shipShapeAngle));
            
            Draw.BackBuffer.DrawPolygon(Damaged ? Draw.DamagedPen : Draw.WhitePen, pts);

            if (Thrusting)
            {
                // Draw the thruster's flame
                Draw.BackBuffer.DrawLine(Draw.WhitePen,
                                        Draw.GameToScreenX(Position.X - Radius * Cos(Rotation)),
                                        Draw.GameToScreenY(Position.Y - Radius * Sin(Rotation)),
                                        Draw.GameToScreenX(Position.X - (Radius * 1.4 * Cos(Rotation))),
                                        Draw.GameToScreenY(Position.Y - (Radius * 1.4 * Sin(Rotation))));
            }

            // Paint the missiles
            for (int i = 0; i < maxMissiles; i++)
            {
                Missile m = Missiles[i];
                if (m.Launched)
                {
                    Draw.BackBuffer.DrawEllipse(Draw.WhitePen, 
                                  Draw.GameToScreenX(m.Position.X - m.Radius), 
                                  Draw.GameToScreenY(m.Position.Y - m.Radius),
                                  m.Radius / draw.ScaleFactor, 
                                  m.Radius / draw.ScaleFactor);
                }
            }
        }


        #region IGameStateChangeSink
        // These methods will only be called on an enemy ship.

        public void OnShipMove(Vector vPos)
        {
            Position = vPos;
        }

        public void OnShipDamage(bool damaged)
        {
            this.damaged = damaged;
            if (damaged)
            {
                damageCount++;
            }
        }

        public void OnShipThrust(bool thrusting)
        {
            this.thrusting = thrusting;
        }

        public void OnShipRotate(int rotation)
        {
            this.rotation = rotation;
        }

        public void OnMissileMove(int iMissile, Vector vPos)
        {
            missiles[iMissile].Position = vPos;
            missiles[iMissile].Launched = true;
        }

        public void OnMissileGone(int iMissile)
        {
            missiles[iMissile].Launched = false;
        }

        public void OnOtherShipsMissileGone(int iMissile)
        {
            OtherShip.Missiles[iMissile].Launched = false;
        }

        #endregion
    }
}
