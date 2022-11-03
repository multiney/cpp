#include <bits/types/clock_t.h>
#include <cstdio>
#include <exception>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <array>
#include <list>

using std::vector;
using std::string;
using std::cout;
using std::endl;

#define CONTAINER_SIZE 100000

string arrS[CONTAINER_SIZE];
long indexTarget = 78977;
string target;

int compareString(const void* a, const void* b) {
    if (*(string*)a > *(string*)b) return 1;
    else if (*(string*)a < *(string*)b) return -1;
    return 0;
}

void fill_container() {
    char buf[10];
    std::srand(999999);
    for (long i = 0; i < CONTAINER_SIZE; ++i) {
        snprintf(buf, 10, "%d", rand());
        arrS[i] = string(buf);
    }
    target = arrS[indexTarget];
}

void test_vector()
{
    cout << "test_vector()............." << endl;

    vector<string> vs;

    for (long i = 0; i < CONTAINER_SIZE; ++i) {
        try {
            vs.push_back(arrS[i]);
        }
        catch (std::exception& e){
            cout << "i=" << i << " " << e.what() << endl;
            abort();
        }
    }
    cout << "vector.size()=" << vs.size() << endl;
    cout << "vector.capacity()=" << vs.capacity() << endl;
    cout << "vector.front()=" << vs.front() << endl;
    cout << "vector.back()=" << vs.back() << endl;
    cout << "vector.data()=" << vs.data() << endl;

    clock_t timeStart = clock();
    std::sort(vs.begin(), vs.end());
    string* pTarget = (string*)bsearch(&target, vs.data(), vs.size(), sizeof(string), compareString);
    cout << "bsearch() makes " << (clock() - timeStart) / 1000 << " milli-seconds." << endl;
    if (pTarget != nullptr)
        cout << "found, " << *pTarget << endl;
    else
        cout << "not found!" << endl;
}

void test_array() {
    cout << "test_array()................" << endl;
    std::array<string, CONTAINER_SIZE> as;
    for (long i = 0; i < CONTAINER_SIZE; ++i) {
        try {
            as[i] = arrS[i];
        }
        catch (std::exception& e) {
            cout << "i=" << i << " " << e.what() << endl;
            abort();
        }
    }
    clock_t timeStart = clock();
    std::sort(as.begin(), as.end());
    string* pTarget = (string*)bsearch(&target, as.data(), as.size(), sizeof(string), compareString);
    cout << "bsearch() makes " << (clock() - timeStart) / 1000 << " milli-seconds." << endl;
    if (pTarget != nullptr)
        cout << "found, " << *pTarget << endl;
    else
        cout << "not found!" << endl;
}

void test_list() {
    cout << "test_list()................." << endl;
    std::list<string> lst;
    std::list<int> lst2;
    cout << "list.max_size()=" << lst.max_size() << endl;
    cout << "lst2.max_size()=" << lst2.max_size() << endl;
}


int main (int argc, char *argv[])
{
    fill_container();
    test_vector();
    test_array();
    test_list();
    return 0;
}
