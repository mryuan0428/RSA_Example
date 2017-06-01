#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "bigInt.h"
#include "gcd.h"
#include "mrTest.h"
#include "power.h"
#include "random.h"

using namespace std;

string num2str(int i)
{
        stringstream ss;
        ss<<i;
        return ss.str();
}

int str2num(string s)
 {
        int num;
        stringstream ss(s);
        ss>>num;
        return num;
}


bigInt string2bigInt(string s)
{
	bigInt b("0");
	int l = s.length();
	for(int i = 0;i < l;i ++)
	{
		int n = s[i];
		string num(3,'0');
		num[2] += n%10;
		num[1] += (n/10)%10;
		num[0] += (n/100)%10;
		b = b * bigInt("128") + bigInt(num);
	}
	return b;
}

string bigInt2string(bigInt b)
{
	bigInt mod("128");
	string res = "";
	while(b > bigInt("0"))
	{

		string s = (b % mod).getnum();
		b = b / mod;
		char c = 0;
		int l = s.length();
		for(int i = 0;i < l;i ++)
			c = c * 10 + s[i]-'0';
		//cout << c << endl;
		string tmp(1,c);
		res = c + res;
	}
	return res;
}

int main()
{
    cout<<"Please input the bits of p & q(14 bits ~ 5 bits decimal number,47 bits ~ 14 bits decimal number):"<<endl;
    cin>>BIT;


	cout << "generating p and q..." << endl;//Çóp,q
	bigInt p,q;
	p = createprime();
	q = createprime();
	while(p == q) q = createprime();

	bigInt n = p * q;//Çón,fai(n)
	bigInt fai = (p-bigInt("1"))*(q-bigInt("1"));

	cout << "generating d and e..." << "\n"<<"-"<<endl;//ÇóË½Ô¿dºÍ¹«Ô¿e
	bigInt d,e;
	d = bigInt("3");
	while(!(gcd(d,fai) == bigInt("1")))
		d = d + bigInt("2");
	e = inv(d,fai);

	cout<<"Pbulic Key: "<<" "<<"n = "<< n << ","<<"e = " << e<<"\n"<<"-"<<endl;
	cout<<"Private Key: "<<" "<<"p = " << p << ","<<"q = " << q<< ","<<"d = "<< d <<"\n"<<"-"<<endl;
	cout<<"Infomation: "<<"m = Mathematical Fundation of Infomation Security + 201405001 + 515021910471"<<"\n"<<"-"<<endl;

	string str[11]={"m","=","Mathematical","Fundation","of","Infomation","Security","+","201405001","+","515021910471"};
    cout<<"Numerical Information: ";
	bigInt num[11][15];
	int l[11];
	for(int i=0;i<11;i++)
	{
	    l[i]=str[i].length();
	    for(int j=0;j<l[i];j++)
	    {
	        int k1=int(str[i][j]);
	        string k2=num2str(k1);
	        num[i][j]=bigInt(k2);
	        num[i][j].print();
	    }
        cout<<" ";

	}
	cout<<"\n"<<"-"<<endl;


	cout<<"ENCRYPT_____Ciphertext: ";
	bigInt cipher[11][15];
	for(int i=0;i<11;i++)
	{
	    for(int j=0;j<l[i];j++)
	    {
	        cipher[i][j]=power(num[i][j],e,n);
	        cipher[i][j].print();
	    }
	    cout<<" ";
	}
	cout<<"\n"<<"-"<<endl;

	cout<<"DECRYPT_____Plaintext: ";
	bigInt plain[11][15];
	for(int i=0;i<11;i++)
	{
	    for(int j=0;j<l[i];j++)
	    {
	        plain[i][j]=power(cipher[i][j],d,n);
	        plain[i][j].print();
	    }
	    cout<<" ";
	}
	cout<<"\n"<<"-"<<endl;


	cout<<"Restore Information: ";
	int num0[11][15];
	for(int i=0;i<11;i++)
	{
	    for(int j=0;j<l[i];j++)
	    {
           num0[i][j]=str2num(plain[i][j].getnum());
           cout<<char(num0[i][j]);
	    }
	    cout<<" ";
	}
	cout<<"\n"<<"-"<<endl;

	return 0;

	system("pause");
}
