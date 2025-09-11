#pragma once


#ifdef LOG_ENABLE
#include <cstdio>
#define LOG(fmt, ...) printf("[LOG] %s" fmt "\n",  __func__, ##__VA_ARGS__)
#define LOG_INTERVAL(var, total, interval) do { \
	if ((var) % (interval) == 0) \
		printf("[LOG] %s: var=%zu, total=%zu, interval=%d\n", __func__, (size_t)(var), (size_t)(total), (int)(interval)); \
} while(0)
#else
#define LOG(fmt, ...)
#define LOG_INTERVAL(var, total)
#endif
