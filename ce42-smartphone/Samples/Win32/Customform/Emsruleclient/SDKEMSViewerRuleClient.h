/******************************************************************************

	File: SDKEMSViewerRuleClient.h
    
    Purpose: Class and macros definitions for EMS rule client

    Author: Matthew S. Baker (mbaker)

    Date: 11/7/2002

******************************************************************************/
#pragma once
#pragma warning(disable : 4201)
#pragma warning(disable : 4512)
#pragma warning(disable : 4245)
#pragma warning(disable : 4063)
#include <windows.h>
#include <stdlib.h>
#include <cemapi.h>

//MACROS///////////////////////////////////////////////////////////////////////
#define CountOf(p) (sizeof(p) / sizeof(*(p)))
#define SAFE_RELEASE(p) if(p){p->Release(); p=NULL;}
#define SAFE_DELETE(p) if(p){delete p; p=NULL;}
#define CBR(fResult, bRet) do {if (!(fResult)){bRet = FALSE; goto Exit;}} while(0,0)
#define CBRH(fResult, hr) do {if (!(fResult)){hr = E_FAIL; goto Exit;}} while(0,0)

#define STR_EMSID _T("{0FB7FE4F-BC3C-41ef-9B86-E916F5C25CA6}")

/*Information Element Identifiers, defined in "3GPP TS 23.040 V4.3.0 (2001-06)"
These are the ones of interest in processing EMS messages*/
#define IEI_MULTI_8BIT          0x00    //Present only if multipart SM
#define IEI_MULTI_16BIT         0x08    //ditto, but ID is 2 octets
#define IEI_TEXT_FORMATTING     0x0A    //Text formatting info
#define IEI_PREDEFINED_SOUND    0x0B    //System defined sound
#define IEI_USERDEFINED_SOUND   0x0C    //custom sound data (max 128 bytes)
#define IEI_PREDEFINED_ANIM     0x0D    //System defined animation
#define IEI_LARGE_ANIM          0x0E    //custom animation 32x32x4
#define IEI_SMALL_ANIM          0x0F    //custom animation 16x16x4
#define IEI_LARGE_PICTURE       0x10    //32x32 picture
#define IEI_SMALL_PICTURE       0x11    //16x16 picture
#define IEI_VARIABLE_PICTURE    0x12    //NxN picture
#define IEI_USER_PROMPT         0x13    //Notification to prompt user

#define IEI_TEXT_ONLY           0xFF    //NOT 3GPP defined, but we only use
                                        //it on incoming data, not sent out

#define PICTURE_RES_LARGE       32      //Dimensions of LARGE PICTURE
#define PICTURE_RES_SMALL       16      //Dimensions of SMALL PICTURE
#define MAX_IMELODY_LEN         128     //Max byte length of iMelody data
#define BASE_HEX                16      //Hex base for _itot
#define BASE_BIN                2       //Binary base for _itot
#define NUM_ANIM_FRAMES         4       //Frames in animation sequence

#define MAX_EMS_HEADERS         255     //Max parts of Multipart SM

typedef HRESULT (*FPCREATEINSTANCE)(IUnknown*, IUnknown**);

typedef union _SMREFIDVAL {
    BYTE chRefID;           //8-bit ID
    WORD wRefID;            //16-bit ID
} SMREFIDVAL, *LPSMREFIDVAL;

typedef struct _EMSHEADERINFO {
    LPBYTE      lpData;     //Header buffer
    UINT        cbData;     //Size of buffer
    LPTSTR      pszUserData;//Text string in SM
    UINT        uNumParts;  //Number of parts in SM
    UINT        uCurrPart;  //Current part
    BOOL        fMultiPart; //TRUE if part of larger message
    BOOL        fRef16Bit;  //TRUE if using 16bit ref id
    SMREFIDVAL  smRefIDVal; //ID, valid only if fMultiPart is TRUE
} EMSHEADERINFO, *LPEMSHEADERINFO;

#define FREE_EMSHEADERINFO(p) {if(NULL != p.lpData){free(p.lpData); p.lpData = NULL;}\
    if(NULL != p.pszUserData){free(p.pszUserData);}memset(&p, 0, sizeof(p));}

