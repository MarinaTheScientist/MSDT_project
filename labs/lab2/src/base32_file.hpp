#pragma once

#include "base_file.hpp"

class Base32File : public BaseFile {
    char *codetable;
    unsigned long long write_bits;
    int write_bit_count;
    unsigned long long read_bits;

    int read_bit_count;

    void set_table(const char *table);
    int table_index(char c) const;

public:
    Base32File();
    Base32File(const char *path, const char *mode, const char *table = nullptr);
    Base32File(FILE *file, bool can_r = true, bool can_w = true,
               const char *table = nullptr);

    ~Base32File();

    void flush();

    void close();
    bool seek(long offset);

    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t max_bytes);
};