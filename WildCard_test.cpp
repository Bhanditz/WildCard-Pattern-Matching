#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include <iomanip>
#include<algorithm>
using namespace std;
static double Arr[5][15] = { 0 };  //用于存放文件中数据的数组

int chartorol(char ch)
{
	switch (ch)
	{
	case 'A': return 1;
	case 'C': return 2;
	case 'G': return 3;
	case 'T': return 4;
	default: break;
	}
	return 0;
}

/*
A∪B∪C = A+B+C - A∩B - B∩C - C∩A +A∩B∩C= A+B+C – (A∩B + B∩C + C∩A -A∩B∩C)；
其中每次计算即计算其中的一项，如开始计算(A+B+C)的概率，然后是(A∩B + B∩C + C∩A)的概率，
最后是(A∩B∩C)的概率，而其概率的正负号有sign=-sign；得到，即正负交叉进行。
*/
int inter(string &temp1, string &temp2, string &temp, double &prob)
{
	//cout << "inter:" << temp1 << " " << temp2 << endl;//8.31注释
	int flag = 1, k;
	int m = temp1.size();

	prob = 1.0;
	temp.resize(m + 1);//此处应该是用问题的？？？？优化的时候选择合适的大小
	//temp.resize(m+1);
	temp[0] = '\0';//%%%%%%%%%%%%需要注意，temp的下标是从1开始存储的。

	//分别使2个string的下标从1开始 
	char *ch1 = new char[m + 1];
	for (int i = 0; i < m; i++)
		ch1[i + 1] = temp1[i];
	ch1[0] = '\0';

	//int temp2len = temp2.size();//9.22添加
	char *ch2 = new char[m + 1];//9.22修改
	for (int i = 0; i < m; i++)//9.22修改
		ch2[i + 1] = temp2[i];//9.22号有问题
	ch2[0] = '\0';
	/*
	cout << "ch1;";
	for (int i = 0; i <= m; i++)
	cout <<ch1[i];
	cout << endl;
	cout << "ch2;";
	for (int i = 0; i <= m; i++)
	cout << ch2[i];
	*/
	for (k = 1; k < m + 1; k++)
	{
		if (ch1[k] != '0' && ch2[k] != '0' && ch1[k] != ch2[k])
		{
			flag = 0;
			return flag;
		}
		if (ch1[k] == ch2[k])
			temp[k] = ch1[k];
		if (ch1[k] == '0' && ch2[k] != '0')
			temp[k] = ch2[k];
		if (ch1[k] != '0' && ch2[k] == '0')
			temp[k] = ch1[k];
		if (temp[k] != '0')
		{
			int i = chartorol(temp[k]);
			prob *= Arr[i][k]; //s在下面的dp函数里是从1开始索引的
		}
	}
	//cout << "inter: prob" << prob << endl;//8.31注释
	return flag;
}



//把文件中的数据存入Arr的函数
void filetoarray()
{
	ifstream input("C:\\Users\\lzz\\Documents\\Visual Studio 2013\\Projects\\CO\\WildCard生成文件\\序列\\7.txt");
	if (!input)
		cerr << "error!";

	string line, word;
	int i(1), j(1);
	while (getline(input, line))  //读取每行的字符
	{
		istringstream isstream(line);//将记录绑定到刚读入的行
		while (isstream >> word)  //读取该行用空格隔开的单个数据
		{
			Arr[i][j] = stod(word);  //string转double
			++j;
		}
		++i;
		j = 1;
	}


}



