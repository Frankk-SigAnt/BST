#ifndef BSTREE_H_
#define BSTREE_H_

#include<cstdlib>
#include<algorithm>

namespace fsa
{
    template<class T>
    class bstree
    {
        protected:
            struct bst_node
            {
                T data;
                bst_node * father;
                bst_node * left, right;

                bst_node(): data(T()), father(0), left(0), right(0) {}
                bst_node(T & _val, bst_node * _pf = 0): data(_val), father(_pf), left(0), right(0) {}
            };

            struct bst_iterator
            {
                bst_node * _ptr;

                bst_iterator(bst_node * _Ptr_ = 0): _ptr(_Ptr_) {}
                bst_iterator(bst_iterator & __it): _ptr(__it.ptr) {}

                bst_node & operator*()
                {
                    return *_ptr;
                }

                bst_node * operator->()
                {
                    return _ptr;
                }

                bst_iterator & operator++()
                {
                    // increment unfinished
                    return *this;
                }

                bst_iterator operator++(int)
                {
                    bst_iterator tmp_It = *this;
                    *(this)++;
                    return tmp_It;
                }

                bst_iterator & operator--()
                {
                    // decrement unfinished
                    return *this;
                }

                bst_iterator operator--(int)
                {
                    bst_iterator tmp_It = *this;
                    *(this)--;
                    return tmp_It;
                }

                bool operator==(bst_iterator & It)
                {
                    return _ptr == It._ptr;
                }

                bool operator!=(bst_iterator & It)
                {
                    return _ptr != It._ptr;
                }
            };

        public:
            typedef T             value_type;
            typedef T &           reference;
            typedef bst_node      node_type;
            typedef bst_iterator  iterator;
            typedef unsigned int  size_type;

        private:
            iterator _root;
            size_type _size;
            bool isempty;

        protected:
            void destroy_node(iterator _rm_iter);
            iterator left_rotate(iterator _pos);
            iterator right_rotate(iterator _pos);

        public:
            //Con-/De-structors and operator=
            bstree(): _root(0), _size(0), isempty(true) {}
            explicit bstree(value_type & _val): _size(1), isempty(false) {_root = new node_type(_val);}
            virtual ~bstree();
            bstree & operator=(bstree & _opr);

            //Capasity and element access
            iterator root() {return _root;}
            size_type size() const {return _size;}
            bool empty() const {return isempty;}
            iterator begin();
            iterator end();
            reference front() const {return *(begin());}
            reference back() const {return *(end());}
            iterator search(reference _val);

            //Modifiers
            void insert(reference _val);
            void erase(iterator _pos);
            void remove(reference _val);
            void swap(bstree & _opr);
            void splice(bstree & _opr);
    };

    template<class T>
    void bstree<T>::destroy_node(bstree<T>::iterator _rm_iter)
    {
        if(_rm_iter == 0) return;
        destroy_node(_rm_iter->left);
        destroy_node(_rm_iter->right);
        delete _rm_iter;
    }

    template<class T>
    bstree<T>::~bstree()
    {
        destroy_node(_root);
    }

    template<class T>
    bstree<T> & bstree<T>::operator=(bstree<T> & _opr)
    {
        this->_root = _opr._root;
        _size = _opr._size;
        isempty = _opr.isempty;
    }

    template<class T>
    typename bstree<T>::iterator bstree<T>::begin()
    {
        iterator _iter = _root;
        while(_iter->left != 0) _iter = _iter->left;
        return _iter;
    }

    template<class T>
    typename bstree<T>::iterator bstree<T>::end()
    {
        iterator _iter = _root;
        while(_iter->right != 0) _iter = _iter->right;
        return _iter;
    }

}

#endif
