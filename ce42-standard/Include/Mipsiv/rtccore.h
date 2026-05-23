
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Tue Feb 11 13:44:05 2003
 */
/* Compiler settings for .\rtccore.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __rtccore_h__
#define __rtccore_h__

/* Forward Declarations */ 

#ifndef __IRTCClient_FWD_DEFINED__
#define __IRTCClient_FWD_DEFINED__
typedef interface IRTCClient IRTCClient;
#endif 	/* __IRTCClient_FWD_DEFINED__ */


#ifndef __IRTCClient2_FWD_DEFINED__
#define __IRTCClient2_FWD_DEFINED__
typedef interface IRTCClient2 IRTCClient2;
#endif 	/* __IRTCClient2_FWD_DEFINED__ */


#ifndef __IRTCClientPresence_FWD_DEFINED__
#define __IRTCClientPresence_FWD_DEFINED__
typedef interface IRTCClientPresence IRTCClientPresence;
#endif 	/* __IRTCClientPresence_FWD_DEFINED__ */


#ifndef __IRTCClientPresence2_FWD_DEFINED__
#define __IRTCClientPresence2_FWD_DEFINED__
typedef interface IRTCClientPresence2 IRTCClientPresence2;
#endif 	/* __IRTCClientPresence2_FWD_DEFINED__ */


#ifndef __IRTCClientProvisioning_FWD_DEFINED__
#define __IRTCClientProvisioning_FWD_DEFINED__
typedef interface IRTCClientProvisioning IRTCClientProvisioning;
#endif 	/* __IRTCClientProvisioning_FWD_DEFINED__ */


#ifndef __IRTCClientProvisioning2_FWD_DEFINED__
#define __IRTCClientProvisioning2_FWD_DEFINED__
typedef interface IRTCClientProvisioning2 IRTCClientProvisioning2;
#endif 	/* __IRTCClientProvisioning2_FWD_DEFINED__ */


#ifndef __IRTCProfile_FWD_DEFINED__
#define __IRTCProfile_FWD_DEFINED__
typedef interface IRTCProfile IRTCProfile;
#endif 	/* __IRTCProfile_FWD_DEFINED__ */


#ifndef __IRTCProfile2_FWD_DEFINED__
#define __IRTCProfile2_FWD_DEFINED__
typedef interface IRTCProfile2 IRTCProfile2;
#endif 	/* __IRTCProfile2_FWD_DEFINED__ */


#ifndef __IRTCSession_FWD_DEFINED__
#define __IRTCSession_FWD_DEFINED__
typedef interface IRTCSession IRTCSession;
#endif 	/* __IRTCSession_FWD_DEFINED__ */


#ifndef __IRTCSession2_FWD_DEFINED__
#define __IRTCSession2_FWD_DEFINED__
typedef interface IRTCSession2 IRTCSession2;
#endif 	/* __IRTCSession2_FWD_DEFINED__ */


#ifndef __IRTCSessionCallControl_FWD_DEFINED__
#define __IRTCSessionCallControl_FWD_DEFINED__
typedef interface IRTCSessionCallControl IRTCSessionCallControl;
#endif 	/* __IRTCSessionCallControl_FWD_DEFINED__ */


#ifndef __IRTCParticipant_FWD_DEFINED__
#define __IRTCParticipant_FWD_DEFINED__
typedef interface IRTCParticipant IRTCParticipant;
#endif 	/* __IRTCParticipant_FWD_DEFINED__ */


#ifndef __IRTCRoamingEvent_FWD_DEFINED__
#define __IRTCRoamingEvent_FWD_DEFINED__
typedef interface IRTCRoamingEvent IRTCRoamingEvent;
#endif 	/* __IRTCRoamingEvent_FWD_DEFINED__ */


#ifndef __IRTCProfileEvent_FWD_DEFINED__
#define __IRTCProfileEvent_FWD_DEFINED__
typedef interface IRTCProfileEvent IRTCProfileEvent;
#endif 	/* __IRTCProfileEvent_FWD_DEFINED__ */


#ifndef __IRTCProfileEvent2_FWD_DEFINED__
#define __IRTCProfileEvent2_FWD_DEFINED__
typedef interface IRTCProfileEvent2 IRTCProfileEvent2;
#endif 	/* __IRTCProfileEvent2_FWD_DEFINED__ */


#ifndef __IRTCClientEvent_FWD_DEFINED__
#define __IRTCClientEvent_FWD_DEFINED__
typedef interface IRTCClientEvent IRTCClientEvent;
#endif 	/* __IRTCClientEvent_FWD_DEFINED__ */


#ifndef __IRTCRegistrationStateChangeEvent_FWD_DEFINED__
#define __IRTCRegistrationStateChangeEvent_FWD_DEFINED__
typedef interface IRTCRegistrationStateChangeEvent IRTCRegistrationStateChangeEvent;
#endif 	/* __IRTCRegistrationStateChangeEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionStateChangeEvent_FWD_DEFINED__
#define __IRTCSessionStateChangeEvent_FWD_DEFINED__
typedef interface IRTCSessionStateChangeEvent IRTCSessionStateChangeEvent;
#endif 	/* __IRTCSessionStateChangeEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionStateChangeEvent2_FWD_DEFINED__
#define __IRTCSessionStateChangeEvent2_FWD_DEFINED__
typedef interface IRTCSessionStateChangeEvent2 IRTCSessionStateChangeEvent2;
#endif 	/* __IRTCSessionStateChangeEvent2_FWD_DEFINED__ */


#ifndef __IRTCSessionOperationCompleteEvent_FWD_DEFINED__
#define __IRTCSessionOperationCompleteEvent_FWD_DEFINED__
typedef interface IRTCSessionOperationCompleteEvent IRTCSessionOperationCompleteEvent;
#endif 	/* __IRTCSessionOperationCompleteEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionOperationCompleteEvent2_FWD_DEFINED__
#define __IRTCSessionOperationCompleteEvent2_FWD_DEFINED__
typedef interface IRTCSessionOperationCompleteEvent2 IRTCSessionOperationCompleteEvent2;
#endif 	/* __IRTCSessionOperationCompleteEvent2_FWD_DEFINED__ */


#ifndef __IRTCParticipantStateChangeEvent_FWD_DEFINED__
#define __IRTCParticipantStateChangeEvent_FWD_DEFINED__
typedef interface IRTCParticipantStateChangeEvent IRTCParticipantStateChangeEvent;
#endif 	/* __IRTCParticipantStateChangeEvent_FWD_DEFINED__ */


#ifndef __IRTCMediaEvent_FWD_DEFINED__
#define __IRTCMediaEvent_FWD_DEFINED__
typedef interface IRTCMediaEvent IRTCMediaEvent;
#endif 	/* __IRTCMediaEvent_FWD_DEFINED__ */


#ifndef __IRTCIntensityEvent_FWD_DEFINED__
#define __IRTCIntensityEvent_FWD_DEFINED__
typedef interface IRTCIntensityEvent IRTCIntensityEvent;
#endif 	/* __IRTCIntensityEvent_FWD_DEFINED__ */


#ifndef __IRTCMessagingEvent_FWD_DEFINED__
#define __IRTCMessagingEvent_FWD_DEFINED__
typedef interface IRTCMessagingEvent IRTCMessagingEvent;
#endif 	/* __IRTCMessagingEvent_FWD_DEFINED__ */


#ifndef __IRTCBuddyEvent_FWD_DEFINED__
#define __IRTCBuddyEvent_FWD_DEFINED__
typedef interface IRTCBuddyEvent IRTCBuddyEvent;
#endif 	/* __IRTCBuddyEvent_FWD_DEFINED__ */


#ifndef __IRTCBuddyEvent2_FWD_DEFINED__
#define __IRTCBuddyEvent2_FWD_DEFINED__
typedef interface IRTCBuddyEvent2 IRTCBuddyEvent2;
#endif 	/* __IRTCBuddyEvent2_FWD_DEFINED__ */


#ifndef __IRTCWatcherEvent_FWD_DEFINED__
#define __IRTCWatcherEvent_FWD_DEFINED__
typedef interface IRTCWatcherEvent IRTCWatcherEvent;
#endif 	/* __IRTCWatcherEvent_FWD_DEFINED__ */


#ifndef __IRTCWatcherEvent2_FWD_DEFINED__
#define __IRTCWatcherEvent2_FWD_DEFINED__
typedef interface IRTCWatcherEvent2 IRTCWatcherEvent2;
#endif 	/* __IRTCWatcherEvent2_FWD_DEFINED__ */


#ifndef __IRTCBuddyGroupEvent_FWD_DEFINED__
#define __IRTCBuddyGroupEvent_FWD_DEFINED__
typedef interface IRTCBuddyGroupEvent IRTCBuddyGroupEvent;
#endif 	/* __IRTCBuddyGroupEvent_FWD_DEFINED__ */


#ifndef __IRTCInfoEvent_FWD_DEFINED__
#define __IRTCInfoEvent_FWD_DEFINED__
typedef interface IRTCInfoEvent IRTCInfoEvent;
#endif 	/* __IRTCInfoEvent_FWD_DEFINED__ */


#ifndef __IRTCMediaRequestEvent_FWD_DEFINED__
#define __IRTCMediaRequestEvent_FWD_DEFINED__
typedef interface IRTCMediaRequestEvent IRTCMediaRequestEvent;
#endif 	/* __IRTCMediaRequestEvent_FWD_DEFINED__ */


#ifndef __IRTCReInviteEvent_FWD_DEFINED__
#define __IRTCReInviteEvent_FWD_DEFINED__
typedef interface IRTCReInviteEvent IRTCReInviteEvent;
#endif 	/* __IRTCReInviteEvent_FWD_DEFINED__ */


#ifndef __IRTCPresencePropertyEvent_FWD_DEFINED__
#define __IRTCPresencePropertyEvent_FWD_DEFINED__
typedef interface IRTCPresencePropertyEvent IRTCPresencePropertyEvent;
#endif 	/* __IRTCPresencePropertyEvent_FWD_DEFINED__ */


#ifndef __IRTCPresenceDataEvent_FWD_DEFINED__
#define __IRTCPresenceDataEvent_FWD_DEFINED__
typedef interface IRTCPresenceDataEvent IRTCPresenceDataEvent;
#endif 	/* __IRTCPresenceDataEvent_FWD_DEFINED__ */


#ifndef __IRTCPresenceStatusEvent_FWD_DEFINED__
#define __IRTCPresenceStatusEvent_FWD_DEFINED__
typedef interface IRTCPresenceStatusEvent IRTCPresenceStatusEvent;
#endif 	/* __IRTCPresenceStatusEvent_FWD_DEFINED__ */


#ifndef __IRTCCollection_FWD_DEFINED__
#define __IRTCCollection_FWD_DEFINED__
typedef interface IRTCCollection IRTCCollection;
#endif 	/* __IRTCCollection_FWD_DEFINED__ */


#ifndef __IRTCEnumParticipants_FWD_DEFINED__
#define __IRTCEnumParticipants_FWD_DEFINED__
typedef interface IRTCEnumParticipants IRTCEnumParticipants;
#endif 	/* __IRTCEnumParticipants_FWD_DEFINED__ */


#ifndef __IRTCEnumProfiles_FWD_DEFINED__
#define __IRTCEnumProfiles_FWD_DEFINED__
typedef interface IRTCEnumProfiles IRTCEnumProfiles;
#endif 	/* __IRTCEnumProfiles_FWD_DEFINED__ */


#ifndef __IRTCEnumBuddies_FWD_DEFINED__
#define __IRTCEnumBuddies_FWD_DEFINED__
typedef interface IRTCEnumBuddies IRTCEnumBuddies;
#endif 	/* __IRTCEnumBuddies_FWD_DEFINED__ */


#ifndef __IRTCEnumWatchers_FWD_DEFINED__
#define __IRTCEnumWatchers_FWD_DEFINED__
typedef interface IRTCEnumWatchers IRTCEnumWatchers;
#endif 	/* __IRTCEnumWatchers_FWD_DEFINED__ */


#ifndef __IRTCEnumGroups_FWD_DEFINED__
#define __IRTCEnumGroups_FWD_DEFINED__
typedef interface IRTCEnumGroups IRTCEnumGroups;
#endif 	/* __IRTCEnumGroups_FWD_DEFINED__ */


#ifndef __IRTCPresenceContact_FWD_DEFINED__
#define __IRTCPresenceContact_FWD_DEFINED__
typedef interface IRTCPresenceContact IRTCPresenceContact;
#endif 	/* __IRTCPresenceContact_FWD_DEFINED__ */


#ifndef __IRTCBuddy_FWD_DEFINED__
#define __IRTCBuddy_FWD_DEFINED__
typedef interface IRTCBuddy IRTCBuddy;
#endif 	/* __IRTCBuddy_FWD_DEFINED__ */


#ifndef __IRTCBuddy2_FWD_DEFINED__
#define __IRTCBuddy2_FWD_DEFINED__
typedef interface IRTCBuddy2 IRTCBuddy2;
#endif 	/* __IRTCBuddy2_FWD_DEFINED__ */


#ifndef __IRTCWatcher_FWD_DEFINED__
#define __IRTCWatcher_FWD_DEFINED__
typedef interface IRTCWatcher IRTCWatcher;
#endif 	/* __IRTCWatcher_FWD_DEFINED__ */


#ifndef __IRTCWatcher2_FWD_DEFINED__
#define __IRTCWatcher2_FWD_DEFINED__
typedef interface IRTCWatcher2 IRTCWatcher2;
#endif 	/* __IRTCWatcher2_FWD_DEFINED__ */


#ifndef __IRTCBuddyGroup_FWD_DEFINED__
#define __IRTCBuddyGroup_FWD_DEFINED__
typedef interface IRTCBuddyGroup IRTCBuddyGroup;
#endif 	/* __IRTCBuddyGroup_FWD_DEFINED__ */


#ifndef __IRTCEventNotification_FWD_DEFINED__
#define __IRTCEventNotification_FWD_DEFINED__
typedef interface IRTCEventNotification IRTCEventNotification;
#endif 	/* __IRTCEventNotification_FWD_DEFINED__ */


#ifndef __IRTCDispatchEventNotification_FWD_DEFINED__
#define __IRTCDispatchEventNotification_FWD_DEFINED__
typedef interface IRTCDispatchEventNotification IRTCDispatchEventNotification;
#endif 	/* __IRTCDispatchEventNotification_FWD_DEFINED__ */


#ifndef __IRTCPortManager_FWD_DEFINED__
#define __IRTCPortManager_FWD_DEFINED__
typedef interface IRTCPortManager IRTCPortManager;
#endif 	/* __IRTCPortManager_FWD_DEFINED__ */


#ifndef __IRTCSessionPortManagement_FWD_DEFINED__
#define __IRTCSessionPortManagement_FWD_DEFINED__
typedef interface IRTCSessionPortManagement IRTCSessionPortManagement;
#endif 	/* __IRTCSessionPortManagement_FWD_DEFINED__ */


#ifndef __IRTCClientPortManagement_FWD_DEFINED__
#define __IRTCClientPortManagement_FWD_DEFINED__
typedef interface IRTCClientPortManagement IRTCClientPortManagement;
#endif 	/* __IRTCClientPortManagement_FWD_DEFINED__ */


#ifndef __IRTCUserSearch_FWD_DEFINED__
#define __IRTCUserSearch_FWD_DEFINED__
typedef interface IRTCUserSearch IRTCUserSearch;
#endif 	/* __IRTCUserSearch_FWD_DEFINED__ */


#ifndef __IRTCUserSearchQuery_FWD_DEFINED__
#define __IRTCUserSearchQuery_FWD_DEFINED__
typedef interface IRTCUserSearchQuery IRTCUserSearchQuery;
#endif 	/* __IRTCUserSearchQuery_FWD_DEFINED__ */


#ifndef __IRTCUserSearchResult_FWD_DEFINED__
#define __IRTCUserSearchResult_FWD_DEFINED__
typedef interface IRTCUserSearchResult IRTCUserSearchResult;
#endif 	/* __IRTCUserSearchResult_FWD_DEFINED__ */


#ifndef __IRTCEnumUserSearchResults_FWD_DEFINED__
#define __IRTCEnumUserSearchResults_FWD_DEFINED__
typedef interface IRTCEnumUserSearchResults IRTCEnumUserSearchResults;
#endif 	/* __IRTCEnumUserSearchResults_FWD_DEFINED__ */


#ifndef __IRTCUserSearchResultsEvent_FWD_DEFINED__
#define __IRTCUserSearchResultsEvent_FWD_DEFINED__
typedef interface IRTCUserSearchResultsEvent IRTCUserSearchResultsEvent;
#endif 	/* __IRTCUserSearchResultsEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionReferStatusEvent_FWD_DEFINED__
#define __IRTCSessionReferStatusEvent_FWD_DEFINED__
typedef interface IRTCSessionReferStatusEvent IRTCSessionReferStatusEvent;
#endif 	/* __IRTCSessionReferStatusEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionReferredEvent_FWD_DEFINED__
#define __IRTCSessionReferredEvent_FWD_DEFINED__
typedef interface IRTCSessionReferredEvent IRTCSessionReferredEvent;
#endif 	/* __IRTCSessionReferredEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionDescriptionManager_FWD_DEFINED__
#define __IRTCSessionDescriptionManager_FWD_DEFINED__
typedef interface IRTCSessionDescriptionManager IRTCSessionDescriptionManager;
#endif 	/* __IRTCSessionDescriptionManager_FWD_DEFINED__ */


#ifndef __IRTCEnumPresenceDevices_FWD_DEFINED__
#define __IRTCEnumPresenceDevices_FWD_DEFINED__
typedef interface IRTCEnumPresenceDevices IRTCEnumPresenceDevices;
#endif 	/* __IRTCEnumPresenceDevices_FWD_DEFINED__ */


#ifndef __IRTCPresenceDevice_FWD_DEFINED__
#define __IRTCPresenceDevice_FWD_DEFINED__
typedef interface IRTCPresenceDevice IRTCPresenceDevice;
#endif 	/* __IRTCPresenceDevice_FWD_DEFINED__ */


#ifndef __IRTCProfile_FWD_DEFINED__
#define __IRTCProfile_FWD_DEFINED__
typedef interface IRTCProfile IRTCProfile;
#endif 	/* __IRTCProfile_FWD_DEFINED__ */


#ifndef __IRTCProfile2_FWD_DEFINED__
#define __IRTCProfile2_FWD_DEFINED__
typedef interface IRTCProfile2 IRTCProfile2;
#endif 	/* __IRTCProfile2_FWD_DEFINED__ */


#ifndef __IRTCEnumProfiles_FWD_DEFINED__
#define __IRTCEnumProfiles_FWD_DEFINED__
typedef interface IRTCEnumProfiles IRTCEnumProfiles;
#endif 	/* __IRTCEnumProfiles_FWD_DEFINED__ */


#ifndef __IRTCSession_FWD_DEFINED__
#define __IRTCSession_FWD_DEFINED__
typedef interface IRTCSession IRTCSession;
#endif 	/* __IRTCSession_FWD_DEFINED__ */


#ifndef __IRTCSession2_FWD_DEFINED__
#define __IRTCSession2_FWD_DEFINED__
typedef interface IRTCSession2 IRTCSession2;
#endif 	/* __IRTCSession2_FWD_DEFINED__ */


#ifndef __IRTCSessionCallControl_FWD_DEFINED__
#define __IRTCSessionCallControl_FWD_DEFINED__
typedef interface IRTCSessionCallControl IRTCSessionCallControl;
#endif 	/* __IRTCSessionCallControl_FWD_DEFINED__ */


#ifndef __IRTCParticipant_FWD_DEFINED__
#define __IRTCParticipant_FWD_DEFINED__
typedef interface IRTCParticipant IRTCParticipant;
#endif 	/* __IRTCParticipant_FWD_DEFINED__ */


#ifndef __IRTCEnumParticipants_FWD_DEFINED__
#define __IRTCEnumParticipants_FWD_DEFINED__
typedef interface IRTCEnumParticipants IRTCEnumParticipants;
#endif 	/* __IRTCEnumParticipants_FWD_DEFINED__ */


#ifndef __IRTCCollection_FWD_DEFINED__
#define __IRTCCollection_FWD_DEFINED__
typedef interface IRTCCollection IRTCCollection;
#endif 	/* __IRTCCollection_FWD_DEFINED__ */


#ifndef __IRTCPresenceContact_FWD_DEFINED__
#define __IRTCPresenceContact_FWD_DEFINED__
typedef interface IRTCPresenceContact IRTCPresenceContact;
#endif 	/* __IRTCPresenceContact_FWD_DEFINED__ */


#ifndef __IRTCBuddy_FWD_DEFINED__
#define __IRTCBuddy_FWD_DEFINED__
typedef interface IRTCBuddy IRTCBuddy;
#endif 	/* __IRTCBuddy_FWD_DEFINED__ */


#ifndef __IRTCBuddy2_FWD_DEFINED__
#define __IRTCBuddy2_FWD_DEFINED__
typedef interface IRTCBuddy2 IRTCBuddy2;
#endif 	/* __IRTCBuddy2_FWD_DEFINED__ */


#ifndef __IRTCEnumBuddies_FWD_DEFINED__
#define __IRTCEnumBuddies_FWD_DEFINED__
typedef interface IRTCEnumBuddies IRTCEnumBuddies;
#endif 	/* __IRTCEnumBuddies_FWD_DEFINED__ */


#ifndef __IRTCWatcher_FWD_DEFINED__
#define __IRTCWatcher_FWD_DEFINED__
typedef interface IRTCWatcher IRTCWatcher;
#endif 	/* __IRTCWatcher_FWD_DEFINED__ */


#ifndef __IRTCWatcher2_FWD_DEFINED__
#define __IRTCWatcher2_FWD_DEFINED__
typedef interface IRTCWatcher2 IRTCWatcher2;
#endif 	/* __IRTCWatcher2_FWD_DEFINED__ */


#ifndef __IRTCEnumWatchers_FWD_DEFINED__
#define __IRTCEnumWatchers_FWD_DEFINED__
typedef interface IRTCEnumWatchers IRTCEnumWatchers;
#endif 	/* __IRTCEnumWatchers_FWD_DEFINED__ */


#ifndef __IRTCBuddyGroup_FWD_DEFINED__
#define __IRTCBuddyGroup_FWD_DEFINED__
typedef interface IRTCBuddyGroup IRTCBuddyGroup;
#endif 	/* __IRTCBuddyGroup_FWD_DEFINED__ */


#ifndef __IRTCEnumGroups_FWD_DEFINED__
#define __IRTCEnumGroups_FWD_DEFINED__
typedef interface IRTCEnumGroups IRTCEnumGroups;
#endif 	/* __IRTCEnumGroups_FWD_DEFINED__ */


#ifndef __IRTCUserSearchQuery_FWD_DEFINED__
#define __IRTCUserSearchQuery_FWD_DEFINED__
typedef interface IRTCUserSearchQuery IRTCUserSearchQuery;
#endif 	/* __IRTCUserSearchQuery_FWD_DEFINED__ */


#ifndef __IRTCUserSearchResult_FWD_DEFINED__
#define __IRTCUserSearchResult_FWD_DEFINED__
typedef interface IRTCUserSearchResult IRTCUserSearchResult;
#endif 	/* __IRTCUserSearchResult_FWD_DEFINED__ */


#ifndef __IRTCEnumUserSearchResults_FWD_DEFINED__
#define __IRTCEnumUserSearchResults_FWD_DEFINED__
typedef interface IRTCEnumUserSearchResults IRTCEnumUserSearchResults;
#endif 	/* __IRTCEnumUserSearchResults_FWD_DEFINED__ */


#ifndef __IRTCEventNotification_FWD_DEFINED__
#define __IRTCEventNotification_FWD_DEFINED__
typedef interface IRTCEventNotification IRTCEventNotification;
#endif 	/* __IRTCEventNotification_FWD_DEFINED__ */


#ifndef __IRTCClientEvent_FWD_DEFINED__
#define __IRTCClientEvent_FWD_DEFINED__
typedef interface IRTCClientEvent IRTCClientEvent;
#endif 	/* __IRTCClientEvent_FWD_DEFINED__ */


#ifndef __IRTCRegistrationStateChangeEvent_FWD_DEFINED__
#define __IRTCRegistrationStateChangeEvent_FWD_DEFINED__
typedef interface IRTCRegistrationStateChangeEvent IRTCRegistrationStateChangeEvent;
#endif 	/* __IRTCRegistrationStateChangeEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionStateChangeEvent_FWD_DEFINED__
#define __IRTCSessionStateChangeEvent_FWD_DEFINED__
typedef interface IRTCSessionStateChangeEvent IRTCSessionStateChangeEvent;
#endif 	/* __IRTCSessionStateChangeEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionStateChangeEvent2_FWD_DEFINED__
#define __IRTCSessionStateChangeEvent2_FWD_DEFINED__
typedef interface IRTCSessionStateChangeEvent2 IRTCSessionStateChangeEvent2;
#endif 	/* __IRTCSessionStateChangeEvent2_FWD_DEFINED__ */


#ifndef __IRTCSessionOperationCompleteEvent_FWD_DEFINED__
#define __IRTCSessionOperationCompleteEvent_FWD_DEFINED__
typedef interface IRTCSessionOperationCompleteEvent IRTCSessionOperationCompleteEvent;
#endif 	/* __IRTCSessionOperationCompleteEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionOperationCompleteEvent2_FWD_DEFINED__
#define __IRTCSessionOperationCompleteEvent2_FWD_DEFINED__
typedef interface IRTCSessionOperationCompleteEvent2 IRTCSessionOperationCompleteEvent2;
#endif 	/* __IRTCSessionOperationCompleteEvent2_FWD_DEFINED__ */


#ifndef __IRTCParticipantStateChangeEvent_FWD_DEFINED__
#define __IRTCParticipantStateChangeEvent_FWD_DEFINED__
typedef interface IRTCParticipantStateChangeEvent IRTCParticipantStateChangeEvent;
#endif 	/* __IRTCParticipantStateChangeEvent_FWD_DEFINED__ */


#ifndef __IRTCMediaEvent_FWD_DEFINED__
#define __IRTCMediaEvent_FWD_DEFINED__
typedef interface IRTCMediaEvent IRTCMediaEvent;
#endif 	/* __IRTCMediaEvent_FWD_DEFINED__ */


#ifndef __IRTCIntensityEvent_FWD_DEFINED__
#define __IRTCIntensityEvent_FWD_DEFINED__
typedef interface IRTCIntensityEvent IRTCIntensityEvent;
#endif 	/* __IRTCIntensityEvent_FWD_DEFINED__ */


#ifndef __IRTCMessagingEvent_FWD_DEFINED__
#define __IRTCMessagingEvent_FWD_DEFINED__
typedef interface IRTCMessagingEvent IRTCMessagingEvent;
#endif 	/* __IRTCMessagingEvent_FWD_DEFINED__ */


#ifndef __IRTCBuddyEvent_FWD_DEFINED__
#define __IRTCBuddyEvent_FWD_DEFINED__
typedef interface IRTCBuddyEvent IRTCBuddyEvent;
#endif 	/* __IRTCBuddyEvent_FWD_DEFINED__ */


#ifndef __IRTCBuddyEvent2_FWD_DEFINED__
#define __IRTCBuddyEvent2_FWD_DEFINED__
typedef interface IRTCBuddyEvent2 IRTCBuddyEvent2;
#endif 	/* __IRTCBuddyEvent2_FWD_DEFINED__ */


#ifndef __IRTCWatcherEvent_FWD_DEFINED__
#define __IRTCWatcherEvent_FWD_DEFINED__
typedef interface IRTCWatcherEvent IRTCWatcherEvent;
#endif 	/* __IRTCWatcherEvent_FWD_DEFINED__ */


#ifndef __IRTCPortManager_FWD_DEFINED__
#define __IRTCPortManager_FWD_DEFINED__
typedef interface IRTCPortManager IRTCPortManager;
#endif 	/* __IRTCPortManager_FWD_DEFINED__ */


#ifndef __IRTCSessionPortManagement_FWD_DEFINED__
#define __IRTCSessionPortManagement_FWD_DEFINED__
typedef interface IRTCSessionPortManagement IRTCSessionPortManagement;
#endif 	/* __IRTCSessionPortManagement_FWD_DEFINED__ */


#ifndef __IRTCClientPortManagement_FWD_DEFINED__
#define __IRTCClientPortManagement_FWD_DEFINED__
typedef interface IRTCClientPortManagement IRTCClientPortManagement;
#endif 	/* __IRTCClientPortManagement_FWD_DEFINED__ */


#ifndef __IRTCWatcherEvent2_FWD_DEFINED__
#define __IRTCWatcherEvent2_FWD_DEFINED__
typedef interface IRTCWatcherEvent2 IRTCWatcherEvent2;
#endif 	/* __IRTCWatcherEvent2_FWD_DEFINED__ */


#ifndef __IRTCBuddyGroupEvent_FWD_DEFINED__
#define __IRTCBuddyGroupEvent_FWD_DEFINED__
typedef interface IRTCBuddyGroupEvent IRTCBuddyGroupEvent;
#endif 	/* __IRTCBuddyGroupEvent_FWD_DEFINED__ */


#ifndef __IRTCProfileEvent_FWD_DEFINED__
#define __IRTCProfileEvent_FWD_DEFINED__
typedef interface IRTCProfileEvent IRTCProfileEvent;
#endif 	/* __IRTCProfileEvent_FWD_DEFINED__ */


#ifndef __IRTCProfileEvent2_FWD_DEFINED__
#define __IRTCProfileEvent2_FWD_DEFINED__
typedef interface IRTCProfileEvent2 IRTCProfileEvent2;
#endif 	/* __IRTCProfileEvent2_FWD_DEFINED__ */


#ifndef __IRTCUserSearchResultsEvent_FWD_DEFINED__
#define __IRTCUserSearchResultsEvent_FWD_DEFINED__
typedef interface IRTCUserSearchResultsEvent IRTCUserSearchResultsEvent;
#endif 	/* __IRTCUserSearchResultsEvent_FWD_DEFINED__ */


#ifndef __IRTCInfoEvent_FWD_DEFINED__
#define __IRTCInfoEvent_FWD_DEFINED__
typedef interface IRTCInfoEvent IRTCInfoEvent;
#endif 	/* __IRTCInfoEvent_FWD_DEFINED__ */


#ifndef __IRTCRoamingEvent_FWD_DEFINED__
#define __IRTCRoamingEvent_FWD_DEFINED__
typedef interface IRTCRoamingEvent IRTCRoamingEvent;
#endif 	/* __IRTCRoamingEvent_FWD_DEFINED__ */


#ifndef __IRTCMediaRequestEvent_FWD_DEFINED__
#define __IRTCMediaRequestEvent_FWD_DEFINED__
typedef interface IRTCMediaRequestEvent IRTCMediaRequestEvent;
#endif 	/* __IRTCMediaRequestEvent_FWD_DEFINED__ */


#ifndef __IRTCReInviteEvent_FWD_DEFINED__
#define __IRTCReInviteEvent_FWD_DEFINED__
typedef interface IRTCReInviteEvent IRTCReInviteEvent;
#endif 	/* __IRTCReInviteEvent_FWD_DEFINED__ */


#ifndef __IRTCPresencePropertyEvent_FWD_DEFINED__
#define __IRTCPresencePropertyEvent_FWD_DEFINED__
typedef interface IRTCPresencePropertyEvent IRTCPresencePropertyEvent;
#endif 	/* __IRTCPresencePropertyEvent_FWD_DEFINED__ */


#ifndef __IRTCPresenceDataEvent_FWD_DEFINED__
#define __IRTCPresenceDataEvent_FWD_DEFINED__
typedef interface IRTCPresenceDataEvent IRTCPresenceDataEvent;
#endif 	/* __IRTCPresenceDataEvent_FWD_DEFINED__ */


#ifndef __IRTCPresenceStatusEvent_FWD_DEFINED__
#define __IRTCPresenceStatusEvent_FWD_DEFINED__
typedef interface IRTCPresenceStatusEvent IRTCPresenceStatusEvent;
#endif 	/* __IRTCPresenceStatusEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionReferStatusEvent_FWD_DEFINED__
#define __IRTCSessionReferStatusEvent_FWD_DEFINED__
typedef interface IRTCSessionReferStatusEvent IRTCSessionReferStatusEvent;
#endif 	/* __IRTCSessionReferStatusEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionReferredEvent_FWD_DEFINED__
#define __IRTCSessionReferredEvent_FWD_DEFINED__
typedef interface IRTCSessionReferredEvent IRTCSessionReferredEvent;
#endif 	/* __IRTCSessionReferredEvent_FWD_DEFINED__ */


#ifndef __IRTCSessionDescriptionManager_FWD_DEFINED__
#define __IRTCSessionDescriptionManager_FWD_DEFINED__
typedef interface IRTCSessionDescriptionManager IRTCSessionDescriptionManager;
#endif 	/* __IRTCSessionDescriptionManager_FWD_DEFINED__ */


#ifndef __IRTCDispatchEventNotification_FWD_DEFINED__
#define __IRTCDispatchEventNotification_FWD_DEFINED__
typedef interface IRTCDispatchEventNotification IRTCDispatchEventNotification;
#endif 	/* __IRTCDispatchEventNotification_FWD_DEFINED__ */


#ifndef __RTCClient_FWD_DEFINED__
#define __RTCClient_FWD_DEFINED__

#ifdef __cplusplus
typedef class RTCClient RTCClient;
#else
typedef struct RTCClient RTCClient;
#endif /* __cplusplus */

#endif 	/* __RTCClient_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "control.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_rtccore_0000 */
/* [local] */ 

//  Copyright (c) Microsoft Corporation.  All rights reserved.
typedef 
enum RTC_AUDIO_DEVICE
    {	RTCAD_SPEAKER	= 0,
	RTCAD_MICROPHONE	= RTCAD_SPEAKER + 1
    }	RTC_AUDIO_DEVICE;

typedef 
enum RTC_VIDEO_DEVICE
    {	RTCVD_RECEIVE	= 0,
	RTCVD_PREVIEW	= RTCVD_RECEIVE + 1
    }	RTC_VIDEO_DEVICE;

typedef 
enum RTC_EVENT
    {	RTCE_CLIENT	= 0,
	RTCE_REGISTRATION_STATE_CHANGE	= RTCE_CLIENT + 1,
	RTCE_SESSION_STATE_CHANGE	= RTCE_REGISTRATION_STATE_CHANGE + 1,
	RTCE_SESSION_OPERATION_COMPLETE	= RTCE_SESSION_STATE_CHANGE + 1,
	RTCE_PARTICIPANT_STATE_CHANGE	= RTCE_SESSION_OPERATION_COMPLETE + 1,
	RTCE_MEDIA	= RTCE_PARTICIPANT_STATE_CHANGE + 1,
	RTCE_INTENSITY	= RTCE_MEDIA + 1,
	RTCE_MESSAGING	= RTCE_INTENSITY + 1,
	RTCE_BUDDY	= RTCE_MESSAGING + 1,
	RTCE_WATCHER	= RTCE_BUDDY + 1,
	RTCE_PROFILE	= RTCE_WATCHER + 1,
	RTCE_USERSEARCH	= RTCE_PROFILE + 1,
	RTCE_INFO	= RTCE_USERSEARCH + 1,
	RTCE_GROUP	= RTCE_INFO + 1,
	RTCE_MEDIA_REQUEST	= RTCE_GROUP + 1,
	RTCE_ROAMING	= RTCE_MEDIA_REQUEST + 1,
	RTCE_PRESENCE_PROPERTY	= RTCE_ROAMING + 1,
	RTCE_PRESENCE_DATA	= RTCE_PRESENCE_PROPERTY + 1,
	RTCE_PRESENCE_STATUS	= RTCE_PRESENCE_DATA + 1,
	RTCE_SESSION_REFER_STATUS	= RTCE_PRESENCE_STATUS + 1,
	RTCE_SESSION_REFERRED	= RTCE_SESSION_REFER_STATUS + 1,
	RTCE_REINVITE	= RTCE_SESSION_REFERRED + 1
    }	RTC_EVENT;

typedef 
enum RTC_LISTEN_MODE
    {	RTCLM_NONE	= 0,
	RTCLM_DYNAMIC	= RTCLM_NONE + 1,
	RTCLM_BOTH	= RTCLM_DYNAMIC + 1
    }	RTC_LISTEN_MODE;

typedef 
enum RTC_CLIENT_EVENT_TYPE
    {	RTCCET_VOLUME_CHANGE	= 0,
	RTCCET_DEVICE_CHANGE	= RTCCET_VOLUME_CHANGE + 1,
	RTCCET_NETWORK_QUALITY_CHANGE	= RTCCET_DEVICE_CHANGE + 1,
	RTCCET_ASYNC_CLEANUP_DONE	= RTCCET_NETWORK_QUALITY_CHANGE + 1
    }	RTC_CLIENT_EVENT_TYPE;

typedef 
enum RTC_BUDDY_EVENT_TYPE
    {	RTCBET_BUDDY_ADD	= 0,
	RTCBET_BUDDY_REMOVE	= RTCBET_BUDDY_ADD + 1,
	RTCBET_BUDDY_UPDATE	= RTCBET_BUDDY_REMOVE + 1,
	RTCBET_BUDDY_STATE_CHANGE	= RTCBET_BUDDY_UPDATE + 1,
	RTCBET_BUDDY_ROAMED	= RTCBET_BUDDY_STATE_CHANGE + 1,
	RTCBET_BUDDY_SUBSCRIBED	= RTCBET_BUDDY_ROAMED + 1
    }	RTC_BUDDY_EVENT_TYPE;

