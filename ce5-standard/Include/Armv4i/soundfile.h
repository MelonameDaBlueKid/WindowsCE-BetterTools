//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

// **************************************************************************
//  APIs for dealing with system sounds
//
//  SndGetSoundDirectoriesList       Gets a list of available directories for
//                                   an indicated sound event and memory
//                                   location(s).
//  SndGetSoundFileList              Gets a list of sounds for an indicated 
//                                   event currently available.
//  SndSetSound                      Sets sound for an indicated event
//  SndGetSound                      Gets current sound for indicated event
// **************************************************************************

#ifndef _SOUNDFILE_H_
#define _SOUNDFILE_H_

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */



// **************************************************************************
// SND_SOUNDTYPE
// 
// Purpose: This enum indicates the type of sound for the SNDFILEINFO 
//          structure.
//
// **************************************************************************
typedef enum tagSND_SOUNDTYPE
{
    SND_SOUNDTYPE_ON,             // If sound is currently Vibrate or None this will restore the 
                                  // sound to the previous value. This is only valid for the SND_EVENT_ALL
                                  // SND_EVENT.
    SND_SOUNDTYPE_FILE,           // Soundfile will be specified by SNDFILEINFO.szPathName
    SND_SOUNDTYPE_VIBRATE,        // Sound is vibration.  SNDFILEINFO.szPathName is ignored.
    SND_SOUNDTYPE_NONE,           // No sound (silence).  SNDFILEINFO.szPathName is ignored.
    SND_SOUNDTYPE_DISABLE,        // Only applies to SND_EVENTs for KNOWNCALLER and ROAMING
                                  // Sound will be disabled and behavior will revert back to default.
    
    SND_SOUNDTYPE_LAST = SND_SOUNDTYPE_DISABLE
} SND_SOUNDTYPE;





// **************************************************************************
// SNDFILEINFO
// 
// Purpose: This structure is used to set and retrieve information about 
//          event sounds.
//
// Fields:
//      [in/out] TCHAR szPathName[MAX_PATH]
//          A pointer to a string indicating the fully qualified
//          path to the sound file.
//
//      [in/out] TCHAR szDisplayName[MAX_PATH]
//          A pointer to a string indicating the friendly name of a 
//          sound file, that is the name of the file without extension
//          or path. When used with SndSetSoundFile, szDisplayName is ignored.
//
//      [in/out] SND_SOUNDTYPE sstType
//          An enum indicating the type of sound that is played for the event.
//          If this is not equal to SND_SOUNDTYPE_FILE, szPathName is ignored.
// **************************************************************************
typedef struct tagSNDFILEINFO
{
    TCHAR szPathName[MAX_PATH];
    TCHAR szDisplayName[MAX_PATH];
    SND_SOUNDTYPE sstType;    
} SNDFILEINFO;





// **************************************************************************
// SNDDIRECTORYINFO
// 
// Purpose: This structure is returned when querying for directories for
//          sound events.
//
// Fields:
//      [in/out] TCHAR szPathName[MAX_PATH]
//          A string indicating the fully qualified
//          path to the directory containing sound files.
//
//
// Notes:   This struct is used with SndGetSoundDirectoriesList.
//
//
// Description:
// **************************************************************************
typedef struct tagSNDDIRECTORYINFO
{
    TCHAR szPathName[MAX_PATH];
} SNDDIRECTORYINFO;






