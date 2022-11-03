#include "Calculator.h"
#include <string>

using std::cout;
using std::endl;

void test_create_tree() {
    CalTree *t = parseExpr("32+233*434/24234+2423/2332");
    /*
    cout << t->node() << endl;
    cout << t->left().node() << endl;
    cout << t->right().node() << endl;
    cout << t->right().left().node() << endl;
    cout << t->right().right().node() << endl;
    */
    inorder(t);
    cout << endl;
}

void test_calculate() {
    CalTree *t = parseExpr("100+2*3*4*5-3");
    cout << t->calculate() << endl;
    t->deleteTree();
}

int main (int argc, char *argv[])
{
    // test_create_tree();
    test_calculate();
    return 0;
}