typedef 
enum RTC_WATCHER_EVENT_TYPE
    {	RTCWET_WATCHER_ADD	= 0,
	RTCWET_WATCHER_REMOVE	= RTCWET_WATCHER_ADD + 1,
	RTCWET_WATCHER_UPDATE	= RTCWET_WATCHER_REMOVE + 1,
	RTCWET_WATCHER_OFFERING	= RTCWET_WATCHER_UPDATE + 1,
	RTCWET_WATCHER_ROAMED	= RTCWET_WATCHER_OFFERING + 1
    }	RTC_WATCHER_EVENT_TYPE;

typedef 
enum RTC_GROUP_EVENT_TYPE
    {	RTCGET_GROUP_ADD	= 0,
	RTCGET_GROUP_REMOVE	= RTCGET_GROUP_ADD + 1,
	RTCGET_GROUP_UPDATE	= RTCGET_GROUP_REMOVE + 1,
	RTCGET_GROUP_BUDDY_ADD	= RTCGET_GROUP_UPDATE + 1,
	RTCGET_GROUP_BUDDY_REMOVE	= RTCGET_GROUP_BUDDY_ADD + 1,
	RTCGET_GROUP_ROAMED	= RTCGET_GROUP_BUDDY_REMOVE + 1
    }	RTC_GROUP_EVENT_TYPE;

typedef 
enum RTC_TERMINATE_REASON
    {	RTCTR_NORMAL	= 0,
	RTCTR_DND	= RTCTR_NORMAL + 1,
	RTCTR_BUSY	= RTCTR_DND + 1,
	RTCTR_REJECT	= RTCTR_BUSY + 1,
	RTCTR_TIMEOUT	= RTCTR_REJECT + 1,
	RTCTR_SHUTDOWN	= RTCTR_TIMEOUT + 1,
	RTCTR_INSUFFICIENT_SECURITY_LEVEL	= RTCTR_SHUTDOWN + 1
    }	RTC_TERMINATE_REASON;

typedef 
enum RTC_REGISTRATION_STATE
    {	RTCRS_NOT_REGISTERED	= 0,
	RTCRS_REGISTERING	= RTCRS_NOT_REGISTERED + 1,
	RTCRS_REGISTERED	= RTCRS_REGISTERING + 1,
	RTCRS_REJECTED	= RTCRS_REGISTERED + 1,
	RTCRS_UNREGISTERING	= RTCRS_REJECTED + 1,
	RTCRS_ERROR	= RTCRS_UNREGISTERING + 1,
	RTCRS_LOGGED_OFF	= RTCRS_ERROR + 1,
	RTCRS_LOCAL_PA_LOGGED_OFF	= RTCRS_LOGGED_OFF + 1,
	RTCRS_REMOTE_PA_LOGGED_OFF	= RTCRS_LOCAL_PA_LOGGED_OFF + 1
    }	RTC_REGISTRATION_STATE;

typedef 
enum RTC_SESSION_STATE
    {	RTCSS_IDLE	= 0,
	RTCSS_INCOMING	= RTCSS_IDLE + 1,
	RTCSS_ANSWERING	= RTCSS_INCOMING + 1,
	RTCSS_INPROGRESS	= RTCSS_ANSWERING + 1,
	RTCSS_CONNECTED	= RTCSS_INPROGRESS + 1,
	RTCSS_DISCONNECTED	= RTCSS_CONNECTED + 1,
	RTCSS_HOLD	= RTCSS_DISCONNECTED + 1,
	RTCSS_REFER	= RTCSS_HOLD + 1
    }	RTC_SESSION_STATE;

typedef 
enum RTC_PARTICIPANT_STATE
    {	RTCPS_IDLE	= 0,
	RTCPS_PENDING	= RTCPS_IDLE + 1,
	RTCPS_INCOMING	= RTCPS_PENDING + 1,
	RTCPS_ANSWERING	= RTCPS_INCOMING + 1,
	RTCPS_INPROGRESS	= RTCPS_ANSWERING + 1,
	RTCPS_ALERTING	= RTCPS_INPROGRESS + 1,
	RTCPS_CONNECTED	= RTCPS_ALERTING + 1,
	RTCPS_DISCONNECTING	= RTCPS_CONNECTED + 1,
	RTCPS_DISCONNECTED	= RTCPS_DISCONNECTING + 1
    }	RTC_PARTICIPANT_STATE;

typedef 
enum RTC_WATCHER_STATE
    {	RTCWS_UNKNOWN	= 0,
	RTCWS_OFFERING	= RTCWS_UNKNOWN + 1,
	RTCWS_ALLOWED	= RTCWS_OFFERING + 1,
	RTCWS_BLOCKED	= RTCWS_ALLOWED + 1,
	RTCWS_DENIED	= RTCWS_BLOCKED + 1,
	RTCWS_PROMPT	= RTCWS_DENIED + 1
    }	RTC_WATCHER_STATE;

typedef 
enum RTC_ACE_SCOPE
    {	RTCAS_SCOPE_USER	= 0,
	RTCAS_SCOPE_DOMAIN	= RTCAS_SCOPE_USER + 1,
	RTCAS_SCOPE_ALL	= RTCAS_SCOPE_DOMAIN + 1
    }	RTC_ACE_SCOPE;

typedef 
enum RTC_OFFER_WATCHER_MODE
    {	RTCOWM_OFFER_WATCHER_EVENT	= 0,
	RTCOWM_AUTOMATICALLY_ADD_WATCHER	= RTCOWM_OFFER_WATCHER_EVENT + 1
    }	RTC_OFFER_WATCHER_MODE;

typedef 
enum RTC_WATCHER_MATCH_MODE
    {	RTCWMM_EXACT_MATCH	= 0,
	RTCWMM_BEST_ACE_MATCH	= RTCWMM_EXACT_MATCH + 1
    }	RTC_WATCHER_MATCH_MODE;

typedef 
enum RTC_PRIVACY_MODE
    {	RTCPM_BLOCK_LIST_EXCLUDED	= 0,
	RTCPM_ALLOW_LIST_ONLY	= RTCPM_BLOCK_LIST_EXCLUDED + 1
    }	RTC_PRIVACY_MODE;

typedef 
enum RTC_SESSION_TYPE
    {	RTCST_PC_TO_PC	= 0,
	RTCST_PC_TO_PHONE	= RTCST_PC_TO_PC + 1,
	RTCST_PHONE_TO_PHONE	= RTCST_PC_TO_PHONE + 1,
	RTCST_IM	= RTCST_PHONE_TO_PHONE + 1,
	RTCST_MULTIPARTY_IM	= RTCST_IM + 1,
	RTCST_APPLICATION	= RTCST_MULTIPARTY_IM + 1
    }	RTC_SESSION_TYPE;

typedef 
enum RTC_PRESENCE_STATUS
    {	RTCXS_PRESENCE_OFFLINE	= 0,
	RTCXS_PRESENCE_ONLINE	= RTCXS_PRESENCE_OFFLINE + 1,
	RTCXS_PRESENCE_AWAY	= RTCXS_PRESENCE_ONLINE + 1,
	RTCXS_PRESENCE_IDLE	= RTCXS_PRESENCE_AWAY + 1,
	RTCXS_PRESENCE_BUSY	= RTCXS_PRESENCE_IDLE + 1,
	RTCXS_PRESENCE_BE_RIGHT_BACK	= RTCXS_PRESENCE_BUSY + 1,
	RTCXS_PRESENCE_ON_THE_PHONE	= RTCXS_PRESENCE_BE_RIGHT_BACK + 1,
	RTCXS_PRESENCE_OUT_TO_LUNCH	= RTCXS_PRESENCE_ON_THE_PHONE + 1
    }	RTC_PRESENCE_STATUS;

typedef 
enum RTC_BUDDY_SUBSCRIPTION_TYPE
    {	RTCBT_SUBSCRIBED	= 0,
	RTCBT_ALWAYS_OFFLINE	= RTCBT_SUBSCRIBED + 1,
	RTCBT_ALWAYS_ONLINE	= RTCBT_ALWAYS_OFFLINE + 1
    }	RTC_BUDDY_SUBSCRIPTION_TYPE;

typedef 
enum RTC_MEDIA_EVENT_TYPE
    {	RTCMET_STOPPED	= 0,
	RTCMET_STARTED	= RTCMET_STOPPED + 1,
	RTCMET_FAILED	= RTCMET_STARTED + 1
    }	RTC_MEDIA_EVENT_TYPE;

typedef 
enum RTC_MEDIA_EVENT_REASON
    {	RTCMER_NORMAL	= 0,
	RTCMER_HOLD	= RTCMER_NORMAL + 1,
	RTCMER_TIMEOUT	= RTCMER_HOLD + 1,
	RTCMER_BAD_DEVICE	= RTCMER_TIMEOUT + 1,
	RTCMER_NO_PORT	= RTCMER_BAD_DEVICE + 1,
	RTCMER_PORT_MAPPING_FAILED	= RTCMER_NO_PORT + 1,
	RTCMER_REMOTE_REQUEST	= RTCMER_PORT_MAPPING_FAILED + 1
    }	RTC_MEDIA_EVENT_REASON;

typedef 
enum RTC_MESSAGING_EVENT_TYPE
    {	RTCMSET_MESSAGE	= 0,
	RTCMSET_STATUS	= RTCMSET_MESSAGE + 1
    }	RTC_MESSAGING_EVENT_TYPE;

typedef 
enum RTC_MESSAGING_USER_STATUS
    {	RTCMUS_IDLE	= 0,
	RTCMUS_TYPING	= RTCMUS_IDLE + 1
    }	RTC_MESSAGING_USER_STATUS;

typedef 
enum RTC_DTMF
    {	RTC_DTMF_0	= 0,
	RTC_DTMF_1	= RTC_DTMF_0 + 1,
	RTC_DTMF_2	= RTC_DTMF_1 + 1,
	RTC_DTMF_3	= RTC_DTMF_2 + 1,
	RTC_DTMF_4	= RTC_DTMF_3 + 1,
	RTC_DTMF_5	= RTC_DTMF_4 + 1,
	RTC_DTMF_6	= RTC_DTMF_5 + 1,
	RTC_DTMF_7	= RTC_DTMF_6 + 1,
	RTC_DTMF_8	= RTC_DTMF_7 + 1,
	RTC_DTMF_9	= RTC_DTMF_8 + 1,
	RTC_DTMF_STAR	= RTC_DTMF_9 + 1,
	RTC_DTMF_POUND	= RTC_DTMF_STAR + 1,
	RTC_DTMF_A	= RTC_DTMF_POUND + 1,
	RTC_DTMF_B	= RTC_DTMF_A + 1,
	RTC_DTMF_C	= RTC_DTMF_B + 1,
	RTC_DTMF_D	= RTC_DTMF_C + 1,
	RTC_DTMF_FLASH	= RTC_DTMF_D + 1
    }	RTC_DTMF;

typedef 
enum RTC_PROVIDER_URI
    {	RTCPU_URIHOMEPAGE	= 0,
	RTCPU_URIHELPDESK	= RTCPU_URIHOMEPAGE + 1,
	RTCPU_URIPERSONALACCOUNT	= RTCPU_URIHELPDESK + 1,
	RTCPU_URIDISPLAYDURINGCALL	= RTCPU_URIPERSONALACCOUNT + 1,
	RTCPU_URIDISPLAYDURINGIDLE	= RTCPU_URIDISPLAYDURINGCALL + 1
    }	RTC_PROVIDER_URI;

typedef 
enum RTC_RING_TYPE
    {	RTCRT_PHONE	= 0,
	RTCRT_MESSAGE	= RTCRT_PHONE + 1,
	RTCRT_RINGBACK	= RTCRT_MESSAGE + 1
    }	RTC_RING_TYPE;

typedef 
enum RTC_T120_APPLET
    {	RTCTA_WHITEBOARD	= 0,
	RTCTA_APPSHARING	= RTCTA_WHITEBOARD + 1
    }	RTC_T120_APPLET;

typedef 
enum RTC_PORT_TYPE
    {	RTCPT_AUDIO_RTP	= 0,
	RTCPT_AUDIO_RTCP	= RTCPT_AUDIO_RTP + 1,
	RTCPT_VIDEO_RTP	= RTCPT_AUDIO_RTCP + 1,
	RTCPT_VIDEO_RTCP	= RTCPT_VIDEO_RTP + 1,
	RTCPT_SIP	= RTCPT_VIDEO_RTCP + 1
    }	RTC_PORT_TYPE;

typedef 
enum RTC_USER_SEARCH_COLUMN
    {	RTCUSC_URI	= 0,
	RTCUSC_DISPLAYNAME	= RTCUSC_URI + 1,
	RTCUSC_TITLE	= RTCUSC_DISPLAYNAME + 1,
	RTCUSC_OFFICE	= RTCUSC_TITLE + 1,
	RTCUSC_PHONE	= RTCUSC_OFFICE + 1,
	RTCUSC_COMPANY	= RTCUSC_PHONE + 1,
	RTCUSC_CITY	= RTCUSC_COMPANY + 1,
	RTCUSC_STATE	= RTCUSC_CITY + 1,
	RTCUSC_COUNTRY	= RTCUSC_STATE + 1,
	RTCUSC_EMAIL	= RTCUSC_COUNTRY + 1
    }	RTC_USER_SEARCH_COLUMN;

typedef 
enum RTC_USER_SEARCH_PREFERENCE
    {	RTCUSP_MAX_MATCHES	= 0,
	RTCUSP_TIME_LIMIT	= RTCUSP_MAX_MATCHES + 1
    }	RTC_USER_SEARCH_PREFERENCE;

typedef 
enum RTC_ROAMING_EVENT_TYPE
    {	RTCRET_BUDDY_ROAMING	= 0,
	RTCRET_WATCHER_ROAMING	= RTCRET_BUDDY_ROAMING + 1,
	RTCRET_PRESENCE_ROAMING	= RTCRET_WATCHER_ROAMING + 1,
	RTCRET_PROFILE_ROAMING	= RTCRET_PRESENCE_ROAMING + 1,
	RTCRET_WPENDING_ROAMING	= RTCRET_PROFILE_ROAMING + 1
    }	RTC_ROAMING_EVENT_TYPE;

typedef 
enum RTC_PROFILE_EVENT_TYPE
    {	RTCPFET_PROFILE_GET	= 0,
	RTCPFET_PROFILE_UPDATE	= RTCPFET_PROFILE_GET + 1
    }	RTC_PROFILE_EVENT_TYPE;

typedef 
enum RTC_ANSWER_MODE
    {	RTCAM_OFFER_SESSION_EVENT	= 0,
	RTCAM_AUTOMATICALLY_ACCEPT	= RTCAM_OFFER_SESSION_EVENT + 1,
	RTCAM_AUTOMATICALLY_REJECT	= RTCAM_AUTOMATICALLY_ACCEPT + 1,
	RTCAM_NOT_SUPPORTED	= RTCAM_AUTOMATICALLY_REJECT + 1
    }	RTC_ANSWER_MODE;

typedef 
enum RTC_SESSION_REFER_STATUS
    {	RTCSRS_REFERRING	= 0,
	RTCSRS_ACCEPTED	= RTCSRS_REFERRING + 1,
	RTCSRS_ERROR	= RTCSRS_ACCEPTED + 1,
	RTCSRS_REJECTED	= RTCSRS_ERROR + 1,
	RTCSRS_DROPPED	= RTCSRS_REJECTED + 1,
	RTCSRS_DONE	= RTCSRS_DROPPED + 1
    }	RTC_SESSION_REFER_STATUS;

typedef 
enum RTC_PRESENCE_PROPERTY
    {	RTCPP_PHONENUMBER	= 0,
	RTCPP_DISPLAYNAME	= RTCPP_PHONENUMBER + 1,
	RTCPP_EMAIL	= RTCPP_DISPLAYNAME + 1,
	RTCPP_DEVICE_NAME	= RTCPP_EMAIL + 1,
	RTCPP_MULTIPLE	= RTCPP_DEVICE_NAME + 1
    }	RTC_PRESENCE_PROPERTY;

typedef 
enum RTC_SECURITY_TYPE
    {	RTCSECT_AUDIO_VIDEO_MEDIA_ENCRYPTION	= 0,
	RTCSECT_T120_MEDIA_ENCRYPTION	= RTCSECT_AUDIO_VIDEO_MEDIA_ENCRYPTION + 1
    }	RTC_SECURITY_TYPE;

typedef 
enum RTC_SECURITY_LEVEL
    {	RTCSECL_UNSUPPORTED	= 1,
	RTCSECL_SUPPORTED	= RTCSECL_UNSUPPORTED + 1,
	RTCSECL_REQUIRED	= RTCSECL_SUPPORTED + 1
    }	RTC_SECURITY_LEVEL;

typedef 
enum RTC_REINVITE_STATE
    {	RTCRIN_INCOMING	= 0,
	RTCRIN_SUCCEEDED	= RTCRIN_INCOMING + 1,
	RTCRIN_FAIL	= RTCRIN_SUCCEEDED + 1
    }	RTC_REINVITE_STATE;

#define RTCCS_FORCE_PROFILE          0x00000001
#define RTCCS_FAIL_ON_REDIRECT       0x00000002
#define RTCMT_AUDIO_SEND     0x00000001
#define RTCMT_AUDIO_RECEIVE  0x00000002
#define RTCMT_VIDEO_SEND     0x00000004
#define RTCMT_VIDEO_RECEIVE  0x00000008
#define RTCMT_T120_SENDRECV  0x00000010
#define RTCMT_ALL_RTP   (       \
         RTCMT_AUDIO_SEND    |  \
         RTCMT_AUDIO_RECEIVE  | \
         RTCMT_VIDEO_SEND  |    \
         RTCMT_VIDEO_RECEIVE )    
#define RTCMT_ALL       (       \
         RTCMT_ALL_RTP    |     \
         RTCMT_T120_SENDRECV  )   
#define RTCSI_PC_TO_PC       0x00000001
#define RTCSI_PC_TO_PHONE    0x00000002
#define RTCSI_PHONE_TO_PHONE 0x00000004
#define RTCSI_IM             0x00000008
#define RTCSI_MULTIPARTY_IM  0x00000010
#define RTCTR_UDP            0x00000001
#define RTCTR_TCP            0x00000002
#define RTCTR_TLS            0x00000004
#define RTCAU_BASIC                  0x00000001
#define RTCAU_DIGEST                 0x00000002
#define RTCAU_NTLM                   0x00000004
#define RTCAU_KERBEROS               0x00000008
#define RTCAU_USE_LOGON_CRED         0x00010000
#define RTCRF_REGISTER_INVITE_SESSIONS   0x00000001
#define RTCRF_REGISTER_MESSAGE_SESSIONS  0x00000002
#define RTCRF_REGISTER_PRESENCE          0x00000004
#define RTCRF_REGISTER_NOTIFY            0x00000008
#define RTCRF_REGISTER_ALL               0x0000000F
#define RTCRMF_BUDDY_ROAMING              0x00000001
#define RTCRMF_WATCHER_ROAMING            0x00000002
#define RTCRMF_PRESENCE_ROAMING           0x00000004
#define RTCRMF_PROFILE_ROAMING            0x00000008
#define RTCRMF_ALL_ROAMING                0x0000000F
#define RTCEF_CLIENT                     0x00000001
#define RTCEF_REGISTRATION_STATE_CHANGE  0x00000002
#define RTCEF_SESSION_STATE_CHANGE       0x00000004
#define RTCEF_SESSION_OPERATION_COMPLETE 0x00000008
#define RTCEF_PARTICIPANT_STATE_CHANGE   0x00000010
#define RTCEF_MEDIA                      0x00000020
#define RTCEF_INTENSITY                  0x00000040
#define RTCEF_MESSAGING                  0x00000080
#define RTCEF_BUDDY                      0x00000100
#define RTCEF_WATCHER                    0x00000200
#define RTCEF_PROFILE                    0x00000400
#define RTCEF_USERSEARCH                 0x00000800
#define RTCEF_INFO                       0x00001000
#define RTCEF_GROUP                      0x00002000
#define RTCEF_MEDIA_REQUEST              0x00004000
#define RTCEF_ROAMING                    0x00010000
#define RTCEF_PRESENCE_PROPERTY             0x00020000
#define RTCEF_BUDDY2                     0x00040000
#define RTCEF_WATCHER2                   0x00080000
#define RTCEF_SESSION_REFER_STATUS       0x00100000
#define RTCEF_SESSION_REFERRED           0x00200000
#define RTCEF_REINVITE                   0x00400000
#define RTCEF_PRESENCE_DATA              0x00800000
#define RTCEF_PRESENCE_STATUS            0x01000000
#define RTCEF_ALL                        0x01FFFFFF
#define RTCIF_DISABLE_MEDIA              0x00000001
#define RTCIF_DISABLE_UPNP               0x00000002




































extern RPC_IF_HANDLE __MIDL_itf_rtccore_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_rtccore_0000_v0_0_s_ifspec;

#ifndef __IRTCClient_INTERFACE_DEFINED__
#define __IRTCClient_INTERFACE_DEFINED__

/* interface IRTCClient */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCClient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07829e45-9a34-408e-a011-bddf13487cd1")
    IRTCClient : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Shutdown( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PrepareForShutdown( void) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EventFilter( 
            /* [in] */ long lFilter) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EventFilter( 
            /* [retval][out] */ long __RPC_FAR *plFilter) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPreferredMediaTypes( 
            /* [in] */ long lMediaTypes,
            /* [in] */ VARIANT_BOOL fPersistent) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredMediaTypes( 
            /* [retval][out] */ long __RPC_FAR *plMediaTypes) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MediaCapabilities( 
            /* [retval][out] */ long __RPC_FAR *plMediaTypes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateSession( 
            /* [in] */ RTC_SESSION_TYPE enType,
            /* [in] */ BSTR bstrLocalPhoneURI,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ListenForIncomingSessions( 
            /* [in] */ RTC_LISTEN_MODE enListen) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ListenForIncomingSessions( 
            /* [retval][out] */ RTC_LISTEN_MODE __RPC_FAR *penListen) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NetworkAddresses( 
            /* [in] */ VARIANT_BOOL fTCP,
            /* [in] */ VARIANT_BOOL fExternal,
            /* [retval][out] */ VARIANT __RPC_FAR *pvAddresses) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Volume( 
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ long lVolume) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Volume( 
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ long __RPC_FAR *plVolume) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AudioMuted( 
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ VARIANT_BOOL fMuted) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AudioMuted( 
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IVideoWindow( 
            /* [in] */ RTC_VIDEO_DEVICE enDevice,
            /* [retval][out] */ IVideoWindow __RPC_FAR *__RPC_FAR *ppIVideoWindow) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PreferredAudioDevice( 
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ BSTR bstrDeviceName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredAudioDevice( 
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDeviceName) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PreferredVolume( 
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ long lVolume) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredVolume( 
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ long __RPC_FAR *plVolume) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PreferredAEC( 
            /* [in] */ VARIANT_BOOL bEnable) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredAEC( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEnabled) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PreferredVideoDevice( 
            /* [in] */ BSTR bstrDeviceName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredVideoDevice( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDeviceName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ActiveMedia( 
            /* [retval][out] */ long __RPC_FAR *plMediaType) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MaxBitrate( 
            /* [in] */ long lMaxBitrate) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxBitrate( 
            /* [retval][out] */ long __RPC_FAR *plMaxBitrate) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TemporalSpatialTradeOff( 
            /* [in] */ long lValue) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TemporalSpatialTradeOff( 
            /* [retval][out] */ long __RPC_FAR *plValue) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NetworkQuality( 
            /* [retval][out] */ long __RPC_FAR *plNetworkQuality) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StartT120Applet( 
            /* [in] */ RTC_T120_APPLET enApplet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StopT120Applets( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsT120AppletRunning( 
            /* [in] */ RTC_T120_APPLET enApplet,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRunning) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LocalUserURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LocalUserURI( 
            /* [in] */ BSTR bstrUserURI) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LocalUserName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LocalUserName( 
            /* [in] */ BSTR bstrUserName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlayRing( 
            /* [in] */ RTC_RING_TYPE enType,
            /* [in] */ VARIANT_BOOL bPlay) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SendDTMF( 
            /* [in] */ RTC_DTMF enDTMF) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InvokeTuningWizard( 
            /* [in] */ OAHWND hwndParent) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsTuned( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfTuned) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCClient __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCClient __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IRTCClient __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shutdown )( 
            IRTCClient __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrepareForShutdown )( 
            IRTCClient __RPC_FAR * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EventFilter )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ long lFilter);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventFilter )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plFilter);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPreferredMediaTypes )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ long lMediaTypes,
            /* [in] */ VARIANT_BOOL fPersistent);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredMediaTypes )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMediaTypes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaCapabilities )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMediaTypes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSession )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_SESSION_TYPE enType,
            /* [in] */ BSTR bstrLocalPhoneURI,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ListenForIncomingSessions )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_LISTEN_MODE enListen);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ListenForIncomingSessions )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ RTC_LISTEN_MODE __RPC_FAR *penListen);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetworkAddresses )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fTCP,
            /* [in] */ VARIANT_BOOL fExternal,
            /* [retval][out] */ VARIANT __RPC_FAR *pvAddresses);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Volume )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ long lVolume);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Volume )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ long __RPC_FAR *plVolume);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AudioMuted )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ VARIANT_BOOL fMuted);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudioMuted )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVideoWindow )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_VIDEO_DEVICE enDevice,
            /* [retval][out] */ IVideoWindow __RPC_FAR *__RPC_FAR *ppIVideoWindow);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PreferredAudioDevice )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ BSTR bstrDeviceName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredAudioDevice )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDeviceName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PreferredVolume )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ long lVolume);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredVolume )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ long __RPC_FAR *plVolume);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PreferredAEC )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bEnable);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredAEC )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEnabled);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PreferredVideoDevice )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ BSTR bstrDeviceName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredVideoDevice )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDeviceName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActiveMedia )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMediaType);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxBitrate )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ long lMaxBitrate);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxBitrate )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMaxBitrate);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TemporalSpatialTradeOff )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ long lValue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TemporalSpatialTradeOff )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plValue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetworkQuality )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plNetworkQuality);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartT120Applet )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_T120_APPLET enApplet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopT120Applets )( 
            IRTCClient __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsT120AppletRunning )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_T120_APPLET enApplet,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRunning);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalUserURI )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalUserURI )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ BSTR bstrUserURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalUserName )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalUserName )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ BSTR bstrUserName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayRing )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_RING_TYPE enType,
            /* [in] */ VARIANT_BOOL bPlay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendDTMF )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ RTC_DTMF enDTMF);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeTuningWizard )( 
            IRTCClient __RPC_FAR * This,
            /* [in] */ OAHWND hwndParent);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsTuned )( 
            IRTCClient __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfTuned);
        
        END_INTERFACE
    } IRTCClientVtbl;

    interface IRTCClient
    {
        CONST_VTBL struct IRTCClientVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCClient_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCClient_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCClient_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCClient_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IRTCClient_Shutdown(This)	\
    (This)->lpVtbl -> Shutdown(This)

#define IRTCClient_PrepareForShutdown(This)	\
    (This)->lpVtbl -> PrepareForShutdown(This)

#define IRTCClient_put_EventFilter(This,lFilter)	\
    (This)->lpVtbl -> put_EventFilter(This,lFilter)

#define IRTCClient_get_EventFilter(This,plFilter)	\
    (This)->lpVtbl -> get_EventFilter(This,plFilter)

#define IRTCClient_SetPreferredMediaTypes(This,lMediaTypes,fPersistent)	\
    (This)->lpVtbl -> SetPreferredMediaTypes(This,lMediaTypes,fPersistent)

#define IRTCClient_get_PreferredMediaTypes(This,plMediaTypes)	\
    (This)->lpVtbl -> get_PreferredMediaTypes(This,plMediaTypes)

#define IRTCClient_get_MediaCapabilities(This,plMediaTypes)	\
    (This)->lpVtbl -> get_MediaCapabilities(This,plMediaTypes)

#define IRTCClient_CreateSession(This,enType,bstrLocalPhoneURI,pProfile,lFlags,ppSession)	\
    (This)->lpVtbl -> CreateSession(This,enType,bstrLocalPhoneURI,pProfile,lFlags,ppSession)

#define IRTCClient_put_ListenForIncomingSessions(This,enListen)	\
    (This)->lpVtbl -> put_ListenForIncomingSessions(This,enListen)

#define IRTCClient_get_ListenForIncomingSessions(This,penListen)	\
    (This)->lpVtbl -> get_ListenForIncomingSessions(This,penListen)

#define IRTCClient_get_NetworkAddresses(This,fTCP,fExternal,pvAddresses)	\
    (This)->lpVtbl -> get_NetworkAddresses(This,fTCP,fExternal,pvAddresses)

#define IRTCClient_put_Volume(This,enDevice,lVolume)	\
    (This)->lpVtbl -> put_Volume(This,enDevice,lVolume)

#define IRTCClient_get_Volume(This,enDevice,plVolume)	\
    (This)->lpVtbl -> get_Volume(This,enDevice,plVolume)

#define IRTCClient_put_AudioMuted(This,enDevice,fMuted)	\
    (This)->lpVtbl -> put_AudioMuted(This,enDevice,fMuted)

#define IRTCClient_get_AudioMuted(This,enDevice,pfMuted)	\
    (This)->lpVtbl -> get_AudioMuted(This,enDevice,pfMuted)

#define IRTCClient_get_IVideoWindow(This,enDevice,ppIVideoWindow)	\
    (This)->lpVtbl -> get_IVideoWindow(This,enDevice,ppIVideoWindow)

#define IRTCClient_put_PreferredAudioDevice(This,enDevice,bstrDeviceName)	\
    (This)->lpVtbl -> put_PreferredAudioDevice(This,enDevice,bstrDeviceName)

#define IRTCClient_get_PreferredAudioDevice(This,enDevice,pbstrDeviceName)	\
    (This)->lpVtbl -> get_PreferredAudioDevice(This,enDevice,pbstrDeviceName)

#define IRTCClient_put_PreferredVolume(This,enDevice,lVolume)	\
    (This)->lpVtbl -> put_PreferredVolume(This,enDevice,lVolume)

#define IRTCClient_get_PreferredVolume(This,enDevice,plVolume)	\
    (This)->lpVtbl -> get_PreferredVolume(This,enDevice,plVolume)

#define IRTCClient_put_PreferredAEC(This,bEnable)	\
    (This)->lpVtbl -> put_PreferredAEC(This,bEnable)

#define IRTCClient_get_PreferredAEC(This,pbEnabled)	\
    (This)->lpVtbl -> get_PreferredAEC(This,pbEnabled)

#define IRTCClient_put_PreferredVideoDevice(This,bstrDeviceName)	\
    (This)->lpVtbl -> put_PreferredVideoDevice(This,bstrDeviceName)

#define IRTCClient_get_PreferredVideoDevice(This,pbstrDeviceName)	\
    (This)->lpVtbl -> get_PreferredVideoDevice(This,pbstrDeviceName)

#define IRTCClient_get_ActiveMedia(This,plMediaType)	\
    (This)->lpVtbl -> get_ActiveMedia(This,plMediaType)

#define IRTCClient_put_MaxBitrate(This,lMaxBitrate)	\
    (This)->lpVtbl -> put_MaxBitrate(This,lMaxBitrate)

#define IRTCClient_get_MaxBitrate(This,plMaxBitrate)	\
    (This)->lpVtbl -> get_MaxBitrate(This,plMaxBitrate)

#define IRTCClient_put_TemporalSpatialTradeOff(This,lValue)	\
    (This)->lpVtbl -> put_TemporalSpatialTradeOff(This,lValue)

#define IRTCClient_get_TemporalSpatialTradeOff(This,plValue)	\
    (This)->lpVtbl -> get_TemporalSpatialTradeOff(This,plValue)

#define IRTCClient_get_NetworkQuality(This,plNetworkQuality)	\
    (This)->lpVtbl -> get_NetworkQuality(This,plNetworkQuality)

#define IRTCClient_StartT120Applet(This,enApplet)	\
    (This)->lpVtbl -> StartT120Applet(This,enApplet)

#define IRTCClient_StopT120Applets(This)	\
    (This)->lpVtbl -> StopT120Applets(This)

#define IRTCClient_get_IsT120AppletRunning(This,enApplet,pfRunning)	\
    (This)->lpVtbl -> get_IsT120AppletRunning(This,enApplet,pfRunning)

#define IRTCClient_get_LocalUserURI(This,pbstrUserURI)	\
    (This)->lpVtbl -> get_LocalUserURI(This,pbstrUserURI)

#define IRTCClient_put_LocalUserURI(This,bstrUserURI)	\
    (This)->lpVtbl -> put_LocalUserURI(This,bstrUserURI)

#define IRTCClient_get_LocalUserName(This,pbstrUserName)	\
    (This)->lpVtbl -> get_LocalUserName(This,pbstrUserName)

#define IRTCClient_put_LocalUserName(This,bstrUserName)	\
    (This)->lpVtbl -> put_LocalUserName(This,bstrUserName)

#define IRTCClient_PlayRing(This,enType,bPlay)	\
    (This)->lpVtbl -> PlayRing(This,enType,bPlay)

#define IRTCClient_SendDTMF(This,enDTMF)	\
    (This)->lpVtbl -> SendDTMF(This,enDTMF)

#define IRTCClient_InvokeTuningWizard(This,hwndParent)	\
    (This)->lpVtbl -> InvokeTuningWizard(This,hwndParent)

#define IRTCClient_get_IsTuned(This,pfTuned)	\
    (This)->lpVtbl -> get_IsTuned(This,pfTuned)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient_Initialize_Proxy( 
    IRTCClient __RPC_FAR * This);


void __RPC_STUB IRTCClient_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient_Shutdown_Proxy( 
    IRTCClient __RPC_FAR * This);


void __RPC_STUB IRTCClient_Shutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient_PrepareForShutdown_Proxy( 
    IRTCClient __RPC_FAR * This);


void __RPC_STUB IRTCClient_PrepareForShutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_EventFilter_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ long lFilter);


void __RPC_STUB IRTCClient_put_EventFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_EventFilter_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plFilter);


void __RPC_STUB IRTCClient_get_EventFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient_SetPreferredMediaTypes_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ long lMediaTypes,
    /* [in] */ VARIANT_BOOL fPersistent);


void __RPC_STUB IRTCClient_SetPreferredMediaTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_PreferredMediaTypes_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMediaTypes);


void __RPC_STUB IRTCClient_get_PreferredMediaTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_MediaCapabilities_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMediaTypes);


void __RPC_STUB IRTCClient_get_MediaCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient_CreateSession_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_SESSION_TYPE enType,
    /* [in] */ BSTR bstrLocalPhoneURI,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile,
    /* [in] */ long lFlags,
    /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);


void __RPC_STUB IRTCClient_CreateSession_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_ListenForIncomingSessions_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_LISTEN_MODE enListen);


void __RPC_STUB IRTCClient_put_ListenForIncomingSessions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_ListenForIncomingSessions_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ RTC_LISTEN_MODE __RPC_FAR *penListen);


void __RPC_STUB IRTCClient_get_ListenForIncomingSessions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_NetworkAddresses_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fTCP,
    /* [in] */ VARIANT_BOOL fExternal,
    /* [retval][out] */ VARIANT __RPC_FAR *pvAddresses);


void __RPC_STUB IRTCClient_get_NetworkAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_Volume_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_AUDIO_DEVICE enDevice,
    /* [in] */ long lVolume);


void __RPC_STUB IRTCClient_put_Volume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_Volume_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_AUDIO_DEVICE enDevice,
    /* [retval][out] */ long __RPC_FAR *plVolume);


void __RPC_STUB IRTCClient_get_Volume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_AudioMuted_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_AUDIO_DEVICE enDevice,
    /* [in] */ VARIANT_BOOL fMuted);


void __RPC_STUB IRTCClient_put_AudioMuted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_AudioMuted_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_AUDIO_DEVICE enDevice,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted);


void __RPC_STUB IRTCClient_get_AudioMuted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_IVideoWindow_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_VIDEO_DEVICE enDevice,
    /* [retval][out] */ IVideoWindow __RPC_FAR *__RPC_FAR *ppIVideoWindow);


void __RPC_STUB IRTCClient_get_IVideoWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_PreferredAudioDevice_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_AUDIO_DEVICE enDevice,
    /* [in] */ BSTR bstrDeviceName);


void __RPC_STUB IRTCClient_put_PreferredAudioDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_PreferredAudioDevice_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_AUDIO_DEVICE enDevice,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDeviceName);


void __RPC_STUB IRTCClient_get_PreferredAudioDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_PreferredVolume_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_AUDIO_DEVICE enDevice,
    /* [in] */ long lVolume);


void __RPC_STUB IRTCClient_put_PreferredVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_PreferredVolume_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_AUDIO_DEVICE enDevice,
    /* [retval][out] */ long __RPC_FAR *plVolume);


void __RPC_STUB IRTCClient_get_PreferredVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_PreferredAEC_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bEnable);


void __RPC_STUB IRTCClient_put_PreferredAEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_PreferredAEC_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEnabled);


void __RPC_STUB IRTCClient_get_PreferredAEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_PreferredVideoDevice_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ BSTR bstrDeviceName);


void __RPC_STUB IRTCClient_put_PreferredVideoDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_PreferredVideoDevice_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDeviceName);


void __RPC_STUB IRTCClient_get_PreferredVideoDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_ActiveMedia_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMediaType);


