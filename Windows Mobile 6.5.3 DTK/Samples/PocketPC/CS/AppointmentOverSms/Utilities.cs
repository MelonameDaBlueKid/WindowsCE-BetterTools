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
using System.Text;
using Microsoft.WindowsMobile.PocketOutlook;

namespace AppointmentOverSms
{
    internal class Utilities
    {
        /// <summary>
        /// This finds the appointment that matches the appointment received through
        /// an SMS.
        /// </summary>
        /// <param name="appointment"> The appointment received from the SMS</param>
        /// <returns>If found, the appointment that matches the parameter. If not
        /// found, it returns null.
        /// </returns>
        public static Appointment FindAppointment(Appointment appointment)
        {
            Appointment match = null;

            if (appointment == null)
            {
                return null;
            }

            using (OutlookSession session = new OutlookSession())
            {

                //Go through all the appointments and find the matching appointment
                foreach (Appointment currentAppointment in session.Appointments.Items)
                {
                    if (currentAppointment.Subject.StartsWith(appointment.Subject) && 
                        DateTime.Compare(appointment.Start, currentAppointment.Start) == 0 &&
                        DateTime.Compare(appointment.End, currentAppointment.End) == 0)
                    {
                        match = currentAppointment;
                        break;
                    }

                }
            }
            return match;
        }


        /// <summary>
        /// This finds conflicts for the given meeting request time, and notifies
        /// the user accordingly
        /// </summary>
        /// <returns> String indicating whether there is a conflict or not</returns>
        public static string FindConflicts(Appointment appointment)
        {
            using (OutlookSession session = new OutlookSession())
            {

                // Convert start and end date to a format that can be used for the query.
                // Cannot simply use appointment.Start.ToString because
                // "pm/am" format for the time is not supported.
                String start = appointment.Start.Date.ToString("d", System.Globalization.DateTimeFormatInfo.CurrentInfo) + " " +
                               appointment.Start.TimeOfDay.ToString();

                String end = appointment.End.Date.ToString("d", System.Globalization.DateTimeFormatInfo.CurrentInfo) + " " +
                             appointment.End.TimeOfDay.ToString();

                string query = "([Start] >  " + start + " and [Start] <  " + end + ") " +
                            "or ([End]   >  " + start + " and [End]   <  " + end + ") " +
                            "or ([Start] <= " + start + " and [End]   >= " + end + ") ";

                PimItemCollection collection = session.Appointments.Items.Restrict(query);

                if (collection.Count > 0)
                {
                    return "Appointment conflicts.";
                }
                else
                {
                    return "No conflict";
                }
            }
        }

        #region Appointment and Contact searches

        /// <summary>
        /// This finds the contact with the specified phone number
        /// </summary>
        /// <param name="sender">The recipient to find a contact for.</param>
        /// <returns>The contact that has the same name as sender, if found. 
        /// If not found, it returns a new contact.</returns>
        public static Contact FindContact(Recipient sender)
        {
            using (OutlookSession session = new OutlookSession())
            {
                string query = "([FileAs] = \"" + sender.Name + "\")";
                PimItemCollection itemCollection = session.Contacts.Items.Restrict(query);

                //If the user is found, return the user, otherwise create a new contact
                //with the phone number as name and mobile number
                if (itemCollection.Count > 0)
                {
                    return (Contact)itemCollection[0];
                }
                else
                {
                    // This would happen in the rare situation that a person
                    // not in our contacts sent the meeting or responded to our
                    // meeting request.
                    Contact newContact = new Contact();
                    newContact.MobileTelephoneNumber = sender.Address;
                    newContact.FirstName = sender.Name;
                    return newContact;
                }
            }
        }
        #endregion


    }
}
