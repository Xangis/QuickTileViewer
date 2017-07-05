#ifndef _WXSELECTABLEBITMAP_H_
#define _WXSELECTABLEBITMAP_H_

#include "wx/wx.h"
#include "wx/bitmap.h"
#include "wx/image.h"
#include "wx/dcbuffer.h"

class wxSelectableBitmap: public wxControl
{
public:
	wxSelectableBitmap() : wxControl() { }
    wxSelectableBitmap( wxWindow* parent, wxWindowID id, const wxBitmap& value, const wxPoint& pos, const wxSize& size, long style )
    {
        Create (parent, id, pos, size, style );
	    _bitmap = value;
    }
	void OnLButtonDown(wxMouseEvent& event);
	void OnLButtonUp(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnPaint(wxPaintEvent& event);
	void SetBitmap( wxImage image );
        void PaintRect( wxDC& dc );
	void GetSelection( wxRect& retval ) { retval = _selectionRect; }
	void ResetSelection();
	void UpdateSelection( wxPoint& point );
        wxVisualAttributes GetDefaultAttributes() const;
private:
	wxRect _selectionRect;
	wxBitmap _bitmap;
	DECLARE_EVENT_TABLE()
};

#endif
