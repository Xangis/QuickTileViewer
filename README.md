# QuickTileViewer

A tiled image viewer for Windows and Linux..

QuickTileViewer displays images in a tiled layout so you can see whether they'll 
tile well. It was originally posted on http://zetacentauri.com and was 
downloaded more than 9,000 times before being open-sourced.

![QuickTileViewer Screenshot](https://github.com/Xangis/QuickTileViewer/blob/master/images/QuickTileViewer.png)

A prebuilt Windows installer is in the installer directory:

https://github.com/Xangis/QuickTileViewer/blob/master/installer/QuickTileViewer1.1Setup.exe

It is written in C++ and uses wxWidgets for its user interface.

## Features

- Shows images in a 3x3 grid so you can see whether they will tile well.
- Supports BMP, GIF, ICO, JPG, PCX, PNG, TGA, TIFF, and XPM images.

# Building

Building requires that wxWidgets be installed (3.0 preferred).  

### Linux

There is a Makefile for use on Linux and building should be as simple as running "make".

If your wx-config is in a different location than that in the Makfile, change the path 
in the Makefile.

To get the required wxWidgets development libraries on an Ubuntu or Debian-based 
system, run:

sudo apt-get install libwxgtk3.0-dev

### Windows

To get wxWidgets for Windows, download it here:

http://wxwidgets.org/downloads/

There is a Visual Studio project included as QuickTileViewer.sln. However, you'll need to
edit the "Additional Library Directories" and "Additional Include Directories"
paths in the project settings to point to where wxWidgets is on your system.

If it complains about not finding "wx/wx.h", then you need to set the include
path.

If it complains about a bunch of "unresolved external symbols" starting with wx,
then you need to set the library path.

#### Windows Installer

There is an InnoSetup installer script in the installer directory. You'll need to
edit it to match the paths where your project is located since they are all absolute
paths.

You can get InnoSetup here:

http://www.jrsoftware.org/isinfo.php

# Changelog

### Changes in Version 1.1

- Added support for loading PCX images.
- Added support for loading TGA images.

# Development Status

I consider this application to be feature complete and am not actively developing new 
features for it. However, it does need some improvements to make it work and/or build 
better on some platforms (OSX, for example). This is something I may work on as I 
have time.

I do still maintain this application and will accept pull requests if you have improvements 
to contribute.
