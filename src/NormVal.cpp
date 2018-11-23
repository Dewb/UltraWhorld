// Copyleft 2006 Chris Korda
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.
/*
        chris korda
 
		revision history:
		rev		date	comments
        00      19apr06	initial version

		normalization helper
 
*/

#include "stdafx.h"
#include "NormVal.h"
#include <math.h>

CNormVal::~CNormVal()
{
}

inline double CNormVal::Log(double Base, double x)
{
	return(log(x) / log(Base));	// log with arbitrary base
}

inline double CNormVal::LogNorm(double x, double Base, double Scale)
{
	// x is exponential from 0..1, result is linear from 0..Scale
	return(Log(Base, x * (Base - 1) + 1) * Scale);
}

inline double CNormVal::ExpNorm(double x, double Base, double Scale)
{
	// x is linear from 0..Scale, result is exponential from 0..1
	return((pow(Base, x / Scale) - 1) / (Base - 1));
}

double CNormVal::Norm(double Val) const
{
	if (m_LogBase)
		Val = Log(m_LogBase, Val);
	Val /= m_Scale;
	Val += m_Offset;
	return(Val);
}

double CNormVal::Denorm(double Val) const
{
	Val -= m_Offset;
	Val *= m_Scale;
	if (m_LogBase)
		Val = pow(m_LogBase, Val);
	return(Val);
}

double CPosNormVal::Norm(double x) const
{
	return(LogNorm(x, m_LogBase, m_Scale));
}

double CPosNormVal::Denorm(double x) const
{
	return(ExpNorm(x, m_LogBase, m_Scale));
}
