#############################################################################
# Makefile for building: StrongAIVideoAnalysis
# Generated by qmake (3.1) (Qt 5.14.2)
# Project:  StrongAIVideoAnalysis.pro
# Template: subdirs
# Command: D:\Qt\Qt5.14.2\5.14.2\msvc2017_64\bin\qmake.exe -o Makefile StrongAIVideoAnalysis.pro -spec win32-msvc "CONFIG+=qtquickcompiler"
#############################################################################

MAKEFILE      = Makefile

EQ            = =

first: make_first
QMAKE         = D:\Qt\Qt5.14.2\5.14.2\msvc2017_64\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = copy /y
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = copy /y
INSTALL_PROGRAM = copy /y
INSTALL_DIR   = xcopy /s /q /y /i
QINSTALL      = D:\Qt\Qt5.14.2\5.14.2\msvc2017_64\bin\qmake.exe -install qinstall
QINSTALL_PROGRAM = D:\Qt\Qt5.14.2\5.14.2\msvc2017_64\bin\qmake.exe -install qinstall -exe
DEL_FILE      = del
SYMLINK       = $(QMAKE) -install ln -f -s
DEL_DIR       = rmdir
MOVE          = move
IDC           = idc
IDL           = midl
ZIP           = zip -r -9
DEF_FILE      = 
RES_FILE      = 
SED           = $(QMAKE) -install sed
MOVE          = move
SUBTARGETS    =  \
		sub-mainTestALL


