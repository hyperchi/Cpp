#ifndef __READCONFFILE_H__
#define __READCONFFILE_H__

#include <map>
#include <vector>
#include <ctype.h>
#include <iostream>

#include "Predicate.h"

using namespace std;

class ReadConf
{	
public:
	ReadConf( string filePath );

public:
	Predicate			mCFVector;

	bool				OpenConfFile( string filePath );
	void				ShowConfFile();
	void Tranversal( const string &name, Predicate &tarP );

private:
	string				mRCPath;
	FILE				*mCF;

	bool				ReadConfFile		(				);
	int					GetSubMsg			( string &msg	);		//返回子字符串的结尾
	bool				GetOneLineConf		( string msg	);
};

#endif __READCONFFILE_H__

/***************************************************************************
//							配置文件读取类		Writen by Leo
//												2008-8-21
//												CopyLeft												
//			格式：
//			#		注释
//			名称	属性1	属性2	属性3	……	
//
//			名称规则：
//					英文字母（大小写均可）+ 数字 + 下划线 的组合 （首字母不能是下划线） 
//
//			属性规则：
//					英文字母（大小写均可）+ 数字 + 下划线 + 小数点 的组合 （首字母不能是下划线）
//					
***************************************************************************/