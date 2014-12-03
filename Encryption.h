#ifndef __ENCRYPTION_H__
#define __ENCRYPTION_H__

#include <vector>
#include <string>
#include "stdio.h"

#define Mo 11

//class Verify{
//
//public:
//	bool AddVerify(vector<int> vec)
//	{
//		int len = (int)vec.size();
//		float sum = 0;
//		for (int i = 0; i < len; ++i)
//		{
//			sum += vec[i] * (i+1);
//		}
//		int r = sum % Mo;
//		vec.push_back(r);
//		return true;
//	}
//	bool DecodeVerify(vector<int> v)
//	{
//		int len = (int)v.size();
//		int verify = v[len - 1];
//		float testsum = 0;
//		for (int i = 0; i < len - 1; ++i)
//		{
//			testsum += v[i] * (i + 1);
//		}
//		int r = testsum % Mo;
//		if (r == verify)
//		{
//			return true;
//		}
//		else
//			return false;
//	}
//};
#define round(x) ((x)>0?int((x)+0.5f):int((x)-0.5f))

template<class T> inline const T Min(const T& x, const T& y){
	return x < y ? x : y;
}
template<class T> inline const T Max(const T& x, const T& y){
	return x > y ? x : y;
}
class Encryption{

public:
	int ciphertext(char m){
		if (m >= '0' && m <= '9'){
			return m - '0' + 1;
		}
		switch(m){
		case '.':
			return 11;
		case '(':
			return 12;
		case ')':
			return 13;
		case ' ':
			return 14;
		case '-':
			return 15;
		}
		return 0;
	}

	char deciphertext(int e){
		if (e <= 10) return char(e -1 + '0');
		switch(e){
		case 11:
			return '.';
		case 12:
			return '(';
		case 13:
			return ')';
		case 14:
			return ' ';
		case 15:
			return '-';
		}
		return 0;
	}



	void encipher(char * buffer, int len){
		int tmp, j = 0;
		int i;
		for(i =0; i < len; i ++){
			switch(i % 3){
			case 0:
				tmp = ciphertext(buffer[i]) * 4;
				break;
			case 1:
				buffer[j ++] = map_into_printablechar(tmp + (ciphertext(buffer[i]) / 4));
				tmp = (ciphertext(buffer[i]) % 4) * 16;
				break;
			case 2:
				buffer[j ++] = map_into_printablechar(tmp + ciphertext(buffer[i]));
			}	
		}
		if(len % 3 != 0){
			buffer[j ++] = map_into_printablechar(tmp);
		}
		buffer[j] = 0;
	}

	void decipher(char * buffer, int len){
		int* tmp = new int[len], j = 0;
		int i;
		for(i = 0; i < len; i ++)
			tmp[i] = map_from_printablechar(buffer[i]);

		for(i =0; i < len; i ++){
			switch(i % 2){
			case 0:
				buffer[j ++] = deciphertext(tmp[i] / 4);
				break;
			case 1:
				buffer[j ++] = deciphertext((tmp[i-1] % 4) * 4 + tmp[i] / 16);
				buffer[j ++] = deciphertext(tmp[i] % 16);
				break;
			}
		}
		buffer[j] = 0;
		delete tmp;
	}
	char map_into_printablechar(int i){
		if (i < 10) return i + '0';
		i -= 10;
		if (i < 26) return i + 'a';
		i -= 26;
		if (i < 26) return i + 'A';
		i -= 26;
		switch(i){
	case 0: return '(';
	case 1: return ')';
	case 2: return '.';
	case 3: return '+';
	case 4: return '-';
	case 5: return '*';
	case 6: return '/';
	case 7: return '?';
	case 8: return '<';
	case 9: return '>';
	default:return '_';
		}
	}

