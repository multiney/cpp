#include <vector>
#include <iostream>

#include "./Vector.h"

using std::vector;
using std::cout;
using std::endl;

template<typename T>
void printVec(const Vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";
    cout << endl;
}

template<typename T>
void printStlVec(const vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";
    cout << endl;
}

void test_stl_vec() {
    vector<int> vi(3, 1);
    cout << vi[-1] << endl;
    const vector<int> vi1(vi.begin(), vi.end());
    vi.reserve(10);
    vi.resize(2, 0);
    vector<int> viCopy = vi;
    printStlVec(vi);
    vector<int> vDefault;
    cout << vDefault.capacity() << endl;
    vDefault.insert(vDefault.begin(), 2, 3);
    printStlVec(vDefault);
}

void test_constructor() {
    Vector<int> vi1(3, 1);
    Vector<int> vi2(vi1);
    const Vector<int> vi3(vi2.cbegin(), vi2.cend());
    cout << vi1.size() << " " << vi1.capacity() << endl;
    printVec(vi3);
}

void test_push_back() {
    Vector<int> vi;
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(3);
    vi.push_back(4);
    vi.push_back(5);
    cout << std::boolalpha << vi.empty() << endl;
    cout << vi.size() << " " << vi.capacity() << endl;
    printVec(vi);
}

void test_insert() {
    Vector<int> vi;
    vi.insert(vi.begin(), 2, 4);
    printVec(vi);
    auto it = vi.insert(vi.end(), 10, 5);
    printVec(vi);
    vi.insert(it, 2, 6);
    printVec(vi);
}

void test_resize() {
    Vector<int> vi;
    vi.resize(1, 1);
    printVec(vi);
    vi.resize(3, 2);
    printVec(vi);
    vi.resize(6, 3);
    printVec(vi);
    vi.resize(1, 0);
    printVec(vi);
}


int main (int argc, char *argv[])
{
    //test_stl_vec();
    //test_push_back();
    //test_constructor();
    //test_insert();
    test_resize();

    return 0;
}
