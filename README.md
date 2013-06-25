UltraWhorld
===========

FFGL (FreeFrame 1.5) port of Chris Korda's UltraWhorld FreeFrame 1.0 plugin.

UltraWhorld (and its standalone parent, Whorld) are built with Visual C++ 6.0 and 
make use of GDI, MFC, DirectDraw, and other Windows platform features.

This repo is an effort to get this rich and popular effect running in FFGL hosts
like Resolume and other cross-platform OpenGL environments.

src: the original UltraWhorld source distro, with small modifications:
* modify stdafx.h to use shim headers rather than Win32 headers on OS X
* replace CList/CArray with portable std::list/std::vector

ffgl: new code
* open UltraWhorldFFGL.xcodeproj for OSX development
* Windows FFGL project files to come later

