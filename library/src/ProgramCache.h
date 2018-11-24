#pragma once

#include <map>
#include <mutex>
#include "Device.h"
#include "helpers/opencl.h"

namespace cl_graph {

class ProgramCache {
public:
    cl_kernel get_kernel(const Device & device, const char * program);
    // TODO: implement dump binaries on disk void dump_binaries_on_disk(const char * path);

private:
    std::mutex m_mutex;
    std::map<size_t, cl_program> m_cache;
};

}