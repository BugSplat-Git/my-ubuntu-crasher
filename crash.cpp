#include <cstddef>

extern "C" {
    // Function that will cause a crash
    __attribute__((visibility("default")))
    void crash() {
        // Dereference null pointer to cause a crash
        *(volatile int*)nullptr = 42;
    }
} 