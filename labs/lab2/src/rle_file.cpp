#include "rle_file.hpp"

#include <iostream>
using namespace std;

static const unsigned MAX_RUN = 255;


RleFile::RleFile()
    : BaseFile(),
      run_byte(0), run_count(0), pend_byte(0), pend_count(0) {
    //cout << "RleFile(): " << this << "\n";
}

RleFile::RleFile(const char *path, const char *mode)
    : BaseFile(path, mode),
      run_byte(0), run_count(0), pend_byte(0), pend_count(0) {
    //cout << "RleFile(path, mode): " << this << "\n";
}

RleFile::RleFile(FILE *file, bool can_r, bool can_w)
    : BaseFile(file, can_r, can_w),
      run_byte(0), run_count(0), pend_byte(0), pend_count(0) {
    //cout << "RleFile(FILE*): " << this << "\n";
}

RleFile::~RleFile() {
//    cout << "~RleFile(): " << this << "\n";
    flush();
}

bool RleFile::flush_run() {
    if (run_count == 0) {
        return true;
    }
    unsigned char pair[2] = { (unsigned char)run_count, run_byte };
    bool ok = write_raw(pair, 2) == 2;
    run_count = 0;
    return ok;
}

void RleFile::flush() {
    if (can_write()) {
        flush_run();
    }
    run_count = 0;
}

size_t RleFile::write(const void *buf, size_t n_bytes) {
    if (!can_write() || buf == nullptr) {
        return 0;
    }
    const unsigned char *p = (const unsigned char *)buf;

    for (size_t i = 0; i < n_bytes; ++i) {
        if (run_count > 0 && p[i] == run_byte && run_count < MAX_RUN) {
            ++run_count;
            continue;
        }
        if (!flush_run()) {
            return i;
        }
        run_byte = p[i];
        run_count = 1;
    }
    return n_bytes;
}

size_t RleFile::read(void *buf, size_t max_bytes) {
    if (!can_read() || buf == nullptr) {
        return 0;
    }
    unsigned char *out = (unsigned char *)buf;
    size_t done = 0;

    while (done < max_bytes) {
        if (pend_count == 0) {
            unsigned char pair[2];
            if (read_raw(pair, 2) != 2) {
                break;
            }
            if (pair[0] == 0) {
                break;
            }
            pend_count = pair[0];
            pend_byte = pair[1];
        }
        out[done] = pend_byte;
        --pend_count;
        ++done;
    }
    return done;
}


void RleFile::close() {
    flush();
    BaseFile::close();
    pend_count = 0;
}

bool RleFile::seek(long offset) {
    flush();
    pend_count = 0;
    return BaseFile::seek(offset);
}