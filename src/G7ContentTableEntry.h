#pragma once

#include <stdint.h>
#include <string>
#include <cstdio>

class G7ContentTableEntry
{
public:
    char name[64];
    uint64_t size;
    uint64_t offset;
    uint64_t flags;
    uint64_t assetType;
};