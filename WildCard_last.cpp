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
//static double Arr[5][C] = { 0 };  //���ڴ���ļ������ݵ�����
//static double table[Total][2] = { 0 }; //���ڴ��ĳ����ĸ��ĳ��λ���ϵĸ��ʱ�
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
//A��B��C = A+B+C - A��B - B��C - C��A +A��B��C= A+B+C �C (A��B + B��C + C��A -A��B��C)��
//����ÿ�μ��㼴�������е�һ��翪ʼ����(A+B+C)�ĸ��ʣ�Ȼ����(A��B + B��C + C��A)�ĸ��ʣ�
//�����(A��B��C)�ĸ��ʣ�������ʵ���������sign=-sign���õ���������������С�
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
//	//�ֱ�ʹ2��string���±��1��ʼ 
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
//			prob *= Arr[i][k]; //s�������dp�������Ǵ�1��ʼ������
//		}
//	}
//	return flag;
//}
//
//
//
////�������е�����д�뵽�ļ���
//void arraytofile1(string str, int m, int n)//Ϊд��table��
//{
//	ofstream out(str, ios::out);//���ϴ�д�Ľ������������
//
//	//д���ļ���
//	ofstream os(str, ios::app);
//	if (os)
//	{
//		os << "���г���" << "     ʱ��/����";
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
//		cerr << "�޷����ļ���" << endl;
//	os.close();
//
//
//}
//
//
//
//
//
////���ļ��е����ݴ���Arr�ĺ���
//void filetoarray()
//{
//
//	//string patternstr[10] = { "_1.txt", "_2.txt", "_3.txt", "_4.txt", "_5.txt", "_6.txt", "_7.txt" ,"_8.txt", "_9.txt", "_10.txt" };
//	string patternstr[10] = { "_1.txt", "_2.txt" };
//	string pattern_input[8] = { "pattern_1.txt", "pattern_2.txt", "pattern_3.txt", "pattern_4.txt", "pattern_5.txt","pattern_6.txt","pattern_7.txt","pattern_8.txt"};
//	clock_t start, finish;
//
//	string pattern;
//	int M;//M��ʾģʽ�ĳ���
//	
//
//
//	for (int q = 0; q < 8; q++)
//	{
//
//		int number_pattern = 0;
//		
//		 stringstream ss; //��int��ת��Ϊstringͬʱֵ���� ��1 ->"1"
//		 ss << q+1;
//		string s1 = ss.str();
//		 string s2;
//		 ss >> s2;
//	
//
//		//****************************************��ȡģʽ*******************************
//		ifstream p_input("C:\\Users\\lzz\\Documents\\Visual Studio 2013\\Projects\\CO\\WildCard�����ļ�\\Pattern\\"+pattern_input[q]);
//		if (!p_input)
//			cerr << "ģʽ��ȡ����error!";
//
//		string p_line, p_word;
//		//getline(p_input, p_line, '\n');//��ȡ��һ�С��������Ʋ����д洢
//		while (getline(p_input, p_line))  //��ȡÿ�е��ַ�
//		{
//			istringstream isstream(p_line);//����¼�󶨵��ն������
//				while (isstream >> p_word)  //��ȡ�����ÿո�����ĵ�������
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
//					ifstream input("C:\\Users\\lzz\\Documents\\Visual Studio 2013\\Projects\\CO\\WildCard�����ļ�\\����\\process_data.txt");
//					if (!input)
//						cerr << "���ж�ȡ����!" << endl;
//					int m, len;          //m��Ƕ���ÿ�����������len��Ƕ���ÿ�������
//					string line, word;
//					int i(1), j(1);
//
//					for (int ii = 0; ii < Total; ii++)//��593�����н��ж�ȡ
//					{
//						getline(input, line, '\n');//��ȡ��һ�С��������Ʋ����д洢
//
//						while (getline(input, line))  //��ȡÿ�е��ַ�
//						{
//							istringstream isstream(line);//����¼�󶨵��ն������
//
//							while (isstream >> word)  //��ȡ�����ÿո�����ĵ�������
//							{
//								Arr[i][j] = stod(word);  //stringתdouble
//
//								++j;
//								//len��ʱ��ǵľ������еĳ���
//							}
//							++i;
//							m = i;
//
//							if (i == 5)  //ÿһ����5�У�����һ������ж���һ��Ĵ洢
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
//							DP(0, 2, pattern, len);//��һ������Ϊ��С������ڶ�������Ϊ���������������Ϊģʽ�����ĸ�����Ϊ���г���
//
//							finish = clock();
//							onetime = (double)(finish - start);//�����ʱ�䵥λ�Ǻ���
//							totaltime += onetime;
//							cout << "  totaltime=" << totaltime << endl;
//
//							table[number_Sequence][0] = len;
//							table[number_Sequence][1] = onetime;
//							number_Sequence++;
//							string str1 = "C:\\Users\\lzz\\Documents\\Visual Studio 2013\\Projects\\CO\\WildCard�����ļ�\\result\\" + s2 + patternstr[number_pattern % 10];
//							arraytofile1(str1, number_Sequence, 2);//�������еĸ��ʴ洢���ļ��У���һ��������ʾд���ļ���λ�ӣ��ڶ���������ʾtable�м�¼��������ά���������,����������Ϊÿ�е�Ԫ��������ά��������
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
//	varray.resize(2 * (m + n)*m*n);//��С��Ҫ�����趨��ѡ��ȽϺ��ʵģ���ʡ�ռ��Լ���ֹԽ��
//	//cout << "*************����A+B+C�͸���:***************" << endl;
//	for (i = 0; i <= m - 1; i++)
//	{
//		varray.push_back(line);  // Ҫ��ÿһ��vector��ʼ���������ܴ���Ԫ��
//		for (j = 0; j <= n - 1; j++)
//		{
//			if ((flag = inter(temp1[i], temp2[j], temp, prob)) == 1)
//			{
//				//cout << "temp" << temp << endl;
//				k++;
//				varray[k].push_back(num1[i]);
//
//				varray[k].push_back(num2[j]);//Ҫ����ͬһλ��
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
//	varray.resize(2 * (m + n)*m*n + k*k*k+1000);//��С��Ҫ�����趨��ѡ��ȽϺ��ʵģ���ʡ�ռ��Լ���ֹԽ��
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
////max����
//int max(const int &a, const int& b)
//{
//	return a > b ? a : b;
//}
//
////min����
//int min(const int &a, const int& b)
//{
//	return a < b ? a : b;
//}
//
//
//void DP(int L, int H, string q, int N) //pp�Ǹ��ʱ� ����L�Ǽ��Լ�����ߣ�H�Ǽ��Լ�����ߣ�qΪģʽ��NΪ���г���
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
//		for (j = 0; j <= N; j++)   //M��ģʽ�ĳ��ȣ�N�����еĳ���  ��P���г�ʼ��
//			if (i + (i - 1)*L>j)   
//			{
//
//				P[i][j].data = 0;
//				P[i][j].next = svec;
//			} //P[i][j]�ǽṹ��
//
//	for (j = 0; j <= N; j++)//��P�����һ����ֵ��ֵΪ1
//	{
//		P[0][j].data = 1;
//		P[0][j].next = svec;
//	}
//
//	//*************************************************************************************
//	//��һ�������i=1ʱ
//	i = 1;
//	//cout << "************************�����һ��i=1���******************************" << endl;
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
//		for (x = ymin; x <= ymax; x++)  //xΪβ���Լ��
//
//			if (x == 0)  //β���Ϊ0�����
//			{
//				P[i][j].data = Arr[a][j] * P[i - 1][j - 1].data;
//				if (Arr[a][j] != 0)//��P(s[j]=q[1])!=0ʱ��q��1��ʼ������
//				{
//					for (k = 0; k <= j - 2; k++)
//						ch[k] = '0';
//					ch[j - 1] = ch1[i];  //q��1��������ch1��1��ʼ��������ch���Ǵ�0��ʼ
//					ch[j] = '\0';//ת��Ϊ�ַ�������ʽ
//
//
//
//					P[i][j].next.push_back(ch);
//					
//				}
//
//				else P[i][j].next = svec;//��P(s[j]=q[1])=0ʱ
//
//			}
//
//
//
//		//β�����Ϊ0�����
//			else
//			{
//				P[i + x][j].data = Arr[a][j] * P[i - 1][j - 1].data + (1 - Arr[a][j])*P[i + x - 1][j - 1].data;//dp�й�ʽ��3���ⲿ��Ӧ�������⣬����������ĵط�
//
//				if (Arr[a][j] != 0)  {  //��P(s[j]=q[1]) !=0ʱ,��P(s[j]=q[1]) =1ʱֻ���и�������䣬q��1��ʼ������
//					for (k = 0; k <= j - 2; k++)
//						ch[k] = '0';
//					ch[j - 1] = ch1[i];  //q��1����
//					ch[j] = '\0';
//					P[i + x][j].next.push_back(ch);
//
//					
//				}
//
//				else  P[i][j].next = svec;  //nextָ����ַ�����0��ʼ����
//
//				if ((1 - Arr[a][j]) != 0)   //��P(s[j]=q[1])!=1ʱ��q��1��ʼ������
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
//								str[k + 1] = P[i + x - 1][j - 1].next[k] + str1;//�ⲿ��Ӧ�������⣬����������ĵط�
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
//								str[k] = P[i + x - 1][j - 1].next[k] + str1;//�ⲿ��Ӧ�������⣬����������ĵط�
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
//	//�ڶ��������2��i��Mʱ
//	//cout << endl;
//	//cout << "************************����ڶ���2��i��M���******************************" << endl;
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
//	//�����������i=Mʱ
//	//cout << endl;
//	//cout << "************************���������i=M���******************************" << endl;
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
//			cout << "����û��" << endl;
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
//					str[k].resize(j);//���ڶ�str[k]��������
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
//	cout << "����" << endl;
//	
//
//
//	getchar();
//}