/////////////////////////////////////////////////////////////////////////////
// Name:        PixelSwapperApp.h
// Purpose:     
// Author:      Jason Champion
// Modified by: 
// Created:     15/09/2006 13:12:36
// RCS-ID:      
// Copyright:   (c) 2006
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _EXTRACTOSPLITTERAPP_H_
#define _EXTRACTOSPLITTERAPP_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "extractosplitterApp.h"
#endif

#include "wx/image.h"
#include "PixelSwapperDlg.h"

class ExtractoSplitterApp: public wxApp
{    
    DECLARE_CLASS( ExtractoSplitterApp )
    DECLARE_EVENT_TABLE()

public:
    ExtractoSplitterApp();
    virtual bool OnInit();
    virtual int OnExit();
};

#endif
