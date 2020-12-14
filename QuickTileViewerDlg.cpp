/////////////////////////////////////////////////////////////////////////////
// Name:        QuickTileViewerDlg.cpp
// Purpose:     
// Author:      Jason Champion
// Modified by: 
// Created:     15/09/2006 13:20:04
// RCS-ID:      
// Copyright:   (c) 2006
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "QuickTileViewerDlg.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/bitmap.h"
#include "wx/dialog.h"
#include "wx/image.h"
#include "wx/aboutdlg.h"
#include "wx/filesys.h"
#include "wx/fs_zip.h"
#include "wx/dataobj.h"
#include "wx/clipbrd.h"
#include "wx/metafile.h"
#include "wx/accel.h"
#include "wx/stdpaths.h"
#include "QuickTileViewerDlg.h"
#include "QuickTileViewerPrint.h"
#include <algorithm>

#if !wxUSE_PRINTING_ARCHITECTURE
#error "You must set wxUSE_PRINTING_ARCHITECTURE to 1 in setup.h, and recompile the library."
#endif

IMPLEMENT_DYNAMIC_CLASS( QuickTileViewerDlg, wxFrame )

BEGIN_EVENT_TABLE( QuickTileViewerDlg, wxFrame )
    EVT_CLOSE( QuickTileViewerDlg::OnCloseWindow )
    EVT_BUTTON( ID_BTN_MIRROR, QuickTileViewerDlg::OnBtnMirrorClick )
    EVT_BUTTON( ID_BTN_RESCALE, QuickTileViewerDlg::OnBtnRescaleClick )
    EVT_BUTTON( ID_BTN_ROTATE, QuickTileViewerDlg::OnBtnRotateClick )
    EVT_BUTTON( ID_BTN_BROWSEOUTPUT, QuickTileViewerDlg::OnBtnBrowseoutputClick )
	EVT_BUTTON( ID_BTN_REVERT, QuickTileViewerDlg::OnBtnLoadClick )
    EVT_TEXT( ID_TXT_THRESHOLD, QuickTileViewerDlg::OnTxtThresholdUpdated )
//EVT_MENU( ID_FILE_SAVE, QuickTileViewerDlg::OnBtnSaveClick )
//EVT_MENU( ID_FILE_SAVE_AS, QuickTileViewerDlg::OnBtnSaveAsClick )
	EVT_MENU( ID_FILE_LOAD, QuickTileViewerDlg::OnBtnBrowseinputClick )
	EVT_MENU( ID_FILE_REVERT, QuickTileViewerDlg::OnBtnLoadClick )
	EVT_MENU( ID_TRANSFORM_ROTATE_RIGHT, QuickTileViewerDlg::OnBtnRotateClick )
	EVT_MENU( ID_TRANSFORM_ROTATE_LEFT, QuickTileViewerDlg::OnBtnRotateRightClick )
	EVT_MENU( ID_TRANSFORM_MIRROR_VERTICAL, QuickTileViewerDlg::OnBtnMirrorRightClick )
	EVT_MENU( ID_TRANSFORM_MIRROR_HORIZONTAL, QuickTileViewerDlg::OnBtnMirrorClick )
	EVT_MENU( ID_TRANSFORM_RESCALE_SMALLER, QuickTileViewerDlg::OnBtnRescaleClick )
	EVT_MENU( ID_TRANSFORM_RESCALE_LARGER, QuickTileViewerDlg::OnBtnRescaleRightClick )
	EVT_MENU( ID_HELP_ABOUT, QuickTileViewerDlg::OnBtnAboutClick )
	EVT_MENU( ID_HELP_HELP, QuickTileViewerDlg::OnBtnHelpClick )
	EVT_MENU( ID_FILE_PASTE, QuickTileViewerDlg::OnBtnFilePaste )
    EVT_MENU( ID_FILE_PRINT, QuickTileViewerDlg::OnPrint )
    EVT_MENU( ID_FILE_PRINT_PREVIEW, QuickTileViewerDlg::OnPrintPreview )
    EVT_MENU( ID_FILE_PAGE_SETUP, QuickTileViewerDlg::OnPageSetup )
END_EVENT_TABLE()

