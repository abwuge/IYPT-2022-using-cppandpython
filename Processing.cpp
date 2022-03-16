#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "Processing.h"

const double PI = 3.14159265358979323846;//PIΪԲ����(3.14159265358979323846)

using namespace std;

void toEulerAngle(double x, double y, double z, double w, double& roll, double& pitch, double& yaw)//������Ԫ��x��y��z��w�����ŷ����roll��pitvh��yaw
{
	// xƫת��
	double sinr_cosp = +2.0 * (w * x + y * z);
	double cosr_cosp = +1.0 - 2.0 * (x * x + y * y);
	roll = atan2(sinr_cosp, cosr_cosp);

	// yƫת��
	double sinp = +2.0 * (w * y - z * x);
	if (fabs(sinp) >= 1)//���sin p�ľ���ֵ����1���ͽ�arcsin��sin p������Ϊpi/2
		pitch = copysign(PI / 2, sinp);
	else
		pitch = asin(sinp);

	// zƫת��
	double siny_cosp = +2.0 * (w * z + x * y);
	double cosy_cosp = +1.0 - 2.0 * (y * y + z * z);
	yaw = atan2(siny_cosp, cosy_cosp);
}

void Orientation(double& x, double& y, double& z, double& w, int& sides, int& bottom)
{
	double roll, pitch, yaw;//����ŷ��������
	toEulerAngle(x, y, z, w, roll, pitch, yaw);//����Ԫ��תΪŷ����
	if (fabs(roll) > 0.35 * PI && fabs(roll) < 0.65 * PI)//��roll�ľ���ֵΪ1/2PIʱ��Բ��һ�������ŵ�
	{
		sides++;
	}
	else if (fabs(pitch) > 0.35 * PI && fabs(pitch) < 0.65 * PI)//��rollΪ�����������pitch�ľ���ֵΪPI/2ʱ��Բ��Ҳһ�������ŵ�
	{
		sides++;
	}
	else//��roll��Pitch��Ϊ�������ʱ��Բ��һ�������ŵ�
	{
		bottom++;
	}
}

int processing(double** ori, int times, double high) {
	int sides = 0, bottom = 0;
	for (int i = 0; i < times * times; i++)
	{
		Orientation(ori[i][0], ori[i][1], ori[i][2], ori[i][3], sides, bottom);
	}
	cout <<rr<< "�߶ȣ�" << high << ";�����ŵصĴ���Ϊ��" << sides << "�������ŵصĸ���Ϊ��" << (double)sides / times / times << ";���µ����ŵصĴ���Ϊ��" << bottom << "��\n";
	ofstream out("D:/LOCK/7_Three-Sided_Dice/���ν��.txt", ios::app);//��������
	out << "����ģ���ܴ�����" << times * times << "���߶ȣ�" << setw(3) << high << "�������ŵصĴ���Ϊ��" << sides << "�������ŵصĸ���Ϊ��" << (double)sides / times / times << "�����µ����ŵصĴ���Ϊ��" << bottom << "��\n";
	out.close();
	ofstream outtomatlab("D:/LOCK/7_Three-Sided_Dice/MATLAB/in.txt", ios::app);
	outtomatlab << times * times << " " << high << " " << (double)sides / times / times << endl;
	outtomatlab.close();
	ofstream csv("out.csv", ios::app);
	csv <<rr<<"," << sides << "," << bottom << endl;
	csv.close();
	return 0;
}