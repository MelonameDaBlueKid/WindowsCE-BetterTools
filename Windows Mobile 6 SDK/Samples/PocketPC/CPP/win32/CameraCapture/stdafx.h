#include <windows.h>
#include <winbase.h>
#include <atlbase.h>

#include <streams.h>
#include <dmodshow.h>
#include <dmoreg.h>
#include <wmcodecids.h>

#include "struct.h"
#include "CPropertyBag.h"
#include "graphmanager.h"
#include "appwindow.h"

#define CHK( x ) do{ if( FAILED( hr = ( x ))) { goto Cleanup; }} while( FALSE );
#define ERR( x ) do{ hr = x; goto Cleanup; } while( FALSE );

