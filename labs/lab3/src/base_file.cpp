#include "base_file.hpp"

#include <cstring>
#include <iostream>
using namespace std;
#include <iostream>

BaseFile::BaseFile()
    : f(nullptr), readable(false), writable(false), owns(false) {
    //cout << "BaseFile(): " << this << "\n";
}

BaseFile::BaseFile(const char *path, const char *mode)
    : f(nullptr), readable(false), writable(false), owns(true) {
    if (path && mode) {
        f = fopen(path, mode);
        readable = (strchr(mode, 'r') != nullptr) ||
                   (strchr(mode, '+') != nullptr);
        writable = (strchr(mode, 'w') != nullptr) ||
                   (strchr(mode, 'a') != nullptr) ||
                   (strchr(mode, '+') != nullptr);
    }
    //cout << "BaseFile(path, mode): " << this << "\n";
}

BaseFile::BaseFile(FILE *file, bool can_r, bool can_w)
    : f(file), readable(can_r), writable(can_w), owns(false) {
    //cout << "BaseFile(FILE*): " << this << "\n";
}

BaseFile::~BaseFile() {
    //cout << "~BaseFile(): " << this << "\n";
    close();
}
BaseFile::BaseFile(BaseFile &&other) noexcept
    : f(other.f), readable(other.readable), writable(other.writable), owns(other.owns) {
    other.f = nullptr;
    other.readable = false;
    other.writable = false;
    other.owns = false;
}

BaseFile& BaseFile::operator=(BaseFile &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    close();

    f = other.f;
    readable = other.readable;
    writable = other.writable;
    owns = other.owns;

    other.f = nullptr;
    other.readable = false;
    other.writable = false;
    other.owns = false;
    return *this;
}

bool BaseFile::is_open() const { return f != nullptr; }

bool BaseFile::can_read() const { return f != nullptr && readable; }

bool BaseFile::can_write() const { return f != nullptr && writable; }

void BaseFile::close() {
    if (f != nullptr && owns) {
        fclose(f);
    }
    f = nullptr;
    readable = false;
    writable = false;
}

size_t BaseFile::write_raw(const void *buf, size_t n_bytes) {
    if (!can_write() || buf == nullptr) {
        return 0;
    }
    return fwrite(buf, 1, n_bytes, f);
}

size_t BaseFile::read_raw(void *buf, size_t max_bytes) {
    if (!can_read() || buf == nullptr) {
        return 0;
    }
    return fread(buf, 1, max_bytes, f);
}

long BaseFile::tell() const {
    return f != nullptr ? ftell(f) : -1L;
}

bool BaseFile::seek(long offset) {
    return f != nullptr && fseek(f, offset, SEEK_SET) == 0;
}

size_t BaseFile::write(const void *buf, size_t n_bytes) {
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void *buf, size_t max_bytes) {
    return read_raw(buf, max_bytes);
}