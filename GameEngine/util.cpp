#include"util.h"
#include<iostream>
namespace myCode
{
	Ushort GetSizeI(long arg)
	{
		Ushort size = 1;
		while (arg /= 10)
		{
			size++;
		}
		return size;
	}
	template<typename T>
	T Pow(T src, short arg)
	{
		if (arg == 0)
		{
			return 1;
		}
		T result = src;
		if (arg > 0)
		{
			for (int i = 1; i < arg; i++)
			{
				result *= src;
			}
		}
		else
		{
			for (int i = arg; i <= 0; i++)
			{
				result /= src;
			}
		}
		return result;
	}
	char* Itoc(long arg)
	{
		char *result = nullptr;
		Ushort size = GetSizeI(arg);
		if (arg < 0)
		{
			arg = -arg;
			result = new char[size + 2];
			result[0] = '-';
			result[size + 1] = '\0';
			for (Ushort i = 1; i <= size; i++)
			{
				result[i] = arg / Pow(10,size - i) + 48;
				arg %= Pow(10, size - i);
			}
		}
		else
		{
			result = new char[size + 1];
			result[size] = '\0';
			for (Ushort i = 0; i < size; i++)
			{
				result[i] = arg / Pow(10, size - i - 1) + 48;
				arg %= Pow(10, size - i - 1);
			}
		}
		return result;
	}
	char* Ftoc(double arg, Ushort accurcy)
	{
		int inteager = arg;
		double si = arg - inteager;
		int other = si*Pow(10,(short)accurcy);
		if (other < 0)
		{
			other = -other;
		}
		char *r1 = Itoc(inteager);
		char *r2 = Itoc(other);
		Uint len1 = strlen(r1);
		Uint len2 = strlen(r2);
		char *reslut = new char[len1 + len2 + 2];
		memcpy(reslut, r1, len1);
		memcpy(reslut + len1 + 1, r2, len2);
		reslut[len1] = '.';
		reslut[len1 + len2 + 1] = '\0';
		return reslut;
	}
	long Ctol(const char *str)
	{
		Ushort len = strlen(str);
		bool flag = false;
		long result = 0;
		if (str[0] == '-')
		{
			flag = true;
		}
		if (flag)
		{
			for (Ushort i = 1; i < len; i++)
			{
				result += (str[i] - 48)*myCode::Pow(10, len - i-1);
			}
			result = -result;
		}
		else
		{
			for (Ushort i = 0; i < len; i++)
			{
				result += (str[i] - 48)*myCode::Pow(10, len - i - 1);
			}
		}
		return result;
	}
	double Ctod(const char *str)
	{
		Ushort len = strlen(str);
		bool flag = false;
		if (str[0] == '-')
		{
			flag = true;
		}
		double result = 0;
		Ushort i = 0;
		while (str[i]!='.')
		{
			i++;
		}
		char *inteager = new char[i+1];
		inteager[i] = '\0';
		memcpy(inteager, str, i);
		long templ = myCode::Ctol(inteager);
		delete[] inteager;
		i++;
		Ushort k = 1;
		double temp2 = 0;
		while (i<len)
		{
			temp2 += (str[i] - 48)*myCode::Pow(10.0,-k);
			i++;
			k++;

		}
		if (flag)
		{
			result = templ - temp2;
		}
		else
		{
			result = templ + temp2;
		}
		return result;
	}
}