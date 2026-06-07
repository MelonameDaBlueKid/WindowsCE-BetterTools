using Microsoft.WindowsMobile.PocketOutlook.MessageInterception;
using Microsoft.WindowsMobile.PocketOutlook;
using System;
using System.Text.RegularExpressions;

namespace AppointmentOverSms
{

    /// <summary>
    /// Type of message.
    /// </summary>
    public enum MessageType
    {
        Appointment
    };

    /// <summary>
    /// The action that the user has taken.
    /// </summary>
    public enum ActionType
    {
        ProposalSubject,
        ProposalBody,
        Accept,
        Decline,
        Tentative
    };

    /// <summary>
    /// This class handles all the back end of this app. It creates
    /// SMS', 
    /// </summary>
    public static class SmsCreator
    {
        // Sms encoding strings
        public const string  identifierProtocol = "I:";
        public const string  appointmentProtocol = "A";
        public const string  separator = "#";
        public const string acceptActionString = "A";
        public const string proposalSubjectString = "PS";
        public const string proposalBodyString = "PB";
        public const string declineActionString = "D";
        public const string tentativeActionString = "T";
        
        //Maximum size that an SMS can take
        private const int maxSmsSize = 140;

        #region Constructor
        /// <summary>
        /// Creates two strings that contain all the information necessary to send
        /// an appointment proposal. These strings are to be sent as sms messages.
        /// </summary>
        public static void SmsCreateProposalMessages(Appointment appointment, ref string smsMessage1, ref string SmsMessage2)
        {
            int spaceLeft;
            string subject = appointment.Subject;
            DateTime start = appointment.Start;
            DateTime end = appointment.End;
            string location = appointment.Location;

            // 3 digit random number to maintain uniqueness of SMS
            Random random = new Random();
            int identifier = random.Next(1000);

            string action = GetActionString(ActionType.ProposalSubject);

            // Construct first message.
            spaceLeft = CheckSpaceAvailable(ActionType.ProposalSubject, appointment, identifier);
          
            smsMessage1 = identifierProtocol + appointmentProtocol + separator + action + separator + identifier +
                          separator + location + 
                          separator + subject.Substring(0,spaceLeft)   + 
                          separator + start.ToFileTimeUtc().ToString() +
                          separator + end.ToFileTimeUtc().ToString()   + separator;

            // Construct second message
            action = GetActionString(ActionType.ProposalBody);

            spaceLeft = CheckSpaceAvailable(ActionType.ProposalBody, appointment, identifier);

            if (appointment.Body.Length > spaceLeft)
            {
                SmsMessage2 = identifierProtocol + appointmentProtocol + separator + action + 
                              separator + identifier + 
                              separator + 
                              separator + appointment.Body.Substring(0, spaceLeft) +
                              separator + separator + separator;
            }
            else
            {
                SmsMessage2 = identifierProtocol + appointmentProtocol + 
                              separator + action +
                              separator + identifier + 
                              separator + 
                              separator + appointment.Body +
                              separator + separator + separator;
            }
        }

        /// <summary>
        /// Creates a string that contains all the information necessary to send a response to an
        /// appointment proposal. This strings is to be sent as an sms message.
        /// </summary>
        /// <param name="appointment">The appointment to respond to.</param>
        /// <param name="actionType">The action taken by the user - request/accept/decline/tentative.</param>
        /// <param name="smsMessage">the sms message string.</param>
        public static void SmsCreateResponseMessage(Appointment appointment, ActionType actionType, ref string smsMessage)
        {
            string subject  = appointment.Subject;
            string location = appointment.Location;
            DateTime start  = appointment.Start;
            DateTime end    = appointment.End;

            // 3 digit random number to maintain uniqueness of SMS
            Random random = new Random();
            int identifier = random.Next(1000);

            string action = GetActionString(actionType);

            // Construct message.
            int spaceLeft = CheckSpaceAvailable(actionType, appointment, identifier);

            smsMessage = identifierProtocol + appointmentProtocol + separator + action + separator + identifier +
                    separator + location + separator + subject.Substring(0, spaceLeft) +
                    separator + start.ToFileTimeUtc().ToString() + separator + end.ToFileTimeUtc().ToString() +
                    separator;
        }
        #endregion

        /// <summary>
        /// Helper function to check the availabe space in an SMS
        /// </summary>
        /// <param name="actionType"> Proposal body or proposal subject</param>
        /// <param name="appointment"> The appointment</param>
        /// <param name="identifier"> Identifier for the SMS</param>
        /// <returns>Space available for body/subject</returns>
        private static int CheckSpaceAvailable(ActionType actionType, Appointment appointment, int identifier)
        {
            string msg;
            int spaceLeft;
            string action = GetActionString(actionType);
            
            if (ActionType.ProposalBody == actionType)
            {
                //create "fake" msg to find out how much space will be left for body
                msg = identifierProtocol + appointmentProtocol + separator + action + 
                      separator + identifier +
                      separator + separator + separator +  separator + separator;
                
                spaceLeft = maxSmsSize - msg.Length;

                //Take as much of the body as can fit into the SMS
                if (spaceLeft > appointment.Body.Length)
                {
                    spaceLeft = appointment.Body.Length;
                }
            }
            else
            {
                //create "fake" msg to find out how much space will be left for subject
                msg = identifierProtocol + appointmentProtocol + separator + action + separator + identifier +
                    separator + appointment.Location + 
                    separator + 
                    separator + appointment.Start.ToFileTimeUtc().ToString() +
                    separator + appointment.End.ToFileTimeUtc().ToString() +
                    separator;

                spaceLeft = maxSmsSize - msg.Length;
               
                if (spaceLeft < 5)
                {
                    throw new ArgumentException("Appointment request is too large");
                }

                if (spaceLeft > appointment.Subject.Length)
                {
                    spaceLeft = appointment.Subject.Length;
                }
            }

            return spaceLeft;
        }

        

