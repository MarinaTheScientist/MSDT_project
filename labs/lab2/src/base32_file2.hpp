#pragma once

#include "ifile.hpp"

class Base32File2 : public IFile {
    IFile *inner;
    char *codetable;

    unsigned long long write_bits;
    int write_bit_count;
    unsigned long long read_bits;
    int read_bit_count;

    void set_table(const char *table);
    int table_index(char c) const;

public:
    explicit Base32File2(IFile *file, const char *table = nullptr);

    Base32File2(const Base32File2 &) = delete;
    Base32File2 &operator=(const Base32File2 &) = delete;

    ~Base32File2() override;

    bool can_read() const override;
    bool can_write() const override;

    size_t write(const void *buf, size_t n_bytes) override;
    size_t read(void *buf, size_t max_bytes) override;

    void flush();
};