void __RPC_STUB IRTCClient_get_ActiveMedia_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_MaxBitrate_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ long lMaxBitrate);


void __RPC_STUB IRTCClient_put_MaxBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_MaxBitrate_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMaxBitrate);


void __RPC_STUB IRTCClient_get_MaxBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_TemporalSpatialTradeOff_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IRTCClient_put_TemporalSpatialTradeOff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_TemporalSpatialTradeOff_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plValue);


void __RPC_STUB IRTCClient_get_TemporalSpatialTradeOff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_NetworkQuality_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plNetworkQuality);


void __RPC_STUB IRTCClient_get_NetworkQuality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient_StartT120Applet_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_T120_APPLET enApplet);


void __RPC_STUB IRTCClient_StartT120Applet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient_StopT120Applets_Proxy( 
    IRTCClient __RPC_FAR * This);


void __RPC_STUB IRTCClient_StopT120Applets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_IsT120AppletRunning_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_T120_APPLET enApplet,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRunning);


void __RPC_STUB IRTCClient_get_IsT120AppletRunning_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_LocalUserURI_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI);


void __RPC_STUB IRTCClient_get_LocalUserURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_LocalUserURI_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ BSTR bstrUserURI);


void __RPC_STUB IRTCClient_put_LocalUserURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_LocalUserName_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName);


void __RPC_STUB IRTCClient_get_LocalUserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient_put_LocalUserName_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ BSTR bstrUserName);


void __RPC_STUB IRTCClient_put_LocalUserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient_PlayRing_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_RING_TYPE enType,
    /* [in] */ VARIANT_BOOL bPlay);


void __RPC_STUB IRTCClient_PlayRing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient_SendDTMF_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ RTC_DTMF enDTMF);


void __RPC_STUB IRTCClient_SendDTMF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient_InvokeTuningWizard_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [in] */ OAHWND hwndParent);


void __RPC_STUB IRTCClient_InvokeTuningWizard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient_get_IsTuned_Proxy( 
    IRTCClient __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfTuned);


void __RPC_STUB IRTCClient_get_IsTuned_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCClient_INTERFACE_DEFINED__ */


#ifndef __IRTCClient2_INTERFACE_DEFINED__
#define __IRTCClient2_INTERFACE_DEFINED__

/* interface IRTCClient2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCClient2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0C91D71D-1064-42da-BFA5-572BEB8EEA84")
    IRTCClient2 : public IRTCClient
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AnswerMode( 
            /* [in] */ RTC_SESSION_TYPE enType,
            /* [in] */ RTC_ANSWER_MODE enMode) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AnswerMode( 
            /* [in] */ RTC_SESSION_TYPE enType,
            /* [retval][out] */ RTC_ANSWER_MODE __RPC_FAR *penMode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InvokeTuningWizardEx( 
            /* [in] */ OAHWND hwndParent,
            /* [in] */ VARIANT_BOOL fAllowAudio,
            /* [in] */ VARIANT_BOOL fAllowVideo) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ long __RPC_FAR *plVersion) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ClientName( 
            /* [in] */ BSTR bstrClientName) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ClientCurVer( 
            /* [in] */ BSTR bstrClientCurVer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitializeEx( 
            /* [in] */ long lFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateSessionWithDescription( 
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetSessionDescriptionManager( 
            /* [in] */ IRTCSessionDescriptionManager __RPC_FAR *pSessionDescriptionManager) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PreferredSecurityLevel( 
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [in] */ RTC_SECURITY_LEVEL enSecurityLevel) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredSecurityLevel( 
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AllowedPorts( 
            /* [in] */ long lTransport,
            /* [in] */ RTC_LISTEN_MODE enListenMode) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AllowedPorts( 
            /* [in] */ long lTransport,
            /* [retval][out] */ RTC_LISTEN_MODE __RPC_FAR *penListenMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCClient2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCClient2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCClient2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IRTCClient2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shutdown )( 
            IRTCClient2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrepareForShutdown )( 
            IRTCClient2 __RPC_FAR * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EventFilter )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ long lFilter);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventFilter )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plFilter);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPreferredMediaTypes )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ long lMediaTypes,
            /* [in] */ VARIANT_BOOL fPersistent);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredMediaTypes )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMediaTypes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaCapabilities )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMediaTypes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSession )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_SESSION_TYPE enType,
            /* [in] */ BSTR bstrLocalPhoneURI,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ListenForIncomingSessions )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_LISTEN_MODE enListen);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ListenForIncomingSessions )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ RTC_LISTEN_MODE __RPC_FAR *penListen);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetworkAddresses )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fTCP,
            /* [in] */ VARIANT_BOOL fExternal,
            /* [retval][out] */ VARIANT __RPC_FAR *pvAddresses);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Volume )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ long lVolume);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Volume )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ long __RPC_FAR *plVolume);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AudioMuted )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ VARIANT_BOOL fMuted);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudioMuted )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVideoWindow )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_VIDEO_DEVICE enDevice,
            /* [retval][out] */ IVideoWindow __RPC_FAR *__RPC_FAR *ppIVideoWindow);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PreferredAudioDevice )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ BSTR bstrDeviceName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredAudioDevice )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDeviceName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PreferredVolume )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [in] */ long lVolume);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredVolume )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_AUDIO_DEVICE enDevice,
            /* [retval][out] */ long __RPC_FAR *plVolume);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PreferredAEC )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bEnable);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredAEC )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEnabled);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PreferredVideoDevice )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ BSTR bstrDeviceName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredVideoDevice )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDeviceName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActiveMedia )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMediaType);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxBitrate )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ long lMaxBitrate);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxBitrate )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMaxBitrate);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TemporalSpatialTradeOff )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ long lValue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TemporalSpatialTradeOff )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plValue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetworkQuality )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plNetworkQuality);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartT120Applet )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_T120_APPLET enApplet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopT120Applets )( 
            IRTCClient2 __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsT120AppletRunning )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_T120_APPLET enApplet,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRunning);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalUserURI )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalUserURI )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ BSTR bstrUserURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalUserName )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalUserName )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ BSTR bstrUserName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayRing )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_RING_TYPE enType,
            /* [in] */ VARIANT_BOOL bPlay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendDTMF )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_DTMF enDTMF);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeTuningWizard )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ OAHWND hwndParent);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsTuned )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfTuned);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AnswerMode )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_SESSION_TYPE enType,
            /* [in] */ RTC_ANSWER_MODE enMode);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AnswerMode )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_SESSION_TYPE enType,
            /* [retval][out] */ RTC_ANSWER_MODE __RPC_FAR *penMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeTuningWizardEx )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ OAHWND hwndParent,
            /* [in] */ VARIANT_BOOL fAllowAudio,
            /* [in] */ VARIANT_BOOL fAllowVideo);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IRTCClient2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVersion);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClientName )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ BSTR bstrClientName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClientCurVer )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ BSTR bstrClientCurVer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitializeEx )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ long lFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSessionWithDescription )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSessionDescriptionManager )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ IRTCSessionDescriptionManager __RPC_FAR *pSessionDescriptionManager);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PreferredSecurityLevel )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [in] */ RTC_SECURITY_LEVEL enSecurityLevel);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredSecurityLevel )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AllowedPorts )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ long lTransport,
            /* [in] */ RTC_LISTEN_MODE enListenMode);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AllowedPorts )( 
            IRTCClient2 __RPC_FAR * This,
            /* [in] */ long lTransport,
            /* [retval][out] */ RTC_LISTEN_MODE __RPC_FAR *penListenMode);
        
        END_INTERFACE
    } IRTCClient2Vtbl;

    interface IRTCClient2
    {
        CONST_VTBL struct IRTCClient2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCClient2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCClient2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCClient2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCClient2_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IRTCClient2_Shutdown(This)	\
    (This)->lpVtbl -> Shutdown(This)

#define IRTCClient2_PrepareForShutdown(This)	\
    (This)->lpVtbl -> PrepareForShutdown(This)

#define IRTCClient2_put_EventFilter(This,lFilter)	\
    (This)->lpVtbl -> put_EventFilter(This,lFilter)

#define IRTCClient2_get_EventFilter(This,plFilter)	\
    (This)->lpVtbl -> get_EventFilter(This,plFilter)

#define IRTCClient2_SetPreferredMediaTypes(This,lMediaTypes,fPersistent)	\
    (This)->lpVtbl -> SetPreferredMediaTypes(This,lMediaTypes,fPersistent)

#define IRTCClient2_get_PreferredMediaTypes(This,plMediaTypes)	\
    (This)->lpVtbl -> get_PreferredMediaTypes(This,plMediaTypes)

#define IRTCClient2_get_MediaCapabilities(This,plMediaTypes)	\
    (This)->lpVtbl -> get_MediaCapabilities(This,plMediaTypes)

#define IRTCClient2_CreateSession(This,enType,bstrLocalPhoneURI,pProfile,lFlags,ppSession)	\
    (This)->lpVtbl -> CreateSession(This,enType,bstrLocalPhoneURI,pProfile,lFlags,ppSession)

#define IRTCClient2_put_ListenForIncomingSessions(This,enListen)	\
    (This)->lpVtbl -> put_ListenForIncomingSessions(This,enListen)

#define IRTCClient2_get_ListenForIncomingSessions(This,penListen)	\
    (This)->lpVtbl -> get_ListenForIncomingSessions(This,penListen)

#define IRTCClient2_get_NetworkAddresses(This,fTCP,fExternal,pvAddresses)	\
    (This)->lpVtbl -> get_NetworkAddresses(This,fTCP,fExternal,pvAddresses)

#define IRTCClient2_put_Volume(This,enDevice,lVolume)	\
    (This)->lpVtbl -> put_Volume(This,enDevice,lVolume)

#define IRTCClient2_get_Volume(This,enDevice,plVolume)	\
    (This)->lpVtbl -> get_Volume(This,enDevice,plVolume)

#define IRTCClient2_put_AudioMuted(This,enDevice,fMuted)	\
    (This)->lpVtbl -> put_AudioMuted(This,enDevice,fMuted)

#define IRTCClient2_get_AudioMuted(This,enDevice,pfMuted)	\
    (This)->lpVtbl -> get_AudioMuted(This,enDevice,pfMuted)

#define IRTCClient2_get_IVideoWindow(This,enDevice,ppIVideoWindow)	\
    (This)->lpVtbl -> get_IVideoWindow(This,enDevice,ppIVideoWindow)

#define IRTCClient2_put_PreferredAudioDevice(This,enDevice,bstrDeviceName)	\
    (This)->lpVtbl -> put_PreferredAudioDevice(This,enDevice,bstrDeviceName)

#define IRTCClient2_get_PreferredAudioDevice(This,enDevice,pbstrDeviceName)	\
    (This)->lpVtbl -> get_PreferredAudioDevice(This,enDevice,pbstrDeviceName)

#define IRTCClient2_put_PreferredVolume(This,enDevice,lVolume)	\
    (This)->lpVtbl -> put_PreferredVolume(This,enDevice,lVolume)

#define IRTCClient2_get_PreferredVolume(This,enDevice,plVolume)	\
    (This)->lpVtbl -> get_PreferredVolume(This,enDevice,plVolume)

#define IRTCClient2_put_PreferredAEC(This,bEnable)	\
    (This)->lpVtbl -> put_PreferredAEC(This,bEnable)

#define IRTCClient2_get_PreferredAEC(This,pbEnabled)	\
    (This)->lpVtbl -> get_PreferredAEC(This,pbEnabled)

#define IRTCClient2_put_PreferredVideoDevice(This,bstrDeviceName)	\
    (This)->lpVtbl -> put_PreferredVideoDevice(This,bstrDeviceName)

#define IRTCClient2_get_PreferredVideoDevice(This,pbstrDeviceName)	\
    (This)->lpVtbl -> get_PreferredVideoDevice(This,pbstrDeviceName)

#define IRTCClient2_get_ActiveMedia(This,plMediaType)	\
    (This)->lpVtbl -> get_ActiveMedia(This,plMediaType)

#define IRTCClient2_put_MaxBitrate(This,lMaxBitrate)	\
    (This)->lpVtbl -> put_MaxBitrate(This,lMaxBitrate)

#define IRTCClient2_get_MaxBitrate(This,plMaxBitrate)	\
    (This)->lpVtbl -> get_MaxBitrate(This,plMaxBitrate)

#define IRTCClient2_put_TemporalSpatialTradeOff(This,lValue)	\
    (This)->lpVtbl -> put_TemporalSpatialTradeOff(This,lValue)

#define IRTCClient2_get_TemporalSpatialTradeOff(This,plValue)	\
    (This)->lpVtbl -> get_TemporalSpatialTradeOff(This,plValue)

#define IRTCClient2_get_NetworkQuality(This,plNetworkQuality)	\
    (This)->lpVtbl -> get_NetworkQuality(This,plNetworkQuality)

#define IRTCClient2_StartT120Applet(This,enApplet)	\
    (This)->lpVtbl -> StartT120Applet(This,enApplet)

#define IRTCClient2_StopT120Applets(This)	\
    (This)->lpVtbl -> StopT120Applets(This)

#define IRTCClient2_get_IsT120AppletRunning(This,enApplet,pfRunning)	\
    (This)->lpVtbl -> get_IsT120AppletRunning(This,enApplet,pfRunning)

#define IRTCClient2_get_LocalUserURI(This,pbstrUserURI)	\
    (This)->lpVtbl -> get_LocalUserURI(This,pbstrUserURI)

#define IRTCClient2_put_LocalUserURI(This,bstrUserURI)	\
    (This)->lpVtbl -> put_LocalUserURI(This,bstrUserURI)

#define IRTCClient2_get_LocalUserName(This,pbstrUserName)	\
    (This)->lpVtbl -> get_LocalUserName(This,pbstrUserName)

#define IRTCClient2_put_LocalUserName(This,bstrUserName)	\
    (This)->lpVtbl -> put_LocalUserName(This,bstrUserName)

#define IRTCClient2_PlayRing(This,enType,bPlay)	\
    (This)->lpVtbl -> PlayRing(This,enType,bPlay)

#define IRTCClient2_SendDTMF(This,enDTMF)	\
    (This)->lpVtbl -> SendDTMF(This,enDTMF)

#define IRTCClient2_InvokeTuningWizard(This,hwndParent)	\
    (This)->lpVtbl -> InvokeTuningWizard(This,hwndParent)

#define IRTCClient2_get_IsTuned(This,pfTuned)	\
    (This)->lpVtbl -> get_IsTuned(This,pfTuned)


#define IRTCClient2_put_AnswerMode(This,enType,enMode)	\
    (This)->lpVtbl -> put_AnswerMode(This,enType,enMode)

#define IRTCClient2_get_AnswerMode(This,enType,penMode)	\
    (This)->lpVtbl -> get_AnswerMode(This,enType,penMode)

#define IRTCClient2_InvokeTuningWizardEx(This,hwndParent,fAllowAudio,fAllowVideo)	\
    (This)->lpVtbl -> InvokeTuningWizardEx(This,hwndParent,fAllowAudio,fAllowVideo)

#define IRTCClient2_get_Version(This,plVersion)	\
    (This)->lpVtbl -> get_Version(This,plVersion)

#define IRTCClient2_put_ClientName(This,bstrClientName)	\
    (This)->lpVtbl -> put_ClientName(This,bstrClientName)

#define IRTCClient2_put_ClientCurVer(This,bstrClientCurVer)	\
    (This)->lpVtbl -> put_ClientCurVer(This,bstrClientCurVer)

#define IRTCClient2_InitializeEx(This,lFlags)	\
    (This)->lpVtbl -> InitializeEx(This,lFlags)

#define IRTCClient2_CreateSessionWithDescription(This,bstrContentType,bstrSessionDescription,pProfile,lFlags,ppSession2)	\
    (This)->lpVtbl -> CreateSessionWithDescription(This,bstrContentType,bstrSessionDescription,pProfile,lFlags,ppSession2)

#define IRTCClient2_SetSessionDescriptionManager(This,pSessionDescriptionManager)	\
    (This)->lpVtbl -> SetSessionDescriptionManager(This,pSessionDescriptionManager)

#define IRTCClient2_put_PreferredSecurityLevel(This,enSecurityType,enSecurityLevel)	\
    (This)->lpVtbl -> put_PreferredSecurityLevel(This,enSecurityType,enSecurityLevel)

#define IRTCClient2_get_PreferredSecurityLevel(This,enSecurityType,penSecurityLevel)	\
    (This)->lpVtbl -> get_PreferredSecurityLevel(This,enSecurityType,penSecurityLevel)

#define IRTCClient2_put_AllowedPorts(This,lTransport,enListenMode)	\
    (This)->lpVtbl -> put_AllowedPorts(This,lTransport,enListenMode)

#define IRTCClient2_get_AllowedPorts(This,lTransport,penListenMode)	\
    (This)->lpVtbl -> get_AllowedPorts(This,lTransport,penListenMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient2_put_AnswerMode_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ RTC_SESSION_TYPE enType,
    /* [in] */ RTC_ANSWER_MODE enMode);


void __RPC_STUB IRTCClient2_put_AnswerMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient2_get_AnswerMode_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ RTC_SESSION_TYPE enType,
    /* [retval][out] */ RTC_ANSWER_MODE __RPC_FAR *penMode);


void __RPC_STUB IRTCClient2_get_AnswerMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient2_InvokeTuningWizardEx_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ OAHWND hwndParent,
    /* [in] */ VARIANT_BOOL fAllowAudio,
    /* [in] */ VARIANT_BOOL fAllowVideo);


void __RPC_STUB IRTCClient2_InvokeTuningWizardEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient2_get_Version_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVersion);


void __RPC_STUB IRTCClient2_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient2_put_ClientName_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ BSTR bstrClientName);


void __RPC_STUB IRTCClient2_put_ClientName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient2_put_ClientCurVer_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ BSTR bstrClientCurVer);


void __RPC_STUB IRTCClient2_put_ClientCurVer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient2_InitializeEx_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ long lFlags);


void __RPC_STUB IRTCClient2_InitializeEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient2_CreateSessionWithDescription_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ BSTR bstrContentType,
    /* [in] */ BSTR bstrSessionDescription,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile,
    /* [in] */ long lFlags,
    /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession2);


void __RPC_STUB IRTCClient2_CreateSessionWithDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClient2_SetSessionDescriptionManager_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ IRTCSessionDescriptionManager __RPC_FAR *pSessionDescriptionManager);


void __RPC_STUB IRTCClient2_SetSessionDescriptionManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient2_put_PreferredSecurityLevel_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ RTC_SECURITY_TYPE enSecurityType,
    /* [in] */ RTC_SECURITY_LEVEL enSecurityLevel);


void __RPC_STUB IRTCClient2_put_PreferredSecurityLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient2_get_PreferredSecurityLevel_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ RTC_SECURITY_TYPE enSecurityType,
    /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel);


void __RPC_STUB IRTCClient2_get_PreferredSecurityLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClient2_put_AllowedPorts_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ long lTransport,
    /* [in] */ RTC_LISTEN_MODE enListenMode);


void __RPC_STUB IRTCClient2_put_AllowedPorts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClient2_get_AllowedPorts_Proxy( 
    IRTCClient2 __RPC_FAR * This,
    /* [in] */ long lTransport,
    /* [retval][out] */ RTC_LISTEN_MODE __RPC_FAR *penListenMode);


void __RPC_STUB IRTCClient2_get_AllowedPorts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCClient2_INTERFACE_DEFINED__ */


#ifndef __IRTCClientPresence_INTERFACE_DEFINED__
#define __IRTCClientPresence_INTERFACE_DEFINED__

/* interface IRTCClientPresence */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCClientPresence;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11c3cbcc-0744-42d1-968a-51aa1bb274c6")
    IRTCClientPresence : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnablePresence( 
            /* [in] */ VARIANT_BOOL fUseStorage,
            /* [in] */ VARIANT varStorage) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Export( 
            /* [in] */ VARIANT varStorage) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Import( 
            /* [in] */ VARIANT varStorage,
            /* [in] */ VARIANT_BOOL fReplaceAll) = 0;
        
        virtual /* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE EnumerateBuddies( 
            /* [retval][out] */ IRTCEnumBuddies __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Buddies( 
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Buddy( 
            /* [in] */ BSTR bstrPresentityURI,
            /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddBuddy( 
            /* [in] */ BSTR bstrPresentityURI,
            /* [in] */ BSTR bstrUserName,
            /* [in] */ BSTR bstrData,
            /* [in] */ VARIANT_BOOL fPersistent,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveBuddy( 
            /* [in] */ IRTCBuddy __RPC_FAR *pBuddy) = 0;
        
        virtual /* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE EnumerateWatchers( 
            /* [retval][out] */ IRTCEnumWatchers __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Watchers( 
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Watcher( 
            /* [in] */ BSTR bstrPresentityURI,
            /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddWatcher( 
            /* [in] */ BSTR bstrPresentityURI,
            /* [in] */ BSTR bstrUserName,
            /* [in] */ BSTR bstrData,
            /* [in] */ VARIANT_BOOL fBlocked,
            /* [in] */ VARIANT_BOOL fPersistent,
            /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveWatcher( 
            /* [in] */ IRTCWatcher __RPC_FAR *pWatcher) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLocalPresenceInfo( 
            /* [in] */ RTC_PRESENCE_STATUS enStatus,
            /* [in] */ BSTR bstrNotes) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OfferWatcherMode( 
            /* [retval][out] */ RTC_OFFER_WATCHER_MODE __RPC_FAR *penMode) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OfferWatcherMode( 
            /* [in] */ RTC_OFFER_WATCHER_MODE enMode) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PrivacyMode( 
            /* [retval][out] */ RTC_PRIVACY_MODE __RPC_FAR *penMode) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PrivacyMode( 
            /* [in] */ RTC_PRIVACY_MODE enMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCClientPresenceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCClientPresence __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCClientPresence __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnablePresence )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fUseStorage,
            /* [in] */ VARIANT varStorage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Export )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ VARIANT varStorage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Import )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ VARIANT varStorage,
            /* [in] */ VARIANT_BOOL fReplaceAll);
        
        /* [helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateBuddies )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumBuddies __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Buddies )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Buddy )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI,
            /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddBuddy )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI,
            /* [in] */ BSTR bstrUserName,
            /* [in] */ BSTR bstrData,
            /* [in] */ VARIANT_BOOL fPersistent,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveBuddy )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ IRTCBuddy __RPC_FAR *pBuddy);
        
        /* [helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateWatchers )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumWatchers __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Watchers )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Watcher )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI,
            /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddWatcher )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI,
            /* [in] */ BSTR bstrUserName,
            /* [in] */ BSTR bstrData,
            /* [in] */ VARIANT_BOOL fBlocked,
            /* [in] */ VARIANT_BOOL fPersistent,
            /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveWatcher )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ IRTCWatcher __RPC_FAR *pWatcher);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLocalPresenceInfo )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ RTC_PRESENCE_STATUS enStatus,
            /* [in] */ BSTR bstrNotes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OfferWatcherMode )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [retval][out] */ RTC_OFFER_WATCHER_MODE __RPC_FAR *penMode);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OfferWatcherMode )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ RTC_OFFER_WATCHER_MODE enMode);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivacyMode )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [retval][out] */ RTC_PRIVACY_MODE __RPC_FAR *penMode);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PrivacyMode )( 
            IRTCClientPresence __RPC_FAR * This,
            /* [in] */ RTC_PRIVACY_MODE enMode);
        
        END_INTERFACE
    } IRTCClientPresenceVtbl;

    interface IRTCClientPresence
    {
        CONST_VTBL struct IRTCClientPresenceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCClientPresence_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCClientPresence_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCClientPresence_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCClientPresence_EnablePresence(This,fUseStorage,varStorage)	\
    (This)->lpVtbl -> EnablePresence(This,fUseStorage,varStorage)

#define IRTCClientPresence_Export(This,varStorage)	\
    (This)->lpVtbl -> Export(This,varStorage)

#define IRTCClientPresence_Import(This,varStorage,fReplaceAll)	\
    (This)->lpVtbl -> Import(This,varStorage,fReplaceAll)

#define IRTCClientPresence_EnumerateBuddies(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateBuddies(This,ppEnum)

#define IRTCClientPresence_get_Buddies(This,ppCollection)	\
    (This)->lpVtbl -> get_Buddies(This,ppCollection)

#define IRTCClientPresence_get_Buddy(This,bstrPresentityURI,ppBuddy)	\
    (This)->lpVtbl -> get_Buddy(This,bstrPresentityURI,ppBuddy)

#define IRTCClientPresence_AddBuddy(This,bstrPresentityURI,bstrUserName,bstrData,fPersistent,pProfile,lFlags,ppBuddy)	\
    (This)->lpVtbl -> AddBuddy(This,bstrPresentityURI,bstrUserName,bstrData,fPersistent,pProfile,lFlags,ppBuddy)

#define IRTCClientPresence_RemoveBuddy(This,pBuddy)	\
    (This)->lpVtbl -> RemoveBuddy(This,pBuddy)

#define IRTCClientPresence_EnumerateWatchers(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateWatchers(This,ppEnum)

#define IRTCClientPresence_get_Watchers(This,ppCollection)	\
    (This)->lpVtbl -> get_Watchers(This,ppCollection)

#define IRTCClientPresence_get_Watcher(This,bstrPresentityURI,ppWatcher)	\
    (This)->lpVtbl -> get_Watcher(This,bstrPresentityURI,ppWatcher)

#define IRTCClientPresence_AddWatcher(This,bstrPresentityURI,bstrUserName,bstrData,fBlocked,fPersistent,ppWatcher)	\
    (This)->lpVtbl -> AddWatcher(This,bstrPresentityURI,bstrUserName,bstrData,fBlocked,fPersistent,ppWatcher)

#define IRTCClientPresence_RemoveWatcher(This,pWatcher)	\
    (This)->lpVtbl -> RemoveWatcher(This,pWatcher)

#define IRTCClientPresence_SetLocalPresenceInfo(This,enStatus,bstrNotes)	\
    (This)->lpVtbl -> SetLocalPresenceInfo(This,enStatus,bstrNotes)

#define IRTCClientPresence_get_OfferWatcherMode(This,penMode)	\
    (This)->lpVtbl -> get_OfferWatcherMode(This,penMode)

#define IRTCClientPresence_put_OfferWatcherMode(This,enMode)	\
    (This)->lpVtbl -> put_OfferWatcherMode(This,enMode)

#define IRTCClientPresence_get_PrivacyMode(This,penMode)	\
    (This)->lpVtbl -> get_PrivacyMode(This,penMode)

#define IRTCClientPresence_put_PrivacyMode(This,enMode)	\
    (This)->lpVtbl -> put_PrivacyMode(This,enMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_EnablePresence_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fUseStorage,
    /* [in] */ VARIANT varStorage);


void __RPC_STUB IRTCClientPresence_EnablePresence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_Export_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ VARIANT varStorage);


void __RPC_STUB IRTCClientPresence_Export_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_Import_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ VARIANT varStorage,
    /* [in] */ VARIANT_BOOL fReplaceAll);


void __RPC_STUB IRTCClientPresence_Import_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_EnumerateBuddies_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumBuddies __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCClientPresence_EnumerateBuddies_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_get_Buddies_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);


void __RPC_STUB IRTCClientPresence_get_Buddies_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_get_Buddy_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ BSTR bstrPresentityURI,
    /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy);


void __RPC_STUB IRTCClientPresence_get_Buddy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_AddBuddy_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ BSTR bstrPresentityURI,
    /* [in] */ BSTR bstrUserName,
    /* [in] */ BSTR bstrData,
    /* [in] */ VARIANT_BOOL fPersistent,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile,
    /* [in] */ long lFlags,
    /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy);


void __RPC_STUB IRTCClientPresence_AddBuddy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_RemoveBuddy_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ IRTCBuddy __RPC_FAR *pBuddy);


void __RPC_STUB IRTCClientPresence_RemoveBuddy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_EnumerateWatchers_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumWatchers __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCClientPresence_EnumerateWatchers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_get_Watchers_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);


void __RPC_STUB IRTCClientPresence_get_Watchers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_get_Watcher_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ BSTR bstrPresentityURI,
    /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher);


void __RPC_STUB IRTCClientPresence_get_Watcher_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_AddWatcher_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ BSTR bstrPresentityURI,
    /* [in] */ BSTR bstrUserName,
    /* [in] */ BSTR bstrData,
    /* [in] */ VARIANT_BOOL fBlocked,
    /* [in] */ VARIANT_BOOL fPersistent,
    /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher);


void __RPC_STUB IRTCClientPresence_AddWatcher_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_RemoveWatcher_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ IRTCWatcher __RPC_FAR *pWatcher);


void __RPC_STUB IRTCClientPresence_RemoveWatcher_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_SetLocalPresenceInfo_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ RTC_PRESENCE_STATUS enStatus,
    /* [in] */ BSTR bstrNotes);


void __RPC_STUB IRTCClientPresence_SetLocalPresenceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_get_OfferWatcherMode_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [retval][out] */ RTC_OFFER_WATCHER_MODE __RPC_FAR *penMode);


void __RPC_STUB IRTCClientPresence_get_OfferWatcherMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_put_OfferWatcherMode_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ RTC_OFFER_WATCHER_MODE enMode);


void __RPC_STUB IRTCClientPresence_put_OfferWatcherMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_get_PrivacyMode_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [retval][out] */ RTC_PRIVACY_MODE __RPC_FAR *penMode);


void __RPC_STUB IRTCClientPresence_get_PrivacyMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence_put_PrivacyMode_Proxy( 
    IRTCClientPresence __RPC_FAR * This,
    /* [in] */ RTC_PRIVACY_MODE enMode);


void __RPC_STUB IRTCClientPresence_put_PrivacyMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCClientPresence_INTERFACE_DEFINED__ */


#ifndef __IRTCClientPresence2_INTERFACE_DEFINED__
#define __IRTCClientPresence2_INTERFACE_DEFINED__

/* interface IRTCClientPresence2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCClientPresence2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AD1809E8-62F7-4783-909A-29C9D2CB1D34")
    IRTCClientPresence2 : public IRTCClientPresence
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnablePresenceEx( 
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ VARIANT varStorage,
            /* [in] */ long lFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DisablePresence( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddGroup( 
            /* [in] */ BSTR bstrGroupName,
            /* [in] */ BSTR bstrData,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppGroup) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveGroup( 
            /* [in] */ IRTCBuddyGroup __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE EnumerateGroups( 
            /* [retval][out] */ IRTCEnumGroups __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Groups( 
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [in] */ BSTR bstrGroupName,
            /* [retval][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppGroup) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddWatcherEx( 
            /* [in] */ BSTR bstrPresentityURI,
            /* [in] */ BSTR bstrUserName,
            /* [in] */ BSTR bstrData,
            /* [in] */ RTC_WATCHER_STATE enState,
            /* [in] */ VARIANT_BOOL fPersistent,
            /* [in] */ RTC_ACE_SCOPE enScope,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCWatcher2 __RPC_FAR *__RPC_FAR *ppWatcher) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WatcherEx( 
            /* [in] */ RTC_WATCHER_MATCH_MODE enMode,
            /* [in] */ BSTR bstrPresentityURI,
            /* [retval][out] */ IRTCWatcher2 __RPC_FAR *__RPC_FAR *ppWatcher) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PresenceProperty( 
            /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
            /* [in] */ BSTR bstrProperty) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PresenceProperty( 
            /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProperty) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPresenceData( 
            /* [in] */ BSTR bstrNamespace,
            /* [in] */ BSTR bstrData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPresenceData( 
            /* [out] */ BSTR __RPC_FAR *pbstrNamespace,
            /* [out] */ BSTR __RPC_FAR *pbstrData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLocalPresenceInfo( 
            /* [out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus,
            /* [out] */ BSTR __RPC_FAR *pbstrNotes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddBuddyEx( 
            /* [in] */ BSTR bstrPresentityURI,
            /* [in] */ BSTR bstrUserName,
            /* [in] */ BSTR bstrData,
            /* [in] */ VARIANT_BOOL fPersistent,
            /* [in] */ RTC_BUDDY_SUBSCRIPTION_TYPE enSubscriptionType,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCBuddy2 __RPC_FAR *__RPC_FAR *ppBuddy) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCClientPresence2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCClientPresence2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCClientPresence2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnablePresence )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fUseStorage,
            /* [in] */ VARIANT varStorage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Export )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ VARIANT varStorage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Import )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ VARIANT varStorage,
            /* [in] */ VARIANT_BOOL fReplaceAll);
        
        /* [helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateBuddies )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumBuddies __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Buddies )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Buddy )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI,
            /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddBuddy )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI,
            /* [in] */ BSTR bstrUserName,
            /* [in] */ BSTR bstrData,
            /* [in] */ VARIANT_BOOL fPersistent,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveBuddy )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ IRTCBuddy __RPC_FAR *pBuddy);
        
        /* [helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateWatchers )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumWatchers __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Watchers )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Watcher )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI,
            /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddWatcher )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI,
            /* [in] */ BSTR bstrUserName,
            /* [in] */ BSTR bstrData,
            /* [in] */ VARIANT_BOOL fBlocked,
            /* [in] */ VARIANT_BOOL fPersistent,
            /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveWatcher )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ IRTCWatcher __RPC_FAR *pWatcher);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLocalPresenceInfo )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ RTC_PRESENCE_STATUS enStatus,
            /* [in] */ BSTR bstrNotes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OfferWatcherMode )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [retval][out] */ RTC_OFFER_WATCHER_MODE __RPC_FAR *penMode);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OfferWatcherMode )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ RTC_OFFER_WATCHER_MODE enMode);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivacyMode )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [retval][out] */ RTC_PRIVACY_MODE __RPC_FAR *penMode);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PrivacyMode )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ RTC_PRIVACY_MODE enMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnablePresenceEx )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ VARIANT varStorage,
            /* [in] */ long lFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisablePresence )( 
            IRTCClientPresence2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddGroup )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ BSTR bstrGroupName,
            /* [in] */ BSTR bstrData,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppGroup);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveGroup )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ IRTCBuddyGroup __RPC_FAR *pGroup);
        
        /* [helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateGroups )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumGroups __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Groups )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ BSTR bstrGroupName,
            /* [retval][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppGroup);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddWatcherEx )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI,
            /* [in] */ BSTR bstrUserName,
            /* [in] */ BSTR bstrData,
            /* [in] */ RTC_WATCHER_STATE enState,
            /* [in] */ VARIANT_BOOL fPersistent,
            /* [in] */ RTC_ACE_SCOPE enScope,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCWatcher2 __RPC_FAR *__RPC_FAR *ppWatcher);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WatcherEx )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ RTC_WATCHER_MATCH_MODE enMode,
            /* [in] */ BSTR bstrPresentityURI,
            /* [retval][out] */ IRTCWatcher2 __RPC_FAR *__RPC_FAR *ppWatcher);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PresenceProperty )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
            /* [in] */ BSTR bstrProperty);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PresenceProperty )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProperty);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPresenceData )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ BSTR bstrNamespace,
            /* [in] */ BSTR bstrData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPresenceData )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrNamespace,
            /* [out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLocalPresenceInfo )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus,
            /* [out] */ BSTR __RPC_FAR *pbstrNotes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddBuddyEx )( 
            IRTCClientPresence2 __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI,
            /* [in] */ BSTR bstrUserName,
            /* [in] */ BSTR bstrData,
            /* [in] */ VARIANT_BOOL fPersistent,
            /* [in] */ RTC_BUDDY_SUBSCRIPTION_TYPE enSubscriptionType,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags,
            /* [retval][out] */ IRTCBuddy2 __RPC_FAR *__RPC_FAR *ppBuddy);
        
        END_INTERFACE
    } IRTCClientPresence2Vtbl;

    interface IRTCClientPresence2
    {
        CONST_VTBL struct IRTCClientPresence2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCClientPresence2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCClientPresence2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCClientPresence2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCClientPresence2_EnablePresence(This,fUseStorage,varStorage)	\
    (This)->lpVtbl -> EnablePresence(This,fUseStorage,varStorage)

#define IRTCClientPresence2_Export(This,varStorage)	\
    (This)->lpVtbl -> Export(This,varStorage)

#define IRTCClientPresence2_Import(This,varStorage,fReplaceAll)	\
    (This)->lpVtbl -> Import(This,varStorage,fReplaceAll)

#define IRTCClientPresence2_EnumerateBuddies(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateBuddies(This,ppEnum)

#define IRTCClientPresence2_get_Buddies(This,ppCollection)	\
    (This)->lpVtbl -> get_Buddies(This,ppCollection)

#define IRTCClientPresence2_get_Buddy(This,bstrPresentityURI,ppBuddy)	\
    (This)->lpVtbl -> get_Buddy(This,bstrPresentityURI,ppBuddy)

#define IRTCClientPresence2_AddBuddy(This,bstrPresentityURI,bstrUserName,bstrData,fPersistent,pProfile,lFlags,ppBuddy)	\
    (This)->lpVtbl -> AddBuddy(This,bstrPresentityURI,bstrUserName,bstrData,fPersistent,pProfile,lFlags,ppBuddy)

#define IRTCClientPresence2_RemoveBuddy(This,pBuddy)	\
    (This)->lpVtbl -> RemoveBuddy(This,pBuddy)

#define IRTCClientPresence2_EnumerateWatchers(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateWatchers(This,ppEnum)

#define IRTCClientPresence2_get_Watchers(This,ppCollection)	\
    (This)->lpVtbl -> get_Watchers(This,ppCollection)

#define IRTCClientPresence2_get_Watcher(This,bstrPresentityURI,ppWatcher)	\
    (This)->lpVtbl -> get_Watcher(This,bstrPresentityURI,ppWatcher)

#define IRTCClientPresence2_AddWatcher(This,bstrPresentityURI,bstrUserName,bstrData,fBlocked,fPersistent,ppWatcher)	\
    (This)->lpVtbl -> AddWatcher(This,bstrPresentityURI,bstrUserName,bstrData,fBlocked,fPersistent,ppWatcher)

#define IRTCClientPresence2_RemoveWatcher(This,pWatcher)	\
    (This)->lpVtbl -> RemoveWatcher(This,pWatcher)

#define IRTCClientPresence2_SetLocalPresenceInfo(This,enStatus,bstrNotes)	\
    (This)->lpVtbl -> SetLocalPresenceInfo(This,enStatus,bstrNotes)

#define IRTCClientPresence2_get_OfferWatcherMode(This,penMode)	\
    (This)->lpVtbl -> get_OfferWatcherMode(This,penMode)

#define IRTCClientPresence2_put_OfferWatcherMode(This,enMode)	\
    (This)->lpVtbl -> put_OfferWatcherMode(This,enMode)

#define IRTCClientPresence2_get_PrivacyMode(This,penMode)	\
    (This)->lpVtbl -> get_PrivacyMode(This,penMode)

#define IRTCClientPresence2_put_PrivacyMode(This,enMode)	\
    (This)->lpVtbl -> put_PrivacyMode(This,enMode)


#define IRTCClientPresence2_EnablePresenceEx(This,pProfile,varStorage,lFlags)	\
    (This)->lpVtbl -> EnablePresenceEx(This,pProfile,varStorage,lFlags)

#define IRTCClientPresence2_DisablePresence(This)	\
    (This)->lpVtbl -> DisablePresence(This)

#define IRTCClientPresence2_AddGroup(This,bstrGroupName,bstrData,pProfile,lFlags,ppGroup)	\
    (This)->lpVtbl -> AddGroup(This,bstrGroupName,bstrData,pProfile,lFlags,ppGroup)

#define IRTCClientPresence2_RemoveGroup(This,pGroup)	\
    (This)->lpVtbl -> RemoveGroup(This,pGroup)

#define IRTCClientPresence2_EnumerateGroups(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateGroups(This,ppEnum)

#define IRTCClientPresence2_get_Groups(This,ppCollection)	\
    (This)->lpVtbl -> get_Groups(This,ppCollection)

#define IRTCClientPresence2_get_Group(This,bstrGroupName,ppGroup)	\
    (This)->lpVtbl -> get_Group(This,bstrGroupName,ppGroup)

#define IRTCClientPresence2_AddWatcherEx(This,bstrPresentityURI,bstrUserName,bstrData,enState,fPersistent,enScope,pProfile,lFlags,ppWatcher)	\
    (This)->lpVtbl -> AddWatcherEx(This,bstrPresentityURI,bstrUserName,bstrData,enState,fPersistent,enScope,pProfile,lFlags,ppWatcher)

#define IRTCClientPresence2_get_WatcherEx(This,enMode,bstrPresentityURI,ppWatcher)	\
    (This)->lpVtbl -> get_WatcherEx(This,enMode,bstrPresentityURI,ppWatcher)

#define IRTCClientPresence2_put_PresenceProperty(This,enProperty,bstrProperty)	\
    (This)->lpVtbl -> put_PresenceProperty(This,enProperty,bstrProperty)

#define IRTCClientPresence2_get_PresenceProperty(This,enProperty,pbstrProperty)	\
    (This)->lpVtbl -> get_PresenceProperty(This,enProperty,pbstrProperty)

#define IRTCClientPresence2_SetPresenceData(This,bstrNamespace,bstrData)	\
    (This)->lpVtbl -> SetPresenceData(This,bstrNamespace,bstrData)

#define IRTCClientPresence2_GetPresenceData(This,pbstrNamespace,pbstrData)	\
    (This)->lpVtbl -> GetPresenceData(This,pbstrNamespace,pbstrData)

#define IRTCClientPresence2_GetLocalPresenceInfo(This,penStatus,pbstrNotes)	\
    (This)->lpVtbl -> GetLocalPresenceInfo(This,penStatus,pbstrNotes)

#define IRTCClientPresence2_AddBuddyEx(This,bstrPresentityURI,bstrUserName,bstrData,fPersistent,enSubscriptionType,pProfile,lFlags,ppBuddy)	\
    (This)->lpVtbl -> AddBuddyEx(This,bstrPresentityURI,bstrUserName,bstrData,fPersistent,enSubscriptionType,pProfile,lFlags,ppBuddy)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_EnablePresenceEx_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile,
    /* [in] */ VARIANT varStorage,
    /* [in] */ long lFlags);


