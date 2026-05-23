// WCE_DatabaseDoc.cpp : implementation of the CWCEDBDoc class
//

#include "stdafx.h"

#include "wcedbtst.h"
#include "wcedbdoc.h"


// Define app-defined values
const DWORD DB_IDENT_PEOPLE  = 12345;
const WCHAR DB_NAME_PEOPLE[] = _T("People");
const WORD  PROP_LASTNAME    = 101,  
            PROP_FIRSTNAME   = 102,  
            PROP_AGE         = 103,
#if (_WIN32_WCE <= 211)			
            PROP_GENDER      = 104;
#else // _WIN32_WCE
            PROP_GENDER      = 104,
			PROP_MARRIED     = 105,
			PROP_SALARY      = 106;
#endif // _WIN32_WCE



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWCEDBDoc

IMPLEMENT_DYNCREATE(CWCEDBDoc, CDocument)

BEGIN_MESSAGE_MAP(CWCEDBDoc, CDocument)
	//{{AFX_MSG_MAP(CWCEDBDoc)
	ON_COMMAND(ID_FILE_BASICTESTS, OnFileBasicTests)
	ON_COMMAND(ID_FILE_ENUM, OnFileEnum)
	ON_COMMAND(ID_FILE_SORTTEST, OnFileSortTest)
	ON_COMMAND(ID_FILE_SEEKTEST, OnFileSeekTest)
	ON_COMMAND(ID_FILE_DELETIONTEST, OnFileDeletionTest)
	ON_COMMAND(ID_FILE_MODIFYTEST, OnFileModifyTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWCEDBDoc construction/destruction

CWCEDBDoc::CWCEDBDoc()
{
}

CWCEDBDoc::~CWCEDBDoc()
{
	if(CCeDBDatabase::Exists(DB_NAME_PEOPLE)) 
	{
		CCeDBDatabase db;
		db.Open(DB_NAME_PEOPLE);
		db.Delete();
	}
}

BOOL CWCEDBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CWCEDBDoc serialization

void CWCEDBDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWCEDBDoc diagnostics

#ifdef _DEBUG
void CWCEDBDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWCEDBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWCEDBDoc commands

// Need to figure out error values
#define FAIL_AND_EXIT { Output.Add(CString((LPCTSTR)IDS_FAILEXIT)),UpdateAllViews(NULL); return; }
#define FAIL Output.Add(CString((LPCTSTR)IDS_FAILED)),UpdateAllViews(NULL)
#define OK   Output.Add(CString((LPCTSTR)IDS_OK)),UpdateAllViews(NULL)
#define PRINT(what) Output.Add(CString((LPCTSTR)what)),UpdateAllViews(NULL)
#define PRINT_BLANK() Output.Add(_T("")),UpdateAllViews(NULL)
#define PRINT_WSTR(what) Output.Add(what),UpdateAllViews(NULL)
#define START {Output.RemoveAll(); \
			  POSITION pos = GetFirstViewPosition(); \
              GetNextView(pos)->SetScrollPos(SB_VERT,0);\
              UpdateAllViews(NULL); }


