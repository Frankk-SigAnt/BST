#include <iostream>
#include "bstree.h"

using fsa::debug_bstree;
using std::cerr;
using std::endl;

int main()
{
    debug_bstree<int> tree_a;
    tree_a.insert(234);
    tree_a.insert(20);
    tree_a.insert(5000);
    tree_a.insert(46928);
    tree_a.insert(24);
    tree_a.insert(1);
    tree_a.insert(5724);
    // tree_a == {1, 20, 24, 234, 5000, 5724, 46928}

    // Search for elements existing in the tree.
    auto f_it = tree_a.find(234);
    //BOOST_CHECK_EQUAL(*f_it, 234);
    cerr << (*f_it == 234) << endl;
    tree_a.erase(f_it);
    // Value 234 has already erased. Find it again.
    // Return value `end()` expected.
    f_it = tree_a.find(234);
    //BOOST_CHECK(f_it == tree_a.end());
    cerr << (f_it == tree_a.end()) << endl;
    return 0;
}