void __RPC_STUB IRTCClientPresence2_EnablePresenceEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_DisablePresence_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This);


void __RPC_STUB IRTCClientPresence2_DisablePresence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_AddGroup_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [in] */ BSTR bstrGroupName,
    /* [in] */ BSTR bstrData,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile,
    /* [in] */ long lFlags,
    /* [retval][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppGroup);


void __RPC_STUB IRTCClientPresence2_AddGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_RemoveGroup_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [in] */ IRTCBuddyGroup __RPC_FAR *pGroup);


void __RPC_STUB IRTCClientPresence2_RemoveGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_EnumerateGroups_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumGroups __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCClientPresence2_EnumerateGroups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_get_Groups_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);


void __RPC_STUB IRTCClientPresence2_get_Groups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_get_Group_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [in] */ BSTR bstrGroupName,
    /* [retval][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppGroup);


void __RPC_STUB IRTCClientPresence2_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_AddWatcherEx_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [in] */ BSTR bstrPresentityURI,
    /* [in] */ BSTR bstrUserName,
    /* [in] */ BSTR bstrData,
    /* [in] */ RTC_WATCHER_STATE enState,
    /* [in] */ VARIANT_BOOL fPersistent,
    /* [in] */ RTC_ACE_SCOPE enScope,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile,
    /* [in] */ long lFlags,
    /* [retval][out] */ IRTCWatcher2 __RPC_FAR *__RPC_FAR *ppWatcher);


void __RPC_STUB IRTCClientPresence2_AddWatcherEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_get_WatcherEx_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [in] */ RTC_WATCHER_MATCH_MODE enMode,
    /* [in] */ BSTR bstrPresentityURI,
    /* [retval][out] */ IRTCWatcher2 __RPC_FAR *__RPC_FAR *ppWatcher);


void __RPC_STUB IRTCClientPresence2_get_WatcherEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_put_PresenceProperty_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
    /* [in] */ BSTR bstrProperty);


void __RPC_STUB IRTCClientPresence2_put_PresenceProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_get_PresenceProperty_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrProperty);


void __RPC_STUB IRTCClientPresence2_get_PresenceProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_SetPresenceData_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [in] */ BSTR bstrNamespace,
    /* [in] */ BSTR bstrData);


void __RPC_STUB IRTCClientPresence2_SetPresenceData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_GetPresenceData_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrNamespace,
    /* [out] */ BSTR __RPC_FAR *pbstrData);


void __RPC_STUB IRTCClientPresence2_GetPresenceData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_GetLocalPresenceInfo_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus,
    /* [out] */ BSTR __RPC_FAR *pbstrNotes);


void __RPC_STUB IRTCClientPresence2_GetLocalPresenceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPresence2_AddBuddyEx_Proxy( 
    IRTCClientPresence2 __RPC_FAR * This,
    /* [in] */ BSTR bstrPresentityURI,
    /* [in] */ BSTR bstrUserName,
    /* [in] */ BSTR bstrData,
    /* [in] */ VARIANT_BOOL fPersistent,
    /* [in] */ RTC_BUDDY_SUBSCRIPTION_TYPE enSubscriptionType,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile,
    /* [in] */ long lFlags,
    /* [retval][out] */ IRTCBuddy2 __RPC_FAR *__RPC_FAR *ppBuddy);


void __RPC_STUB IRTCClientPresence2_AddBuddyEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCClientPresence2_INTERFACE_DEFINED__ */


#ifndef __IRTCClientProvisioning_INTERFACE_DEFINED__
#define __IRTCClientProvisioning_INTERFACE_DEFINED__

/* interface IRTCClientProvisioning */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCClientProvisioning;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B9F5CF06-65B9-4a80-A0E6-73CAE3EF3822")
    IRTCClientProvisioning : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateProfile( 
            /* [in] */ BSTR bstrProfileXML,
            /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableProfile( 
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lRegisterFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DisableProfile( 
            /* [in] */ IRTCProfile __RPC_FAR *pProfile) = 0;
        
        virtual /* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE EnumerateProfiles( 
            /* [retval][out] */ IRTCEnumProfiles __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profiles( 
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetProfile( 
            /* [in] */ BSTR bstrUserAccount,
            /* [in] */ BSTR bstrUserPassword,
            /* [in] */ BSTR bstrUserURI,
            /* [in] */ BSTR bstrServer,
            /* [in] */ long lTransport,
            /* [in] */ LONG_PTR lCookie) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SessionCapabilities( 
            /* [retval][out] */ long __RPC_FAR *plSupportedSessions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCClientProvisioningVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCClientProvisioning __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCClientProvisioning __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCClientProvisioning __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateProfile )( 
            IRTCClientProvisioning __RPC_FAR * This,
            /* [in] */ BSTR bstrProfileXML,
            /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableProfile )( 
            IRTCClientProvisioning __RPC_FAR * This,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lRegisterFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisableProfile )( 
            IRTCClientProvisioning __RPC_FAR * This,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile);
        
        /* [helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateProfiles )( 
            IRTCClientProvisioning __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumProfiles __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profiles )( 
            IRTCClientProvisioning __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProfile )( 
            IRTCClientProvisioning __RPC_FAR * This,
            /* [in] */ BSTR bstrUserAccount,
            /* [in] */ BSTR bstrUserPassword,
            /* [in] */ BSTR bstrUserURI,
            /* [in] */ BSTR bstrServer,
            /* [in] */ long lTransport,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SessionCapabilities )( 
            IRTCClientProvisioning __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plSupportedSessions);
        
        END_INTERFACE
    } IRTCClientProvisioningVtbl;

    interface IRTCClientProvisioning
    {
        CONST_VTBL struct IRTCClientProvisioningVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCClientProvisioning_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCClientProvisioning_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCClientProvisioning_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCClientProvisioning_CreateProfile(This,bstrProfileXML,ppProfile)	\
    (This)->lpVtbl -> CreateProfile(This,bstrProfileXML,ppProfile)

#define IRTCClientProvisioning_EnableProfile(This,pProfile,lRegisterFlags)	\
    (This)->lpVtbl -> EnableProfile(This,pProfile,lRegisterFlags)

#define IRTCClientProvisioning_DisableProfile(This,pProfile)	\
    (This)->lpVtbl -> DisableProfile(This,pProfile)

#define IRTCClientProvisioning_EnumerateProfiles(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateProfiles(This,ppEnum)

#define IRTCClientProvisioning_get_Profiles(This,ppCollection)	\
    (This)->lpVtbl -> get_Profiles(This,ppCollection)

#define IRTCClientProvisioning_GetProfile(This,bstrUserAccount,bstrUserPassword,bstrUserURI,bstrServer,lTransport,lCookie)	\
    (This)->lpVtbl -> GetProfile(This,bstrUserAccount,bstrUserPassword,bstrUserURI,bstrServer,lTransport,lCookie)

#define IRTCClientProvisioning_get_SessionCapabilities(This,plSupportedSessions)	\
    (This)->lpVtbl -> get_SessionCapabilities(This,plSupportedSessions)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientProvisioning_CreateProfile_Proxy( 
    IRTCClientProvisioning __RPC_FAR * This,
    /* [in] */ BSTR bstrProfileXML,
    /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB IRTCClientProvisioning_CreateProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientProvisioning_EnableProfile_Proxy( 
    IRTCClientProvisioning __RPC_FAR * This,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile,
    /* [in] */ long lRegisterFlags);


void __RPC_STUB IRTCClientProvisioning_EnableProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientProvisioning_DisableProfile_Proxy( 
    IRTCClientProvisioning __RPC_FAR * This,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile);


void __RPC_STUB IRTCClientProvisioning_DisableProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IRTCClientProvisioning_EnumerateProfiles_Proxy( 
    IRTCClientProvisioning __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumProfiles __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCClientProvisioning_EnumerateProfiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientProvisioning_get_Profiles_Proxy( 
    IRTCClientProvisioning __RPC_FAR * This,
    /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);


void __RPC_STUB IRTCClientProvisioning_get_Profiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientProvisioning_GetProfile_Proxy( 
    IRTCClientProvisioning __RPC_FAR * This,
    /* [in] */ BSTR bstrUserAccount,
    /* [in] */ BSTR bstrUserPassword,
    /* [in] */ BSTR bstrUserURI,
    /* [in] */ BSTR bstrServer,
    /* [in] */ long lTransport,
    /* [in] */ LONG_PTR lCookie);


void __RPC_STUB IRTCClientProvisioning_GetProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientProvisioning_get_SessionCapabilities_Proxy( 
    IRTCClientProvisioning __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plSupportedSessions);


void __RPC_STUB IRTCClientProvisioning_get_SessionCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCClientProvisioning_INTERFACE_DEFINED__ */


#ifndef __IRTCClientProvisioning2_INTERFACE_DEFINED__
#define __IRTCClientProvisioning2_INTERFACE_DEFINED__

/* interface IRTCClientProvisioning2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCClientProvisioning2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A70909B5-F40E-4587-BB75-E6BC0845023E")
    IRTCClientProvisioning2 : public IRTCClientProvisioning
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableProfileEx( 
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lRegisterFlags,
            /* [in] */ long lRoamingFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCClientProvisioning2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCClientProvisioning2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCClientProvisioning2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCClientProvisioning2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateProfile )( 
            IRTCClientProvisioning2 __RPC_FAR * This,
            /* [in] */ BSTR bstrProfileXML,
            /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableProfile )( 
            IRTCClientProvisioning2 __RPC_FAR * This,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lRegisterFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisableProfile )( 
            IRTCClientProvisioning2 __RPC_FAR * This,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile);
        
        /* [helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateProfiles )( 
            IRTCClientProvisioning2 __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumProfiles __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profiles )( 
            IRTCClientProvisioning2 __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProfile )( 
            IRTCClientProvisioning2 __RPC_FAR * This,
            /* [in] */ BSTR bstrUserAccount,
            /* [in] */ BSTR bstrUserPassword,
            /* [in] */ BSTR bstrUserURI,
            /* [in] */ BSTR bstrServer,
            /* [in] */ long lTransport,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SessionCapabilities )( 
            IRTCClientProvisioning2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plSupportedSessions);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableProfileEx )( 
            IRTCClientProvisioning2 __RPC_FAR * This,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lRegisterFlags,
            /* [in] */ long lRoamingFlags);
        
        END_INTERFACE
    } IRTCClientProvisioning2Vtbl;

    interface IRTCClientProvisioning2
    {
        CONST_VTBL struct IRTCClientProvisioning2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCClientProvisioning2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCClientProvisioning2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCClientProvisioning2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCClientProvisioning2_CreateProfile(This,bstrProfileXML,ppProfile)	\
    (This)->lpVtbl -> CreateProfile(This,bstrProfileXML,ppProfile)

#define IRTCClientProvisioning2_EnableProfile(This,pProfile,lRegisterFlags)	\
    (This)->lpVtbl -> EnableProfile(This,pProfile,lRegisterFlags)

#define IRTCClientProvisioning2_DisableProfile(This,pProfile)	\
    (This)->lpVtbl -> DisableProfile(This,pProfile)

#define IRTCClientProvisioning2_EnumerateProfiles(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateProfiles(This,ppEnum)

#define IRTCClientProvisioning2_get_Profiles(This,ppCollection)	\
    (This)->lpVtbl -> get_Profiles(This,ppCollection)

#define IRTCClientProvisioning2_GetProfile(This,bstrUserAccount,bstrUserPassword,bstrUserURI,bstrServer,lTransport,lCookie)	\
    (This)->lpVtbl -> GetProfile(This,bstrUserAccount,bstrUserPassword,bstrUserURI,bstrServer,lTransport,lCookie)

#define IRTCClientProvisioning2_get_SessionCapabilities(This,plSupportedSessions)	\
    (This)->lpVtbl -> get_SessionCapabilities(This,plSupportedSessions)


#define IRTCClientProvisioning2_EnableProfileEx(This,pProfile,lRegisterFlags,lRoamingFlags)	\
    (This)->lpVtbl -> EnableProfileEx(This,pProfile,lRegisterFlags,lRoamingFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientProvisioning2_EnableProfileEx_Proxy( 
    IRTCClientProvisioning2 __RPC_FAR * This,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile,
    /* [in] */ long lRegisterFlags,
    /* [in] */ long lRoamingFlags);


void __RPC_STUB IRTCClientProvisioning2_EnableProfileEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCClientProvisioning2_INTERFACE_DEFINED__ */


#ifndef __IRTCProfile_INTERFACE_DEFINED__
#define __IRTCProfile_INTERFACE_DEFINED__

/* interface IRTCProfile */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCProfile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d07eca9e-4062-4dd4-9e7d-722a49ba7303")
    IRTCProfile : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Key( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrKey) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XML( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrXML) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProviderName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProviderURI( 
            /* [in] */ RTC_PROVIDER_URI enURI,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURI) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProviderData( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClientName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClientBanner( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfBanner) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClientMinVer( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrMinVer) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClientCurVer( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCurVer) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClientUpdateURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUpdateURI) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClientData( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UserURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UserName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UserAccount( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserAccount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCredentials( 
            /* [in] */ BSTR bstrUserURI,
            /* [in] */ BSTR bstrUserAccount,
            /* [in] */ BSTR bstrPassword) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SessionCapabilities( 
            /* [retval][out] */ long __RPC_FAR *plSupportedSessions) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ RTC_REGISTRATION_STATE __RPC_FAR *penState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCProfileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCProfile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCProfile __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCProfile __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Key )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrKey);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_XML )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrXML);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderName )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderURI )( 
            IRTCProfile __RPC_FAR * This,
            /* [in] */ RTC_PROVIDER_URI enURI,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderData )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientName )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientBanner )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfBanner);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientMinVer )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrMinVer);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientCurVer )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCurVer);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientUpdateURI )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUpdateURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientData )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserURI )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserAccount )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserAccount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCredentials )( 
            IRTCProfile __RPC_FAR * This,
            /* [in] */ BSTR bstrUserURI,
            /* [in] */ BSTR bstrUserAccount,
            /* [in] */ BSTR bstrPassword);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SessionCapabilities )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plSupportedSessions);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCProfile __RPC_FAR * This,
            /* [retval][out] */ RTC_REGISTRATION_STATE __RPC_FAR *penState);
        
        END_INTERFACE
    } IRTCProfileVtbl;

    interface IRTCProfile
    {
        CONST_VTBL struct IRTCProfileVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCProfile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCProfile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCProfile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCProfile_get_Key(This,pbstrKey)	\
    (This)->lpVtbl -> get_Key(This,pbstrKey)

#define IRTCProfile_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IRTCProfile_get_XML(This,pbstrXML)	\
    (This)->lpVtbl -> get_XML(This,pbstrXML)

#define IRTCProfile_get_ProviderName(This,pbstrName)	\
    (This)->lpVtbl -> get_ProviderName(This,pbstrName)

#define IRTCProfile_get_ProviderURI(This,enURI,pbstrURI)	\
    (This)->lpVtbl -> get_ProviderURI(This,enURI,pbstrURI)

#define IRTCProfile_get_ProviderData(This,pbstrData)	\
    (This)->lpVtbl -> get_ProviderData(This,pbstrData)

#define IRTCProfile_get_ClientName(This,pbstrName)	\
    (This)->lpVtbl -> get_ClientName(This,pbstrName)

#define IRTCProfile_get_ClientBanner(This,pfBanner)	\
    (This)->lpVtbl -> get_ClientBanner(This,pfBanner)

#define IRTCProfile_get_ClientMinVer(This,pbstrMinVer)	\
    (This)->lpVtbl -> get_ClientMinVer(This,pbstrMinVer)

#define IRTCProfile_get_ClientCurVer(This,pbstrCurVer)	\
    (This)->lpVtbl -> get_ClientCurVer(This,pbstrCurVer)

#define IRTCProfile_get_ClientUpdateURI(This,pbstrUpdateURI)	\
    (This)->lpVtbl -> get_ClientUpdateURI(This,pbstrUpdateURI)

#define IRTCProfile_get_ClientData(This,pbstrData)	\
    (This)->lpVtbl -> get_ClientData(This,pbstrData)

#define IRTCProfile_get_UserURI(This,pbstrUserURI)	\
    (This)->lpVtbl -> get_UserURI(This,pbstrUserURI)

#define IRTCProfile_get_UserName(This,pbstrUserName)	\
    (This)->lpVtbl -> get_UserName(This,pbstrUserName)

#define IRTCProfile_get_UserAccount(This,pbstrUserAccount)	\
    (This)->lpVtbl -> get_UserAccount(This,pbstrUserAccount)

#define IRTCProfile_SetCredentials(This,bstrUserURI,bstrUserAccount,bstrPassword)	\
    (This)->lpVtbl -> SetCredentials(This,bstrUserURI,bstrUserAccount,bstrPassword)

#define IRTCProfile_get_SessionCapabilities(This,plSupportedSessions)	\
    (This)->lpVtbl -> get_SessionCapabilities(This,plSupportedSessions)

#define IRTCProfile_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_Key_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrKey);


void __RPC_STUB IRTCProfile_get_Key_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_Name_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IRTCProfile_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_XML_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrXML);


void __RPC_STUB IRTCProfile_get_XML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_ProviderName_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IRTCProfile_get_ProviderName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_ProviderURI_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [in] */ RTC_PROVIDER_URI enURI,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrURI);


void __RPC_STUB IRTCProfile_get_ProviderURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_ProviderData_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrData);


void __RPC_STUB IRTCProfile_get_ProviderData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_ClientName_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IRTCProfile_get_ClientName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_ClientBanner_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfBanner);


void __RPC_STUB IRTCProfile_get_ClientBanner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_ClientMinVer_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrMinVer);


void __RPC_STUB IRTCProfile_get_ClientMinVer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_ClientCurVer_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrCurVer);


void __RPC_STUB IRTCProfile_get_ClientCurVer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_ClientUpdateURI_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrUpdateURI);


void __RPC_STUB IRTCProfile_get_ClientUpdateURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_ClientData_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrData);


void __RPC_STUB IRTCProfile_get_ClientData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_UserURI_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI);


void __RPC_STUB IRTCProfile_get_UserURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_UserName_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName);


void __RPC_STUB IRTCProfile_get_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_UserAccount_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrUserAccount);


void __RPC_STUB IRTCProfile_get_UserAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCProfile_SetCredentials_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [in] */ BSTR bstrUserURI,
    /* [in] */ BSTR bstrUserAccount,
    /* [in] */ BSTR bstrPassword);


void __RPC_STUB IRTCProfile_SetCredentials_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_SessionCapabilities_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plSupportedSessions);


void __RPC_STUB IRTCProfile_get_SessionCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile_get_State_Proxy( 
    IRTCProfile __RPC_FAR * This,
    /* [retval][out] */ RTC_REGISTRATION_STATE __RPC_FAR *penState);


void __RPC_STUB IRTCProfile_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCProfile_INTERFACE_DEFINED__ */


#ifndef __IRTCProfile2_INTERFACE_DEFINED__
#define __IRTCProfile2_INTERFACE_DEFINED__

/* interface IRTCProfile2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCProfile2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4B81F84E-BDC7-4184-9154-3CB2DD7917FB")
    IRTCProfile2 : public IRTCProfile
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Realm( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRealm) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Realm( 
            /* [in] */ BSTR bstrRealm) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AllowedAuth( 
            /* [retval][out] */ long __RPC_FAR *plAllowedAuth) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AllowedAuth( 
            /* [in] */ long lAllowedAuth) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCProfile2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCProfile2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCProfile2 __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Key )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrKey);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_XML )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrXML);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderName )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderURI )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [in] */ RTC_PROVIDER_URI enURI,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderData )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientName )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientBanner )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfBanner);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientMinVer )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrMinVer);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientCurVer )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCurVer);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientUpdateURI )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUpdateURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientData )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserURI )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserAccount )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserAccount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCredentials )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [in] */ BSTR bstrUserURI,
            /* [in] */ BSTR bstrUserAccount,
            /* [in] */ BSTR bstrPassword);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SessionCapabilities )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plSupportedSessions);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ RTC_REGISTRATION_STATE __RPC_FAR *penState);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Realm )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRealm);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Realm )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [in] */ BSTR bstrRealm);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AllowedAuth )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plAllowedAuth);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AllowedAuth )( 
            IRTCProfile2 __RPC_FAR * This,
            /* [in] */ long lAllowedAuth);
        
        END_INTERFACE
    } IRTCProfile2Vtbl;

    interface IRTCProfile2
    {
        CONST_VTBL struct IRTCProfile2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCProfile2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCProfile2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCProfile2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCProfile2_get_Key(This,pbstrKey)	\
    (This)->lpVtbl -> get_Key(This,pbstrKey)

#define IRTCProfile2_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IRTCProfile2_get_XML(This,pbstrXML)	\
    (This)->lpVtbl -> get_XML(This,pbstrXML)

#define IRTCProfile2_get_ProviderName(This,pbstrName)	\
    (This)->lpVtbl -> get_ProviderName(This,pbstrName)

#define IRTCProfile2_get_ProviderURI(This,enURI,pbstrURI)	\
    (This)->lpVtbl -> get_ProviderURI(This,enURI,pbstrURI)

#define IRTCProfile2_get_ProviderData(This,pbstrData)	\
    (This)->lpVtbl -> get_ProviderData(This,pbstrData)

#define IRTCProfile2_get_ClientName(This,pbstrName)	\
    (This)->lpVtbl -> get_ClientName(This,pbstrName)

#define IRTCProfile2_get_ClientBanner(This,pfBanner)	\
    (This)->lpVtbl -> get_ClientBanner(This,pfBanner)

#define IRTCProfile2_get_ClientMinVer(This,pbstrMinVer)	\
    (This)->lpVtbl -> get_ClientMinVer(This,pbstrMinVer)

#define IRTCProfile2_get_ClientCurVer(This,pbstrCurVer)	\
    (This)->lpVtbl -> get_ClientCurVer(This,pbstrCurVer)

#define IRTCProfile2_get_ClientUpdateURI(This,pbstrUpdateURI)	\
    (This)->lpVtbl -> get_ClientUpdateURI(This,pbstrUpdateURI)

#define IRTCProfile2_get_ClientData(This,pbstrData)	\
    (This)->lpVtbl -> get_ClientData(This,pbstrData)

#define IRTCProfile2_get_UserURI(This,pbstrUserURI)	\
    (This)->lpVtbl -> get_UserURI(This,pbstrUserURI)

#define IRTCProfile2_get_UserName(This,pbstrUserName)	\
    (This)->lpVtbl -> get_UserName(This,pbstrUserName)

#define IRTCProfile2_get_UserAccount(This,pbstrUserAccount)	\
    (This)->lpVtbl -> get_UserAccount(This,pbstrUserAccount)

#define IRTCProfile2_SetCredentials(This,bstrUserURI,bstrUserAccount,bstrPassword)	\
    (This)->lpVtbl -> SetCredentials(This,bstrUserURI,bstrUserAccount,bstrPassword)

#define IRTCProfile2_get_SessionCapabilities(This,plSupportedSessions)	\
    (This)->lpVtbl -> get_SessionCapabilities(This,plSupportedSessions)

#define IRTCProfile2_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)


#define IRTCProfile2_get_Realm(This,pbstrRealm)	\
    (This)->lpVtbl -> get_Realm(This,pbstrRealm)

#define IRTCProfile2_put_Realm(This,bstrRealm)	\
    (This)->lpVtbl -> put_Realm(This,bstrRealm)

#define IRTCProfile2_get_AllowedAuth(This,plAllowedAuth)	\
    (This)->lpVtbl -> get_AllowedAuth(This,plAllowedAuth)

#define IRTCProfile2_put_AllowedAuth(This,lAllowedAuth)	\
    (This)->lpVtbl -> put_AllowedAuth(This,lAllowedAuth)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile2_get_Realm_Proxy( 
    IRTCProfile2 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRealm);


void __RPC_STUB IRTCProfile2_get_Realm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCProfile2_put_Realm_Proxy( 
    IRTCProfile2 __RPC_FAR * This,
    /* [in] */ BSTR bstrRealm);


void __RPC_STUB IRTCProfile2_put_Realm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfile2_get_AllowedAuth_Proxy( 
    IRTCProfile2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plAllowedAuth);


void __RPC_STUB IRTCProfile2_get_AllowedAuth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCProfile2_put_AllowedAuth_Proxy( 
    IRTCProfile2 __RPC_FAR * This,
    /* [in] */ long lAllowedAuth);


void __RPC_STUB IRTCProfile2_put_AllowedAuth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCProfile2_INTERFACE_DEFINED__ */


#ifndef __IRTCSession_INTERFACE_DEFINED__
#define __IRTCSession_INTERFACE_DEFINED__

/* interface IRTCSession */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCSession;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("387c8086-99be-42fb-9973-7c0fc0ca9fa8")
    IRTCSession : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Client( 
            /* [retval][out] */ IRTCClient __RPC_FAR *__RPC_FAR *ppClient) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ RTC_SESSION_STATE __RPC_FAR *penState) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ RTC_SESSION_TYPE __RPC_FAR *penType) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Participants( 
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Answer( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Terminate( 
            /* [in] */ RTC_TERMINATE_REASON enReason) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Redirect( 
            /* [in] */ RTC_SESSION_TYPE enType,
            /* [in] */ BSTR bstrLocalPhoneURI,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddParticipant( 
            /* [in] */ BSTR bstrAddress,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveParticipant( 
            /* [in] */ IRTCParticipant __RPC_FAR *pParticipant) = 0;
        
        virtual /* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE EnumerateParticipants( 
            /* [retval][out] */ IRTCEnumParticipants __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CanAddParticipants( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCanAdd) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RedirectedUserURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RedirectedUserName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NextRedirectedUser( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SendMessage( 
            /* [in] */ BSTR bstrMessageHeader,
            /* [in] */ BSTR bstrMessage,
            /* [in] */ LONG_PTR lCookie) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SendMessageStatus( 
            /* [in] */ RTC_MESSAGING_USER_STATUS enUserStatus,
            /* [in] */ LONG_PTR lCookie) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddStream( 
            /* [in] */ long lMediaType,
            /* [in] */ LONG_PTR lCookie) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStream( 
            /* [in] */ long lMediaType,
            /* [in] */ LONG_PTR lCookie) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EncryptionKey( 
            /* [in] */ long lMediaType,
            /* [in] */ BSTR EncryptionKey) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCSessionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCSession __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCSession __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCSession __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Client )( 
            IRTCSession __RPC_FAR * This,
            /* [retval][out] */ IRTCClient __RPC_FAR *__RPC_FAR *ppClient);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCSession __RPC_FAR * This,
            /* [retval][out] */ RTC_SESSION_STATE __RPC_FAR *penState);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IRTCSession __RPC_FAR * This,
            /* [retval][out] */ RTC_SESSION_TYPE __RPC_FAR *penType);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IRTCSession __RPC_FAR * This,
            /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Participants )( 
            IRTCSession __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Answer )( 
            IRTCSession __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Terminate )( 
            IRTCSession __RPC_FAR * This,
            /* [in] */ RTC_TERMINATE_REASON enReason);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Redirect )( 
            IRTCSession __RPC_FAR * This,
            /* [in] */ RTC_SESSION_TYPE enType,
            /* [in] */ BSTR bstrLocalPhoneURI,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddParticipant )( 
            IRTCSession __RPC_FAR * This,
            /* [in] */ BSTR bstrAddress,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveParticipant )( 
            IRTCSession __RPC_FAR * This,
            /* [in] */ IRTCParticipant __RPC_FAR *pParticipant);
        
        /* [helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateParticipants )( 
            IRTCSession __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumParticipants __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CanAddParticipants )( 
            IRTCSession __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCanAdd);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectedUserURI )( 
            IRTCSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectedUserName )( 
            IRTCSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NextRedirectedUser )( 
            IRTCSession __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessage )( 
            IRTCSession __RPC_FAR * This,
            /* [in] */ BSTR bstrMessageHeader,
            /* [in] */ BSTR bstrMessage,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessageStatus )( 
            IRTCSession __RPC_FAR * This,
            /* [in] */ RTC_MESSAGING_USER_STATUS enUserStatus,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddStream )( 
            IRTCSession __RPC_FAR * This,
            /* [in] */ long lMediaType,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveStream )( 
            IRTCSession __RPC_FAR * This,
            /* [in] */ long lMediaType,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncryptionKey )( 
            IRTCSession __RPC_FAR * This,
            /* [in] */ long lMediaType,
            /* [in] */ BSTR EncryptionKey);
        
        END_INTERFACE
    } IRTCSessionVtbl;

    interface IRTCSession
    {
        CONST_VTBL struct IRTCSessionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCSession_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCSession_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCSession_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCSession_get_Client(This,ppClient)	\
    (This)->lpVtbl -> get_Client(This,ppClient)

#define IRTCSession_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#define IRTCSession_get_Type(This,penType)	\
    (This)->lpVtbl -> get_Type(This,penType)

#define IRTCSession_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#define IRTCSession_get_Participants(This,ppCollection)	\
    (This)->lpVtbl -> get_Participants(This,ppCollection)

#define IRTCSession_Answer(This)	\
    (This)->lpVtbl -> Answer(This)

#define IRTCSession_Terminate(This,enReason)	\
    (This)->lpVtbl -> Terminate(This,enReason)

#define IRTCSession_Redirect(This,enType,bstrLocalPhoneURI,pProfile,lFlags)	\
    (This)->lpVtbl -> Redirect(This,enType,bstrLocalPhoneURI,pProfile,lFlags)

#define IRTCSession_AddParticipant(This,bstrAddress,bstrName,ppParticipant)	\
    (This)->lpVtbl -> AddParticipant(This,bstrAddress,bstrName,ppParticipant)

#define IRTCSession_RemoveParticipant(This,pParticipant)	\
    (This)->lpVtbl -> RemoveParticipant(This,pParticipant)

#define IRTCSession_EnumerateParticipants(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateParticipants(This,ppEnum)

#define IRTCSession_get_CanAddParticipants(This,pfCanAdd)	\
    (This)->lpVtbl -> get_CanAddParticipants(This,pfCanAdd)

#define IRTCSession_get_RedirectedUserURI(This,pbstrUserURI)	\
    (This)->lpVtbl -> get_RedirectedUserURI(This,pbstrUserURI)

#define IRTCSession_get_RedirectedUserName(This,pbstrUserName)	\
    (This)->lpVtbl -> get_RedirectedUserName(This,pbstrUserName)

#define IRTCSession_NextRedirectedUser(This)	\
    (This)->lpVtbl -> NextRedirectedUser(This)

#define IRTCSession_SendMessage(This,bstrMessageHeader,bstrMessage,lCookie)	\
    (This)->lpVtbl -> SendMessage(This,bstrMessageHeader,bstrMessage,lCookie)

#define IRTCSession_SendMessageStatus(This,enUserStatus,lCookie)	\
    (This)->lpVtbl -> SendMessageStatus(This,enUserStatus,lCookie)

#define IRTCSession_AddStream(This,lMediaType,lCookie)	\
    (This)->lpVtbl -> AddStream(This,lMediaType,lCookie)

#define IRTCSession_RemoveStream(This,lMediaType,lCookie)	\
    (This)->lpVtbl -> RemoveStream(This,lMediaType,lCookie)

#define IRTCSession_put_EncryptionKey(This,lMediaType,EncryptionKey)	\
    (This)->lpVtbl -> put_EncryptionKey(This,lMediaType,EncryptionKey)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSession_get_Client_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [retval][out] */ IRTCClient __RPC_FAR *__RPC_FAR *ppClient);


void __RPC_STUB IRTCSession_get_Client_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSession_get_State_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [retval][out] */ RTC_SESSION_STATE __RPC_FAR *penState);


void __RPC_STUB IRTCSession_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSession_get_Type_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [retval][out] */ RTC_SESSION_TYPE __RPC_FAR *penType);


void __RPC_STUB IRTCSession_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSession_get_Profile_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB IRTCSession_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSession_get_Participants_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);


void __RPC_STUB IRTCSession_get_Participants_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession_Answer_Proxy( 
    IRTCSession __RPC_FAR * This);


void __RPC_STUB IRTCSession_Answer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession_Terminate_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [in] */ RTC_TERMINATE_REASON enReason);


void __RPC_STUB IRTCSession_Terminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession_Redirect_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [in] */ RTC_SESSION_TYPE enType,
    /* [in] */ BSTR bstrLocalPhoneURI,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile,
    /* [in] */ long lFlags);


void __RPC_STUB IRTCSession_Redirect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession_AddParticipant_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [in] */ BSTR bstrAddress,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant);


void __RPC_STUB IRTCSession_AddParticipant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession_RemoveParticipant_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [in] */ IRTCParticipant __RPC_FAR *pParticipant);


