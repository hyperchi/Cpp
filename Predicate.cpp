#include "stdafx.h"
/*/////////////////copy right AmoiesisNQ ////////////////////
*
*        Robocup 3D Soccer Simulation Team AmoiesisNQ
*    the automation department of Xiamen University China
*
*	用于解析的基础类
*
*change log
*2007年8月22日　完成初期框架
*
*////////////////////////////////////////////////////////////
#include "Predicate.h"
#include "Logger.h"

bool Parser::Parse(const string& line, Predicate& pred, int& head)
{
	if (line[head] != '(') 
	{		
		//LOG_PARSE << "Column" << head << " Syntax error. '(' Missing" << END;
		return false;
	}

	for (++ head; head < (int)line.size(); ++ head) 
	{
		if (string(" \t\r\n").find(line[head]) != -1) continue;
		if (line[head] == ')') break;
		if (line[head] == '(') 
		{
			Predicate pp;
			if (Parse(line, pp, head) == false) 
			{
				return false;
			}
			if (pp.name != "") 
			{
				pred.AddChild(pp.name, pp);
			}
		} 
		else 
		{
			int tail = head + 1;
			while (tail < (int)line.size() && string(" \t\r\n)").find(line[tail]) == -1)
				++ tail;

			if (pred.name == "") 
			{
				pred.name = line.substr(head, tail - head);
			} 
			else 
			{
				pred.AddValue(line.substr(head, tail - head));
			}

			head = tail;
			if (head >= (int)line.size() || line[head] == ')') break;
		}
	}

	if (line[head] != ')') 
	{
		//LOG_PARSE << "Column" << head << " Syntax error. ')' Missing" << END;
		return false;
	}

	return true;
}

bool Parser::Parse(const string& line, Predicate& pred)
{
	int head = 0;
	pred.name = "";
	pred.attr.clear();
	pred.child.clear();

	return Parse(line, pred, head);
}

bool Parser::Parse(const string& line, vector<Predicate>& preds)
{
	preds.clear();
	for (int head = 0; head < (int) line.size(); ++ head) 
	{
		preds.push_back(Predicate());
		if (Parse(line, preds[preds.size() - 1], head) == false) 
		{
			return false;
		}
	}
	return true;
}