/******************************************************************************

    CFactoryData - Each component hosted by CFactory in the DLL must register
    with the global varibale g_rgFactoryData, which is a collection of the info
    in this class.  This info is needed so one generic class factory can create
    several different components (as oppossed to having to write a class factory
    for each one - which is boring and repetitive).

    The global variable, g_rgFactoryData, is in SDKEMSViewerRuleClient.cpp

******************************************************************************/
class CFactoryData
{
public:
    //CLSID of component
    const CLSID* m_pCLSID;

    //Pointer to function that creates component
    FPCREATEINSTANCE CreateInstance;        
    
    //Helper to check CLSID
    BOOL IsClassID(const CLSID& clsid) const { return (*m_pCLSID == clsid); }
};


/******************************************************************************

    CFactory - Generic class factory for all the components in this DLL.  The
    sharing magic is accomplished by the GetClassObject method, called by
    DllGetClassObject, which will look up the CLSID in the supported components
    global array and create the proper class factory.

******************************************************************************/
class CFactory : public IClassFactory
{
public:
    CFactory(const CFactoryData* pFData);
    ~CFactory();
    
    //IUnknown interface
    STDMETHOD (QueryInterface)(const IID& iid, LPVOID *ppv);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    //IClassFactory interface
    STDMETHOD (CreateInstance)(IUnknown *pUnknownOuter, const IID& iid, LPVOID *ppv);
    STDMETHOD (LockServer)(BOOL bLock);

    //Called by DllGetClassObject
    static HRESULT GetClassObject(const CLSID& clsid, const IID& iid, void** ppv);

private:
    long m_cRef;                //object reference count
    CFactoryData m_FactoryData; //info needed to create the correct component
                                //provided by GetClassObject() method
};

/******************************************************************************

    CRuleClientBase - Rule client base class.  It implements IUnknown goo, and
    some basic functionality.  Derived classes implement the IMailRuleClient 
    methods.

******************************************************************************/
class CRuleClientBase : public IMailRuleClient
{    
protected:    
    CRuleClientBase();
    virtual ~CRuleClientBase();

    //IUnknown interface
    STDMETHOD (QueryInterface)(const IID& iid, LPVOID *ppv);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    //Derived classes need to override these
    MAPIMETHOD(Initialize)(
            IMsgStore *pMsgStore,
            MRCACCESS *pmaDesired
            );
            
    MAPIMETHOD(ProcessMessage)(
            IMsgStore *pMsgStore, 
            ULONG cbMsg,
            LPENTRYID lpMsg,
            ULONG cbDestFolder,
            LPENTRYID lpDestFolder,
            ULONG *pulEventType,
            MRCHANDLED *pHandled
            );

    long        m_cRef;         //object reference count
    
public:
    MRCACCESS   m_mrcAccess;    //Requested access
    MRCHANDLED  m_mrcHandled;   //does the client handle the message
};

/******************************************************************************

    CRuleClient_EMS - Rule client that intercepts EMS only.

******************************************************************************/
class CRuleClient_EMS : public CRuleClientBase
{
public:
    //Required by CFactory
    static HRESULT CreateInstance(IUnknown* pUnknownOuter, 
                                  IUnknown** ppNewComponent);

    ~CRuleClient_EMS();

private:
    //IMailRuleClient Implementation
    MAPIMETHOD(Initialize)(
            IMsgStore *pMsgStore,
            MRCACCESS *pmaDesired
            );
            
    MAPIMETHOD(ProcessMessage)(
            IMsgStore *pMsgStore, 
            ULONG cbMsg,
            LPENTRYID lpMsg,
            ULONG cbDestFolder,
            LPENTRYID lpDestFolder,
            ULONG *pulEventType,
            MRCHANDLED *pHandled
            );
};

/******************************************************************************

    CEMSBaseObject - All EMS objects are derived from this class.  Each has an
    offset into the user data (text) and some data associated with it.  Every
    object must also provide some way to validate its data and convert itself
    to a text string that gets written to the body of the message.  The custom
    read form will parse this string to determine how to display the object.

******************************************************************************/
class CEMSBaseObject 
{
protected:
    CEMSBaseObject(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData);
    ~CEMSBaseObject();

    //Must be overloaded by derived EMS objects
    virtual BOOL ValidateData() _PURE;
    virtual BOOL ExtractInfoFromHeader() _PURE;
    virtual BOOL ToString(LPTSTR* ppszObjectData) _PURE;
    
