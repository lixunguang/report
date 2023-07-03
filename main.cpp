// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "inja/inja.hpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


// Just for convenience
using namespace inja;

 
using namespace std;
 
//将string转换成wstring  
wstring string2wstring(string str)
{
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
									//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

//将wstring转换成string  
string wstring2string(wstring wstr)
{
	string result;
	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

std::string GbkToUtf8(std::string src_str1)
{
	const char *src_str = src_str1.data();
	int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	std::string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
}

std::string Utf8ToGbk(std::string src_str1) //const char *src_str
{
	const char* src_str = src_str1.data();
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

int main()
{

	//json data;
	//data["neighbour"] = "Peter";
	//data["guests"] = { "Jeff", "Tom", "Patrick" };
	//data["time"]["start"] = 16;
	//data["time"]["end"] = 22;


	//read input
	std::ifstream contentIn;
	contentIn.open("./data/input_param.txt");

	std::stringstream contentStream;
	contentStream << contentIn.rdbuf(); //read the file
	std::string str = contentStream.str(); //str holds the content of the file
	json content = json::parse(str);
	
	//read template	
	std::ifstream templateIn;
	templateIn.open("./data/html_template.txt" );

	std::stringstream strStream;
	strStream << templateIn.rdbuf(); //read the file
	std::string templateStr = strStream.str(); //str holds the content of the file
 
 

	//render
	std::string html = render(templateStr, content);
	//std::string htmlStr = Utf8ToGbk(html);
	
	//output
	ofstream ofs("./data/sim_ic_report.html", ios_base::trunc);//以追加的形式打开文件
	if (!ofs.is_open())
	{
		cout << "file open fail" << endl;

		return 0;
	}
	ofs << html;
 

    return 0;
}

 
