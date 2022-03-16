#include <iostream>
#include "main.h"
#include "CallPython.h"
#include "ResetXml.h"
#include "Processing.h"

using namespace std;

int main()
{
	char c;
	cin >> c;
	if (c == '0')
	{
		int times;
		times = 50;
		double** ori = new double* [times * times];
		double high = 1;
			CallPython(times, high, ori);
			processing(ori, times, high);
		return 0;
	}
	else if (c == '1')
	{
		int times;
		times = 50;
		double** ori = new double* [times * times];
		double high = 1;
		double height = 0.2, radius = 0.214, mass = 1;
		for (; radius <= 0.23; radius += 0.0003)
		{
			rr = radius;
			Cylinder* a = new Cylinder(height, radius, mass);
			update("D:/LOCK/7_Three-Sided_Dice/Cylinder.urdf", a);
			delete a;
			CallPython(times, high, ori);
			processing(ori, times, high);
		}
		return 0;
	}
	else if (c == '2')
	{
		cout << "依次输入高、半径、质量：";
		double height, radius, mass;
		cin >> height >> radius >> mass;
		Cylinder a(height, radius, mass);
		update("D:/LOCK/7_Three-Sided_Dice/Cylinder.urdf", &a);
		cout << "创建完成！";
		return 0;
	}
}