BOOL CWCEDBDoc::GeneratePeopleDB() 
{
#if (_WIN32_WCE <=211)
	PRINT(IDS_GENERATE_PEOPLE);
	PRINT(IDS_SORT_ORDER); 
#else // _WIN32_WCE
	PRINT(IDS_GENERATE_PEOPLE2);
	PRINT(IDS_SORT_ORDER2); 
#endif // _WIN32_WCE

	// Delete old database if existent
	if(CCeDBDatabase::Exists(DB_NAME_PEOPLE)) 
	{
		CCeDBDatabase db;
		db.Open(DB_NAME_PEOPLE);
		if(!db.Delete())
			return FALSE;
	}

	// Create database
	CCeDBDatabase db;
	CEOID poid;  
#if (_WIN32_WCE <= 211)
	CCeDBProp SortProps[3] = {
#else // _WIN32_WCE
	CCeDBProp SortProps[5] = {
#endif // _WIN32_WCE_PSPC
		CCeDBProp(CCeDBProp::Type_String, PROP_LASTNAME,
		           CCeDBProp::Sort_Ascending | CCeDBProp::Sort_CaseInsensitive),
		CCeDBProp(CCeDBProp::Type_UShort, PROP_AGE,      
		           CCeDBProp::Sort_Descending),
		CCeDBProp(CCeDBProp::Type_UShort, PROP_GENDER,
#if (_WIN32_WCE <= 211)		
		           CCeDBProp::Sort_UnknownFirst)
#else // _WIN32_WCE_PSPC
				   CCeDBProp::Sort_UnknownFirst),
		CCeDBProp(CCeDBProp::Type_Double, PROP_SALARY,   
		           CCeDBProp::Sort_Descending),
#endif // _WIN32_WCE				   
	};

#if (_WIN32_WCE <=211)
	if(!(poid = db.Create(DB_NAME_PEOPLE,DB_IDENT_PEOPLE,3,SortProps))) 
#else // _WIN32_WCE
	if(!(poid = db.Create(DB_NAME_PEOPLE,DB_IDENT_PEOPLE,4,SortProps))) 
#endif // _WIN32_WCE
		return FALSE;

	if(!db.Open(poid))
		return FALSE;

	// Add records
	CCeDBRecord rec;
#if (_WIN32_WCE <= 211)
	CCeDBProp props[4];
#else // _WIN32_WCE
	CCeDBProp props[6];
#endif // _WIN32_WCE

	CString str;

	str.LoadString(IDS_SMITH);
	props[0] = CCeDBProp((LPWSTR)(LPCTSTR)str,PROP_LASTNAME);
	str.LoadString(IDS_BOB);
	props[1] = CCeDBProp((LPWSTR)(LPCTSTR)str,  PROP_FIRSTNAME);
	props[2] = CCeDBProp((USHORT)34, PROP_AGE);
	props[3] = CCeDBProp((USHORT)'M',PROP_GENDER);
#if (_WIN32_WCE <= 211)
	rec.AddProps(props,4);
#else // _WIN32_WCE	
	props[4] = CCeDBProp((BOOL)1,PROP_MARRIED);
	props[5] = CCeDBProp((DOUBLE)20000.00,PROP_SALARY);
	rec.AddProps(props,6);
#endif // _WIN32_WCE
	if(!db.AddRecord(&rec))
		return FALSE;

	rec.DeleteAllProps();
	str.LoadString(IDS_SMITH);
	props[0] = CCeDBProp((LPWSTR)(LPCTSTR)str,PROP_LASTNAME);
	str.LoadString(IDS_MARY);
	props[1] = CCeDBProp((LPWSTR)(LPCTSTR)str, PROP_FIRSTNAME);
	props[2] = CCeDBProp((USHORT)22, PROP_AGE);
	props[3] = CCeDBProp((USHORT)'F',PROP_GENDER);
#if (_WIN32_WCE <= 211)
	rec.AddProps(props,4);
#else // _WIN32_WCE
	props[4] = CCeDBProp((BOOL)0,PROP_MARRIED);
	props[5] = CCeDBProp((DOUBLE)60000.00,PROP_SALARY);
	rec.AddProps(props,6);
#endif // _WIN32_WCE
	if(!db.AddRecord(&rec))
		return FALSE;

	rec.DeleteAllProps();
	str.LoadString(IDS_EMERSON);
	props[0] = CCeDBProp((LPWSTR)(LPCTSTR)str,PROP_LASTNAME);
	str.LoadString(IDS_RALPH);
	props[1] = CCeDBProp((LPWSTR)(LPCTSTR)str, PROP_FIRSTNAME);
	props[2] = CCeDBProp((USHORT)65, PROP_AGE);
	props[3] = CCeDBProp((USHORT)'M',PROP_GENDER);
#if (_WIN32_WCE <= 211)
	rec.AddProps(props,4);
#else // _WIN32_WCE
	props[4] = CCeDBProp((BOOL)0,PROP_MARRIED);
	props[5] = CCeDBProp((DOUBLE)40000.00,PROP_SALARY);
	rec.AddProps(props,6);
#endif // _WIN32_WCE
	if(!db.AddRecord(&rec))
		return FALSE;

	rec.DeleteAllProps();
	str.LoadString(IDS_CABANA);
	props[0] = CCeDBProp((LPWSTR)(LPCTSTR)str,PROP_LASTNAME);
	str.LoadString(IDS_ANNA);
	props[1] = CCeDBProp((LPWSTR)(LPCTSTR)str, PROP_FIRSTNAME);
	props[2] = CCeDBProp((USHORT)19, PROP_AGE);
	props[3] = CCeDBProp((USHORT)'F',PROP_GENDER);
#if (_WIN32_WCE <= 211)
	rec.AddProps(props,4);
#else // _WIN32_WCE
	props[4] = CCeDBProp((BOOL)1,PROP_MARRIED);
	props[5] = CCeDBProp((DOUBLE)80000.00,PROP_SALARY);
	rec.AddProps(props,6);
#endif // _WIN32_WCE
	if(!db.AddRecord(&rec))
		return FALSE;

	rec.DeleteAllProps();
	str.LoadString(IDS_ZIMMERMAN);
	props[0] = CCeDBProp((LPWSTR)(LPCTSTR)str,PROP_LASTNAME);
	str.LoadString(IDS_ZACH);
	props[1] = CCeDBProp((LPWSTR)(LPCTSTR)str, PROP_FIRSTNAME);
	props[2] = CCeDBProp((USHORT)25, PROP_AGE);
	props[3] = CCeDBProp((USHORT)'M',PROP_GENDER);
#if (_WIN32_WCE <= 211)
	rec.AddProps(props,4);
#else // _WIN32_WCE
	props[4] = CCeDBProp((BOOL)1,PROP_MARRIED);
	props[5] = CCeDBProp((DOUBLE)50000.00,PROP_SALARY);
	rec.AddProps(props,6);
#endif // _WIN32_WCE
	if(!db.AddRecord(&rec))
		return FALSE;

	// Write a partial record (an unknown gender)
	rec.DeleteAllProps();
	str.LoadString(IDS_EVANS);
	props[0] = CCeDBProp((LPWSTR)(LPCTSTR)str,PROP_LASTNAME);
	str.LoadString(IDS_PAT);
	props[1] = CCeDBProp((LPWSTR)(LPCTSTR)str, PROP_FIRSTNAME);
	props[2] = CCeDBProp((USHORT)41, PROP_AGE);
	props[3] = CCeDBProp((USHORT)'F',PROP_GENDER);
#if (_WIN32_WCE <= 211)
	rec.AddProps(props,4);
#else // _WIN32_WCE
	props[4] = CCeDBProp((BOOL)0,PROP_MARRIED);
	props[5] = CCeDBProp((DOUBLE)60000.00,PROP_SALARY);
	rec.AddProps(props,6);
#endif // _WIN32_WCE
	// We added the last prop so we can test deletion
	rec.DeleteProp(PROP_GENDER);
	if(!db.AddRecord(&rec))
		return FALSE;

	return TRUE;
}


