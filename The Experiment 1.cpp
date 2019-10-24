/*
 * @Description: Deal with the input string and then do certain operations
 * @Version: 1.0
 * @Author: Kevin Liu
 * @Date: 2019-10-24 15:55:55
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-24 16:05:35
 */
#include<string.h>
#include<stdio.h>
#include<iostream>
using namespace std;

typedef struct node
{
	string name = "";
	string type = "";
	int address = 0;
	int length = 0;
	int id = 0;
	int pointneirong = -1;
}node;

static node bl[10][10];
static int bi[10][10];
static char bc[10][10];
static short bs[10][10];
static float bf[10][10];
static int* bpi[10][10];
static char* bpc[10][10];
static short* bps[10][10];
static float* bpf[10][10];
static int address = 0;
static int bl_id = 0;
const static string leixing[8] = { "char","short","int","float","char*","short*","int*","float*" };
const static int leixinglength[8] = { 1,2,4,4,4,4,4,4 };//以32位机器作为参考

int main()
{
	int flag = 0;
	node test[10];
	string in;
	int i = 0;//用来存每句句段
	int t = 0;
	string temp[10];
	
	//定义变量
	while (cin >> in)
	{
		if (in == "exit")
		{
			break;
		}
		temp[i] = in;//把整句话先存下来
		int nLen = temp[i].length();
		if (temp[i][nLen - 1] == ';')
		{//定义变量语句解析  暂时缺少变量查重
			if (temp[i][nLen - 2] == ']')//类型 变量名[num]；
			{
				for (t = 0; t < 8; t++)
				{
					if (temp[0] == leixing[t])
					{
						string sub = temp[i].substr(nLen - 3, nLen - 2);
						string suv = sub.substr(0, 1);

						for (int ccbl = 0; ccbl < bl_id; ccbl++)
						{
							if (temp[i].substr(0, nLen - 4) == test[ccbl].name)
							{
								cout << "Variable " << test[ccbl].name << " name conflict!" << endl;
								flag = 1;
							}
						}
						if (flag == 0)
						{
							if (t > 3)
							{
								test[bl_id].type = "array(" + suv + "," + "*" + temp[0].substr(0, temp[0].length() - 1) + ")";
							}
							else
							{
								test[bl_id].type = "array(" + suv + "," + temp[0] + ")";
							}
							test[bl_id].name = temp[i].substr(0, nLen - 4);
							test[bl_id].length = atoi(suv.c_str()) * leixinglength[t];
							test[bl_id].address = address;
							while (test[bl_id].address % test[bl_id].length)
							{
								test[bl_id].address++;
							}
							address = test[bl_id].address + test[bl_id].length;
						}
					}
				}
			}
			else//类型 变量；
			{
				for (t = 0; t < 8; t++)
				{
					if (temp[0] == leixing[t])
					{
						string sub = temp[i].substr(0, nLen - 1);
						for (int ccbl = 0; ccbl < bl_id; ccbl++)
						{
							if (test[ccbl].name == sub)
							{
								cout << "Variable " << test[ccbl].name << " name conflict!" << endl;
								flag = 1;
							}
						}
						if (flag == 0)
						{
							if (t > 3)
							{
								test[bl_id].type = "*" + temp[0].substr(0, temp[0].length() - 1);
							}
							else
							{
								test[bl_id].type = temp[0];
							}
							test[bl_id].name = sub;
							test[bl_id].length = leixinglength[t];
							test[bl_id].address = address;
							while (test[bl_id].address % test[bl_id].length)
							{
								test[bl_id].address++;
							}
							address = test[bl_id].address + test[bl_id].length;
						}

					}
				}
			}
			if (flag == 0)
			{
				test[i].id = bl_id;
				bl_id++;
				if (bl_id > 9)
				{
					cout << "Space overflow!" << endl;
				}
			}
			flag = 0;
			i = 0;
		}
		else
		{
			i++;
		}
	}

	//赋值  暂时缺少    类型 变量[num] = {...};
	//已实现语句 a[id] = value;  p（*类型） = &q;  p = value;  p = q;(p、q相同类型)
	
	
	i = 0;
	while (cin >> in)
	{
		if (in == "exit")
		{
			break;
		}
		temp[i] = in;
		if (temp[i][temp[i].length() - 1] == ';')
		{
			if (temp[1] == "=")
			{
				if (temp[0][temp[0].length() - 1] == ']')
				{
					string name = temp[0].substr(0, temp[0].length() - 3);
					for (int tt = 0; tt < bl_id; tt++)
					{
						if (name == test[tt].name)//a[num] = value;
						{
							string tyuansuleixing = test[tt].type.substr(8, test[tt].type.length() - 1);
							string yuansuleixing = tyuansuleixing.substr(0, tyuansuleixing.length() - 1);
							if (yuansuleixing == "int")
							{
								string tdd = temp[0].substr(temp[0].length() - 2, temp[0].length() - 1);
								string dd = tdd.substr(0, tdd.length() - 1);
								bi[test[tt].id][atoi(dd.c_str())] = atoi(temp[2].substr(0, temp[2].length() - 1).c_str());
							}
							else if (yuansuleixing == "char")
							{
								string tdd = temp[0].substr(temp[0].length() - 2, temp[0].length() - 1);
								string dd = tdd.substr(0, tdd.length() - 1);
								bc[test[tt].id][atoi(dd.c_str())] = temp[2][0];
							}
							else if (yuansuleixing == "short")
							{
								string tdd = temp[0].substr(temp[0].length() - 2, temp[0].length() - 1);
								string dd = tdd.substr(0, tdd.length() - 1);
								bs[test[tt].id][atoi(dd.c_str())] = atoi(temp[2].substr(0, temp[2].length() - 1).c_str());
							}
							else if (yuansuleixing == "float")
							{
								string tdd = temp[0].substr(temp[0].length() - 2, temp[0].length() - 1);
								string dd = tdd.substr(0, tdd.length() - 1);
								bf[test[tt].id][atoi(dd.c_str())] = atof(temp[2].substr(0, temp[2].length() - 1).c_str());
							}
						}
					}
				}
				else if (temp[2][0] == '&')//p = &q;
				{
					string duibip = temp[0];
					string tduibiq = temp[2].substr(1, temp[2].length() - 1);
					string duibiq = tduibiq.substr(0, tduibiq.length() - 1);
					for (int tt = 0; tt < bl_id; tt++)
					{
						if (duibip == test[tt].name)
						{
							duibip = test[tt].type.substr(1, test[tt].type.length());
							break;
						}
					}
					for (int tt = 0; tt < bl_id; tt++)
					{
						if (duibiq == test[tt].name)
						{
							duibiq = test[tt].type;
							break;
						}
					}
					if (duibip != duibiq)
					{
						cout << "Type Error!" << endl;
					}
					else
					{
						string duibip = temp[0];
						string tduibiq = temp[2].substr(1, temp[2].length() - 1);
						string duibiq = tduibiq.substr(0, tduibiq.length() - 1);
						int pp, qq;
						for (pp = 0; pp < bl_id; pp++)
						{
							if (test[pp].name == duibip)
							{
								break;
							}
						}
						for (qq = 0; qq < bl_id; qq++)
						{
							if (test[qq].name == duibiq)
							{
								break;
							}
						}
						test[pp].pointneirong = test[qq].address;
					}
				}
				else//p = q;或p = value;
				{
					int pp;
					if(!isalpha(temp[2][0]))//p = value;
					{
						for (pp = 0; pp < bl_id; pp++)
						{
							if (test[pp].name == temp[0])
							{
								break;
							}
						}
						if (test[pp].type == "int")
						{
							bi[test[pp].id][0] = atoi(temp[2].substr(0,temp[2].length() - 1).c_str());
						}
						else if (test[pp].type == "short")
						{
							bs[test[pp].id][0] = atoi(temp[2].substr(0, temp[2].length() - 1).c_str());
						}
						else if (test[pp].type == "char")
						{
							bc[test[pp].id][0] = temp[2].substr(1, 2)[0];
						}
						else if (test[pp].type == "float")
						{
							bf[test[pp].id][0] = atof(temp[2].substr(0, temp[2].length() - 1).c_str());
						}
					}
					else//p = q;
					{
						string duibip = temp[0];
						string duibiq = temp[2].substr(0, temp[2].length() - 1);
						int pp, qq;
						for (pp = 0; pp < bl_id; pp++)
						{
							if (test[pp].name == duibip)
							{
								break;
							}
						}
						for (qq = 0; qq < bl_id; qq++)
						{
							if (test[qq].name == duibiq)
							{
								break;
							}
						}
						if (pp >= bl_id || qq >= bl_id)
						{
							cout << "Variable not exists!" << endl;
						}
						if (test[pp].type != test[qq].type)
						{
							cout << "Type Error!" << endl;
						}
						else
						{
							if (test[pp].type == "int")
							{
								bi[test[pp].id][0] = bi[test[qq].id][0];
							}
							else if (test[pp].type == "char")
							{
								bc[test[pp].id][0] = bc[test[qq].id][0];
							}
							else if (test[pp].type == "short")
							{
								bs[test[pp].id][0] = bs[test[qq].id][0];
							}
							else if (test[pp].type == "float")
							{
								bf[test[pp].id][0] = bf[test[qq].id][0];
							}
						}
					}
				}
			}
			i = 0;
		}
		else
		{
			i++;
		}
	}
	
	
	//取值
	while (cin >> in)
	{
		if (in == "exit")
		{
			break;
		}
		temp[i] = in;
		if (temp[i][temp[i].length() - 1] == ';')
		{
			if (temp[0][0] == '&')//&变量名
			{
				string duibi = temp[0].substr(1, temp[0].length() - 2);
				int tt;
				for (tt = 0; tt < bl_id; tt++)
				{
					if (duibi == test[tt].name)
					{
						printf("%p\n", test[tt].address);
						break;
					}
					if (tt == bl_id)
					{
						cout << duibi << " not " << "exist!" << endl;
					}
				}
			}
			else if (temp[0][0] == '*')//*指针变量
			{
				string tduibi = temp[0].substr(1, temp[0].length() - 1);
				string duibi = tduibi.substr(0, tduibi.length() - 1);
				int tt;
				for (tt = 0; tt < bl_id; tt++)
				{
					if (test[tt].name == duibi)
					{
						break;
					}
				}
				int xunzhi = test[tt].pointneirong;
				for (tt = 0; tt < bl_id; tt++)
				{
					if (test[tt].address == xunzhi)
					{
						break;
					}
				}
				if (test[tt].type == "int")
				{
					cout << bi[test[tt].id][0] << endl;
				}
				else if (test[tt].type == "short")
				{
					cout << bs[test[tt].id][0] << endl;
				}
				else if (test[tt].type == "float")
				{
					cout << bf[test[tt].id][0] << endl;
				}
				else if (test[tt].type == "char")
				{
					cout << bc[test[tt].id][0] << endl;
				}
			}
			else if (temp[0][0] != '&' && temp[0][0] != '*')//变量名直接访问
			{
				string duibi = temp[0].substr(0, temp[0].length() - 1);
				int tt;
				for (tt = 0; tt < bl_id; tt++)
				{
					if (test[tt].name == duibi)
					{
						break;
					}
				}
				if (test[tt].type == "int")
				{
					cout << bi[test[tt].id][0] << endl;
				}
				else if (test[tt].type == "char")
				{
					cout << bc[test[tt].id][0] << endl;
				}
				else if (test[tt].type == "short")
				{
					cout << bs[test[tt].id][0] << endl;
				}
				else if (test[tt].type == "float")
				{
					cout << bf[test[tt].id][0] << endl;
				}
				else if (test[tt].type[0] == '*')
				{
					printf("%p\n", test[tt].pointneirong);
				}
				else if (test[tt].type[0] == 'a')
				{
					int id = atoi(test[tt].type.substr(6, 7).c_str());
					cout << "{";
					string tleixing = test[tt].type.substr(8, test[tt].type.length() - 1);
					string leixing = tleixing.substr(0, tleixing.length() - 1);
					if (leixing == "int")
					{
						for (int x = 0; x < id - 1; x++)
						{
							cout << bi[test[tt].id][x] << ", ";
						}
						cout << bi[test[tt].id][id - 1];
					}
					else if (leixing == "short")
					{
						for (int x = 0; x < id - 1; x++)
						{
							cout << bs[test[tt].id][x] << ", ";
						}
						cout << bs[test[tt].id][id - 1];
					}
					else if (leixing == "char")
					{
						for (int x = 0; x < id - 1; x++)
						{
							cout << bc[test[tt].id][x] << ", ";
						}
						cout << bc[test[tt].id][id - 1];
					}
					else if (leixing == "float")
					{
						for (int x = 0; x < id - 1; x++)
						{
							cout << bf[test[tt].id][x] << ", ";
						}
						cout << bi[test[tt].id][id - 1];
					}
					cout << "}" << endl;
					//数组类型全部输出
				}
			}
			i = 0;
		}
		else
		{
			i++;
		}
	}

	//输出符号表
	for (int t1 = 0; t1 < bl_id; t1++)
	{
		cout << test[t1].name << "~" << test[t1].type << " ";
		printf("%p", (void*)test[t1].address);
		cout << " " << test[t1].length << endl;
	}

	system("pause");

	return 0;
}