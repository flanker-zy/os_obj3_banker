#pragma once
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

struct process {
	string name;
	int Max[10];
	int Allocation[10];
	int Need[10];
	int flag = 0;
};
void update(process &p, int* Ava, int res_num, int& count);
void security(process* p, int process_num, int res_num, int* Ava, int& result,int *seq);