        #region ActionType enum conversion (string <-> ActionType)


        /// <summary>
        /// Helper function that converts an ActionType to a string
        /// </summary>
        /// <param name="actionType"> An ActionType enum member</param>
        /// <returns> The equivalent string</returns>
        private static string GetActionString(ActionType actionType)
        {
            string action = "";

            switch (actionType)
            {
                case ActionType.Accept:
                    action = acceptActionString;
                    break;
                case ActionType.Decline:
                    action = declineActionString;
                    break;
                case ActionType.ProposalSubject:
                    action = proposalSubjectString;
                    break;
                case ActionType.ProposalBody:
                    action = proposalBodyString;
                    break;
                case ActionType.Tentative:
                    action = tentativeActionString;
                    break;
                default: break;
            }

            return action;
        }

        #endregion
    }


    /// <summary>
    /// The SmsParser object parses SMS messages and stores the information
    /// necessary until two SMS messages that contain all the information
    /// pertinent to an appointment are received.
    /// </summary>
    public static class SmsParser
    {
        #region Private Variables        
        private const string separator = SmsCreator.separator;

        //This stores SMS that are waiting for another part
        //for completion.
        private static ProposalTracker proposalArray = new ProposalTracker();
        #endregion

        #region Parse SMS

        /// <summary>
        /// This method parses an SMS that is intercepted using regular expressions.
        /// </summary>
        /// <param name="msg"> The intercepted SMS</param>
        /// <returns>The appointment parsed, if it is null no appointment was parsed.</returns>
        public static Appointment ParseMessage(string msg, string address, ref ActionType appointmentAction)
        {
            string temp = "";
            string pattern = SmsCreator.identifierProtocol + @"(?<type>\w+)" + separator;            
            Regex msgRegex = new Regex(pattern);
            Match m = msgRegex.Match(msg);

            if (m.Success)
            {
                temp = m.Groups["type"].Value;
            }

            //If the message type is an appointment
            if (temp != null && temp[0] == 'A')
            {
                pattern = SmsCreator.identifierProtocol + @"(?<type>\w*)" +
                          separator + @"(?<action>\w*)" +
                          separator + @"(?<identifier>[^" +
                          separator + "]*)" + 
                          separator + @"(?<location>[^" + 
                          separator + "]*)" + 
                          separator + @"(?<subject>.[^" + 
                          separator + "]*)" +
                          separator + @"(?<startTime>[^" + 
                          separator + "]*)" + 
                          separator + @"(?<endTime>[^" + 
                          separator + "]*)" + 
                          separator;

                msgRegex = new Regex(pattern);
                m = msgRegex.Match(msg);

                if (!m.Success)
                {
                    pattern = SmsCreator.identifierProtocol + @"(?<type>\w*)" +
                              separator + @"(?<action>\w*)" +
                              separator + @"(?<identifier>[^" +
                              separator + "]*)" +
                              separator + @"(?<body>[^" +
                              separator + "]*)" +
                              separator + @"(?<body>.[^" +
                              separator + "]*)" +
                              separator;

                    msgRegex = new Regex(pattern);
                    m = msgRegex.Match(msg);
                }

                if (m.Success)
                {
                    appointmentAction = GetEnumActionType(m.Groups["action"].Value);
                    int identifier = Int32.Parse(m.Groups["identifier"].Value);
                    Appointment appointment = new Appointment();

                    //Is it an appointment request body
                    if (appointmentAction == ActionType.ProposalBody)
                    {
                        appointment.Body = m.Groups["subject"].Value;
                        //See if the first part has already arrived
                        Appointment fullAppointment = proposalArray.Add(appointment, identifier);
                        return fullAppointment;
                    }
                    else
                    {
                        appointment.Subject = m.Groups["subject"].Value;
                        appointment.Location = m.Groups["location"].Value;
                        appointment.Start = DateTime.FromFileTimeUtc(long.Parse(m.Groups["startTime"].Value));
                        appointment.End = DateTime.FromFileTimeUtc(long.Parse(m.Groups["endTime"].Value));

                        if (appointmentAction == ActionType.ProposalSubject)
                        {
                            //Check if the second part has already arrived
                            Appointment fullAppointment = proposalArray.Add(appointment, identifier);
                            return fullAppointment;
                        }
                        else
                        {
                            return appointment;
                        }
                    }
                }
                else
                {
                    return null;
                }
            }
            return null;
        }

        #endregion

        /// <summary>
        /// Helper function that converts a string to an ActionType Enum
        /// </summary>
        /// <param name="actionType"> The string containing an action</param>
        /// <returns> The parsed ActionType</returns>
        private static ActionType GetEnumActionType(string actionType)
        {
            ActionType toReturn;

            if (actionType.Equals(SmsCreator.acceptActionString))
            {
                toReturn = ActionType.Accept;
            }
            else if (actionType.Equals(SmsCreator.proposalSubjectString))
            {
                toReturn = ActionType.ProposalSubject;
            }
            else if (actionType.Equals(SmsCreator.proposalBodyString))
            {
                toReturn = ActionType.ProposalBody;
            }
            else if (actionType.Equals(SmsCreator.declineActionString))
            {
                toReturn = ActionType.Decline;
            }
            else
            {
                toReturn = ActionType.Tentative;
            }

            return toReturn;
        }

    }
}