double common(vector<string> pointer1, vector<string> pointer2, int L, int H)
{
	//cout << "进入common" << endl;
	int m = pointer2.size();
	int n = pointer1.size();
	//cout << "pointer1的长度：" << n << endl;
	//cout << "pointer2的长度：" << m << endl;

	//	/*vector <string>::iterator striter;
	//	for (striter = pointer1.begin(); striter != pointer1.end();striter++)
	//	{
	//		cout<<"传进来的pointer1:"<<*striter<<endl;
	//	}
	//
	//	for (striter = pointer2.begin(); striter != pointer2.end(); striter++)
	//	{
	//		cout << "传进来的pointer2:" << *striter << endl;
	//	}
	//*/

	vector <vector <int>> varray;
	vector <int> line;
	vector <string> stringset;
	vector <double> problist;
	vector <int> dest1;
	int flag, sign = 1, k, i, j, y, z;
	double prob, probsum = 0;
	string s = "0";
	//string temp1[m], temp2[n], temp;
	string *temp1 = new string[m];
	string *temp2 = new string[n];
	string temp;
	//int num1[m], num2[n];
	int *num1 = new int[m];
	int *num2 = new int[n];

	//cout << "m=" << m << " n=" << n << endl;
	if ((m == 0) || (n == 0))
		return 0;

	for (k = 0; k <= m - 1; k++)
	{
		temp1[k] = pointer2[k];
		num1[k] = k + 1;
		for (i = 1; i <= L; i++)
			temp1[k] += s;
	}

	for (k = 0; k <= n - 1; k++)
	{
		temp2[k] = pointer1[k];
		num2[k] = m + k + 1;
	}

	k = -1;
	z = k;
	

	varray.resize(2*(m+n)*m*n);//大小需要从新设定，选择比较合适的，节省空间以及防止越界
	cout << "*************计算A+B+C和概率:***************" << endl;
	for (i = 0; i <= m - 1; i++)
	{
		varray.push_back(line);  // 要对每一个vector初始化，否则不能存入元素
		for (j = 0; j <= n - 1; j++)
		{
			if ((flag = inter(temp1[i], temp2[j], temp, prob)) == 1)
			{
				cout << "temp" << temp << endl;//8.31号注释
				k++;
				varray[k].push_back(num1[i]);//%%%%%%%%%%%%%%%%%%%

				varray[k].push_back(num2[j]);//要存在同一位置

				int templength = temp.size();

				char *ch1 = new char[templength];
				int ii;
				for (ii = 0; ii < templength - 1; ii++)
					ch1[ii] = temp[ii + 1];
				ch1[ii] = '\0';//9.2号注释


				//stringset.push_back(temp);////9.2号添加
				stringset.push_back(ch1);//9.2号注释
				problist.push_back(prob);
				probsum += sign*prob;
				cout << "probsum=" << probsum << endl;//8.31号注释
			}
			cout << endl;//8.31号注释
		}
	}

	

	cout << "**********************************************" << endl;


	y = k;
	vector<int>::iterator intiter;

	//9.2号添加
	/*
	问题出在最后一次循环，其实AA0G，都是2345，只要计算一次就可以了，结果计算了6次，所以多了0.1

	所以现在要有一个语句，如果dest1里的值和前面的相同，就不用计算了
	这句话的if (dest1.size() == varray[i].size() + 1)后面加句话来过滤就行了，就是看看前面有没有相同的，有就不用再计算了

	*/

	varray.resize(2 * (m + n)*m*n+k*k*k);//大小需要从新设定，选择比较合适的，节省空间以及防止越界
	while (k - z != 0)
	{
		sign = (-1)*sign;

		//for (i = z + 1; i <= y - z - 2; i++)
		//	//for (j = z + 2; j <= y - z - 1; j++)
		//for (j = i + 1; j <= y - z - 1; j++)
		for (i = z + 1; i <= y - 1; i++)
			for (j = i + 1; j <= y; j++)
			{
				vector <int> dest1;
				//set_union(varray[i].begin(), varray[i].end(), varray[j].begin(), varray[j].end(), dest1.begin());

				//cout << "调用了set_union()" << endl;
				set_union(varray[i].begin(), varray[i].end(), varray[j].begin(), varray[j].end(), back_inserter(dest1));



				int flag2 = 1;
				if (dest1.size() == varray[i].size() + 1)
				{	//这句话的if(dest1.size() == varray[i].size() + 1)后面加句话来过滤就行了，就是看看前面有没有相同的，有就不用再计算了//9.2号添加
					for (int j = 0; j <= k; j++)//*****************************9.2号添加开始
					{
						if (dest1 == varray[j])
						{
							flag2 = 0;
							break;
						}

						else
							flag2 = 1;

					}//************************************9.2号添加结束


					if ((flag = inter(stringset[i], stringset[j], temp, prob)) == 1 && (flag2 == 1))//9.2号添加flag2==1
					{

						for (intiter = dest1.begin(); intiter != dest1.end(); intiter++)
							cout << *intiter << " ";
						cout << endl;  //8.31号注释

						cout << "set_union temp:" << temp << "  prob:" << prob << "k=" << k << endl;//8.31号注释

						k++;
						varray[k] = dest1;



						int templength = temp.size();
						char *ch1 = new char[templength];
						int ii;
						for (ii = 0; ii < templength - 1; ii++)
							ch1[ii] = temp[ii + 1];
						ch1[ii] = '\0';    //9.2号注释

						//stringset.push_back(temp);//9.2号添加
						stringset.push_back(ch1);//9.2号注释
						problist.push_back(prob);
						probsum += sign*prob;
						cout << "probsum:" << probsum << endl;
					}
				}
			}

		z = y;
		y = k;
		cout << "**************************************************" << endl;
	}
	cout << "varray前的容量：" << varray.capacity() << endl;
	varray.shrink_to_fit();
	cout << "varray后的容量：" << varray.capacity() << endl;

	vector <vector <int>> ().swap(varray);
	
	cout << "varray后的容量：" << varray.capacity() << endl;

	return probsum;
}


