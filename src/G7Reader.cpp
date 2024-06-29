#define _CRT_SECURE_NO_WARNINGS

#include "G7ContentTableEntry.h"
#include "G7Header.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static std::string get_asset_type_name(uint64_t assetType)
{
    switch (assetType)
    {
    case 2:
        return "texture3d";
    case 3:
        return "camera";
    case 4:
        return "anim";
    case 5:
        return "rig";
    case 6:
        return "material";
    case 7:
        return "material_list";
    case 8:
        return "info_date";
    case 9:
        return "unknown";
    case 15:
        return "data";
    case 16:
        return "alt_material";
    case 18:
        return "bitmap";
    case 20:
        return "model";
    case 21:
        return "alt_material2";
    case 22:
        return "cubemap";
    case 23:
        return "vectors";
    case 24:
        return "alt_material3";
    default:
        return "unknown";
    }
}

static void read_string(FILE *file, char *str, size_t size)
{
    fread(str, 1, size, file);
    str[size - 1] = '\0';
}

int read_file(const char *filepath, const std::string &outpath)
{
    FILE* input_file = fopen(filepath, "rb");
    if (input_file)
    {
        std::cerr << "Unable to open file " << filepath << std::endl;
        return 1;
    }

    G7Header header{};
    fread(&header.magic, 4, 1, input_file);
    fread(&header.unknown, 4, 1, input_file);
    fread(&header.table_count, 4, 1, input_file);

    printf("Magic: %u\n", header.magic);
    printf("Unknown: %u\n", header.unknown);
    printf("Table Count: %u\n", header.table_count);

    for (unsigned int i = 0; i < header.table_count; i++)
    {
        G7ContentTableEntry tableEntry{};
        read_string(input_file, tableEntry.name, 64);
        fread(&tableEntry.size, 8, 1, input_file);
        fread(&tableEntry.offset, 8, 1, input_file);
        fread(&tableEntry.flags, 8, 1, input_file);
        fread(&tableEntry.assetType, 8, 1, input_file);

        std::string entryName(tableEntry.name);
        std::cout << "Entry " << i + 1 << " Name: " << entryName << std::endl;
        long offset = ftell(input_file);

        fseek(input_file, tableEntry.offset, 0);
        std::vector<char> buffer(tableEntry.size);

        fread(buffer.data(), 1, tableEntry.size, input_file);
        fseek(input_file, offset, 0);

        std::string outputFilePath = outpath + "/" + tableEntry.name + "." + get_asset_type_name(tableEntry.assetType);
        std::ofstream outputFile(outputFilePath, std::ios::binary);
        if (outputFile.is_open()) 
        {
            outputFile.write(buffer.data(), buffer.size());
            outputFile.close();
        } 
        else 
        {
            std::cerr << "Unable to create G7 file output (does the directory exist?) " << outputFilePath << std::endl;
            return 1;
        }
    }

    fclose(input_file);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>"
                  << std::endl;
        return 1;
    }
    return read_file(argv[1], argv[2]);
}
