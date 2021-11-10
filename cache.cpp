#include <iostream>
#include <math.h>

using std::cout;
using std::endl;

template<int CACHE_LINES = 256, int LINE_SIZE = 16>
class d_cache {
public:
    d_cache();
    int read(const int& addr);
    void write (const int& addr, int data);
private:
    int storage[CACHE_LINES][LINE_SIZE];
    int tag[CACHE_LINES];
    int OFFSET_MASK;
    int IND_MASK;
    int OFFSET_BITS;
    int IND_BITS;
};

template<int CACHE_LINES, int LINE_SIZE>
d_cache<CACHE_LINES, LINE_SIZE>::d_cache() {
    OFFSET_BITS = log2(LINE_SIZE);
    IND_BITS = log2(CACHE_LINES);
    OFFSET_MASK = LINE_SIZE - 1;
    IND_MASK = CACHE_LINES - 1;
    for (int i = 0; i < CACHE_LINES; i++) {
        tag[i] = 0;
        for (int j = 0; j < LINE_SIZE; j++) {
            storage[i][j] = 0;
        }
    }
}

template<int CACHE_LINES, int LINE_SIZE>
void d_cache<CACHE_LINES, LINE_SIZE>::write(const int& addr, int data) {
    int write_offset = addr & OFFSET_BITS;
    int write_addr = addr >> OFFSET_BITS;
    int write_ind = write_addr & IND_BITS;
    int write_tag = write_addr >> IND_BITS;
    tag[write_ind] = write_tag;
    storage[write_ind][write_offset] = data;
}

template<int CACHE_LINES, int LINE_SIZE>
int d_cache<CACHE_LINES, LINE_SIZE>::read(const int& addr) {
    int check_offset = addr & OFFSET_BITS;
    int check_addr = addr >> OFFSET_BITS;
    int check_ind = check_addr & IND_BITS;
    int check_tag = check_addr >> IND_BITS;
    if (tag[check_ind] == check_tag)
        return storage[check_ind][check_offset];
    else
        return -1;
}

int main() {
    d_cache<256, 16> cache1;
    cout << cache1.read(1) << endl;
    cache1.write(12, 10);
    cout << cache1.read(12) << endl;
    return 0;
}