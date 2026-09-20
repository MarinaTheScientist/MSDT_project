#pragma once

#include "ifile.hpp"

class RleFile2 : public IFile {
    IFile *inner;

    unsigned char run_byte;
    unsigned run_count;

    unsigned char pend_byte;
    unsigned pend_count;

    bool flush_run();

public:
    explicit RleFile2(IFile *file);

    RleFile2(const RleFile2 &) = delete;
    RleFile2 &operator=(const RleFile2 &) = delete;

    ~RleFile2() override;

    bool can_read() const override;
    bool can_write() const override;

    size_t write(const void *buf, size_t n_bytes) override;
    size_t read(void *buf, size_t max_bytes) override;

    void flush();
};