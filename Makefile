# PixelSwapper makefile.  Requires wxWidgets.
# by default, wx-config from the PATH is used
WX_CONFIG := wx-config

# Main executable file
PROGRAM = QuickTileViewer

# Directory containing library portions of code.
INCLUDEDIR = /usr/local/include/wx-2.8/

# Object files
OBJECTS = AboutDlg.o PixelSwapperApp.o PixelSwapperPrint.o ResizeDlg.o PixelSwapperDlg.o ../wxControls/wxSelectableBitmap.o

CXX = $(shell $(WX_CONFIG) --cxx -ggdb)

.SUFFIXES:	.o .cpp

.cpp.o :
	$(CXX) -ggdb -c -I$(INCLUDEDIR) -I$(INCLUDEDIR2) -I$(INCLUDEDIR3) `$(WX_CONFIG) --cxxflags` -o $@ $<

all:    $(PROGRAM)

$(PROGRAM):	$(OBJECTS)
	$(CXX) -o $(PROGRAM) -I$(INCLUDEDIR) $(OBJECTS) `$(WX_CONFIG) --libs`

clean: 
	rm -f *.o $(PROGRAM)
