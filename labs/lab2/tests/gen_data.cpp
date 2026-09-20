/** Генератор случайных данных для тестов: 50 Кб всех значений байта. */
#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
    srand((unsigned)time(nullptr));
    FILE *f = fopen("tests/data.bin", "wb");
    if (f == nullptr) {
        return 1;
    }
    for (int i = 0; i < 50 * 1024; ++i) {
        fputc(rand() % 256, f);
    }
    fclose(f);
    return 0;
}