QuickTileViewerDlg::QuickTileViewerDlg( )
{
}

QuickTileViewerDlg::~QuickTileViewerDlg()
{
}

QuickTileViewerDlg::QuickTileViewerDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

bool QuickTileViewerDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    _btnMirror = NULL;
    _btnRotate = NULL;
    _btnRescale = NULL;
    _bmpImage[0] = NULL;
    _bmpImage[1] = NULL;
    _bmpImage[2] = NULL;
    _bmpImage[3] = NULL;
    _bmpImage[4] = NULL;
    _bmpImage[5] = NULL;
    _bmpImage[6] = NULL;
    _bmpImage[7] = NULL;
    _bmpImage[8] = NULL;
	_btnRevert = NULL;
    _mainSizer = NULL;
	_dropTarget = NULL;
    _mainFrame = NULL;
    _mainPanel = NULL;
    _mainMenu = NULL;
    _fileMenu = NULL;
    _transformMenu = NULL;
    _helpMenu = NULL;
    _statusBar = NULL;
	_helpCtrl = NULL;
    _printData = NULL;
    _pageSetupData = NULL;
	_scaleFactor = 1.0;
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxFrame::Create( parent, id, caption, pos, size, style );
	wxFileSystem::AddHandler(new wxZipFSHandler);
	wxInitAllImageHandlers();
	CreateControls();
	if( _icon.LoadFile(_T("quicktile16x16.ico"), wxBITMAP_TYPE_ICO ))
	{
		SetIcon(_icon);
	}
	_dropTarget = new QuickTileViewerDropTarget(this);
	wxWindow::SetDropTarget( _dropTarget );
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    _printData = new wxPrintData;
    _printData->SetPaperId( wxPAPER_LETTER );
    _pageSetupData = new wxPageSetupDialogData(*_printData);
    _pageSetupData->SetDefaultMinMargins(true);
    //Centre();
	return true;
}

