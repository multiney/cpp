## 2. 结构体内存

对于空的struct，c++中大小为1， C中大小为0.

- 结构体内成员按照声明顺序存储，第一个成员地址和整个结构体地址相同。
- 未特殊说明时，按结构体中size最大的成员对齐（若有double成员，按8字节对齐。）

### 成员起始位置

除初始成员外，所有成员的位置偏移（对于struct的起始位置）必须是所有成员内部中最大pod类型的大小的整数倍。

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
2. 使用`#pragma pack(push,n)`或`__attribute__((packed))`；==待确定==
3. 确定每个元素大小用`: n`。
