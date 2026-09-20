#include "rle_file2.hpp"

static const unsigned MAX_RUN = 255;

RleFile2::RleFile2(IFile *file)
    : inner(file), run_byte(0), run_count(0), pend_byte(0), pend_count(0) {}
RleFile2::~RleFile2() {
    flush();
    delete inner;
}

bool RleFile2::can_read() const {
    return inner != nullptr && inner->can_read();
}

bool RleFile2::can_write() const {
    return inner != nullptr && inner->can_write();
}

bool RleFile2::flush_run() {
    if (run_count == 0) {
        return true;
    }
    unsigned char pair[2] = { (unsigned char)run_count, run_byte };
    bool ok = inner->write(pair, 2) == 2;
    run_count = 0;
    return ok;
}

void RleFile2::flush() {
    if (can_write()) {
        flush_run();
    }
    run_count = 0;
}

size_t RleFile2::write(const void *buf, size_t n_bytes) {
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

size_t RleFile2::read(void *buf, size_t max_bytes) {
    if (!can_read() || buf == nullptr) {
        return 0;
    }
    unsigned char *out = (unsigned char *)buf;
    size_t done = 0;

    while (done < max_bytes) {
        if (pend_count == 0) {
            unsigned char pair[2];
            if (inner->read(pair, 2) != 2) {
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