void __RPC_STUB IRTCSession_RemoveParticipant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IRTCSession_EnumerateParticipants_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumParticipants __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCSession_EnumerateParticipants_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSession_get_CanAddParticipants_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCanAdd);


void __RPC_STUB IRTCSession_get_CanAddParticipants_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSession_get_RedirectedUserURI_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI);


void __RPC_STUB IRTCSession_get_RedirectedUserURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSession_get_RedirectedUserName_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName);


void __RPC_STUB IRTCSession_get_RedirectedUserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession_NextRedirectedUser_Proxy( 
    IRTCSession __RPC_FAR * This);


void __RPC_STUB IRTCSession_NextRedirectedUser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession_SendMessage_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [in] */ BSTR bstrMessageHeader,
    /* [in] */ BSTR bstrMessage,
    /* [in] */ LONG_PTR lCookie);


void __RPC_STUB IRTCSession_SendMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession_SendMessageStatus_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [in] */ RTC_MESSAGING_USER_STATUS enUserStatus,
    /* [in] */ LONG_PTR lCookie);


void __RPC_STUB IRTCSession_SendMessageStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession_AddStream_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [in] */ long lMediaType,
    /* [in] */ LONG_PTR lCookie);


void __RPC_STUB IRTCSession_AddStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession_RemoveStream_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [in] */ long lMediaType,
    /* [in] */ LONG_PTR lCookie);


void __RPC_STUB IRTCSession_RemoveStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCSession_put_EncryptionKey_Proxy( 
    IRTCSession __RPC_FAR * This,
    /* [in] */ long lMediaType,
    /* [in] */ BSTR EncryptionKey);


void __RPC_STUB IRTCSession_put_EncryptionKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCSession_INTERFACE_DEFINED__ */


#ifndef __IRTCSession2_INTERFACE_DEFINED__
#define __IRTCSession2_INTERFACE_DEFINED__

/* interface IRTCSession2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCSession2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("17D7CDFC-B007-484c-99D2-86A8A820991D")
    IRTCSession2 : public IRTCSession
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SendInfo( 
            /* [in] */ BSTR bstrInfoHeader,
            /* [in] */ BSTR bstrInfo,
            /* [in] */ LONG_PTR lCookie) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PreferredSecurityLevel( 
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [in] */ RTC_SECURITY_LEVEL enSecurityLevel) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredSecurityLevel( 
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsSecurityEnabled( 
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSecurityEnabled) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AnswerWithSessionDescription( 
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReInviteWithSessionDescription( 
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription,
            /* [in] */ LONG_PTR lCookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCSession2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCSession2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCSession2 __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Client )( 
            IRTCSession2 __RPC_FAR * This,
            /* [retval][out] */ IRTCClient __RPC_FAR *__RPC_FAR *ppClient);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCSession2 __RPC_FAR * This,
            /* [retval][out] */ RTC_SESSION_STATE __RPC_FAR *penState);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IRTCSession2 __RPC_FAR * This,
            /* [retval][out] */ RTC_SESSION_TYPE __RPC_FAR *penType);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IRTCSession2 __RPC_FAR * This,
            /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Participants )( 
            IRTCSession2 __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Answer )( 
            IRTCSession2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Terminate )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ RTC_TERMINATE_REASON enReason);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Redirect )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ RTC_SESSION_TYPE enType,
            /* [in] */ BSTR bstrLocalPhoneURI,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ long lFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddParticipant )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ BSTR bstrAddress,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveParticipant )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ IRTCParticipant __RPC_FAR *pParticipant);
        
        /* [helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateParticipants )( 
            IRTCSession2 __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumParticipants __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CanAddParticipants )( 
            IRTCSession2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCanAdd);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectedUserURI )( 
            IRTCSession2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectedUserName )( 
            IRTCSession2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NextRedirectedUser )( 
            IRTCSession2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessage )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ BSTR bstrMessageHeader,
            /* [in] */ BSTR bstrMessage,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessageStatus )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ RTC_MESSAGING_USER_STATUS enUserStatus,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddStream )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ long lMediaType,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveStream )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ long lMediaType,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncryptionKey )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ long lMediaType,
            /* [in] */ BSTR EncryptionKey);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendInfo )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ BSTR bstrInfoHeader,
            /* [in] */ BSTR bstrInfo,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PreferredSecurityLevel )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [in] */ RTC_SECURITY_LEVEL enSecurityLevel);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredSecurityLevel )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSecurityEnabled )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSecurityEnabled);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AnswerWithSessionDescription )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReInviteWithSessionDescription )( 
            IRTCSession2 __RPC_FAR * This,
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription,
            /* [in] */ LONG_PTR lCookie);
        
        END_INTERFACE
    } IRTCSession2Vtbl;

    interface IRTCSession2
    {
        CONST_VTBL struct IRTCSession2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCSession2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCSession2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCSession2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCSession2_get_Client(This,ppClient)	\
    (This)->lpVtbl -> get_Client(This,ppClient)

#define IRTCSession2_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#define IRTCSession2_get_Type(This,penType)	\
    (This)->lpVtbl -> get_Type(This,penType)

#define IRTCSession2_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#define IRTCSession2_get_Participants(This,ppCollection)	\
    (This)->lpVtbl -> get_Participants(This,ppCollection)

#define IRTCSession2_Answer(This)	\
    (This)->lpVtbl -> Answer(This)

#define IRTCSession2_Terminate(This,enReason)	\
    (This)->lpVtbl -> Terminate(This,enReason)

#define IRTCSession2_Redirect(This,enType,bstrLocalPhoneURI,pProfile,lFlags)	\
    (This)->lpVtbl -> Redirect(This,enType,bstrLocalPhoneURI,pProfile,lFlags)

#define IRTCSession2_AddParticipant(This,bstrAddress,bstrName,ppParticipant)	\
    (This)->lpVtbl -> AddParticipant(This,bstrAddress,bstrName,ppParticipant)

#define IRTCSession2_RemoveParticipant(This,pParticipant)	\
    (This)->lpVtbl -> RemoveParticipant(This,pParticipant)

#define IRTCSession2_EnumerateParticipants(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateParticipants(This,ppEnum)

#define IRTCSession2_get_CanAddParticipants(This,pfCanAdd)	\
    (This)->lpVtbl -> get_CanAddParticipants(This,pfCanAdd)

#define IRTCSession2_get_RedirectedUserURI(This,pbstrUserURI)	\
    (This)->lpVtbl -> get_RedirectedUserURI(This,pbstrUserURI)

#define IRTCSession2_get_RedirectedUserName(This,pbstrUserName)	\
    (This)->lpVtbl -> get_RedirectedUserName(This,pbstrUserName)

#define IRTCSession2_NextRedirectedUser(This)	\
    (This)->lpVtbl -> NextRedirectedUser(This)

#define IRTCSession2_SendMessage(This,bstrMessageHeader,bstrMessage,lCookie)	\
    (This)->lpVtbl -> SendMessage(This,bstrMessageHeader,bstrMessage,lCookie)

#define IRTCSession2_SendMessageStatus(This,enUserStatus,lCookie)	\
    (This)->lpVtbl -> SendMessageStatus(This,enUserStatus,lCookie)

#define IRTCSession2_AddStream(This,lMediaType,lCookie)	\
    (This)->lpVtbl -> AddStream(This,lMediaType,lCookie)

#define IRTCSession2_RemoveStream(This,lMediaType,lCookie)	\
    (This)->lpVtbl -> RemoveStream(This,lMediaType,lCookie)

#define IRTCSession2_put_EncryptionKey(This,lMediaType,EncryptionKey)	\
    (This)->lpVtbl -> put_EncryptionKey(This,lMediaType,EncryptionKey)


#define IRTCSession2_SendInfo(This,bstrInfoHeader,bstrInfo,lCookie)	\
    (This)->lpVtbl -> SendInfo(This,bstrInfoHeader,bstrInfo,lCookie)

#define IRTCSession2_put_PreferredSecurityLevel(This,enSecurityType,enSecurityLevel)	\
    (This)->lpVtbl -> put_PreferredSecurityLevel(This,enSecurityType,enSecurityLevel)

#define IRTCSession2_get_PreferredSecurityLevel(This,enSecurityType,penSecurityLevel)	\
    (This)->lpVtbl -> get_PreferredSecurityLevel(This,enSecurityType,penSecurityLevel)

#define IRTCSession2_IsSecurityEnabled(This,enSecurityType,pfSecurityEnabled)	\
    (This)->lpVtbl -> IsSecurityEnabled(This,enSecurityType,pfSecurityEnabled)

#define IRTCSession2_AnswerWithSessionDescription(This,bstrContentType,bstrSessionDescription)	\
    (This)->lpVtbl -> AnswerWithSessionDescription(This,bstrContentType,bstrSessionDescription)

#define IRTCSession2_ReInviteWithSessionDescription(This,bstrContentType,bstrSessionDescription,lCookie)	\
    (This)->lpVtbl -> ReInviteWithSessionDescription(This,bstrContentType,bstrSessionDescription,lCookie)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession2_SendInfo_Proxy( 
    IRTCSession2 __RPC_FAR * This,
    /* [in] */ BSTR bstrInfoHeader,
    /* [in] */ BSTR bstrInfo,
    /* [in] */ LONG_PTR lCookie);


void __RPC_STUB IRTCSession2_SendInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCSession2_put_PreferredSecurityLevel_Proxy( 
    IRTCSession2 __RPC_FAR * This,
    /* [in] */ RTC_SECURITY_TYPE enSecurityType,
    /* [in] */ RTC_SECURITY_LEVEL enSecurityLevel);


void __RPC_STUB IRTCSession2_put_PreferredSecurityLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSession2_get_PreferredSecurityLevel_Proxy( 
    IRTCSession2 __RPC_FAR * This,
    /* [in] */ RTC_SECURITY_TYPE enSecurityType,
    /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel);


void __RPC_STUB IRTCSession2_get_PreferredSecurityLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession2_IsSecurityEnabled_Proxy( 
    IRTCSession2 __RPC_FAR * This,
    /* [in] */ RTC_SECURITY_TYPE enSecurityType,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSecurityEnabled);


void __RPC_STUB IRTCSession2_IsSecurityEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession2_AnswerWithSessionDescription_Proxy( 
    IRTCSession2 __RPC_FAR * This,
    /* [in] */ BSTR bstrContentType,
    /* [in] */ BSTR bstrSessionDescription);


void __RPC_STUB IRTCSession2_AnswerWithSessionDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSession2_ReInviteWithSessionDescription_Proxy( 
    IRTCSession2 __RPC_FAR * This,
    /* [in] */ BSTR bstrContentType,
    /* [in] */ BSTR bstrSessionDescription,
    /* [in] */ LONG_PTR lCookie);


void __RPC_STUB IRTCSession2_ReInviteWithSessionDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCSession2_INTERFACE_DEFINED__ */


#ifndef __IRTCSessionCallControl_INTERFACE_DEFINED__
#define __IRTCSessionCallControl_INTERFACE_DEFINED__

/* interface IRTCSessionCallControl */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCSessionCallControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E9A50D94-190B-4F82-9530-3B8EBF60758A")
    IRTCSessionCallControl : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Hold( 
            /* [in] */ LONG_PTR lCookie) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnHold( 
            /* [in] */ LONG_PTR lCookie) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Forward( 
            /* [in] */ BSTR bstrForwardToURI) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Refer( 
            /* [in] */ BSTR bstrReferToURI,
            /* [in] */ BSTR bstrReferCookie) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ReferredByURI( 
            /* [in] */ BSTR bstrReferredByURI) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ReferredByURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferredByURI) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ReferCookie( 
            /* [in] */ BSTR bstrReferCookie) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ReferCookie( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferCookie) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsReferred( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsReferred) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCSessionCallControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCSessionCallControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCSessionCallControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCSessionCallControl __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hold )( 
            IRTCSessionCallControl __RPC_FAR * This,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnHold )( 
            IRTCSessionCallControl __RPC_FAR * This,
            /* [in] */ LONG_PTR lCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Forward )( 
            IRTCSessionCallControl __RPC_FAR * This,
            /* [in] */ BSTR bstrForwardToURI);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refer )( 
            IRTCSessionCallControl __RPC_FAR * This,
            /* [in] */ BSTR bstrReferToURI,
            /* [in] */ BSTR bstrReferCookie);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReferredByURI )( 
            IRTCSessionCallControl __RPC_FAR * This,
            /* [in] */ BSTR bstrReferredByURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReferredByURI )( 
            IRTCSessionCallControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferredByURI);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReferCookie )( 
            IRTCSessionCallControl __RPC_FAR * This,
            /* [in] */ BSTR bstrReferCookie);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReferCookie )( 
            IRTCSessionCallControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferCookie);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsReferred )( 
            IRTCSessionCallControl __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsReferred);
        
        END_INTERFACE
    } IRTCSessionCallControlVtbl;

    interface IRTCSessionCallControl
    {
        CONST_VTBL struct IRTCSessionCallControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCSessionCallControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCSessionCallControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCSessionCallControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCSessionCallControl_Hold(This,lCookie)	\
    (This)->lpVtbl -> Hold(This,lCookie)

#define IRTCSessionCallControl_UnHold(This,lCookie)	\
    (This)->lpVtbl -> UnHold(This,lCookie)

#define IRTCSessionCallControl_Forward(This,bstrForwardToURI)	\
    (This)->lpVtbl -> Forward(This,bstrForwardToURI)

#define IRTCSessionCallControl_Refer(This,bstrReferToURI,bstrReferCookie)	\
    (This)->lpVtbl -> Refer(This,bstrReferToURI,bstrReferCookie)

#define IRTCSessionCallControl_put_ReferredByURI(This,bstrReferredByURI)	\
    (This)->lpVtbl -> put_ReferredByURI(This,bstrReferredByURI)

#define IRTCSessionCallControl_get_ReferredByURI(This,pbstrReferredByURI)	\
    (This)->lpVtbl -> get_ReferredByURI(This,pbstrReferredByURI)

#define IRTCSessionCallControl_put_ReferCookie(This,bstrReferCookie)	\
    (This)->lpVtbl -> put_ReferCookie(This,bstrReferCookie)

#define IRTCSessionCallControl_get_ReferCookie(This,pbstrReferCookie)	\
    (This)->lpVtbl -> get_ReferCookie(This,pbstrReferCookie)

#define IRTCSessionCallControl_get_IsReferred(This,pfIsReferred)	\
    (This)->lpVtbl -> get_IsReferred(This,pfIsReferred)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSessionCallControl_Hold_Proxy( 
    IRTCSessionCallControl __RPC_FAR * This,
    /* [in] */ LONG_PTR lCookie);


void __RPC_STUB IRTCSessionCallControl_Hold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSessionCallControl_UnHold_Proxy( 
    IRTCSessionCallControl __RPC_FAR * This,
    /* [in] */ LONG_PTR lCookie);


void __RPC_STUB IRTCSessionCallControl_UnHold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSessionCallControl_Forward_Proxy( 
    IRTCSessionCallControl __RPC_FAR * This,
    /* [in] */ BSTR bstrForwardToURI);


void __RPC_STUB IRTCSessionCallControl_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCSessionCallControl_Refer_Proxy( 
    IRTCSessionCallControl __RPC_FAR * This,
    /* [in] */ BSTR bstrReferToURI,
    /* [in] */ BSTR bstrReferCookie);


void __RPC_STUB IRTCSessionCallControl_Refer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCSessionCallControl_put_ReferredByURI_Proxy( 
    IRTCSessionCallControl __RPC_FAR * This,
    /* [in] */ BSTR bstrReferredByURI);


void __RPC_STUB IRTCSessionCallControl_put_ReferredByURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionCallControl_get_ReferredByURI_Proxy( 
    IRTCSessionCallControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrReferredByURI);


void __RPC_STUB IRTCSessionCallControl_get_ReferredByURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCSessionCallControl_put_ReferCookie_Proxy( 
    IRTCSessionCallControl __RPC_FAR * This,
    /* [in] */ BSTR bstrReferCookie);


void __RPC_STUB IRTCSessionCallControl_put_ReferCookie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionCallControl_get_ReferCookie_Proxy( 
    IRTCSessionCallControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrReferCookie);


void __RPC_STUB IRTCSessionCallControl_get_ReferCookie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionCallControl_get_IsReferred_Proxy( 
    IRTCSessionCallControl __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsReferred);


void __RPC_STUB IRTCSessionCallControl_get_IsReferred_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCSessionCallControl_INTERFACE_DEFINED__ */


#ifndef __IRTCParticipant_INTERFACE_DEFINED__
#define __IRTCParticipant_INTERFACE_DEFINED__

/* interface IRTCParticipant */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCParticipant;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ae86add5-26b1-4414-af1d-b94cd938d739")
    IRTCParticipant : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UserURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Removable( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRemovable) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ RTC_PARTICIPANT_STATE __RPC_FAR *penState) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCParticipantVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCParticipant __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCParticipant __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCParticipant __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserURI )( 
            IRTCParticipant __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IRTCParticipant __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Removable )( 
            IRTCParticipant __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRemovable);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCParticipant __RPC_FAR * This,
            /* [retval][out] */ RTC_PARTICIPANT_STATE __RPC_FAR *penState);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IRTCParticipant __RPC_FAR * This,
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);
        
        END_INTERFACE
    } IRTCParticipantVtbl;

    interface IRTCParticipant
    {
        CONST_VTBL struct IRTCParticipantVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCParticipant_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCParticipant_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCParticipant_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCParticipant_get_UserURI(This,pbstrUserURI)	\
    (This)->lpVtbl -> get_UserURI(This,pbstrUserURI)

#define IRTCParticipant_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IRTCParticipant_get_Removable(This,pfRemovable)	\
    (This)->lpVtbl -> get_Removable(This,pfRemovable)

#define IRTCParticipant_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#define IRTCParticipant_get_Session(This,ppSession)	\
    (This)->lpVtbl -> get_Session(This,ppSession)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCParticipant_get_UserURI_Proxy( 
    IRTCParticipant __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrUserURI);


void __RPC_STUB IRTCParticipant_get_UserURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCParticipant_get_Name_Proxy( 
    IRTCParticipant __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IRTCParticipant_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCParticipant_get_Removable_Proxy( 
    IRTCParticipant __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRemovable);


void __RPC_STUB IRTCParticipant_get_Removable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCParticipant_get_State_Proxy( 
    IRTCParticipant __RPC_FAR * This,
    /* [retval][out] */ RTC_PARTICIPANT_STATE __RPC_FAR *penState);


void __RPC_STUB IRTCParticipant_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCParticipant_get_Session_Proxy( 
    IRTCParticipant __RPC_FAR * This,
    /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);


void __RPC_STUB IRTCParticipant_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCParticipant_INTERFACE_DEFINED__ */


#ifndef __IRTCRoamingEvent_INTERFACE_DEFINED__
#define __IRTCRoamingEvent_INTERFACE_DEFINED__

/* interface IRTCRoamingEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCRoamingEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("79960a6b-0cb1-4dc8-a805-7318e99902e8")
    IRTCRoamingEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EventType( 
            /* [retval][out] */ RTC_ROAMING_EVENT_TYPE __RPC_FAR *pEventType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCRoamingEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCRoamingEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCRoamingEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCRoamingEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCRoamingEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCRoamingEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCRoamingEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCRoamingEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventType )( 
            IRTCRoamingEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_ROAMING_EVENT_TYPE __RPC_FAR *pEventType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IRTCRoamingEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCRoamingEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IRTCRoamingEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);
        
        END_INTERFACE
    } IRTCRoamingEventVtbl;

    interface IRTCRoamingEvent
    {
        CONST_VTBL struct IRTCRoamingEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCRoamingEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCRoamingEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCRoamingEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCRoamingEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCRoamingEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCRoamingEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCRoamingEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCRoamingEvent_get_EventType(This,pEventType)	\
    (This)->lpVtbl -> get_EventType(This,pEventType)

#define IRTCRoamingEvent_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#define IRTCRoamingEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCRoamingEvent_get_StatusText(This,pbstrStatusText)	\
    (This)->lpVtbl -> get_StatusText(This,pbstrStatusText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCRoamingEvent_get_EventType_Proxy( 
    IRTCRoamingEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_ROAMING_EVENT_TYPE __RPC_FAR *pEventType);


void __RPC_STUB IRTCRoamingEvent_get_EventType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCRoamingEvent_get_Profile_Proxy( 
    IRTCRoamingEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB IRTCRoamingEvent_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCRoamingEvent_get_StatusCode_Proxy( 
    IRTCRoamingEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCRoamingEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCRoamingEvent_get_StatusText_Proxy( 
    IRTCRoamingEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);


void __RPC_STUB IRTCRoamingEvent_get_StatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCRoamingEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCProfileEvent_INTERFACE_DEFINED__
#define __IRTCProfileEvent_INTERFACE_DEFINED__

/* interface IRTCProfileEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCProfileEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D6D5AB3B-770E-43e8-800A-79B062395FCA")
    IRTCProfileEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cookie( 
            /* [retval][out] */ LONG_PTR __RPC_FAR *plCookie) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCProfileEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCProfileEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCProfileEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCProfileEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCProfileEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCProfileEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCProfileEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCProfileEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IRTCProfileEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cookie )( 
            IRTCProfileEvent __RPC_FAR * This,
            /* [retval][out] */ LONG_PTR __RPC_FAR *plCookie);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCProfileEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        END_INTERFACE
    } IRTCProfileEventVtbl;

    interface IRTCProfileEvent
    {
        CONST_VTBL struct IRTCProfileEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCProfileEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCProfileEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCProfileEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCProfileEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCProfileEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCProfileEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCProfileEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCProfileEvent_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#define IRTCProfileEvent_get_Cookie(This,plCookie)	\
    (This)->lpVtbl -> get_Cookie(This,plCookie)

#define IRTCProfileEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfileEvent_get_Profile_Proxy( 
    IRTCProfileEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB IRTCProfileEvent_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfileEvent_get_Cookie_Proxy( 
    IRTCProfileEvent __RPC_FAR * This,
    /* [retval][out] */ LONG_PTR __RPC_FAR *plCookie);


void __RPC_STUB IRTCProfileEvent_get_Cookie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfileEvent_get_StatusCode_Proxy( 
    IRTCProfileEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCProfileEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCProfileEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCProfileEvent2_INTERFACE_DEFINED__
#define __IRTCProfileEvent2_INTERFACE_DEFINED__

/* interface IRTCProfileEvent2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCProfileEvent2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62E56EDC-03FA-4121-94FB-23493FD0AE64")
    IRTCProfileEvent2 : public IRTCProfileEvent
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EventType( 
            /* [retval][out] */ RTC_PROFILE_EVENT_TYPE __RPC_FAR *pEventType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCProfileEvent2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCProfileEvent2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCProfileEvent2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCProfileEvent2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCProfileEvent2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCProfileEvent2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCProfileEvent2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCProfileEvent2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IRTCProfileEvent2 __RPC_FAR * This,
            /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cookie )( 
            IRTCProfileEvent2 __RPC_FAR * This,
            /* [retval][out] */ LONG_PTR __RPC_FAR *plCookie);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCProfileEvent2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventType )( 
            IRTCProfileEvent2 __RPC_FAR * This,
            /* [retval][out] */ RTC_PROFILE_EVENT_TYPE __RPC_FAR *pEventType);
        
        END_INTERFACE
    } IRTCProfileEvent2Vtbl;

    interface IRTCProfileEvent2
    {
        CONST_VTBL struct IRTCProfileEvent2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCProfileEvent2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCProfileEvent2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCProfileEvent2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCProfileEvent2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCProfileEvent2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCProfileEvent2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCProfileEvent2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCProfileEvent2_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#define IRTCProfileEvent2_get_Cookie(This,plCookie)	\
    (This)->lpVtbl -> get_Cookie(This,plCookie)

#define IRTCProfileEvent2_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)


#define IRTCProfileEvent2_get_EventType(This,pEventType)	\
    (This)->lpVtbl -> get_EventType(This,pEventType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCProfileEvent2_get_EventType_Proxy( 
    IRTCProfileEvent2 __RPC_FAR * This,
    /* [retval][out] */ RTC_PROFILE_EVENT_TYPE __RPC_FAR *pEventType);


void __RPC_STUB IRTCProfileEvent2_get_EventType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCProfileEvent2_INTERFACE_DEFINED__ */


#ifndef __IRTCClientEvent_INTERFACE_DEFINED__
#define __IRTCClientEvent_INTERFACE_DEFINED__

/* interface IRTCClientEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCClientEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2b493b7a-3cba-4170-9c8b-76a9dacdd644")
    IRTCClientEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EventType( 
            /* [retval][out] */ RTC_CLIENT_EVENT_TYPE __RPC_FAR *penEventType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Client( 
            /* [retval][out] */ IRTCClient __RPC_FAR *__RPC_FAR *ppClient) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCClientEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCClientEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCClientEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCClientEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCClientEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCClientEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCClientEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCClientEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventType )( 
            IRTCClientEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_CLIENT_EVENT_TYPE __RPC_FAR *penEventType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Client )( 
            IRTCClientEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCClient __RPC_FAR *__RPC_FAR *ppClient);
        
        END_INTERFACE
    } IRTCClientEventVtbl;

    interface IRTCClientEvent
    {
        CONST_VTBL struct IRTCClientEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCClientEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCClientEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCClientEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCClientEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCClientEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCClientEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCClientEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCClientEvent_get_EventType(This,penEventType)	\
    (This)->lpVtbl -> get_EventType(This,penEventType)

#define IRTCClientEvent_get_Client(This,ppClient)	\
    (This)->lpVtbl -> get_Client(This,ppClient)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientEvent_get_EventType_Proxy( 
    IRTCClientEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_CLIENT_EVENT_TYPE __RPC_FAR *penEventType);


void __RPC_STUB IRTCClientEvent_get_EventType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCClientEvent_get_Client_Proxy( 
    IRTCClientEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCClient __RPC_FAR *__RPC_FAR *ppClient);


void __RPC_STUB IRTCClientEvent_get_Client_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCClientEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCRegistrationStateChangeEvent_INTERFACE_DEFINED__
#define __IRTCRegistrationStateChangeEvent_INTERFACE_DEFINED__

/* interface IRTCRegistrationStateChangeEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCRegistrationStateChangeEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62d0991b-50ab-4f02-b948-ca94f26f8f95")
    IRTCRegistrationStateChangeEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ RTC_REGISTRATION_STATE __RPC_FAR *penState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCRegistrationStateChangeEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCRegistrationStateChangeEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCRegistrationStateChangeEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCRegistrationStateChangeEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCRegistrationStateChangeEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCRegistrationStateChangeEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCRegistrationStateChangeEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCRegistrationStateChangeEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IRTCRegistrationStateChangeEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCRegistrationStateChangeEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_REGISTRATION_STATE __RPC_FAR *penState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCRegistrationStateChangeEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IRTCRegistrationStateChangeEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);
        
        END_INTERFACE
    } IRTCRegistrationStateChangeEventVtbl;

    interface IRTCRegistrationStateChangeEvent
    {
        CONST_VTBL struct IRTCRegistrationStateChangeEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCRegistrationStateChangeEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCRegistrationStateChangeEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCRegistrationStateChangeEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCRegistrationStateChangeEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCRegistrationStateChangeEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCRegistrationStateChangeEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCRegistrationStateChangeEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCRegistrationStateChangeEvent_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#define IRTCRegistrationStateChangeEvent_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#define IRTCRegistrationStateChangeEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCRegistrationStateChangeEvent_get_StatusText(This,pbstrStatusText)	\
    (This)->lpVtbl -> get_StatusText(This,pbstrStatusText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCRegistrationStateChangeEvent_get_Profile_Proxy( 
    IRTCRegistrationStateChangeEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB IRTCRegistrationStateChangeEvent_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCRegistrationStateChangeEvent_get_State_Proxy( 
    IRTCRegistrationStateChangeEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_REGISTRATION_STATE __RPC_FAR *penState);


void __RPC_STUB IRTCRegistrationStateChangeEvent_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCRegistrationStateChangeEvent_get_StatusCode_Proxy( 
    IRTCRegistrationStateChangeEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCRegistrationStateChangeEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCRegistrationStateChangeEvent_get_StatusText_Proxy( 
    IRTCRegistrationStateChangeEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);


void __RPC_STUB IRTCRegistrationStateChangeEvent_get_StatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCRegistrationStateChangeEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCSessionStateChangeEvent_INTERFACE_DEFINED__
#define __IRTCSessionStateChangeEvent_INTERFACE_DEFINED__

/* interface IRTCSessionStateChangeEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCSessionStateChangeEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b5bad703-5952-48b3-9321-7f4500521506")
    IRTCSessionStateChangeEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ RTC_SESSION_STATE __RPC_FAR *penState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCSessionStateChangeEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCSessionStateChangeEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCSessionStateChangeEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCSessionStateChangeEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCSessionStateChangeEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCSessionStateChangeEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCSessionStateChangeEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCSessionStateChangeEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IRTCSessionStateChangeEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCSessionStateChangeEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_SESSION_STATE __RPC_FAR *penState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCSessionStateChangeEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IRTCSessionStateChangeEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);
        
        END_INTERFACE
    } IRTCSessionStateChangeEventVtbl;

    interface IRTCSessionStateChangeEvent
    {
        CONST_VTBL struct IRTCSessionStateChangeEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCSessionStateChangeEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCSessionStateChangeEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCSessionStateChangeEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCSessionStateChangeEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCSessionStateChangeEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCSessionStateChangeEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCSessionStateChangeEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCSessionStateChangeEvent_get_Session(This,ppSession)	\
    (This)->lpVtbl -> get_Session(This,ppSession)

#define IRTCSessionStateChangeEvent_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#define IRTCSessionStateChangeEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCSessionStateChangeEvent_get_StatusText(This,pbstrStatusText)	\
    (This)->lpVtbl -> get_StatusText(This,pbstrStatusText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionStateChangeEvent_get_Session_Proxy( 
    IRTCSessionStateChangeEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);


void __RPC_STUB IRTCSessionStateChangeEvent_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionStateChangeEvent_get_State_Proxy( 
    IRTCSessionStateChangeEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_SESSION_STATE __RPC_FAR *penState);


void __RPC_STUB IRTCSessionStateChangeEvent_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionStateChangeEvent_get_StatusCode_Proxy( 
    IRTCSessionStateChangeEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCSessionStateChangeEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionStateChangeEvent_get_StatusText_Proxy( 
    IRTCSessionStateChangeEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);


void __RPC_STUB IRTCSessionStateChangeEvent_get_StatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCSessionStateChangeEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCSessionStateChangeEvent2_INTERFACE_DEFINED__
#define __IRTCSessionStateChangeEvent2_INTERFACE_DEFINED__

/* interface IRTCSessionStateChangeEvent2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCSessionStateChangeEvent2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F933171-6F95-4880-80D9-2EC8D495D261")
    IRTCSessionStateChangeEvent2 : public IRTCSessionStateChangeEvent
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaTypes( 
            /* [retval][out] */ long __RPC_FAR *pMediaTypes) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemotePreferredSecurityLevel( 
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsForked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsForked) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRemoteSessionDescription( 
            /* [out] */ BSTR __RPC_FAR *pbstrContentType,
            /* [out] */ BSTR __RPC_FAR *pbstrSessionDescription) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCSessionStateChangeEvent2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [retval][out] */ RTC_SESSION_STATE __RPC_FAR *penState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaTypes )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pMediaTypes);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemotePreferredSecurityLevel )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsForked )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsForked);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRemoteSessionDescription )( 
            IRTCSessionStateChangeEvent2 __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrContentType,
            /* [out] */ BSTR __RPC_FAR *pbstrSessionDescription);
        
        END_INTERFACE
    } IRTCSessionStateChangeEvent2Vtbl;

    interface IRTCSessionStateChangeEvent2
    {
        CONST_VTBL struct IRTCSessionStateChangeEvent2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCSessionStateChangeEvent2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCSessionStateChangeEvent2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCSessionStateChangeEvent2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCSessionStateChangeEvent2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCSessionStateChangeEvent2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCSessionStateChangeEvent2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCSessionStateChangeEvent2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCSessionStateChangeEvent2_get_Session(This,ppSession)	\
    (This)->lpVtbl -> get_Session(This,ppSession)

#define IRTCSessionStateChangeEvent2_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#define IRTCSessionStateChangeEvent2_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCSessionStateChangeEvent2_get_StatusText(This,pbstrStatusText)	\
    (This)->lpVtbl -> get_StatusText(This,pbstrStatusText)


#define IRTCSessionStateChangeEvent2_get_MediaTypes(This,pMediaTypes)	\
    (This)->lpVtbl -> get_MediaTypes(This,pMediaTypes)

#define IRTCSessionStateChangeEvent2_get_RemotePreferredSecurityLevel(This,enSecurityType,penSecurityLevel)	\
    (This)->lpVtbl -> get_RemotePreferredSecurityLevel(This,enSecurityType,penSecurityLevel)

#define IRTCSessionStateChangeEvent2_get_IsForked(This,pfIsForked)	\
    (This)->lpVtbl -> get_IsForked(This,pfIsForked)

#define IRTCSessionStateChangeEvent2_GetRemoteSessionDescription(This,pbstrContentType,pbstrSessionDescription)	\
    (This)->lpVtbl -> GetRemoteSessionDescription(This,pbstrContentType,pbstrSessionDescription)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionStateChangeEvent2_get_MediaTypes_Proxy( 
    IRTCSessionStateChangeEvent2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pMediaTypes);


void __RPC_STUB IRTCSessionStateChangeEvent2_get_MediaTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionStateChangeEvent2_get_RemotePreferredSecurityLevel_Proxy( 
    IRTCSessionStateChangeEvent2 __RPC_FAR * This,
    /* [in] */ RTC_SECURITY_TYPE enSecurityType,
    /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel);


void __RPC_STUB IRTCSessionStateChangeEvent2_get_RemotePreferredSecurityLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionStateChangeEvent2_get_IsForked_Proxy( 
    IRTCSessionStateChangeEvent2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsForked);


void __RPC_STUB IRTCSessionStateChangeEvent2_get_IsForked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCSessionStateChangeEvent2_GetRemoteSessionDescription_Proxy( 
    IRTCSessionStateChangeEvent2 __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrContentType,
    /* [out] */ BSTR __RPC_FAR *pbstrSessionDescription);


void __RPC_STUB IRTCSessionStateChangeEvent2_GetRemoteSessionDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCSessionStateChangeEvent2_INTERFACE_DEFINED__ */


#ifndef __IRTCSessionOperationCompleteEvent_INTERFACE_DEFINED__
#define __IRTCSessionOperationCompleteEvent_INTERFACE_DEFINED__

/* interface IRTCSessionOperationCompleteEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCSessionOperationCompleteEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a6bff4c0-f7c8-4d3c-9a41-3550f78a95b0")
    IRTCSessionOperationCompleteEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cookie( 
            /* [retval][out] */ LONG_PTR __RPC_FAR *plCookie) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCSessionOperationCompleteEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCSessionOperationCompleteEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCSessionOperationCompleteEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCSessionOperationCompleteEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCSessionOperationCompleteEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCSessionOperationCompleteEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCSessionOperationCompleteEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCSessionOperationCompleteEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IRTCSessionOperationCompleteEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cookie )( 
            IRTCSessionOperationCompleteEvent __RPC_FAR * This,
            /* [retval][out] */ LONG_PTR __RPC_FAR *plCookie);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCSessionOperationCompleteEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IRTCSessionOperationCompleteEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);
        
        END_INTERFACE
    } IRTCSessionOperationCompleteEventVtbl;

    interface IRTCSessionOperationCompleteEvent
    {
        CONST_VTBL struct IRTCSessionOperationCompleteEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCSessionOperationCompleteEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCSessionOperationCompleteEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCSessionOperationCompleteEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCSessionOperationCompleteEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCSessionOperationCompleteEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCSessionOperationCompleteEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCSessionOperationCompleteEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCSessionOperationCompleteEvent_get_Session(This,ppSession)	\
    (This)->lpVtbl -> get_Session(This,ppSession)

#define IRTCSessionOperationCompleteEvent_get_Cookie(This,plCookie)	\
    (This)->lpVtbl -> get_Cookie(This,plCookie)

#define IRTCSessionOperationCompleteEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCSessionOperationCompleteEvent_get_StatusText(This,pbstrStatusText)	\
    (This)->lpVtbl -> get_StatusText(This,pbstrStatusText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionOperationCompleteEvent_get_Session_Proxy( 
    IRTCSessionOperationCompleteEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);


void __RPC_STUB IRTCSessionOperationCompleteEvent_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionOperationCompleteEvent_get_Cookie_Proxy( 
    IRTCSessionOperationCompleteEvent __RPC_FAR * This,
    /* [retval][out] */ LONG_PTR __RPC_FAR *plCookie);


void __RPC_STUB IRTCSessionOperationCompleteEvent_get_Cookie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionOperationCompleteEvent_get_StatusCode_Proxy( 
    IRTCSessionOperationCompleteEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCSessionOperationCompleteEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionOperationCompleteEvent_get_StatusText_Proxy( 
    IRTCSessionOperationCompleteEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);


void __RPC_STUB IRTCSessionOperationCompleteEvent_get_StatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCSessionOperationCompleteEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCSessionOperationCompleteEvent2_INTERFACE_DEFINED__
#define __IRTCSessionOperationCompleteEvent2_INTERFACE_DEFINED__

/* interface IRTCSessionOperationCompleteEvent2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCSessionOperationCompleteEvent2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f6fc2a9b-d5bc-4241-b436-1b8460c13832")
    IRTCSessionOperationCompleteEvent2 : public IRTCSessionOperationCompleteEvent
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Participant( 
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRemoteSessionDescription( 
            /* [out] */ BSTR __RPC_FAR *pbstrContentType,
            /* [out] */ BSTR __RPC_FAR *pbstrSessionDescription) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCSessionOperationCompleteEvent2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cookie )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
            /* [retval][out] */ LONG_PTR __RPC_FAR *plCookie);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Participant )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRemoteSessionDescription )( 
            IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrContentType,
            /* [out] */ BSTR __RPC_FAR *pbstrSessionDescription);
        
        END_INTERFACE
    } IRTCSessionOperationCompleteEvent2Vtbl;

    interface IRTCSessionOperationCompleteEvent2
    {
        CONST_VTBL struct IRTCSessionOperationCompleteEvent2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCSessionOperationCompleteEvent2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCSessionOperationCompleteEvent2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCSessionOperationCompleteEvent2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCSessionOperationCompleteEvent2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCSessionOperationCompleteEvent2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCSessionOperationCompleteEvent2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCSessionOperationCompleteEvent2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCSessionOperationCompleteEvent2_get_Session(This,ppSession)	\
    (This)->lpVtbl -> get_Session(This,ppSession)

#define IRTCSessionOperationCompleteEvent2_get_Cookie(This,plCookie)	\
    (This)->lpVtbl -> get_Cookie(This,plCookie)

#define IRTCSessionOperationCompleteEvent2_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCSessionOperationCompleteEvent2_get_StatusText(This,pbstrStatusText)	\
    (This)->lpVtbl -> get_StatusText(This,pbstrStatusText)


#define IRTCSessionOperationCompleteEvent2_get_Participant(This,ppParticipant)	\
    (This)->lpVtbl -> get_Participant(This,ppParticipant)

#define IRTCSessionOperationCompleteEvent2_GetRemoteSessionDescription(This,pbstrContentType,pbstrSessionDescription)	\
    (This)->lpVtbl -> GetRemoteSessionDescription(This,pbstrContentType,pbstrSessionDescription)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionOperationCompleteEvent2_get_Participant_Proxy( 
    IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
    /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant);


void __RPC_STUB IRTCSessionOperationCompleteEvent2_get_Participant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCSessionOperationCompleteEvent2_GetRemoteSessionDescription_Proxy( 
    IRTCSessionOperationCompleteEvent2 __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrContentType,
    /* [out] */ BSTR __RPC_FAR *pbstrSessionDescription);


void __RPC_STUB IRTCSessionOperationCompleteEvent2_GetRemoteSessionDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCSessionOperationCompleteEvent2_INTERFACE_DEFINED__ */


#ifndef __IRTCParticipantStateChangeEvent_INTERFACE_DEFINED__
#define __IRTCParticipantStateChangeEvent_INTERFACE_DEFINED__

/* interface IRTCParticipantStateChangeEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCParticipantStateChangeEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("09bcb597-f0fa-48f9-b420-468cea7fde04")
    IRTCParticipantStateChangeEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Participant( 
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ RTC_PARTICIPANT_STATE __RPC_FAR *penState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCParticipantStateChangeEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCParticipantStateChangeEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCParticipantStateChangeEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCParticipantStateChangeEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCParticipantStateChangeEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCParticipantStateChangeEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCParticipantStateChangeEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCParticipantStateChangeEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Participant )( 
            IRTCParticipantStateChangeEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCParticipantStateChangeEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_PARTICIPANT_STATE __RPC_FAR *penState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCParticipantStateChangeEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        END_INTERFACE
    } IRTCParticipantStateChangeEventVtbl;

    interface IRTCParticipantStateChangeEvent
    {
        CONST_VTBL struct IRTCParticipantStateChangeEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCParticipantStateChangeEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCParticipantStateChangeEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCParticipantStateChangeEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCParticipantStateChangeEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCParticipantStateChangeEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCParticipantStateChangeEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCParticipantStateChangeEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCParticipantStateChangeEvent_get_Participant(This,ppParticipant)	\
    (This)->lpVtbl -> get_Participant(This,ppParticipant)

#define IRTCParticipantStateChangeEvent_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#define IRTCParticipantStateChangeEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCParticipantStateChangeEvent_get_Participant_Proxy( 
    IRTCParticipantStateChangeEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant);


void __RPC_STUB IRTCParticipantStateChangeEvent_get_Participant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCParticipantStateChangeEvent_get_State_Proxy( 
    IRTCParticipantStateChangeEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_PARTICIPANT_STATE __RPC_FAR *penState);


void __RPC_STUB IRTCParticipantStateChangeEvent_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCParticipantStateChangeEvent_get_StatusCode_Proxy( 
    IRTCParticipantStateChangeEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCParticipantStateChangeEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCParticipantStateChangeEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCMediaEvent_INTERFACE_DEFINED__
#define __IRTCMediaEvent_INTERFACE_DEFINED__

/* interface IRTCMediaEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCMediaEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("099944fb-bcda-453e-8c41-e13da2adf7f3")
    IRTCMediaEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaType( 
            /* [retval][out] */ long __RPC_FAR *pMediaType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EventType( 
            /* [retval][out] */ RTC_MEDIA_EVENT_TYPE __RPC_FAR *penEventType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EventReason( 
            /* [retval][out] */ RTC_MEDIA_EVENT_REASON __RPC_FAR *penEventReason) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCMediaEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCMediaEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCMediaEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCMediaEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCMediaEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCMediaEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCMediaEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCMediaEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaType )( 
            IRTCMediaEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pMediaType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventType )( 
            IRTCMediaEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_MEDIA_EVENT_TYPE __RPC_FAR *penEventType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventReason )( 
            IRTCMediaEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_MEDIA_EVENT_REASON __RPC_FAR *penEventReason);
        
        END_INTERFACE
    } IRTCMediaEventVtbl;

    interface IRTCMediaEvent
    {
        CONST_VTBL struct IRTCMediaEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCMediaEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCMediaEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCMediaEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCMediaEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCMediaEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCMediaEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCMediaEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCMediaEvent_get_MediaType(This,pMediaType)	\
    (This)->lpVtbl -> get_MediaType(This,pMediaType)

#define IRTCMediaEvent_get_EventType(This,penEventType)	\
    (This)->lpVtbl -> get_EventType(This,penEventType)

#define IRTCMediaEvent_get_EventReason(This,penEventReason)	\
    (This)->lpVtbl -> get_EventReason(This,penEventReason)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMediaEvent_get_MediaType_Proxy( 
    IRTCMediaEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pMediaType);


void __RPC_STUB IRTCMediaEvent_get_MediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMediaEvent_get_EventType_Proxy( 
    IRTCMediaEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_MEDIA_EVENT_TYPE __RPC_FAR *penEventType);


void __RPC_STUB IRTCMediaEvent_get_EventType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMediaEvent_get_EventReason_Proxy( 
    IRTCMediaEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_MEDIA_EVENT_REASON __RPC_FAR *penEventReason);


void __RPC_STUB IRTCMediaEvent_get_EventReason_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCMediaEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCIntensityEvent_INTERFACE_DEFINED__
#define __IRTCIntensityEvent_INTERFACE_DEFINED__

/* interface IRTCIntensityEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCIntensityEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4c23bf51-390c-4992-a41d-41eec05b2a4b")
    IRTCIntensityEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Level( 
            /* [retval][out] */ long __RPC_FAR *plLevel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Min( 
            /* [retval][out] */ long __RPC_FAR *plMin) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Max( 
            /* [retval][out] */ long __RPC_FAR *plMax) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Direction( 
            /* [retval][out] */ RTC_AUDIO_DEVICE __RPC_FAR *penDirection) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCIntensityEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCIntensityEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCIntensityEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCIntensityEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCIntensityEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCIntensityEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCIntensityEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCIntensityEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Level )( 
            IRTCIntensityEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Min )( 
            IRTCIntensityEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Max )( 
            IRTCIntensityEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMax);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Direction )( 
            IRTCIntensityEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_AUDIO_DEVICE __RPC_FAR *penDirection);
        
        END_INTERFACE
    } IRTCIntensityEventVtbl;

    interface IRTCIntensityEvent
    {
        CONST_VTBL struct IRTCIntensityEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCIntensityEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCIntensityEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCIntensityEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCIntensityEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCIntensityEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCIntensityEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCIntensityEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCIntensityEvent_get_Level(This,plLevel)	\
    (This)->lpVtbl -> get_Level(This,plLevel)

#define IRTCIntensityEvent_get_Min(This,plMin)	\
    (This)->lpVtbl -> get_Min(This,plMin)

#define IRTCIntensityEvent_get_Max(This,plMax)	\
    (This)->lpVtbl -> get_Max(This,plMax)

#define IRTCIntensityEvent_get_Direction(This,penDirection)	\
    (This)->lpVtbl -> get_Direction(This,penDirection)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCIntensityEvent_get_Level_Proxy( 
    IRTCIntensityEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plLevel);


void __RPC_STUB IRTCIntensityEvent_get_Level_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCIntensityEvent_get_Min_Proxy( 
    IRTCIntensityEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMin);


void __RPC_STUB IRTCIntensityEvent_get_Min_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCIntensityEvent_get_Max_Proxy( 
    IRTCIntensityEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMax);


void __RPC_STUB IRTCIntensityEvent_get_Max_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCIntensityEvent_get_Direction_Proxy( 
    IRTCIntensityEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_AUDIO_DEVICE __RPC_FAR *penDirection);


void __RPC_STUB IRTCIntensityEvent_get_Direction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCIntensityEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCMessagingEvent_INTERFACE_DEFINED__
#define __IRTCMessagingEvent_INTERFACE_DEFINED__

/* interface IRTCMessagingEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCMessagingEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d3609541-1b29-4de5-a4ad-5aebaf319512")
    IRTCMessagingEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Participant( 
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EventType( 
            /* [retval][out] */ RTC_MESSAGING_EVENT_TYPE __RPC_FAR *penEventType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Message( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrMessage) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MessageHeader( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrMessageHeader) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserStatus( 
            /* [retval][out] */ RTC_MESSAGING_USER_STATUS __RPC_FAR *penUserStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCMessagingEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCMessagingEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCMessagingEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCMessagingEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCMessagingEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCMessagingEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCMessagingEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCMessagingEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IRTCMessagingEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Participant )( 
            IRTCMessagingEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventType )( 
            IRTCMessagingEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_MESSAGING_EVENT_TYPE __RPC_FAR *penEventType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Message )( 
            IRTCMessagingEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrMessage);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MessageHeader )( 
            IRTCMessagingEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrMessageHeader);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserStatus )( 
            IRTCMessagingEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_MESSAGING_USER_STATUS __RPC_FAR *penUserStatus);
        
        END_INTERFACE
    } IRTCMessagingEventVtbl;

    interface IRTCMessagingEvent
    {
        CONST_VTBL struct IRTCMessagingEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCMessagingEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCMessagingEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCMessagingEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCMessagingEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCMessagingEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCMessagingEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCMessagingEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCMessagingEvent_get_Session(This,ppSession)	\
    (This)->lpVtbl -> get_Session(This,ppSession)

#define IRTCMessagingEvent_get_Participant(This,ppParticipant)	\
    (This)->lpVtbl -> get_Participant(This,ppParticipant)

#define IRTCMessagingEvent_get_EventType(This,penEventType)	\
    (This)->lpVtbl -> get_EventType(This,penEventType)

#define IRTCMessagingEvent_get_Message(This,pbstrMessage)	\
    (This)->lpVtbl -> get_Message(This,pbstrMessage)

#define IRTCMessagingEvent_get_MessageHeader(This,pbstrMessageHeader)	\
    (This)->lpVtbl -> get_MessageHeader(This,pbstrMessageHeader)

#define IRTCMessagingEvent_get_UserStatus(This,penUserStatus)	\
    (This)->lpVtbl -> get_UserStatus(This,penUserStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMessagingEvent_get_Session_Proxy( 
    IRTCMessagingEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *ppSession);


void __RPC_STUB IRTCMessagingEvent_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMessagingEvent_get_Participant_Proxy( 
    IRTCMessagingEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant);


void __RPC_STUB IRTCMessagingEvent_get_Participant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMessagingEvent_get_EventType_Proxy( 
    IRTCMessagingEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_MESSAGING_EVENT_TYPE __RPC_FAR *penEventType);


void __RPC_STUB IRTCMessagingEvent_get_EventType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMessagingEvent_get_Message_Proxy( 
    IRTCMessagingEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrMessage);


void __RPC_STUB IRTCMessagingEvent_get_Message_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMessagingEvent_get_MessageHeader_Proxy( 
    IRTCMessagingEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrMessageHeader);


void __RPC_STUB IRTCMessagingEvent_get_MessageHeader_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMessagingEvent_get_UserStatus_Proxy( 
    IRTCMessagingEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_MESSAGING_USER_STATUS __RPC_FAR *penUserStatus);


void __RPC_STUB IRTCMessagingEvent_get_UserStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCMessagingEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCBuddyEvent_INTERFACE_DEFINED__
#define __IRTCBuddyEvent_INTERFACE_DEFINED__

/* interface IRTCBuddyEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCBuddyEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f36d755d-17e6-404e-954f-0fc07574c78d")
    IRTCBuddyEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Buddy( 
            /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCBuddyEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCBuddyEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCBuddyEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCBuddyEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCBuddyEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCBuddyEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCBuddyEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCBuddyEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Buddy )( 
            IRTCBuddyEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy);
        
        END_INTERFACE
    } IRTCBuddyEventVtbl;

    interface IRTCBuddyEvent
    {
        CONST_VTBL struct IRTCBuddyEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCBuddyEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCBuddyEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCBuddyEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCBuddyEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCBuddyEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCBuddyEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCBuddyEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCBuddyEvent_get_Buddy(This,ppBuddy)	\
    (This)->lpVtbl -> get_Buddy(This,ppBuddy)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyEvent_get_Buddy_Proxy( 
    IRTCBuddyEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy);


void __RPC_STUB IRTCBuddyEvent_get_Buddy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCBuddyEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCBuddyEvent2_INTERFACE_DEFINED__
#define __IRTCBuddyEvent2_INTERFACE_DEFINED__

/* interface IRTCBuddyEvent2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCBuddyEvent2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("484A7F1E-73F0-4990-BFC2-60BC3978A720")
    IRTCBuddyEvent2 : public IRTCBuddyEvent
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EventType( 
            /* [retval][out] */ RTC_BUDDY_EVENT_TYPE __RPC_FAR *pEventType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCBuddyEvent2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCBuddyEvent2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCBuddyEvent2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCBuddyEvent2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCBuddyEvent2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCBuddyEvent2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCBuddyEvent2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCBuddyEvent2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Buddy )( 
            IRTCBuddyEvent2 __RPC_FAR * This,
            /* [retval][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppBuddy);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventType )( 
            IRTCBuddyEvent2 __RPC_FAR * This,
            /* [retval][out] */ RTC_BUDDY_EVENT_TYPE __RPC_FAR *pEventType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCBuddyEvent2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IRTCBuddyEvent2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);
        
        END_INTERFACE
    } IRTCBuddyEvent2Vtbl;

    interface IRTCBuddyEvent2
    {
        CONST_VTBL struct IRTCBuddyEvent2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCBuddyEvent2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCBuddyEvent2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCBuddyEvent2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCBuddyEvent2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCBuddyEvent2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCBuddyEvent2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCBuddyEvent2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCBuddyEvent2_get_Buddy(This,ppBuddy)	\
    (This)->lpVtbl -> get_Buddy(This,ppBuddy)


#define IRTCBuddyEvent2_get_EventType(This,pEventType)	\
    (This)->lpVtbl -> get_EventType(This,pEventType)

#define IRTCBuddyEvent2_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCBuddyEvent2_get_StatusText(This,pbstrStatusText)	\
    (This)->lpVtbl -> get_StatusText(This,pbstrStatusText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyEvent2_get_EventType_Proxy( 
    IRTCBuddyEvent2 __RPC_FAR * This,
    /* [retval][out] */ RTC_BUDDY_EVENT_TYPE __RPC_FAR *pEventType);


void __RPC_STUB IRTCBuddyEvent2_get_EventType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyEvent2_get_StatusCode_Proxy( 
    IRTCBuddyEvent2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCBuddyEvent2_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyEvent2_get_StatusText_Proxy( 
    IRTCBuddyEvent2 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);


void __RPC_STUB IRTCBuddyEvent2_get_StatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCBuddyEvent2_INTERFACE_DEFINED__ */


#ifndef __IRTCWatcherEvent_INTERFACE_DEFINED__
#define __IRTCWatcherEvent_INTERFACE_DEFINED__

/* interface IRTCWatcherEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCWatcherEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f30d7261-587a-424f-822c-312788f43548")
    IRTCWatcherEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Watcher( 
            /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCWatcherEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCWatcherEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCWatcherEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCWatcherEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCWatcherEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCWatcherEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCWatcherEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCWatcherEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Watcher )( 
            IRTCWatcherEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher);
        
        END_INTERFACE
    } IRTCWatcherEventVtbl;

    interface IRTCWatcherEvent
    {
        CONST_VTBL struct IRTCWatcherEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCWatcherEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCWatcherEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCWatcherEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCWatcherEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCWatcherEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCWatcherEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCWatcherEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCWatcherEvent_get_Watcher(This,ppWatcher)	\
    (This)->lpVtbl -> get_Watcher(This,ppWatcher)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCWatcherEvent_get_Watcher_Proxy( 
    IRTCWatcherEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher);


void __RPC_STUB IRTCWatcherEvent_get_Watcher_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCWatcherEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCWatcherEvent2_INTERFACE_DEFINED__
#define __IRTCWatcherEvent2_INTERFACE_DEFINED__

/* interface IRTCWatcherEvent2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCWatcherEvent2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E52891E8-188C-49AF-B005-98ED13F83F9C")
    IRTCWatcherEvent2 : public IRTCWatcherEvent
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EventType( 
            /* [retval][out] */ RTC_WATCHER_EVENT_TYPE __RPC_FAR *pEventType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCWatcherEvent2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCWatcherEvent2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCWatcherEvent2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCWatcherEvent2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCWatcherEvent2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCWatcherEvent2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCWatcherEvent2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCWatcherEvent2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Watcher )( 
            IRTCWatcherEvent2 __RPC_FAR * This,
            /* [retval][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppWatcher);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventType )( 
            IRTCWatcherEvent2 __RPC_FAR * This,
            /* [retval][out] */ RTC_WATCHER_EVENT_TYPE __RPC_FAR *pEventType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCWatcherEvent2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        END_INTERFACE
    } IRTCWatcherEvent2Vtbl;

    interface IRTCWatcherEvent2
    {
        CONST_VTBL struct IRTCWatcherEvent2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCWatcherEvent2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCWatcherEvent2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCWatcherEvent2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCWatcherEvent2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCWatcherEvent2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCWatcherEvent2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCWatcherEvent2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCWatcherEvent2_get_Watcher(This,ppWatcher)	\
    (This)->lpVtbl -> get_Watcher(This,ppWatcher)


#define IRTCWatcherEvent2_get_EventType(This,pEventType)	\
    (This)->lpVtbl -> get_EventType(This,pEventType)

#define IRTCWatcherEvent2_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCWatcherEvent2_get_EventType_Proxy( 
    IRTCWatcherEvent2 __RPC_FAR * This,
    /* [retval][out] */ RTC_WATCHER_EVENT_TYPE __RPC_FAR *pEventType);


void __RPC_STUB IRTCWatcherEvent2_get_EventType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCWatcherEvent2_get_StatusCode_Proxy( 
    IRTCWatcherEvent2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCWatcherEvent2_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCWatcherEvent2_INTERFACE_DEFINED__ */


#ifndef __IRTCBuddyGroupEvent_INTERFACE_DEFINED__
#define __IRTCBuddyGroupEvent_INTERFACE_DEFINED__

/* interface IRTCBuddyGroupEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCBuddyGroupEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3A79E1D1-B736-4414-96F8-BBC7F08863E4")
    IRTCBuddyGroupEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EventType( 
            /* [retval][out] */ RTC_GROUP_EVENT_TYPE __RPC_FAR *pEventType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppGroup) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Buddy( 
            /* [retval][out] */ IRTCBuddy2 __RPC_FAR *__RPC_FAR *ppBuddy) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCBuddyGroupEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCBuddyGroupEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCBuddyGroupEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCBuddyGroupEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCBuddyGroupEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCBuddyGroupEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCBuddyGroupEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCBuddyGroupEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventType )( 
            IRTCBuddyGroupEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_GROUP_EVENT_TYPE __RPC_FAR *pEventType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            IRTCBuddyGroupEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppGroup);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Buddy )( 
            IRTCBuddyGroupEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCBuddy2 __RPC_FAR *__RPC_FAR *ppBuddy);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCBuddyGroupEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        END_INTERFACE
    } IRTCBuddyGroupEventVtbl;

    interface IRTCBuddyGroupEvent
    {
        CONST_VTBL struct IRTCBuddyGroupEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCBuddyGroupEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCBuddyGroupEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCBuddyGroupEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCBuddyGroupEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCBuddyGroupEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCBuddyGroupEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCBuddyGroupEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCBuddyGroupEvent_get_EventType(This,pEventType)	\
    (This)->lpVtbl -> get_EventType(This,pEventType)

#define IRTCBuddyGroupEvent_get_Group(This,ppGroup)	\
    (This)->lpVtbl -> get_Group(This,ppGroup)

#define IRTCBuddyGroupEvent_get_Buddy(This,ppBuddy)	\
    (This)->lpVtbl -> get_Buddy(This,ppBuddy)

#define IRTCBuddyGroupEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroupEvent_get_EventType_Proxy( 
    IRTCBuddyGroupEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_GROUP_EVENT_TYPE __RPC_FAR *pEventType);


