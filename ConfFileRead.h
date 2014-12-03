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
	int					GetSubMsg			( string &msg	);		//�������ַ����Ľ�β
	bool				GetOneLineConf		( string msg	);
};

#endif __READCONFFILE_H__

/***************************************************************************
//							�����ļ���ȡ��		Writen by Leo
//												2008-8-21
//												CopyLeft												
//			��ʽ��
//			#		ע��
//			����	����1	����2	����3	����	
//
//			���ƹ���
//					Ӣ����ĸ����Сд���ɣ�+ ���� + �»��� ����� ������ĸ�������»��ߣ� 
//
//			���Թ���
//					Ӣ����ĸ����Сд���ɣ�+ ���� + �»��� + С���� ����� ������ĸ�������»��ߣ�
//					
***************************************************************************/