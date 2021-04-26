#include"os_obj3.h"

//文件的输入（储存在结构体中）
void in(process* p, int process_num, int res_num, int *Ava)
{
	const char* filename = "process.txt";
	ifstream ism;
	ism.open(filename);
	if (!ism.is_open())
	{
		cout << "hhhhhhhhh" << endl;
	}
	int i = 0;
	for (i; i < process_num; i++)
	{
		ism >> p[i].name;
		for (int j = 0; j < res_num; j++)
		{
			ism >> p[i].Max[j];
		}
		for (int j = 0; j < res_num; j++)
		{
			ism >> p[i].Allocation[j];
		}
		for (int j = 0; j < res_num; j++)
		{
			ism >> p[i].Need[j];
		}
	}
	for (int k = 0; k < res_num; k++)
	{
		ism >> Ava[k];
	}
}

//输出初始化数据以及最终的安全序列
void out(process* p, int process_num, int res_num, int* Ava, int result,int *seq)
{
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "PID" << "\t" << "work" << "\t" << "Allocation" << "\t" << "Need" << endl;
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].name << "\t";
		for (int j = 0; j < res_num; j++)
		{
			cout<< p[i].Max[j]<<" ";
		}
		cout << "\t";
		for (int j = 0; j < res_num; j++)
		{
			cout << p[i].Allocation[j] << " ";
		}
		cout << "\t";
		cout << "\t";
		for (int j = 0; j < res_num; j++)
		{
			cout << p[i].Need[j] << " ";
		}
		cout << "\t";
		cout << endl;
	}
	cout << "Available" << endl;
	for (int i = 0; i < res_num; i++)
	{
		cout << Ava[i] << " ";
	}
	cout << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	if (result == 0)
	{
		cout << "不安全！！";
	}
	else if (result == 1)
	{
		cout << "安全序列为：" << endl;
		for (int i = 0; i < process_num; i++)
		{
			cout << seq[i] << "\t";
		}
	}
}

//验证是否为安全状态
void security(process* p, int process_num, int res_num, int* Ava,int &result,int *seq)
{
	int count = 0;	//控制循环结束，检查是否有足够的资源完成所有进程
	int flag = 0;	//控制result变量
	int k = 0;	//安全序列数组下标
	int num = 0;	//控制while循环次数，若进行过多次循环说明状态为不安全，结束循环
	while (count < process_num)
	{
		for (int i = 0; i < process_num; i++)
		{
			int key = 0;	//判断当前所拥有的资源是否满足当前的进程的需求
			if (p[i].flag != 1)		//判断进程是否被释放
			{
				for (int j = 0; j < res_num; j++)
				{
					if (Ava[j] < p[i].Need[j])		//检查每一个进程的每一种类资源是否足够
					{
						key = 1;
						break;
					}
					else
					{
						continue;
					}
				}
				if (key == 1)	//若不够，检查下一进程
				{
					continue;
				}
				else
				{
					update(p[i], Ava, res_num, count);
					seq[k] = i;		//记录安全序列
					k++;	
					i = -1;		//从第一个序列开始重新找
					if (count == process_num)
					{
						flag = 1;		//若所有进程均被释放
					}
				}
			}
			else
			{
				continue;
			}
			
		}
		num++;
		if (num > 100) { break; } // 循环次数过多，强行退出循环
	}
	//更新最终结果
	if (flag == 1)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
}

//更新结构体数据以及可支配的总资源数量
void update(process &p, int* Ava, int res_num, int &count)
{
	
	for (int i = 0; i < res_num; i++)
	{
		Ava[i] += p.Max[i];		//更新资源数量
	}
	p.flag = 1;
	count++;
}

int main()
{
	int process_num = 5;
	int res_num = 3;
	int Ava[3] = { 0 };
	int result = 0;
	int seq[10];
	process* p = new process[process_num];
	in(p, process_num, res_num, Ava);
	cout << "Available" << endl;
	for (int i = 0; i < res_num; i++)
	{
		cout << Ava[i] << " ";
	}
	cout << endl;
	security(p, process_num, res_num, Ava, result, seq);
	out(p,process_num, res_num, Ava,result,seq);
}