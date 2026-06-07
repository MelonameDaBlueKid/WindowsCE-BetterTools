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
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

using System;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Windows.Forms;
using Microsoft.WindowsMobile.PocketOutlook;


namespace Microsoft.WindowsMobile.Samples.ControlLibrary
{
    /// <summary>
    /// Base class for TaskListView, ContactListView and AppointmentListView
    /// </summary>
    public partial class PimItemListView: System.Windows.Forms.UserControl, IDisposable
    {
        #region Private and protected member variables
        //
        //   Cell:
        //   +---------------------------------------------+   +
        //   |                           +---------+  | /\ |   | 
        //   |   First Label- property1  |         |  |    |   |
        //   |                           |         |  |    |   | e
        //   |   Second Label -property2 |         |  |    |   |
        //   |                           +---------+  | \/ |   |
        //   +---------------------------------------------+   +
        //   <->                          <--------><-><--->
        //    a                                b     c   d
        //
        //   a: borderWidth
        //   b: pictureWidth
        //   c: pictureBorderWidth
        //   d: Scrollbar 
        //   e: cellHeight
                
        private int pimItemsShowing;            // Number of PimItems currently showing
        private int maxCellCount;               // Maximum number of cells that fit in the control
        private int cellHeight;                 // Height of each pimItem on the view
        private int cellHeightDiv2;             // Height divided by 2
        private int pictureWidth;               // Picture width
        private int pictureHeight;              // Picture height

        private int borderWidth;                // Label border width
        private int pictureBorderWidth;         // Picture border width

        private int minControlHeight;           // Minimum control height
        private int minControlWidth;            // Minimum control width
        private int scrollValue;                // Current value of the scrollbar
        private int selectedCell;               // Selected cell

        private Color highlightBackgroundColor; // Highlighted cell background 
        private Color backgroundColor;          // Control default background 
        private Color highlightTextColor;       // Highlighted cell text color 
        private Color textColor;                // Control default text color

        protected bool showPicture;             // Show the picture?
        protected ContactProperty property1;    // Property shown by first label for a pimItem
        protected ContactProperty property2;    // Property shown by second label for a pimItem

        private PimItemCollection pimItemsCollection; //PimItem collection passed in by the user

        private Font line1Font;                 // Font used in cell's first line.
        private Font line2Font;                 // Font used in cell's second line.

        // Objects required for rendering 
        private Graphics   formGraphics;
        private Graphics backGraphics;
        private Bitmap backBuffer;
        private SolidBrush backgroundBrush;
        private SolidBrush highlightBackgroundBrush;
        private SolidBrush textBrush;
        private SolidBrush hightlightTextBrush;
        private Pen pen;

        private bool disposed = false;

        #endregion

        #region Public Event
        public class PimItemListViewEventArgs : EventArgs
        {
            #region Public
            public PimItem PimItem
            {
                get
                {
                    return pimItem;
                }
            }
            #endregion

            #region Private
            private PimItem pimItem;
            #endregion

            #region Internal
            internal PimItemListViewEventArgs(PimItem pimItem)
            {
                this.pimItem = pimItem;
            }
            #endregion
        }
        public delegate void ClickEventHandler(object sender, PimItemListViewEventArgs item);
        #endregion

