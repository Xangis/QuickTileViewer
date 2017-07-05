/////////////////////////////////////////////////////////////////////////////
// Name:        ResizeDlg.h
// Purpose:     
// Author:      Jason Champion
// Modified by: 
// Created:     02/10/2006 04:35:09
// RCS-ID:      
// Copyright:   (c) 2006
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _RESIZEDLG_H_
#define _RESIZEDLG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "ResizeDlg.h"
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
#define ID_RESIZE_DLG 22000
#define SYMBOL_RESIZEDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_RESIZEDLG_TITLE _("Enter New Size")
#define SYMBOL_RESIZEDLG_IDNAME ID_RESIZE_DLG
#define SYMBOL_RESIZEDLG_SIZE wxSize(400, 300)
#define SYMBOL_RESIZEDLG_POSITION wxDefaultPosition
#define ID_TEXT_WIDTH 22002
#define ID_TEXT_HEIGHT 22003
#define ID_RADIO_REPROPORTION 22010
#define ID_RADIOB_CALCWIDTH 22011
#define ID_RADIO_CALCHEIGHT 22012
#define ID_BUTTON_OK 22001
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

class QuickTileViewerDlg;

class ResizeDlg: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( ResizeDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    ResizeDlg();
    ResizeDlg( wxWindow* parent, wxWindowID id = SYMBOL_RESIZEDLG_IDNAME, const wxString& caption = SYMBOL_RESIZEDLG_TITLE, const wxPoint& pos = SYMBOL_RESIZEDLG_POSITION, const wxSize& size = SYMBOL_RESIZEDLG_SIZE, long style = SYMBOL_RESIZEDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_RESIZEDLG_IDNAME, const wxString& caption = SYMBOL_RESIZEDLG_TITLE, const wxPoint& pos = SYMBOL_RESIZEDLG_POSITION, const wxSize& size = SYMBOL_RESIZEDLG_SIZE, long style = SYMBOL_RESIZEDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin ResizeDlg event handler declarations

    void OnTextWidthUpdated( wxCommandEvent& event );
    void OnTextHeightUpdated( wxCommandEvent& event );
    void OnRadioReproportionSelected( wxCommandEvent& event );
    void OnRadiobCalcwidthSelected( wxCommandEvent& event );
    void OnRadioCalcheightSelected( wxCommandEvent& event );
    void OnButtonOkClick( wxCommandEvent& event );

	void SetValues(int width, int height);
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );

    /// Should we show tooltips?
    static bool ShowToolTips();

    wxStaticText* _oldWidthText;
    wxStaticText* _oldHeightText;
    wxTextCtrl* _txtWidth;
    wxTextCtrl* _txtHeight;
    QuickTileViewerDlg* _mainDlg;
    wxRadioButton* _radioReProportion;
    wxRadioButton* _radioCalcWidth;
    wxRadioButton* _radioCalcHeight;
    bool _calcWidth;
    bool _calcHeight;
};

#endif
    // _RESIZEDLG_H_