BOOL CWCEDBDoc::PrintPeopleDB(CCeDBDatabase *pdb) 
{
	PRINT(IDS_PRINT_PEOPLE);

	CCeDBRecord rec;

	WCHAR szBuf[100];
	CString str;
	str.LoadString(IDS_NUM_RECORD);
	wsprintf(szBuf,(LPCTSTR)str,pdb->GetNumRecords());
	PRINT_WSTR(szBuf);

	BOOL bPrev = pdb->m_bAutoSeekNext;
	pdb->m_bAutoSeekNext = TRUE;
	pdb->SeekFirst();
	while(pdb->ReadCurrRecord(&rec))
		PrintPerson(&rec);
	pdb->m_bAutoSeekNext = bPrev;

	PRINT_BLANK();
	return TRUE;
}

void CWCEDBDoc::PrintIndex(CCeDBDatabase* pdb) 
{
	WCHAR szBuf[20];
	CString str;
	str.LoadString(IDS_CURRENT_RECORD);
	wsprintf(szBuf,(LPCTSTR)str,pdb->GetCurrIndex());
	PRINT_WSTR(szBuf);
}

void CWCEDBDoc::PrintPerson(CCeDBRecord* prec) 
{
#if (_WIN32_WCE <= 211)
	CCeDBProp *pPropLast,*pPropFirst,*pPropAge,*pPropGender;
#else // _WIN32_WCE
	CCeDBProp *pPropLast,*pPropFirst,*pPropAge,*pPropGender, *pPropMarried,
		      *pPropSalary;
#endif // _WIN32_WCE
	WCHAR szBuf[200];

	pPropLast    = prec->GetPropFromIdent(PROP_LASTNAME);
	pPropFirst   = prec->GetPropFromIdent(PROP_FIRSTNAME);
	pPropAge     = prec->GetPropFromIdent(PROP_AGE);
	pPropGender  = prec->GetPropFromIdent(PROP_GENDER);
#if !(_WIN32_WCE <= 211)
	pPropMarried = prec->GetPropFromIdent(PROP_MARRIED);
	pPropSalary  = prec->GetPropFromIdent(PROP_SALARY);
#endif // _WIN32_WCE

	CString str, str2;
#if (_WIN32_WCE <= 211)
	str.LoadString(IDS_AGE_GENDER);
#else // _WIN32_WCE
	str.LoadString(IDS_AGE_GENDER2);
#endif // _WIN32_WCE
	str2.LoadString(IDS_QUESTION);
	wsprintf(szBuf,(LPCTSTR)str,
		     pPropLast?     pPropLast->GetString()   : (LPCTSTR)str2,
			 pPropFirst?    pPropFirst->GetString()  : (LPCTSTR)str2,
			 pPropAge?      pPropAge->GetUShort()    : 999,
#if (_WIN32_WCE <= 211)
			 pPropGender?   pPropGender->GetUShort() : '?');
#else // _WIN32_WCE
			 pPropGender?   pPropGender->GetUShort() : '?',
			 pPropMarried? (pPropMarried->GetBool()? 'Y' : 'N') : '?',
			 pPropSalary?   pPropSalary->GetDouble() : '?' );
