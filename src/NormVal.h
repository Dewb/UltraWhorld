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

#ifndef CNORMVAL_INCLUDED
#define CNORMVAL_INCLUDED

class CNormVal {
public:
// Construction
	CNormVal(double Offset, double Scale, double LogBase);
	virtual ~CNormVal();

// Attributes
	double	GetOffset() const;
	double	GetScale() const;
	double	GetLogBase() const;

// Overridables
	virtual double	Norm(double Val) const;
	virtual double	Denorm(double Val) const;

protected:
// Member data
	double	m_Offset;
	double	m_Scale;
	double	m_LogBase;

// Helpers
	static	double	Log(double Base, double x);
	static	double	LogNorm(double x, double Base, double Scale);
	static	double	ExpNorm(double x, double Base, double Scale);
};

inline CNormVal::CNormVal(double Offset, double Scale, double LogBase) :
	m_Offset(Offset),
	m_Scale(Scale),
	m_LogBase(LogBase)
{
}

inline double CNormVal::GetOffset() const
{
	return(m_Offset);
}

inline double CNormVal::GetScale() const
{
	return(m_Scale);
}

inline double CNormVal::GetLogBase() const
{
	return(m_LogBase);
}

class CPosNormVal : public CNormVal {
public:
	CPosNormVal(double Offset, double Scale, double LogBase);
	double	Norm(double Val) const;
	double	Denorm(double Val) const;
};

inline CPosNormVal::CPosNormVal(double Offset, double Scale, double LogBase) :
	CNormVal(Offset, Scale, LogBase)
{
}

#endif