//max函数
int max(const int &a, const int& b)
{
	return a > b ? a : b;
}

//min函数
int min(const int &a, const int& b)
{
	return a < b ? a : b;
}


void DP(int L, int H, string q, int N) //pp是概率表 其中L是间隔约束下线，H是间隔约束上线，q为模式，N为序列长度
{

	cout << q << endl;
	int g = H - L;
	int gg = g;
	int i, j, ymax, ymin, x, k, kk;
	int M = q.size();
	string str1 = "0";
	vector<string> svec;
	vector<string>::iterator striter;
	struct PP
	{
		double data;
		vector<string> next;
	};
	PP P[100][100];

	//保证q下标从1开始
	char *ch1 = new char[M + 1];

	for (int t = 0; t < M; t++)
		ch1[t + 1] = q[t];
	ch1[0] = '\0';

	//for (int t = 0; t < M+1; t++)
	//cout << "ch1["<<t<<"]="<<ch1[t] << endl;

	for (i = 1; i <= (M - 1)*(H - L + 1) + 1; i++)	// (M - 1)*(H - L + 1) + 1????
		for (j = 0; j <= N; j++)   //M是模式的长度，N是序列的长度  对P进行初始化
			if (i + (i - 1)*L>j)   //%%%%%%%%%%%%%%%%%新改动，进行全部出初始化
			{

				P[i][j].data = 0;
				P[i][j].next = svec;
			} //P[i][j]是结构体

	for (j = 0; j <= N; j++)//将P的最后一行数值赋值为1
	{
		P[0][j].data = 1;
		P[0][j].next = svec;
	}

	//*************************************************************************************
	//第一种情况当i=1时
	i = 1;
	cout << "************************进入第一种i=1情况******************************" << endl;

	for (j = 1; j <= N - (M - 1)*(L + 1); j++)
	{

		int a = chartorol(ch1[i]);

		ymax = min(j - 1, g);
		ymin = max(g - (N - (M - 1)*(L + 1) - j), 0);

		//10.10添加
		if (ymin > ymax)
		{
			/*int temp;
			temp = ymin;
			ymin = ymax;
			ymax = temp*/;
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@ymin>ymax@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		ymin = ymax;
		}


		char *ch = new char[j + 1];
		for (x = ymin; x <= ymax; x++)  //x为尾间隔约束

			if (x == 0)  //尾间隔为0的情况
			{
				P[i][j].data = Arr[a][j] * P[i - 1][j - 1].data;
				if (Arr[a][j] != 0)//当P(s[j]=q[1])!=0时，q从1开始索引的
				{
					for (k = 0; k <= j - 2; k++)
						ch[k] = '0';
					ch[j - 1] = ch1[i];  //q从1索引，即ch1从1开始，而序列ch则是从0开始
					ch[j] = '\0';//转换为字符串的形式



					P[i][j].next.push_back(ch);
					cout << endl;
					cout << "&&&&&&&&&&&&&&&&&&&&&&&&当x=0时&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
					cout << "if x=0 i=1时j=" << j << " x=" << x << "中共有字符为：" << endl;
					//printf("新加入的ch:%s\n",ch);
					cout << "此时的p[" << i << "]" << "[" << j << "].next的长度为:" << P[i][j].next.size() << endl;
					int count = 0;
					for (striter = P[i][j].next.begin(); striter != P[i][j].next.end(); striter++)
					{
						count++;
						cout << count << "." << *striter << " ";
					}

					cout << endl;
				}

				else P[i][j].next = svec;//当P(s[j]=q[1])=0时

			}



		//尾间隔不为0的情况
			else
			{
				P[i + x][j].data = Arr[a][j] * P[i - 1][j - 1].data + (1 - Arr[a][j])*P[i + x - 1][j - 1].data;//dp中公式（3）这部分应该有问题，出现随机数的地方

				if (Arr[a][j] != 0)  {  //当P(s[j]=q[1]) !=0时,当P(s[j]=q[1]) =1时只进行改条件语句，q从1开始索引的
					for (k = 0; k <= j - 2; k++)
						ch[k] = '0';
					ch[j - 1] = ch1[i];  //q从1索引
					ch[j] = '\0';
					P[i + x][j].next.push_back(ch);

					cout << endl;
					cout << "&&&&&&&&&&&&&&&&&&&&&&&当X！=0，Arr[a][j] != 0时&&&&&&&&&&&&&&&&&&&&&&&" << endl;
					cout << "i=1时j=" << j << "  x=" << x << "中共有字符为：" << endl;
					//printf("新加入的ch:%s", ch);
					cout << "此时的p[" << i + x << "]" << "[" << j << "].next的长度为:" << P[i + x][j].next.size() << endl;
					int count = 0;
					for (striter = P[i + x][j].next.begin(); striter != P[i + x][j].next.end(); striter++)
					{
						count++;
						cout << count << "." << *striter << " ";
					}
					cout << endl;

				}

				else  P[i][j].next = svec;  //next指向的字符串从0开始索引

				if ((1 - Arr[a][j]) != 0)   //当P(s[j]=q[1])!=1时，q从1开始索引的
				{
					if (P[i + x - 1][j - 1].data != 0)
					{
						int m = P[i + x - 1][j - 1].next.size();
						//cout << "m=p[" << i+x-1 << "]" << "[" << j -1<< "].next的长度为:" << P[i+x-1][j-1].next.size() << endl;
						if (Arr[a][j] != 0)
						{
							//string *str = new string[m + 1];
							vector<string> str(m + 1);
							str[0] = ch;
							//str.push_back(ch);//新更改的
							for (k = 0; k <= m - 1; k++)
							{
								str[k + 1] = P[i + x - 1][j - 1].next[k] + str1;//这部分应该有问题，出现随机数的地方
								//str.push_back(P[i + x - 1][j - 1].next[k] + str1);
							}

							/*	cout << "$$$$$$$$$$$$$$$其中str1为$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
							cout << "m=" << m;
							cout << "str的长度：" << str.size() << endl;
							for (auto pstr : str)
							cout << pstr << " ";
							cout << endl;
							cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;*/

							P[i + x][j].next = str;
							//P[i + x][j].next.push_back(ch);



							cout << endl;
							cout << "&&&&&&&&&&&&&&&&&&&&&当X ！=0,(1 - Arr[a][j]) != 0时&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
							cout << "i=1时j=" << j << "  x=" << x << "中共有字符为：" << endl;
							cout << "此时的p[" << i + x << "]" << "[" << j << "].next的长度为:" << P[i + x][j].next.size() << endl;
							int count = 0;
							for (striter = P[i + x][j].next.begin(); striter != P[i + x][j].next.end(); striter++)
							{
								count++;
								cout << count << "." << *striter << " ";
							}
							cout << endl;




						}


						else
						{
							//string *str = new string[m];
							vector<string> str(m);
							for (k = 0; k <= m - 1; k++)
							{
								str[k] = P[i + x - 1][j - 1].next[k] + str1;//这部分应该有问题，出现随机数的地方
								//str.push_back(P[i + x - 1][j - 1].next[k] + str1);

								//	cout << "str[" << k << "]=" << str[k] << endl;
							}

							////cout << "$$$$$$$$$$$$$$$其中str2为$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
							////cout << "m=" << m;
							////cout << "str的长度：" << str.size() << endl;
							////for (auto pstr : str)
							////	cout << pstr << " ";
							////cout << endl;
							////cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;


							P[i + x][j].next = str;

							cout << endl;
							cout << "&&&&&&&&&&&&&&&&&&&&&&&&最后一个可能&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
							cout << "i=1时j=" << j << "  x=" << x << "中共有字符为：" << endl;
							//	printf("新加入的ch:%s", ch);
							cout << "此时的p[" << i + x << "]" << "[" << j << "].next的长度为:" << P[i + x][j].next.size() << endl;
							int count = 0;
							for (striter = P[i + x][j].next.begin(); striter != P[i + x][j].next.end(); striter++)
							{
								count++;
								cout << count << "." << *striter << " ";
							}
							cout << endl;


						}
					}
				}
			}


	}
	/*
	cout << "i=1时" << endl;
	for (j = 1; j <= N - (M - 1)*(L + 1); j++)
	{
	cout << endl;

	cout << "*********************************************************" << endl;

	cout << "此时的p[" << i << "]" << "[" << j << "].next的长度为:" << P[i][j].next.size() << endl;

	for (striter = P[i][j].next.begin(); striter != P[i][j].next.end(); striter++)
	{
	cout << *striter << " ";
	}
	cout << endl;
	}*/

	//*************************************************************************************
	//第二种情况当2≤i＜M时
	cout << endl;
	cout << "************************进入第二种2≤i＜M情况******************************" << endl;

	for (i = 2; i < M; i++)
	{

		int a = chartorol(ch1[i]);
		for (j = i + (i - 1)*L; j <= N - (M - i)*(L + 1); j++)
		{
			//10.10注释
			ymax = min(j - i - (i - 1)*L, g);
			ymin = max(g - (N - (M - i)*(L + 1) - j), 0);

			//10.10添加
			if (ymin > ymax)
			{
				cout << "@@@@@@@@@@@@@@@@@@@@@@@@@ymin>ymax@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

				/*int temp;
				temp = ymin;
				ymin = ymax;
				ymax = temp;*/
				ymin = ymax;
			}

			for (x = ymin; x <= ymax; x++)
				if (x == 0)
				{

					P[i + (i - 1)*g][j].data = Arr[a][j] * P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data;//10.9.2修改
					if (Arr[a][j] != 0 && P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data != 0)
					{
						int m = (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next).size();
						//string *str = new string[m];
						vector<string> str(m);
						for (k = 0; k <= m - 1; k++)
						{
							str[k] = P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next[k];

							cout << "%%%%%%%%%%%%%%%%%%%%%%加前1%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
							cout << "长度为：" << str[k].length() << " ";
							int agostrlen = str[k].size();//9月15号添加 下同
							int count1 = 1;
							for (auto pstr : str[k])
							{
								cout << "count=" << count1 << ":" << pstr << " ";
								count1++;
							}
							cout << endl;

							str[k].resize(j);//新添加的语句，用于对str[k]进行扩充
							for (kk = 1; kk <= L; kk++)
							{
								//str[k] += str1;
								str[k][agostrlen + kk - 1] = '0';
							}
							str[k][j - 1] = ch1[i];  //这样对string类型的数据操作合法吗？
							str[k][j] = '\0';

							cout << "%%%%%%%%%%%%%%%%%%%%加后%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
							cout << "长度为：" << str[k].length() << " ";
							cout << "str[" << k << "].size=" << str[k].size() << endl;
							int count2 = 1;
							for (auto pstr : str[k])
							{
								cout << "count=" << count2 << pstr << " ";
								count2++;
							}

							cout << endl;


						}
						P[i + (i - 1)*g][j].next = str;
					}
					else
						P[i + (i - 1)*g][j].next = svec;
				}



				else
				{
					//下面一句9月15号注释
					//P[i + (i - 1)*g + x][j].data = (1 - Arr[a][j])*P[i + (i - 1)*g + x - 1][j - 1].data + Arr[a][j] * (P[i + (i - 1)*g + x - 1][j - 1].data + P[i - 1 + (i - 2)*g + x][j - 1 - L].data - common(P[i + (i - 1)*g + x - 1][j - 1].next, P[i - 1 + (i - 2)*g + x][j - 1 - L].next, L, H));//现将common不参与进来，进行调试
					if ((1 - Arr[a][j]) != 0 && P[i + (i - 1)*g + x - 1][j - 1].data != 0)
					{
						P[i + (i - 1)*g + x][j].data = (1 - Arr[a][j])*P[i + (i - 1)*g + x - 1][j - 1].data;//9月15号新加

						int m = (P[i + (i - 1)*g + x - 1][j - 1].next).size();
						//string *str = new string[m];
						vector<string> str(m);
						for (k = 0; k <= m - 1; k++)
							str[k] = P[i + (i - 1)*g + x - 1][j - 1].next[k] + str1;
						P[i + (i - 1)*g + x][j].next = str;
					}
					else
					{
						P[i + (i - 1)*g + x][j].next = svec;
						P[i + (i - 1)*g + x][j].data = 0;//9月15号新加

					}

					//9.7号更改下面部分******************************************************************************************************************
					//if ((Arr[a][j] != 0) && (P[i + (i - 1)*g + x - 1][j - 1].data != 0) && (P[i - 1 + (i - 2)*g + x][j - 1 - L].data != 0))//10月9号注释
					if ((Arr[a][j] != 0) && (P[i + (i - 1)*g + x - 1][j - 1].data != 0) && (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data != 0))//10月9.2号添加
					{

						cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << j << endl;

						cout << "传入common:pointer1长度为=" << P[i + (i - 1)*g - 1][j - 1].next.size() << " P[" << i + (i - 1)*g + x - 1 << "][" << j - 1 << "].next:";
						for (auto pstr : P[i + (i - 1)*g + x - 1][j - 1].next)
							cout << pstr << " ";
						cout << endl;

						cout << "传入common:pointer2长度为=" << P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next.size() << " P[" << (i - 1) + (i - 2)*g + ymax << "][" << j - 1 - L << "].next:";
						for (auto pstr : P[i + (i - 1)*g - 1][j - 1 - L].next)
							cout << pstr << " ";
						cout << endl;

						//下面一句是9月15号新加
						P[i + (i - 1)*g + x][j].data += Arr[a][j] * (P[i + (i - 1)*g + x - 1][j - 1].data + P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data - common(P[i + (i - 1)*g + x - 1][j - 1].next, P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next, L, H));

						int m = (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next).size();
						int n = (P[i + (i - 1)*g + x - 1][j - 1].next).size();
						vector<string> str(m + n);
						//string *str = new string[m + n];


						for (k = 0; k <= m - 1; k++)
						{


							str[k] = P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next[k];

							int count1 = 1;
							cout << "%%%%%%%%%%%%%%%%%%%%%%加前2%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
							cout << "长度为：" << str[k].length() << " ";
							for (auto pstr : str[k])
							{
								cout << "count=" << count1 << ":" << pstr << " ";
								count1++;
							}
							cout << endl;


							int agostrlen = str[k].size();
							str[k].resize(j);//新添加的语句，用于对str[k]进行扩充
							for (kk = 1; kk <= L; kk++)
							{
								//str[k] += str1;
								str[k][agostrlen + kk - 1] = '0';
							}

							str[k][j - 1] = ch1[i];
							str[k][j] = '\0';

							int count2 = 1;
							cout << "%%%%%%%%%%%%%%%%%%%%%%加后2%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
							cout << "长度为：" << str[k].length() << " ";
							for (auto pstr : str[k])
							{
								cout << "count=" << count2 << ":" << pstr << " ";
								count2++;
							}
							cout << endl;


						}
						for (k = m; k <= m + n - 1; k++)
							str[k] = P[i + (i - 1)*g + x - 1][j - 1].next[k - m] + str1;
						P[i + (i - 1)*g + x][j].next = str;
					}

					else
						//P[i + (i - 1)*g + x][j].next = svec;//9.7号注释

						if ((Arr[a][j] != 0) && (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data != 0) && (P[i + (i - 1)*g + x - 1][j - 1].data == 0))
						{

							P[i + (i - 1)*g + x][j].data += Arr[a][j] * P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data;//10.9%%%%%%%%%%%%不需要修改吗？？9月15号新加

							int m = (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next).size();
							//string *str = new string[m];
							vector<string> str(m);
							for (k = 0; k <= m - 1; k++)
							{
								str[k] = P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next[k];//此处有问题，当str[k]=P[][].next[k],赋值是则把其所有值以及长度都复制过去了


								int count1 = 1;
								cout << "%%%%%%%%%%%%%%%%%%%%%%加前3%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
								cout << "长度为：" << str[k].length() << " ";
								for (auto pstr : str[k])
								{
									cout << "count=" << count1 << ":" << pstr << " ";
									count1++;
								}
								cout << endl;


								int agostrlen = str[k].size();
								str[k].resize(j);//新添加的语句，用于对str[k]进行扩充
								for (kk = 1; kk <= L; kk++)
								{
									//str[k] += str1;
									str[k][agostrlen + kk - 1] = '0';
								}
								str[k][j - 1] = ch1[i];
								str[k][j] = '\0';


								int count2 = 1;
								cout << "%%%%%%%%%%%%%%%%%%%%%%加后3%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
								cout << "长度为：" << str[k].length() << " ";
								for (auto pstr : str[k])
								{
									cout << "count=" << count2 << ":" << pstr << " ";
									count2++;
								}
								cout << endl;
								//cout << "=0,str[" << k << "]=" << str[k] << endl;

							}
							P[i + (i - 1)*g + x][j].next = str;
						}
						else
							//P[i + (i - 1)*g + x][j].next = svec;//9.7号注释


							if ((Arr[a][j] != 0) && (P[i + (i - 1)*g + x - 1][j - 1].data != 0) && (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data == 0))
							{
								P[i + (i - 1)*g + x][j].data += Arr[a][j] * P[i + (i - 1)*g + x - 1][j - 1].data;//9月15号添加

								int m = (P[i + (i - 1)*g + x - 1][j - 1].next).size();
								//string *str = new string[m];
								vector<string> str(m);
								for (k = 0; k <= m - 1; k++)
									str[k] = P[i + (i - 1)*g + x - 1][j - 1].next[k] + str1;
								P[i + (i - 1)*g + x][j].next = str;
							}
					//	else //9.7号注释
					//	P[i + (i - 1)*g + x][j].next = svec;//9.7号注释
					//9.7号更改上面部分******************************************************************************************************************
				}
		}
	}


	//*************************************************************************************
	//第三种情况当i=M时
	cout << endl;
	cout << "************************进入第三种i=M情况******************************" << endl;
	i = M;
	int a = chartorol(ch1[i]);
	for (j = M + (M - 1)*L; j <= N; j++)
	{
		gg = g;
		if ((M - 1) + (M - 2)*L + gg > j - 1 - L)
			gg = j - 1 - L - (M - 1) - (M - 2)*L;

		cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << j << endl;

		cout << "传入common:pointer1长度为=" << P[M + (M - 1)*g][j - 1].next.size() << " P[" << M + (M - 1)*g << "][" << j - 1 << "].next:";
		for (auto pstr : P[M + (M - 1)*g][j - 1].next)
			cout << pstr << " ";
		cout << endl;

		cout << "传入common:pointer2长度为=" << P[M - 1 + (M - 2)*g + gg][j - 1 - L].next.size() << " P[" << M - 1 + (M - 2)*g + gg << "][" << j - 1 - L << "].next:";

		/*for (auto pstr : P[M - 1 + (M - 2)*g + gg][j - 1 - L].next)
			cout << pstr << " ";
		cout << endl;*/

		//9月14号注释下面一句
		//P[M + (M - 1)*g][j].data = (1 - Arr[a][j])*P[M + (M - 1)*g][j - 1].data + Arr[a][j] * (P[M + (M - 1)*g][j - 1].data + P[M - 1 + (M - 2)*g + gg][j - 1 - L].data - common(P[M + (M - 1)*g][j - 1].next, P[M - 1 + (M - 2)*g + gg][j - 1 - L].next, L, H));


		if ((1 - Arr[a][j]) != 0 && P[M + (M - 1)*g][j - 1].data != 0)
		{
			P[M + (M - 1)*g][j].data = (1 - Arr[a][j])*P[M + (M - 1)*g][j - 1].data;//9.8号添加

			int m = (P[M + (M - 1)*g][j - 1].next).size();
			//string *str = new string[m];

			if (m < 0 || m>800000)
				m = 0;

			vector<string> str(m);
		

			for (k = 0; k <= m - 1; k++)
				str[k] = P[M + (M - 1)*g][j - 1].next[k] + str1;
			P[M + (M - 1)*g][j].next = str;
		}
		else{
			P[M + (M - 1)*g][j].next = svec;
			P[M + (M - 1)*g][j].data = 0;	//9.8号添加


		}


		//8_30号这一部分进行改动…………………………………………………………………………………………
		if ((Arr[a][j] != 0) && (P[M + (M - 1)*g][j - 1].data != 0) && (P[M - 1 + (M - 2)*g + gg][j - 1 - L].data != 0))
		{
			//下面一句是9.8号添加
			P[M + (M - 1)*g][j].data += Arr[a][j] * (P[M + (M - 1)*g][j - 1].data + P[M - 1 + (M - 2)*g + gg][j - 1 - L].data - common(P[M + (M - 1)*g][j - 1].next, P[M - 1 + (M - 2)*g + gg][j - 1 - L].next, L, H));
			//9月14号添加
			double commonresult = common(P[M + (M - 1)*g][j - 1].next, P[M - 1 + (M - 2)*g + gg][j - 1 - L].next, L, H);
			cout << "commonresult=" << commonresult << endl;

			int m = (P[M - 1 + (M - 2)*g + gg][j - 1 - L].next).size();
			int n = (P[M + (M - 1)*g][j - 1].next).size();

			if (m < 0 || m>800000)
				m = 0;

			if (n < 0 || n>800000)
				n = 0;
			//string *str = new string[m + n];
			vector<string> str(m + n);
			for (k = 0; k <= m - 1; k++)
			{
				str[k] = P[M - 1 + (M - 2)*g + gg][j - 1 - L].next[k];
				int agostrlen = str[k].size();

				str[k].resize(j);//%%%%%%%%%%%%%%%%%%%%%%%%
				for (kk = 1; kk <= L; kk++)//9.15号重点调试的部
				{
					//str[k] += str1;
					str[k][agostrlen + kk - 1] = '0';

				}

				str[k][j - 1] = ch1[i];
				str[k][j] = '\0';         //%%%%%%%%%%%%%%%%%此处当i=2,j=3的时候会出现问题
			}
			for (k = m; k <= m + n - 1; k++)
				str[k] = P[M + (M - 1)*g][j - 1].next[k - m] + str1;
			P[M + (M - 1)*g][j].next = str;
		}
		else
			//P[M + (M - 1)*g][j].next = svec;//8.30号注释

			if ((Arr[a][j] != 0) && (P[M - 1 + (M - 2)*g + gg][j - 1 - L].data != 0) && (P[M + (M - 1)*g][j - 1].data == 0))
			{
				P[M + (M - 1)*g][j].data += Arr[a][j] * P[M - 1 + (M - 2)*g + gg][j - 1 - L].data;//9.8号添加

				int m = (P[M - 1 + (M - 2)*g + gg][j - 1 - L].next).size();

				if (m < 0 || m>800000)
					m = 0;
				vector<string> str(m);
				

				//string *str = new string[m];
				for (k = 0; k <= m - 1; k++)
				{

					str[k] = P[M - 1 + (M - 2)*g + gg][j - 1 - L].next[k];
					int agostrlen = str[k].size();

					str[k].resize(j);//新添加的语句，用于对str[k]进行扩充

					int length = str[k].length();//8_29新加
					for (kk = 1; kk <= L; kk++)
					{
						//str[k] += str1;
						str[k][agostrlen + kk - 1] = '0';
					}
					str[k][j - 1] = ch1[i];
					str[k][j] = '\0';
				}
				P[M + (M - 1)*g][j].next = str;

				cout << str[0] << endl;  //8_29新加
				cout << P[M + (M - 1)*g][j].next[0] << endl;//8_29新加



			}
			else
				//P[M + (M - 1)*g][j].next = svec;//8.30注释




				if ((Arr[a][j] != 0) && (P[M + (M - 1)*g][j - 1].data != 0) && (P[M - 1 + (M - 2)*g + gg][j - 1 - L].data == 0))
				{
					P[M + (M - 1)*g][j].data += Arr[a][j] * P[M + (M - 1)*g][j - 1].data;//9.8号添加
					int m = (P[M + (M - 1)*g][j - 1].next).size();
					//string *str = new string[m];
					cout << "m=P[" << M + (M - 1)*g << "][" << j - 1 << "].next.size()=" << (P[M + (M - 1)*g][j - 1].next).size() << endl;

					if (m < 0 || m>800000)
						m = 0;
					vector<string> str(m);
					for (k = 0; k <= m - 1; k++)
					{
						//	cout << i + (i - 1)*g + x - 1 <<" "<< j - 1 << endl;
						//	cout << "P[" << i + (i - 1)*g  << "][" << j - 1 << "].next[" << k << "]=" << P[i + (i - 1)*g][j - 1].next[k]<<endl;

						//str[k] = P[i + (i - 1)*g + x - 1][j - 1].next[k] + str1;//9.22跑到此出现问题
						str[k] = P[i + (i - 1)*g][j - 1].next[k] + str1;//9.22新添加的语句

						cout << str[k] << endl;//8_29新加

					}

					P[M + (M - 1)*g][j].next = str;
				}
		//else    //9.2号注释
		//P[M + (M - 1)*g][j].next = svec; //9.2号注释
	}

	//8.30号改动上面一部分……………………………………………………………………………………………………………………………………………………………………


	//for (i = 1; i <= (M - 1)*(H - L + 1) + 1; i++)
	//{
	//	for (j = 1; j <= N; j++)

	//		cout << P[i][j].data << " ";
	//	cout << endl;

	//}

	cout << endl;

	int temp = 1;
	int flag = 0;
	for (i = 1; i <= M; i++)
	{
		if (flag == 1)
			temp = temp + g + 1;
		if (i == M)
		{
			//temp = temp - 3;
			cout << "i=" << i << endl;
			for (j = 1; j <= N; j++)
				cout << setw(6) << left << P[temp][j].data << " ";
			return;
		}
		cout << "i=" << i << endl;
		for (int x = 0; x <= g; x++)
		{
			//cout << "x=" << x << "  ";
			for (j = 1; j <= N; j++)
				cout << setw(6) << left << P[temp + x][j].data << " ";
			flag = 1;
			cout << endl;
		}


		cout << endl << endl;
	}



	cout << endl;
}

void main()
{
	cout << "wildCard" << endl;
	//string s3 = "ACTAC";
	string s3 = "AGC";
	double prob;
	filetoarray();
	//int flag = inter(s1, s2, s3, prob);
	//cout << flag << endl;
	//cout << prob << endl;
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 12; j++)
		{
			cout << Arr[i][j] << "  ";
		}
		cout << endl;
	}

	clock_t start, finish;
	double total;
	start = clock();
	DP(0,1, s3,8);
	finish = clock();
	total = (double)finish - start;
	cout << "total=" << total;

	getchar();
}