#endif // _WIN32_WCE
	PRINT_WSTR(szBuf);		
}


void CWCEDBDoc::OnFileClear() 
{
	Output.RemoveAll();
	UpdateAllViews(NULL);
	CCeDBProp DBassign;
}



void CWCEDBDoc::OnFileBasicTests()
{
	START;

	PRINT(IDS_BASIC_TEST);
	PRINT_BLANK();

	PRINT(IDS_CHECK_TEST);
	//if(!CCeDBDatabase::Exists(_T("Test Database")))
	CString str;
	str.LoadString(IDS_DATABASE);
	if(!CCeDBDatabase::Exists((LPCTSTR)str))
		FAIL;
	else
	{
		OK;
		PRINT(IDS_OPENIT);
		CCeDBDatabase temp;
		if(temp.Open((LPCTSTR)str))
			OK;
		else 
			FAIL_AND_EXIT;
		PRINT(IDS_DELETEIT);
		if(temp.Delete())
			OK;
		else
			FAIL_AND_EXIT;
	}

	PRINT(IDS_CREATING_TEST);

	CCeDBDatabase* pdb = new CCeDBDatabase; // use ptr to new

	if(!pdb->Create((LPCTSTR)str))
		FAIL_AND_EXIT;
	OK;

	PRINT(IDS_CHECK_EXIST);
	if(CCeDBDatabase::Exists((LPCTSTR)str))
		OK;
	else
		FAIL;

	delete pdb;

	CCeDBDatabase db; // use auto

	PRINT(IDS_OPEN_AGAIN);
	if(!db.Open((LPCTSTR)str))
		FAIL_AND_EXIT;
	OK;

	PRINT(IDS_DELETEIT);
	db.Delete();

	PRINT_BLANK();
	PRINT(IDS_DONE_BASIC);
}