sub-mainTestALL-qmake_all:  FORCE
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	cd mainTestALL\ && $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler"
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && $(MAKE) -f Makefile qmake_all
sub-mainTestALL: $(MAKEFILE) FORCE
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && ( if not exist Makefile $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler" ) && $(MAKE) -f Makefile
sub-mainTestALL-make_first: FORCE
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && ( if not exist Makefile $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler" ) && $(MAKE) -f Makefile 
sub-mainTestALL-all: FORCE
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && ( if not exist Makefile $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler" ) && $(MAKE) -f Makefile all
sub-mainTestALL-clean: FORCE
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && ( if not exist Makefile $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler" ) && $(MAKE) -f Makefile clean
sub-mainTestALL-distclean: FORCE
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && ( if not exist Makefile $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler" ) && $(MAKE) -f Makefile distclean
sub-mainTestALL-install_subtargets: FORCE
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && ( if not exist Makefile $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler" ) && $(MAKE) -f Makefile install
sub-mainTestALL-uninstall_subtargets: FORCE
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && ( if not exist Makefile $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler" ) && $(MAKE) -f Makefile uninstall

Makefile: StrongAIVideoAnalysis.pro ..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\win32-msvc\qmake.conf ..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\spec_pre.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\common\angle.conf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\common\windows-desktop.conf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\win32\windows_vulkan_sdk.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\common\windows-vulkan.conf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\common\msvc-desktop.conf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\qconfig.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3danimation.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3danimation_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dcore.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dcore_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dextras.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dextras_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dinput.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dinput_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dlogic.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dlogic_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquick.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquick_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickanimation.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickanimation_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickextras.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickextras_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickinput.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickinput_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickrender.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickrender_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickscene2d.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickscene2d_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3drender.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3drender_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_accessibility_support_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axbase.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axbase_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axcontainer.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axcontainer_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axserver.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axserver_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_bluetooth.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_bluetooth_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_bootstrap_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_concurrent.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_concurrent_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_core.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_core_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_dbus.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_dbus_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_designer.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_designer_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_designercomponents_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_devicediscovery_support_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_edid_support_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_egl_support_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_eventdispatcher_support_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_fb_support_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_fontdatabase_support_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_gamepad.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_gamepad_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_gui.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_gui_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_help.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_help_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_location.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_location_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_multimedia.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_multimedia_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_multimediawidgets.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_multimediawidgets_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_network.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_network_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_nfc.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_nfc_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_opengl.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_opengl_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_openglextensions.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_openglextensions_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_packetprotocol_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_platformcompositor_support_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_positioning.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_positioning_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_positioningquick.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_positioningquick_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_printsupport.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_printsupport_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qml.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qml_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmldebug_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmldevtools_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmlmodels.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmlmodels_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmltest.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmltest_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmlworkerscript.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmlworkerscript_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qtmultimediaquicktools_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quick.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quick_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickcontrols2.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickcontrols2_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickparticles_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickshapes_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quicktemplates2.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quicktemplates2_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickwidgets.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickwidgets_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_remoteobjects.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_remoteobjects_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_repparser.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_repparser_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_scxml.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_scxml_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_sensors.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_sensors_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_serialbus.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_serialbus_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_serialport.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_serialport_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_sql.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_sql_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_svg.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_svg_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_testlib.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_testlib_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_texttospeech.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_texttospeech_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_theme_support_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_uiplugin.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_uitools.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_uitools_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_vulkan_support_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_webchannel.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_webchannel_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_websockets.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_websockets_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_webview.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_webview_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_widgets.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_widgets_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_windowsuiautomation_support_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_winextras.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_winextras_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_xml.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_xml_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_xmlpatterns.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_xmlpatterns_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_zlib_private.pri \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\qt_functions.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\qt_config.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\win32-msvc\qmake.conf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\spec_post.prf \
		.qmake.stash \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\exclusive_builds.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\common\msvc-version.conf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\toolchain.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\default_pre.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\win32\default_pre.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\resolve_config.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\exclusive_builds_post.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\default_post.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\resources_functions.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\qtquickcompiler.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\precompile_header.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\warn_on.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\qmake_use.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\file_copies.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\win32\windows.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\testcase_targets.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\exceptions.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\yacc.prf \
		..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\lex.prf \
		StrongAIVideoAnalysis.pro
	$(QMAKE) -o Makefile StrongAIVideoAnalysis.pro -spec win32-msvc "CONFIG+=qtquickcompiler"
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\spec_pre.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\common\angle.conf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\common\windows-desktop.conf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\win32\windows_vulkan_sdk.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\common\windows-vulkan.conf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\common\msvc-desktop.conf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\qconfig.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3danimation.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3danimation_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dcore.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dcore_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dextras.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dextras_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dinput.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dinput_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dlogic.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dlogic_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquick.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquick_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickanimation.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickanimation_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickextras.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickextras_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickinput.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickinput_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickrender.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickrender_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickscene2d.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3dquickscene2d_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3drender.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_3drender_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_accessibility_support_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axbase.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axbase_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axcontainer.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axcontainer_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axserver.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_axserver_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_bluetooth.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_bluetooth_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_bootstrap_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_concurrent.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_concurrent_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_core.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_core_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_dbus.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_dbus_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_designer.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_designer_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_designercomponents_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_devicediscovery_support_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_edid_support_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_egl_support_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_eventdispatcher_support_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_fb_support_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_fontdatabase_support_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_gamepad.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_gamepad_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_gui.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_gui_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_help.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_help_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_location.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_location_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_multimedia.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_multimedia_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_multimediawidgets.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_multimediawidgets_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_network.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_network_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_nfc.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_nfc_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_opengl.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_opengl_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_openglextensions.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_openglextensions_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_packetprotocol_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_platformcompositor_support_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_positioning.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_positioning_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_positioningquick.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_positioningquick_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_printsupport.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_printsupport_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qml.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qml_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmldebug_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmldevtools_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmlmodels.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmlmodels_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmltest.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmltest_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmlworkerscript.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qmlworkerscript_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_qtmultimediaquicktools_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quick.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quick_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickcontrols2.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickcontrols2_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickparticles_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickshapes_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quicktemplates2.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quicktemplates2_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickwidgets.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_quickwidgets_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_remoteobjects.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_remoteobjects_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_repparser.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_repparser_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_scxml.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_scxml_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_sensors.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_sensors_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_serialbus.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_serialbus_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_serialport.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_serialport_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_sql.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_sql_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_svg.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_svg_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_testlib.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_testlib_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_texttospeech.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_texttospeech_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_theme_support_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_uiplugin.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_uitools.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_uitools_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_vulkan_support_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_webchannel.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_webchannel_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_websockets.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_websockets_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_webview.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_webview_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_widgets.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_widgets_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_windowsuiautomation_support_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_winextras.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_winextras_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_xml.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_xml_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_xmlpatterns.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_xmlpatterns_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\modules\qt_lib_zlib_private.pri:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\qt_functions.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\qt_config.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\win32-msvc\qmake.conf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\spec_post.prf:
.qmake.stash:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\exclusive_builds.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\common\msvc-version.conf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\toolchain.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\default_pre.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\win32\default_pre.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\resolve_config.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\exclusive_builds_post.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\default_post.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\resources_functions.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\qtquickcompiler.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\precompile_header.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\warn_on.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\qmake_use.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\file_copies.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\win32\windows.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\testcase_targets.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\exceptions.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\yacc.prf:
..\..\Qt5.14.2\5.14.2\msvc2017_64\mkspecs\features\lex.prf:
StrongAIVideoAnalysis.pro:
qmake: FORCE
	@$(QMAKE) -o Makefile StrongAIVideoAnalysis.pro -spec win32-msvc "CONFIG+=qtquickcompiler"

qmake_all: sub-mainTestALL-qmake_all FORCE

make_first: sub-mainTestALL-make_first  FORCE
all: sub-mainTestALL-all  FORCE
clean: sub-mainTestALL-clean  FORCE
distclean: sub-mainTestALL-distclean  FORCE
	-$(DEL_FILE) Makefile
	-$(DEL_FILE) .qmake.stash
install_subtargets: sub-mainTestALL-install_subtargets FORCE
uninstall_subtargets: sub-mainTestALL-uninstall_subtargets FORCE

sub-mainTestALL-debug:
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && ( if not exist Makefile $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler" ) && $(MAKE) -f Makefile debug
debug: sub-mainTestALL-debug

sub-mainTestALL-release:
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && ( if not exist Makefile $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler" ) && $(MAKE) -f Makefile release
release: sub-mainTestALL-release

sub-mainTestALL-check:
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && ( if not exist Makefile $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler" ) && $(MAKE) -f Makefile check
check: sub-mainTestALL-check

sub-mainTestALL-benchmark:
	@if not exist mainTestALL\ mkdir mainTestALL\ & if not exist mainTestALL\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd mainTestALL\ && ( if not exist Makefile $(QMAKE) -o Makefile D:\Qt\Projects\StrongAIVideoAnalysis\mainTestALL\mainTestALL.pro -spec win32-msvc "CONFIG+=qtquickcompiler" ) && $(MAKE) -f Makefile benchmark
benchmark: sub-mainTestALL-benchmark
install:install_subtargets  FORCE

uninstall: uninstall_subtargets FORCE

FORCE:

