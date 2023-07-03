#include <QCoreApplication>
#include <Python.h>
#include <iostream>
#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo()<<"Begin---------------\n";
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        qInfo()<<"Cant initialized!";
        return -1;
    }
    PyObject* Module=PyImport_ImportModule("temp");
    if (!Module){
        qInfo()<<"Cant open python file!";
        return -1;
    }
    PyObject* pFunc=PyObject_GetAttrString(Module,"hello");
    if (!pFunc){
        qInfo()<<"Cant load the function!";
        return -1;
    }
    PyObject_CallFunction(pFunc,NULL);
    Py_Finalize();
    qInfo()<<"Finished-------------\n";
    return a.exec();
}
