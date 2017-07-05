# PixelSwapper makefile.  Requires wxWidgets.
# by default, wx-config from the PATH is used
WX_CONFIG := wx-config

# Main executable file
PROGRAM = QuickTileViewer

# Object files
OBJECTS = AboutDlg.o PixelSwapperApp.o PixelSwapperPrint.o ResizeDlg.o PixelSwapperDlg.o wxSelectableBitmap.o

CXX = $(shell $(WX_CONFIG) --cxx -ggdb)

.SUFFIXES:	.o .cpp

.cpp.o :
	$(CXX) -ggdb -c `$(WX_CONFIG) --cxxflags` -o $@ $<

all:    $(PROGRAM)

$(PROGRAM):	$(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) `$(WX_CONFIG) --libs`

clean: 
	rm -f *.o $(PROGRAM)
