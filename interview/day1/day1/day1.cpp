#include <stdint.h>

#include <iostream>

using std::cout;
using std::endl;

#if defined(__GNUC__) || defined(__GNUC__)
    #define ONEBYTE_ALIGN __attribute__((packed))
#elif defined(_MSC_VER)
    #define ONEBYTE_ALIGN
    #pragma pack(push,1)
#endif

struct alignas(4) Info {
    uint8_t a;
    uint32_t b;
    uint8_t c;
} ONEBYTE_ALIGN;

struct alignas(4) Info2 {
    char a[5];
    uint32_t b;
    uint8_t c;
};

/**
* 0 1   3     6   8 9            16
* +-+---+-----+---+-+-------------+
* | |   |     |   | |             |
* |a| b |  c  | d |e|     pad     |
* | |   |     |   | |             |
* +-+---+-----+---+-+-------------+
*/
struct Info3 {
  uint16_t a : 1;
  uint16_t b : 2;
  uint16_t c : 3;
  uint16_t d : 2;
  uint16_t e : 1;
  uint32_t pad : 20;
} ONEBYTE_ALIGN;

#if defined(__GNUC__) || defined(__GNUG__)
  #undef ONEBYTE_ALIGN
#elif defined(_MSC_VER)
  #pragma pack(pop)
  #undef ONEBYTE_ALIGN
#endif

int main (int argc, char *argv[])
{
    cout << sizeof(Info) << endl; // 12 4 + 4 + 4
    cout << alignof(Info) << endl; // 4
    Info info;
    cout << static_cast<void*>(&info.a) << endl;
    cout << static_cast<void*>(&info.b) << endl;
    cout << static_cast<void*>(&info.c) << endl;

    Info2 info2;
    cout << &info2 << endl;
    cout << static_cast<void*>(&info2.a[4]) << endl;
    cout << static_cast<void*>(&info2.b) << endl;
    cout << static_cast<void*>(&info2.c) << endl;

    Info3 info3;
    info3.a = 1;
    info3.b = 1;
    cout << info3.a << endl;
    cout << sizeof(info3) << endl;
    cout << alignof(Info3) << endl;
    return 0;
}
