/*
 *  TNEF.H
 *
 *  This declares the published interface to TNEFUTIL.DLL, a set of
 *  utility fuctions designed to encode/decode unusual mail properties in
 *  a Transport-Neutral form.
 *
 *  Owner: Dave Whitney
 *
 *  Copyright 1986-1998 Microsoft Corporation, All Rights Reserved
 */

#ifndef     _TNEFAPI_H_
#define     _TNEFAPI_H_

#ifdef      __cplusplus
extern "C" {
#endif      /* __cplusplus */

/**************************************************/
/* Constants **************************************/
/**************************************************/

/*
 *  Type INETENCODE - describes the encoding type for MIME encodings
 */
typedef enum {
    CODE_NONE = 0,
    CODE_UU,                                /* UUEncode                         */
    CODE_B64,                               /* base64                           */
    CODE_QP,                                /* quoted-printable                 */
    CODE_QPH,                               /* quoted-printable, in msg hdr     */
} INETENCODE;


/*
 *  Codepages supported by TnefConverToUnicode
 */
#define CPG_WINDOWS_1250        1250
#define CPG_WINDOWS_1251        1251
#define CPG_WINDOWS_1252        1252
#define CPG_WINDOWS_1253        1253
#define CPG_WINDOWS_1254        1254
#define CPG_WINDOWS_1255        1255
#define CPG_WINDOWS_1256        1256
#define CPG_WINDOWS_1257        1257
#define CPG_WINDOWS_1258        1258
#define CPG_KOI8_R              20866
#define CPG_KOI8_U              21866
#define CPG_ISO8859_1           28591
#define CPG_ISO8859_2           28592
#define CPG_ISO8859_3           28593
#define CPG_ISO8859_4           28594
#define CPG_ISO8859_5           28595
#define CPG_ISO8859_6           28596
#define CPG_ISO8859_7           28597
#define CPG_ISO8859_8           28598
#define CPG_ISO8859_9           28599
#define CPG_ISO8859_10          28600
#define CPG_ISO8859_14          28604
#define CPG_ISO8859_15          28605
#define CPG_UTF7                65000
#define CPG_UTF8                65001



/**************************************************/
/* Structures *************************************/
/**************************************************/

/*
 *  Type TNEFMIMEINFO
 *
 *  Used by TnefGetInfo, TnefBuildInfo
 */
#include <pshpack1.h>
typedef struct _tnefinfo {
    INETENCODE  wContentEncoding;           /* Content encoding                             */
    BOOL        fAttHdrs;                   /* Tells TnefGetInfo to get att headers only    */
    HANDLE      hHeap;                      /* Heap (from msg) to allocate from             */
    LPWSTR      szTnefCorrelator;           /* TNEF correlator from msg header              */
    WCHAR       szTnefFileName[MAX_PATH];   /* File name of TNEF file, if found             */
} TNEFINFO;
#include <poppack.h>

/**************************************************/
/* Functions **************************************/
/**************************************************/

/*
 *  TnefGetInfo
 *
 *  Purpose:
 *      Pulls info out of an encoded TNEF file
 *
 *  Parameters:
 *      TNEFINFO *          [in]        describes the TNEF file
 *      MailNonIpmInfo *    [out]       filled in
 *      MailAttArray *      [out]       filled in
 *
 *  Returns:
 *      BOOL        TRUE on success
 *
 *  Side Effects:
 *      * The file identified by ptmi->szTnefFileName is deleted once
 *        processing is completed - error or not
 *      * The remaining parms are filled in
 */
BOOL WINAPI TnefGetInfo(const TNEFINFO *, MailNonIpmInfo **, MailAttArray **);
typedef BOOL (WINAPI * LPFNTNEFGETINFO) (const TNEFINFO *, MailNonIpmInfo **, MailAttArray **);

/*
 *  TnefBuildInfo
 *
 *  Purpose:
 *      Puts info into an encoded TNEF file.
 *      Attachments are not supported in this release.
 *
 *  Parameters:
 *      TNEFINFO *          [in]        describes the TNEF file
 *      LPWSTR              [in]        msg subject
 *      MailNonIpmInfo *    [in]        other msg properties
 *      MailAttArray *      [in]        msg attachments
 *
 *  Returns:
 *      BOOL        TRUE indicates success
 *
 *  Side Effects:
 *      szTnefFileName is created on success. Caller is responsible for deleting it.
 *
 */
BOOL WINAPI TnefBuildInfo(const TNEFINFO *, LPWSTR, MailNonIpmInfo *, MailAttArray *);
typedef BOOL (WINAPI * LPFNTNEFBUILDINFO) (const TNEFINFO *, LPWSTR, MailNonIpmInfo *, MailAttArray *);

/*
 *  TnefEncodeFile
 *
 *  Purpose:
 *      Encode an attachment for sending
 *
 *  Parameters:
 *      LPWSTR              [in]        attachment filename
 *      INETENCODE          [in]        encoding method
 *
 *  Returns:
 *      LPWSTR  - filename of encoded file
 *
 *  Side Effects:
 *      file is created
 *
 *  Notes:
 *      Input file is not affected.
 *      Returned file must be deleted by caller.
 *      returned name must be LocalFree'd by caller
 */
LPWSTR WINAPI TnefEncodeFile(LPWSTR, INETENCODE);
typedef LPWSTR (WINAPI * LPFNTNEFENCODEFILE) (LPWSTR, INETENCODE);

/*
 *  TnefDecodeFile
 *
 *  Purpose:
 *      Decodes a file
 *
 *  Parameters:
 *      INETENCODE          [in]        encoding method
 *      LPWSTR              [in]        name of file to decode
 *      LPWSTR              [in]        name of output file
 *
 *  Returns:
 *      BOOL            TRUE on success
 *
 *  Side Effects:
 *      DecodedFileName is created. Caller is responsible for deleting.
 */
BOOL WINAPI TnefDecodeFile(INETENCODE, LPWSTR, LPWSTR);
typedef BOOL (WINAPI * LPFNTNEFDECODEFILE) (INETENCODE, LPWSTR, LPWSTR);

/*
 *  TnefEncodeBuffer
 *
 *  Purpose:
 *      Encode some binary
 *
 *  Parameters:
 *      INETENCODE          [in]        encoding method
 *      UINT                [in]        size of input buffer
 *      BYTE *              [in]        data to encode
 *      UINT *              [in/out]    size of output buffer/encoded data
 *      LPSTR               [in/out]    encoded data
 *
 *  Returns:
 *      BOOL        TRUE on success
 *
 *  Notes:
 *      Output buffer needs to be big enough to contain
 *      all encoded data.
 */
BOOL WINAPI TnefEncodeBuffer(INETENCODE, UINT, BYTE *, UINT *, LPSTR);
typedef BOOL (WINAPI * LPFNTNEFENCODEBUFFER) (INETENCODE, UINT, BYTE *, UINT *, LPSTR);

/*
 *  TnefDecodeBuffer
 *
 *  Purpose:
 *      Decode a buffer of ANSI text
 *
 *  Parameters:
 *      INETENCODE          [in]        encoding method
 *      LPSTR               [in]        buffer to decode
 *      BYTE *              [in]        decoded buffer
 *      UINT *              [in/out]    size of output buffer/decoded data
 *
 *  Returns:
 *      BOOL        TRUE on success
 *
 *  Notes:
 *      Output buffer needs to be big enough to contain
 *      all decoded data.
 */
BOOL WINAPI TnefDecodeBuffer(INETENCODE, LPSTR, BYTE *, UINT *);
typedef BOOL (WINAPI * LPFNTNEFDECODEBUFFER) (INETENCODE, LPSTR, BYTE *, UINT *);

/*
 *  TnefConvertToUnicode
 *
 *  Purpose:
 *      Convert a string encoded in the specified codepage to Unicode
 *
 *  Parameters:
 *      UINT                [in]        codepage to decode from
 *      DWORD               [in]        character-type options
 *      LPCSTR              [in]        input string
 *      int                 [in]        length of the input string
 *      LPWSTR              [in]        output buffer
 *      int                 [in]        size of the output buffer
 *
 *  Returns:
 *      int        if output buffer size is not 0, number of charactes copied to it;
 *                 otherwise, size of the buffer required to contain the output string;
 *                 0 indicates failure
 *
 *  Notes:
 *    The codepages supported by this routine are:
 *      1250  -- Windows 1250 (Central European langugages)
 *      1251  -- Windows 1251 (Cyrillic)
 *      1252  -- Windows 1252 (Western European languages)
 *      1253  -- Windows 1253 (Greek)
 *      1254  -- Windows 1254 (Turkish)
 *      1255  -- Windows 1255 (Hebrew)
 *      1256  -- Windows 1256 (Arabic)
 *      1257  -- Windows 1257 (Baltic languages)
 *      1258  -- Windows 1258 (Vietnamese)
 *      20866 -- KOI8-R (Russian Cyrillic standard)
 *      21886 -- KOI8-U (Ukrainian Cyrillic standard)
 *      28592 -- ISO 8859-2 (Central European languages)
 *      28593 -- ISO 8859-3 (Esperanto/Galician/Maltese/incomplete Turkish)
 *      28594 -- ISO 8859-4 (Baltic languages)
 *      28595 -- ISO 8859-5 (Cyrillic)
 *      28596 -- ISO 8859-6 (Arabic)
 *      28597 -- ISO 8859-7 (Greek)
 *      28598 -- ISO 8859-8 (Hebrew)
 *      28599 -- ISO 8859-9 (Turkish)
 *      28600 -- ISO 8859-10 (Nordic languages, except Skolt Sami)
 *      28604 -- ISO 8859-14 (Celtic)
 *      28605 -- ISO 8859-15 (Western Europe, updated)
 *      65000 -- UTF-7 (7-bit Unicode encoding)
 *      65001 -- UTF-8 (8-bit Unicode encoding)
 */
int WINAPI TnefConvertToUnicode(UINT, DWORD, LPCSTR, int, LPWSTR, int);
typedef BOOL (WINAPI * LPFNTNEFCONVERTTOUNICODE) (UINT, DWORD, LPCSTR, int, LPWSTR, int);

/*
 *  ModifiedUTF7ToUnicode
 *
 *  Purpose:
 *      Converts the IMAP "modified" UTF7 string into straight Unicode.
 *      Includes quoted chars:  \\   \"   &-
 *
 *  Parameters:
 *      LPCSTR              [in]        address of string to convert
 *      int                 [in]        number of bytes in string
 *      LPWSTR              [out]       address of wide-character buffer
 *      int                 [in]        size of output buffer
 *
 *  Returns:
 *      int             character count of Unicode string, including NULL
 *                      terminator.
 */
int WINAPI ModifiedUTF7ToUnicode(LPCSTR lpMultiByteStr, int cchMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
typedef int (WINAPI * LPFNMODIFIEDUTF7TOUNICODE) (LPCSTR, int, LPWSTR, int);

/*
 *  UnicodeToModifiedUTF7
 *
 *  Purpose:
 *      Converts the straight Unicode string into IMAP "modified" UTF7.
 *      Quotes chars:  \   "   &
 *
 *  Parameters:
 *      LPCWSTR             [in]        address of string to convert
 *      int                 [in]        number of bytes in string
 *      LPSTR               [out]       address of wide-character buffer
 *      int                 [in]        size of output buffer
 *
 *  Returns:
 *      int             character count of Unicode string, including NULL
 *                      terminator.
 */
int WINAPI UnicodeToModifiedUTF7(LPCWSTR wszIn, int cchIn, LPSTR pchOut, int cchOut);
typedef int (WINAPI * LPFNUNICODETOMODIFIEDUTF7) (LPCWSTR, int, LPSTR, int);

#ifdef      __cplusplus
}
#endif      /* __cplusplus */

#endif      /* _TNEFAPI_H_ */
