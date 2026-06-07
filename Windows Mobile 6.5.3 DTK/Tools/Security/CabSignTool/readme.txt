CabSignTool
===========
Copyright(c) 2006 Microsoft Corporation 


CabSignTool.exe signs a CAB and all its executable content (.exe, .dll) with specified certificate(s).

Usage:

CABSIGNTOOL source destination [options]
    Uses the same certificate to sign both the CAB and its executable content.

CABSIGNTOOL source destination [options] -exesign [options]
    Uses the first certificate to sign the CAB and the second.
    certificate to sign its executable content.

source       Name of unsigned input CAB file (.cab or .hme).
destination  Name of signed output CAB file.
options      Parameters to be used by signtool.exe
             Use signtool.exe /? for a full list.
exesign      Specify this parameter and subsequent signtool.exe options
             to sign the executable contents with a different certificate.

e.g.  cabsigntool.exe c:\generic.cab c:\generic.cab -f c:\cabpriv.pfx
