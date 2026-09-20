#include "../src/rle_file.hpp"
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

#define SIZE_BUF 256
#define DATA_SIZE (50 * 1024)

char src[DATA_SIZE] = {};
char dst[DATA_SIZE] = {};

int main() {
    const char *data      = "tests/data.bin";
    const char *test_file = "tests/tmp_rle_file.bin";

    // --- 1. читаем большой массив исходных данных ---
    {
        BaseFile f(data, "rb");
        assert(f.is_open());
        size_t got = 0, n;
        while (got < DATA_SIZE && (n = f.read_raw(src + got, SIZE_BUF)) > 0) {
            got += n;
        }
        assert(got == DATA_SIZE);
    }

    // --- 2. пишем во временный файл буферами по 256 байт ---
    {
        RleFile f(test_file, "wb");
        assert(f.can_write());
        size_t written = 0;
        while (written < DATA_SIZE) {
            size_t want = DATA_SIZE - written;
            if (want > SIZE_BUF) {
                want = SIZE_BUF;
            }
            size_t n = f.write(src + written, want);
            assert(n == want);
            written += n;
        }
    }   // деструктор дописывает хвост и закрывает файл

    // --- 3. читаем обратно буферами по 256 байт ---
    size_t got = 0;
    {
        RleFile f(test_file, "rb");
        assert(f.can_read());
        size_t n;
        while (got < DATA_SIZE && (n = f.read(dst + got, SIZE_BUF)) > 0) {
            got += n;
        }
    }

    // --- 4. сравниваем побайтово ---
    assert(got == DATA_SIZE);
    int res = memcmp(src, dst, DATA_SIZE);
    cout << "RleFile: прочитано " << got << " байт, memcmp = " << res << "\n";
    assert(res == 0);
    cout << "RleFile: PASS\n";
    return 0;
}