void QuickTileViewerDlg::CreateControls()
{    
    _mainFrame = this;
	// Set up menus
    _mainMenu = new wxMenuBar;
    _fileMenu = new wxMenu;
    _fileMenu->Append( ID_FILE_LOAD, "Load File\tAlt+L", "Load file from disk" );
	_fileMenu->Append( ID_FILE_PASTE, "Paste\tCtrl+V", "Paste image data from the clipboard" );
    _fileMenu->Append( ID_FILE_REVERT, "Revert\tAlt+V", "Revert to original file" );
    _fileMenu->Append( ID_FILE_PAGE_SETUP, "Page Setup\tCtrl+S", "" );
    _fileMenu->Append( ID_FILE_PRINT, "Print\tAlt+P", "" );
    _fileMenu->Append( ID_FILE_PRINT_PREVIEW, "Print Preview\tAlt+W", "" );
    _mainMenu->Append(_fileMenu, _("File"));
    _transformMenu = new wxMenu;
	_transformMenu->Append( ID_TRANSFORM_MIRROR_HORIZONTAL, "Mirror Horizontal\tCtrl+M", "" );
	_transformMenu->Append( ID_TRANSFORM_MIRROR_VERTICAL, "Mirror Vertical\tAlt+M", "" );
	_transformMenu->Append( ID_TRANSFORM_RESCALE_LARGER, "Rescale Larger\tCtrl+R", "" );
	_transformMenu->Append( ID_TRANSFORM_RESCALE_SMALLER, "Rescale Smaller\tAlt+R", "" );
    _transformMenu->Append( ID_TRANSFORM_ROTATE_RIGHT, "Rotate Right\tAlt+O", "" );
    _transformMenu->Append( ID_TRANSFORM_ROTATE_LEFT, "Rotate Left\tCtrl+O", "" );
    _mainMenu->Append(_transformMenu, _("Transform"));
    _helpMenu = new wxMenu;
	_helpMenu->Append( ID_HELP_HELP, "Help\tF1" );
    _helpMenu->Append( ID_HELP_ABOUT, "About\tAlt+A" );
    _mainMenu->Append( _helpMenu, _("Help") );
    _mainFrame->SetMenuBar(_mainMenu);

    wxSizer* itemSizer1 = new wxBoxSizer(wxVERTICAL);
    _mainFrame->SetSizer(itemSizer1);

    _mainPanel = new wxPanel( this, ID_MAIN_PANEL );

    wxPanel* itemDialog1 = _mainPanel;

    _mainSizer = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(_mainSizer);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    _mainSizer->Add(itemBoxSizer3, 0, wxALIGN_LEFT|wxALL, 1);

    _btnMirror = new wxButton( itemDialog1, ID_BTN_MIRROR, _("Mirror"), wxDefaultPosition, wxSize( 60, 24 ), 0 );
    itemBoxSizer3->Add(_btnMirror, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
	_btnMirror->Connect(ID_BTN_MIRROR, wxEVT_RIGHT_DOWN, wxMouseEventHandler(QuickTileViewerDlg::OnBtnMirrorRightClick), NULL, this);

    _btnRescale = new wxButton( itemDialog1, ID_BTN_RESCALE, _("Rescale"), wxDefaultPosition, wxSize( 60, 24 ), 0 );
    itemBoxSizer3->Add(_btnRescale, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
	_btnRescale->Connect(ID_BTN_RESCALE, wxEVT_RIGHT_DOWN, wxMouseEventHandler(QuickTileViewerDlg::OnBtnRescaleRightClick), NULL, this);

    _btnRevert = new wxButton( itemDialog1, ID_BTN_REVERT, _("Revert"), wxDefaultPosition, wxSize( 60, 24 ), 0 );
    itemBoxSizer3->Add(_btnRevert, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);

    _btnRotate = new wxButton( itemDialog1, ID_BTN_ROTATE, _("Rotate"), wxDefaultPosition, wxSize( 60, 24 ), 0 );
    itemBoxSizer3->Add(_btnRotate, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
	_btnRotate->Connect(ID_BTN_ROTATE, wxEVT_RIGHT_DOWN, wxMouseEventHandler(QuickTileViewerDlg::OnBtnRotateRightClick), NULL, this);

    wxGridSizer* sizerA = new wxGridSizer(3,3,0,0);
    for( int count  = 0; count < 9; count++ )
    {
        wxBitmap _bmpImageBitmap(wxNullBitmap);
        _bmpImage[count] = new wxStaticBitmap( itemDialog1, wxID_STATIC, _bmpImageBitmap, wxDefaultPosition, wxSize( 1, 1 ), wxNO_BORDER );
	    sizerA->Add(_bmpImage[count], 1, wxALIGN_LEFT|wxALL, 0);
    }
    _mainSizer->Add(sizerA, 1, wxALIGN_LEFT|wxALL, 5);

    _statusBar = new wxStatusBar( _mainPanel, ID_STATUS_BAR );
    _statusBar->SetFieldsCount(4);
    _statusBar->SetStatusText( "No File Loaded", 0 );
    _statusBar->SetStatusText( "Width: 0", 1 );
    _statusBar->SetStatusText( "Height: 0", 2 );
	_statusBar->SetStatusText( "100%", 3 );
	int widths[4] = { -1, 80, 80, 54 };
	_statusBar->SetStatusWidths( 4, widths );
    // Filename, height, width.
	_mainSizer->Add(_statusBar, 0, wxGROW|wxALL, 0 );

	_helpCtrl = new wxHtmlHelpController(wxHF_CONTENTS);
	wxString filename = wxStandardPaths::Get().GetDataDir() + "\\quicktileviewer.htb";
	if( !_helpCtrl->AddBook(filename))
	{
		wxMessageBox( "Unable to load help file.  Please make sure that quicktileviewer.htb is in the program directory." );
	}

	// Finally, attach the panel to the main sizer.
	itemSizer1->Add(itemDialog1, 1, wxALL|wxGROW, 0);
}

bool QuickTileViewerDlg::ShowToolTips()
{
    return true;
}

wxBitmap QuickTileViewerDlg::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
}

wxIcon QuickTileViewerDlg::GetIconResource( const wxString& name )
{
    // Icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
}

void QuickTileViewerDlg::OnTxtThresholdUpdated( wxCommandEvent& event )
{
    event.Skip(false);
}

void QuickTileViewerDlg::OnBtnBrowseinputClick( wxCommandEvent& event )
{
	wxFileDialog fdialog( NULL, _T("Choose a file"), _T("."), _T(""), _T("All Supported File Types|*.bmp;*.gif;*.ico;*.jpg;*.jpeg;*.pcx;*.png;*.tga;*.tif;*.tiff;*.xpm;*.BMP;*.GIF;*.ICO;*.JPG;*.JPEG;*.PCX;*.PNG;*.TGA;*.TIF;*.TIFF;*.XPM|BMP Files (*.bmp)|*.bmp;*.BMP|GIF Files (*.gif)|*.gif;*.GIF|Icon Files (*.ico)|*.ico;*.ICO|JPEG Files (*.jpg,*.jpeg)|*.jpg;*.jpeg;*.JPG;*.JPEG|PCX Files (*.pcx)|*.pcx;*.PCX|PNG Files (*.png)|*.png;*.PNG|TGA Files (*.tga)|*.tga;*.TGA|TIF Files (*.tif,*.tiff) |*.tif;*.tiff;*.TIF;*.TIFF|X Pixmap Files (*.xpm)|*.xpm;*.XPM||"), wxFD_OPEN|wxFD_CHANGE_DIR );
	wxString fileName;
	if( fdialog.ShowModal() != wxID_OK )
	{
		return;
	}
	fileName = fdialog.GetPath();
	_statusBar->SetStatusText( fileName, 0 );
	wxCommandEvent nullEvent;
	OnBtnLoadClick( nullEvent );
    event.Skip(false);
}

void QuickTileViewerDlg::OnBtnBrowseoutputClick( wxCommandEvent& event )
{
	wxFileDialog fdialog( NULL, _T("Choose a file"), _T("."), _T(""), _T("BMP and GIF files (*.bmp;*.gif)|*.bmp;*.gif|BMP Files (*.bmp)|*.bmp|Icon Files (*.ico)|*.gif|JPEG Files (*.jpg)|*.jpg|PNG Files (*.png)|*.png|TIFF Files (*.tif) |*.tif|X Pixmap Files (*.xpm)|*.xpm|"), wxFD_SAVE|wxFD_CHANGE_DIR );
	wxString fileName;
	if( fdialog.ShowModal() != wxID_OK )
	{
		return;
	}
	fileName = fdialog.GetPath();
	_statusBar->SetStatusText( fileName, 0 );
    event.Skip(false); 
}

void QuickTileViewerDlg::OnBtnMirrorClick( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		_currentImage = _currentImage.Mirror( false );
        PlaceImageInWindow();
	}
    event.Skip(false);
}

void QuickTileViewerDlg::OnBtnMirrorRightClick( wxMouseEvent& event )
{
	if( _currentImage.Ok() )
	{
		_currentImage = _currentImage.Mirror( true );
        PlaceImageInWindow();
	}
    event.Skip(false);
}

void QuickTileViewerDlg::OnBtnRescaleClick( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		int x = 2;
		_currentImage = _currentImage.Rescale( (_currentImage.GetWidth() / x), (_currentImage.GetHeight() / x) );
        PlaceImageInWindow();
	}
	event.Skip(false);
}

