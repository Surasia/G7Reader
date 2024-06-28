#pragma once

#include <stdint.h>

class G7Header
{
public:
    uint32_t magic;
    uint32_t unknown;
    uint32_t table_count;
};