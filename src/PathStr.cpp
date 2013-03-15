// Copyleft 2005 Chris Korda
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.
/*
        chris korda
 
		revision history:
		rev		date	comments
        00      27jul05	initial version
		01		02sep05	add QuoteSpaces

		wrap useful shell path functions
 
*/

#include "stdafx.h"
#include "PathStr.h"

BOOL CPathStr::Append(LPCSTR More)
{
	char	*p = GetBuffer(MAX_PATH);
	BOOL	retc = PathAppend(p, More);
	ReleaseBuffer();
	return(retc);
}

void CPathStr::RemoveExtension()
{
	char	*p = GetBuffer(MAX_PATH);
	PathRemoveExtension(p);
	ReleaseBuffer();
}

BOOL CPathStr::RemoveFileSpec()
{
	char	*p = GetBuffer(MAX_PATH);
	BOOL	retc = PathRemoveFileSpec(p);
	ReleaseBuffer();
	return(retc);
}

BOOL CPathStr::RenameExtension(LPCSTR Ext)
{
	char	*p = GetBuffer(MAX_PATH);
	BOOL	retc = PathRenameExtension(p, Ext);
	ReleaseBuffer();
	return(retc);
}

void CPathStr::QuoteSpaces()
{
	char	*p = GetBuffer(MAX_PATH);
	PathQuoteSpaces(p);
	ReleaseBuffer();
}