        #region Constructor and Initializers
        /// <summary>
        /// Constructor: Initialize all the values
        /// </summary>
        public PimItemListView()
        {
            InitializeComponent();

            InitializeWithDefaultValues();
            ResetGeometry();

            vScrollBar1.ValueChanged += new EventHandler(vScrollBar1_ValueChanged);
            this.Resize += new System.EventHandler(this.FormResized);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.OnMouseDown);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);            
        }

        /// <summary>
        /// Initializes private members with default values.
        /// </summary>
        private void InitializeWithDefaultValues()
        {
            //Setting background colors and color for highlighting            
            backgroundColor = System.Drawing.SystemColors.Window;
            textColor = System.Drawing.SystemColors.WindowText;
            highlightBackgroundColor = System.Drawing.SystemColors.Highlight;
            highlightTextColor = System.Drawing.SystemColors.HighlightText;
            
            //Setting graphic objects
            formGraphics = this.CreateGraphics();

            line1Font = new Font("Microsoft Sans Serif", 8, FontStyle.Regular);
            line2Font = new Font("Microsoft Sans Serif", 8, FontStyle.Regular);
            backgroundBrush = new SolidBrush(backgroundColor);
            highlightBackgroundBrush = new SolidBrush(highlightBackgroundColor);
            textBrush = new SolidBrush(textColor);
            hightlightTextBrush = new SolidBrush(highlightTextColor);
            pen = new Pen(textColor);

            //Height of each cell for one PimItem (two labels for every pimItem)
            cellHeight = 32;

            borderWidth = 2;

            //height offset for the picture so that it appears on the center
            //of the pimItem "panel"            
            pictureBorderWidth = 0;

            //Minimum height/width that the control can take
            minControlHeight = 36;
            minControlWidth = 120;

            //Change when the arrows on the scrollbar is clicked
            vScrollBar1.SmallChange = 1;

            //Default property1
            property1 = ContactProperty.FirstName;

            //Default property2
            property2 = ContactProperty.MobileTelephoneNumber;

            //Default - don't show pictures.
            showPicture = false;
        }

        /// <summary>
        /// Resets all the values that depend on the size of the control
        /// or on the cellHeight
        /// </summary>
        private void ResetGeometry()
        {
            //Height of each pimItem on screen (height of one label)
            cellHeightDiv2 = cellHeight / 2;

            //Number of cells that can be drawn.
            maxCellCount = this.ClientSize.Height / cellHeight;

            // Actual number of items that we can display is
            pimItemsShowing = 0;
            vScrollBar1.Hide();

            if (pimItemsCollection != null && pimItemsCollection.Count > 0)
            {
                //Dont show more than maximum pimItems
                if (pimItemsCollection.Count > maxCellCount)
                {
                    pimItemsShowing = maxCellCount;
                    vScrollBar1.Location = new System.Drawing.Point(this.ClientSize.Width - vScrollBar1.Width, 0);
                    vScrollBar1.Minimum = 0;
                    vScrollBar1.Maximum = pimItemsCollection.Count - 1;
                    vScrollBar1.LargeChange = pimItemsShowing;
                    vScrollBar1.Size = new System.Drawing.Size(vScrollBar1.Width, maxCellCount * cellHeight + 1);                    
                    vScrollBar1.Show();
                }
                else
                {                    
                    pimItemsShowing = pimItemsCollection.Count;
                    this.ClientSize = new System.Drawing.Size(this.ClientSize.Width, cellHeight * pimItemsShowing + 1);
                }
            }

            //Picture width and height. Maintain 4:3 ration between height
            //and picture to be consistent with the way pictures are shown
            //on the built-in pimItem viewer           
            pictureHeight = cellHeight - 2 * pictureBorderWidth - 1; //1 is the divider line width.
            pictureWidth = pictureHeight * 3 / 4;

            //Creating a back buffer to make scrolling smooth.
            if (backGraphics != null)
            {
                backGraphics.Dispose();
            }

            if (backBuffer != null)
            {
                backBuffer.Dispose();
            }
            backBuffer = new Bitmap(this.Size.Width, this.Size.Height);
            backGraphics = Graphics.FromImage(backBuffer);
        }
        #endregion

        #region Public Event
        /// <summary>
        /// Raised when a pimItem is selected
        /// </summary>
        public event ClickEventHandler PimItemSelected;
        #endregion

        #region Scrollbar Event Handler
       /// <summary>
       /// Eventhandler for scroll bar changing value
       /// </summary>
       /// <param name="sender"> Sender</param>
       /// <param name="e"> EventArgs</param>
       /// <remarks> This is called twice on every value change. Thats why the
       /// if clase is required.</remarks>
       private void vScrollBar1_ValueChanged(Object sender,
           EventArgs e)
       {
           if (scrollValue != vScrollBar1.Value)
           {
               UpdateDisplay();
           }
       }
       #endregion

        #region Resize Handler
       /// <summary>
       /// Handles resizing of the control
       /// </summary>
       /// <param name="sender"> Sender with resizing information</param>
       /// <param name="e"> EventArgs</param>
       private void FormResized(object sender, System.EventArgs e)
       {
           Control control = (Control)sender;
           int newHeight = control.Size.Height;
           int newWidth = control.Size.Width;

           //Dont go below a minimum height
           if (newHeight < minControlHeight)
           {
               newHeight = minControlHeight;
           }

           //Dont go below a minimum width
           if (newWidth < minControlWidth)
           {
               newWidth = minControlWidth;               
           }

           this.ClientSize = new System.Drawing.Size(newWidth, newHeight);

           //Refresh form
           ResetGeometry();
           this.Invalidate();
       }
       #endregion

        #region Mouse Event Handler
       /// <summary>
       /// Capture the click event
       /// </summary>
       /// <param name="sender"> Sender </param>
       /// <param name="e"> Information about the click</param>
       private void OnMouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
       {
           //Calculation to find out which pimItem was clicked
           selectedCell = e.Y / cellHeight;

           //Do highlighting if the pimItem is on display
           if (selectedCell < pimItemsShowing)
           {
               UpdateDisplay();
               PimItemListViewEventArgs args = new PimItemListViewEventArgs((PimItem)pimItemsCollection[scrollValue + selectedCell]);
               PimItemSelected(sender, args);
           }
       }
       #endregion

        #region Paint Event Handler
       /// <summary>
       /// This paints the PimItemListView control
       /// </summary>
       /// <param name="sender">Sender</param>
       /// <param name="eventArgs">Event arguments</param>
        private void Form1_Paint(object sender, System.Windows.Forms.PaintEventArgs eventArgs)
       {
           UpdateDisplay();
       }
       #endregion

        #region Private Methods - Display PimItem Information

       /// <summary>
       /// Draw picture if requested and if picture exists
       /// </summary>
       /// <param name="picture">Picture to be drawn</param>
       /// <param name="pimItemNo">The pimItem index indicating where the
       /// picture should be drawn</param>
       private void DrawPicture(System.Drawing.Image picture, int pimItemNo)
       {
           if (showPicture && picture != null)
           {               
               //Rectangle where the picture should be drawn.
               System.Drawing.Rectangle destRect = new System.Drawing.Rectangle(
                                                   this.ClientSize.Width - (vScrollBar1.Width + pictureBorderWidth + pictureWidth), 
                                                   cellHeight * pimItemNo + pictureBorderWidth + 1 , 
                                                   pictureWidth, 
                                                   pictureHeight);

               //Select the full picture from the picture file
               System.Drawing.Rectangle srcRect = new System.Drawing.Rectangle(0, 0, picture.Size.Width, picture.Size.Height);

               backGraphics.DrawImage(picture, destRect, srcRect, System.Drawing.GraphicsUnit.Pixel);
           }
       }

        /// <summary>
        /// Displays one cell in the PimItemViewer
        /// </summary>
        /// <param name="cellNumber">Number of cell to display.</param>
        /// <param name="firstLine">String to display in the first label.</param>
        /// <param name="lastLine">String to display in the second label.</param>
        private void DisplayCell(int cellNumber, String firstLine, String lastLine)
        {            
            int y1 = cellNumber * cellHeight;
            int y2 = cellNumber * cellHeight + cellHeightDiv2;
            int width = this.ClientSize.Width - vScrollBar1.Width - borderWidth;
            int height = cellHeightDiv2 - borderWidth;

            if (selectedCell != cellNumber)
            {
                backGraphics.DrawString(firstLine,line1Font, textBrush, new RectangleF(borderWidth, y1, width, height));
                backGraphics.DrawString(lastLine, line2Font, textBrush, new RectangleF(borderWidth, y2, width, height));
            }
            else
            {
                backGraphics.DrawString(firstLine, line1Font, hightlightTextBrush, new RectangleF(borderWidth, y1, width, height));
                backGraphics.DrawString(lastLine, line2Font, hightlightTextBrush, new RectangleF(borderWidth, y2, width, height));
            }
        }

        #endregion

        #region Protected Properties and Methods

        /// <summary>
        /// The collection of items to display in the ListView.
        /// </summary>
        protected PimItemCollection PimItems
        {
            set
            {
                pimItemsCollection = value;
                ResetGeometry();
            }
        }

        /// <summary>
        /// Update the pimItem information on the pimItem viewer
        /// </summary>
        protected void UpdateDisplay()
        {
            scrollValue = vScrollBar1.Value;
            int offset = scrollValue;

            String firstLine;
            String secondLine;
            PimItem pimItem;
            bool highlighted;
            object pimProperty1;
            object pimProperty2;

            if (pimItemsShowing == 0)
            {
                formGraphics.FillRectangle(backgroundBrush, 0, 0,
                            this.Size.Width, this.Size.Height);

                formGraphics.DrawString("There are no items in the collection", line1Font, textBrush, 0, 0);
                return;
            }

            // Paint background
            backGraphics.FillRectangle(backgroundBrush, 0, 0,
                                       this.Size.Width, this.Size.Height);


            // Highlight selected item.
            backGraphics.FillRectangle(highlightBackgroundBrush, 0, selectedCell * cellHeight,
                                       this.Size.Width - vScrollBar1.Width, cellHeight);

            //Set the information on the labels according to the value of the scrollbar
            for (int i = 0; i < pimItemsShowing && pimItemsCollection != null && offset < pimItemsCollection.Count; i++, offset++)
            {
                pimItem = pimItemsCollection[offset];

                pimProperty1 = pimItem.Properties[property1];
                pimProperty2 = pimItem.Properties[property2];

                if (pimProperty1 != null)
                {
                    firstLine = pimProperty1.ToString();
                }
                else
                {
                    firstLine = "";
                }

                if (pimProperty2 != null)
                {
                    secondLine = pimProperty2.ToString();
                }
                else
                {
                    secondLine = "";
                }
                highlighted = (selectedCell == i);

                DisplayCell(i, firstLine, secondLine);

                if (showPicture)
                {
                    DrawPicture(((Contact)pimItemsCollection[i + scrollValue]).Picture, i);
                }
            }

            int yStart;
            int xEnd = this.ClientSize.Width - vScrollBar1.Width;

            //Draw the lines separating the pimItems
            if (pimItemsShowing != 0)
            {
                for (int i = 0; i <= pimItemsShowing; i++)
                {
                    yStart = cellHeight * i;
                    //Draw Line. yStart is the same as yEnd.
                    backGraphics.DrawLine(pen, 0, yStart, xEnd, yStart);
                }
            }

            // Copy the backBuffer to the front buffer. Using the backbuffer 
            // makes changes in the display smoother.
            formGraphics.DrawImage(backBuffer, 0, 0);
        }
        #endregion

        #region Public Properties
       /// <summary>
       /// The font for the first line in a cell.
       /// </summary>
       public System.Drawing.Font Property1Font
        {
            get
            {
                return line1Font;
            }
            set
            {
                line1Font = value;
            }
        }

       /// <summary>
       /// The font for the second line in a cell.
       /// </summary>
       public System.Drawing.Font Property2Font
        {
            get
            {
                return line2Font;
            }
            set
            {
                line2Font = value;
            }
              
        }

       /// <summary>
       /// The height of one of the cells in pixels.
       /// </summary>
       public int CellHeight
       {
           get
           {
               return cellHeight;
           }
           set
           {
               cellHeight = value;
               ResetGeometry();
           }
       }
       #endregion

        #region IDisposable Members

        /// <summary>
        /// Disposes the PimItemViewer object.
        /// </summary>
        void IDisposable.Dispose()
        {
            if (!disposed)
            {
                disposed = true;
                backgroundBrush.Dispose();
                backgroundBrush.Dispose();
                highlightBackgroundBrush.Dispose();
                textBrush.Dispose();
                hightlightTextBrush.Dispose();
                pen.Dispose();
                line1Font.Dispose();
                line2Font.Dispose();
                formGraphics.Dispose();
                backGraphics.Dispose();
                backBuffer.Dispose();
                GC.SuppressFinalize(this);
            }
        }

        /// <summary>
        /// Finalizer.
        /// Dispose should be called by the parent object. We dispose just
        /// in case it does not.
        /// </summary>
        ~PimItemListView()
        {
            Dispose();
        }
        #endregion
    }
}
