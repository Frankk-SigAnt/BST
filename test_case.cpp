#include "bstree.h"
#define BOOST_TEST_MODULE bstree_test
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <boost/test/included/unit_test.hpp> 

// Just ensure that the functions exeicuted and returned
BOOST_AUTO_TEST_CASE(it_works)
{
    // defualt constructor
    fsa::debug_bstree<int> tree_a, tree_b;
    fsa::debug_bstree<std::string> string_tree, string_tree_b;
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
    fsa::debug_bstree<int> tree_a;
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
    fsa::debug_bstree<int> tree_a;
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

BOOST_AUTO_TEST_CASE(begin_end_works_expectly)
{
    fsa::debug_bstree<int> tree_a;
    tree_a.insert(3);
    BOOST_CHECK_EQUAL(*tree_a.begin(), 3);
    BOOST_CHECK_EQUAL(*tree_a.end(), 3);
    tree_a.insert(27);
    BOOST_CHECK_EQUAL(*tree_a.begin(), 3);
    BOOST_CHECK_EQUAL(*tree_a.end(), 27);
    tree_a.insert(2);
    BOOST_CHECK_EQUAL(*tree_a.begin(), 2);
    BOOST_CHECK_EQUAL(*tree_a.end(), 27);
}

BOOST_AUTO_TEST_CASE(iterators_works_expectly)
{
    fsa::debug_bstree<int> tree_a;
    std::vector<int> vect_a;

    std::srand(13627);
    std::rand();
    for (int i = 0; i < 20; i++)
    {
        int tmp = std::rand();
        vect_a.push_back(tmp);
        tree_a.insert(tmp);
    }
    std::sort(vect_a.begin(), vect_a.end());
    vect_a.erase(std::unique(vect_a.begin(), vect_a.end()), vect_a.end());

    BOOST_CHECK_EQUAL_COLLECTIONS(tree_a.begin(), tree_a.end(), vect_a.begin(), vect_a.end());
}
