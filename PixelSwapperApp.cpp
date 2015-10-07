/////////////////////////////////////////////////////////////////////////////
// Name:        PixelSwapperApp.cpp
// Purpose:     
// Author:      Jason Champion
// Modified by: 
// Created:     15/09/2006 13:12:36
// RCS-ID:      
// Copyright:   (c) 2006
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "extractosplitterApp.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/apptrait.h>
#if wxUSE_STACKWALKER && defined( __WXDEBUG__ )
// silly workaround for the link error with debug configuration:
// \src\common\appbase.cpp
wxString wxAppTraitsBase::GetAssertStackTrace()
{
   return wxT("");
}
#endif

#include "PixelSwapperApp.h"

DECLARE_APP(ExtractoSplitterApp)

IMPLEMENT_APP( ExtractoSplitterApp )

IMPLEMENT_CLASS( ExtractoSplitterApp, wxApp )

BEGIN_EVENT_TABLE( ExtractoSplitterApp, wxApp )
END_EVENT_TABLE()

ExtractoSplitterApp::ExtractoSplitterApp()
{
}

bool ExtractoSplitterApp::OnInit()
{    
#if wxUSE_XPM
    wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
    wxImage::AddHandler(new wxGIFHandler);
#endif
    PixelSwapperDlg* mainWindow = new PixelSwapperDlg(NULL, ID_PIXELSWAPPER_DIALOG, _("Quick Tile Viewer"));
    mainWindow->Show(true);
	if( argc > 1 )
	{
		mainWindow->LoadFile( wxString(argv[1]) );
	}
    return true;
}

int ExtractoSplitterApp::OnExit()
{    
    return wxApp::OnExit();
}