    ULONG   m_ulOffset;     //Offset into UserData (text)
    ULONG   m_cbData;       //size of data buffer
    LPBYTE  m_lpData;       //data buffer
    TCHAR*  m_szUserData;   //Text associated with EMS
    BOOL    m_fValidated;   //Has object been validated?
    BOOL    m_fInitialized; //Derived objects should not proceed if FALSE
};

/******************************************************************************

    CEMSTextFormatting - Text formatting object.  This represents a sequential
    series of text characters that share a common formatting.

******************************************************************************/
class CEMSTextFormatting : public CEMSBaseObject
{
public:
    CEMSTextFormatting(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData);
    
    //Alignment options
    enum EMS_TF_ALIGNMENT {
        EMSTF_ALIGN_LEFT = 0,
        EMSTF_ALIGN_CENTER = 1,
        EMSTF_ALIGN_RIGHT = 2,
        EMSTF_ALIGN_LANGUAGEDEPENDENT = 3
    };

    //Font size options, a "size" in the sense we're used to in WIN32 is not
    //given, it's up to the manufacturer to decide what is 'normal' and 'large'
    enum EMS_TF_FONTSIZE {
        EMSTF_FONTSIZE_NORMAL = 0,
        EMSTF_FONTSIZE_LARGE = 1,
        EMSTF_FONTSIZE_SMALL = 2,
        EMSTF_FONTSIZE_RESERVED = 3
    };

    //Overloaded Methods
    BOOL ValidateData();
    BOOL ToString(LPTSTR* ppszObjectData);
    BOOL ExtractInfoFromHeader();
    
private:
    ULONG               m_ulBaseOffset;   //Need to save for validation
    BYTE                m_chLen;          //Length of chars formatted
    EMS_TF_ALIGNMENT    m_eAlignment;     //alignment of text
    EMS_TF_FONTSIZE     m_eFontSize;      //size of text
    BOOL                m_fBold;          //Bold?
    BOOL                m_fItalics;       //Italicized?
    BOOL                m_fUnderlined;    //Underlined?
    BOOL                m_fStrikethrough; //Strikethough?
};

/******************************************************************************

    CEMSPredefinedSound - A predefined sound object.  This is really just an 
    offset and an index into a predefined list of sounds.  The sounds are 
    described in the 3GPP spec, but are up to the manufacturer to supply

******************************************************************************/
class CEMSPredefinedSound : public CEMSBaseObject
{
public:
    CEMSPredefinedSound(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData);

    //List of available sounds as defined in 3GPP...
    enum EMS_PREDEFINEDSOUND {
        EMSPS_CHIMESHIGH = 0,
        EMSPS_CHIMESLOW = 1,
        EMSPS_DING = 2,
        EMSPS_TADA = 3,
        EMSPS_NOTIFY = 4,
        EMSPS_DRUM = 5,
        EMSPS_CLAPS = 6,
        EMSPS_FANFAR = 7,
        EMSPS_CHORDHIGH = 8,
        EMSPS_CHORDLOW = 9
    };

    //Overloaded Methods
    BOOL ValidateData();
    BOOL ToString(LPTSTR* ppszObjectData);
    BOOL ExtractInfoFromHeader();
    
private:
    EMS_PREDEFINEDSOUND m_eSound;
};

/******************************************************************************
    
    CEMSUserdefinedSound - A user defined sound.  This is an offset, and then
    a chunk of data representing the sound.  The data is in a format called
    iMelody and has a max length of 128 bytes (MAX_IMELODY_LEN)

******************************************************************************/
class CEMSUserdefinedSound : public CEMSBaseObject
{
public:
    CEMSUserdefinedSound(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData);
    ~CEMSUserdefinedSound();

    //Overloaded Methods
    BOOL ValidateData();
    BOOL ToString(LPTSTR* ppszObjectData);
    BOOL ExtractInfoFromHeader();

private:
    LPBYTE  m_lpiMelody;    //iMelody data
    ULONG   m_cbiMelody;    //size in bytes of iMelody data
};