void CWCEDBDoc::OnFileEnum() 
{
	START;
	PRINT(IDS_ENUM_TEST);
	PRINT_BLANK();

	// Create 3 databases, inside a new scope so the db's are closed at the end of it
	{
		CStringArray names;
		CCeDBDatabase databases[3];	
		names.Add(CString((LPCTSTR)IDS_HERE));
		names.Add(CString((LPCTSTR)IDS_THERE));
		names.Add(CString((LPCTSTR)IDS_NOWHERE));

		PRINT(IDS_CREATING_DB99);
		for(int n=0; n < names.GetSize(); n++)
		{
			LPWSTR name = (LPWSTR)(LPCTSTR)names[n]; // blah!
			if(CCeDBDatabase::Exists(name)) 
			{
				CCeDBDatabase db;
				db.Open(name);
				db.Delete();
			}

			CString printLine;
			printLine.LoadString(IDS_CREATING);
			printLine += name;
			PRINT_WSTR(printLine);
			if(!databases[n].Create(name,99))
				FAIL_AND_EXIT;
			OK;

			PRINT(IDS_SLEEPING);
			Sleep(500);
		}

		// note that databases that go out of scope (i.e. destructed) get closed
	}

	// First pass: p=0: enumerates the three databases
	// Subsequent passes delete the three databases (in Windows CE 2.1, the object store
	// stores the databases in a different order, so multiple passes is necessary).
	int nDeleted = 0;
	for(int p=0; nDeleted < 3; p++)
	{
		PRINT_BLANK();
		if(!p)
			PRINT(IDS_DOING_ENUM);
		else
			PRINT(IDS_DOING_ENUM99);

		CCeDBEnum dbEnumAll;
		CCeDBEnum dbEnum(99);
		CEOID CEOID;
	
		while(CEOID = (p?dbEnum.Next():dbEnumAll.Next()))
		{
			CCeDBDatabase db;
			WCHAR szBuf[200];

			CString str;
			str.LoadString(IDS_FOUND_DB);
			wsprintf(szBuf,(LPCTSTR)str,CEOID);
			PRINT_WSTR(szBuf);			

			if(!db.Open(CEOID))
				FAIL_AND_EXIT;

			WCHAR szName[33];
			db.GetName(szName);

			FILETIME FileTime = db.GetLastModified();
			SYSTEMTIME SystemTime;
			FileTimeToSystemTime(&FileTime, &SystemTime);

			str.LoadString(IDS_NAME_SIZE);
			wsprintf(szBuf,(LPCTSTR)str,
			         szName,db.GetSize(),db.GetIdent(),
					 SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond, 
					 SystemTime.wMilliseconds);
			PRINT_WSTR(szBuf);

			if(p)
			{
				PRINT(IDS_ENUM_DELETE);
				db.Delete();
				nDeleted++;
			}
		}
	}

	PRINT(IDS_ENUM_DONE);
}



void CWCEDBDoc::OnFileSortTest() 
{
	START;
	PRINT(IDS_SORT_TEST);
	PRINT_BLANK();

	if(!GeneratePeopleDB())
		FAIL_AND_EXIT;
	OK;


	PRINT(IDS_PRINT_DEFAULT);

	CCeDBDatabase db;
	if(db.Open(DB_NAME_PEOPLE))
		PrintPeopleDB(&db);
	db.Close();

	PRINT(IDS_NOTE);
	

	// Note: the property has to match on both the type and the identifier in 
	// order for the Open() to work!
#if !(_WIN32_WCE <= 211)
	PRINT_BLANK();
	PRINT(IDS_PRINT_SALARY);

	CCeDBProp Salary(CCeDBProp::Type_Double,PROP_SALARY); 
	if(db.Open(DB_NAME_PEOPLE,&Salary))
		PrintPeopleDB(&db);
	db.Close();
#endif // _WIN32_WCE

	PRINT_BLANK();
	PRINT(IDS_PRINT_AGE);

	CCeDBProp Age(CCeDBProp::Type_UShort,PROP_AGE); 
	if(db.Open(DB_NAME_PEOPLE,&Age))
		PrintPeopleDB(&db);
	db.Close();


	PRINT_BLANK();
	PRINT(IDS_PRINT_GENDER);

	CCeDBProp Gender(CCeDBProp::Type_UShort,PROP_GENDER); 
	if(db.Open(DB_NAME_PEOPLE,&Gender))
		PrintPeopleDB(&db);
	db.Close();


	PRINT_BLANK();
	PRINT(IDS_CHANGE_FIRST);
	PRINT(IDS_PRIMARY_NOTE);

	if(db.Open(DB_NAME_PEOPLE))
	{
		CCeDBProp sortProps[4];
		int nNumSortProps;
		db.GetSortProps(&nNumSortProps,sortProps);
		sortProps[0].SetSortFlags(CCeDBProp::Sort_Descending);
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
		db.Close();
#endif
		db.SetSortProps(nNumSortProps,sortProps);
	}
#if !defined(_WIN32_WCE_PSPC) || (_WIN32_WCE < 300)
	db.Close();
#endif
	CCeDBProp LastName(CCeDBProp::Type_String,PROP_LASTNAME); 
	if(db.Open(DB_NAME_PEOPLE,&LastName))
		PrintPeopleDB(&db);
	db.Close();
}





