#include"define.h"

namespace myCode
{
    class String
    {
    private:
        char* data;
    public:
        Uint Length;
        String();
		String(long);
		String(double);
        String(const char* str);
        String(const String &str);
        String(Byte* bt,Uint len);
        ~String(); 
        void operator+=(const char *str);
        void operator+=(const String &str);
        void operator=(const char *str);
        void operator=(const String &str);//只能保留4位，慎用
        void operator+=(double);
        void operator+=(long);
		bool operator==(const String& str);
		void Free();
		char* Str();
		double ToDouble();
		long ToLong();
		bool Equals(const String &str);
		Uint FindFirst(Uint start, Uint end, const char* str);//范围查找
		Uint FindFirst(Uint start, const char* str);//从什么敌方开始查找
		Uint FindFirst(Uint start, Uint end, const String &str);
		Uint FindFirst(Uint start, const String &str);
		String& SubStr(Uint start, Uint end);//从下表start开始到下表end结束复制字符串
		String& SubStrNotCutSelf(const char* start, const char* end);//复制字符串,包含自身
		String& SubStr(const char *start, const char* end);//复制字符串,从start开始,到end结束
		String& SubStrNotCutSelf(const String &start, const String &end);//复制字符串,包含自身
		String& SubStr(const String &start, const String &end);//复制字符串,从start开始,到end结束
		String* Split(const char *str,Uint *size);//用str切割字符串,size是返回字符串数组长度
		String* Split(const String& str, Uint *size);//用str切割字符串,size是返回字符串数组长度
		void Replace(const char* wheres, const char* what);//替换所有的wheres字符串
		void ReplaceOne(const char* wheres, const char *what);//模仿java中sql语句占位符替换
		void Replace(const String& wheres, const String& whats);
		void ReplaceOne(const String &wheres, const String &whats);
		Byte* GetBytes();//返回字节数组
    };
}

