#ifdef __APPLE__
#include "OpenCL/opencl.h"
#else
#ifdef _WIN32
#include "CL/cl.h"
#else
#include "cl.h"
#endif
#endif