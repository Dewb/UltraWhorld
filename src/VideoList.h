// Copyleft 2006 Chris Korda
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.
/*
        chris korda
 
		revision history:
		rev		date	comments
        00      06may06	initial version
        01      08may06	gut for freeframe
        02      25jul07	add main info structs

        array of video clips
 
*/

#ifndef CVIDEOLIST_INCLUDED
#define CVIDEOLIST_INCLUDED

class CVideoList {
public:
	enum {
		MAX_VIDEOS = 10	// maximum number of open videos
	};
	typedef struct tagINFO_BASE {
		int		CurPos;		// current video's position in list, or -1 if none
		int		ROPIdx;		// index of raster operation
		bool	AutoRewind;	// if true, rewind clips before playing them
		bool	Cycle;		// if true, cycle clips
		int		CycleLen;	// cycle length
	} INFO_BASE;
	typedef struct tagINFO : INFO_BASE {
		char	MRUPath[MAX_VIDEOS][MAX_PATH];	// most recently used videos
	} INFO;

	CVideoList() {};
	void	SetROPIdx(int Idx) {};
	int		GetROPIdx() const {};
};

class CCrossDlg {
public:
	typedef struct tagINFO {
		double	Pos;		// crossfader position; 0 = A, 1 = B, .5= 50/50 mix
		double	Seconds;	// duration of automated crossfade, in seconds 
		bool	Loop;		// if true, automated crossfade loops repeatedly
		int		Waveform;	// oscillator waveform type for automated crossfade
	} INFO;
};

class CPlaylistMidiDlg {
public:
	typedef struct tagINFO {
		int		Scheme;
		int		Chan;
		int		First;
		int		Last;
	} INFO;
};

class CPlaylistDlg {
public:
	typedef CPlaylistMidiDlg::INFO MIDI_INFO;
	typedef struct tagINFO {
		MIDI_INFO	Midi;	// MIDI mapping dialog state
		double	PatchSecs;	// in auto-play, duration of each patch, in seconds
		double	XFadeSecs;	// crossfade duration, in seconds; may exceed PatchSecs
		bool	Playing;	// true if auto-playing
		bool	Shuffle;	// true if auto-play should randomize playlist order
		int		CurBank;	// index of current bank
		int		CurPatch;	// index of currently playing patch; -1 if none
		int		CurPatchBank;	// index of current patch's bank
	} INFO;
};

#endif
