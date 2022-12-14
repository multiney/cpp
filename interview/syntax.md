## 2. 结构体内存

对于空的struct，c++中大小为1， C中大小为0.

- 结构体内成员按照声明顺序存储，第一个成员地址和整个结构体地址相同。
- 未特殊说明时，按结构体中size最大的成员对齐（若有double成员，按8字节对齐。）
- struct大小必须是内部最大pod类型的大小的整数倍

### 成员起始位置

为特殊说明时,成员的位置偏移（该成员放置位置对于struct的起始位置）必须是该成员内部中最大pod类型的大小的整数倍。

成员内部最大pod类型可分以下情况：
1. 基本的pod类型（int,char,double,...) ，那么其内部最大pod类型大小自然是其本身成员的大小。
2. struct类型，其内部最大pod类型为struct内部的各个成员的内部最大pod类型中最大的那个（存在递归）。
3. 数组，每个数组成员之间无空隙排列的，没有填充字节。内部最大pod类型的大小为数组成员内部的最大pod类型大小（存在递归）。

```cpp
// 求内部最大的成员大小
function maxInnerUnitSize(data)
    if data 是 pod类型：
         return sizeof(pod类型)
    else if data 是 struct 类型:
        return max(map(data.members, maxInnerUnitSize))
    else if data  是 数组类型:
       return maxInnerUnitSize(data[0])
end
```

```cpp
// 成员大小计算
function dataSize(data)
    if data 是 pod类型：
         return sizeof(pod类型)
    else if data 是 struct 类型:
        return struct 的大小
    else if data  是 数组类型:
       return 数组长度 * sizeof(data[0])
end
```

c++11引入`alignas`与`alignof`,alignof可以计算出类型的对齐方式，alignas可以指定结构体的对齐方式。

alignas在以下情况失效：
1. 若alignas小于自然对齐的最小单位，则被忽略；
2. 使用`#pragma pack(push,n)`或`__attribute__((packed))`时，alignas定义对齐方式失效，但是alignof等于alignas，且struct大小是alignas整数倍。
3. 确定每个元素大小用`: n`。alignas效果同2

### pragma pack(n) 的影响

pack 的参数n，有1，2，4，8，16， 原则是 2 的次幂。

```cpp
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
```
