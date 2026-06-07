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

#if !defined(AFX_PTRLIST_H__)
#define AFX_PTRLIST_H__

typedef struct tagPtrNode
{
    void*                ptr;
    struct tagPtrNode*    next;
} PTRNODE;

typedef PTRNODE* POSITION;

class CPtrList
{
public:
    CPtrList();
    ~CPtrList();

    int GetCount(void) { return m_cNode; };
    HRESULT AddTail(void* ptr);
    POSITION GetHeadPosition(void) { return m_pHead; }
    POSITION FindIndex(int iIndex);
    void* GetAt(POSITION position);
    void RemoveHead(void);
    void RemoveAt(POSITION position);

private:
    void RemoveAllNodes(void);

private:
    PTRNODE* m_pHead;
    int      m_cNode;
};

#endif // !defined(AFX_PTRLIST_H__)