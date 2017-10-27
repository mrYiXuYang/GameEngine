#include"String.h"
#include<iostream>
#include<vector>
#include"util.h"

using std::vector;
namespace myCode
{
    String::String()
    {
        data=new char[1];
        data[0]='\0';
        Length=0;
    }
	String::String(long arg)
	{
		data = myCode::Itoc(arg);
		Length = strlen(data);
	}
	String::String(double arg)
	{
		data = myCode::Ftoc(arg, 4);
		Length = strlen(data);
	}
    String::String(const char* str)
    {
		if (str != nullptr)
		{
			Length = strlen(str);
			data = new char[Length + 1];
			data[Length] = '\0';
			memcpy(data, str, Length);
		}
		else
		{
			data = new char[1];
			data[0] = '\0';
			Length = 0;
		}

    }
    String::String(const String &str)
    {
        Length=str.Length;
        data=new char[Length+1];
        data[Length]='\0';
        memcpy(data,str.data,Length);
    }
    String::String(Byte* bt,Uint len)
    {
        Length=len;
        data=new char[Length+1];
        data[Length]='\0';
        memcpy(data,bt,len);
    }
    String::~String()
    {
        delete[] data;
    }
    void String::operator=(const char *str)
    {
        delete[] data;
        Length=strlen(str);
        data=new char[Length+1];
        data[Length]='\0';
        memcpy(data,str,Length);
    }
    void String::operator=(const String &str)
    {
        *this+=str.data;
    }
    void String::operator+=(const char* str)
    {
        Uint len=strlen(str);
        char *temp=new char[Length+len+1];
        temp[Length+len]='\0';
        memcpy(temp,data,Length);
        memcpy(temp+Length,str,len);
        Length+=len;
        delete[] data;
        data=temp;
        temp=nullptr;
        delete temp;
    }
    void String::operator+=(const String &str)
    {
        *this+=str.data;
    }
	void String::operator+=(long inteager)
	{
		char *re = myCode::Itoc(inteager);
		*this += re;
	}
	void String::operator+=(double arg)
	{
		char *re = myCode::Ftoc(arg, 4);
	}
	bool String::operator==(const String &str)
	{
		return this->Equals(str);
	}
	void String::Free()
	{
		delete[] data;
	}
	long String::ToLong()
	{

		return myCode::Ctol(data);
	}
	double String::ToDouble()
	{
		return myCode::Ctod(data);
	}
	bool String::Equals(const String &str)
	{
		if (Length != str.Length)
		{
			return false;
		}
		else if (!Length)
		{
			return true;
		}
		else
		{
			for (Uint i = 0; i < Length; i++)
			{
				if (data[i] != str.data[i])
				{
					return false;
				}
			}
		}
		return true;
	}
	char* String::Str()
	{
		return data;
	}
	Uint String::FindFirst(Uint start, Uint end, const char* str)
	{
		Uint result = -1;
		Uint len = strlen(str);
		if (start<0 || end >= Length || len>Length)
		{
			return result;
		}
		bool flag = true;
		for (Uint i = start; i <= end; i++)
		{
			flag = true;
			for (Uint j = 0; j < len; j++)
			{
				if (data[i + j] != str[j])
				{
					flag = false;
				}
			}
			if (flag)
			{
				result = i;
				break;
			}
		}
		return result;
	}
	Uint String::FindFirst(Uint start, Uint end, const String &str)
	{
		return this->FindFirst(start, end, str.data);
	}
	Uint String::FindFirst(Uint start, const char* str)
	{
		Uint result = -1;
		Uint len = strlen(str);
		if (start<0 ||len>Length)
		{
			return result;
		}
		bool flag = true;
		for (Uint i = start; i<Length; i++)
		{
			flag = true;
			for (Uint j = 0; j < len; j++)
			{
				if (data[i + j] != str[j])
				{
					flag = false;
				}
			}
			if (flag)
			{
				result = i;
				break;
			}
		}
		return result;
	}
	Uint String::FindFirst(Uint start, const String &str)
	{
		return this->FindFirst(start, str.data);
	}
	String& String::SubStr(Uint start, Uint end)
	{
		if (start < 0 || end >= Length)
		{
			String *re = new String();
			String &result = *re;
			re = nullptr;
			delete re;
			return result;
		}
		Uint len = end - start + 1;
		char *re = new char[len+1];
		re[len] = '\0';
		memcpy(re, data + start, len);
		String *str = new String(re);
		String &result = *str;
		str = nullptr;
		delete str;
		return result;
	}
	String& String::SubStrNotCutSelf(const char* start, const char* end)
	{
		String *NU = new String();
		String& result = *NU;
		Uint lens = strlen(start);
		Uint lene = strlen(end);
		if (lens>Length||lene>Length)
		{
			NU = nullptr;
			delete NU;
			return result;
		}
		Uint st = FindFirst(0,start);
		Uint et = FindFirst(st + lens, end);
		if (st != -1 && et != -1)
		{
			Uint len = (et + lene) - st;
			char* re = new char[len+1];
			memcpy(re, data + st, len);
			re[len] = '\0';
			String *str = new String(re);
			result = *str;
			str = nullptr;
			delete str;
			return result;
		}
		NU = nullptr;
		delete NU;
		return result;
	}
	String& String::SubStr(const char* start, const char* end)
	{
		String *NU = new String();
		String& result = *NU;
		Uint lens = strlen(start);
		Uint lene = strlen(end);
		if (lens>Length || lene>Length)
		{
			NU = nullptr;
			delete NU;
			return result;
		}
		Uint st = FindFirst(0, start);
		Uint et = FindFirst(st + lens, end);
		if (st != -1 && et != -1)
		{
			Uint len = et - st-lens;
			char* re = new char[len + 1];
			memcpy(re, data + st+lens, len);
			re[len] = '\0';
			String *str = new String(re);
			result = *str;
			str = nullptr;
			delete str;
			return result;
		}
		NU = nullptr;
		delete NU;
		return result;
	}
	String& String::SubStrNotCutSelf(const String &start, const String &end)
	{
		return this->SubStrNotCutSelf(start.data, end.data);
	}
	String& String::SubStr(const String &start, const String &end)
	{
		return this->SubStr(start.data, end.data);
	}
	String* String::Split(const char *str, Uint *size)
	{
		vector<char*> temp;
		Uint len = strlen(str);
		Uint now=0;
		Uint before=0;
		while ((now=FindFirst(before, str)) != -1)
		{
			
			char *re = new char[now - before+1];
			re[now - before] = '\0';
			memcpy(re, data + before, now - before);
			temp.push_back(re);
			before = now+len;
		}
		if (before)
		{
			Uint rlen = Length - before;
			char *re = new char[ rlen+ 1];
			re[rlen] = '\0';
			memcpy(re, data + before, rlen);
			temp.push_back(re);
		}
		else
		{
			char *re = new char[Length+1];
			strcpy(re, data);
			temp.push_back(re);
		}
		*size = temp.size();
		String *result = new String[*size];
		for (Uint i = 0; i < *size; i++)
		{
			result[i] = temp[i];
			delete[] temp[i];
		}
		temp.clear();
		return result;
	}
	String* String::Split(const String &str, Uint *size)
	{
		return this->Split(str.data, size);
	}
	void String::Replace(const char* wheres, const char* whats)
	{
		Uint lenw = strlen(wheres);
		Uint lent = strlen(whats);
		Uint now = 0;
		Uint next = 0;
		vector<Uint> pos;
		while ((now = FindFirst(next, wheres)) != -1)
		{
			pos.push_back(now);
			next = now + lenw;
		}
		Uint size = pos.size();
		if (size)
		{
			Uint reAdd = 0;
			Uint daAdd = 0;
			next = 0;
			Uint newLen=Length+(lent - lenw)*size;
			char *re = new char[newLen + 1];
			re[newLen] = '\0';
			for (Uint i = 0; i < size; i++)
			{
				memcpy(re+reAdd, data+daAdd,pos[i]-next);//pos[i]³öÏÖµã
				reAdd += pos[i] - next;
				daAdd += pos[i] - next;
				memcpy(re+reAdd, whats, lent);
				reAdd += lent;
				daAdd += lenw;
				next = pos[i]+lenw;
			}
			if (pos[size - 1]+lenw < Length)
			{
				memcpy(re+reAdd, data + pos[size - 1] + lenw, Length - pos[size - 1] - lenw);
			}
			Length = newLen;
			delete[] data;
			data = re;
			re = nullptr;
			delete re;
		}
		pos.clear();
	}
	void String::ReplaceOne(const char* wheres, const char*whats)
	{
		Uint pos = FindFirst(0, wheres);
		if (pos != -1)
		{
			Uint lenw = strlen(wheres);
			Uint lent = strlen(whats);
			Uint neLen = Length + (lent - lenw);
			char* re = new char[neLen + 1];
			re[neLen] = '\0';
			memcpy(re, data, pos);
			memcpy(re + pos, whats, lent);
			memcpy(re + pos + lent, data + pos + lenw, Length - pos - lenw);
			Length = neLen;
			delete[] data;
			data = re;
			re = nullptr;
			delete re;
		}
	}
	void String::Replace(const String& wheres, const String& whats)
	{
		this->Replace(wheres.data, whats.data);
	}
	void String::ReplaceOne(const String& wheres, const String& whats)
	{
		this->ReplaceOne(wheres.data, whats.data);
	}
	Byte* String::GetBytes()
	{
		Byte* result = new Byte[Length];
		memcpy(result, data, Length);
		return result;
	}
}
