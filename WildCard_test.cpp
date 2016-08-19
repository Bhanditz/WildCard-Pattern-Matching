#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include <iomanip>
#include<algorithm>
using namespace std;
static double Arr[5][15] = { 0 };  //���ڴ���ļ������ݵ�����

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
A��B��C = A+B+C - A��B - B��C - C��A +A��B��C= A+B+C �C (A��B + B��C + C��A -A��B��C)��
����ÿ�μ��㼴�������е�һ��翪ʼ����(A+B+C)�ĸ��ʣ�Ȼ����(A��B + B��C + C��A)�ĸ��ʣ�
�����(A��B��C)�ĸ��ʣ�������ʵ���������sign=-sign���õ���������������С�
*/
int inter(string &temp1, string &temp2, string &temp, double &prob)
{
	//cout << "inter:" << temp1 << " " << temp2 << endl;//8.31ע��
	int flag = 1, k;
	int m = temp1.size();

	prob = 1.0;
	temp.resize(m + 1);//�˴�Ӧ����������ģ��������Ż���ʱ��ѡ����ʵĴ�С
	//temp.resize(m+1);
	temp[0] = '\0';//%%%%%%%%%%%%��Ҫע�⣬temp���±��Ǵ�1��ʼ�洢�ġ�

	//�ֱ�ʹ2��string���±��1��ʼ 
	char *ch1 = new char[m + 1];
	for (int i = 0; i < m; i++)
		ch1[i + 1] = temp1[i];
	ch1[0] = '\0';

	//int temp2len = temp2.size();//9.22���
	char *ch2 = new char[m + 1];//9.22�޸�
	for (int i = 0; i < m; i++)//9.22�޸�
		ch2[i + 1] = temp2[i];//9.22��������
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
			prob *= Arr[i][k]; //s�������dp�������Ǵ�1��ʼ������
		}
	}
	//cout << "inter: prob" << prob << endl;//8.31ע��
	return flag;
}



//���ļ��е����ݴ���Arr�ĺ���
void filetoarray()
{
	ifstream input("C:\\Users\\lzz\\Documents\\Visual Studio 2013\\Projects\\CO\\WildCard�����ļ�\\����\\7.txt");
	if (!input)
		cerr << "error!";

	string line, word;
	int i(1), j(1);
	while (getline(input, line))  //��ȡÿ�е��ַ�
	{
		istringstream isstream(line);//����¼�󶨵��ն������
		while (isstream >> word)  //��ȡ�����ÿո�����ĵ�������
		{
			Arr[i][j] = stod(word);  //stringתdouble
			++j;
		}
		++i;
		j = 1;
	}


}