// **************************************************************************
// SND_EVENT
// 
// Purpose: This enum indicates which sound event type the user wishes to
//          set or query.
//
// **************************************************************************
typedef enum tagSND_EVENT
{
    SND_EVENT_ALL,                       // This is a special sound event that applies to all sounds
                                         // on a system wide scale. Currently only supported on Pocket PC, the
                                         // only valid values for SNDFILEINFO.sstType are SND_SOUNDTYPE_ON,
                                         // SND_SOUNDTYPE_VIBRATE, and SND_SOUNDTYPE_NONE. Invoking SndSetSound
                                         // with SND_EVENT_ALL and a SNDFILEINFO struct set to one of the above
                                         // values will be equivalent to the user using the Pocket PC Volume Bubble
                                         // on the home screen. If the volume bubble is currently open the change will
                                         // be reflected in the bubble right away. If the bubble is not open the change
                                         // will take effect immediately and will be visible the next time the user
                                         // opens the bubble.
    SND_EVENT_RINGTONELINE1,             // The ringtone for line 1 of the phone
    SND_EVENT_RINGTONELINE2,             // The ringtone for line 2 of the phone
    SND_EVENT_KNOWNCALLERRINGTONELINE1,  // The ringtone to play for a caller in the contact list who has no contact-specific ring tone.
                                         // This event does not support the "vibrate" and "none" sound types
                                         // Currently applies to both lines without distinction
    SND_EVENT_ROAMINGRINGTONELINE1,      // The ringtone to play while roaming.  This has higher priority than other ring tones.
                                         // This event does not support the "vibrate" and "none" sound types
                                         // Currently applies to both lines without distinction
    
    SND_EVENT_LAST = SND_EVENT_ROAMINGRINGTONELINE1
} SND_EVENT;


// **************************************************************************
// Bitmasks for SndGetSoundFileList and SndGetSoundDirectoriesList
// **************************************************************************
#define SND_LOCATION_STORAGECARD 0x01 // Retrieve sound files or directories from 
                                      // the storage card.  For some sound events,
                                      // this may not be a valid location.
#define SND_LOCATION_USERDATA    0x02 // Retrieve sound files in userdata (
                                      // \My Documents and
                                      // \Application Data\Sounds\ or
                                      // \Storage Application Data for persistent
                                      // store devices)
#define SND_LOCATION_ROM         0x04 // Retrieve sound files in ROM.

#define SND_LOCATION_ALL         0xFFFFFFFF
                                      // A combination of all locations.  Return all.



// **************************************************************************
// Function Name:   SndGetSoundDirectoriesList
// 
// Purpose: Returns an array of possible directories for sound files for the
//          specified sound event type and memory location.
//
// Arguments:
//      [in] seSoundEvent
//          Indicates the type of sound event you wish to query for.
//
//      [in] grfLocations
//          Indicates which locations in memory are searched for sound.
//          directories.  See the bitfields adove for a description.
//
//      [out] ppSoundDirectories
//          A pointer to an array of sound directories.  This function will 
//          create the array of SNDDIRECTORYINFO's, and allocate the  
//          appropriate amount of memory.  User is resposible for freeing 
//          this memory by calling LocalFree on the returned pointer.
//
//      [out] pcSoundDirectories
//          A pointer to an int indicated number of SNDDIRECTORYINFO
//          objects created and returned in ppSoundDirectories.
//
// Return Values:
//      HRESULT
//          This function is free to return any HRESULT and the application 
//          should use the SUCCEEDED/FAILED macros to check the results. 
//
// Description:     
//          This function allows an application to query the directories
//          where sound files should be copied to for any of the sound events 
//          listed in the enum SND_EVENT. The fully qualified path for 
//          the directory is returned. This function allocates
//          memory for all SNDDIRECTORYINFO's as one contiguous 
//          block.  User is responsible for freeing all memory returned by 
//          this function by calling LocalFree on the returned pointer.
// **************************************************************************
HRESULT SndGetSoundDirectoriesList( SND_EVENT seSoundEvent,
                                    DWORD grfLocations, 
                                    SNDDIRECTORYINFO** ppSoundDirectories, 
                                    int* pcSoundDirectories);






