#include "base32_file.hpp"

#include <cstring>
#include <iostream>
using namespace std;
#include <iostream>

static const char DEFAULT_TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";

void Base32File::set_table(const char *table) {
    const char *src = (table != nullptr && strlen(table) == 32)
                      ? table : DEFAULT_TABLE;
    codetable = new char[33];
    strcpy(codetable, src);
}

int Base32File::table_index(char c) const {
    for (int i = 0; i < 32; ++i) {
        if (codetable[i] == c) {
            return i;
        }
    }
    return -1;
}

Base32File::Base32File()
    : BaseFile(),
      codetable(nullptr), write_bits(0), write_bit_count(0),
      read_bits(0), read_bit_count(0) {
    //cout << "Base32File(): " << this << "\n";
    set_table(nullptr);
}

Base32File::Base32File(const char *path, const char *mode, const char *table)
    : BaseFile(path, mode),
      codetable(nullptr), write_bits(0), write_bit_count(0),
      read_bits(0), read_bit_count(0) {
    //cout << "Base32File(path, mode): " << this << "\n";
    set_table(table);
}

Base32File::Base32File(FILE *file, bool can_r, bool can_w, const char *table)
    : BaseFile(file, can_r, can_w),
      codetable(nullptr), write_bits(0), write_bit_count(0),
      read_bits(0), read_bit_count(0) {
    //cout << "Base32File(FILE*): " << this << "\n";
    set_table(table);
}

Base32File::~Base32File() {
    //cout << "~Base32File(): " << this << "\n";
    flush();
    delete[] codetable;
    codetable = nullptr;
}

void Base32File::flush() {
    if (write_bit_count <= 0) {
        return;
    }
    if (can_write() && codetable != nullptr) {
        unsigned long long padded = write_bits << (5 - write_bit_count);
        char encoded = codetable[padded & 31];
        write_raw(&encoded, 1);
    }
    write_bits = 0;
    write_bit_count = 0;
}

size_t Base32File::write(const void *buf, size_t n_bytes) {
    if (!can_write() || buf == nullptr) {
        return 0;
    }
    const unsigned char *ptr_buf = (const unsigned char *)buf;

    for (size_t i = 0; i < n_bytes; ++i) {
        write_bits = (write_bits << 8) | ptr_buf[i];
        write_bit_count += 8;

        while (write_bit_count >= 5) {
            int idx = (int)((write_bits >> (write_bit_count - 5)) & 31);
            char c = codetable[idx];
            if (write_raw(&c, 1) != 1) {
                return i;
            }
            write_bit_count -= 5;
        }
    }
    return n_bytes;
}

size_t Base32File::read(void *buf, size_t max_bytes) {
    if (!can_read() || buf == nullptr) {
        return 0;
    }
    unsigned char *ptr_buf = (unsigned char *)buf;
    size_t read_bytes = 0;

    while (read_bytes < max_bytes) {
        while (read_bit_count < 8) {
            char c;
            if (read_raw(&c, 1) != 1) {
                return read_bytes;
            }
            int val = table_index(c);
            if (val < 0) {
                continue;
            }
            read_bits = (read_bits << 5) | (unsigned)val;
            read_bit_count += 5;
        }
        ptr_buf[read_bytes] =
            (unsigned char)((read_bits >> (read_bit_count - 8)) & 255);
        read_bit_count -= 8;
        ++read_bytes;
    }
    return read_bytes;
}

void Base32File::close() {
    flush();
    BaseFile::close();
    read_bits = 0;
    read_bit_count = 0;
}

bool Base32File::seek(long offset) {
    flush();
    read_bits = 0;
    read_bit_count = 0;
    return BaseFile::seek(offset);
}