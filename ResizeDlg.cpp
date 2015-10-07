/////////////////////////////////////////////////////////////////////////////
// Name:        ResizeDlg.cpp
// Purpose:     
// Author:      Jason Champion
// Modified by: 
// Created:     02/10/2006 04:35:09
// RCS-ID:      
// Copyright:   (c) 2006
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "ResizeDlg.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "ResizeDlg.h"
#include "PixelSwapperDlg.h"

IMPLEMENT_DYNAMIC_CLASS( ResizeDlg, wxDialog )

BEGIN_EVENT_TABLE( ResizeDlg, wxDialog )
    EVT_TEXT( ID_TEXT_WIDTH, ResizeDlg::OnTextWidthUpdated )
    EVT_TEXT( ID_TEXT_HEIGHT, ResizeDlg::OnTextHeightUpdated )
    EVT_RADIOBUTTON( ID_RADIO_REPROPORTION, ResizeDlg::OnRadioReproportionSelected )
    EVT_RADIOBUTTON( ID_RADIOB_CALCWIDTH, ResizeDlg::OnRadiobCalcwidthSelected )
    EVT_RADIOBUTTON( ID_RADIO_CALCHEIGHT, ResizeDlg::OnRadioCalcheightSelected )
    EVT_BUTTON( ID_BUTTON_OK, ResizeDlg::OnButtonOkClick )
END_EVENT_TABLE()

ResizeDlg::ResizeDlg( )
{
}

ResizeDlg::ResizeDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

bool ResizeDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    _oldWidthText = NULL;
    _oldHeightText = NULL;
    _txtWidth = NULL;
    _txtHeight = NULL;
    _radioReProportion = NULL;
    _radioCalcWidth = NULL;
    _radioCalcHeight = NULL;
    _calcWidth = false;
    _calcHeight = false;

    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
	_mainDlg = (PixelSwapperDlg*)parent;
    return true;
}

void ResizeDlg::CreateControls()
{    
    ResizeDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, _T(""));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALL|wxGROW, 0);

    wxFlexGridSizer* itemFlexGridSizer4 = new wxFlexGridSizer(3, 3, 0, 0);
    itemStaticBoxSizer3->Add(itemFlexGridSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    itemFlexGridSizer4->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Width"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemDialog1, wxID_STATIC, _("Height"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("Old Size:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    _oldWidthText = new wxStaticText( itemDialog1, wxID_STATIC, _("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(_oldWidthText, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    _oldHeightText = new wxStaticText( itemDialog1, wxID_STATIC, _("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(_oldHeightText, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxStaticText* itemStaticText11 = new wxStaticText( itemDialog1, wxID_STATIC, _("New Size:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    _txtWidth = new wxTextCtrl( itemDialog1, ID_TEXT_WIDTH, _T(""), wxDefaultPosition, wxSize(54, -1), 0 );
    itemFlexGridSizer4->Add(_txtWidth, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _txtHeight = new wxTextCtrl( itemDialog1, ID_TEXT_HEIGHT, _T(""), wxDefaultPosition, wxSize(54, -1), 0 );
    itemFlexGridSizer4->Add(_txtHeight, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    _radioReProportion = new wxRadioButton( itemDialog1, ID_RADIO_REPROPORTION, _("None"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    _radioReProportion->SetValue(true);
    itemBoxSizer14->Add(_radioReProportion, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _radioCalcWidth = new wxRadioButton( itemDialog1, ID_RADIOB_CALCWIDTH, _("Calc Width"), wxDefaultPosition, wxDefaultSize, 0 );
    _radioCalcWidth->SetValue(false);
    itemBoxSizer14->Add(_radioCalcWidth, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _radioCalcHeight = new wxRadioButton( itemDialog1, ID_RADIO_CALCHEIGHT, _("Calc Height"), wxDefaultPosition, wxDefaultSize, 0 );
    _radioCalcHeight->SetValue(false);
    itemBoxSizer14->Add(_radioCalcHeight, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer18 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer18, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxButton* itemButton19 = new wxButton( itemDialog1, ID_BUTTON_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer18->Add(itemButton19, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end ResizeDlg content construction
}

bool ResizeDlg::ShowToolTips()
{
    return true;
}

wxBitmap ResizeDlg::GetBitmapResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullBitmap;
}

wxIcon ResizeDlg::GetIconResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullIcon;
}

void ResizeDlg::OnButtonOkClick( wxCommandEvent& event )
{
	_mainDlg->ProcessResize( atoi(_txtWidth->GetLabel().mb_str()), atoi(_txtHeight->GetLabel().mb_str() ));
	EndModal(0);
    event.Skip(false);
}

void ResizeDlg::SetValues( int width, int height )
{
	_oldHeightText->SetLabel( wxString::Format( _("%d"), height ));
	_oldWidthText->SetLabel( wxString::Format( _("%d"), width ));
}

void ResizeDlg::OnTextWidthUpdated( wxCommandEvent& event )
{
    if( _calcHeight == false )
    {
        return;
    }
    int width = atoi(_txtWidth->GetValue().mb_str());
    int origWidth = atoi( _oldWidthText->GetLabel().mb_str());
    int origHeight = atoi( _oldHeightText->GetLabel().mb_str());
    if( width == 0 || origWidth == 0 || origHeight == 0 )
    {
        return;
    }
    double ratio = (double)width / (double)origWidth;
    int height = ((double)origHeight * ratio );
    _txtHeight->SetValue( wxString::Format( _("%d"), height ));
    event.Skip(false);
}

void ResizeDlg::OnTextHeightUpdated( wxCommandEvent& event )
{
    if( _calcWidth == false )
    {
        return;
    }
    int height = atoi(_txtHeight->GetValue().mb_str());
    int origHeight = atoi( _oldHeightText->GetLabel().mb_str());
    int origWidth = atoi( _oldWidthText->GetLabel().mb_str());
    if( height == 0 || origHeight == 0 || origWidth == 0 )
    {
        return;
    }
    double ratio = (double)height / (double)origHeight;
    int width = ((double)origWidth * ratio );
    _txtWidth->SetValue( wxString::Format( _("%d"), width ));
    event.Skip(false);
}

void ResizeDlg::OnRadioReproportionSelected( wxCommandEvent& event )
{
    _calcWidth = false;
    _calcHeight = false;
    _txtWidth->Enable();
    _txtHeight->Enable();
    event.Skip(false);
}

void ResizeDlg::OnRadiobCalcwidthSelected( wxCommandEvent& event )
{
    _calcWidth = true;
    _calcHeight = false;
    _txtWidth->Disable();
    _txtHeight->Enable();
    event.Skip(false);
}

void ResizeDlg::OnRadioCalcheightSelected( wxCommandEvent& event )
{
    _calcHeight = true;
    _calcWidth = false;
    _txtHeight->Disable();
    _txtWidth->Enable();
    event.Skip(false);
}
