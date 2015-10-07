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
     @file      AboutDlg.cpp
     @version   $Revision: 4907 $
     @date      $LastChangedDate: 2006-06-28 10:09:21 -0400 (Wed, 28 Jun 2006) $
     @author    $LastChangedBy: jchampion $
     @brief     Digital Radio about box.
     Digital Radio about box implementation using wxWidgets.
     $URL: https://subversion.dsci-usa.com/svn/IRD/DR/trunk/src/DigitalRadio/AboutDlg.cpp $
*/

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "AboutDlg.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "AboutDlg.h"

/*!
 * AboutDlg type definition
 */
IMPLEMENT_DYNAMIC_CLASS( AboutDlg, wxDialog )

/*!
 * AboutDlg event table definition
 */
BEGIN_EVENT_TABLE( AboutDlg, wxDialog )
////@begin AboutDlg event table entries
////@end AboutDlg event table entries
END_EVENT_TABLE()

/*!
 * AboutDlg constructors
 */
AboutDlg::AboutDlg( )
{
}

AboutDlg::AboutDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * AboutDlg creator
 */
bool AboutDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin AboutDlg member initialisation
////@end AboutDlg member initialisation

////@begin AboutDlg creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end AboutDlg creation
    return true;
}

/*!
 * Control creation for AboutDlg
 */
void AboutDlg::CreateControls()
{    
////@begin AboutDlg content construction
    AboutDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, 0, 7);

	wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("PixelSwapper Version 1\n(c) 2006 Zeta Centauri, Inc.\nDeveloped by Jason Champion\nhttp://www.zetacentauri.com"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 10);


////@end AboutDlg content construction
}

/*!
 * Should we show tooltips?
 */
bool AboutDlg::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */
wxBitmap AboutDlg::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin AboutDlg bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end AboutDlg bitmap retrieval
}

/*!
 * Get icon resources
 */
wxIcon AboutDlg::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin AboutDlg icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end AboutDlg icon retrieval
}