void CWCEDBDoc::OnFileSeekTest() 
{
	START;
	PRINT(IDS_SEEK_TEST);
	PRINT_BLANK();

	if(!GeneratePeopleDB())
		FAIL_AND_EXIT;
	OK;

	CCeDBDatabase db;
	if(!db.Open(DB_NAME_PEOPLE))
		FAIL_AND_EXIT;

	CCeDBRecord rec;

	PRINT_BLANK();
	PRINT(IDS_SEEK_FIRST);
	if(!db.SeekFirst() || !db.ReadCurrRecord(&rec))
		FAIL_AND_EXIT;
	PrintIndex(&db);
	PrintPerson(&rec);

	PRINT_BLANK();
	PRINT(IDS_SEEK_LAST);
	if(!db.SeekLast() || !db.ReadCurrRecord(&rec))
		FAIL_AND_EXIT;
	PrintIndex(&db);
	PrintPerson(&rec);

	PRINT_BLANK();
	PRINT(IDS_SEEK_SECOND);
	if(!db.SeekToIndex(1) || !db.ReadCurrRecord(&rec)) // 0-based indexing!
		FAIL_AND_EXIT;
	PrintIndex(&db);
	PrintPerson(&rec);

	PRINT_BLANK();
	PRINT(IDS_REMEMBERING);
	CEOID poid = db.GetCurrRecord();

	PRINT_BLANK();	
	PRINT(IDS_SECOND);
	if(!db.SeekToIndex(1,TRUE) || !db.ReadCurrRecord(&rec)) // 0-based indexing!
		FAIL_AND_EXIT;
	PrintIndex(&db);
	PrintPerson(&rec);

	PRINT_BLANK();
	PRINT(IDS_SEEK_PREV);
	if(!db.SeekPrev() || !db.ReadCurrRecord(&rec)) 
		FAIL_AND_EXIT;
	PrintIndex(&db);
	PrintPerson(&rec);

	PRINT_BLANK();
	PRINT(IDS_REMEMBERED);
	if(!db.SeekToRecord(poid) || !db.ReadCurrRecord(&rec)) 
		FAIL_AND_EXIT;
	PrintIndex(&db);
	PrintPerson(&rec);

	CString str;
	str.LoadString(IDS_SMITH);
	CCeDBProp lastName((LPWSTR)(LPCTSTR)str,PROP_LASTNAME);

	PRINT_BLANK();
	PRINT(IDS_FIRST_SMITH);
	if(!db.SeekFirstEqual(lastName) || !db.ReadCurrRecord(&rec)) 
		FAIL_AND_EXIT;
	PrintIndex(&db);
	PrintPerson(&rec);

	PRINT_BLANK();
	PRINT(IDS_NEXT_SMITH);
	if(!db.SeekNextEqual(lastName) || !db.ReadCurrRecord(&rec)) 
		FAIL_AND_EXIT;
	PrintIndex(&db);
	PrintPerson(&rec);

	PRINT_BLANK();
	PRINT(IDS_NEXT_SMITH2);
	if(!db.SeekNextEqual(lastName) || !db.ReadCurrRecord(&rec)) 
		PRINT(IDS_NOT_FOUND);
	
	PRINT_BLANK();
	PRINT(IDS_PREV_EVANS);
	str.LoadString(IDS_EVANS);	
	CCeDBProp propLarger((LPWSTR)(LPCTSTR)str,PROP_LASTNAME);
	if(!db.SeekValueSmaller(propLarger) || !db.ReadCurrRecord(&rec)) 
		FAIL_AND_EXIT;
	PrintIndex(&db);
	PrintPerson(&rec);

	// Reset propLarger to be the current property.
	propLarger.SetString(rec.GetPropFromIdent(PROP_LASTNAME)->GetString());
	if(!db.SeekValueSmaller(propLarger) || !db.ReadCurrRecord(&rec)) 
		FAIL_AND_EXIT;
	PrintIndex(&db);
	PrintPerson(&rec);

	PRINT_BLANK();
	PRINT(IDS_NEXT_EVANS);
	str.LoadString(IDS_EVANS);
	CCeDBProp propSmaller((LPWSTR)(LPCTSTR)str,PROP_LASTNAME);
	if(!db.SeekValueGreater(propSmaller) || !db.ReadCurrRecord(&rec)) 
		FAIL_AND_EXIT;
	PrintIndex(&db);
	PrintPerson(&rec);

	PRINT_BLANK();
	PRINT(IDS_DONE);
}

