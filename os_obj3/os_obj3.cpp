#include"os_obj3.h"

//�ļ������루�����ڽṹ���У�
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

//�����ʼ�������Լ����յİ�ȫ����
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
		cout << "����ȫ����";
	}
	else if (result == 1)
	{
		cout << "��ȫ����Ϊ��" << endl;
		for (int i = 0; i < process_num; i++)
		{
			cout << seq[i] << "\t";
		}
	}
}

//��֤�Ƿ�Ϊ��ȫ״̬
void security(process* p, int process_num, int res_num, int* Ava,int &result,int *seq)
{
	int count = 0;	//����ѭ������������Ƿ����㹻����Դ������н���
	int flag = 0;	//����result����
	int k = 0;	//��ȫ���������±�
	int num = 0;	//����whileѭ�������������й����ѭ��˵��״̬Ϊ����ȫ������ѭ��
	while (count < process_num)
	{
		for (int i = 0; i < process_num; i++)
		{
			int key = 0;	//�жϵ�ǰ��ӵ�е���Դ�Ƿ����㵱ǰ�Ľ��̵�����
			if (p[i].flag != 1)		//�жϽ����Ƿ��ͷ�
			{
				for (int j = 0; j < res_num; j++)
				{
					if (Ava[j] < p[i].Need[j])		//���ÿһ�����̵�ÿһ������Դ�Ƿ��㹻
					{
						key = 1;
						break;
					}
					else
					{
						continue;
					}
				}
				if (key == 1)	//�������������һ����
				{
					continue;
				}
				else
				{
					update(p[i], Ava, res_num, count);
					seq[k] = i;		//��¼��ȫ����
					k++;	
					i = -1;		//�ӵ�һ�����п�ʼ������
					if (count == process_num)
					{
						flag = 1;		//�����н��̾����ͷ�
					}
				}
			}
			else
			{
				continue;
			}
			
		}
		num++;
		if (num > 100) { break; } // ѭ���������࣬ǿ���˳�ѭ��
	}
	//�������ս��
	if (flag == 1)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
}

//���½ṹ�������Լ���֧�������Դ����
void update(process &p, int* Ava, int res_num, int &count)
{
	
	for (int i = 0; i < res_num; i++)
	{
		Ava[i] += p.Max[i];		//������Դ����
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