// **************************************************************************
// Function Name:   SndGetSoundFileList
// 
// Purpose: Returns an array of available soundfiles on the device for the
//          specified sound event.
//
// Arguments:
//      [in] seSoundEvent
//          Indicates the type of sound event you wish to query for.
//
//      [in] grfLocations
//          Indicates which locations in memory are searched for sound files.
//          See the bitfields above for a description.
//
//      [out] ppSoundFiles
//          A pointer to an array of sound files.  This function will create 
//          the array of SNDFILEINFO's, and allocate the appropriate amount
//          of memory.  User is resposible for freeing this memory
//          by calling LocalFree.
//
//      [out] pcSoundFiles
//          A pointer to an int indicating number of SNDFILEINFO
//          objects created and returned in ppSoundFiles.
//
// Return Values:
//      HRESULT
//          This function is free to return any HRESULT and the application 
//          should use the SUCCEEDED/FAILED macros to check the results. 
//
// Description:     
//          This function allows an application to query sound files
//          available to the device for any of the sound events listed
//          in the enum SND_EVENT.  By specifying the appropriate
//          bitfield, sound files can be retrieved from all valid
//          sound file storage locations.  The fully qualified file path and
//          friendly file name are returned for each sound file. This function
//          allocates memory for all SNDFILEINFO's as one contiguous 
//          block.  User is responsible for freeing all memory returned by 
//          this function by calling LocalFree on the returned pointer.
// **************************************************************************
HRESULT SndGetSoundFileList(SND_EVENT seSoundEvent,
                            DWORD grfLocations, 
                            SNDFILEINFO** ppSoundFiles, 
                            int* pcSoundFiles);




// **************************************************************************
// Function Name:   SndSetSound
// 
// Purpose: Sets the current sound file for the indicated event.
//
// Arguments:
//      [in] seSoundEvent
//          Indicates which type of sound event the user wishes to set.
//
//      [in] pSoundFileInfo
//          A pointer to a SNDFILEINFO which indicates
//          the file that the user wishes to set as the indicated sound.
//          The fully qualified path should be included.  szDisplayName
//          is ignored.
//
//      [in] fSuppressUI
//          Determines if error message should be displayed if the
//          function fails to set the current sound file.  This error
//          message would only appear in the case of failure.
//
// Return Values:
//      HRESULT
//          This function is free to return any HRESULT and the application 
//          should use the SUCCEEDED/FAILED macros to check the results.
//
//        
// Description:     
//          This function sets the current sound file for the appropriate
//          event.  This function can fail and will not change the current
//          sound file if it determines it is unable to play the sound file
//          for any reason.  It will also fail if the sound file is not in
//          an appropriate sounds directory.  It will fail if a sound file
//          is in the ROM sounds directory, unless it is returned by
//          SndGetSoundFileList.  If fSuppressUI is true, no user interface
//          will be displayed explaining reasons that the sound file could
//          not be set.  If it is false, then a dialog may appear explaining
//          the reason the sound file could not be set (such as insufficient
//          digital rights, an invalid file, etc).
//
// Note:
//          The SND_EVENT_ALL event type and corresponding SND_SOUNDTYPE values
//          are currently only supported on Pocket PC.
// **************************************************************************
HRESULT SndSetSound(SND_EVENT seSoundEvent,
                    const SNDFILEINFO* pSoundFileInfo,
                    BOOL fSuppressUI);




// **************************************************************************
// Function Name:   SndGetSound
// 
// Purpose:         Returns the current sound file for the indicated sound
//                  event.
//
// Arguments:      
//      [in] seSoundEvent
//          Indicates the type of sound event you wish to query.
//
//      [out] pSoundFileInfo
//          Caller should pass in a pointer to a SNDFILEINFO object 
//          that will be filled in by this function.  
//
// Return Values:
//      HRESULT
//          This function is free to return any HRESULT and the application 
//          should use the SUCCEEDED/FAILED macros to check the results. 
//
// Description:
//          This function returns the current sound file for the specified 
//          sound event. The fully qualified file path along with the 
//          friendly file name of the sound event file are returned in 
//          pSoundFileInfo.  This function needs a pointer to a valid 
//          SNDFILEINFO structure.
//
// Note:
//          The SND_EVENT_ALL event type and corresponding SND_SOUNDTYPE values
//          are currently only supported on Pocket PC.
// **************************************************************************
HRESULT SndGetSound(SND_EVENT seSoundEvent,
                    SNDFILEINFO* pSoundFileInfo);


#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // _SOUNDFILE_H_