void QuickTileViewerDlg::OnBtnRescaleRightClick( wxMouseEvent& event )
{
	if( _currentImage.Ok() )
	{
		int x = 2;
		_currentImage = _currentImage.Rescale( (_currentImage.GetWidth() * x), (_currentImage.GetHeight() * x) );
        PlaceImageInWindow();
	}
	event.Skip(false);
}

void QuickTileViewerDlg::OnBtnAboutClick( wxCommandEvent& event )
{
	// Show about box.
    wxAboutDialogInfo info;
    info.SetName(_("QuickTileViewer"));
    info.SetVersion(_("1.2"));
    info.SetCopyright(_("(c) 2006-2020 Jason Champion"));
	info.AddDeveloper(_("Jason Champion"));
	info.SetIcon(_icon);
	info.SetLicense(_("QuickTileViewer is free software and may be distributed freely under the terms of the MIT license."));
	info.SetWebSite(_("https://lambdacentauri.com/software_quicktileviewer.htm"));
	info.SetDescription(_("QuickTileViewer uses the wxWidgets libraries."));

    wxAboutBox(info);
    event.Skip(false);
}

void QuickTileViewerDlg::OnBtnHelpClick( wxCommandEvent& event )
{
	_helpCtrl->DisplayContents();
    event.Skip(false);
}

