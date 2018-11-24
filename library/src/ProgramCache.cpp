//
// Created by pav on 24/11/2018.
//

#include "ProgramCache.h"

namespace cl_graph {

cl_kernel ProgramCache::get_kernel(const cl_graph::Device & device, const char * program) {
    std::lock_guard<std::mutex> lock(m_mutex);
    const auto it = m_cache.find(device.get_id());
    if (it == m_cache.end()) {
        // TODO: compile etc
    }
    cl_kernel kernel;
    // TODO: make kernel
    return kernel;
}

}