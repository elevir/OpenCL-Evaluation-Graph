#pragma once

#ifndef OPENCL_EVAL_G_API
#  ifdef WIN32
#    ifdef OpenCLGraphExport
#      define OPENCL_EVAL_G_API __declspec(dllexport)
#    else
#      define OPENCL_EVAL_G_API __declspec(dllimport)
#    endif
#  else
#    define OPENCL_EVAL_G_API
#  endif // WIN32
#endif // !OPENCV_EVAL_G_API

namespace cl_graph {

class Data;
class DataImpl;
class Device;
class DeviceImpl;
class INode;
class Node;

}