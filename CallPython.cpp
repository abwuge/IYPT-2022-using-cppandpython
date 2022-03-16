#include<iostream>
#include <Python.h>

using namespace std;

void CallPython(int times, double high, double**& ori) {
	Py_Initialize();  // 初始化python模块
	if (!Py_IsInitialized())  // 检查初始化是否成功  
	{
		cout << "初始化失败！" << endl;
		Py_Finalize();
	}
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");  // 设置python模块，搜寻位置，文件放在.cpp文件一起
	PyObject* pModule = PyImport_ImportModule("ToBeCalled");  // Python文件名     
	if (!pModule) {
		cout << "py文件导入失败！" << endl;
		Py_Finalize();
	}
	else {
		PyObject* pDict = PyModule_GetDict(pModule);
		if (!pDict) {
			cout << "内容获取失败！" << endl;
			Py_Finalize();
		}
		PyObject* pFunc = PyObject_GetAttrString(pModule, "sim");  // Python文件中的函数名  
		if (!pFunc) {
			cout << "函数导入失败！" << endl;
			Py_Finalize();
		}

		PyObject* result = PyObject_CallFunction(pFunc, "id", times, high);  // 调用函数
		for (int i = 0; i < times * times; i++)
		{
			ori[i] = new double[4];
			for (int j = 0; j < 4; j++)
			{
				ori[i][j] = PyFloat_AsDouble(PyTuple_GetItem(PyList_GetItem(result, i), j));
			}
		}
	}
	Py_Finalize();
}