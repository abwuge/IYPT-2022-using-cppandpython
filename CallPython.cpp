#include<iostream>
#include <Python.h>

using namespace std;

void CallPython(int times, double high, double**& ori) {
	Py_Initialize();  // ��ʼ��pythonģ��
	if (!Py_IsInitialized())  // ����ʼ���Ƿ�ɹ�  
	{
		cout << "��ʼ��ʧ�ܣ�" << endl;
		Py_Finalize();
	}
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");  // ����pythonģ�飬��Ѱλ�ã��ļ�����.cpp�ļ�һ��
	PyObject* pModule = PyImport_ImportModule("ToBeCalled");  // Python�ļ���     
	if (!pModule) {
		cout << "py�ļ�����ʧ�ܣ�" << endl;
		Py_Finalize();
	}
	else {
		PyObject* pDict = PyModule_GetDict(pModule);
		if (!pDict) {
			cout << "���ݻ�ȡʧ�ܣ�" << endl;
			Py_Finalize();
		}
		PyObject* pFunc = PyObject_GetAttrString(pModule, "sim");  // Python�ļ��еĺ�����  
		if (!pFunc) {
			cout << "��������ʧ�ܣ�" << endl;
			Py_Finalize();
		}

		PyObject* result = PyObject_CallFunction(pFunc, "id", times, high);  // ���ú���
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