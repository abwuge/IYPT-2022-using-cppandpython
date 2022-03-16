#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "Processing.h"

const double PI = 3.14159265358979323846;//PI为圆周率(3.14159265358979323846)

using namespace std;

void toEulerAngle(double x, double y, double z, double w, double& roll, double& pitch, double& yaw)//输入四元数x、y、z、w，输出欧拉角roll、pitvh、yaw
{
	// x偏转角
	double sinr_cosp = +2.0 * (w * x + y * z);
	double cosr_cosp = +1.0 - 2.0 * (x * x + y * y);
	roll = atan2(sinr_cosp, cosr_cosp);

	// y偏转角
	double sinp = +2.0 * (w * y - z * x);
	if (fabs(sinp) >= 1)//如果sin p的绝对值大于1，就将arcsin（sin p）设置为pi/2
		pitch = copysign(PI / 2, sinp);
	else
		pitch = asin(sinp);

	// z偏转角
	double siny_cosp = +2.0 * (w * z + x * y);
	double cosy_cosp = +1.0 - 2.0 * (y * y + z * z);
	yaw = atan2(siny_cosp, cosy_cosp);
}

void Orientation(double& x, double& y, double& z, double& w, int& sides, int& bottom)
{
	double roll, pitch, yaw;//三个欧拉角数据
	toEulerAngle(x, y, z, w, roll, pitch, yaw);//将四元数转为欧拉角
	if (fabs(roll) > 0.35 * PI && fabs(roll) < 0.65 * PI)//当roll的绝对值为1/2PI时，圆柱一定侧面着地
	{
		sides++;
	}
	else if (fabs(pitch) > 0.35 * PI && fabs(pitch) < 0.65 * PI)//当roll为其余情况，但pitch的绝对值为PI/2时，圆柱也一定侧面着地
	{
		sides++;
	}
	else//当roll和Pitch均为其余情况时，圆柱一定底面着地
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
	cout <<rr<< "高度：" << high << ";侧面着地的次数为：" << sides << "；侧面着地的概率为：" << (double)sides / times / times << ";上下底面着地的次数为：" << bottom << "；\n";
	ofstream out("D:/LOCK/7_Three-Sided_Dice/历次结果.txt", ios::app);//将结果输出
	out << "本次模拟总次数：" << times * times << "；高度：" << setw(3) << high << "；侧面着地的次数为：" << sides << "；侧面着地的概率为：" << (double)sides / times / times << "；上下底面着地的次数为：" << bottom << "；\n";
	out.close();
	ofstream outtomatlab("D:/LOCK/7_Three-Sided_Dice/MATLAB/in.txt", ios::app);
	outtomatlab << times * times << " " << high << " " << (double)sides / times / times << endl;
	outtomatlab.close();
	ofstream csv("out.csv", ios::app);
	csv <<rr<<"," << sides << "," << bottom << endl;
	csv.close();
	return 0;
}