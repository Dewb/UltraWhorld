*** UltraWhorld freeframe plugin source distribution ***

REQUIREMENTS:

UltraWhorld is designed to be an MFC VC++ 6.0 project.  It may or may not
compile correctly in other versions of MFC, or in .NET.  UltraWhorld has
mainly been tested under Windows 2000 SP4, but it should work fine
under XP SP2.

UltraWhorld is an enhanced version of the original Whorld Freeframe
plugin (WhorldFF).  The main enhancement is that UltraWhorld exposes
nearly all of the Whorld application's parameters and switches.  This
allows you to run Whorld from within your favorite VJ application, 
without sacrificing the Whorld application's extensive real-time 
controls; in short, the best of both Whorlds.  :) 

UltraWhorld has an unusually large number of Freeframe parameters. 
Unfortunately some VJ softwares limit the number of parameters a
Freeframe plugin can expose.  UltraWhorld is most useful with VJ
softwares that don't limit Freeframe parameters, e.g. FFRend (see
http://ffrend.sourceforge.net).

INSTALLATION:

Most softwares reserve a special folder for freeframe plugins.  If your
software does this, simply copy UltraWhorld.dll to the special folder.
Be sure to do this BEFORE launching your software, since it probably 
only checks for plugins during startup.  Otherwise, consult your 
software's documentation.

IMPORTANT: In addition to installing the plugin, you may also wan to
install some Whorld patches.  Use the following procedure:

1. Find your "My Documents" folder.  If you're unfamiliar with Windows,
there are various ways to do this.  One reliable way is to go to the
Start menu, select "Documents", and then select "My Documents".

