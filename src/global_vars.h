#include <mutex>
#ifndef GLOBAL_VARS
#define GLOBAL_VARS

// Declare the global variable as extern
extern int totalCount; 
extern std::mutex count_mutex;
#endif