/******************************************************************************
    
    CEMSPredefinedAnimation - A predefined animation object.  This is an offset
    and an index to a predefined animation.  The animations are defined in the
    3GPP spec, but again are up to the manufacturer to design.
    
******************************************************************************/
class CEMSPredefinedAnimation : public CEMSBaseObject
{
public:
    CEMSPredefinedAnimation(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData);

    //Animation list as defined in 3GPP
    enum EMS_PREDEFINEDANIM {
        EMSPA_IAMIRONICFLIRTY = 0,
        EMSPA_IAMGLAD = 1,
        EMSPA_IAMSCEPTIC = 2,
        EMSPA_IAMSAD = 3,
        EMSPA_WOW = 4,
        EMSPA_IAMCRYING = 5,
        EMSPA_IAMWINKING = 6,
        EMSPA_IAMLAUGHING = 7,
        EMSPA_IAMINDIFFERENT = 8,
        EMSPA_INLOVEKISSING = 9,
        EMSPA_IAMCONFUSED = 10,
        EMSPA_TONGUEHANGINGOUT = 11,
        EMSPA_IAMANGRY = 12,
        EMSPA_WEARINGGLASSES = 13,
        EMSPA_DEVIL = 14
    };

    //Overloaded Methods
    BOOL ValidateData();
    BOOL ToString(LPTSTR* ppszObjectData);
    BOOL ExtractInfoFromHeader();

private:
    EMS_PREDEFINEDANIM m_eAnimation;    
};

/******************************************************************************
    
    CEMSAnimation - Animation object.  Both small and large animations are 
    handled by this class.  Animations are always 4 pictures and are either
    16x16 each (small) or 32x32 each (large).
 
******************************************************************************/
class CEMSAnimation : public CEMSBaseObject
{
public:
    CEMSAnimation(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData, int iType);
    ~CEMSAnimation();

    //Supported animation types as defined in 3GPP
    enum EMS_ANIMATIONTYPE {
        EMSAT_LARGE = 0,
        EMSAT_SMALL = 1        
    };

    //Overloaded Methods
    BOOL ValidateData();
    BOOL ToString(LPTSTR* ppszObjectData);
    BOOL ExtractInfoFromHeader();

private:
    LPBYTE              m_rglpAnimData[NUM_ANIM_FRAMES];  //always 4 images
    UINT                m_uRes;             //16 or 32
    EMS_ANIMATIONTYPE   m_eAnimType;
};

/******************************************************************************

    CEMSPicture - A picture object.  Small, large, and variable picture types
    are handled by this class.  A picture can be small (16x16), large (32x32), 
    or variable, remembering that a single SM can only be 140 BYTES in size,
    including the other portions of the header data and any user data, so the
    total size of the picture is limited...

******************************************************************************/
class CEMSPicture : public CEMSBaseObject
{
public:
    CEMSPicture(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData, int iType);
    ~CEMSPicture();

    //Picture types as defined in 3GPP
    enum EMS_PICTURETYPE {
        EMSPT_LARGE = 0,
        EMSPT_SMALL = 1,
        EMSPT_VARIABLE = 2
    };

    //Overloaded Methods
    BOOL ValidateData();
    BOOL ToString(LPTSTR* ppszObjectData);
    BOOL ExtractInfoFromHeader();

private:
    LPBYTE          m_lpPicData;    //Picture data
    UINT            m_uHorzRes;     //Horizontal resolution in pixels
    UINT            m_uVertRes;     //Vertical resolution in pixels
    EMS_PICTURETYPE m_ePicType;     //Picture type
};

/******************************************************************************

    CEMSUserPrompt - A user prompt object.  This is an offset and a number of
    objects that follow the user prompt to be included in the prompt.  It would
    seem from the 3GPPP spec that this would not be included with other objects
    that aren't part of the prompt in the same EMS.  This really isn't of
    concern here, but the custom form should consider objects included in the
    prompt as candidates for "stitching" - e.g. joining images and sounds that
    follow each other in order.

******************************************************************************/
class CEMSUserPrompt : public CEMSBaseObject
{
public:
    CEMSUserPrompt(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData);

    //Overloaded Methods
    BOOL ValidateData();
    BOOL ToString(LPTSTR* ppszObjectData);
    BOOL ExtractInfoFromHeader();
        
private:
    ULONG m_ulNumObjects;   //Number of objects to follow to include in prompt
};