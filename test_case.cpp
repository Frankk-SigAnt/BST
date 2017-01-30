#include "bstree.h"
#define BOOST_TEST_MODULE bstree_test
#include <string>
#include <boost/test/included/unit_test.hpp> 

// Just ensure that the functions exeicuted and returned
BOOST_AUTO_TEST_CASE(it_works)
{
    // defualt constructor
    fsa::bstree<int> tree_a, tree_b;
    fsa::bstree<std::string> string_tree, string_tree_b;
    // `operator=(const bstree&)`
    tree_a = tree_b;

    // iterators
    tree_a.begin(), tree_a.end();
    
    //// `insert(T)`
    tree_a.insert(666);
    string_tree.insert("666");

    // If it enters here, this test passes
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(empty_work_expectly)
{
    fsa::bstree<int> tree_a;
    BOOST_CHECK(tree_a.empty());
}
