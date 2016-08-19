//#include<iostream>
//#include<string>
//#include<vector>
//#include<fstream>
//#include<sstream>
//#include <iomanip>
//#include<algorithm>
//
//
//#define C 40
//#define Total 593
//using namespace std;
//
//static double Arr[5][C] = { 0 };  //用于存放文件中数据的数组
//static double table[Total][2] = { 0 }; //用于存放某个字母在某个位置上的概率表
//
//double common(vector<string> pointer1, vector<string> pointer2, int L, int H);
//void DP(int L, int H, string q, int N);
//int inter(string &temp1, string &temp2, string &temp, double &prob);
//
//int chartorol(char ch)
//{
//	switch (ch)
//	{
//	case 'A': return 1;
//	case 'C': return 2;
//	case 'G': return 3;
//	case 'T': return 4;
//	default: break;
//	}
//	return 0;
//}
//
///*
//A∪B∪C = A+B+C - A∩B - B∩C - C∩A +A∩B∩C= A+B+C – (A∩B + B∩C + C∩A -A∩B∩C)；
//其中每次计算即计算其中的一项，如开始计算(A+B+C)的概率，然后是(A∩B + B∩C + C∩A)的概率，
//最后是(A∩B∩C)的概率，而其概率的正负号有sign=-sign；得到，即正负交叉进行。
//*/
//int inter(string &temp1, string &temp2, string &temp, double &prob)
//{
//	int flag = 1, k;
//	int m = temp1.size();
//
//	prob = 1.0;
//	temp.resize(m + 1);
//	temp[0] = '\0';
//
//	//分别使2个string的下标从1开始 
//	char *ch1 = new char[m + 1];
//	for (int i = 0; i < m; i++)
//		ch1[i + 1] = temp1[i];
//	ch1[0] = '\0';
//
//	char *ch2 = new char[m + 1];
//	for (int i = 0; i < m; i++)
//		ch2[i + 1] = temp2[i];
//	ch2[0] = '\0';
//	
//	for (k = 1; k < m + 1; k++)
//	{
//		if (ch1[k] != '0' && ch2[k] != '0' && ch1[k] != ch2[k])
//		{
//			flag = 0;
//			return flag;
//		}
//		if (ch1[k] == ch2[k])
//			temp[k] = ch1[k];
//		if (ch1[k] == '0' && ch2[k] != '0')
//			temp[k] = ch2[k];
//		if (ch1[k] != '0' && ch2[k] == '0')
//			temp[k] = ch1[k];
//		if (temp[k] != '0')
//		{
//			int i = chartorol(temp[k]);
//			prob *= Arr[i][k]; //s在下面的dp函数里是从1开始索引的
//		}
//	}
//	return flag;
//}
//
//
//
////把数组中的数据写入到文件中
//void arraytofile1(string str, int m, int n)//为写出table表
//{
//	ofstream out(str, ios::out);//将上次写的进行内容了清空
//
//	//写入文件中
//	ofstream os(str, ios::app);
//	if (os)
//	{
//		os << "序列长度" << "     时间/毫秒";
//		os << endl;
//		for (int i = 0; i<m; ++i)
//		{
//			for (int j = 0; j<n; ++j)
//				os << setiosflags(ios::left) << setw(12) << table[i][j] << "   ";
//			os << endl;
//		}
//		os << endl;
//
//	}
//	else
//		cerr << "无法打开文件！" << endl;
//	os.close();
//
//
//}
//
//
//
//
//
////把文件中的数据存入Arr的函数
//void filetoarray()
//{
//
//	//string patternstr[10] = { "_1.txt", "_2.txt", "_3.txt", "_4.txt", "_5.txt", "_6.txt", "_7.txt" ,"_8.txt", "_9.txt", "_10.txt" };
//	string patternstr[10] = { "_1.txt", "_2.txt" };
//	string pattern_input[8] = { "pattern_1.txt", "pattern_2.txt", "pattern_3.txt", "pattern_4.txt", "pattern_5.txt","pattern_6.txt","pattern_7.txt","pattern_8.txt"};
//	clock_t start, finish;
//
//	string pattern;
//	int M;//M表示模式的长度
//	
//
//
//	for (int q = 0; q < 8; q++)
//	{
//
//		int number_pattern = 0;
//		
//		 stringstream ss; //将int型转换为string同时值不变 即1 ->"1"
//		 ss << q+1;
//		string s1 = ss.str();
//		 string s2;
//		 ss >> s2;
//	
//
//		//****************************************读取模式*******************************
//		ifstream p_input("C:\\Users\\lzz\\Documents\\Visual Studio 2013\\Projects\\CO\\WildCard生成文件\\Pattern\\"+pattern_input[q]);
//		if (!p_input)
//			cerr << "模式读取出错error!";
//
//		string p_line, p_word;
//		//getline(p_input, p_line, '\n');//读取第一行、序列名称不进行存储
//		while (getline(p_input, p_line))  //读取每行的字符
//		{
//			istringstream isstream(p_line);//将记录绑定到刚读入的行
//				while (isstream >> p_word)  //读取该行用空格隔开的单个数据
//				{
//
//
//					pattern = p_word;
//					M = pattern.length();
//					cout << pattern << endl;
//					int number_Sequence = 0;
//
//					double onetime = 0, totaltime = 0;
//
//					ifstream input("C:\\Users\\lzz\\Documents\\Visual Studio 2013\\Projects\\CO\\WildCard生成文件\\序列\\process_data.txt");
//					if (!input)
//						cerr << "序列读取错误!" << endl;
//					int m, len;          //m标记读入每组的行数，用len标记读入每组的列数
//					string line, word;
//					int i(1), j(1);
//
//					for (int ii = 0; ii < Total; ii++)//对593组序列进行读取
//					{
//						getline(input, line, '\n');//读取第一行、序列名称不进行存储
//
//						while (getline(input, line))  //读取每行的字符
//						{
//							istringstream isstream(line);//将记录绑定到刚读入的行
//
//							while (isstream >> word)  //读取该行用空格隔开的单个数据
//							{
//								Arr[i][j] = stod(word);  //string转double
//
//								++j;
//								//len此时标记的就是序列的长度
//							}
//							++i;
//							m = i;
//
//							if (i == 5)  //每一组是5行，读完一组则进行对下一组的存储
//							{
//								i = 1;
//								len = j - 1;
//								j = 1;
//								break;
//
//							}
//							j = 1;
//						}
//
//						cout << ii + 1 << " len=" << len << endl;
//						/*	for (int i = 1; i < 5; i++)
//							{
//							for (int j = 1; j < 12; j++)
//							{
//							cout << Arr[i][j] << "  ";
//							}
//							cout << endl;
//							}
//
//							cout << endl;*/
//
//						if (len <8)
//						{
//							start = clock();
//
//							DP(0, 2, pattern, len);//第一个参数为最小间隔，第二个参数为最大间隔，三个参数为模式，第四个参数为序列长度
//
//							finish = clock();
//							onetime = (double)(finish - start);//计算的时间单位是毫秒
//							totaltime += onetime;
//							cout << "  totaltime=" << totaltime << endl;
//
//							table[number_Sequence][0] = len;
//							table[number_Sequence][1] = onetime;
//							number_Sequence++;
//							string str1 = "C:\\Users\\lzz\\Documents\\Visual Studio 2013\\Projects\\CO\\WildCard生成文件\\result\\" + s2 + patternstr[number_pattern % 10];
//							arraytofile1(str1, number_Sequence, 2);//将数组中的概率存储到文件中，第一个参数表示写入文件的位子，第二个参数表示table中记录个数及二维数组的行数,第三个参数为每行的元素数及二维数组列数
//
//
//						}
//
//
//						else
//
//							continue;
//
//					}
//
//					number_pattern++;
//					cout << number_pattern << endl;
//
//				}
//
//			
//		}
//	}
//
//}
//
//
//
//double common(vector<string> pointer1, vector<string> pointer2, int L, int H)
//{
//	int m = pointer2.size();
//	int n = pointer1.size();
//	
//	vector <vector <int>> varray;
//	vector <int> line;
//	vector <string> stringset;
//	vector <double> problist;
//	vector <int> dest1;
//	int flag, sign = 1, k, i, j, y, z;
//	double prob, probsum = 0;
//	string s = "0";
//	string *temp1 = new string[m];
//	string *temp2 = new string[n];
//	string temp;
//	int *num1 = new int[m];
//	int *num2 = new int[n];
//
//	if ((m == 0) || (n == 0))
//		return 0;
//
//	for (k = 0; k <= m - 1; k++)
//	{
//		temp1[k] = pointer2[k];
//		num1[k] = k + 1;
//		for (i = 1; i <= L; i++)
//			temp1[k] += s;
//	}
//
//	for (k = 0; k <= n - 1; k++)
//	{
//		temp2[k] = pointer1[k];
//		num2[k] = m + k + 1;
//	}
//
//	k = -1;
//	z = k;
//	varray.resize(2 * (m + n)*m*n);//大小需要从新设定，选择比较合适的，节省空间以及防止越界
//	//cout << "*************计算A+B+C和概率:***************" << endl;
//	for (i = 0; i <= m - 1; i++)
//	{
//		varray.push_back(line);  // 要对每一个vector初始化，否则不能存入元素
//		for (j = 0; j <= n - 1; j++)
//		{
//			if ((flag = inter(temp1[i], temp2[j], temp, prob)) == 1)
//			{
//				//cout << "temp" << temp << endl;
//				k++;
//				varray[k].push_back(num1[i]);
//
//				varray[k].push_back(num2[j]);//要存在同一位置
//
//				int templength = temp.size();
//
//				char *ch1 = new char[templength];
//				int ii;
//				for (ii = 0; ii < templength - 1; ii++)
//					ch1[ii] = temp[ii + 1];
//				ch1[ii] = '\0';
//
//				stringset.push_back(ch1);
//				problist.push_back(prob);
//				probsum += sign*prob;
//				//cout << "probsum=" << probsum << endl;
//			}
//			//cout << endl;
//		}
//	}
//
////	cout << "**********************************************" << endl;
//
//	varray.resize(2 * (m + n)*m*n + k*k*k+1000);//大小需要从新设定，选择比较合适的，节省空间以及防止越界
//
//	y = k;
//	vector<int>::iterator intiter;
//
//
//	while (k - z != 0)
//	{
//		sign = (-1)*sign;
//
//		for (i = z + 1; i <= y - 1; i++)
//			for (j = i + 1; j <= y; j++)
//			{
//				vector <int> dest1;
//			
//				set_union(varray[i].begin(), varray[i].end(), varray[j].begin(), varray[j].end(), back_inserter(dest1));
//
//
//
//				int flag2 = 1;
//				if (dest1.size() == varray[i].size() + 1)
//				{	
//					for (int j = 0; j <= k; j++)
//					{
//						if (dest1 == varray[j])
//						{
//							flag2 = 0;
//							break;
//						}
//
//						else
//							flag2 = 1;
//
//					}
//
//
//					if ((flag = inter(stringset[i], stringset[j], temp, prob)) == 1 && (flag2 == 1))
//					{
//
//						
//
//						k++;
//						varray[k] = dest1;
//
//
//
//						int templength = temp.size();
//						char *ch1 = new char[templength];
//						int ii;
//						for (ii = 0; ii < templength - 1; ii++)
//							ch1[ii] = temp[ii + 1];
//						ch1[ii] = '\0';    
//			
//						stringset.push_back(ch1);
//						problist.push_back(prob);
//						probsum += sign*prob;
//					//	cout << "probsum:" << probsum << endl;
//					}
//				}
//			}
//
//		z = y;
//		y = k;
//	//	cout << "**************************************************" << endl;
//	}
//
//	vector <vector <int>>().swap(varray);
//
//	return probsum;
//}
//
//
////max函数
//int max(const int &a, const int& b)
//{
//	return a > b ? a : b;
//}
//
////min函数
//int min(const int &a, const int& b)
//{
//	return a < b ? a : b;
//}
//
//
//void DP(int L, int H, string q, int N) //pp是概率表 其中L是间隔约束下线，H是间隔约束上线，q为模式，N为序列长度
//{
//
//	//cout << q << endl;
//	int g = H - L;
//	int gg = g;
//	int i, j, ymax, ymin, x, k, kk;
//	int M = q.size();
//	string str1 = "0";
//	vector<string> svec;
//	vector<string>::iterator striter;
//	struct PP
//	{
//		double data;
//		vector<string> next;
//	};
//	PP P[100][100];
//
//	
//	char *ch1 = new char[M + 1];
//
//	for (int t = 0; t < M; t++)
//		ch1[t + 1] = q[t];
//	ch1[0] = '\0';
//
//	
//
//	for (i = 1; i <= (M - 1)*(H - L + 1) + 1; i++)	// (M - 1)*(H - L + 1) + 1????
//		for (j = 0; j <= N; j++)   //M是模式的长度，N是序列的长度  对P进行初始化
//			if (i + (i - 1)*L>j)   
//			{
//
//				P[i][j].data = 0;
//				P[i][j].next = svec;
//			} //P[i][j]是结构体
//
//	for (j = 0; j <= N; j++)//将P的最后一行数值赋值为1
//	{
//		P[0][j].data = 1;
//		P[0][j].next = svec;
//	}
//
//	//*************************************************************************************
//	//第一种情况当i=1时
//	i = 1;
//	//cout << "************************进入第一种i=1情况******************************" << endl;
//
//	for (j = 1; j <= N - (M - 1)*(L + 1); j++)
//	{
//
//		int a = chartorol(ch1[i]);
//
//		ymax = min(j - 1, g);
//		ymin = max(g - (N - (M - 1)*(L + 1) - j), 0);
//
//		if (ymin > ymax)
//		{
//		ymin = ymax;
//		}
//
//
//		char *ch = new char[j + 1];
//		for (x = ymin; x <= ymax; x++)  //x为尾间隔约束
//
//			if (x == 0)  //尾间隔为0的情况
//			{
//				P[i][j].data = Arr[a][j] * P[i - 1][j - 1].data;
//				if (Arr[a][j] != 0)//当P(s[j]=q[1])!=0时，q从1开始索引的
//				{
//					for (k = 0; k <= j - 2; k++)
//						ch[k] = '0';
//					ch[j - 1] = ch1[i];  //q从1索引，即ch1从1开始，而序列ch则是从0开始
//					ch[j] = '\0';//转换为字符串的形式
//
//
//
//					P[i][j].next.push_back(ch);
//					
//				}
//
//				else P[i][j].next = svec;//当P(s[j]=q[1])=0时
//
//			}
//
//
//
//		//尾间隔不为0的情况
//			else
//			{
//				P[i + x][j].data = Arr[a][j] * P[i - 1][j - 1].data + (1 - Arr[a][j])*P[i + x - 1][j - 1].data;//dp中公式（3）这部分应该有问题，出现随机数的地方
//
//				if (Arr[a][j] != 0)  {  //当P(s[j]=q[1]) !=0时,当P(s[j]=q[1]) =1时只进行改条件语句，q从1开始索引的
//					for (k = 0; k <= j - 2; k++)
//						ch[k] = '0';
//					ch[j - 1] = ch1[i];  //q从1索引
//					ch[j] = '\0';
//					P[i + x][j].next.push_back(ch);
//
//					
//				}
//
//				else  P[i][j].next = svec;  //next指向的字符串从0开始索引
//
//				if ((1 - Arr[a][j]) != 0)   //当P(s[j]=q[1])!=1时，q从1开始索引的
//				{
//					if (P[i + x - 1][j - 1].data != 0)
//					{
//						int m = P[i + x - 1][j - 1].next.size();
//						if (Arr[a][j] != 0)
//						{
//							vector<string> str(m + 1);
//							str[0] = ch;
//							for (k = 0; k <= m - 1; k++)
//							{
//								str[k + 1] = P[i + x - 1][j - 1].next[k] + str1;//这部分应该有问题，出现随机数的地方
//							}
//
//							
//							P[i + x][j].next = str;
//							
//
//						}
//
//
//						else
//						{
//							
//							vector<string> str(m);
//							for (k = 0; k <= m - 1; k++)
//							{
//								str[k] = P[i + x - 1][j - 1].next[k] + str1;//这部分应该有问题，出现随机数的地方
//								
//							}
//
//							
//
//							P[i + x][j].next = str;
//
//
//						}
//					}
//				}
//			}
//
//
//	}
//	
//
//	//*************************************************************************************
//	//第二种情况当2≤i＜M时
//	//cout << endl;
//	//cout << "************************进入第二种2≤i＜M情况******************************" << endl;
//
//	for (i = 2; i < M; i++)
//	{
//
//		int a = chartorol(ch1[i]);
//		for (j = i + (i - 1)*L; j <= N - (M - i)*(L + 1); j++)
//		{
//		
//			ymax = min(j - i - (i - 1)*L, g);
//			ymin = max(g - (N - (M - i)*(L + 1) - j), 0);
//
//			if (ymin > ymax)
//			{
//			ymin = ymax;
//			}
//
//			for (x = ymin; x <= ymax; x++)
//				if (x == 0)
//				{
//
//					P[i + (i - 1)*g][j].data = Arr[a][j] * P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data;
//					if (Arr[a][j] != 0 && P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data != 0)
//					{
//						int m = (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next).size();
//						
//						vector<string> str(m);
//						for (k = 0; k <= m - 1; k++)
//						{
//							str[k] = P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next[k];
//
//							int agostrlen = str[k].size();
//		
//
//							str[k].resize(j);
//							for (kk = 1; kk <= L; kk++)
//							{
//								
//								str[k][agostrlen + kk - 1] = '0';
//							}
//							str[k][j - 1] = ch1[i];  
//							str[k][j] = '\0';
//
//
//
//						}
//						P[i + (i - 1)*g][j].next = str;
//					}
//					else
//						P[i + (i - 1)*g][j].next = svec;
//				}
//
//
//
//				else
//				{
//					if ((1 - Arr[a][j]) != 0 && P[i + (i - 1)*g + x - 1][j - 1].data != 0)
//					{
//						P[i + (i - 1)*g + x][j].data = (1 - Arr[a][j])*P[i + (i - 1)*g + x - 1][j - 1].data;
//
//						int m = (P[i + (i - 1)*g + x - 1][j - 1].next).size();
//						
//						vector<string> str(m);
//						for (k = 0; k <= m - 1; k++)
//							str[k] = P[i + (i - 1)*g + x - 1][j - 1].next[k] + str1;
//						P[i + (i - 1)*g + x][j].next = str;
//					}
//					else
//					{
//						P[i + (i - 1)*g + x][j].next = svec;
//						P[i + (i - 1)*g + x][j].data = 0;
//					}
//
//					
//					if ((Arr[a][j] != 0) && (P[i + (i - 1)*g + x - 1][j - 1].data != 0) && (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data != 0))
//					{
//
//						
//
//						
//						P[i + (i - 1)*g + x][j].data += Arr[a][j] * (P[i + (i - 1)*g + x - 1][j - 1].data + P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data - common(P[i + (i - 1)*g + x - 1][j - 1].next, P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next, L, H));
//
//						int m = (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next).size();
//						int n = (P[i + (i - 1)*g + x - 1][j - 1].next).size();
//						vector<string> str(m + n);
//						
//
//
//						for (k = 0; k <= m - 1; k++)
//						{
//
//
//							str[k] = P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next[k];
//
//							
//
//
//							int agostrlen = str[k].size();
//							str[k].resize(j);
//							for (kk = 1; kk <= L; kk++)
//							{
//								
//								str[k][agostrlen + kk - 1] = '0';
//							}
//
//							str[k][j - 1] = ch1[i];
//							str[k][j] = '\0';
//
//							
//
//						}
//						for (k = m; k <= m + n - 1; k++)
//							str[k] = P[i + (i - 1)*g + x - 1][j - 1].next[k - m] + str1;
//						P[i + (i - 1)*g + x][j].next = str;
//					}
//
//					else
//				
//
//						if ((Arr[a][j] != 0) && (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data != 0) && (P[i + (i - 1)*g + x - 1][j - 1].data == 0))
//						{
//
//							P[i + (i - 1)*g + x][j].data += Arr[a][j] * P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data;
//
//							int m = (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next).size();
//							
//							vector<string> str(m);
//							for (k = 0; k <= m - 1; k++)
//							{
//								str[k] = P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next[k];
//
//
//								
//
//
//								int agostrlen = str[k].size();
//								str[k].resize(j);
//								for (kk = 1; kk <= L; kk++)
//								{
//									
//									str[k][agostrlen + kk - 1] = '0';
//								}
//								str[k][j - 1] = ch1[i];
//								str[k][j] = '\0';
//
//
//								
//							
//
//							}
//							P[i + (i - 1)*g + x][j].next = str;
//						}
//						else
//							
//
//
//							if ((Arr[a][j] != 0) && (P[i + (i - 1)*g + x - 1][j - 1].data != 0) && (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data == 0))
//							{
//								P[i + (i - 1)*g + x][j].data += Arr[a][j] * P[i + (i - 1)*g + x - 1][j - 1].data;
//
//								int m = (P[i + (i - 1)*g + x - 1][j - 1].next).size();
//								vector<string> str(m);
//								for (k = 0; k <= m - 1; k++)
//									str[k] = P[i + (i - 1)*g + x - 1][j - 1].next[k] + str1;
//								P[i + (i - 1)*g + x][j].next = str;
//							}
//					
//				}
//		}
//	}
//
//
//	//*************************************************************************************
//	//第三种情况当i=M时
//	//cout << endl;
//	//cout << "************************进入第三种i=M情况******************************" << endl;
//	i = M;
//	int a = chartorol(ch1[i]);
//	for (j = M + (M - 1)*L; j <= N; j++)
//	{
//		gg = g;
//		if ((M - 1) + (M - 2)*L + gg > j - 1 - L)
//			gg = j - 1 - L - (M - 1) - (M - 2)*L;
//
//		if ((1 - Arr[a][j]) != 0 && P[M + (M - 1)*g][j - 1].data != 0)
//		{
//			P[M + (M - 1)*g][j].data = (1 - Arr[a][j])*P[M + (M - 1)*g][j - 1].data;
//
//			int m = (P[M + (M - 1)*g][j - 1].next).size();
//			cout <<"m=" <<m << endl;
//			if (m < 0)
//				m = 0;
//
//			vector<string> str(m);
//			for (k = 0; k <= m - 1; k++)
//				str[k] = P[M + (M - 1)*g][j - 1].next[k] + str1;
//			P[M + (M - 1)*g][j].next = str;
//		}
//		else{
//			P[M + (M - 1)*g][j].next = svec;
//			P[M + (M - 1)*g][j].data = 0;	
//
//
//		}
//
//
//		
//		if ((Arr[a][j] != 0) && (P[M + (M - 1)*g][j - 1].data != 0) && (P[M - 1 + (M - 2)*g + gg][j - 1 - L].data != 0))
//		{
//			
//			P[M + (M - 1)*g][j].data += Arr[a][j] * (P[M + (M - 1)*g][j - 1].data + P[M - 1 + (M - 2)*g + gg][j - 1 - L].data - common(P[M + (M - 1)*g][j - 1].next, P[M - 1 + (M - 2)*g + gg][j - 1 - L].next, L, H));
//			
//			double commonresult = common(P[M + (M - 1)*g][j - 1].next, P[M - 1 + (M - 2)*g + gg][j - 1 - L].next, L, H);
//			//cout << "commonresult=" << commonresult << endl;
//
//			int m = (P[M - 1 + (M - 2)*g + gg][j - 1 - L].next).size();
//			int n = (P[M + (M - 1)*g][j - 1].next).size();
//			cout << "m=" << m << " n=" << n << endl;
//			if (m < 0||m>5000)
//				m = 0;
//			if (n < 0 || n>5000)
//				n = 0;
//
//			vector<string> str(m + n);
//		
//
//			cout << "断了没？" << endl;
//			for (k = 0; k <= m - 1; k++)
//			{
//				str[k] = P[M - 1 + (M - 2)*g + gg][j - 1 - L].next[k];
//				int agostrlen = str[k].size();
//
//				str[k].resize(j);
//				for (kk = 1; kk <= L; kk++)
//				{
//					
//					str[k][agostrlen + kk - 1] = '0';
//
//				}
//
//				str[k][j - 1] = ch1[i];
//				str[k][j] = '\0';         
//			}
//			for (k = m; k <= m + n - 1; k++)
//				str[k] = P[M + (M - 1)*g][j - 1].next[k - m] + str1;
//			P[M + (M - 1)*g][j].next = str;
//		}
//		else
//		
//
//			if ((Arr[a][j] != 0) && (P[M - 1 + (M - 2)*g + gg][j - 1 - L].data != 0) && (P[M + (M - 1)*g][j - 1].data == 0))
//			{
//				P[M + (M - 1)*g][j].data += Arr[a][j] * P[M - 1 + (M - 2)*g + gg][j - 1 - L].data;
//
//				int m = (P[M - 1 + (M - 2)*g + gg][j - 1 - L].next).size();
//				cout <<"m="<<m << endl;
//
//				if (m < 0)
//					m = 0;
//				vector<string> str(m);
//
//				for (k = 0; k <= m - 1; k++)
//				{
//
//					str[k] = P[M - 1 + (M - 2)*g + gg][j - 1 - L].next[k];
//					int agostrlen = str[k].size();
//
//					str[k].resize(j);//用于对str[k]进行扩充
//
//					int length = str[k].length();
//					for (kk = 1; kk <= L; kk++)
//					{
//						
//						str[k][agostrlen + kk - 1] = '0';
//					}
//					str[k][j - 1] = ch1[i];
//					str[k][j] = '\0';
//				}
//				P[M + (M - 1)*g][j].next = str;
//
//				//cout << str[0] << endl; 
//			//	cout << P[M + (M - 1)*g][j].next[0] << endl;
//
//
//
//			}
//			else
//				
//
//				if ((Arr[a][j] != 0) && (P[M + (M - 1)*g][j - 1].data != 0) && (P[M - 1 + (M - 2)*g + gg][j - 1 - L].data == 0))
//				{
//					P[M + (M - 1)*g][j].data += Arr[a][j] * P[M + (M - 1)*g][j - 1].data;
//					int m = (P[M + (M - 1)*g][j - 1].next).size();
//					
//					//cout << "m=P[" << M + (M - 1)*g << "][" << j - 1 << "].next.size()=" << (P[M + (M - 1)*g][j - 1].next).size() << endl;
//					cout <<"m="<< m << endl;
//					if (m < 0)
//						m = 0;
//					
//					vector<string> str(m);
//			
//
//
//					for (k = 0; k <= m - 1; k++)
//					{
//						
//						str[k] = P[i + (i - 1)*g][j - 1].next[k] + str1;
//
//					//	cout << str[k] << endl;
//
//					}
//
//					P[M + (M - 1)*g][j].next = str;
//				}
//	
//	}
//
//
////	cout << endl;
//
//	/*int temp = 1;
//	int flag = 0;
//	for (i = 1; i <= M; i++)
//	{
//		if (flag == 1)
//			temp = temp + g + 1;
//		if (i == M)
//		{
//			cout << "i=" << i << endl;
//			for (j = 1; j <= N; j++)
//				cout << setw(6) << left << P[temp][j].data << " ";
//			return;
//		}
//		cout << "i=" << i << endl;
//		for (int x = 0; x <= g; x++)
//		{
//			for (j = 1; j <= N; j++)
//				cout << setw(6) << left << P[temp + x][j].data << " ";
//			flag = 1;
//			cout << endl;
//		}
//
//
//		cout << endl << endl;
//	}*/
//
//
//
//	//cout << endl;
//}
//
//
//
//void main()
//{
//
//	filetoarray();
//
//
//	cout << "结束" << endl;
//	
//
//
//	getchar();
//}