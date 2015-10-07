/************************************************************************/
/* Copyright (c) 2006. D&S Consultants, Inc.  All Rights Reserved       */
/* Permission to use, copy, modify, and distribute this software and    */
/* its documentation for any purpose, without fee and without a signed  */
/* licensing agreement, is hereby prohibited.  Any unauthorized         */
/* reproduction or distribution of this software, or any portion of it, */
/* may result in severe civil and criminal penalties, and will be       */
/* prosecuted to the maximum extent possible under the law.             */
/************************************************************************/
/**
     @file      AboutDlg.h
     @version   $Revision: 4907 $
     @date      $LastChangedDate: 2006-06-28 10:09:21 -0400 (Wed, 28 Jun 2006) $
     @author    $LastChangedBy: jchampion $
     @brief     Digital Radio about box.
     Digital Radio about box wxWidgets header.
     $URL: https://subversion.dsci-usa.com/svn/IRD/DR/trunk/src/DigitalRadio/AboutDlg.h $
*/

#ifndef _ABOUTDLG_H_
#define _ABOUTDLG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "AboutDlg.h"
#endif

/*!
 * Includes
 */

////@begin includes
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_ABOUT 22000
#define SYMBOL_ABOUTDLG_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_ABOUTDLG_TITLE _("About PixelSwapper")
#define SYMBOL_ABOUTDLG_IDNAME ID_ABOUT
#define SYMBOL_ABOUTDLG_SIZE wxSize(400, 300)
#define SYMBOL_ABOUTDLG_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/**
     @brief     About dialog for Digital Radio

	 Implements a wxWidgets about box for the Digital Radio.

	 \author Jason Champion
*/
class AboutDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( AboutDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    AboutDlg( );
    AboutDlg( wxWindow* parent, wxWindowID id = SYMBOL_ABOUTDLG_IDNAME, const wxString& caption = SYMBOL_ABOUTDLG_TITLE, const wxPoint& pos = SYMBOL_ABOUTDLG_POSITION, const wxSize& size = SYMBOL_ABOUTDLG_SIZE, long style = SYMBOL_ABOUTDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ABOUTDLG_IDNAME, const wxString& caption = SYMBOL_ABOUTDLG_TITLE, const wxPoint& pos = SYMBOL_ABOUTDLG_POSITION, const wxSize& size = SYMBOL_ABOUTDLG_SIZE, long style = SYMBOL_ABOUTDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin AboutDlg event handler declarations
////@end AboutDlg event handler declarations

////@begin AboutDlg member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end AboutDlg member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin AboutDlg member variables
////@end AboutDlg member variables
};

#endif
    // _ABOUTDLG_H_
