// string_arthmetic.cpp : Defines the entry point for the console application.
//#include "stdafx.h"
#include<iostream>
#include<string>
using namespace std;
class large_int
{
string str = "+0";
//string to store integer
string addition(string &,const string &);
string subtraction(string &,const string &);
string multiplication(const string &, const string &);
void modify(string &);
void add_0(string &no, int &&i);
void swap(string &str1, string &str2);
int convert(char &ch);
bool less_than_compare(const string &, const string &);
bool less_than_equal_compare(const string &, const string &);
public:
// all constructors
large_int() = default;
large_int(string &a) :str(a) { modify(str); }
large_int(string &&a) :str(a) { modify(str); };
large_int(large_int &obj) :str( obj.str ) { modify(str); }
large_int(large_int &&obj) :str(move(obj.str)) { modify(str); }
~large_int() {}
//member functionslarge_int operator +(const large_int &);
large_int operator -(const large_int &);
large_int operator *(const large_int &);
large_int operator /(const large_int &);
large_int operator %(const large_int &);
large_int operator =(const large_int &);
large_int operator =(const string &);
friend large_int operator ++(large_int &);
friend large_int operator ++(large_int &,int);
friend large_int operator --(large_int &);
friend large_int operator --(large_int &,int);
large_int operator +=(const large_int &);
large_int operator -=(const large_int &);
large_int operator *=(const large_int &);
large_int operator /=(const large_int &);
friend istream& operator >>(istream &,large_int &);
friend ostream& operator <<(ostream &,const large_int &);
bool operator <(const large_int &);
bool operator >(const large_int &);
bool operator <=(const large_int &);
bool operator >=(const large_int &);
bool operator ==(const large_int &);
large_int reverse();
large_int abs();large_int power(large_int &);
string string();
};
string large_int::addition(string &str1, const string &str_t)
{
string str2 = str_t;
string result = "";
bool carry = 0;
int i, j, t_sum, neg_count = 0;
if (str1.length() < str2.length())swap(str1, str2);
else if (str1.length() == str2.length())
{
for (i = 1; i <= str1.length(); i++)
{
if (str1[i] < str2[i])
{
swap(str1, str2);
break;
}
}
}
if (str1[0] == '-')++neg_count;
if (str2[0] == '-')++neg_count;
if (neg_count % 2 != 0) { str1[0] == '-' ? str2[0] = '-' : str2[0] = '+'; return
subtraction(str1, str2); }for (i = str1.size() - 1, j = str2.size() - 1; j >0; i--, j--)
{
t_sum = convert(str1[i]) + convert(str2[j]) + carry;
result.push_back(t_sum % 10 + '0');
carry = t_sum > 9 ? t_sum / 10 : 0;
}
for (; i > 0; i--)
{
if (carry)
{
t_sum = convert(str1[i]) + carry;
result.push_back(t_sum % 10 + '0');
carry = t_sum / 10;
}
else
{
result.push_back(str1[i]);
}
}
carry ? result.push_back(carry + '0') : void(0);
reverse(result.begin(), result.end());
if (str1[0] == '-')result.insert(0, "-");
return result;
}
string large_int::multiplication(const string &st1, const string &st2)
{
int i, j, carry{ 0 }, temp, neg_count = 0;
string str_temp{ "" }, result{ "0" }, str1{ st1 }, str2{ st2 };if (str1.length() < str2.length()) { swap(str1, str2); }
for (i = str2.length() - 1; i > 0; i--)
{
for (j = str1.length() - 1; j > 0; j--)
{
temp = carry + convert(str1[j])*convert(str2[i]);
temp > 9 ? carry = temp / 10 : carry = 0;
str_temp.push_back((temp % 10) + '0');
}
if (carry) { str_temp.push_back(carry + '0'); }
reverse(str_temp.begin(), str_temp.end());
add_0(str_temp, (str2.length() - 1 - i));
result.insert(0, "+");
str_temp.insert(0, "+");
result = addition(result, str_temp);
str_temp = "";
carry = 0;
}
int cnt = 0;
i = 0;
while (result[i++] == '0')cnt++;
if (cnt){
reverse(result.begin(), result.end());
for (; cnt > 1; cnt--)result.pop_back();
reverse(result.begin(), result.end());
}
if (neg_count % 2 != 0) result.insert(0, "-");
return result;
}
string large_int::subtraction(string &str1, const string &str_T)
{
string str2 = str_T;
string result;
bool borrow = 0;
char sign_m = '+', sign_v = '+';
int i, j, t_diff, neg_count = 0;
if (str1[0] == '-')++neg_count;
if (str2[0] == '-')++neg_count;
if (neg_count % 2 != 0) { str2[0] = str2[0] == '+' ? '-' : '+'; return addition(str1,
str2); }
sign_v = str1[0];
if (str1.length() < str2.length()) { swap(str1, str2); sign_m = '-'; }
else if (str1.length() == str2.length())
{
for (i = 1; i <= str1.length(); i++){
if (str1[i] < str2[i])
{
swap(str1, str2);
sign_m = '-';
break;
}
}
}
for (i = str1.length() - 1, j = str2.length() - 1; j > 0; i--, j--)
{
(str1[i] - borrow - str2[j]) >= 0 ? borrow == 0 ? result.push_back(str1[i] - str2
[j] + '0') : (borrow = 0, result.push_back(str1[i] - 1 - str2[j] + '0')) : (borrow == 1 ?
result.push_back(str1[i] - 1 + 10 - str2[j] + '0') : (borrow = 1, result.push_back(str1[i] + 10 -
str2[j] + '0')));
}
for (; i > 0; i--)
{
(str1[i] - borrow) < '0' ? (result.push_back(str1[i] - borrow + 10), borrow = 1) :
(result.push_back(str1[i] - borrow), borrow = 0);
}
i = result.length() - 1;
int cnt = 0;
while (i >= 1 && result[i] == '0') { cnt++; --i; }if (cnt)
{
for (; cnt >0; cnt--)result.pop_back();
}
if (sign_m == '-'&&sign_v == '+')result.push_back('-');
else if (sign_m == '-'&&sign_v == '-') {}
else if (str1[0] == '-')result.push_back('-');
reverse(result.begin(), result.end());
return result;
}
large_int large_int::operator +(const large_int &obj)
{
string str2 = obj.str;
return large_int(addition(str,str2));
}
large_int large_int::operator -(const large_int &obj)
{
string str2 = obj.str;
return large_int(subtraction(str, str2));
}
large_int large_int::operator *(const large_int &obj)
{
string str2 = obj.str;
return large_int(multiplication(str, str2));}
istream& operator >>(istream &in, large_int &obj)
{
in >> obj.str;
return in;
}
ostream& operator <<(ostream &out,const large_int &obj)
{
out<< obj.str;
return out;
}
large_int large_int::operator =(const large_int &obj)
{
str = obj.str;
return *this;
}
large_int large_int::operator =(const string &a)
{
str = a;
return *this;
}
large_int large_int::power(large_int &obj)
{
large_int res("1");
while(obj.string()!="+0"){
res = res * str;
--obj;
}
return large_int(res);
}
large_int large_int::reverse()
{
reverse(str.begin(), str.end());
return *this;
}
large_int large_int::abs()
{
str[0] = '+';
return *this;
}
large_int operator++(large_int &obj)
{
obj = obj + large_int("1");
return obj;
}
large_int operator++(large_int &obj,int x)
{
obj=obj + large_int("1");
return obj;
}
large_int operator--(large_int &obj)
{obj = obj - large_int("1");
return obj;
}
large_int operator--(large_int &obj,int x)
{
obj = obj - large_int("1");
return obj;
}
large_int large_int::operator +=(const large_int &obj)
{
this->str = addition(this->str,obj.str);
return *this;
}
large_int large_int::operator -=(const large_int &obj)
{
this->str = subtraction(this->str, obj.str);
return *this;
}
/*
large_int large_int::operator /=(const large_int &obj)
{
this->str = division(this->str,obj.str);
return *this;
}
*/
large_int large_int::operator *=(const large_int &obj)
{this->str = multiplication(this->str, obj.str);
return *this;
}
bool large_int::less_than_compare(const string &str1, const string &str2)
{
int i;
auto str1_length = str1.length(), str2_length = str2.length();
auto equality_check = str1_length-1;
if (str1[0] != str2[0])return (str1[0] < str2[0]) ? 0 : 1;
if (str1_length != str2_length)
{
if ((str1_length > str2_length) && str1[0] == '+') { return 0; }
if ((str1_length <str2_length) && str1[0] == '-') { return 0; }
}
else
{
for (i = 1; i < str1_length; i++)if (str1[i] > str2[i])return 0;
}
return equality_check>0?1:0;
}
bool large_int::less_than_equal_compare(const string &str1, const string &str2)
{
long int i;
auto str1_length = str1.length(), str2_length = str2.length();if (str1[0] != str2[0])
{
return (str1[0] < str2[0]) ? 0 : 1;
}
if (str1_length != str2_length)
{
if ((str1_length > str2_length) && str1[0] == '+') { return 0; }
if ((str1_length <str2_length) && str1[0] == '-') { return 0; }
}
for (i = 1; i < str1_length; i++)
{
if (str1[i] == str2[i])continue;
if (str1[i] > str2[i])return 0;
}
return 1;
}
bool large_int::operator <(const large_int &obj)
{
string str1 = str;
string str2 = obj.str;
return less_than_compare(str1, str2);
}
bool large_int::operator >(const large_int &obj)
{
string str1 = str;
string str2 = obj.str;
return less_than_compare(str2, str1);}
bool large_int::operator <=(const large_int &obj)
{
string str1 = str;
string str2 = obj.str;
return less_than_equal_compare(str1, str2);
}
bool large_int::operator >=(const large_int &obj)
{
string str1 = str;
string str2 = obj.str;
return less_than_equal_compare(str2, str1);
}
bool large_int::operator ==(const large_int &obj)
{
string str1 = str;
string str2 = obj.str;
auto str1_length = str1.length(), str2_length = str2.length();
if ((str1_length != str2_length) || (str1[0] != str2[0]))return 0;
for (int i = 1; i < str1_length; ++i)if (str1[i] != str2[i])return 0;
return 1;
}
int large_int::convert(char &ch)
{
return ch - '0';
}void large_int::swap(string &str1, string &str2)
{
string str3 = str1;
str1 = str2;
str2 = str3;
}
void large_int::add_0(string &no, int &&i)
{
while (i--)
{
no.push_back('0');
}
}
void large_int::modify(string &str)
{
auto ck = [](char ch)
{
return ch >= 48 && ch <= 57 ? 1 : 0;
};
if (ck(str[0]))str.insert(0, "+");
if (ck(str[0]))str.insert(0, "+");
}
string large_int::string()
{
string a{ "" };
if (str[0] == '+')
{for (auto it = str.begin() + 1; it != str.end(); it++)a.push_back(*it); }
return a;
}