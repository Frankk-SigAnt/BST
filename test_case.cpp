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

    // `clear()`
    tree_a.clear();
    string_tree.clear();

    // iterators
    tree_a.begin(), tree_a.end();
    
    // `insert(T)`
    tree_a.insert(666);
    string_tree.insert("666");

    tree_a.find(666);

    // If it enters here, this test passes
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(empty_and_size_work_expectly)
{
    // Defualt constructs empty
    fsa::bstree<int> tree_a;
    BOOST_CHECK(tree_a.empty());
    BOOST_CHECK_EQUAL(tree_a.size(), 0);

    // Not empty after insert
    tree_a.insert(666);
    BOOST_CHECK(!tree_a.empty());
    BOOST_CHECK_EQUAL(tree_a.size(), 1);

    // Empty after cleared
    tree_a.clear();
    BOOST_CHECK(tree_a.empty());
    BOOST_CHECK_EQUAL(tree_a.size(), 0);
}

BOOST_AUTO_TEST_CASE(insert_work_expectly)
{
    fsa::bstree<int> tree_a;
    tree_a.insert(1);
    tree_a.insert(1);

    // Same element is ignored
    BOOST_CHECK(!tree_a.empty());
    BOOST_CHECK_EQUAL(tree_a.size(), 1);

    tree_a.insert(122);
    BOOST_CHECK_EQUAL(tree_a.size(), 2);

    for (int i = 2; i < 100; i++)
    {
        tree_a.insert(i);
        BOOST_CHECKPOINT("called insert(" << i << ")");
        BOOST_CHECK(!tree_a.empty());
        BOOST_CHECK_EQUAL(tree_a.size(), i + 1);
    }
}
