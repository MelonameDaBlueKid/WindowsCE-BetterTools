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

#include "stdafx.h"
#include "ptrlist.h"
#include "Macros.h"

CPtrList::CPtrList():
m_pHead(NULL),
m_cNode(0)
{
    m_pHead = new PTRNODE;
    if (m_pHead)
    {
        m_pHead->ptr = NULL;
        m_pHead->next = NULL;
    }
}

CPtrList::~CPtrList()
{
    if (m_pHead)
    {
        RemoveAllNodes();

        delete(m_pHead);
        m_pHead = NULL;
    }
}


void CPtrList::RemoveAllNodes(void)
{
    PTRNODE* pNode;

    if (NULL == m_pHead)
    {
        return;
    }

    while(m_pHead->next)
    {
        pNode = m_pHead->next;
        m_pHead->next = pNode;
        delete(pNode);
        m_cNode--;
    }

    return;
}

HRESULT CPtrList::AddTail(void* ptr)
{
    HRESULT hr = S_OK;
    POSITION pNewNode, pNode = m_pHead;
    
    if (NULL == ptr)
    {
        hr = E_INVALIDARG;
        goto Error;
    }

    CPR(m_pHead);

    while(pNode->next && pNode->next->next)
    {
        pNode = pNode->next;
    }

    pNewNode = new PTRNODE;
    CPR(pNewNode);

    pNewNode->ptr = ptr;
    pNewNode->next = pNode->next;

    pNode->next = pNewNode;
    m_cNode++;

Error:
    return hr;
}

POSITION CPtrList::FindIndex(int iIndex)
{
    POSITION position = NULL;
    int i;

    for(i = 0, position = m_pHead; i < iIndex && position->next; i++)
    {
        position = position->next;
    }

    return position;
}

void* CPtrList::GetAt(POSITION position)
{
    void* ptr = NULL;

    if (position->next)
    {
        ptr = position->next->ptr;
    }

    return ptr;
}

void CPtrList::RemoveHead(void)
{
    if (m_pHead)
    {
        RemoveAt(m_pHead);
    }
    
    return;
}

void CPtrList::RemoveAt(POSITION position)
{
    PTRNODE* pNode = NULL;

    if (position->next)
    {
        pNode = position->next;
        position->next = position->next->next;
    }
    if (pNode)
    {
        delete(pNode);
        m_cNode--;
    }

    return;
}
