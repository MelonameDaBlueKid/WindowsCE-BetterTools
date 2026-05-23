//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft shared
// source or premium shared source license agreement under which you licensed
// this source code. If you did not accept the terms of the license agreement,
// you are not authorized to use this source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the SOURCE.RTF on your install media or the root of your tools installation.
// THE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
/*++

Module Name:

kdioctl.h

Abstract:

Private version of kdioctl.h

Notes:

--*/

#ifndef _KDIOCTL_H_
#define _KDIOCTL_H_


//IOCTL Codes handled by KD


#define IOCTL_DBG_FEX_OFF             0
// lpInBuf:     ignored
// nInBufSize:  ignored
// lpOutBuf:    ignored
// nOutBufSize: ignored

#define IOCTL_DBG_FEX_ON              1
// lpInBuf:     ignored
// nInBufSize:  ignored
// lpOutBuf:    ignored
// nOutBufSize: ignored

#define IOCTL_DBG_FEX_GET_STATUS      2
// lpInBuf:     ignored
// nInBufSize:  ignored
// lpOutBuf:    pointer to a KDFEX_RULESET_STATUS in which the current status of the ruleset will be returned
// nOutBufSize: sizeof(KDFEX_RULESET_STATUS)

#define IOCTL_DBG_FEX_GET_MAX_RULES   3
// lpInBuf:     ignored
// nInBufSize:  ignored
// lpOutBuf:    pointer to a DWORD in which the max number of rule slots will be stored
// nOutBufSize: sizeof(DWORD)

#define IOCTL_DBG_FEX_GET_RELEVANT_RULE_COUNT  4
// lpInBuf:     ignored
// nInBufSize:  ignored
// lpOutBuf:    pointer to a DWORD in which the number of relevant rules will be stored
// nOutBufSize: sizeof(DWORD)

#define IOCTL_DBG_FEX_ADD_RULE        5
// lpInBuf:     pointer to a KDFEX_RULE_INFO structure that contains the information of the rule that will be added.
// nInBufSize:  sizeof(KDFEX_RULE_INFO)
// lpOutBuf:    pointer to a DWORD in which the index of the added rule will be stored
// nOutBufSize: sizeof(DWORD)

#define IOCTL_DBG_FEX_REMOVE_RULE     6
// lpInBuf:     pointer to a DWORD containing the index of the rule that should be removed
// nInBufSize:  sizeof(DWORD)
// lpOutBuf:    ignored
// nOutBufSize: ignored

#define IOCTL_DBG_FEX_GET_RULE_INFO   7
// lpInBuf:     pointer to a DWORD containing the index of the rule that should be removed
// nInBufSize:  sizeof(DWORD)
// lpOutBuf:    pointer to a KDFEX_RULE_INFO structure in which the information of the rule will be copied to
// nOutBufSize: sizeof(KDFEX_RULE_INFO)


typedef enum _KDFEX_RULESET_STATUS
{
  KDFEX_RULESET_STATUS_OFF    = 0x00,  // Indicates that the exception filtering feature is turned OFF
  KDFEX_RULESET_STATUS_ON     = 0x01   // Indicates that the exception filtering feature is turned ON
} KDFEX_RULESET_STATUS;

//Possible immediate decisions to apply for an exception
//An exception filtering rule always have one decision.
typedef enum _KDFEX_RULE_DECISION
{
   KDFEX_RULE_DECISION_DEFAULT = 0x00, //Reserved, not used
   KDFEX_RULE_DECISION_IGNORE  = 0x01, //Don't break into the debugger
   KDFEX_RULE_DECISION_BREAK   = 0x02, //Break into the debugger
   KDFEX_RULE_DECISION_ABSORB  = 0x03, //Absorb the exception (as if it never happened)
   KDFEX_RULE_DECISION_MASK    = 0xFF  //last value, only used as reference.
} KDFEX_RULE_DECISION;


//Possible Chance values for rule specification
//Note: if a rule applies for "handled" exception it applies for all other "handling level" as well.
//      this means that it is inclusive for more critical chances
//      the logic behind this is: "If we care about handled, we must care about unhandled as well"
typedef enum _KDFEX_HANDLING
{
   KDFEX_HANDLING_DEFAULT          = 0x00,   //Reserved, not used
   KDFEX_HANDLING_HANDLED          = 0x01,   //Expected in a certain way.
   KDFEX_HANDLING_USER_SAFETYNET   = 0x02,   //Catched by an except block of an APP that is using a TRY block to protect itself but does NOT know what occurred.
   KDFEX_HANDLING_KERNEL_SAFETYNET = 0x03,   //Catched by an except block of a PSL server that is using a TRY block to protect itself but does NOT know what occurred.
   KDFEX_HANDLING_UNHANDLED        = 0x04,   //Unexpected, unprotected exception.
   KDFEX_HANDLING_LAST             = 0x05,   //Last value of the ENUM. Used as reference to do safe casts. keep it always at the end.
} KDFEX_HANDLING;

typedef enum _KDFEX_RULE_RELEVANCE_FLAGS
{
   KDFEX_RULE_RELEVANCE_NONE     = 0x00000000, //None of the rule fields is relevant (empty rule)
   KDFEX_RULE_RELEVANCE_GENERAL  = 0x00000001, //Minimum relevance of an active rule. Used on rules that represent the most general cases
   KDFEX_RULE_RELEVANCE_CODE     = 0x00000002, //Flag is on when the exception code field is relevant
   KDFEX_RULE_RELEVANCE_HANDLING = 0x00000004, //Flag is on when the chance field is relevant
   KDFEX_RULE_RELEVANCE_PROCESS  = 0x00000008, //Flag is on when the process name field is relevant
   KDFEX_RULE_RELEVANCE_MODULE   = 0x00000010, //Flag is on when the module name field is relevant
   KDFEX_RULE_RELEVANCE_ADDRESS  = 0x00000020, //Flag is on when the address fields are relevant
   KDFEX_RULE_RELEVANCE_ALL      = 0xFFFFFFFF

} KDFEX_RULE_RELEVANCE_FLAGS;

//Single rule container
typedef struct _KDFEX_RULE_INFO
{
   DWORD          dwSize;              //Should ALWAYS be equal to sizeof(_KDFEX_RULE_INFO). Used to control versioning.
   DWORD          fgRelevanceFlags;    //A combination of one or more relevance flags (from _KDFEX_RULE_RELEVANCE_FLAGS)
   DWORD          dwExceptionCode;     //Relevant exception code to which this rule applies
   KDFEX_HANDLING handlingLevel;       //Relevant exception handling level to which this rule applies (from _KDFEX_CHANCE)
   CHAR           szProcessName[128];  //Relevant process name to which this rule applies. Must be NULL terminated.
   CHAR           szModuleName[128];   //Relevant module name to which this rule applies. Must be NULL terminated.
   DWORD          dwFirstAddress;      //Relevant beginning of the address range to which this rule applies.
   DWORD          dwLastAddress;       //Relevant end of the address range to which this rule applies
   KDFEX_RULE_DECISION decision;       //Decision that the kernel debugger will make if an exception matches this rule. (from _KDFEX_RULE_DECISION)
} KDFEX_RULE_INFO;


#endif

