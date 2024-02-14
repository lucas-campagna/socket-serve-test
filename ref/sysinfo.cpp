#include <iostream>
#include <unistd.h>

int main() {
    // Get the number of processors (sockets)
    long numProcessors = sysconf(_SC_NPROCESSORS_CONF);
    std::cout << "Number of Processors (Sockets): " << numProcessors << std::endl;

    // Get the number of cores per processor
    long numCores = sysconf(_SC_NPROCESSORS_ONLN);
    std::cout << "Number of Cores per Processor: " << numCores << std::endl;

    // Get the number of threads per core (if supported)
    long numThreads = sysconf(_SC_NPROCESSORS_ONLN );
    if (numThreads > 0) {
        std::cout << "Number of Threads per Core: " << numThreads << std::endl;
    } else {
        std::cout << "Number of Threads per Core information not available." << std::endl;
    }

    return 0;
}