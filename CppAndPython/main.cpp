#include <iostream>
#include "main.h"
#include "CallPython.h"
#include "ResetXml.h"

using namespace std;

int main()
{
	int times;
	times = 2;
	double** ori = new double* [times*times];
	CallPython(times, 0.5, ori);
	cout << "依次输入高、半径、质量：";
	float height, radius, mass;
	cin >> height >> radius >> mass;
	Cylinder a(height, radius, mass);
	update("D:/LOCK/7_Three-Sided_Dice/Cylinder.urdf", &a);
	cout << "创建完成！";
	return 0;
}