void __RPC_STUB IRTCBuddyGroupEvent_get_EventType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroupEvent_get_Group_Proxy( 
    IRTCBuddyGroupEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppGroup);


void __RPC_STUB IRTCBuddyGroupEvent_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroupEvent_get_Buddy_Proxy( 
    IRTCBuddyGroupEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCBuddy2 __RPC_FAR *__RPC_FAR *ppBuddy);


void __RPC_STUB IRTCBuddyGroupEvent_get_Buddy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroupEvent_get_StatusCode_Proxy( 
    IRTCBuddyGroupEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCBuddyGroupEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCBuddyGroupEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCInfoEvent_INTERFACE_DEFINED__
#define __IRTCInfoEvent_INTERFACE_DEFINED__

/* interface IRTCInfoEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCInfoEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E1D68AE-1912-4f49-B2C3-594FADFD425F")
    IRTCInfoEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Participant( 
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Info( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInfo) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InfoHeader( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInfoHeader) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCInfoEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCInfoEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCInfoEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCInfoEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCInfoEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCInfoEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCInfoEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCInfoEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IRTCInfoEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Participant )( 
            IRTCInfoEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Info )( 
            IRTCInfoEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InfoHeader )( 
            IRTCInfoEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInfoHeader);
        
        END_INTERFACE
    } IRTCInfoEventVtbl;

    interface IRTCInfoEvent
    {
        CONST_VTBL struct IRTCInfoEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCInfoEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCInfoEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCInfoEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCInfoEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCInfoEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCInfoEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCInfoEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCInfoEvent_get_Session(This,ppSession)	\
    (This)->lpVtbl -> get_Session(This,ppSession)

#define IRTCInfoEvent_get_Participant(This,ppParticipant)	\
    (This)->lpVtbl -> get_Participant(This,ppParticipant)

#define IRTCInfoEvent_get_Info(This,pbstrInfo)	\
    (This)->lpVtbl -> get_Info(This,pbstrInfo)

#define IRTCInfoEvent_get_InfoHeader(This,pbstrInfoHeader)	\
    (This)->lpVtbl -> get_InfoHeader(This,pbstrInfoHeader)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCInfoEvent_get_Session_Proxy( 
    IRTCInfoEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession);


void __RPC_STUB IRTCInfoEvent_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCInfoEvent_get_Participant_Proxy( 
    IRTCInfoEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppParticipant);


void __RPC_STUB IRTCInfoEvent_get_Participant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCInfoEvent_get_Info_Proxy( 
    IRTCInfoEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrInfo);


void __RPC_STUB IRTCInfoEvent_get_Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCInfoEvent_get_InfoHeader_Proxy( 
    IRTCInfoEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrInfoHeader);


void __RPC_STUB IRTCInfoEvent_get_InfoHeader_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCInfoEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCMediaRequestEvent_INTERFACE_DEFINED__
#define __IRTCMediaRequestEvent_INTERFACE_DEFINED__

/* interface IRTCMediaRequestEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCMediaRequestEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("52572D15-148C-4d97-A36C-2DA55C289D63")
    IRTCMediaRequestEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProposedMedia( 
            /* [retval][out] */ long __RPC_FAR *plMediaTypes) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentMedia( 
            /* [retval][out] */ long __RPC_FAR *plMediaTypes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Accept( 
            /* [in] */ long lMediaTypes) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemotePreferredSecurityLevel( 
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reject( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ RTC_REINVITE_STATE __RPC_FAR *pState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCMediaRequestEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCMediaRequestEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCMediaRequestEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCMediaRequestEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCMediaRequestEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCMediaRequestEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCMediaRequestEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCMediaRequestEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IRTCMediaRequestEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProposedMedia )( 
            IRTCMediaRequestEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMediaTypes);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentMedia )( 
            IRTCMediaRequestEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMediaTypes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Accept )( 
            IRTCMediaRequestEvent __RPC_FAR * This,
            /* [in] */ long lMediaTypes);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemotePreferredSecurityLevel )( 
            IRTCMediaRequestEvent __RPC_FAR * This,
            /* [in] */ RTC_SECURITY_TYPE enSecurityType,
            /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reject )( 
            IRTCMediaRequestEvent __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCMediaRequestEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_REINVITE_STATE __RPC_FAR *pState);
        
        END_INTERFACE
    } IRTCMediaRequestEventVtbl;

    interface IRTCMediaRequestEvent
    {
        CONST_VTBL struct IRTCMediaRequestEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCMediaRequestEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCMediaRequestEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCMediaRequestEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCMediaRequestEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCMediaRequestEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCMediaRequestEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCMediaRequestEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCMediaRequestEvent_get_Session(This,ppSession)	\
    (This)->lpVtbl -> get_Session(This,ppSession)

#define IRTCMediaRequestEvent_get_ProposedMedia(This,plMediaTypes)	\
    (This)->lpVtbl -> get_ProposedMedia(This,plMediaTypes)

#define IRTCMediaRequestEvent_get_CurrentMedia(This,plMediaTypes)	\
    (This)->lpVtbl -> get_CurrentMedia(This,plMediaTypes)

#define IRTCMediaRequestEvent_Accept(This,lMediaTypes)	\
    (This)->lpVtbl -> Accept(This,lMediaTypes)

#define IRTCMediaRequestEvent_get_RemotePreferredSecurityLevel(This,enSecurityType,penSecurityLevel)	\
    (This)->lpVtbl -> get_RemotePreferredSecurityLevel(This,enSecurityType,penSecurityLevel)

#define IRTCMediaRequestEvent_Reject(This)	\
    (This)->lpVtbl -> Reject(This)

#define IRTCMediaRequestEvent_get_State(This,pState)	\
    (This)->lpVtbl -> get_State(This,pState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMediaRequestEvent_get_Session_Proxy( 
    IRTCMediaRequestEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession);


void __RPC_STUB IRTCMediaRequestEvent_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMediaRequestEvent_get_ProposedMedia_Proxy( 
    IRTCMediaRequestEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMediaTypes);


void __RPC_STUB IRTCMediaRequestEvent_get_ProposedMedia_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMediaRequestEvent_get_CurrentMedia_Proxy( 
    IRTCMediaRequestEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMediaTypes);


void __RPC_STUB IRTCMediaRequestEvent_get_CurrentMedia_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCMediaRequestEvent_Accept_Proxy( 
    IRTCMediaRequestEvent __RPC_FAR * This,
    /* [in] */ long lMediaTypes);


void __RPC_STUB IRTCMediaRequestEvent_Accept_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMediaRequestEvent_get_RemotePreferredSecurityLevel_Proxy( 
    IRTCMediaRequestEvent __RPC_FAR * This,
    /* [in] */ RTC_SECURITY_TYPE enSecurityType,
    /* [retval][out] */ RTC_SECURITY_LEVEL __RPC_FAR *penSecurityLevel);


void __RPC_STUB IRTCMediaRequestEvent_get_RemotePreferredSecurityLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCMediaRequestEvent_Reject_Proxy( 
    IRTCMediaRequestEvent __RPC_FAR * This);


void __RPC_STUB IRTCMediaRequestEvent_Reject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCMediaRequestEvent_get_State_Proxy( 
    IRTCMediaRequestEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_REINVITE_STATE __RPC_FAR *pState);


void __RPC_STUB IRTCMediaRequestEvent_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCMediaRequestEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCReInviteEvent_INTERFACE_DEFINED__
#define __IRTCReInviteEvent_INTERFACE_DEFINED__

/* interface IRTCReInviteEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCReInviteEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11558D84-204C-43e7-99B0-2034E9417F7D")
    IRTCReInviteEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession2) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Accept( 
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reject( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ RTC_REINVITE_STATE __RPC_FAR *pState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRemoteSessionDescription( 
            /* [out] */ BSTR __RPC_FAR *pbstrContentType,
            /* [out] */ BSTR __RPC_FAR *pbstrSessionDescription) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCReInviteEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCReInviteEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCReInviteEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCReInviteEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCReInviteEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCReInviteEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCReInviteEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCReInviteEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IRTCReInviteEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession2);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Accept )( 
            IRTCReInviteEvent __RPC_FAR * This,
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reject )( 
            IRTCReInviteEvent __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCReInviteEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_REINVITE_STATE __RPC_FAR *pState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRemoteSessionDescription )( 
            IRTCReInviteEvent __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrContentType,
            /* [out] */ BSTR __RPC_FAR *pbstrSessionDescription);
        
        END_INTERFACE
    } IRTCReInviteEventVtbl;

    interface IRTCReInviteEvent
    {
        CONST_VTBL struct IRTCReInviteEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCReInviteEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCReInviteEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCReInviteEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCReInviteEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCReInviteEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCReInviteEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCReInviteEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCReInviteEvent_get_Session(This,ppSession2)	\
    (This)->lpVtbl -> get_Session(This,ppSession2)

#define IRTCReInviteEvent_Accept(This,bstrContentType,bstrSessionDescription)	\
    (This)->lpVtbl -> Accept(This,bstrContentType,bstrSessionDescription)

#define IRTCReInviteEvent_Reject(This)	\
    (This)->lpVtbl -> Reject(This)

#define IRTCReInviteEvent_get_State(This,pState)	\
    (This)->lpVtbl -> get_State(This,pState)

#define IRTCReInviteEvent_GetRemoteSessionDescription(This,pbstrContentType,pbstrSessionDescription)	\
    (This)->lpVtbl -> GetRemoteSessionDescription(This,pbstrContentType,pbstrSessionDescription)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCReInviteEvent_get_Session_Proxy( 
    IRTCReInviteEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession2);


void __RPC_STUB IRTCReInviteEvent_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCReInviteEvent_Accept_Proxy( 
    IRTCReInviteEvent __RPC_FAR * This,
    /* [in] */ BSTR bstrContentType,
    /* [in] */ BSTR bstrSessionDescription);


void __RPC_STUB IRTCReInviteEvent_Accept_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCReInviteEvent_Reject_Proxy( 
    IRTCReInviteEvent __RPC_FAR * This);


void __RPC_STUB IRTCReInviteEvent_Reject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCReInviteEvent_get_State_Proxy( 
    IRTCReInviteEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_REINVITE_STATE __RPC_FAR *pState);


void __RPC_STUB IRTCReInviteEvent_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCReInviteEvent_GetRemoteSessionDescription_Proxy( 
    IRTCReInviteEvent __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrContentType,
    /* [out] */ BSTR __RPC_FAR *pbstrSessionDescription);


void __RPC_STUB IRTCReInviteEvent_GetRemoteSessionDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCReInviteEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCPresencePropertyEvent_INTERFACE_DEFINED__
#define __IRTCPresencePropertyEvent_INTERFACE_DEFINED__

/* interface IRTCPresencePropertyEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCPresencePropertyEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F777F570-A820-49d5-86BD-E099493F1518")
    IRTCPresencePropertyEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PresenceProperty( 
            /* [retval][out] */ RTC_PRESENCE_PROPERTY __RPC_FAR *penPresProp) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCPresencePropertyEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCPresencePropertyEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCPresencePropertyEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCPresencePropertyEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCPresencePropertyEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCPresencePropertyEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCPresencePropertyEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCPresencePropertyEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCPresencePropertyEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IRTCPresencePropertyEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PresenceProperty )( 
            IRTCPresencePropertyEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_PRESENCE_PROPERTY __RPC_FAR *penPresProp);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IRTCPresencePropertyEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        END_INTERFACE
    } IRTCPresencePropertyEventVtbl;

    interface IRTCPresencePropertyEvent
    {
        CONST_VTBL struct IRTCPresencePropertyEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCPresencePropertyEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCPresencePropertyEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCPresencePropertyEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCPresencePropertyEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCPresencePropertyEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCPresencePropertyEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCPresencePropertyEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCPresencePropertyEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCPresencePropertyEvent_get_StatusText(This,pbstrStatusText)	\
    (This)->lpVtbl -> get_StatusText(This,pbstrStatusText)

#define IRTCPresencePropertyEvent_get_PresenceProperty(This,penPresProp)	\
    (This)->lpVtbl -> get_PresenceProperty(This,penPresProp)

#define IRTCPresencePropertyEvent_get_Value(This,pbstrValue)	\
    (This)->lpVtbl -> get_Value(This,pbstrValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresencePropertyEvent_get_StatusCode_Proxy( 
    IRTCPresencePropertyEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCPresencePropertyEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresencePropertyEvent_get_StatusText_Proxy( 
    IRTCPresencePropertyEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);


void __RPC_STUB IRTCPresencePropertyEvent_get_StatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresencePropertyEvent_get_PresenceProperty_Proxy( 
    IRTCPresencePropertyEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_PRESENCE_PROPERTY __RPC_FAR *penPresProp);


void __RPC_STUB IRTCPresencePropertyEvent_get_PresenceProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresencePropertyEvent_get_Value_Proxy( 
    IRTCPresencePropertyEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);


void __RPC_STUB IRTCPresencePropertyEvent_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCPresencePropertyEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCPresenceDataEvent_INTERFACE_DEFINED__
#define __IRTCPresenceDataEvent_INTERFACE_DEFINED__

/* interface IRTCPresenceDataEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCPresenceDataEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("38F0E78C-8B87-4c04-A82D-AEDD83C909BB")
    IRTCPresenceDataEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPresenceData( 
            /* [out] */ BSTR __RPC_FAR *pbstrNamespace,
            /* [out] */ BSTR __RPC_FAR *pbstrData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCPresenceDataEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCPresenceDataEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCPresenceDataEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCPresenceDataEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCPresenceDataEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCPresenceDataEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCPresenceDataEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCPresenceDataEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCPresenceDataEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IRTCPresenceDataEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPresenceData )( 
            IRTCPresenceDataEvent __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrNamespace,
            /* [out] */ BSTR __RPC_FAR *pbstrData);
        
        END_INTERFACE
    } IRTCPresenceDataEventVtbl;

    interface IRTCPresenceDataEvent
    {
        CONST_VTBL struct IRTCPresenceDataEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCPresenceDataEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCPresenceDataEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCPresenceDataEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCPresenceDataEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCPresenceDataEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCPresenceDataEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCPresenceDataEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCPresenceDataEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCPresenceDataEvent_get_StatusText(This,pbstrStatusText)	\
    (This)->lpVtbl -> get_StatusText(This,pbstrStatusText)

#define IRTCPresenceDataEvent_GetPresenceData(This,pbstrNamespace,pbstrData)	\
    (This)->lpVtbl -> GetPresenceData(This,pbstrNamespace,pbstrData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresenceDataEvent_get_StatusCode_Proxy( 
    IRTCPresenceDataEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCPresenceDataEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresenceDataEvent_get_StatusText_Proxy( 
    IRTCPresenceDataEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);


void __RPC_STUB IRTCPresenceDataEvent_get_StatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCPresenceDataEvent_GetPresenceData_Proxy( 
    IRTCPresenceDataEvent __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrNamespace,
    /* [out] */ BSTR __RPC_FAR *pbstrData);


void __RPC_STUB IRTCPresenceDataEvent_GetPresenceData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCPresenceDataEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCPresenceStatusEvent_INTERFACE_DEFINED__
#define __IRTCPresenceStatusEvent_INTERFACE_DEFINED__

/* interface IRTCPresenceStatusEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCPresenceStatusEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("78673F32-4A0F-462c-89AA-EE7706707678")
    IRTCPresenceStatusEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLocalPresenceInfo( 
            /* [out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus,
            /* [out] */ BSTR __RPC_FAR *pbstrNotes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCPresenceStatusEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCPresenceStatusEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCPresenceStatusEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCPresenceStatusEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCPresenceStatusEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCPresenceStatusEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCPresenceStatusEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCPresenceStatusEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCPresenceStatusEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IRTCPresenceStatusEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLocalPresenceInfo )( 
            IRTCPresenceStatusEvent __RPC_FAR * This,
            /* [out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus,
            /* [out] */ BSTR __RPC_FAR *pbstrNotes);
        
        END_INTERFACE
    } IRTCPresenceStatusEventVtbl;

    interface IRTCPresenceStatusEvent
    {
        CONST_VTBL struct IRTCPresenceStatusEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCPresenceStatusEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCPresenceStatusEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCPresenceStatusEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCPresenceStatusEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCPresenceStatusEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCPresenceStatusEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCPresenceStatusEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCPresenceStatusEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCPresenceStatusEvent_get_StatusText(This,pbstrStatusText)	\
    (This)->lpVtbl -> get_StatusText(This,pbstrStatusText)

#define IRTCPresenceStatusEvent_GetLocalPresenceInfo(This,penStatus,pbstrNotes)	\
    (This)->lpVtbl -> GetLocalPresenceInfo(This,penStatus,pbstrNotes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresenceStatusEvent_get_StatusCode_Proxy( 
    IRTCPresenceStatusEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCPresenceStatusEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresenceStatusEvent_get_StatusText_Proxy( 
    IRTCPresenceStatusEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);


void __RPC_STUB IRTCPresenceStatusEvent_get_StatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCPresenceStatusEvent_GetLocalPresenceInfo_Proxy( 
    IRTCPresenceStatusEvent __RPC_FAR * This,
    /* [out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus,
    /* [out] */ BSTR __RPC_FAR *pbstrNotes);


void __RPC_STUB IRTCPresenceStatusEvent_GetLocalPresenceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCPresenceStatusEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCCollection_INTERFACE_DEFINED__
#define __IRTCCollection_INTERFACE_DEFINED__

/* interface IRTCCollection */
/* [dual][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC7C8096-B918-4044-94F1-E4FBA0361D5C")
    IRTCCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *lCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppNewEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IRTCCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *lCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IRTCCollection __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IRTCCollection __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppNewEnum);
        
        END_INTERFACE
    } IRTCCollectionVtbl;

    interface IRTCCollection
    {
        CONST_VTBL struct IRTCCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCCollection_get_Count(This,lCount)	\
    (This)->lpVtbl -> get_Count(This,lCount)

#define IRTCCollection_get_Item(This,Index,pVariant)	\
    (This)->lpVtbl -> get_Item(This,Index,pVariant)

#define IRTCCollection_get__NewEnum(This,ppNewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,ppNewEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCCollection_get_Count_Proxy( 
    IRTCCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *lCount);


void __RPC_STUB IRTCCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCCollection_get_Item_Proxy( 
    IRTCCollection __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB IRTCCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IRTCCollection_get__NewEnum_Proxy( 
    IRTCCollection __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppNewEnum);


void __RPC_STUB IRTCCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCCollection_INTERFACE_DEFINED__ */


#ifndef __IRTCEnumParticipants_INTERFACE_DEFINED__
#define __IRTCEnumParticipants_INTERFACE_DEFINED__

/* interface IRTCEnumParticipants */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_IRTCEnumParticipants;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("fcd56f29-4a4f-41b2-ba5c-f5bccc060bf6")
    IRTCEnumParticipants : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IRTCEnumParticipants __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCEnumParticipantsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCEnumParticipants __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCEnumParticipants __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCEnumParticipants __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IRTCEnumParticipants __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IRTCEnumParticipants __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IRTCEnumParticipants __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IRTCEnumParticipants __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumParticipants __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IRTCEnumParticipantsVtbl;

    interface IRTCEnumParticipants
    {
        CONST_VTBL struct IRTCEnumParticipantsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCEnumParticipants_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCEnumParticipants_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCEnumParticipants_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCEnumParticipants_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IRTCEnumParticipants_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IRTCEnumParticipants_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IRTCEnumParticipants_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRTCEnumParticipants_Next_Proxy( 
    IRTCEnumParticipants __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [size_is][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *ppElements,
    /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IRTCEnumParticipants_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumParticipants_Reset_Proxy( 
    IRTCEnumParticipants __RPC_FAR * This);


void __RPC_STUB IRTCEnumParticipants_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumParticipants_Skip_Proxy( 
    IRTCEnumParticipants __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IRTCEnumParticipants_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumParticipants_Clone_Proxy( 
    IRTCEnumParticipants __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumParticipants __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCEnumParticipants_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCEnumParticipants_INTERFACE_DEFINED__ */


#ifndef __IRTCEnumProfiles_INTERFACE_DEFINED__
#define __IRTCEnumProfiles_INTERFACE_DEFINED__

/* interface IRTCEnumProfiles */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_IRTCEnumProfiles;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29b7c41c-ed82-4bca-84ad-39d5101b58e3")
    IRTCEnumProfiles : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IRTCEnumProfiles __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCEnumProfilesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCEnumProfiles __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCEnumProfiles __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCEnumProfiles __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IRTCEnumProfiles __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IRTCEnumProfiles __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IRTCEnumProfiles __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IRTCEnumProfiles __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumProfiles __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IRTCEnumProfilesVtbl;

    interface IRTCEnumProfiles
    {
        CONST_VTBL struct IRTCEnumProfilesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCEnumProfiles_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCEnumProfiles_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCEnumProfiles_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCEnumProfiles_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IRTCEnumProfiles_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IRTCEnumProfiles_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IRTCEnumProfiles_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRTCEnumProfiles_Next_Proxy( 
    IRTCEnumProfiles __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [size_is][out] */ IRTCProfile __RPC_FAR *__RPC_FAR *ppElements,
    /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IRTCEnumProfiles_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumProfiles_Reset_Proxy( 
    IRTCEnumProfiles __RPC_FAR * This);


void __RPC_STUB IRTCEnumProfiles_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumProfiles_Skip_Proxy( 
    IRTCEnumProfiles __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IRTCEnumProfiles_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumProfiles_Clone_Proxy( 
    IRTCEnumProfiles __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumProfiles __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCEnumProfiles_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCEnumProfiles_INTERFACE_DEFINED__ */


#ifndef __IRTCEnumBuddies_INTERFACE_DEFINED__
#define __IRTCEnumBuddies_INTERFACE_DEFINED__

/* interface IRTCEnumBuddies */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_IRTCEnumBuddies;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f7296917-5569-4b3b-b3af-98d1144b2b87")
    IRTCEnumBuddies : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IRTCEnumBuddies __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCEnumBuddiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCEnumBuddies __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCEnumBuddies __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCEnumBuddies __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IRTCEnumBuddies __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IRTCEnumBuddies __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IRTCEnumBuddies __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IRTCEnumBuddies __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumBuddies __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IRTCEnumBuddiesVtbl;

    interface IRTCEnumBuddies
    {
        CONST_VTBL struct IRTCEnumBuddiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCEnumBuddies_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCEnumBuddies_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCEnumBuddies_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCEnumBuddies_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IRTCEnumBuddies_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IRTCEnumBuddies_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IRTCEnumBuddies_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRTCEnumBuddies_Next_Proxy( 
    IRTCEnumBuddies __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [size_is][out] */ IRTCBuddy __RPC_FAR *__RPC_FAR *ppElements,
    /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IRTCEnumBuddies_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumBuddies_Reset_Proxy( 
    IRTCEnumBuddies __RPC_FAR * This);


void __RPC_STUB IRTCEnumBuddies_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumBuddies_Skip_Proxy( 
    IRTCEnumBuddies __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IRTCEnumBuddies_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumBuddies_Clone_Proxy( 
    IRTCEnumBuddies __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumBuddies __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCEnumBuddies_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCEnumBuddies_INTERFACE_DEFINED__ */


#ifndef __IRTCEnumWatchers_INTERFACE_DEFINED__
#define __IRTCEnumWatchers_INTERFACE_DEFINED__

/* interface IRTCEnumWatchers */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_IRTCEnumWatchers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a87d55d7-db74-4ed1-9ca4-77a0e41b413e")
    IRTCEnumWatchers : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IRTCEnumWatchers __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCEnumWatchersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCEnumWatchers __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCEnumWatchers __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCEnumWatchers __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IRTCEnumWatchers __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IRTCEnumWatchers __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IRTCEnumWatchers __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IRTCEnumWatchers __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumWatchers __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IRTCEnumWatchersVtbl;

    interface IRTCEnumWatchers
    {
        CONST_VTBL struct IRTCEnumWatchersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCEnumWatchers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCEnumWatchers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCEnumWatchers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCEnumWatchers_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IRTCEnumWatchers_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IRTCEnumWatchers_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IRTCEnumWatchers_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRTCEnumWatchers_Next_Proxy( 
    IRTCEnumWatchers __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [size_is][out] */ IRTCWatcher __RPC_FAR *__RPC_FAR *ppElements,
    /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IRTCEnumWatchers_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumWatchers_Reset_Proxy( 
    IRTCEnumWatchers __RPC_FAR * This);


void __RPC_STUB IRTCEnumWatchers_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumWatchers_Skip_Proxy( 
    IRTCEnumWatchers __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IRTCEnumWatchers_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumWatchers_Clone_Proxy( 
    IRTCEnumWatchers __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumWatchers __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCEnumWatchers_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCEnumWatchers_INTERFACE_DEFINED__ */


#ifndef __IRTCEnumGroups_INTERFACE_DEFINED__
#define __IRTCEnumGroups_INTERFACE_DEFINED__

/* interface IRTCEnumGroups */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_IRTCEnumGroups;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("742378D6-A141-4415-8F27-35D99076CF5D")
    IRTCEnumGroups : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IRTCEnumGroups __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCEnumGroupsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCEnumGroups __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCEnumGroups __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCEnumGroups __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IRTCEnumGroups __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IRTCEnumGroups __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IRTCEnumGroups __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IRTCEnumGroups __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumGroups __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IRTCEnumGroupsVtbl;

    interface IRTCEnumGroups
    {
        CONST_VTBL struct IRTCEnumGroupsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCEnumGroups_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCEnumGroups_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCEnumGroups_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCEnumGroups_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IRTCEnumGroups_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IRTCEnumGroups_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IRTCEnumGroups_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRTCEnumGroups_Next_Proxy( 
    IRTCEnumGroups __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [size_is][out] */ IRTCBuddyGroup __RPC_FAR *__RPC_FAR *ppElements,
    /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IRTCEnumGroups_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumGroups_Reset_Proxy( 
    IRTCEnumGroups __RPC_FAR * This);


void __RPC_STUB IRTCEnumGroups_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumGroups_Skip_Proxy( 
    IRTCEnumGroups __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IRTCEnumGroups_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumGroups_Clone_Proxy( 
    IRTCEnumGroups __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumGroups __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCEnumGroups_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCEnumGroups_INTERFACE_DEFINED__ */


#ifndef __IRTCPresenceContact_INTERFACE_DEFINED__
#define __IRTCPresenceContact_INTERFACE_DEFINED__

/* interface IRTCPresenceContact */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCPresenceContact;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8b22f92c-cd90-42db-a733-212205c3e3df")
    IRTCPresenceContact : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PresentityURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPresentityURI) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PresentityURI( 
            /* [in] */ BSTR bstrPresentityURI) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Data( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Data( 
            /* [in] */ BSTR bstrData) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Persistent( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPersistent) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Persistent( 
            /* [in] */ VARIANT_BOOL fPersistent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCPresenceContactVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCPresenceContact __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCPresenceContact __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCPresenceContact __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PresentityURI )( 
            IRTCPresenceContact __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPresentityURI);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PresentityURI )( 
            IRTCPresenceContact __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IRTCPresenceContact __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IRTCPresenceContact __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Data )( 
            IRTCPresenceContact __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Data )( 
            IRTCPresenceContact __RPC_FAR * This,
            /* [in] */ BSTR bstrData);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Persistent )( 
            IRTCPresenceContact __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPersistent);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Persistent )( 
            IRTCPresenceContact __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPersistent);
        
        END_INTERFACE
    } IRTCPresenceContactVtbl;

    interface IRTCPresenceContact
    {
        CONST_VTBL struct IRTCPresenceContactVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCPresenceContact_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCPresenceContact_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCPresenceContact_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCPresenceContact_get_PresentityURI(This,pbstrPresentityURI)	\
    (This)->lpVtbl -> get_PresentityURI(This,pbstrPresentityURI)

#define IRTCPresenceContact_put_PresentityURI(This,bstrPresentityURI)	\
    (This)->lpVtbl -> put_PresentityURI(This,bstrPresentityURI)

#define IRTCPresenceContact_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IRTCPresenceContact_put_Name(This,bstrName)	\
    (This)->lpVtbl -> put_Name(This,bstrName)

#define IRTCPresenceContact_get_Data(This,pbstrData)	\
    (This)->lpVtbl -> get_Data(This,pbstrData)

#define IRTCPresenceContact_put_Data(This,bstrData)	\
    (This)->lpVtbl -> put_Data(This,bstrData)

#define IRTCPresenceContact_get_Persistent(This,pfPersistent)	\
    (This)->lpVtbl -> get_Persistent(This,pfPersistent)

#define IRTCPresenceContact_put_Persistent(This,fPersistent)	\
    (This)->lpVtbl -> put_Persistent(This,fPersistent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresenceContact_get_PresentityURI_Proxy( 
    IRTCPresenceContact __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrPresentityURI);


void __RPC_STUB IRTCPresenceContact_get_PresentityURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCPresenceContact_put_PresentityURI_Proxy( 
    IRTCPresenceContact __RPC_FAR * This,
    /* [in] */ BSTR bstrPresentityURI);


void __RPC_STUB IRTCPresenceContact_put_PresentityURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresenceContact_get_Name_Proxy( 
    IRTCPresenceContact __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IRTCPresenceContact_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCPresenceContact_put_Name_Proxy( 
    IRTCPresenceContact __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IRTCPresenceContact_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresenceContact_get_Data_Proxy( 
    IRTCPresenceContact __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrData);


void __RPC_STUB IRTCPresenceContact_get_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCPresenceContact_put_Data_Proxy( 
    IRTCPresenceContact __RPC_FAR * This,
    /* [in] */ BSTR bstrData);


void __RPC_STUB IRTCPresenceContact_put_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresenceContact_get_Persistent_Proxy( 
    IRTCPresenceContact __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPersistent);


void __RPC_STUB IRTCPresenceContact_get_Persistent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCPresenceContact_put_Persistent_Proxy( 
    IRTCPresenceContact __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fPersistent);


void __RPC_STUB IRTCPresenceContact_put_Persistent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCPresenceContact_INTERFACE_DEFINED__ */


#ifndef __IRTCBuddy_INTERFACE_DEFINED__
#define __IRTCBuddy_INTERFACE_DEFINED__

/* interface IRTCBuddy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCBuddy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("fcb136c8-7b90-4e0c-befe-56edf0ba6f1c")
    IRTCBuddy : public IRTCPresenceContact
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Notes( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNotes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCBuddyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCBuddy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCBuddy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCBuddy __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PresentityURI )( 
            IRTCBuddy __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPresentityURI);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PresentityURI )( 
            IRTCBuddy __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IRTCBuddy __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IRTCBuddy __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Data )( 
            IRTCBuddy __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Data )( 
            IRTCBuddy __RPC_FAR * This,
            /* [in] */ BSTR bstrData);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Persistent )( 
            IRTCBuddy __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPersistent);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Persistent )( 
            IRTCBuddy __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPersistent);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IRTCBuddy __RPC_FAR * This,
            /* [retval][out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Notes )( 
            IRTCBuddy __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNotes);
        
        END_INTERFACE
    } IRTCBuddyVtbl;

    interface IRTCBuddy
    {
        CONST_VTBL struct IRTCBuddyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCBuddy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCBuddy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCBuddy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCBuddy_get_PresentityURI(This,pbstrPresentityURI)	\
    (This)->lpVtbl -> get_PresentityURI(This,pbstrPresentityURI)

#define IRTCBuddy_put_PresentityURI(This,bstrPresentityURI)	\
    (This)->lpVtbl -> put_PresentityURI(This,bstrPresentityURI)

#define IRTCBuddy_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IRTCBuddy_put_Name(This,bstrName)	\
    (This)->lpVtbl -> put_Name(This,bstrName)

#define IRTCBuddy_get_Data(This,pbstrData)	\
    (This)->lpVtbl -> get_Data(This,pbstrData)

#define IRTCBuddy_put_Data(This,bstrData)	\
    (This)->lpVtbl -> put_Data(This,bstrData)

#define IRTCBuddy_get_Persistent(This,pfPersistent)	\
    (This)->lpVtbl -> get_Persistent(This,pfPersistent)

#define IRTCBuddy_put_Persistent(This,fPersistent)	\
    (This)->lpVtbl -> put_Persistent(This,fPersistent)


#define IRTCBuddy_get_Status(This,penStatus)	\
    (This)->lpVtbl -> get_Status(This,penStatus)

#define IRTCBuddy_get_Notes(This,pbstrNotes)	\
    (This)->lpVtbl -> get_Notes(This,pbstrNotes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddy_get_Status_Proxy( 
    IRTCBuddy __RPC_FAR * This,
    /* [retval][out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus);


void __RPC_STUB IRTCBuddy_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddy_get_Notes_Proxy( 
    IRTCBuddy __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrNotes);


void __RPC_STUB IRTCBuddy_get_Notes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCBuddy_INTERFACE_DEFINED__ */


#ifndef __IRTCBuddy2_INTERFACE_DEFINED__
#define __IRTCBuddy2_INTERFACE_DEFINED__

/* interface IRTCBuddy2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCBuddy2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("102F9588-23E7-40e3-954D-CD7A1D5C0361")
    IRTCBuddy2 : public IRTCBuddy
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE EnumerateGroups( 
            /* [retval][out] */ IRTCEnumGroups __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Groups( 
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PresenceProperty( 
            /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProperty) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumeratePresenceDevices( 
            /* [retval][out] */ IRTCEnumPresenceDevices __RPC_FAR *__RPC_FAR *ppEnumDevices) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PresenceDevices( 
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppDevicesCollection) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SubscriptionType( 
            /* [retval][out] */ RTC_BUDDY_SUBSCRIPTION_TYPE __RPC_FAR *penSubscriptionType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCBuddy2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCBuddy2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCBuddy2 __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PresentityURI )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPresentityURI);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PresentityURI )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Data )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Data )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [in] */ BSTR bstrData);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Persistent )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPersistent);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Persistent )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPersistent);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Notes )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNotes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IRTCBuddy2 __RPC_FAR * This);
        
        /* [helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateGroups )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumGroups __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Groups )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PresenceProperty )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProperty);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumeratePresenceDevices )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumPresenceDevices __RPC_FAR *__RPC_FAR *ppEnumDevices);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PresenceDevices )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppDevicesCollection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubscriptionType )( 
            IRTCBuddy2 __RPC_FAR * This,
            /* [retval][out] */ RTC_BUDDY_SUBSCRIPTION_TYPE __RPC_FAR *penSubscriptionType);
        
        END_INTERFACE
    } IRTCBuddy2Vtbl;

    interface IRTCBuddy2
    {
        CONST_VTBL struct IRTCBuddy2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCBuddy2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCBuddy2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCBuddy2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCBuddy2_get_PresentityURI(This,pbstrPresentityURI)	\
    (This)->lpVtbl -> get_PresentityURI(This,pbstrPresentityURI)

#define IRTCBuddy2_put_PresentityURI(This,bstrPresentityURI)	\
    (This)->lpVtbl -> put_PresentityURI(This,bstrPresentityURI)

#define IRTCBuddy2_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IRTCBuddy2_put_Name(This,bstrName)	\
    (This)->lpVtbl -> put_Name(This,bstrName)

#define IRTCBuddy2_get_Data(This,pbstrData)	\
    (This)->lpVtbl -> get_Data(This,pbstrData)

#define IRTCBuddy2_put_Data(This,bstrData)	\
    (This)->lpVtbl -> put_Data(This,bstrData)

#define IRTCBuddy2_get_Persistent(This,pfPersistent)	\
    (This)->lpVtbl -> get_Persistent(This,pfPersistent)

#define IRTCBuddy2_put_Persistent(This,fPersistent)	\
    (This)->lpVtbl -> put_Persistent(This,fPersistent)


#define IRTCBuddy2_get_Status(This,penStatus)	\
    (This)->lpVtbl -> get_Status(This,penStatus)

#define IRTCBuddy2_get_Notes(This,pbstrNotes)	\
    (This)->lpVtbl -> get_Notes(This,pbstrNotes)


#define IRTCBuddy2_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#define IRTCBuddy2_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IRTCBuddy2_EnumerateGroups(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateGroups(This,ppEnum)

#define IRTCBuddy2_get_Groups(This,ppCollection)	\
    (This)->lpVtbl -> get_Groups(This,ppCollection)

#define IRTCBuddy2_get_PresenceProperty(This,enProperty,pbstrProperty)	\
    (This)->lpVtbl -> get_PresenceProperty(This,enProperty,pbstrProperty)

#define IRTCBuddy2_EnumeratePresenceDevices(This,ppEnumDevices)	\
    (This)->lpVtbl -> EnumeratePresenceDevices(This,ppEnumDevices)

#define IRTCBuddy2_get_PresenceDevices(This,ppDevicesCollection)	\
    (This)->lpVtbl -> get_PresenceDevices(This,ppDevicesCollection)

#define IRTCBuddy2_get_SubscriptionType(This,penSubscriptionType)	\
    (This)->lpVtbl -> get_SubscriptionType(This,penSubscriptionType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddy2_get_Profile_Proxy( 
    IRTCBuddy2 __RPC_FAR * This,
    /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB IRTCBuddy2_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCBuddy2_Refresh_Proxy( 
    IRTCBuddy2 __RPC_FAR * This);


void __RPC_STUB IRTCBuddy2_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IRTCBuddy2_EnumerateGroups_Proxy( 
    IRTCBuddy2 __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumGroups __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCBuddy2_EnumerateGroups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddy2_get_Groups_Proxy( 
    IRTCBuddy2 __RPC_FAR * This,
    /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);


void __RPC_STUB IRTCBuddy2_get_Groups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddy2_get_PresenceProperty_Proxy( 
    IRTCBuddy2 __RPC_FAR * This,
    /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrProperty);


void __RPC_STUB IRTCBuddy2_get_PresenceProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCBuddy2_EnumeratePresenceDevices_Proxy( 
    IRTCBuddy2 __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumPresenceDevices __RPC_FAR *__RPC_FAR *ppEnumDevices);


void __RPC_STUB IRTCBuddy2_EnumeratePresenceDevices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddy2_get_PresenceDevices_Proxy( 
    IRTCBuddy2 __RPC_FAR * This,
    /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppDevicesCollection);


void __RPC_STUB IRTCBuddy2_get_PresenceDevices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddy2_get_SubscriptionType_Proxy( 
    IRTCBuddy2 __RPC_FAR * This,
    /* [retval][out] */ RTC_BUDDY_SUBSCRIPTION_TYPE __RPC_FAR *penSubscriptionType);


void __RPC_STUB IRTCBuddy2_get_SubscriptionType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCBuddy2_INTERFACE_DEFINED__ */


#ifndef __IRTCWatcher_INTERFACE_DEFINED__
#define __IRTCWatcher_INTERFACE_DEFINED__

/* interface IRTCWatcher */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCWatcher;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c7cedad8-346b-4d1b-ac02-a2088df9be4f")
    IRTCWatcher : public IRTCPresenceContact
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ RTC_WATCHER_STATE __RPC_FAR *penState) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_State( 
            /* [in] */ RTC_WATCHER_STATE enState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCWatcherVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCWatcher __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCWatcher __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCWatcher __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PresentityURI )( 
            IRTCWatcher __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPresentityURI);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PresentityURI )( 
            IRTCWatcher __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IRTCWatcher __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IRTCWatcher __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Data )( 
            IRTCWatcher __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Data )( 
            IRTCWatcher __RPC_FAR * This,
            /* [in] */ BSTR bstrData);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Persistent )( 
            IRTCWatcher __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPersistent);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Persistent )( 
            IRTCWatcher __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPersistent);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCWatcher __RPC_FAR * This,
            /* [retval][out] */ RTC_WATCHER_STATE __RPC_FAR *penState);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_State )( 
            IRTCWatcher __RPC_FAR * This,
            /* [in] */ RTC_WATCHER_STATE enState);
        
        END_INTERFACE
    } IRTCWatcherVtbl;

    interface IRTCWatcher
    {
        CONST_VTBL struct IRTCWatcherVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCWatcher_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCWatcher_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCWatcher_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCWatcher_get_PresentityURI(This,pbstrPresentityURI)	\
    (This)->lpVtbl -> get_PresentityURI(This,pbstrPresentityURI)

#define IRTCWatcher_put_PresentityURI(This,bstrPresentityURI)	\
    (This)->lpVtbl -> put_PresentityURI(This,bstrPresentityURI)

#define IRTCWatcher_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IRTCWatcher_put_Name(This,bstrName)	\
    (This)->lpVtbl -> put_Name(This,bstrName)

#define IRTCWatcher_get_Data(This,pbstrData)	\
    (This)->lpVtbl -> get_Data(This,pbstrData)

#define IRTCWatcher_put_Data(This,bstrData)	\
    (This)->lpVtbl -> put_Data(This,bstrData)

#define IRTCWatcher_get_Persistent(This,pfPersistent)	\
    (This)->lpVtbl -> get_Persistent(This,pfPersistent)

#define IRTCWatcher_put_Persistent(This,fPersistent)	\
    (This)->lpVtbl -> put_Persistent(This,fPersistent)


#define IRTCWatcher_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#define IRTCWatcher_put_State(This,enState)	\
    (This)->lpVtbl -> put_State(This,enState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCWatcher_get_State_Proxy( 
    IRTCWatcher __RPC_FAR * This,
    /* [retval][out] */ RTC_WATCHER_STATE __RPC_FAR *penState);


void __RPC_STUB IRTCWatcher_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCWatcher_put_State_Proxy( 
    IRTCWatcher __RPC_FAR * This,
    /* [in] */ RTC_WATCHER_STATE enState);


void __RPC_STUB IRTCWatcher_put_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCWatcher_INTERFACE_DEFINED__ */


#ifndef __IRTCWatcher2_INTERFACE_DEFINED__
#define __IRTCWatcher2_INTERFACE_DEFINED__

/* interface IRTCWatcher2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCWatcher2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D4D9967F-D011-4b1d-91E3-ABA78F96393D")
    IRTCWatcher2 : public IRTCWatcher
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Scope( 
            /* [retval][out] */ RTC_ACE_SCOPE __RPC_FAR *penScope) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCWatcher2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCWatcher2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCWatcher2 __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PresentityURI )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPresentityURI);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PresentityURI )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [in] */ BSTR bstrPresentityURI);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Data )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Data )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [in] */ BSTR bstrData);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Persistent )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPersistent);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Persistent )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPersistent);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [retval][out] */ RTC_WATCHER_STATE __RPC_FAR *penState);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_State )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [in] */ RTC_WATCHER_STATE enState);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Scope )( 
            IRTCWatcher2 __RPC_FAR * This,
            /* [retval][out] */ RTC_ACE_SCOPE __RPC_FAR *penScope);
        
        END_INTERFACE
    } IRTCWatcher2Vtbl;

    interface IRTCWatcher2
    {
        CONST_VTBL struct IRTCWatcher2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCWatcher2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCWatcher2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCWatcher2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCWatcher2_get_PresentityURI(This,pbstrPresentityURI)	\
    (This)->lpVtbl -> get_PresentityURI(This,pbstrPresentityURI)

#define IRTCWatcher2_put_PresentityURI(This,bstrPresentityURI)	\
    (This)->lpVtbl -> put_PresentityURI(This,bstrPresentityURI)

#define IRTCWatcher2_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IRTCWatcher2_put_Name(This,bstrName)	\
    (This)->lpVtbl -> put_Name(This,bstrName)

#define IRTCWatcher2_get_Data(This,pbstrData)	\
    (This)->lpVtbl -> get_Data(This,pbstrData)

#define IRTCWatcher2_put_Data(This,bstrData)	\
    (This)->lpVtbl -> put_Data(This,bstrData)

#define IRTCWatcher2_get_Persistent(This,pfPersistent)	\
    (This)->lpVtbl -> get_Persistent(This,pfPersistent)

#define IRTCWatcher2_put_Persistent(This,fPersistent)	\
    (This)->lpVtbl -> put_Persistent(This,fPersistent)


#define IRTCWatcher2_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#define IRTCWatcher2_put_State(This,enState)	\
    (This)->lpVtbl -> put_State(This,enState)


#define IRTCWatcher2_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#define IRTCWatcher2_get_Scope(This,penScope)	\
    (This)->lpVtbl -> get_Scope(This,penScope)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCWatcher2_get_Profile_Proxy( 
    IRTCWatcher2 __RPC_FAR * This,
    /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB IRTCWatcher2_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCWatcher2_get_Scope_Proxy( 
    IRTCWatcher2 __RPC_FAR * This,
    /* [retval][out] */ RTC_ACE_SCOPE __RPC_FAR *penScope);


void __RPC_STUB IRTCWatcher2_get_Scope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCWatcher2_INTERFACE_DEFINED__ */


#ifndef __IRTCBuddyGroup_INTERFACE_DEFINED__
#define __IRTCBuddyGroup_INTERFACE_DEFINED__

/* interface IRTCBuddyGroup */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCBuddyGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("60361E68-9164-4389-A4C6-D0B3925BDA5E")
    IRTCBuddyGroup : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrGroupName) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrGroupName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddBuddy( 
            /* [in] */ IRTCBuddy __RPC_FAR *pBuddy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveBuddy( 
            /* [in] */ IRTCBuddy __RPC_FAR *pBuddy) = 0;
        
        virtual /* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE EnumerateBuddies( 
            /* [retval][out] */ IRTCEnumBuddies __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Buddies( 
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Data( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Data( 
            /* [in] */ BSTR bstrData) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCBuddyGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCBuddyGroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCBuddyGroup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCBuddyGroup __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IRTCBuddyGroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrGroupName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IRTCBuddyGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrGroupName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddBuddy )( 
            IRTCBuddyGroup __RPC_FAR * This,
            /* [in] */ IRTCBuddy __RPC_FAR *pBuddy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveBuddy )( 
            IRTCBuddyGroup __RPC_FAR * This,
            /* [in] */ IRTCBuddy __RPC_FAR *pBuddy);
        
        /* [helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateBuddies )( 
            IRTCBuddyGroup __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumBuddies __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Buddies )( 
            IRTCBuddyGroup __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Data )( 
            IRTCBuddyGroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Data )( 
            IRTCBuddyGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrData);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IRTCBuddyGroup __RPC_FAR * This,
            /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile);
        
        END_INTERFACE
    } IRTCBuddyGroupVtbl;

    interface IRTCBuddyGroup
    {
        CONST_VTBL struct IRTCBuddyGroupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCBuddyGroup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCBuddyGroup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCBuddyGroup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCBuddyGroup_get_Name(This,pbstrGroupName)	\
    (This)->lpVtbl -> get_Name(This,pbstrGroupName)

#define IRTCBuddyGroup_put_Name(This,bstrGroupName)	\
    (This)->lpVtbl -> put_Name(This,bstrGroupName)

#define IRTCBuddyGroup_AddBuddy(This,pBuddy)	\
    (This)->lpVtbl -> AddBuddy(This,pBuddy)

#define IRTCBuddyGroup_RemoveBuddy(This,pBuddy)	\
    (This)->lpVtbl -> RemoveBuddy(This,pBuddy)

#define IRTCBuddyGroup_EnumerateBuddies(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateBuddies(This,ppEnum)

#define IRTCBuddyGroup_get_Buddies(This,ppCollection)	\
    (This)->lpVtbl -> get_Buddies(This,ppCollection)

#define IRTCBuddyGroup_get_Data(This,pbstrData)	\
    (This)->lpVtbl -> get_Data(This,pbstrData)

#define IRTCBuddyGroup_put_Data(This,bstrData)	\
    (This)->lpVtbl -> put_Data(This,bstrData)

#define IRTCBuddyGroup_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroup_get_Name_Proxy( 
    IRTCBuddyGroup __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrGroupName);


void __RPC_STUB IRTCBuddyGroup_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroup_put_Name_Proxy( 
    IRTCBuddyGroup __RPC_FAR * This,
    /* [in] */ BSTR bstrGroupName);


void __RPC_STUB IRTCBuddyGroup_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroup_AddBuddy_Proxy( 
    IRTCBuddyGroup __RPC_FAR * This,
    /* [in] */ IRTCBuddy __RPC_FAR *pBuddy);


void __RPC_STUB IRTCBuddyGroup_AddBuddy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroup_RemoveBuddy_Proxy( 
    IRTCBuddyGroup __RPC_FAR * This,
    /* [in] */ IRTCBuddy __RPC_FAR *pBuddy);


void __RPC_STUB IRTCBuddyGroup_RemoveBuddy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroup_EnumerateBuddies_Proxy( 
    IRTCBuddyGroup __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumBuddies __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCBuddyGroup_EnumerateBuddies_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroup_get_Buddies_Proxy( 
    IRTCBuddyGroup __RPC_FAR * This,
    /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);


void __RPC_STUB IRTCBuddyGroup_get_Buddies_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroup_get_Data_Proxy( 
    IRTCBuddyGroup __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrData);


void __RPC_STUB IRTCBuddyGroup_get_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroup_put_Data_Proxy( 
    IRTCBuddyGroup __RPC_FAR * This,
    /* [in] */ BSTR bstrData);


void __RPC_STUB IRTCBuddyGroup_put_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCBuddyGroup_get_Profile_Proxy( 
    IRTCBuddyGroup __RPC_FAR * This,
    /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB IRTCBuddyGroup_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCBuddyGroup_INTERFACE_DEFINED__ */


#ifndef __IRTCEventNotification_INTERFACE_DEFINED__
#define __IRTCEventNotification_INTERFACE_DEFINED__

/* interface IRTCEventNotification */
/* [unique][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCEventNotification;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("13fa24c7-5748-4b21-91f5-7397609ce747")
    IRTCEventNotification : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Event( 
            /* [in] */ RTC_EVENT RTCEvent,
            /* [in] */ IDispatch __RPC_FAR *pEvent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCEventNotificationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCEventNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCEventNotification __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCEventNotification __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Event )( 
            IRTCEventNotification __RPC_FAR * This,
            /* [in] */ RTC_EVENT RTCEvent,
            /* [in] */ IDispatch __RPC_FAR *pEvent);
        
        END_INTERFACE
    } IRTCEventNotificationVtbl;

    interface IRTCEventNotification
    {
        CONST_VTBL struct IRTCEventNotificationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCEventNotification_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCEventNotification_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCEventNotification_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCEventNotification_Event(This,RTCEvent,pEvent)	\
    (This)->lpVtbl -> Event(This,RTCEvent,pEvent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCEventNotification_Event_Proxy( 
    IRTCEventNotification __RPC_FAR * This,
    /* [in] */ RTC_EVENT RTCEvent,
    /* [in] */ IDispatch __RPC_FAR *pEvent);


void __RPC_STUB IRTCEventNotification_Event_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCEventNotification_INTERFACE_DEFINED__ */


#ifndef __IRTCPortManager_INTERFACE_DEFINED__
#define __IRTCPortManager_INTERFACE_DEFINED__

/* interface IRTCPortManager */
/* [unique][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCPortManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DA77C14B-6208-43ca-8DDF-5B60A0A69FAC")
    IRTCPortManager : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMapping( 
            /* [in] */ BSTR bstrRemoteAddress,
            /* [in] */ RTC_PORT_TYPE enPortType,
            /* [out][in] */ BSTR __RPC_FAR *pbstrInternalLocalAddress,
            /* [out][in] */ long __RPC_FAR *plInternalLocalPort,
            /* [out][in] */ BSTR __RPC_FAR *pbstrExternalLocalAddress,
            /* [out][in] */ long __RPC_FAR *plExternalLocalPort) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateRemoteAddress( 
            /* [in] */ BSTR bstrRemoteAddress,
            /* [in] */ BSTR bstrInternalLocalAddress,
            /* [in] */ long lInternalLocalPort,
            /* [in] */ BSTR bstrExternalLocalAddress,
            /* [in] */ long lExternalLocalPort) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseMapping( 
            /* [in] */ BSTR bstrInternalLocalAddress,
            /* [in] */ long lInternalLocalPort,
            /* [in] */ BSTR bstrExternalLocalAddress,
            /* [in] */ long lExternalLocalAddress) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCPortManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCPortManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCPortManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCPortManager __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMapping )( 
            IRTCPortManager __RPC_FAR * This,
            /* [in] */ BSTR bstrRemoteAddress,
            /* [in] */ RTC_PORT_TYPE enPortType,
            /* [out][in] */ BSTR __RPC_FAR *pbstrInternalLocalAddress,
            /* [out][in] */ long __RPC_FAR *plInternalLocalPort,
            /* [out][in] */ BSTR __RPC_FAR *pbstrExternalLocalAddress,
            /* [out][in] */ long __RPC_FAR *plExternalLocalPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateRemoteAddress )( 
            IRTCPortManager __RPC_FAR * This,
            /* [in] */ BSTR bstrRemoteAddress,
            /* [in] */ BSTR bstrInternalLocalAddress,
            /* [in] */ long lInternalLocalPort,
            /* [in] */ BSTR bstrExternalLocalAddress,
            /* [in] */ long lExternalLocalPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseMapping )( 
            IRTCPortManager __RPC_FAR * This,
            /* [in] */ BSTR bstrInternalLocalAddress,
            /* [in] */ long lInternalLocalPort,
            /* [in] */ BSTR bstrExternalLocalAddress,
            /* [in] */ long lExternalLocalAddress);
        
        END_INTERFACE
    } IRTCPortManagerVtbl;

    interface IRTCPortManager
    {
        CONST_VTBL struct IRTCPortManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCPortManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCPortManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCPortManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCPortManager_GetMapping(This,bstrRemoteAddress,enPortType,pbstrInternalLocalAddress,plInternalLocalPort,pbstrExternalLocalAddress,plExternalLocalPort)	\
    (This)->lpVtbl -> GetMapping(This,bstrRemoteAddress,enPortType,pbstrInternalLocalAddress,plInternalLocalPort,pbstrExternalLocalAddress,plExternalLocalPort)

#define IRTCPortManager_UpdateRemoteAddress(This,bstrRemoteAddress,bstrInternalLocalAddress,lInternalLocalPort,bstrExternalLocalAddress,lExternalLocalPort)	\
    (This)->lpVtbl -> UpdateRemoteAddress(This,bstrRemoteAddress,bstrInternalLocalAddress,lInternalLocalPort,bstrExternalLocalAddress,lExternalLocalPort)

#define IRTCPortManager_ReleaseMapping(This,bstrInternalLocalAddress,lInternalLocalPort,bstrExternalLocalAddress,lExternalLocalAddress)	\
    (This)->lpVtbl -> ReleaseMapping(This,bstrInternalLocalAddress,lInternalLocalPort,bstrExternalLocalAddress,lExternalLocalAddress)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCPortManager_GetMapping_Proxy( 
    IRTCPortManager __RPC_FAR * This,
    /* [in] */ BSTR bstrRemoteAddress,
    /* [in] */ RTC_PORT_TYPE enPortType,
    /* [out][in] */ BSTR __RPC_FAR *pbstrInternalLocalAddress,
    /* [out][in] */ long __RPC_FAR *plInternalLocalPort,
    /* [out][in] */ BSTR __RPC_FAR *pbstrExternalLocalAddress,
    /* [out][in] */ long __RPC_FAR *plExternalLocalPort);


void __RPC_STUB IRTCPortManager_GetMapping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCPortManager_UpdateRemoteAddress_Proxy( 
    IRTCPortManager __RPC_FAR * This,
    /* [in] */ BSTR bstrRemoteAddress,
    /* [in] */ BSTR bstrInternalLocalAddress,
    /* [in] */ long lInternalLocalPort,
    /* [in] */ BSTR bstrExternalLocalAddress,
    /* [in] */ long lExternalLocalPort);


void __RPC_STUB IRTCPortManager_UpdateRemoteAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCPortManager_ReleaseMapping_Proxy( 
    IRTCPortManager __RPC_FAR * This,
    /* [in] */ BSTR bstrInternalLocalAddress,
    /* [in] */ long lInternalLocalPort,
    /* [in] */ BSTR bstrExternalLocalAddress,
    /* [in] */ long lExternalLocalAddress);


void __RPC_STUB IRTCPortManager_ReleaseMapping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCPortManager_INTERFACE_DEFINED__ */


#ifndef __IRTCSessionPortManagement_INTERFACE_DEFINED__
#define __IRTCSessionPortManagement_INTERFACE_DEFINED__

/* interface IRTCSessionPortManagement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCSessionPortManagement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a072f1d6-0286-4e1f-85f2-17a2948456ec")
    IRTCSessionPortManagement : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetPortManager( 
            /* [in] */ IRTCPortManager __RPC_FAR *pPortManager) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCSessionPortManagementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCSessionPortManagement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCSessionPortManagement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCSessionPortManagement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPortManager )( 
            IRTCSessionPortManagement __RPC_FAR * This,
            /* [in] */ IRTCPortManager __RPC_FAR *pPortManager);
        
        END_INTERFACE
    } IRTCSessionPortManagementVtbl;

    interface IRTCSessionPortManagement
    {
        CONST_VTBL struct IRTCSessionPortManagementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCSessionPortManagement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCSessionPortManagement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCSessionPortManagement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCSessionPortManagement_SetPortManager(This,pPortManager)	\
    (This)->lpVtbl -> SetPortManager(This,pPortManager)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRTCSessionPortManagement_SetPortManager_Proxy( 
    IRTCSessionPortManagement __RPC_FAR * This,
    /* [in] */ IRTCPortManager __RPC_FAR *pPortManager);


void __RPC_STUB IRTCSessionPortManagement_SetPortManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCSessionPortManagement_INTERFACE_DEFINED__ */


#ifndef __IRTCClientPortManagement_INTERFACE_DEFINED__
#define __IRTCClientPortManagement_INTERFACE_DEFINED__

/* interface IRTCClientPortManagement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCClientPortManagement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d5df3f03-4bde-4417-aefe-71177bdaea66")
    IRTCClientPortManagement : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartListenAddressAndPort( 
            /* [in] */ BSTR bstrInternalLocalAddress,
            /* [in] */ long lInternalLocalPort) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopListenAddressAndPort( 
            /* [in] */ BSTR bstrInternalLocalAddress,
            /* [in] */ long lInternalLocalPort) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPortRange( 
            /* [in] */ RTC_PORT_TYPE enPortType,
            /* [out] */ long __RPC_FAR *plMinValue,
            /* [out] */ long __RPC_FAR *plMaxValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCClientPortManagementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCClientPortManagement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCClientPortManagement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCClientPortManagement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartListenAddressAndPort )( 
            IRTCClientPortManagement __RPC_FAR * This,
            /* [in] */ BSTR bstrInternalLocalAddress,
            /* [in] */ long lInternalLocalPort);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopListenAddressAndPort )( 
            IRTCClientPortManagement __RPC_FAR * This,
            /* [in] */ BSTR bstrInternalLocalAddress,
            /* [in] */ long lInternalLocalPort);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPortRange )( 
            IRTCClientPortManagement __RPC_FAR * This,
            /* [in] */ RTC_PORT_TYPE enPortType,
            /* [out] */ long __RPC_FAR *plMinValue,
            /* [out] */ long __RPC_FAR *plMaxValue);
        
        END_INTERFACE
    } IRTCClientPortManagementVtbl;

    interface IRTCClientPortManagement
    {
        CONST_VTBL struct IRTCClientPortManagementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCClientPortManagement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCClientPortManagement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCClientPortManagement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCClientPortManagement_StartListenAddressAndPort(This,bstrInternalLocalAddress,lInternalLocalPort)	\
    (This)->lpVtbl -> StartListenAddressAndPort(This,bstrInternalLocalAddress,lInternalLocalPort)

#define IRTCClientPortManagement_StopListenAddressAndPort(This,bstrInternalLocalAddress,lInternalLocalPort)	\
    (This)->lpVtbl -> StopListenAddressAndPort(This,bstrInternalLocalAddress,lInternalLocalPort)

#define IRTCClientPortManagement_GetPortRange(This,enPortType,plMinValue,plMaxValue)	\
    (This)->lpVtbl -> GetPortRange(This,enPortType,plMinValue,plMaxValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRTCClientPortManagement_StartListenAddressAndPort_Proxy( 
    IRTCClientPortManagement __RPC_FAR * This,
    /* [in] */ BSTR bstrInternalLocalAddress,
    /* [in] */ long lInternalLocalPort);


void __RPC_STUB IRTCClientPortManagement_StartListenAddressAndPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCClientPortManagement_StopListenAddressAndPort_Proxy( 
    IRTCClientPortManagement __RPC_FAR * This,
    /* [in] */ BSTR bstrInternalLocalAddress,
    /* [in] */ long lInternalLocalPort);


void __RPC_STUB IRTCClientPortManagement_StopListenAddressAndPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCClientPortManagement_GetPortRange_Proxy( 
    IRTCClientPortManagement __RPC_FAR * This,
    /* [in] */ RTC_PORT_TYPE enPortType,
    /* [out] */ long __RPC_FAR *plMinValue,
    /* [out] */ long __RPC_FAR *plMaxValue);


void __RPC_STUB IRTCClientPortManagement_GetPortRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCClientPortManagement_INTERFACE_DEFINED__ */


#ifndef __IRTCUserSearch_INTERFACE_DEFINED__
#define __IRTCUserSearch_INTERFACE_DEFINED__

/* interface IRTCUserSearch */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCUserSearch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B619882B-860C-4db4-BE1B-693B6505BBE5")
    IRTCUserSearch : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateQuery( 
            /* [retval][out] */ IRTCUserSearchQuery __RPC_FAR *__RPC_FAR *ppQuery) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ExecuteSearch( 
            /* [in] */ IRTCUserSearchQuery __RPC_FAR *pQuery,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ LONG_PTR lCookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCUserSearchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCUserSearch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCUserSearch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCUserSearch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateQuery )( 
            IRTCUserSearch __RPC_FAR * This,
            /* [retval][out] */ IRTCUserSearchQuery __RPC_FAR *__RPC_FAR *ppQuery);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExecuteSearch )( 
            IRTCUserSearch __RPC_FAR * This,
            /* [in] */ IRTCUserSearchQuery __RPC_FAR *pQuery,
            /* [in] */ IRTCProfile __RPC_FAR *pProfile,
            /* [in] */ LONG_PTR lCookie);
        
        END_INTERFACE
    } IRTCUserSearchVtbl;

    interface IRTCUserSearch
    {
        CONST_VTBL struct IRTCUserSearchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCUserSearch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCUserSearch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCUserSearch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCUserSearch_CreateQuery(This,ppQuery)	\
    (This)->lpVtbl -> CreateQuery(This,ppQuery)

#define IRTCUserSearch_ExecuteSearch(This,pQuery,pProfile,lCookie)	\
    (This)->lpVtbl -> ExecuteSearch(This,pQuery,pProfile,lCookie)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCUserSearch_CreateQuery_Proxy( 
    IRTCUserSearch __RPC_FAR * This,
    /* [retval][out] */ IRTCUserSearchQuery __RPC_FAR *__RPC_FAR *ppQuery);


void __RPC_STUB IRTCUserSearch_CreateQuery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCUserSearch_ExecuteSearch_Proxy( 
    IRTCUserSearch __RPC_FAR * This,
    /* [in] */ IRTCUserSearchQuery __RPC_FAR *pQuery,
    /* [in] */ IRTCProfile __RPC_FAR *pProfile,
    /* [in] */ LONG_PTR lCookie);


void __RPC_STUB IRTCUserSearch_ExecuteSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCUserSearch_INTERFACE_DEFINED__ */


#ifndef __IRTCUserSearchQuery_INTERFACE_DEFINED__
#define __IRTCUserSearchQuery_INTERFACE_DEFINED__

/* interface IRTCUserSearchQuery */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCUserSearchQuery;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("288300F5-D23A-4365-9A73-9985C98C2881")
    IRTCUserSearchQuery : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SearchTerm( 
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrValue) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SearchTerm( 
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SearchTerms( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNames) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SearchPreference( 
            /* [in] */ RTC_USER_SEARCH_PREFERENCE enPreference,
            /* [in] */ long lValue) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SearchPreference( 
            /* [in] */ RTC_USER_SEARCH_PREFERENCE enPreference,
            /* [retval][out] */ long __RPC_FAR *plValue) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SearchDomain( 
            /* [in] */ BSTR bstrDomain) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SearchDomain( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDomain) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCUserSearchQueryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCUserSearchQuery __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCUserSearchQuery __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCUserSearchQuery __RPC_FAR * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SearchTerm )( 
            IRTCUserSearchQuery __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrValue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SearchTerm )( 
            IRTCUserSearchQuery __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SearchTerms )( 
            IRTCUserSearchQuery __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNames);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SearchPreference )( 
            IRTCUserSearchQuery __RPC_FAR * This,
            /* [in] */ RTC_USER_SEARCH_PREFERENCE enPreference,
            /* [in] */ long lValue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SearchPreference )( 
            IRTCUserSearchQuery __RPC_FAR * This,
            /* [in] */ RTC_USER_SEARCH_PREFERENCE enPreference,
            /* [retval][out] */ long __RPC_FAR *plValue);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SearchDomain )( 
            IRTCUserSearchQuery __RPC_FAR * This,
            /* [in] */ BSTR bstrDomain);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SearchDomain )( 
            IRTCUserSearchQuery __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDomain);
        
        END_INTERFACE
    } IRTCUserSearchQueryVtbl;

    interface IRTCUserSearchQuery
    {
        CONST_VTBL struct IRTCUserSearchQueryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCUserSearchQuery_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCUserSearchQuery_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCUserSearchQuery_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCUserSearchQuery_put_SearchTerm(This,bstrName,bstrValue)	\
    (This)->lpVtbl -> put_SearchTerm(This,bstrName,bstrValue)

#define IRTCUserSearchQuery_get_SearchTerm(This,bstrName,pbstrValue)	\
    (This)->lpVtbl -> get_SearchTerm(This,bstrName,pbstrValue)

#define IRTCUserSearchQuery_get_SearchTerms(This,pbstrNames)	\
    (This)->lpVtbl -> get_SearchTerms(This,pbstrNames)

#define IRTCUserSearchQuery_put_SearchPreference(This,enPreference,lValue)	\
    (This)->lpVtbl -> put_SearchPreference(This,enPreference,lValue)

#define IRTCUserSearchQuery_get_SearchPreference(This,enPreference,plValue)	\
    (This)->lpVtbl -> get_SearchPreference(This,enPreference,plValue)

#define IRTCUserSearchQuery_put_SearchDomain(This,bstrDomain)	\
    (This)->lpVtbl -> put_SearchDomain(This,bstrDomain)

#define IRTCUserSearchQuery_get_SearchDomain(This,pbstrDomain)	\
    (This)->lpVtbl -> get_SearchDomain(This,pbstrDomain)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchQuery_put_SearchTerm_Proxy( 
    IRTCUserSearchQuery __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ BSTR bstrValue);


void __RPC_STUB IRTCUserSearchQuery_put_SearchTerm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchQuery_get_SearchTerm_Proxy( 
    IRTCUserSearchQuery __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);


void __RPC_STUB IRTCUserSearchQuery_get_SearchTerm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchQuery_get_SearchTerms_Proxy( 
    IRTCUserSearchQuery __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrNames);


void __RPC_STUB IRTCUserSearchQuery_get_SearchTerms_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchQuery_put_SearchPreference_Proxy( 
    IRTCUserSearchQuery __RPC_FAR * This,
    /* [in] */ RTC_USER_SEARCH_PREFERENCE enPreference,
    /* [in] */ long lValue);


void __RPC_STUB IRTCUserSearchQuery_put_SearchPreference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchQuery_get_SearchPreference_Proxy( 
    IRTCUserSearchQuery __RPC_FAR * This,
    /* [in] */ RTC_USER_SEARCH_PREFERENCE enPreference,
    /* [retval][out] */ long __RPC_FAR *plValue);


void __RPC_STUB IRTCUserSearchQuery_get_SearchPreference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchQuery_put_SearchDomain_Proxy( 
    IRTCUserSearchQuery __RPC_FAR * This,
    /* [in] */ BSTR bstrDomain);


void __RPC_STUB IRTCUserSearchQuery_put_SearchDomain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchQuery_get_SearchDomain_Proxy( 
    IRTCUserSearchQuery __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDomain);


void __RPC_STUB IRTCUserSearchQuery_get_SearchDomain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCUserSearchQuery_INTERFACE_DEFINED__ */


#ifndef __IRTCUserSearchResult_INTERFACE_DEFINED__
#define __IRTCUserSearchResult_INTERFACE_DEFINED__

/* interface IRTCUserSearchResult */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCUserSearchResult;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("851278B2-9592-480f-8DB5-2DE86B26B54D")
    IRTCUserSearchResult : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [in] */ RTC_USER_SEARCH_COLUMN enColumn,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCUserSearchResultVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCUserSearchResult __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCUserSearchResult __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCUserSearchResult __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IRTCUserSearchResult __RPC_FAR * This,
            /* [in] */ RTC_USER_SEARCH_COLUMN enColumn,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        END_INTERFACE
    } IRTCUserSearchResultVtbl;

    interface IRTCUserSearchResult
    {
        CONST_VTBL struct IRTCUserSearchResultVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCUserSearchResult_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCUserSearchResult_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCUserSearchResult_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCUserSearchResult_get_Value(This,enColumn,pbstrValue)	\
    (This)->lpVtbl -> get_Value(This,enColumn,pbstrValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchResult_get_Value_Proxy( 
    IRTCUserSearchResult __RPC_FAR * This,
    /* [in] */ RTC_USER_SEARCH_COLUMN enColumn,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);


void __RPC_STUB IRTCUserSearchResult_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCUserSearchResult_INTERFACE_DEFINED__ */


#ifndef __IRTCEnumUserSearchResults_INTERFACE_DEFINED__
#define __IRTCEnumUserSearchResults_INTERFACE_DEFINED__

/* interface IRTCEnumUserSearchResults */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCEnumUserSearchResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("83D4D877-AA5D-4a5b-8D0E-002A8067E0E8")
    IRTCEnumUserSearchResults : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCUserSearchResult __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IRTCEnumUserSearchResults __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCEnumUserSearchResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCEnumUserSearchResults __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCEnumUserSearchResults __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCEnumUserSearchResults __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IRTCEnumUserSearchResults __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCUserSearchResult __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IRTCEnumUserSearchResults __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IRTCEnumUserSearchResults __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IRTCEnumUserSearchResults __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumUserSearchResults __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IRTCEnumUserSearchResultsVtbl;

    interface IRTCEnumUserSearchResults
    {
        CONST_VTBL struct IRTCEnumUserSearchResultsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCEnumUserSearchResults_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCEnumUserSearchResults_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCEnumUserSearchResults_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCEnumUserSearchResults_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IRTCEnumUserSearchResults_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IRTCEnumUserSearchResults_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IRTCEnumUserSearchResults_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRTCEnumUserSearchResults_Next_Proxy( 
    IRTCEnumUserSearchResults __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [size_is][out] */ IRTCUserSearchResult __RPC_FAR *__RPC_FAR *ppElements,
    /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IRTCEnumUserSearchResults_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumUserSearchResults_Reset_Proxy( 
    IRTCEnumUserSearchResults __RPC_FAR * This);


void __RPC_STUB IRTCEnumUserSearchResults_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumUserSearchResults_Skip_Proxy( 
    IRTCEnumUserSearchResults __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IRTCEnumUserSearchResults_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumUserSearchResults_Clone_Proxy( 
    IRTCEnumUserSearchResults __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumUserSearchResults __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCEnumUserSearchResults_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCEnumUserSearchResults_INTERFACE_DEFINED__ */


#ifndef __IRTCUserSearchResultsEvent_INTERFACE_DEFINED__
#define __IRTCUserSearchResultsEvent_INTERFACE_DEFINED__

/* interface IRTCUserSearchResultsEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCUserSearchResultsEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D8C8C3CD-7FAC-4088-81C5-C24CBC0938E3")
    IRTCUserSearchResultsEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE EnumerateResults( 
            /* [retval][out] */ IRTCEnumUserSearchResults __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Results( 
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Query( 
            /* [retval][out] */ IRTCUserSearchQuery __RPC_FAR *__RPC_FAR *ppQuery) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cookie( 
            /* [retval][out] */ LONG_PTR __RPC_FAR *plCookie) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MoreAvailable( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMoreAvailable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCUserSearchResultsEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateResults )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumUserSearchResults __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Results )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Query )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCUserSearchQuery __RPC_FAR *__RPC_FAR *ppQuery);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cookie )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [retval][out] */ LONG_PTR __RPC_FAR *plCookie);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MoreAvailable )( 
            IRTCUserSearchResultsEvent __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMoreAvailable);
        
        END_INTERFACE
    } IRTCUserSearchResultsEventVtbl;

    interface IRTCUserSearchResultsEvent
    {
        CONST_VTBL struct IRTCUserSearchResultsEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCUserSearchResultsEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCUserSearchResultsEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCUserSearchResultsEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCUserSearchResultsEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCUserSearchResultsEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCUserSearchResultsEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCUserSearchResultsEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCUserSearchResultsEvent_EnumerateResults(This,ppEnum)	\
    (This)->lpVtbl -> EnumerateResults(This,ppEnum)

#define IRTCUserSearchResultsEvent_get_Results(This,ppCollection)	\
    (This)->lpVtbl -> get_Results(This,ppCollection)

#define IRTCUserSearchResultsEvent_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#define IRTCUserSearchResultsEvent_get_Query(This,ppQuery)	\
    (This)->lpVtbl -> get_Query(This,ppQuery)

#define IRTCUserSearchResultsEvent_get_Cookie(This,plCookie)	\
    (This)->lpVtbl -> get_Cookie(This,plCookie)

#define IRTCUserSearchResultsEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCUserSearchResultsEvent_get_MoreAvailable(This,pfMoreAvailable)	\
    (This)->lpVtbl -> get_MoreAvailable(This,pfMoreAvailable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchResultsEvent_EnumerateResults_Proxy( 
    IRTCUserSearchResultsEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumUserSearchResults __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCUserSearchResultsEvent_EnumerateResults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchResultsEvent_get_Results_Proxy( 
    IRTCUserSearchResultsEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCCollection __RPC_FAR *__RPC_FAR *ppCollection);


void __RPC_STUB IRTCUserSearchResultsEvent_get_Results_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchResultsEvent_get_Profile_Proxy( 
    IRTCUserSearchResultsEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCProfile2 __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB IRTCUserSearchResultsEvent_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchResultsEvent_get_Query_Proxy( 
    IRTCUserSearchResultsEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCUserSearchQuery __RPC_FAR *__RPC_FAR *ppQuery);


void __RPC_STUB IRTCUserSearchResultsEvent_get_Query_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchResultsEvent_get_Cookie_Proxy( 
    IRTCUserSearchResultsEvent __RPC_FAR * This,
    /* [retval][out] */ LONG_PTR __RPC_FAR *plCookie);


void __RPC_STUB IRTCUserSearchResultsEvent_get_Cookie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchResultsEvent_get_StatusCode_Proxy( 
    IRTCUserSearchResultsEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCUserSearchResultsEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCUserSearchResultsEvent_get_MoreAvailable_Proxy( 
    IRTCUserSearchResultsEvent __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMoreAvailable);


void __RPC_STUB IRTCUserSearchResultsEvent_get_MoreAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCUserSearchResultsEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCSessionReferStatusEvent_INTERFACE_DEFINED__
#define __IRTCSessionReferStatusEvent_INTERFACE_DEFINED__

/* interface IRTCSessionReferStatusEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCSessionReferStatusEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3D8FC2CD-5D76-44AB-BB68-2A80353B34A2")
    IRTCSessionReferStatusEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReferStatus( 
            /* [retval][out] */ RTC_SESSION_REFER_STATUS __RPC_FAR *penReferStatus) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusCode( 
            /* [retval][out] */ long __RPC_FAR *plStatusCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCSessionReferStatusEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCSessionReferStatusEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCSessionReferStatusEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCSessionReferStatusEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCSessionReferStatusEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCSessionReferStatusEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCSessionReferStatusEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCSessionReferStatusEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IRTCSessionReferStatusEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReferStatus )( 
            IRTCSessionReferStatusEvent __RPC_FAR * This,
            /* [retval][out] */ RTC_SESSION_REFER_STATUS __RPC_FAR *penReferStatus);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusCode )( 
            IRTCSessionReferStatusEvent __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStatusCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IRTCSessionReferStatusEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);
        
        END_INTERFACE
    } IRTCSessionReferStatusEventVtbl;

    interface IRTCSessionReferStatusEvent
    {
        CONST_VTBL struct IRTCSessionReferStatusEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCSessionReferStatusEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCSessionReferStatusEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCSessionReferStatusEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCSessionReferStatusEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCSessionReferStatusEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCSessionReferStatusEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCSessionReferStatusEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCSessionReferStatusEvent_get_Session(This,ppSession)	\
    (This)->lpVtbl -> get_Session(This,ppSession)

#define IRTCSessionReferStatusEvent_get_ReferStatus(This,penReferStatus)	\
    (This)->lpVtbl -> get_ReferStatus(This,penReferStatus)

#define IRTCSessionReferStatusEvent_get_StatusCode(This,plStatusCode)	\
    (This)->lpVtbl -> get_StatusCode(This,plStatusCode)

#define IRTCSessionReferStatusEvent_get_StatusText(This,pbstrStatusText)	\
    (This)->lpVtbl -> get_StatusText(This,pbstrStatusText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionReferStatusEvent_get_Session_Proxy( 
    IRTCSessionReferStatusEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession);


void __RPC_STUB IRTCSessionReferStatusEvent_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionReferStatusEvent_get_ReferStatus_Proxy( 
    IRTCSessionReferStatusEvent __RPC_FAR * This,
    /* [retval][out] */ RTC_SESSION_REFER_STATUS __RPC_FAR *penReferStatus);


void __RPC_STUB IRTCSessionReferStatusEvent_get_ReferStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionReferStatusEvent_get_StatusCode_Proxy( 
    IRTCSessionReferStatusEvent __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStatusCode);


void __RPC_STUB IRTCSessionReferStatusEvent_get_StatusCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionReferStatusEvent_get_StatusText_Proxy( 
    IRTCSessionReferStatusEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrStatusText);


void __RPC_STUB IRTCSessionReferStatusEvent_get_StatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCSessionReferStatusEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCSessionReferredEvent_INTERFACE_DEFINED__
#define __IRTCSessionReferredEvent_INTERFACE_DEFINED__

/* interface IRTCSessionReferredEvent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCSessionReferredEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("176A6828-4FCC-4F28-A862-04597A6CF1C4")
    IRTCSessionReferredEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReferredByURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferredByURI) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReferToURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferoURI) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReferCookie( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferCookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Accept( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reject( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetReferredSessionState( 
            /* [in] */ RTC_SESSION_STATE enState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCSessionReferredEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCSessionReferredEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCSessionReferredEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCSessionReferredEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCSessionReferredEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCSessionReferredEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCSessionReferredEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCSessionReferredEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IRTCSessionReferredEvent __RPC_FAR * This,
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReferredByURI )( 
            IRTCSessionReferredEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferredByURI);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReferToURI )( 
            IRTCSessionReferredEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferoURI);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReferCookie )( 
            IRTCSessionReferredEvent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Accept )( 
            IRTCSessionReferredEvent __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reject )( 
            IRTCSessionReferredEvent __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetReferredSessionState )( 
            IRTCSessionReferredEvent __RPC_FAR * This,
            /* [in] */ RTC_SESSION_STATE enState);
        
        END_INTERFACE
    } IRTCSessionReferredEventVtbl;

    interface IRTCSessionReferredEvent
    {
        CONST_VTBL struct IRTCSessionReferredEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCSessionReferredEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCSessionReferredEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCSessionReferredEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCSessionReferredEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCSessionReferredEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCSessionReferredEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCSessionReferredEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTCSessionReferredEvent_get_Session(This,ppSession)	\
    (This)->lpVtbl -> get_Session(This,ppSession)

#define IRTCSessionReferredEvent_get_ReferredByURI(This,pbstrReferredByURI)	\
    (This)->lpVtbl -> get_ReferredByURI(This,pbstrReferredByURI)

#define IRTCSessionReferredEvent_get_ReferToURI(This,pbstrReferoURI)	\
    (This)->lpVtbl -> get_ReferToURI(This,pbstrReferoURI)

#define IRTCSessionReferredEvent_get_ReferCookie(This,pbstrReferCookie)	\
    (This)->lpVtbl -> get_ReferCookie(This,pbstrReferCookie)

#define IRTCSessionReferredEvent_Accept(This)	\
    (This)->lpVtbl -> Accept(This)

#define IRTCSessionReferredEvent_Reject(This)	\
    (This)->lpVtbl -> Reject(This)

#define IRTCSessionReferredEvent_SetReferredSessionState(This,enState)	\
    (This)->lpVtbl -> SetReferredSessionState(This,enState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionReferredEvent_get_Session_Proxy( 
    IRTCSessionReferredEvent __RPC_FAR * This,
    /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppSession);


void __RPC_STUB IRTCSessionReferredEvent_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionReferredEvent_get_ReferredByURI_Proxy( 
    IRTCSessionReferredEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrReferredByURI);


void __RPC_STUB IRTCSessionReferredEvent_get_ReferredByURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionReferredEvent_get_ReferToURI_Proxy( 
    IRTCSessionReferredEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrReferoURI);


void __RPC_STUB IRTCSessionReferredEvent_get_ReferToURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRTCSessionReferredEvent_get_ReferCookie_Proxy( 
    IRTCSessionReferredEvent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrReferCookie);


void __RPC_STUB IRTCSessionReferredEvent_get_ReferCookie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCSessionReferredEvent_Accept_Proxy( 
    IRTCSessionReferredEvent __RPC_FAR * This);


void __RPC_STUB IRTCSessionReferredEvent_Accept_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCSessionReferredEvent_Reject_Proxy( 
    IRTCSessionReferredEvent __RPC_FAR * This);


void __RPC_STUB IRTCSessionReferredEvent_Reject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCSessionReferredEvent_SetReferredSessionState_Proxy( 
    IRTCSessionReferredEvent __RPC_FAR * This,
    /* [in] */ RTC_SESSION_STATE enState);


void __RPC_STUB IRTCSessionReferredEvent_SetReferredSessionState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCSessionReferredEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCSessionDescriptionManager_INTERFACE_DEFINED__
#define __IRTCSessionDescriptionManager_INTERFACE_DEFINED__

/* interface IRTCSessionDescriptionManager */
/* [unique][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCSessionDescriptionManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BA7F518E-D336-4070-93A6-865395C843F9")
    IRTCSessionDescriptionManager : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EvaluateSessionDescription( 
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription,
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *pfApplicationSession) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCSessionDescriptionManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCSessionDescriptionManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCSessionDescriptionManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCSessionDescriptionManager __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EvaluateSessionDescription )( 
            IRTCSessionDescriptionManager __RPC_FAR * This,
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription,
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *pfApplicationSession);
        
        END_INTERFACE
    } IRTCSessionDescriptionManagerVtbl;

    interface IRTCSessionDescriptionManager
    {
        CONST_VTBL struct IRTCSessionDescriptionManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCSessionDescriptionManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCSessionDescriptionManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCSessionDescriptionManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCSessionDescriptionManager_EvaluateSessionDescription(This,bstrContentType,bstrSessionDescription,pfApplicationSession)	\
    (This)->lpVtbl -> EvaluateSessionDescription(This,bstrContentType,bstrSessionDescription,pfApplicationSession)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTCSessionDescriptionManager_EvaluateSessionDescription_Proxy( 
    IRTCSessionDescriptionManager __RPC_FAR * This,
    /* [in] */ BSTR bstrContentType,
    /* [in] */ BSTR bstrSessionDescription,
    /* [out][in] */ VARIANT_BOOL __RPC_FAR *pfApplicationSession);


void __RPC_STUB IRTCSessionDescriptionManager_EvaluateSessionDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCSessionDescriptionManager_INTERFACE_DEFINED__ */


#ifndef __IRTCEnumPresenceDevices_INTERFACE_DEFINED__
#define __IRTCEnumPresenceDevices_INTERFACE_DEFINED__

/* interface IRTCEnumPresenceDevices */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_IRTCEnumPresenceDevices;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("708C2AB7-8BF8-42f8-8C7D-635197AD5539")
    IRTCEnumPresenceDevices : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCPresenceDevice __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IRTCEnumPresenceDevices __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCEnumPresenceDevicesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCEnumPresenceDevices __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCEnumPresenceDevices __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCEnumPresenceDevices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IRTCEnumPresenceDevices __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [size_is][out] */ IRTCPresenceDevice __RPC_FAR *__RPC_FAR *ppElements,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IRTCEnumPresenceDevices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IRTCEnumPresenceDevices __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IRTCEnumPresenceDevices __RPC_FAR * This,
            /* [retval][out] */ IRTCEnumPresenceDevices __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IRTCEnumPresenceDevicesVtbl;

    interface IRTCEnumPresenceDevices
    {
        CONST_VTBL struct IRTCEnumPresenceDevicesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCEnumPresenceDevices_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCEnumPresenceDevices_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCEnumPresenceDevices_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCEnumPresenceDevices_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IRTCEnumPresenceDevices_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IRTCEnumPresenceDevices_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IRTCEnumPresenceDevices_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRTCEnumPresenceDevices_Next_Proxy( 
    IRTCEnumPresenceDevices __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [size_is][out] */ IRTCPresenceDevice __RPC_FAR *__RPC_FAR *ppElements,
    /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IRTCEnumPresenceDevices_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumPresenceDevices_Reset_Proxy( 
    IRTCEnumPresenceDevices __RPC_FAR * This);


void __RPC_STUB IRTCEnumPresenceDevices_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumPresenceDevices_Skip_Proxy( 
    IRTCEnumPresenceDevices __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IRTCEnumPresenceDevices_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTCEnumPresenceDevices_Clone_Proxy( 
    IRTCEnumPresenceDevices __RPC_FAR * This,
    /* [retval][out] */ IRTCEnumPresenceDevices __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IRTCEnumPresenceDevices_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCEnumPresenceDevices_INTERFACE_DEFINED__ */


#ifndef __IRTCPresenceDevice_INTERFACE_DEFINED__
#define __IRTCPresenceDevice_INTERFACE_DEFINED__

/* interface IRTCPresenceDevice */
/* [unique][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRTCPresenceDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BC6A90DD-AD9A-48da-9B0C-2515E38521AD")
    IRTCPresenceDevice : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Notes( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNotes) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PresenceProperty( 
            /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProperty) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPresenceData( 
            /* [out] */ BSTR __RPC_FAR *pbstrNamespace,
            /* [out] */ BSTR __RPC_FAR *pbstrData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTCPresenceDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCPresenceDevice __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCPresenceDevice __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCPresenceDevice __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IRTCPresenceDevice __RPC_FAR * This,
            /* [retval][out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Notes )( 
            IRTCPresenceDevice __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNotes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PresenceProperty )( 
            IRTCPresenceDevice __RPC_FAR * This,
            /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProperty);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPresenceData )( 
            IRTCPresenceDevice __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrNamespace,
            /* [out] */ BSTR __RPC_FAR *pbstrData);
        
        END_INTERFACE
    } IRTCPresenceDeviceVtbl;

    interface IRTCPresenceDevice
    {
        CONST_VTBL struct IRTCPresenceDeviceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCPresenceDevice_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCPresenceDevice_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCPresenceDevice_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCPresenceDevice_get_Status(This,penStatus)	\
    (This)->lpVtbl -> get_Status(This,penStatus)

#define IRTCPresenceDevice_get_Notes(This,pbstrNotes)	\
    (This)->lpVtbl -> get_Notes(This,pbstrNotes)

#define IRTCPresenceDevice_get_PresenceProperty(This,enProperty,pbstrProperty)	\
    (This)->lpVtbl -> get_PresenceProperty(This,enProperty,pbstrProperty)

#define IRTCPresenceDevice_GetPresenceData(This,pbstrNamespace,pbstrData)	\
    (This)->lpVtbl -> GetPresenceData(This,pbstrNamespace,pbstrData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresenceDevice_get_Status_Proxy( 
    IRTCPresenceDevice __RPC_FAR * This,
    /* [retval][out] */ RTC_PRESENCE_STATUS __RPC_FAR *penStatus);


void __RPC_STUB IRTCPresenceDevice_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresenceDevice_get_Notes_Proxy( 
    IRTCPresenceDevice __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrNotes);


void __RPC_STUB IRTCPresenceDevice_get_Notes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRTCPresenceDevice_get_PresenceProperty_Proxy( 
    IRTCPresenceDevice __RPC_FAR * This,
    /* [in] */ RTC_PRESENCE_PROPERTY enProperty,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrProperty);


void __RPC_STUB IRTCPresenceDevice_get_PresenceProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRTCPresenceDevice_GetPresenceData_Proxy( 
    IRTCPresenceDevice __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrNamespace,
    /* [out] */ BSTR __RPC_FAR *pbstrData);


void __RPC_STUB IRTCPresenceDevice_GetPresenceData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTCPresenceDevice_INTERFACE_DEFINED__ */



#ifndef __RTCCORELib_LIBRARY_DEFINED__
#define __RTCCORELib_LIBRARY_DEFINED__

/* library RTCCORELib */
/* [helpstring][version][uuid] */ 























































EXTERN_C const IID LIBID_RTCCORELib;

#ifndef __IRTCDispatchEventNotification_DISPINTERFACE_DEFINED__
#define __IRTCDispatchEventNotification_DISPINTERFACE_DEFINED__

/* dispinterface IRTCDispatchEventNotification */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IRTCDispatchEventNotification;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("176ddfbe-fec0-4d55-bc87-84cff1ef7f91")
    IRTCDispatchEventNotification : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IRTCDispatchEventNotificationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTCDispatchEventNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTCDispatchEventNotification __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTCDispatchEventNotification __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRTCDispatchEventNotification __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRTCDispatchEventNotification __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRTCDispatchEventNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRTCDispatchEventNotification __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IRTCDispatchEventNotificationVtbl;

    interface IRTCDispatchEventNotification
    {
        CONST_VTBL struct IRTCDispatchEventNotificationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCDispatchEventNotification_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTCDispatchEventNotification_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTCDispatchEventNotification_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTCDispatchEventNotification_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTCDispatchEventNotification_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTCDispatchEventNotification_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTCDispatchEventNotification_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IRTCDispatchEventNotification_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_RTCClient;

#ifdef __cplusplus

class DECLSPEC_UUID("7a42ea29-a2b7-40c4-b091-f6f024aa89be")
RTCClient;
#endif
#endif /* __RTCCORELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


