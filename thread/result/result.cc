#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

struct Person
{
    std::string name;
    int age;
    std::string city;
};

std::vector<Person> vt = {
    {"aa", 20, "changxing"},
    {"bb", 25, "huzhou"}
};

// groupBy
template<typename F>
std::multimap<typename std::result_of<F(Person)>::type, Person>
groupBy(const std::vector<Person> &vt, const F &keySelect) {
    typedef typename std::result_of<F(Person)>::type key_type;
    std::multimap<key_type, Person> map;
    std::for_each(vt.cbegin(), vt.cend(),
            [&](const Person& p) {
            map.insert(std::make_pair(keySelect(p), p));
            });
    return map;
}

/*
template<typename F>
void printMap(std::multimap<typename std::result_of<F(Person)>::type, Person> &mp) {
    std::for_each(mp.cbegin(), mp.cend(), [](typename decltype(mp)::value_type &p) {
            std::cout << p.second.name << " " << p.second.city << " " << p.second.age << std::endl;
            });
}
*/

int main (int argc, char *argv[])
{
    auto ret = groupBy(vt, [](const Person &p){ return p.age; });
    std::for_each(ret.begin(), ret.end(), [](decltype(ret)::value_type &p) { // TODO: cbegin() error?
            std::cout << p.second.age << " " << p.second.city << " " << p.second.name << std::endl;
            });
    return 0;
}