void CWCEDBDoc::OnFileModifyTest() 
{
	START;
	PRINT(IDS_MODIFY_TEST);
	
	if(!GeneratePeopleDB())
		FAIL_AND_EXIT;
	OK;

	PRINT_BLANK();
	PRINT(IDS_MODIFY_INITIAL);
	CCeDBDatabase db;
	if(db.Open(DB_NAME_PEOPLE))
		PrintPeopleDB(&db);
	db.SeekFirst();
	PRINT_BLANK();
	PRINT(IDS_MODIFY_AGE);
	CCeDBRecord rec;
	CString str;
	str.LoadString(IDS_CABANA);
	CCeDBProp prop((LPWSTR)(LPCTSTR)str,PROP_LASTNAME);
	if(!db.SeekFirstEqual(prop))
		FAIL_AND_EXIT;
	if(!db.ReadCurrRecord(&rec)) 
		FAIL_AND_EXIT;	
	CCeDBProp* pAge = rec.GetPropFromIdent(PROP_AGE);
	if(pAge == NULL)
		FAIL_AND_EXIT;
	pAge->SetUShort(20);
	CCeDBProp ageFilter(CCeDBProp::Type_UShort,PROP_AGE);
	db.WriteCurrRecord(&rec,1,&ageFilter);
	PrintPeopleDB(&db);
}
	

void CWCEDBDoc::OnFileDeletionTest() 
{
	START;
	PRINT(IDS_DELETION_TEST);

	if(!GeneratePeopleDB())
		FAIL_AND_EXIT;
	OK;

	PRINT_BLANK();
	PRINT(IDS_INITIAL);
	CCeDBDatabase db;
	if(db.Open(DB_NAME_PEOPLE))
		PrintPeopleDB(&db);

	PRINT_BLANK();
	PRINT(IDS_RECORD);
	db.SeekToIndex(1);
	if(!db.DeleteCurrRecord())
		FAIL_AND_EXIT;
	PrintPeopleDB(&db);
	
	PRINT_BLANK();
	
	PRINT(IDS_DELETE_FIRST);
	CCeDBProp props[] = {
		CCeDBProp(CCeDBProp::Type_String,PROP_FIRSTNAME),
		CCeDBProp(CCeDBProp::Type_UShort,PROP_GENDER) 
	};

	db.SeekToIndex(2);
	if(!db.DeleteCurrRecordProps(2,props))
		FAIL_AND_EXIT;
	PrintPeopleDB(&db);

	PRINT(IDS_DELETE_LAST);
	CCeDBProp props2[] = {
		CCeDBProp(CCeDBProp::Type_String,PROP_LASTNAME) 
	};

	db.SeekToIndex(1);
	if(!db.DeleteCurrRecordProps(1,props2))
		FAIL_AND_EXIT;
	PrintPeopleDB(&db);


}


