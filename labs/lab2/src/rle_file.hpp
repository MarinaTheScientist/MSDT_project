#pragma once

#include "base_file.hpp"

class RleFile : public BaseFile {
    unsigned char run_byte;
    unsigned run_count;

    unsigned char pend_byte;
    unsigned pend_count;

    bool flush_run();

public:
    RleFile();
    RleFile(const char *path, const char *mode);
    RleFile(FILE *file, bool can_r = true, bool can_w = true);

    RleFile(const RleFile &) = delete;
    RleFile &operator=(const RleFile &) = delete;

    ~RleFile();

    void flush();

    void close();
    bool seek(long offset);

    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t max_bytes);
};