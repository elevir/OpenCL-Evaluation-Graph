#pragma once

#ifdef WIN32

#ifndef OPENCL_EVAL_G_API

#ifdef DllExport
#define OPENCL_EVAL_G_API __declspec(dllexport) 
#else
#define OPENCL_EVAL_G_API __declspec(dllimport) 
#endif

#endif // !OPENCL_EVAL_G_API

#else

#define OPENCL_EVAL_G_API

#endif // WIN32


