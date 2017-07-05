#include "wxSelectableBitmap.h"

BEGIN_EVENT_TABLE( wxSelectableBitmap, wxControl )
	EVT_LEFT_DOWN(wxSelectableBitmap::OnLButtonDown)
	EVT_LEFT_UP(wxSelectableBitmap::OnLButtonUp)
	EVT_MOTION(wxSelectableBitmap::OnMouseMove)
	EVT_PAINT(wxSelectableBitmap::OnPaint)
END_EVENT_TABLE()

void wxSelectableBitmap::OnLButtonDown(wxMouseEvent& event)
{
	// this is in screen coords.  Use ScreenToClient if you need this in coords for your window
    wxRect oldRect = _selectionRect;
    wxPoint point = event.GetPosition();
    _selectionRect.SetLeft(point.x);
    _selectionRect.SetTop(point.y);
	_selectionRect.SetBottom(point.y);
	_selectionRect.SetRight(point.x);
	if( !oldRect.IsEmpty() )
	{
		RefreshRect( oldRect );
	}
}

wxVisualAttributes wxSelectableBitmap::GetDefaultAttributes() const
{
    return wxWindow::GetDefaultAttributes();
}

void wxSelectableBitmap::OnLButtonUp(wxMouseEvent& event)
{
    wxPoint point = event.GetPosition();
	UpdateSelection( point );
	//Refresh();
}

void wxSelectableBitmap::OnMouseMove(wxMouseEvent& event)
{
    wxPoint point = event.GetPosition();
	// detect if the mouse is down and dragging a lasso
	// Maintain the initial rect so we know what size to invalidate.

    if ( event.LeftIsDown()  )
    {
		UpdateSelection( point );
    }
}

void wxSelectableBitmap::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    // Shifts the device origin so we don't have to worry
    // about the current scroll position ourselves
    PrepareDC(dc);
	if( _bitmap.Ok() )
	{
		dc.DrawBitmap(_bitmap, 0, 0);
	}
	if( !_selectionRect.IsEmpty())
	{
		PaintRect(dc);
	}
    event.Skip();
}

void wxSelectableBitmap::SetBitmap( wxImage image )
{
	_bitmap = wxBitmap(image);
	ResetSelection();
}

void wxSelectableBitmap::PaintRect( wxDC& dc )
{
	dc.SetPen( *wxGREEN_PEN );
	dc.DrawLine( _selectionRect.GetLeft(), _selectionRect.GetTop() ,
		_selectionRect.GetLeft(), _selectionRect.GetBottom() );
	dc.DrawLine( _selectionRect.GetLeft(), _selectionRect.GetBottom() ,
		_selectionRect.GetRight(), _selectionRect.GetBottom() );
	dc.DrawLine( _selectionRect.GetRight(), _selectionRect.GetBottom(),
		_selectionRect.GetRight(), _selectionRect.GetTop() );
	dc.DrawLine( _selectionRect.GetRight(), _selectionRect.GetTop(),
		_selectionRect.GetLeft(), _selectionRect.GetTop() );
}

void wxSelectableBitmap::ResetSelection()
{
	_selectionRect = wxRect(0, 0, 0, 0);
}

void wxSelectableBitmap::UpdateSelection( wxPoint& point )
{
	wxRect invalid = _selectionRect;
	if( point.x > (_selectionRect.GetRight() - (_selectionRect.GetWidth() / 2)))
	{
		_selectionRect.SetRight( point.x );
		if( point.x > invalid.GetRight() )
		{
			invalid.SetRight( point.x );
		}
	}
	else
	{
		_selectionRect.SetLeft(point.x);
		_selectionRect.SetWidth(invalid.GetRight() - point.x + 1);
		if( point.x < invalid.GetLeft() )
		{
			invalid.SetLeft(point.x);
			invalid.SetWidth(invalid.GetRight() - point.x + 1);
		}
	}

	if( point.y > (_selectionRect.GetBottom() - (_selectionRect.GetHeight() / 2 )))
	{
		_selectionRect.SetBottom( point.y );
		if( point.y > invalid.GetBottom() )
		{
			invalid.SetBottom( point.y );
		}
	}
	else
	{
		_selectionRect.SetTop( point.y );
		_selectionRect.SetHeight(invalid.GetBottom() - point.y + 1);
		if( point.y < invalid.GetTop() )
		{
			invalid.SetTop( point.y );
			invalid.SetHeight(invalid.GetBottom() - point.y + 1);
		}
	}
	// Increase the size of the invalid rect by two in each direction to reduce redraw artifacts.
	invalid.SetTop( invalid.GetTop() - 2 );
	invalid.SetHeight( invalid.GetHeight() + 4 );
	invalid.SetLeft( invalid.GetLeft() - 2 );
	invalid.SetWidth( invalid.GetWidth() + 4 );

    // invalidate the lasso rect so that it's drawn while dragging the mouse.
    RefreshRect(invalid);
}
