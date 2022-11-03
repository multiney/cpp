#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class ResourceOwner {
public:
    ResourceOwner() {
        theResource = nullptr;
    }

    ResourceOwner(const char res[]) {
        theResource = new string(res);
    }

    ResourceOwner(const ResourceOwner &other) {
        printf("copy %s\n", other.theResource->c_str());
        theResource = new string(other.theResource->c_str());
    }

    ResourceOwner& operator=(const ResourceOwner &other) {
        ResourceOwner tmp(other);
        std::swap(theResource, tmp.theResource);
        printf("assign %s\n", other.theResource->c_str());
        return *this;
    }

    ResourceOwner& operator=(ResourceOwner &&other) {
        if (this != &other) {
            delete theResource;
            theResource = other.theResource;
            other.theResource = nullptr;
        }
        return *this;
    }

    ~ResourceOwner() {
        if (theResource) {
            printf("destructor %s\n", theResource->c_str());
            delete theResource;
        }
    }

private:
    string *theResource;
};

class ResourceHolder {
public:
    ResourceHolder(const ResourceOwner& resourceOwner) : resOwner(resourceOwner) {}

    ResourceHolder(const ResourceHolder &other) {
        resOwner = other.resOwner;
    }

    ResourceHolder& operator=(const ResourceHolder &other) {
        resOwner = other.resOwner;
        return *this;
    }

    ResourceHolder& operator=(ResourceHolder &&other) {
        printf("assign rval\n");
        resOwner = std::move(other.resOwner);
        return *this;
    }
private:
    ResourceOwner resOwner;
};

void testRVal() {
    ResourceOwner res2("res2");
    res2 = ResourceOwner("res1");
    ResourceHolder rh(res2);
    //rh = ResourceHolder(ResourceOwner("res1"));
    rh = ResourceHolder(res2);
}

int main (int argc, char *argv[])
{
    testRVal();
    return 0;
}
