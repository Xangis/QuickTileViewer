;Include Modern UI

  !include "MUI2.nsh"
  !include "FileAssociation.nsh"

Name "QuickTileViewer 1.1"
OutFile "QuickTileViewer1.1Setup.exe"
InstallDir "$PROGRAMFILES\Zeta Centauri\QuickTileViewer"
InstallDirRegKey HKLM "Software\QuickTileViewer" "Install_Dir"
RequestExecutionLevel admin
!define MUI_ICON "quicktile32x32.ico"
!define MUI_UNICON "quicktile32x32.ico"

;Version Information

  VIProductVersion "1.1.0.0"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "QuickTileViewer"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Zeta Centauri"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "Copyright 2006-2012 Zeta Centauri"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "QuickTileViewer Installer"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "1.1.0.0"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductVersion" "1.1.0.0"

;Interface Settings

  !define MUI_ABORTWARNING

;Pages

  !insertmacro MUI_PAGE_LICENSE "License.txt"
;  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
      !define MUI_FINISHPAGE_NOAUTOCLOSE
      !define MUI_FINISHPAGE_RUN
      !define MUI_FINISHPAGE_RUN_CHECKED
      !define MUI_FINISHPAGE_RUN_TEXT "Launch QuickTileViewer"
      !define MUI_FINISHPAGE_RUN_FUNCTION "LaunchProgram"
      !define MUI_FINISHPAGE_SHOWREADME ""
      !define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED
      !define MUI_FINISHPAGE_SHOWREADME_TEXT "Create Desktop Shortcut"
      !define MUI_FINISHPAGE_SHOWREADME_FUNCTION finishpageaction
  !insertmacro MUI_PAGE_FINISH
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;Languages
 
  !insertmacro MUI_LANGUAGE "English"

; The stuff to install
Section "QuickTileViewer"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "QuickTileViewer.exe"
  File "License.txt"
  File "quicktile32x32.ico"
  File "quicktile16x16.ico"
  File "quicktileviewer.htb"  
  File "vcredist_x86.exe"

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\QuickTileViewer "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTileViewer" "DisplayName" "QuickTileViewer"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTileViewer" "DisplayVersion" "1.1"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTileViewer" "Publisher" "Zeta Centauri"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTileViewer" "DisplayIcon" "$INSTDIR\quicktile32x32.ico"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTileViewer" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTileViewer" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTileViewer" "NoRepair" 1
  WriteUninstaller "uninstall.exe"

  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".bmp" "Bitmap File"
  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".gif" "GIF File"
  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".ico" "Icon File"
  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".jpeg" "JPEG Image"
  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".jpg" "JPG Image"
  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".pcx" "PCX File"
  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".png" "PNG Image"
  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".pnm" "PNM File"
  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".tga" "TGA File"
  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".tif" "TIF Image"
  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".tiff" "TIFF Image"
  ${registerExtension} "$INSTDIR\QuickTileViewer.exe" ".xpm" "XPM Image"

  ExecWait '"$INSTDIR\vcredist_x86.exe /q"'

SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Zeta Centauri\QuickTileViewer"
  CreateShortCut "$SMPROGRAMS\Zeta Centauri\QuickTileViewer\QuickTileViewer.lnk" "$INSTDIR\QuickTileViewer.exe" "" "" 0
  ;CreateShortCut "$SMPROGRAMS\Zeta Centauri\QuickTileViewer\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  WriteINIStr "$SMPROGRAMS\Zeta Centauri\QuickTileViewer\QuickTileViewer Website.url" "InternetShortcut" "URL" "http://zetacentauri.com/software_quicktileviewer.htm"
 
SectionEnd

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTileViewer"
  DeleteRegKey HKLM SOFTWARE\QuickTileViewer

  ; Remove files and uninstaller
  Delete $INSTDIR\QuickTileViewer.exe
  Delete $INSTDIR\License.txt
  Delete $INSTDIR\quicktileviewer.htb
  Delete $INSTDIR\quicktile32x32.ico
  Delete $INSTDIR\quicktile16x16.ico
  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Zeta Centauri\QuickTileViewer\*.*"
  Delete "$DESKTOP\QuickTileViewer.lnk"
  Delete "$SMPROGRAMS\Zeta Centauri\QuickTileViewer\QuickTileViewer Website.url"
  ;DeleteINISec "$SMPROGRAMS\Zeta Centauri\QuickTileViewer\QuickTileViewer Website.url" "InternetShortcut"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Zeta Centauri\QuickTileViewer"
  RMDir "$SMPROGRAMS\Zeta Centauri"
  RMDir "$INSTDIR"

  ${unregisterExtension} ".bmp" "Bitmap File"
  ${unregisterExtension} ".gif" "GIF File"
  ${unregisterExtension} ".ico" "Icon File"
  ${unregisterExtension} ".jpeg" "JPEG Image"
  ${unregisterExtension} ".jpg" "JPG Image"
  ${unregisterExtension} ".pcx" "PCX File"
  ${unregisterExtension} ".png" "PNG Image"
  ${unregisterExtension} ".pnm" "PNM File"
  ${unregisterExtension} ".tga" "TGA File"
  ${unregisterExtension} ".tif" "TIF Image"
  ${unregisterExtension} ".tiff" "TIFF Image"
  ${unregisterExtension} ".xpm" "XPM Image"


SectionEnd

; This function is automatically executed when the installer finishes
Function .onGUIEnd
	; Un-register the offer manager plugin with the operating system
        Delete $INSTDIR\vcredist_x86.exe
FunctionEnd


Function LaunchProgram
  ExecShell "" "$SMPROGRAMS\Zeta Centauri\QuickTileViewer\QuickTileViewer.lnk"
FunctionEnd

Function finishpageaction
  CreateShortcut "$DESKTOP\QuickTileViewer.lnk" "$INSTDIR\QuickTileViewer.exe"
FunctionEnd