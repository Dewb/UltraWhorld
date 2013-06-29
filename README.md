UltraWhorldFFGL
===========

#### FFGL (FreeFrame 1.5) port of Chris Korda's Whorld visualizer

The original [Whorld](http://whorld.sourceforge.net) and its FreeFrame 1.0 plugin form, UltraWhorld are built with Visual C++ 6.0 and 
make use of GDI, MFC, DirectDraw, and other Windows platform features.

This repo is an effort to get this rich and popular effect running in FFGL hosts
like Resolume and other cross-platform OpenGL environments.

#### Status/Plan

July should conclude phase 1 of the port. Most core functionality is working; patches, 
mirroring, Fill/Outline/XOR modes are some notable exceptions.

Lines are currently being drawn with native OpenGL line rendering, which unfortunately
does not produce output that's aesthetically on par with GDI's richer 2D line-drawing featureset.

Phase 2 of the port will render lines by creating triangle meshes in a geometry 
shader, which will provide much more control over the appearance of edges, joins, etc. 
and open up interesting possibilities for extension down the road.

#### Repository contents

src: the original UltraWhorld source distro, with small modifications:
* modify stdafx.h to use shim headers rather than Win32 headers on OS X
* replace CList/CArray with portable std::list/std::vector
* chunks of MainFrm have been commented out, will soon replace with #ifdefs.

ffgl: new code
* open UltraWhorldFFGL.xcodeproj for OSX development
* Windows FFGL project files to come in July