void QuickTileViewerDlg::OnBtnFilePaste( wxCommandEvent& event )
{
	wxBitmapDataObject data;
	wxTheClipboard->Open();
	bool success = wxTheClipboard->GetData(data);
	wxTheClipboard->Close();
	if( success )
	{
		wxBitmap bitmap = data.GetBitmap();
		if( bitmap.Ok() )
		{
			_currentImage = bitmap.ConvertToImage();
            PlaceImageInWindow();
		}
	}
}

void QuickTileViewerDlg::ProcessResize(int x, int y)
{
        if( x == 0 || y == 0 )
        {
                return;
        }
        if( _currentImage.Ok() )
        {
                _currentImage = _currentImage.Rescale( x, y );
        PlaceImageInWindow();
        }
}

void QuickTileViewerDlg::OnBtnRotateClick( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		_currentImage = _currentImage.Rotate90( true );
        PlaceImageInWindow();
	}
    event.Skip(false);
}

void QuickTileViewerDlg::OnBtnRotateRightClick( wxMouseEvent& event )
{
	if( _currentImage.Ok() )
	{
		_currentImage = _currentImage.Rotate90( false );
        PlaceImageInWindow();
	}
    event.Skip(false);
}

void QuickTileViewerDlg::LoadFile(wxString filename )
{
	_statusBar->SetStatusText( filename, 0 );
	wxCommandEvent nullEvent;
	OnBtnLoadClick( nullEvent );
}

void QuickTileViewerDlg::OnBtnLoadClick( wxCommandEvent& event )
{
    wxString filename = _statusBar->GetStatusText( 0 );
    _currentImage.LoadFile( filename, wxBITMAP_TYPE_ANY );
    if( _currentImage.Ok() )
    {
        PlaceImageInWindow();
		_statusBar->SetStatusText( filename, 0 );
    }
    event.Skip(false);
}

void QuickTileViewerDlg::OnCloseWindow( wxCloseEvent& event )
{
	Destroy();
    event.Skip(false);
}

bool QuickTileViewerDlg::OnDropFiles(const wxString& filename)
{
	_currentImage.LoadFile( filename, wxBITMAP_TYPE_ANY );
    if( _currentImage.Ok() )
    {
		_statusBar->SetStatusText( filename, 0 );
        PlaceImageInWindow();
    }
	return true;
}

bool QuickTileViewerDropTarget::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
{
	if( filenames.GetCount() < 1 || !_dialog )
	{
		return false;
	}

	return _dialog->OnDropFiles( filenames[0] );
}

void QuickTileViewerDlg::SetStatusSize( int width, int height )
{
	_statusBar->SetStatusText( wxString::Format("Width: %d", width ), 1 );
	_statusBar->SetStatusText( wxString::Format("Height: %d", height ), 2 );
	_statusBar->SetStatusText( wxString::Format("%d%%", (int)(_scaleFactor * 100 )), 3);
}

void QuickTileViewerDlg::OnPrint(wxCommandEvent& WXUNUSED(event))
{
    wxPrintDialogData printDialogData(* _printData);

    wxPrinter printer(& printDialogData);
    QuickTileViewerPrint printout(_T("QuickTileViewer Printout"));
    if( _currentImage.Ok() )
    {
        printout.SetBitmap(wxBitmap(_currentImage));
    }
    if (!printer.Print(this, &printout, true /*prompt*/))
    {
        if (wxPrinter::GetLastError() == wxPRINTER_ERROR)
        {
            wxMessageBox(_T("There was a problem printing.\nPerhaps your current printer is not set correctly?"), _T("Printing"), wxOK);
        }
    }
    else
    {
        (*_printData) = printer.GetPrintDialogData().GetPrintData();
    }
}