2. In your "My Documents" folder, create a subfolder called WhorldFF.
The subfolder name must be spelled correctly.  The subfolder's path
should look something like this (assuming you're the Administrator):

C:\Documents and Settings\Administrator\My Documents\WhorldFF

3. Copy the patches from this distribution into the WhorldFF
subfolder.

UNINSTALLING:

Just delete UltraWhorld.dll and the Whorld patches, and that's all
there is to it.

PLAYLIST SUPPORT 

UltraWhorld features the ability to load a Whorld playlist (.whl),
unlike the original WhorldFF plugin which only loads patches.  There
are two methods for loading a playlist in UltraWhorld: 

1. Create a special initialization file in "My Documents\WhorldFF" 
which directs the plugin to your playlist.  The file is plain text, 
so you can create it using Notepad or any other text editor.  The 
file MUST be called "UltraWhorld.ini", and it should contain a single 
line, consisting of the word "Playlist", followed by an equals sign, 
followed by the absolute path to the desired playlist, like this: 

Playlist=C:\Whatever\MyPlaylist.whl 

Replace C:\Whatever\YourPlaylist.whl with an absolute path to the
desired playlist.  Do NOT enclose the path in quotes.  It's OK if it
contains embedded spaces.  

***OR*** 

2. Copy your playlist to the "My Documents\WhorldFF" folder and then
rename it to "UltraWhorld.whl".  With this method, the playlist MUST be 
called "UltraWhorld.whl", otherwise the plugin won't find it.

NOTE that first method (.ini file) is preferable, because of a problem
with the way the Whorld application stores paths in playlists.  If you
choose to use the second method, you should check UltraWhorld.whl for
broken links, by opening it in the Whorld application.  If Whorld finds
broken links, it will give you an opportunity to repair them.  Be sure
the save the playlist afterwards.  

If UltraWhorld doesn't find a Whorld playlist via one of the above
methods, it defaults to WhorldFF's behavior, i.e.  it looks for patches
in the folder "My Documents\WhorldFF" and loads them in alphabetical
order.  Note that in this case there will only be one bank.  

PARAMETERS - NOTES 

Some of UltraWhorld's parameters are switches, rather than continuous
controls.  There are two types of switches, boolean and event
(momentary).  According to the Freeframe specification, 

boolean - 0.0 defined as false and anything else defined as true.
event - Similar to boolean but for a momentary push button style 
trigger.  1.0 is set momentarily to trigger the event.  

An example of an event is Rotate Hue (90 degrees).  The way it works is
that the event is triggered when the parameter transitions to the value
1.0 (from any other value).  To trigger the event twice in a row, set
the parameter to 1.0, set it to any other value, and then set it to 1.0
again.  

The last parameter (Save Patch) is a momentary switch which saves the
current settings as a new Whorld patch.  The resulting patch is saved to
the folder "My Documents\WhorldFF\Saved".  The filename is synthesized
from the current date and time.  This feature is handy if you develop a
cool setting in UltraWhorld and want to use it in the Whorld 
application too.  

Finally, note that the X and Y position parameters don't do anything
unless Origin Motion is set to "Drag".  The Origin Motion parameter
works as follows: 

0.0 to 1/3	Origin is parked: X/Y position parameters do nothing.
1/3 to 2/3	Origin can be dragged, using X/Y position parameters.
2/3 to 1.0	Origin makes random jumps, at frequency set by Tempo.

PARAMETERS - REFERENCE 

Master Settings

1. Bank - Selects a bank in a Whorld playlist.
2. Patch - Selects a patch from the WhorldFF folder or a Whorld
playlist bank.
3. Speed - Master speed; 0 = min, .5 = nominal, 1 = max.
4. Zoom - Magnification; 0 = min, .5 = nominal, 1 = max.
5. Hue - Shifts the hues in the entire image; 0 to 360 degrees.
6. Damping - Applied to origin motion and zoom; 0 = none, 1 = max.
7. Trail - Slinky effect applied to origin motion; 0 = none, 1 = max.
8. Rings - Maximum number of rings; 0 = none, 1 = unlimited.
9. Tempo - If origin motion is "Random", the jump rate: 0 to 250 BPM.
10. Hue Loop Length - If "Loop Hue" is enabled, loop size in degrees.
11. Canvas Scale - Scale of drawing area; 0 = 100%, 1 = 300%.
12. Copies - Number of copies; 0 = 1, 1 = 20.
13. Spread - Distance of copies from the origin; 0 to 600 pixels.
14. X Position - If origin motion is "Drag", the origin X-coordinate.
15. Y Position - If origin motion is "Drag", the origin Y-coordinate.

Geometry Parameters

The geometry parameters (Ring Growth, Ring Spacing, etc.) are Master
Offsets which are ADDED to the corresponding value from the current
patch.  Values less than .5 have a negative effect, values greater than
.5 have a positive effect, and at .5, the parameter is unaffected.  If
the parameter is being modulated by an oscillator, the master offset 
shifts the modulated value.

16. Ring Growth - How fast rings expand; 0 = max reverse, 1 = max 
forward.
17. Ring Spacing - Space between each ring; 0 = min, 1 = max.
18. Line Width - Width of each ring; 0 = min, 1 = max.
19. Poly Sides - Number of sides each ring has; 0 = min, 1 = max.
20. Rotate Speed - Amount each ring rotates per frame; 0 = max 
clockwise, 1 = max counter-clockwise.
21. Aspect Ratio - Stretches the rings horizontally or vertically; 
0 = max vertical, 1 = max horizontal.
22. Skew Radius - Amount each ring's origin shifts per frame; 
0 = max negative, 1 = max positive.
23. Skew Angle - Direction of the per-frame origin shift; 0 = max 
clockwise, 1 = max counter-clockwise.
24. Star Factor - Causes sides of a ring to bulge outward, or collapse 
inward; 0 = max inward, 1 = max outward.
25. Pinwheel - Rotates the points of a star; 0 = max clockwise, 1 = 
max counter-clockwise.
26. Color Speed - How fast the ring hue cycles around the color wheel; 
0 = max clockwise, 1 = max counter-clockwise.
27. Lightness - Lightness of the ring color; 0 = min, 1 = max.
28. Saturation - Saturation of the ring color; 0 = min, 1 = max.
29. Bk Hue - Background color's hue; 0 = min, 1 = max.
30. Bk Lightness - Background color's lightness; 0 = min, 1 = max.
31. Bk Saturation - Background color's saturation; 0 = min, 1 = max.
32. Even Curve - Curvature at even vertices; 0 = max negative, 1 = max 
positive.
33. Odd Curve - Curvature at odd vertices; 0 = max negative, 1 = max 
positive.

Miscellaneous Switches

34. Patch Mode (boolean) - If true, patch selection affects geometry 
parameters only.
35. Center Origin (event) - Centers the origin.
36. Origin Motion - Selects type of origin motion; 0 = none (park), 
.5 = drag, 1 = random.
37. Loop Hue (boolean) - If true, limits hue cycling to a subset of 
the color wheel.
38. Rotate Hue (event) - Rotates hues of both new and existing rings 
by 90 degrees.
39. Invert Color (boolean) - If true, all colors are inverted.
40. Mirror (boolean) - If true, output is quad-mirrored.
41. Fill (boolean) - If true, rings are filled.
42. Outline (boolean) - If true, filled rings are outlined in 
background color.
43. X-Ray (boolean) - If true, rings are drawn in XOR mode.
44. Random Phase (event) - Randomizes modulator phases.
45. Reverse (boolean) - If true, rings collapse inward instead of 
expanding outward.
46. Convex (boolean) - If true, rings form a convex shape instead 
of concave one.
47. Clear (event) - Clears the screen by deleting all rings.
48. Zoom Center (boolean) - If true, zooming is relative to center of 
screen rather than drawing origin.
49. Save Patch (event) - Saves the current settings as a Whorld patch 
in "My Documents\WhorldFF\Saved".

GETTING HELP: 

If you're able to run the plugin, but the patch slider doesn't do
anything, it's because the plugin didn't find any patches.  The most
likely reason is that you put them in the wrong folder.  Remember,
there's a unique "My Documents" folder for each user.  The plugin looks
in the CURRENT USER's "My Documents\WhorldFF", and nowhere else.  

Some patches may cause performance problems, e.g.  the frame rate may
drop, or your software may become unresponsive.  If this occurs, here
are some things to try: 

1. Use a more powerful gamer-style PC.
2. Use a lower-resolution video mode.
3. Lower the Rings parameter.  
4. Figure out which patches cause trouble, and don't use them.  
5. Edit the patches to reduce their performance requirements.  

It may help to read the "Performance" chapter in Whorld's documentation.
Briefly, any of the following can cause problems: wide lines, fill mode,
outline mode, x-ray mode, B zier curves, excessive poly sides, extreme
star factor, or excessive ring count.  The easiest solution is usually
to reduce the Ring count, either directly via the Rings master control,
or indirectly by increasing the Ring Spacing parameter.  

For more information, see http://whorld.org 

KNOWN BUGS: 

When you change patches, the other parameters (Speed, Zoom, etc.) don't
snap to the new patch's values.  Sorry!  

LICENSE: 

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.  This program is distributed in the hope that
it will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
the GNU General Public License for more details.  You should have
received a copy of the GNU General Public License along with this
program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111 USA.  

Kopyleft 2007 Chris Korda, All Rites Reversed.  

END 
