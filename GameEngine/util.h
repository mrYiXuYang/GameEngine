#pragma once
#include"define.h"
namespace myCode
{
	Ushort GetSizeI(long arg);
	template<typename T>
	T Pow(T src, short arg);
	char* Itoc(long arg);
	char* Ftoc(double arg, Ushort accurcy);
	long Ctol(const char *str);
	double Ctod(const char *str);
}