void QuickTileViewerDlg::OnPrintPreview(wxCommandEvent& WXUNUSED(event))
{
    // Pass two printout objects: for preview, and possible printing.
    wxPrintDialogData printDialogData(* _printData);
    QuickTileViewerPrint* printoutForPreview = new QuickTileViewerPrint;
    QuickTileViewerPrint* printoutForPrint = new QuickTileViewerPrint;
    if( _currentImage.Ok() )
    {
        printoutForPreview->SetBitmap(wxBitmap(_currentImage));
        printoutForPrint->SetBitmap(wxBitmap(_currentImage));
    }
    wxPrintPreview *preview = new wxPrintPreview(printoutForPreview, printoutForPrint, & printDialogData);
    if (!preview->Ok())
    {
        delete preview;
        wxMessageBox(_T("There was a problem previewing.\nPerhaps your current printer is not set correctly?"), _T("Previewing"), wxOK);
        return;
    }

    wxPreviewFrame *frame = new wxPreviewFrame(preview, this, _T("Print Preview"), wxPoint(100, 100), wxSize(600, 650));
    frame->Centre(wxBOTH);
    frame->Initialize();
    frame->Show();
}

void QuickTileViewerDlg::OnPageSetup(wxCommandEvent& WXUNUSED(event))
{
    wxPageSetupDialog pageSetupDialog(this, _pageSetupData);

    pageSetupDialog.ShowModal();

    (*_printData) = pageSetupDialog.GetPageSetupData().GetPrintData();
    (*_pageSetupData) = pageSetupDialog.GetPageSetupData();
}

void QuickTileViewerDlg::PlaceImageInWindow()
{
    if( _currentImage.Ok() )
    {
		// Allow an arbitrary 16 pixel border for width.
		int width = wxSystemSettings::GetMetric ( wxSYS_SCREEN_X ) - 18;
		// Allow an arbitrary 96 pixel border for height.
		int height = wxSystemSettings::GetMetric ( wxSYS_SCREEN_Y ) - 154;
		if( _currentImage.GetWidth() > width || _currentImage.GetHeight() > height )
		{
			double xratio = (double)width / (double)_currentImage.GetWidth();
			double yratio = (double)height / (double)_currentImage.GetHeight();
			double ratio = std::min( xratio, yratio );
            wxImage img = _currentImage.Scale( _currentImage.GetWidth() * ratio, _currentImage.GetHeight() * ratio );
			_bmpImage[0]->SetBitmap( img );
			_bmpImage[1]->SetBitmap( img );
			_bmpImage[2]->SetBitmap( img );
			_bmpImage[3]->SetBitmap( img );
			_bmpImage[4]->SetBitmap( img );
			_bmpImage[5]->SetBitmap( img );
			_bmpImage[6]->SetBitmap( img );
			_bmpImage[7]->SetBitmap( img );
			_bmpImage[8]->SetBitmap( img );
			_scaleFactor = ratio;
		}
		else
		{
			_scaleFactor = 1.0;
			_bmpImage[0]->SetBitmap( _currentImage );
			_bmpImage[1]->SetBitmap( _currentImage );
			_bmpImage[2]->SetBitmap( _currentImage );
			_bmpImage[3]->SetBitmap( _currentImage );
			_bmpImage[4]->SetBitmap( _currentImage );
			_bmpImage[5]->SetBitmap( _currentImage );
			_bmpImage[6]->SetBitmap( _currentImage );
			_bmpImage[7]->SetBitmap( _currentImage );
			_bmpImage[8]->SetBitmap( _currentImage );
		}
		_bmpImage[0]->SetSize( (_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[0]->SetSizeHints((_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[1]->SetSize( (_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[1]->SetSizeHints((_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[2]->SetSize( (_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[2]->SetSizeHints((_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[3]->SetSize( (_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[3]->SetSizeHints((_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[4]->SetSize( (_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[4]->SetSizeHints((_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[5]->SetSize( (_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[5]->SetSizeHints((_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[6]->SetSize( (_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[6]->SetSizeHints((_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[7]->SetSize( (_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[7]->SetSizeHints((_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[8]->SetSize( (_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage[8]->SetSizeHints((_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		SetStatusSize( _currentImage.GetWidth(), _currentImage.GetHeight() );
		Fit();
		Refresh();
    }
}
