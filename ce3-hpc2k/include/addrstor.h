/*++

Copyright (c) 1995  Microsoft Corporation

Module:

    addrstor.h

Purpose:

    This include file allows us to access the address book database.

--*/

#include <windbase.h>
#include <addrmapi.h>

// GetPropertyDataStruct flags
#define GPDS_PROPERTY	1
#define GPDS_INDEX		2
#define GPDS_NAME       3
#define GPDS_ERR        -1

// Types of properties
#define TEXT_PROPERTY       0x01
#define DATE_PROPERTY       0x02
#define PHONE_PROPERTY      0x04
#define NAME_PROPERTY       0x09    // Names are also text
#define ADDRESS_PROPERTY    0x11    // Addresses are also text
#define EMAIL_PROPERTY      0x21    // Email addresses are also text

// Property tags for last name first or last name last, which aren't put into the store
// but which are expanded to include all name properties
#define HHPR_LAST_FIRST_NAME                    PROP_TAG(PT_UNICODE, 0x6012)
#define HHPR_FIRST_LAST_NAME                    PROP_TAG(PT_UNICODE, 0x6013)

// Property tags for full addresses which aren't put into the store, but which
// are expanded to include their address components
#define HHPR_HOME_ADDRESS                       PROP_TAG(PT_UNICODE, 0x6020)
#define HHPR_OTHER_ADDRESS                      PROP_TAG(PT_UNICODE, 0x6021)
#define HHPR_OFFICE_ADDRESS                     PROP_TAG(PT_UNICODE, 0x6022)

// Property tags for use in GetMatchingEntry.  These include all email properties,
// or all email properties and pager properties
#define HHPR_EMAIL_TYPE                         PROP_TAG(PT_UNICODE, 0x6500)
#define HHPR_EMAIL_OR_PAGER_TYPE                PROP_TAG(PT_UNICODE, 0x6501)

// Stores information about a property, including its name, type, and HHPRTAG
typedef struct _PropertyDataStruct {
    TCHAR *pszReserved;         // Reserved -- do not use
    TCHAR *pszPropertyName;     // The name of the property
	ULONG uPropType;            // The type of property (text, phone, or date) 
	HHPRTAG hhProp;             // The property tag of this property
} PropertyDataStruct;

// An address book card
typedef struct _AddressCard {
	// Two systemtimes
    SYSTEMTIME stBirthday;
	SYSTEMTIME stAnniversary;

    // String properties
    TCHAR *pszBusinessFax;
    TCHAR *pszCompany;
	TCHAR *pszDepartment;
	TCHAR *pszEmail;
    TCHAR *pszMobilePhone;
	TCHAR *pszOfficeLocation;
	TCHAR *pszPager;
    TCHAR *pszWorkPhone;
	TCHAR *pszTitle;
	TCHAR *pszHomePhone;
	TCHAR *pszEmail2;
    TCHAR *pszSpouse;
    TCHAR *pszNotes;
	TCHAR *pszEmail3;
    TCHAR *pszHomePhone2;
	TCHAR *pszHomeFax;
    TCHAR *pszCarPhone;
    TCHAR *pszAssistant;
    TCHAR *pszAssistantPhone;
    TCHAR *pszChildren;
    TCHAR *pszCategory;
    TCHAR *pszWebPage;
    TCHAR *pszWorkPhone2;

	// Name fields
    TCHAR *pszNamePrefix;
    TCHAR *pszGivenName;
    TCHAR *pszMiddleName;
    TCHAR *pszSurname;
    TCHAR *pszGeneration;

    // Address Fields
    TCHAR *pszHomeAddrStreet;
    TCHAR *pszHomeAddrCity;
    TCHAR *pszHomeAddrState;
    TCHAR *pszHomeAddrPostalCode;
    TCHAR *pszHomeAddrCountry;

    TCHAR *pszOtherAddrStreet;
    TCHAR *pszOtherAddrCity;
    TCHAR *pszOtherAddrState;
    TCHAR *pszOtherAddrPostalCode;
    TCHAR *pszOtherAddrCountry;

    TCHAR *pszOfficeAddrStreet;
    TCHAR *pszOfficeAddrCity;
    TCHAR *pszOfficeAddrState;
    TCHAR *pszOfficeAddrPostalCode;
    TCHAR *pszOfficeAddrCountry;
#ifdef JAPAN
    TCHAR *pszYomiLastName;
	TCHAR *pszYomiFirstName;
    TCHAR *pszYomiCompany;
#endif //JAPAN
	// Reserved -- don't use
    BYTE rgbReserved[84];
} AddressCard;

// Getting information out of the property data structure
EXTERN_C int GetPropertyDataStruct(int fFlag, ULONG uValue, PropertyDataStruct *ppds);

// Opening and closing the address book
EXTERN_C void CloseAddressBook();
EXTERN_C BOOL CreateAddressBook(HHPRTAG *rghhProps, int numProps);
EXTERN_C BOOL OpenAddressBook(HWND hwnd, HHPRTAG hhProp);

// Getting oids and indexes of cards
EXTERN_C CEOID GetAddressCardOid(int nCard);
EXTERN_C int GetAddressCardIndex(CEOID oidCard);

// Retrieving cards
// Flag for OpenAddressCard
#define OAC_ALLOCATE        0x01

EXTERN_C BOOL OpenAddressCard(CEOID oidCard, AddressCard *pac, ULONG uFlags);
EXTERN_C BOOL GetAddressCardProperties(CEOID oidCard, AddressCard *pac, int numRequestedProps, HHPRTAG *rghhProp);
EXTERN_C BOOL GetMatchingEntry(TCHAR *szMatch, int *pBufSize, TCHAR *szField, CEOID *poidMatch, HHPRTAG *phhMatch);

// Changing cards in the store
EXTERN_C BOOL AddAddressCard(AddressCard *pac, CEOID *poidCard, int *pindex);
EXTERN_C BOOL DeleteAddressCard(CEOID oidCard);
EXTERN_C BOOL ModifyAddressCard(AddressCard *pac, CEOID oidCard, int *pindex);

// Getting a clean address card and freeing an address card
EXTERN_C void FreeAddressCard(AddressCard *pac);

// Replication
EXTERN_C void RecountCards();

// Getting and setting properties from the address book registry settings
EXTERN_C BOOL GetColumnProperties(HHPRTAG *propList, int *pColumns);
EXTERN_C BOOL SetColumnProperties(HHPRTAG *propList, int nColumns);
EXTERN_C HHPRTAG GetSortOrder(BOOL fDatabaseSort);
EXTERN_C BOOL SetSortOrder(HHPRTAG hhProp);
EXTERN_C void SetMask(AddressCard *pac, HHPRTAG hhProp);
EXTERN_C int GetNumberOfAddressCards();
#ifdef JAPAN
EXTERN_C int GetYomiCountAddrStor(TCHAR *szText,HHPRTAG hhProp,AddressCard *pac,int *xyomiCnt);
BOOL AddAddressCardYomi(AddressCard *pac, CEOID *poidCard, int *pindex);
#endif //JAPAN

// Flag for FindFirstEntry
#define FFE_CONTAINS        0x01

EXTERN_C CEOID FindFirstEntry(TCHAR *szFind, HHPRTAG hhProp, int *pindex, DWORD dwFlags);

