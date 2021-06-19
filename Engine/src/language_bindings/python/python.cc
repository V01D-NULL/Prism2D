#include "python.h"
#include "../../OS/os.h"
#include <string>
#include <iostream>

namespace lang
{
    Python::Python()
    {
        // Py_Initialize();
    }

    void Python::ExecString(const char *code)
    {
        PyRun_SimpleString(code);
    }

    /* Call pythons function Enter. Runs once before the first frame is executed */
    void Python::DefEnter(const char *file)
    {
        if ( OS::FileSystem().python_script_has_extension(file))
        {
            throw("File passed to engine must not contain a .py extension");
        }

        if (!OS::FileSystem().python_script_exists(file))
        {
            throw("File does not exist");
        }
        
        //This will add the current path to the sys.path in python (sys.path.append("<executable_path>"))
        std::string path = "sys.path.append(os.getcwd())";

        PyRun_SimpleString("import sys, os");
        PyRun_SimpleString(path.c_str());
        
        PyObject *pyName, *pyModule, *pyFunc, *pyValue;
        pyName = PyUnicode_FromString(file);
        pyModule = PyImport_Import(pyName);
        pyFunc = PyObject_GetAttrString(pyModule, "Enter");
        pyValue = PyObject_CallObject(pyFunc, NULL);
    }

    /* Call pythons function Update. Runs once every frame */
    void Python::DefUpdate(const char *file)
    {
        if ( OS::FileSystem().python_script_has_extension(file))
        {
            throw("File passed to engine must not contain a .py extension");
        }

        if (!OS::FileSystem().python_script_exists(file))
        {
            throw("File does not exist");
        }

        //This will add the current path to the sys.path in python (sys.path.append("<executable_path>"))
        std::string path = "sys.path.append(os.getcwd())";

        PyRun_SimpleString("import sys, os");
        PyRun_SimpleString(path.c_str());
        
        PyObject *pyName, *pyModule, *pyFunc, *pyValue;
        pyName = PyUnicode_FromString(file);
        pyModule = PyImport_Import(pyName);
        pyFunc = PyObject_GetAttrString(pyModule, "Update");
        pyValue = PyObject_CallObject(pyFunc, NULL);
    }

    /* Call pythons function LateUpdate. Runs once per frame */
    void Python::DefLateUpdate(const char *file)
    {
        if ( OS::FileSystem().python_script_has_extension(file))
        {
            throw("File passed to engine must not contain a .py extension");
        }

        if (!OS::FileSystem().python_script_exists(file))
        {
            throw("File does not exist");
        }
        
        //This will add the current path to the sys.path in python (sys.path.append("<executable_path>"))
        std::string path = "sys.path.append(os.getcwd())";

        PyRun_SimpleString("import sys, os");
        PyRun_SimpleString(path.c_str());
        
        PyObject *pyName, *pyModule, *pyFunc, *pyValue;
        pyName = PyUnicode_FromString(file);
        pyModule = PyImport_Import(pyName);
        pyFunc = PyObject_GetAttrString(pyModule, "LateUpdate");
        pyValue = PyObject_CallObject(pyFunc, NULL);
    }

    /* Call pythons function RenderCycle. Runs once per frame */
    void Python::DefRenderCycle(const char *file)
    {
        if ( OS::FileSystem().python_script_has_extension(file))
        {
            throw("File passed to engine must not contain a .py extension");
        }

        if (!OS::FileSystem().python_script_exists(file))
        {
            throw("File does not exist");
        }
        
        //This will add the current path to the sys.path in python (sys.path.append("<executable_path>"))
        std::string path = "sys.path.append(os.getcwd())";

        PyRun_SimpleString("import sys, os");
        PyRun_SimpleString(path.c_str());
        
        PyObject *pyName, *pyModule, *pyFunc, *pyValue;
        pyName = PyUnicode_FromString(file);
        pyModule = PyImport_Import(pyName);
        pyFunc = PyObject_GetAttrString(pyModule, "RenderCycle");
        pyValue = PyObject_CallObject(pyFunc, NULL);
    }

    Python::~Python()
    {
        // Py_Finalize();
    }
}