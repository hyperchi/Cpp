/*/////////////////copy right AmoiesisNQ ////////////////////
*
*        Robocup 3D Soccer Simulation Team AmoiesisNQ
*    the automation department of Xiamen University China
*
*change log
*2007年8月22日　完成初期框架
*
*////////////////////////////////////////////////////////////
#ifndef __PREDICATE_H__
#define __PREDICATE_H__

#include "stdinc.h"
#include <iostream>     // needed for cout

#include "Geometry.h"
#include "Object.h"
#include "Hear.h"
using namespace std;

class Predicate 
{

public:
	string name;								//名称
	vector <string> attr;						//属性

	multimap <string, Predicate> child;

	Predicate() : name("") {}

	virtual ~Predicate() {}

	void ShowValue()
	{
		multimap	<string,Predicate>	:: iterator cp;
		vector		<string>			:: iterator mp;

		for( cp = child.begin(); cp != child.end(); cp ++ )
		{
			cout<< (*cp).first << " ";

			for( mp = (*cp).second.attr.begin(); mp != (*cp).second.attr.end(); mp ++ )
			{
				cout<< (*mp) << " ";
			}

			cout<< endl;
		}

		cout<< endl;
	}

	void AddChild(const string& name, const Predicate &pred) 
	{

		child.insert(make_pair(name, pred));

	}

	void AddValue(const string& value) 
	{

		attr.push_back(value);

	}

	void SetValue(const vector<string>& value) 
	{

		attr = value;

	}

	void SetValue(const string& value) 
	{

		attr = vector<string>(1, value);

	}

	// get the child predicate
	bool GetChild(const string& name, Predicate& ch) 
	{
		multimap<string,Predicate>::iterator it = child.find(name);

		if (it == child.end()) 
		{

			return false;

		}

		ch = it->second;

		return true;
	}

	// find a child predicate
	bool Find(const string& name) 
	{
		return child.find(name) != child.end();
	}

	// get an attribute with a name
	bool GetValue(const string& name, vector<string>& value) 
	{
		
		if( child.size() < 1 )
		{
			value = attr;
		}
		else
		{		multimap<string,Predicate>::iterator it = child.find(name);

			if (it == child.end()) 
			{
				return false;
			}

			value = it->second.attr;

		}

		return true;
	}

	bool GetValue(const string& name, string& value) 
	{

		vector <string> vv;

		if (GetValue(name, vv) == false || vv.size() < 1) 
		{
			return false;
		}

		value = vv[0];

		return true;

	}

	bool GetValue(const string& name, float& value) 
	{

		string vv;

		if (GetValue(name, vv) == false) 
		{
			return false;
		}

		value = (float)atof(vv.data());

		return true;
	}

	bool GetValue(const string& name, int& value) 
	{

		string vv;

		if (GetValue(name, vv) == false) 
		{
			return false;
		}

		value = atoi(vv.data());

		return true;

	}

	bool GetValue(const string& name, unsigned int& value) 
	{

		string vv;

		if (GetValue(name, vv) == false) 
		{
			return false;

		}

		value = atoi(vv.data());

		return true;
	}

	bool GetValue(const string& name, bool& value)
	{
		string vv;
		
		if (GetValue(name, vv) == false) 
		{
			return false;
		}

		if( vv == "true" )
		{
			value = true;
		}
		else
		{
			value = false;
		}
		
		return true;
	}

	bool GetValue(const string& name, Vector3f& value) 
	{

		vector<string> vv;

		if (GetValue(name, vv) == false) 
		{

			return false;

		}

		if (vv.size() < 3) return false;

		for (int i = 0; i < 3; ++ i) 
		{

			value[i] =(float) atof(vv[i].data());

		}

		return true;

	}
	bool GetValue(const string& name, Hear& value) 
	{	//hear
		vector<string> vv;

		if (GetValue(name, vv) == false) 
		{
			return false;
		}

		if (vv.size() < 3) return false;

		vector<string>::const_iterator point;
		point = vv.begin();
		value.mHearTime = (float)atof((*point).data());
		++point;
		if (*point == "self")
		{
			value.mMsg = true;
			return false;
		}

		value.mAngle = (float)atof((*point).data());

		++point;
		if ((*point).size() > 12)
		{
			return false;
		}
		value.mHeardMessage = *point;
		//value.mHeardMessage = (*point).data();(float)atof((*point).data());
		value.mMsg = false;

		return true;
	}
	bool GetValue(const string& name, Polar3f& value) 
	{

		vector<string> vv;

		if (GetValue(name, vv) == false) 
		{

			return false;

		}

		if (vv.size() < 3) return false;

		for (int i = 0; i < 3; ++ i) 
		{

			value[i] = (float)atof(vv[i].data());

		}

		return true;

	} 
	bool GetValue(const string& name, float *value, unsigned int arrayLen )
	{
		vector<string> vv;

		if (GetValue(name, vv) == false) 
		{
			return false;
		}

		if (vv.size() < arrayLen) 
		{
			return false;
		}

		for (unsigned int i = 0; i < arrayLen; ++ i) 
		{
			value[i] = (float)atof(vv[i].data());
		}

		return true;

	}

};

// a parser for predicate
class Parser 
{

private:

	static bool Parse(const string& line, Predicate& pred, int& head);

public:

	static bool Parse(const string& line, Predicate& pred);

	static bool Parse(const string& line, vector<Predicate>& preds);

};

#endif //__PREDICATE_H__