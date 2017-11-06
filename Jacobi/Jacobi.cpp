#include<iostream>

using namespace std;

/*定义全局变量
* N：迭代的次数， sum:迭代的时候求和 ， n：方程的维数
*/
int N=20;
double sum;
const int n = 3;

/*d定义并输入函数，将系数矩阵A，B值和初始值x0[]*/
void input(double ** &a,double * &b,double * &x0)
{
	int i;
	a = new double *[n];            //为a开辟一个* n行空间
	b = new double [n];				//为b开辟一个n行空间
	x0 = new double[n];				//为x0开辟一个n行空间

	for (i = 0; i < n; i++)
	{
		a[i] = new double [n];		//为每一个*a开辟一个n行空间
	}
	
	cout << "请输入系数矩阵A，以空格分隔:" << endl;
	/*输入矩阵A[][]*/
	for (i = 0; i < n; i++)			
	{
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	}

	cout << "请输入矩阵B，以空格分隔:" << endl;
	for (i = 0; i < n; i++)
		cin >> b[i];

	cout << "请输入初始值，以空格分隔：";
	for (i = 0; i < n; i++)
	{
		cin >> x0[i];
	}
}

/*判断误差限，并输出最后的解*/
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

/*jacobi迭代法*/
void jacobi()
{
	cout << "----------------jacobi--------------" << endl;
	int i, j, k;
	
	double ** a = NULL; 
	double * b = NULL;
	double *x0 = NULL;
	input(a, b, x0);				 //调用输入函数
	double x[n],x1[n];

	for (i = 0; i < n; i++)			//初始值的导入
		x[i]=x0[i];

	/*迭代格式
	*其中x1[i]记录第（k-1）次的迭代结果，x[i]记录第k次的迭代结果;调用误差限函数比较 ：x0[i]和x[i]的大小
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
		threshold(x, x0);				//调用误差函数

	}

}

/*gauss_seidel迭代法*/
void gauss_seidel()
{
	cout << "-----------------gauss_seidel---------------" << endl;
	int i, j, k;

	double ** a = NULL;
	double * b = NULL;
	double *x0 = NULL;
	input(a, b, x0);     //调用输入函数
	double x[n];

	for (i = 0; i < n; i++)			//初始值的导入
		x[i] = x0[i];
	
	/*迭代格式
	* 其中x1[i]记录第（k-1）次的迭代结果，x[i]记录第k次的迭代结果;
	* 调用误差限函数比较 ：x0[i]和x[i]的大小
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
		threshold(x, x0);				//调用误差函数
		
	}
}

/*SOR迭代法*/
void sor() 
{
	cout << "----------------SOR---------------" << endl;
	int i, j, k;

	double ** a = NULL;
	double * b = NULL;
	double *x0 = NULL;
	input(a, b, x0);				 //调用输入函数
	double x[n],x1[n];
	double w=1.005;//松弛因子

	for (i = 0; i < n; i++)			//初始值的导入
		x[i] = x0[i];

	/*迭代格式
	* 其中x1[i]记录第（k-1）次的迭代结果，x[i]记录第k次的迭代结果;
	* 调用误差限函数比较 ：x0[i]和x[i]的大小
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
		threshold(x, x0);				//调用误差函数
	}

}

/*迭代函数的调用，按键盘1,2,3实现*/
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
		<< "  1、使用jacobi迭代法解方程组，请按1 \n"
		<< "  2、使用Gauss_seild迭代法解方程组，请按2\n"
		<< "  3、使用sor迭代法解方程组，请按3\n"
	   << "/********************************/\n";
	
	ite();		//调用迭代函数
	system("pause");
	return 0;
}