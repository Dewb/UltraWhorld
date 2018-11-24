// Copyleft 2007 Chris Korda
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.
/*
        chris korda
 
		revision history:
		rev		date	comments
        00      25jul07	initial version
		01		31jan08	add shear and global parameters

		define UltraWhorld freeframe parameters
 
*/

//							 1234567890123456
FFPARM(CLEAR,            0,    "Clear           ", FF_TYPE_EVENT)
FFPARM(SPEED,			.5,	"Speed           ", FF_TYPE_STANDARD)
FFPARM(ZOOM,			.5,	"Zoom            ", FF_TYPE_STANDARD)
FFPARM(RING_GROWTH,        .5,    "Ring Growth     ", FF_TYPE_STANDARD)
FFPARM(RING_SPACING,    .5,    "Ring Spacing    ", FF_TYPE_STANDARD)
FFPARM(LINE_WIDTH,        .5,    "Line Width      ", FF_TYPE_STANDARD)
FFPARM(POLY_SIDES,        .5,    "Poly Sides      ", FF_TYPE_STANDARD)
FFPARM(ROTATE_SPEED,    .5,    "Rotate Speed    ", FF_TYPE_STANDARD)
FFPARM(HUE,				0,	"Pen Color       ", FF_TYPE_HUE)
FFPARM(SATURATION,      .5, "Saturation      ", FF_TYPE_SATURATION)
FFPARM(LIGHTNESS,       .5, "Lightness       ", FF_TYPE_BRIGHTNESS)
FFPARM(HUE_LOOP_LEN,    .08,"Hue Loop Length ", FF_TYPE_STANDARD)    // 30 degrees
FFPARM(LOOP_HUE,        0,    "Loop Hue        ", FF_TYPE_BOOLEAN)
FFPARM(ROTATE_HUE,        0,    "Rotate Hue      ", FF_TYPE_EVENT)
FFPARM(COLOR_SPEED,        .5,    "Color Speed     ", FF_TYPE_STANDARD)
FFPARM(BK_HUE,            .5,    "Background      ", FF_TYPE_HUE)
FFPARM(BK_SATURATION,    .5,    "Bk Saturation   ", FF_TYPE_SATURATION)
FFPARM(BK_LIGHTNESS,    .5, "Bk Lightness    ", FF_TYPE_BRIGHTNESS)
FFPARM(INVERT_COLOR,    0,    "Invert Color    ", FF_TYPE_BOOLEAN)
FFPARM(ORIGIN_MOTION,    0,    "Origin Motion   ", FF_TYPE_STANDARD)
FFPARM(XPOS,            .5,    "X Position      ", FF_TYPE_XPOS)
FFPARM(YPOS,            .5,    "Y Position      ", FF_TYPE_YPOS)
FFPARM(CENTER_ORIGIN,    0,    "Center Origin   ", FF_TYPE_EVENT)
FFPARM(COPIES,            0,    "Copies          ", FF_TYPE_STANDARD)    // none
FFPARM(SPREAD,            .17,"Spread          ", FF_TYPE_STANDARD)    // 100 pixels
FFPARM(DAMPING,			.5,	"Damping         ", FF_TYPE_STANDARD)
FFPARM(TRAIL,			0,	"Trail           ", FF_TYPE_STANDARD)
FFPARM(RINGS,			1,	"Rings           ", FF_TYPE_STANDARD)	// max
FFPARM(TEMPO,			.4,	"Tempo           ", FF_TYPE_STANDARD)	// 100 BPM
FFPARM(CANVAS_SCALE,	.2,	"Canvas Scale    ", FF_TYPE_STANDARD)	// 140%
FFPARM(ASPECT_RATIO,	.5,	"Aspect Ratio    ", FF_TYPE_STANDARD)
FFPARM(SKEW_RADIUS,		.5,	"Skew Radius     ", FF_TYPE_STANDARD)
FFPARM(SKEW_ANGLE,		.5,	"Skew Angle      ", FF_TYPE_STANDARD)
FFPARM(STAR_FACTOR,		.5,	"Star Factor     ", FF_TYPE_STANDARD)
FFPARM(PINWHEEL,		.5,	"Pinwheel        ", FF_TYPE_STANDARD)
FFPARM(EVEN_CURVE,		.5,	"Even Curve      ", FF_TYPE_STANDARD)
FFPARM(ODD_CURVE,		.5,	"Odd Curve       ", FF_TYPE_STANDARD)
FFPARM(EVEN_SHEAR,        .5,    "Even Shear      ", FF_TYPE_STANDARD)
FFPARM(ODD_SHEAR,        .5,    "Odd Shear       ", FF_TYPE_STANDARD)
FFPARM(MIRROR,			0,	"Mirror          ", FF_TYPE_BOOLEAN)
FFPARM(FILL,			0,	"Fill            ", FF_TYPE_BOOLEAN)
FFPARM(OUTLINE,			0,	"Outline         ", FF_TYPE_BOOLEAN)
FFPARM(XRAY,			0,	"X-Ray           ", FF_TYPE_BOOLEAN)
FFPARM(RANDOM_PHASE,	0,	"Random Phase    ", FF_TYPE_EVENT)
FFPARM(REVERSE,			0,	"Reverse         ", FF_TYPE_BOOLEAN)
FFPARM(CONVEX,			0,	"Convex          ", FF_TYPE_BOOLEAN)
FFPARM(ZOOM_CENTER,		0,	"Zoom Center     ", FF_TYPE_BOOLEAN)
FFPARM(BANK,            0,    "Bank            ", FF_TYPE_STANDARD)
FFPARM(PATCH,            0,    "Patch           ", FF_TYPE_STANDARD)
FFPARM(SAVE_PATCH,		0,	"Save Patch      ", FF_TYPE_EVENT)
FFPARM(PATCH_MODE,        0,    "Patch Mode      ", FF_TYPE_STANDARD)
FFPARM(GLOB_LINE_WIDTH,	.5,	"Glob Line Width ", FF_TYPE_STANDARD)
FFPARM(GLOB_POLY_SIDES,	.5,	"Glob Poly Sides ", FF_TYPE_STANDARD)
FFPARM(GLOB_ROTATION,	.5,	"Glob Rotation   ", FF_TYPE_STANDARD)
FFPARM(GLOB_ASPECT_RATIO,.5,"Glob Aspct Ratio", FF_TYPE_STANDARD)
FFPARM(GLOB_SKEW_RADIUS,.5,	"Glob Skew Radius", FF_TYPE_STANDARD)
FFPARM(GLOB_SKEW_ANGLE,	.5,	"Glob Skew Angle ", FF_TYPE_STANDARD)
FFPARM(GLOB_STAR_FACTOR,.5,	"Glob Star Factor", FF_TYPE_STANDARD)
FFPARM(GLOB_PINWHEEL,	.5,	"Glob Pinwheel   ", FF_TYPE_STANDARD)
FFPARM(GLOB_EVEN_CURVE,	.5,	"Glob Even Curve ", FF_TYPE_STANDARD)
FFPARM(GLOB_ODD_CURVE,	.5,	"Glob Odd Curve  ", FF_TYPE_STANDARD)
FFPARM(GLOB_EVEN_SHEAR,	.5,	"Glob Even Shear ", FF_TYPE_STANDARD)
FFPARM(GLOB_ODD_SHEAR,	.5,	"Glob Odd Shear  ", FF_TYPE_STANDARD)
