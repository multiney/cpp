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

/*
 * alignof(Info) == 2
 * sizeof(Info) == 6, 2(alignof(Info)) * 2
 * 若无alignof, 则看最大pod类型大小
 */
struct alignas(2) Info {
    uint8_t a;
    uint32_t b;
    uint8_t c;
} ONEBYTE_ALIGN;

/*
 * 0     5 6    a  c    10   1415  18    
 * +-----+-*----+--*----+----+-+---*
 * |     | |    |  |    |    | |   |
 * |  a  | |  b |  | c  |  d |e|   |
 * |     | |    |  |    |    | |   |
 * +-----+-*----+--*----+----+-+---*
 */
/*
 * alignof(Info2) == 8
 * sizeof(Info2) == 24, 8 + 8 + 8
 */
struct alignas(8) Info2 {
    char a[5];        // 0x00
    uint16_t b[2];    // 0x06
    uint32_t c;       // 0x0c
    uint32_t d;       // 0x10
    uint8_t e;        // 0x14
};                    // one past last: 0x18

/**
* 0 1   3     6   8 9            10               20
* +-+---+-----+---+-+-------------+---------------*
* | |   |     |   | |             |               |
* |a| b |  c  | d |e|     pad     |               |
* | |   |     |   | |             |               |
* +-+---+-----+---+-+-------------+---------------*
*/
/*
 * alignof(Info3) == 4
 * sizeof(Info3) == 4
 */
struct alignas(4) Info3 {
  uint16_t a : 1;
  uint16_t b : 2;
  uint16_t c : 3;
  uint16_t d : 2;
  uint16_t e : 1;
  uint32_t pad : 7;
} ONEBYTE_ALIGN;

#if defined(__GNUC__) || defined(__GNUG__)
  #undef ONEBYTE_ALIGN
#elif defined(_MSC_VER)
  #pragma pack(pop)
  #undef ONEBYTE_ALIGN
#endif

int main (int argc, char *argv[])
{
    cout << sizeof(Info) << endl;
    cout << alignof(Info) << endl;
    Info info;
    cout << static_cast<void*>(&info.a) << endl;
    cout << static_cast<void*>(&info.b) << endl;
    cout << static_cast<void*>(&info.c) << endl;

    cout << sizeof(Info2) << endl;
    cout << alignof(Info2) << endl;
    Info2 info2;
    cout << &info2 << endl;
    cout << static_cast<void*>(&info2.a[4]) << endl;
    cout << static_cast<void*>(info2.b) << endl;
    cout << static_cast<void*>(info2.b + 1) << endl;
    cout << static_cast<void*>(&info2.c) << endl;
    cout << static_cast<void*>(&info2.d) << endl;
    cout << static_cast<void*>(&info2.e) << endl;

    Info3 info3;
    cout << sizeof(info3) << endl;
    cout << alignof(Info3) << endl;
    return 0;
}