double common(vector<string> pointer1, vector<string> pointer2, int L, int H)
{
	//cout << "����common" << endl;
	int m = pointer2.size();
	int n = pointer1.size();
	//cout << "pointer1�ĳ��ȣ�" << n << endl;
	//cout << "pointer2�ĳ��ȣ�" << m << endl;

	//	/*vector <string>::iterator striter;
	//	for (striter = pointer1.begin(); striter != pointer1.end();striter++)
	//	{
	//		cout<<"��������pointer1:"<<*striter<<endl;
	//	}
	//
	//	for (striter = pointer2.begin(); striter != pointer2.end(); striter++)
	//	{
	//		cout << "��������pointer2:" << *striter << endl;
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
	

	varray.resize(2*(m+n)*m*n);//��С��Ҫ�����趨��ѡ��ȽϺ��ʵģ���ʡ�ռ��Լ���ֹԽ��
	cout << "*************����A+B+C�͸���:***************" << endl;
	for (i = 0; i <= m - 1; i++)
	{
		varray.push_back(line);  // Ҫ��ÿһ��vector��ʼ���������ܴ���Ԫ��
		for (j = 0; j <= n - 1; j++)
		{
			if ((flag = inter(temp1[i], temp2[j], temp, prob)) == 1)
			{
				cout << "temp" << temp << endl;//8.31��ע��
				k++;
				varray[k].push_back(num1[i]);//%%%%%%%%%%%%%%%%%%%

				varray[k].push_back(num2[j]);//Ҫ����ͬһλ��

				int templength = temp.size();

				char *ch1 = new char[templength];
				int ii;
				for (ii = 0; ii < templength - 1; ii++)
					ch1[ii] = temp[ii + 1];
				ch1[ii] = '\0';//9.2��ע��


				//stringset.push_back(temp);////9.2�����
				stringset.push_back(ch1);//9.2��ע��
				problist.push_back(prob);
				probsum += sign*prob;
				cout << "probsum=" << probsum << endl;//8.31��ע��
			}
			cout << endl;//8.31��ע��
		}
	}

	

	cout << "**********************************************" << endl;


	y = k;
	vector<int>::iterator intiter;

	//9.2�����
	/*
	����������һ��ѭ������ʵAA0G������2345��ֻҪ����һ�ξͿ����ˣ����������6�Σ����Զ���0.1

	��������Ҫ��һ����䣬���dest1���ֵ��ǰ�����ͬ���Ͳ��ü�����
	��仰��if (dest1.size() == varray[i].size() + 1)����Ӿ仰�����˾����ˣ����ǿ���ǰ����û����ͬ�ģ��оͲ����ټ�����

	*/

	varray.resize(2 * (m + n)*m*n+k*k*k);//��С��Ҫ�����趨��ѡ��ȽϺ��ʵģ���ʡ�ռ��Լ���ֹԽ��
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

				//cout << "������set_union()" << endl;
				set_union(varray[i].begin(), varray[i].end(), varray[j].begin(), varray[j].end(), back_inserter(dest1));



				int flag2 = 1;
				if (dest1.size() == varray[i].size() + 1)
				{	//��仰��if(dest1.size() == varray[i].size() + 1)����Ӿ仰�����˾����ˣ����ǿ���ǰ����û����ͬ�ģ��оͲ����ټ�����//9.2�����
					for (int j = 0; j <= k; j++)//*****************************9.2����ӿ�ʼ
					{
						if (dest1 == varray[j])
						{
							flag2 = 0;
							break;
						}

						else
							flag2 = 1;

					}//************************************9.2����ӽ���


					if ((flag = inter(stringset[i], stringset[j], temp, prob)) == 1 && (flag2 == 1))//9.2�����flag2==1
					{

						for (intiter = dest1.begin(); intiter != dest1.end(); intiter++)
							cout << *intiter << " ";
						cout << endl;  //8.31��ע��

						cout << "set_union temp:" << temp << "  prob:" << prob << "k=" << k << endl;//8.31��ע��

						k++;
						varray[k] = dest1;



						int templength = temp.size();
						char *ch1 = new char[templength];
						int ii;
						for (ii = 0; ii < templength - 1; ii++)
							ch1[ii] = temp[ii + 1];
						ch1[ii] = '\0';    //9.2��ע��

						//stringset.push_back(temp);//9.2�����
						stringset.push_back(ch1);//9.2��ע��
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
	cout << "varrayǰ��������" << varray.capacity() << endl;
	varray.shrink_to_fit();
	cout << "varray���������" << varray.capacity() << endl;

	vector <vector <int>> ().swap(varray);
	
	cout << "varray���������" << varray.capacity() << endl;

	return probsum;
}


//max����
int max(const int &a, const int& b)
{
	return a > b ? a : b;
}

//min����
int min(const int &a, const int& b)
{
	return a < b ? a : b;
}


void DP(int L, int H, string q, int N) //pp�Ǹ��ʱ� ����L�Ǽ��Լ�����ߣ�H�Ǽ��Լ�����ߣ�qΪģʽ��NΪ���г���
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

	//��֤q�±��1��ʼ
	char *ch1 = new char[M + 1];

	for (int t = 0; t < M; t++)
		ch1[t + 1] = q[t];
	ch1[0] = '\0';

	//for (int t = 0; t < M+1; t++)
	//cout << "ch1["<<t<<"]="<<ch1[t] << endl;

	for (i = 1; i <= (M - 1)*(H - L + 1) + 1; i++)	// (M - 1)*(H - L + 1) + 1????
		for (j = 0; j <= N; j++)   //M��ģʽ�ĳ��ȣ�N�����еĳ���  ��P���г�ʼ��
			if (i + (i - 1)*L>j)   //%%%%%%%%%%%%%%%%%�¸Ķ�������ȫ������ʼ��
			{

				P[i][j].data = 0;
				P[i][j].next = svec;
			} //P[i][j]�ǽṹ��

	for (j = 0; j <= N; j++)//��P�����һ����ֵ��ֵΪ1
	{
		P[0][j].data = 1;
		P[0][j].next = svec;
	}

	//*************************************************************************************
	//��һ�������i=1ʱ
	i = 1;
	cout << "************************�����һ��i=1���******************************" << endl;

	for (j = 1; j <= N - (M - 1)*(L + 1); j++)
	{

		int a = chartorol(ch1[i]);

		ymax = min(j - 1, g);
		ymin = max(g - (N - (M - 1)*(L + 1) - j), 0);

		//10.10���
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
		for (x = ymin; x <= ymax; x++)  //xΪβ���Լ��

			if (x == 0)  //β���Ϊ0�����
			{
				P[i][j].data = Arr[a][j] * P[i - 1][j - 1].data;
				if (Arr[a][j] != 0)//��P(s[j]=q[1])!=0ʱ��q��1��ʼ������
				{
					for (k = 0; k <= j - 2; k++)
						ch[k] = '0';
					ch[j - 1] = ch1[i];  //q��1��������ch1��1��ʼ��������ch���Ǵ�0��ʼ
					ch[j] = '\0';//ת��Ϊ�ַ�������ʽ



					P[i][j].next.push_back(ch);
					cout << endl;
					cout << "&&&&&&&&&&&&&&&&&&&&&&&&��x=0ʱ&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
					cout << "if x=0 i=1ʱj=" << j << " x=" << x << "�й����ַ�Ϊ��" << endl;
					//printf("�¼����ch:%s\n",ch);
					cout << "��ʱ��p[" << i << "]" << "[" << j << "].next�ĳ���Ϊ:" << P[i][j].next.size() << endl;
					int count = 0;
					for (striter = P[i][j].next.begin(); striter != P[i][j].next.end(); striter++)
					{
						count++;
						cout << count << "." << *striter << " ";
					}

					cout << endl;
				}

				else P[i][j].next = svec;//��P(s[j]=q[1])=0ʱ

			}



		//β�����Ϊ0�����
			else
			{
				P[i + x][j].data = Arr[a][j] * P[i - 1][j - 1].data + (1 - Arr[a][j])*P[i + x - 1][j - 1].data;//dp�й�ʽ��3���ⲿ��Ӧ�������⣬����������ĵط�

				if (Arr[a][j] != 0)  {  //��P(s[j]=q[1]) !=0ʱ,��P(s[j]=q[1]) =1ʱֻ���и�������䣬q��1��ʼ������
					for (k = 0; k <= j - 2; k++)
						ch[k] = '0';
					ch[j - 1] = ch1[i];  //q��1����
					ch[j] = '\0';
					P[i + x][j].next.push_back(ch);

					cout << endl;
					cout << "&&&&&&&&&&&&&&&&&&&&&&&��X��=0��Arr[a][j] != 0ʱ&&&&&&&&&&&&&&&&&&&&&&&" << endl;
					cout << "i=1ʱj=" << j << "  x=" << x << "�й����ַ�Ϊ��" << endl;
					//printf("�¼����ch:%s", ch);
					cout << "��ʱ��p[" << i + x << "]" << "[" << j << "].next�ĳ���Ϊ:" << P[i + x][j].next.size() << endl;
					int count = 0;
					for (striter = P[i + x][j].next.begin(); striter != P[i + x][j].next.end(); striter++)
					{
						count++;
						cout << count << "." << *striter << " ";
					}
					cout << endl;

				}

				else  P[i][j].next = svec;  //nextָ����ַ�����0��ʼ����

				if ((1 - Arr[a][j]) != 0)   //��P(s[j]=q[1])!=1ʱ��q��1��ʼ������
				{
					if (P[i + x - 1][j - 1].data != 0)
					{
						int m = P[i + x - 1][j - 1].next.size();
						//cout << "m=p[" << i+x-1 << "]" << "[" << j -1<< "].next�ĳ���Ϊ:" << P[i+x-1][j-1].next.size() << endl;
						if (Arr[a][j] != 0)
						{
							//string *str = new string[m + 1];
							vector<string> str(m + 1);
							str[0] = ch;
							//str.push_back(ch);//�¸��ĵ�
							for (k = 0; k <= m - 1; k++)
							{
								str[k + 1] = P[i + x - 1][j - 1].next[k] + str1;//�ⲿ��Ӧ�������⣬����������ĵط�
								//str.push_back(P[i + x - 1][j - 1].next[k] + str1);
							}

							/*	cout << "$$$$$$$$$$$$$$$����str1Ϊ$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
							cout << "m=" << m;
							cout << "str�ĳ��ȣ�" << str.size() << endl;
							for (auto pstr : str)
							cout << pstr << " ";
							cout << endl;
							cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;*/

							P[i + x][j].next = str;
							//P[i + x][j].next.push_back(ch);



							cout << endl;
							cout << "&&&&&&&&&&&&&&&&&&&&&��X ��=0,(1 - Arr[a][j]) != 0ʱ&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
							cout << "i=1ʱj=" << j << "  x=" << x << "�й����ַ�Ϊ��" << endl;
							cout << "��ʱ��p[" << i + x << "]" << "[" << j << "].next�ĳ���Ϊ:" << P[i + x][j].next.size() << endl;
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
								str[k] = P[i + x - 1][j - 1].next[k] + str1;//�ⲿ��Ӧ�������⣬����������ĵط�
								//str.push_back(P[i + x - 1][j - 1].next[k] + str1);

								//	cout << "str[" << k << "]=" << str[k] << endl;
							}

							////cout << "$$$$$$$$$$$$$$$����str2Ϊ$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
							////cout << "m=" << m;
							////cout << "str�ĳ��ȣ�" << str.size() << endl;
							////for (auto pstr : str)
							////	cout << pstr << " ";
							////cout << endl;
							////cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;


							P[i + x][j].next = str;

							cout << endl;
							cout << "&&&&&&&&&&&&&&&&&&&&&&&&���һ������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
							cout << "i=1ʱj=" << j << "  x=" << x << "�й����ַ�Ϊ��" << endl;
							//	printf("�¼����ch:%s", ch);
							cout << "��ʱ��p[" << i + x << "]" << "[" << j << "].next�ĳ���Ϊ:" << P[i + x][j].next.size() << endl;
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
	cout << "i=1ʱ" << endl;
	for (j = 1; j <= N - (M - 1)*(L + 1); j++)
	{
	cout << endl;

	cout << "*********************************************************" << endl;

	cout << "��ʱ��p[" << i << "]" << "[" << j << "].next�ĳ���Ϊ:" << P[i][j].next.size() << endl;

	for (striter = P[i][j].next.begin(); striter != P[i][j].next.end(); striter++)
	{
	cout << *striter << " ";
	}
	cout << endl;
	}*/

	//*************************************************************************************
	//�ڶ��������2��i��Mʱ
	cout << endl;
	cout << "************************����ڶ���2��i��M���******************************" << endl;

	for (i = 2; i < M; i++)
	{

		int a = chartorol(ch1[i]);
		for (j = i + (i - 1)*L; j <= N - (M - i)*(L + 1); j++)
		{
			//10.10ע��
			ymax = min(j - i - (i - 1)*L, g);
			ymin = max(g - (N - (M - i)*(L + 1) - j), 0);

			//10.10���
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

					P[i + (i - 1)*g][j].data = Arr[a][j] * P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data;//10.9.2�޸�
					if (Arr[a][j] != 0 && P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data != 0)
					{
						int m = (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next).size();
						//string *str = new string[m];
						vector<string> str(m);
						for (k = 0; k <= m - 1; k++)
						{
							str[k] = P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next[k];

							cout << "%%%%%%%%%%%%%%%%%%%%%%��ǰ1%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
							cout << "����Ϊ��" << str[k].length() << " ";
							int agostrlen = str[k].size();//9��15����� ��ͬ
							int count1 = 1;
							for (auto pstr : str[k])
							{
								cout << "count=" << count1 << ":" << pstr << " ";
								count1++;
							}
							cout << endl;

							str[k].resize(j);//����ӵ���䣬���ڶ�str[k]��������
							for (kk = 1; kk <= L; kk++)
							{
								//str[k] += str1;
								str[k][agostrlen + kk - 1] = '0';
							}
							str[k][j - 1] = ch1[i];  //������string���͵����ݲ����Ϸ���
							str[k][j] = '\0';

							cout << "%%%%%%%%%%%%%%%%%%%%�Ӻ�%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
							cout << "����Ϊ��" << str[k].length() << " ";
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
					//����һ��9��15��ע��
					//P[i + (i - 1)*g + x][j].data = (1 - Arr[a][j])*P[i + (i - 1)*g + x - 1][j - 1].data + Arr[a][j] * (P[i + (i - 1)*g + x - 1][j - 1].data + P[i - 1 + (i - 2)*g + x][j - 1 - L].data - common(P[i + (i - 1)*g + x - 1][j - 1].next, P[i - 1 + (i - 2)*g + x][j - 1 - L].next, L, H));//�ֽ�common��������������е���
					if ((1 - Arr[a][j]) != 0 && P[i + (i - 1)*g + x - 1][j - 1].data != 0)
					{
						P[i + (i - 1)*g + x][j].data = (1 - Arr[a][j])*P[i + (i - 1)*g + x - 1][j - 1].data;//9��15���¼�

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
						P[i + (i - 1)*g + x][j].data = 0;//9��15���¼�

					}

					//9.7�Ÿ������沿��******************************************************************************************************************
					//if ((Arr[a][j] != 0) && (P[i + (i - 1)*g + x - 1][j - 1].data != 0) && (P[i - 1 + (i - 2)*g + x][j - 1 - L].data != 0))//10��9��ע��
					if ((Arr[a][j] != 0) && (P[i + (i - 1)*g + x - 1][j - 1].data != 0) && (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data != 0))//10��9.2�����
					{

						cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << j << endl;

						cout << "����common:pointer1����Ϊ=" << P[i + (i - 1)*g - 1][j - 1].next.size() << " P[" << i + (i - 1)*g + x - 1 << "][" << j - 1 << "].next:";
						for (auto pstr : P[i + (i - 1)*g + x - 1][j - 1].next)
							cout << pstr << " ";
						cout << endl;

						cout << "����common:pointer2����Ϊ=" << P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next.size() << " P[" << (i - 1) + (i - 2)*g + ymax << "][" << j - 1 - L << "].next:";
						for (auto pstr : P[i + (i - 1)*g - 1][j - 1 - L].next)
							cout << pstr << " ";
						cout << endl;

						//����һ����9��15���¼�
						P[i + (i - 1)*g + x][j].data += Arr[a][j] * (P[i + (i - 1)*g + x - 1][j - 1].data + P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data - common(P[i + (i - 1)*g + x - 1][j - 1].next, P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next, L, H));

						int m = (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next).size();
						int n = (P[i + (i - 1)*g + x - 1][j - 1].next).size();
						vector<string> str(m + n);
						//string *str = new string[m + n];


						for (k = 0; k <= m - 1; k++)
						{


							str[k] = P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next[k];

							int count1 = 1;
							cout << "%%%%%%%%%%%%%%%%%%%%%%��ǰ2%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
							cout << "����Ϊ��" << str[k].length() << " ";
							for (auto pstr : str[k])
							{
								cout << "count=" << count1 << ":" << pstr << " ";
								count1++;
							}
							cout << endl;


							int agostrlen = str[k].size();
							str[k].resize(j);//����ӵ���䣬���ڶ�str[k]��������
							for (kk = 1; kk <= L; kk++)
							{
								//str[k] += str1;
								str[k][agostrlen + kk - 1] = '0';
							}

							str[k][j - 1] = ch1[i];
							str[k][j] = '\0';

							int count2 = 1;
							cout << "%%%%%%%%%%%%%%%%%%%%%%�Ӻ�2%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
							cout << "����Ϊ��" << str[k].length() << " ";
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
						//P[i + (i - 1)*g + x][j].next = svec;//9.7��ע��

						if ((Arr[a][j] != 0) && (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data != 0) && (P[i + (i - 1)*g + x - 1][j - 1].data == 0))
						{

							P[i + (i - 1)*g + x][j].data += Arr[a][j] * P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data;//10.9%%%%%%%%%%%%����Ҫ�޸��𣿣�9��15���¼�

							int m = (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next).size();
							//string *str = new string[m];
							vector<string> str(m);
							for (k = 0; k <= m - 1; k++)
							{
								str[k] = P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].next[k];//�˴������⣬��str[k]=P[][].next[k],��ֵ�����������ֵ�Լ����ȶ����ƹ�ȥ��


								int count1 = 1;
								cout << "%%%%%%%%%%%%%%%%%%%%%%��ǰ3%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
								cout << "����Ϊ��" << str[k].length() << " ";
								for (auto pstr : str[k])
								{
									cout << "count=" << count1 << ":" << pstr << " ";
									count1++;
								}
								cout << endl;


								int agostrlen = str[k].size();
								str[k].resize(j);//����ӵ���䣬���ڶ�str[k]��������
								for (kk = 1; kk <= L; kk++)
								{
									//str[k] += str1;
									str[k][agostrlen + kk - 1] = '0';
								}
								str[k][j - 1] = ch1[i];
								str[k][j] = '\0';


								int count2 = 1;
								cout << "%%%%%%%%%%%%%%%%%%%%%%�Ӻ�3%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
								cout << "����Ϊ��" << str[k].length() << " ";
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
							//P[i + (i - 1)*g + x][j].next = svec;//9.7��ע��


							if ((Arr[a][j] != 0) && (P[i + (i - 1)*g + x - 1][j - 1].data != 0) && (P[(i - 1) + (i - 2)*g + ymax][j - 1 - L].data == 0))
							{
								P[i + (i - 1)*g + x][j].data += Arr[a][j] * P[i + (i - 1)*g + x - 1][j - 1].data;//9��15�����

								int m = (P[i + (i - 1)*g + x - 1][j - 1].next).size();
								//string *str = new string[m];
								vector<string> str(m);
								for (k = 0; k <= m - 1; k++)
									str[k] = P[i + (i - 1)*g + x - 1][j - 1].next[k] + str1;
								P[i + (i - 1)*g + x][j].next = str;
							}
					//	else //9.7��ע��
					//	P[i + (i - 1)*g + x][j].next = svec;//9.7��ע��
					//9.7�Ÿ������沿��******************************************************************************************************************
				}
		}
	}


	//*************************************************************************************
	//�����������i=Mʱ
	cout << endl;
	cout << "************************���������i=M���******************************" << endl;
	i = M;
	int a = chartorol(ch1[i]);
	for (j = M + (M - 1)*L; j <= N; j++)
	{
		gg = g;
		if ((M - 1) + (M - 2)*L + gg > j - 1 - L)
			gg = j - 1 - L - (M - 1) - (M - 2)*L;

		cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << j << endl;

		cout << "����common:pointer1����Ϊ=" << P[M + (M - 1)*g][j - 1].next.size() << " P[" << M + (M - 1)*g << "][" << j - 1 << "].next:";
		for (auto pstr : P[M + (M - 1)*g][j - 1].next)
			cout << pstr << " ";
		cout << endl;

		cout << "����common:pointer2����Ϊ=" << P[M - 1 + (M - 2)*g + gg][j - 1 - L].next.size() << " P[" << M - 1 + (M - 2)*g + gg << "][" << j - 1 - L << "].next:";

		/*for (auto pstr : P[M - 1 + (M - 2)*g + gg][j - 1 - L].next)
			cout << pstr << " ";
		cout << endl;*/

		//9��14��ע������һ��
		//P[M + (M - 1)*g][j].data = (1 - Arr[a][j])*P[M + (M - 1)*g][j - 1].data + Arr[a][j] * (P[M + (M - 1)*g][j - 1].data + P[M - 1 + (M - 2)*g + gg][j - 1 - L].data - common(P[M + (M - 1)*g][j - 1].next, P[M - 1 + (M - 2)*g + gg][j - 1 - L].next, L, H));


		if ((1 - Arr[a][j]) != 0 && P[M + (M - 1)*g][j - 1].data != 0)
		{
			P[M + (M - 1)*g][j].data = (1 - Arr[a][j])*P[M + (M - 1)*g][j - 1].data;//9.8�����

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
			P[M + (M - 1)*g][j].data = 0;	//9.8�����


		}


		//8_30����һ���ֽ��иĶ���������������������������������������������������������������������
		if ((Arr[a][j] != 0) && (P[M + (M - 1)*g][j - 1].data != 0) && (P[M - 1 + (M - 2)*g + gg][j - 1 - L].data != 0))
		{
			//����һ����9.8�����
			P[M + (M - 1)*g][j].data += Arr[a][j] * (P[M + (M - 1)*g][j - 1].data + P[M - 1 + (M - 2)*g + gg][j - 1 - L].data - common(P[M + (M - 1)*g][j - 1].next, P[M - 1 + (M - 2)*g + gg][j - 1 - L].next, L, H));
			//9��14�����
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
				for (kk = 1; kk <= L; kk++)//9.15���ص���ԵĲ�
				{
					//str[k] += str1;
					str[k][agostrlen + kk - 1] = '0';

				}

				str[k][j - 1] = ch1[i];
				str[k][j] = '\0';         //%%%%%%%%%%%%%%%%%�˴���i=2,j=3��ʱ����������
			}
			for (k = m; k <= m + n - 1; k++)
				str[k] = P[M + (M - 1)*g][j - 1].next[k - m] + str1;
			P[M + (M - 1)*g][j].next = str;
		}
		else
			//P[M + (M - 1)*g][j].next = svec;//8.30��ע��

			if ((Arr[a][j] != 0) && (P[M - 1 + (M - 2)*g + gg][j - 1 - L].data != 0) && (P[M + (M - 1)*g][j - 1].data == 0))
			{
				P[M + (M - 1)*g][j].data += Arr[a][j] * P[M - 1 + (M - 2)*g + gg][j - 1 - L].data;//9.8�����

				int m = (P[M - 1 + (M - 2)*g + gg][j - 1 - L].next).size();

				if (m < 0 || m>800000)
					m = 0;
				vector<string> str(m);
				

				//string *str = new string[m];
				for (k = 0; k <= m - 1; k++)
				{

					str[k] = P[M - 1 + (M - 2)*g + gg][j - 1 - L].next[k];
					int agostrlen = str[k].size();

					str[k].resize(j);//����ӵ���䣬���ڶ�str[k]��������

					int length = str[k].length();//8_29�¼�
					for (kk = 1; kk <= L; kk++)
					{
						//str[k] += str1;
						str[k][agostrlen + kk - 1] = '0';
					}
					str[k][j - 1] = ch1[i];
					str[k][j] = '\0';
				}
				P[M + (M - 1)*g][j].next = str;

				cout << str[0] << endl;  //8_29�¼�
				cout << P[M + (M - 1)*g][j].next[0] << endl;//8_29�¼�



			}
			else
				//P[M + (M - 1)*g][j].next = svec;//8.30ע��




				if ((Arr[a][j] != 0) && (P[M + (M - 1)*g][j - 1].data != 0) && (P[M - 1 + (M - 2)*g + gg][j - 1 - L].data == 0))
				{
					P[M + (M - 1)*g][j].data += Arr[a][j] * P[M + (M - 1)*g][j - 1].data;//9.8�����
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

						//str[k] = P[i + (i - 1)*g + x - 1][j - 1].next[k] + str1;//9.22�ܵ��˳�������
						str[k] = P[i + (i - 1)*g][j - 1].next[k] + str1;//9.22����ӵ����

						cout << str[k] << endl;//8_29�¼�

					}

					P[M + (M - 1)*g][j].next = str;
				}
		//else    //9.2��ע��
		//P[M + (M - 1)*g][j].next = svec; //9.2��ע��
	}

	//8.30�ŸĶ�����һ���֡���������������������������������������������������������������������������������������������������������������������������


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