	int map_from_printablechar(char m){
		if (m >= '0' && m <= '9')
			return m - '0';
		if (m >= 'a' && m <= 'z')
			return m - 'a' + 10;
		if (m >= 'A' && m <= 'Z')
			return m - 'A' + 36;
		if (m == '(')
			return 62;
		if (m == ')')
			return 63;
		if (m == '.')
			return 64;
		if (m == '+')
			return 65;
		if (m == '-')
			return 66;
		if (m == '*')
			return 67;
		if (m == '/')
			return 68;
		if (m == '?')
			return 69;
		if (m == '<')
			return 70;
		if (m == '>')
			return 71;
		return 72;
	}

	//map a symmetrical section into [0, map_length]
	inline unsigned char map(float realvalue, float valid_length, float map_length){	
		//cout << round(map_length * Max(0.0f, Min((realvalue / valid_length + 0.5f), 1.0f))) << endl;
		return (unsigned char)round(map_length * Max(0.0f, Min((realvalue / valid_length + 0.5f), 1.0f)));
	}

	//antimap [0, map_length] into a symmetrical section
	inline float antimap(unsigned char mapvalue, float valid_length, float map_length){
		return ((float)mapvalue / map_length - 0.5f) * valid_length;
	}
	unsigned char f2c(float f, float validlength, float maplength){
		unsigned char data = map(f, validlength, maplength);
		return data;
	}
	float c2f(unsigned char c, float valid_length,float maplength)/*int acu, int range_exp = 8, float ref_value,*/
	{
//#ifndef _LONG_AUDIO	
//		unsigned char data = map(ref_value, valid_length, maplength);	
//		unsigned char tmp, high_bits;
//		unsigned char mask = 255;
//
//		//retrieve high bits (which is cut off when msg is generated)
//		mask = mask << range_exp;
//		high_bits = (data & mask) >> range_exp;
//
//		/*simulate transferd bits and compare it with received bits 
//		(the comparing result is used to rectify the high bits)
//		if their distance > 1/2 max_distance then high bits should be rectified
//		*/
//		tmp = data << (8-range_exp);
//		tmp = tmp >> (8-range_exp);
//		tmp = tmp >> acu;
//
//		if(abs(tmp - c) > (1 << (bit_len(acu, range_exp)-1))){
//			if(tmp > c) high_bits ++;
//			else high_bits --;
//		}
//
//		data = high_bits << range_exp;	
//		data = data >> acu;
//		data |= c;
//		data = data << acu;
//
//		return antimap(data, valid_length, maplength);
//#else
		return antimap(c, valid_length, maplength);
//#endif
	}
	/*int bit_len(int acu, int range_exp){
#ifdef _LONG_AUDIO	
		return 8;
#else
		return range_exp - acu;
#endif	*/
	/*}*/
	
	int float_int(float num)//简单的强制转换
	{
		int result;
		if (num < 0)
		{
			result = (int)(num - 0.5);
		}
		else
		{
			result = (int)(num + 0.5);
		}
		return result;
	}
	struct  intNum
	{
		int head;
		int tail;
	};
	intNum float_int_Robust(float num)//...脑残的方法
	{
		intNum result;
		char temp[20];
		sprintf(temp,"%.3f",num);
		string tempString = temp;
		int pos = tempString.find(".");
		int err = (int)tempString.length() - pos;
		if (err == 0)
		{
			result.head = (int)num;
			result.tail = 0;
		}
		else
		{
			result.head = regard(tempString.substr(0,pos));
			result.tail = regard(tempString.substr(pos+1,pos+4));			
		}
		return result;
	}
	int regard(string str)
	{
		int n; 
		n=atoi(str.c_str()); 
		return n;
	}

	int Combine(float input_float)
	{
		intNum temp = float_int_Robust(input_float);
		int left = temp.head;
		int right = temp.tail;
		left = left << 3;
		right /= 125;
		left |= right;
		return left;
	}
	int count(int num)
	{
		int countValid = 0;
		int flag = sizeof(int) * 8;
		if (num & 1)
		{
			countValid = 1;
		}
		int i = 0;
		while (flag)
		{
			--flag;
			++i;	
			if ((num >> i) & 1)
			{
				countValid ++;
			}
		}	
		return countValid;
	}
};
#endif