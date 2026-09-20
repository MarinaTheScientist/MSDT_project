#include "base32_file2.hpp"

#include <cstring>

static const char DEFAULT_TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";

void Base32File2::set_table(const char *table) {
    const char *src = (table != nullptr && strlen(table) == 32)
                      ? table : DEFAULT_TABLE;
    codetable = new char[33];
    strcpy(codetable, src);
}

int Base32File2::table_index(char c) const {
    for (int i = 0; i < 32; ++i) {
        if (codetable[i] == c) {
            return i;
        }
    }
    return -1;
}

Base32File2::Base32File2(IFile *file, const char *table)
    : inner(file), codetable(nullptr),
      write_bits(0), write_bit_count(0),
      read_bits(0), read_bit_count(0) {
    set_table(table);
}

Base32File2::~Base32File2() {
    flush();
    delete[] codetable;
    delete inner;
}

bool Base32File2::can_read() const {
    return inner != nullptr && inner->can_read();
}

bool Base32File2::can_write() const {
    return inner != nullptr && inner->can_write();
}

void Base32File2::flush() {
    if (write_bit_count <= 0) {
        return;
    }
    if (can_write()) {
        unsigned long long padded = write_bits << (5 - write_bit_count);
        char encoded = codetable[padded & 31];
        inner->write(&encoded, 1);
    }
    write_bits = 0;
    write_bit_count = 0;
}

size_t Base32File2::write(const void *buf, size_t n_bytes) {
    if (!can_write() || buf == nullptr) {
        return 0;
    }
    const unsigned char *p = (const unsigned char *)buf;

    for (size_t i = 0; i < n_bytes; ++i) {
        write_bits = (write_bits << 8) | p[i];
        write_bit_count += 8;

        while (write_bit_count >= 5) {
            int idx = (int)((write_bits >> (write_bit_count - 5)) & 31);
            char c = codetable[idx];
            if (inner->write(&c, 1) != 1) {
                return i;
            }
            write_bit_count -= 5;
        }
    }
    return n_bytes;
}

size_t Base32File2::read(void *buf, size_t max_bytes) {
    if (!can_read() || buf == nullptr) {
        return 0;
    }
    unsigned char *out = (unsigned char *)buf;
    size_t done = 0;

    while (done < max_bytes) {
        while (read_bit_count < 8) {
            char c;
            if (inner->read(&c, 1) != 1) {
                return done;
            }
            int val = table_index(c);
            if (val < 0) {
                continue;
            }
            read_bits = (read_bits << 5) | (unsigned)val;
            read_bit_count += 5;
        }
        out[done] = (unsigned char)((read_bits >> (read_bit_count - 8)) & 255);
        read_bit_count -= 8;
        ++done;
    }
    return done;
}