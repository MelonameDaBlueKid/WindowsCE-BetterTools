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
#region Using directives

using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;
using System.Data;
using Microsoft.WindowsMobile.PocketOutlook;

#endregion

namespace Microsoft.WindowsMobile.Samples.BirthdaysToCalendar
{
    /// <summary>
    /// Summary description for BirthdayToCalendar.
    /// </summary>
    public class BirthdayToCalendar : System.Windows.Forms.Form
    {
        private Label lblBday;
        private MenuItem menuItem2;
        private MenuItem menuItem1;
        private MenuItem mnuItmAdd;
        private MenuItem mnuItmQuit;
        /// <summary>
        /// Main menu for the form.
        /// </summary>
        private System.Windows.Forms.MainMenu mainMenu1;

        public BirthdayToCalendar()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
        }

        /// <summary>
        /// Adds a Birthday to the calendar as a recurring all day event.
        /// </summary>
        private bool AddToCalendar(OutlookSession outlooksession, string name, DateTime bDay, string occasion)
        {
            string apptSubject = name + "'s " + occasion;

            // Return if it is already added to the calendar.
            AppointmentCollection appts = outlooksession.Appointments.Items.Restrict(String.Format("[Subject] = \"{0}\"", apptSubject));
            if (appts.Count != 0)
            {
                return false;
            }

            Appointment appointment = new Appointment();
            appointment.Subject = apptSubject;
            appointment.AllDayEvent = true;

            // Setup a yearly recurrence
            appointment.RecurrencePattern.RecurrenceType = RecurrenceType.Yearly;
            appointment.RecurrencePattern.MonthOfYear = (Month)bDay.Month;
            appointment.RecurrencePattern.DayOfMonth = bDay.Day;

            //This would fill  the RecurrencePatternStartDate too.
            appointment.Start = DateTime.Today;
            appointment.ReminderMinutesBeforeStart = 120;
            outlooksession.Appointments.Items.Add(appointment);
            return true;
        }

        /// <summary>
        /// Adds a contact's Birthday to the calendar if it's set.
        /// </summary>
        private void mnuItmAdd_Click(object sender, EventArgs e)
        {
            // Add
            bool added = false;
            using (OutlookSession outlooksession = new OutlookSession())
            {
                // An invalid date is represented as 0 on the FileTime format.
                DateTime invalidDate = DateTime.FromFileTimeUtc(0);
                string invalidDateStr = invalidDate.Date.ToString("d", System.Globalization.DateTimeFormatInfo.CurrentInfo) +
                                                                  " " + invalidDate.TimeOfDay.ToString();
                string query = "[Birthday] <> " + invalidDateStr;
                ContactCollection contacts = outlooksession.Contacts.Items.Restrict(query);

                if (contacts.Count == 0)
                {
                    MessageBox.Show("Contact list does not have items with valid Birthday");
                    return;
                }

                // Enumerator for contact collection.
                foreach (Contact contactobj in contacts)
                {
                    if (AddToCalendar(outlooksession, contactobj.FirstName + ' ' + contactobj.LastName, contactobj.Birthday, "Birthday"))
                        added = true;
                }
                if (added)
                {
                    MessageBox.Show("Successfully added the dates to Calendar");
                    mnuItmAdd.Enabled = false;
                }
                else
                {
                    MessageBox.Show("None of the dates were added. Maybe they are already added");
                    mnuItmAdd.Enabled = false;
                }
            }
        }

        /// <summary>
        /// Cancel.
        /// </summary>
        private void mnuItmQuit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.mainMenu1 = new System.Windows.Forms.MainMenu();
            this.lblBday = new System.Windows.Forms.Label();
            this.menuItem2 = new System.Windows.Forms.MenuItem();
            this.menuItem1 = new System.Windows.Forms.MenuItem();
            this.mnuItmAdd = new System.Windows.Forms.MenuItem();
            this.mnuItmQuit = new System.Windows.Forms.MenuItem();
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.Add(this.menuItem1);
            this.mainMenu1.MenuItems.Add(this.menuItem2);
            // 
            // lblBday
            // 
            this.lblBday.Font = new System.Drawing.Font("Segoe Condensed", 10F, System.Drawing.FontStyle.Bold);
            this.lblBday.Location = new System.Drawing.Point(3, 17);
            this.lblBday.Size = new System.Drawing.Size(170, 45);
            this.lblBday.Text = "This will add all the Birthdays in contact list to Calendar";
            this.lblBday.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // menuItem2
            // 
            this.menuItem2.MenuItems.Add(this.mnuItmAdd);
            this.menuItem2.MenuItems.Add(this.mnuItmQuit);
            this.menuItem2.Text = "Menu";
            // 
            // menuItem1
            // 
            this.menuItem1.Text = "";
            // 
            // mnuItmAdd
            // 
            this.mnuItmAdd.Text = "Add";
            this.mnuItmAdd.Click += new System.EventHandler(this.mnuItmAdd_Click);
            // 
            // mnuItmQuit
            // 
            this.mnuItmQuit.Text = "Quit";
            this.mnuItmQuit.Click += new System.EventHandler(this.mnuItmQuit_Click);
            // 
            // BirthdayToCalendar
            // 
            this.ClientSize = new System.Drawing.Size(176, 180);
            this.Controls.Add(this.lblBday);
            this.Menu = this.mainMenu1;
            this.Text = "BirthdayToCalendar";

        }

        #endregion
    }
}
