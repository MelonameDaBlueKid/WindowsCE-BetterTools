using Microsoft.WindowsMobile.PocketOutlook.MessageInterception;
using Microsoft.WindowsMobile.PocketOutlook;
using System;

namespace AppointmentOverSms
{
    /// <summary>
    /// This class keeps track of proposals since they come in two parts -
    /// body of the appointment request in one SMS, and the rest in another SMS.
    /// </summary>
    public class ProposalTracker
    {
        //Array of proposals - there can be more than one
        //incomplete proposal at a given time
        private System.Collections.ArrayList proposalList;

        #region Constructor

        /// <summary>
        /// Initialize variables.
        /// </summary>
        public ProposalTracker()
        {
            proposalList = new System.Collections.ArrayList();
        }

        #endregion

        #region Add appointment

        /// <summary>
        /// Add a proposal that was received to the array. If a match 
        /// is found, it means that the proposal is complete, and we can
        /// return it and delete it from the array. Otherwise, we just add
        /// the incomplete proposal to the array and wait for its 
        /// counterpart to arrive
        /// </summary>
        /// <param name="a">Appointment request received over SMS</param>
        /// <param name="identifier">Used to match two appointments</param>
        /// <returns>Appointment if we find a completed appointment, 
        /// null otherwise
        /// </returns>
        public Appointment Add(Appointment a, int identifier)
        {
            Appointment result = null;
    
            //Go through the proposal list
            for (int i = 0;i < proposalList.Count; i++)
            {
                //If we have an identifier match:
                if (identifier == ((Proposal)proposalList[i]).Identifier)
                {
                    //Return the appointment that matches
                    result = ((Proposal)proposalList[i]).UpdateAppointment(a);

                    //Remove that appointment from the list
                    proposalList.RemoveAt(i);
                    break;
                }
            }
            
            if (result == null)
            {
                //If no match was found, add the incomplete proposal
                Proposal p = new Proposal(a, identifier);
                proposalList.Add(p);
            }

            return result;
        }   
     
        #endregion

        #region Private Class Proposal
        /// <summary>
        /// This is used to keep track of proposals.
        /// </summary>
        private class Proposal
        {
            private Appointment appointment;
            private int identifier;

            #region Constructor

            /// <summary>
            /// Set the variables of the new instance of this class
            /// </summary>
            /// <param name="appointment">The appointment information to be stored</param>
            /// <param name="identifier">Identifier for this particular appointment</param>
            public Proposal(Appointment appointment, int identifier)
            {
                this.appointment = appointment;
                this.identifier = identifier;
            }

            #endregion

            #region Public Method
            /// <summary>
            /// Counterpart of the appointment is found. Now we can
            /// complete the appointment
            /// </summary>
            /// <param name="appointment">The second half of the appointment</param>
            /// <returns> The complete appointment</returns>
            public Appointment UpdateAppointment(Appointment appointment)
            {
                if (appointment.Subject.Length > 0 )
                {
                    //remember the body of the old appointment.
                    appointment.Body = this.appointment.Body;

                    this.appointment = appointment;
                }
                else
                {
                    this.appointment.Body = appointment.Body;
                }

                return this.appointment;
            }
            #endregion

            #region Properties
            /// <summary>
            /// Gets the appointment stored in the object
            /// </summary>
            public Appointment Appointment
            {
                get
                {
                    return appointment;
                }
            }

            /// <summary>
            /// Gets the identifier for the appointment stored in the object
            /// </summary>
            public int Identifier
            {
                get
                {
                    return identifier;
                }
            }

            #endregion
        }
        #endregion
    }
}