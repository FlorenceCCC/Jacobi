#include<iostream>

using namespace std;

/*����ȫ�ֱ���
* N�������Ĵ����� sum:������ʱ����� �� n�����̵�ά��
*/
int N=20;
double sum;
const int n = 3;

/*d���岢���뺯������ϵ������A��Bֵ�ͳ�ʼֵx0[]*/
void input(double ** &a,double * &b,double * &x0)
{
	int i;
	a = new double *[n];            //Ϊa����һ��* n�пռ�
	b = new double [n];				//Ϊb����һ��n�пռ�
	x0 = new double[n];				//Ϊx0����һ��n�пռ�

	for (i = 0; i < n; i++)
	{
		a[i] = new double [n];		//Ϊÿһ��*a����һ��n�пռ�
	}
	
	cout << "������ϵ������A���Կո�ָ�:" << endl;
	/*�������A[][]*/
	for (i = 0; i < n; i++)			
	{
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	}

	cout << "���������B���Կո�ָ�:" << endl;
	for (i = 0; i < n; i++)
		cin >> b[i];

	cout << "�������ʼֵ���Կո�ָ���";
	for (i = 0; i < n; i++)
	{
		cin >> x0[i];
	}
}

/*�ж�����ޣ���������Ľ�*/
void threshold(double *x,double *x0) 
{
	double max = 0.0;
	int i;
	for (i = 0; i < n; i++)
	{
		if (fabs(x[i] - x0[i]) > max)
			max = x[i];
		//cout << "max = " << max << endl;
		if (fabs(max) < 1e-5) 
		{
			cout << "x[" << i << "]=" << x[i] << endl;
			return;
		}
	}
}

/*jacobi������*/
void jacobi()
{
	cout << "----------------jacobi--------------" << endl;
	int i, j, k;
	
	double ** a = NULL; 
	double * b = NULL;
	double *x0 = NULL;
	input(a, b, x0);				 //�������뺯��
	double x[n],x1[n];

	for (i = 0; i < n; i++)			//��ʼֵ�ĵ���
		x[i]=x0[i];

	/*������ʽ
	*����x1[i]��¼�ڣ�k-1���εĵ��������x[i]��¼��k�εĵ������;��������޺����Ƚ� ��x0[i]��x[i]�Ĵ�С
	*/
	for (k = 0; k < N; k++)
	{
		for (i = 0; i < n; i++)
			x1[i] = x[i];
		for (i = 0; i < n; i++)
		{
			sum = 0.0;
			for (j = 0; j < n; j++)
			{
				if (j != i)
					sum = sum + a[i][j] * x1[j];
			}
			x0[i] = x[i];
			x[i] = (b[i] - sum) / a[i][i];
		}
		threshold(x, x0);				//��������

	}

}

/*gauss_seidel������*/
void gauss_seidel()
{
	cout << "-----------------gauss_seidel---------------" << endl;
	int i, j, k;

	double ** a = NULL;
	double * b = NULL;
	double *x0 = NULL;
	input(a, b, x0);     //�������뺯��
	double x[n];

	for (i = 0; i < n; i++)			//��ʼֵ�ĵ���
		x[i] = x0[i];
	
	/*������ʽ
	* ����x1[i]��¼�ڣ�k-1���εĵ��������x[i]��¼��k�εĵ������;
	* ��������޺����Ƚ� ��x0[i]��x[i]�Ĵ�С
	*/
	for (k = 0; k < N; k++)
	{
		for (i = 0; i < n; i++)
		{
			sum = 0.0;
			for (j = 0; j < n; j++)
			{
				if (j != i)
					sum = sum + a[i][j] * x[j];
			}
			x0[i] = x[i];
			x[i] = (b[i] - sum) / a[i][i];
			cout << "x[" << i << "]=" << x[i] << endl;
		}
		threshold(x, x0);				//��������
		
	}
}

/*SOR������*/
void sor() 
{
	cout << "----------------SOR---------------" << endl;
	int i, j, k;

	double ** a = NULL;
	double * b = NULL;
	double *x0 = NULL;
	input(a, b, x0);				 //�������뺯��
	double x[n],x1[n];
	double w=1.005;//�ɳ�����

	for (i = 0; i < n; i++)			//��ʼֵ�ĵ���
		x[i] = x0[i];

	/*������ʽ
	* ����x1[i]��¼�ڣ�k-1���εĵ��������x[i]��¼��k�εĵ������;
	* ��������޺����Ƚ� ��x0[i]��x[i]�Ĵ�С
	*/

	for (k = 0; k < N; k++)
	{
		for (i = 0; i < n; i++)
			x1[i] = x[i];
		for (i = 0; i < n; i++)
		{
			sum = 0.0;
			for (j = 0; j < n; j++)
			{
				if (j < i)
					sum = sum + a[i][j] * x[j];
				else if (j > i)
					sum = sum + a[i][j] * x1[j];
			}
			x0[i] = x[i];
			x[i] = (1 - w)*x1[i] + w*(b[i] - sum) / a[i][i];;
		}
		threshold(x, x0);				//��������
	}

}

/*���������ĵ��ã�������1,2,3ʵ��*/
void ite()
{
	int c;
	//cin >> c;
	cin >> c;
	switch (c)
	{
	case 1:
		jacobi();
		break;
	case 2:
		gauss_seidel();
		break;
	case 3:
		sor();
		break;
	}
}

int main()
{
	cout << "/********************************/\n" 
		<< "  1��ʹ��jacobi�������ⷽ���飬�밴1 \n"
		<< "  2��ʹ��Gauss_seild�������ⷽ���飬�밴2\n"
		<< "  3��ʹ��sor�������ⷽ���飬�밴3\n"
	   << "/********************************/\n";
	
	ite();		//���õ�������
	system("pause");
	return 0;
}