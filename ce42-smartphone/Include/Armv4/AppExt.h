/*****************************************************************************

    File: AppExt.h
    Purpose: Application extension interface for mobile apps.

    History:
        Created - KK 6-21-2

*/

#pragma once


typedef GUID ITEM_TYPE_ID;

struct ItemRef
{
    ITEM_TYPE_ID* pType;
    void* pRef;
};

struct ItemRefArray
{
    int cRefs;
    ItemRef rgRefs[1]; // rgRefs has cRefs entries
};

#define CFNAME_ITEMREFARRAY TEXT("ItemRefArray")



