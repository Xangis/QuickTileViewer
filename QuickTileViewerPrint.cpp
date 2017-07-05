#include "QuickTileViewerPrint.h"

bool QuickTileViewerPrint::OnPrintPage(int page)
{
    wxDC *dc = GetDC();
    if (dc)
    {
        if (page == 1)
            DrawPage(dc);

        return true;
    }
    else
        return false;
}

bool QuickTileViewerPrint::OnBeginDocument(int startPage, int endPage)
{
    if (!wxPrintout::OnBeginDocument(startPage, endPage))
        return false;

    return true;
}

void QuickTileViewerPrint::GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo)
{
    *minPage = 1;
    *maxPage = 1;
    *selPageFrom = 1;
    *selPageTo = 1;
}

bool QuickTileViewerPrint::HasPage(int pageNum)
{
    return ( pageNum == 1 );
}

void QuickTileViewerPrint::DrawPage(wxDC *dc)
{
    // You might use THIS code if you were scaling
    // graphics of known size to fit on the page.

    // We know the graphic size. If we didn't know this,
    // we'd need to calculate it.
    float maxX = _bitmap.GetWidth();
    float maxY = _bitmap.GetHeight();

    // Let's have at least 10 device units margin
    float marginX = 50;
    float marginY = 50;

    // Add the margin to the graphic size
    maxX += (2*marginX);
    maxY += (2*marginY);

    // Get the size of the DC in pixels
    int w, h;
    dc->GetSize(&w, &h);

    // Calculate a suitable scaling factor
    float scaleX=(float)(w/maxX);
    float scaleY=(float)(h/maxY);

    // Use x or y scaling factor, whichever fits on the DC
    float actualScale = wxMin(scaleX,scaleY);

    // Calculate the position on the DC for centring the graphic
    float posX = (float)((w - (maxX*actualScale))/2.0);
    float posY = (float)((h - (maxY*actualScale))/2.0);

    // Set the scale and origin
    dc->SetUserScale(actualScale, actualScale);
    dc->SetDeviceOrigin( (long)posX, (long)posY );

    if( _bitmap.Ok() )
    {
        dc->DrawBitmap( _bitmap, 50, 50 );
    }
}

