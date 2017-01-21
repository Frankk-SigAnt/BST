#ifndef BSTREE_H_
#define BSTREE_H_

#include<cstdlib>
#include<algorithm>

namespace fsa
{
    template<class _tp>
    class bstree
    {
        protected:
            template<class _Ttp>
            struct bst_node
            {
                _Ttp data;
                bst_node * father;
                bst_node * left, right;

                bst_node(): data(_Ttp()), father(0), left(0), right(0) {}
                bst_node(_Ttp & _val, bst_node * _pf = 0): data(_val), father(_pf), left(0), right(0) {}
        };

            template<class _Ttp>
            struct bst_iterator
            {
                bst_node<_Ttp> * _ptr;

                bst_iterator(bst_node<_Ttp> * _Ptr_ = 0): _ptr(_Ptr_) {}

                bst_iterator(bst_iterator & __it): _ptr(__it.ptr) {}

                bst_node<_Ttp> * operator*()
                {
                    return *_ptr;
                }

                bst_node<_Ttp> * operator->()
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
                    bst_iterator _tmp_it = *this;
                    operator++;
                    return _tmp_it;
                }

                bst_iterator & operator--()
                {
                    // decrement unfinished
                    return *this;
                }

                bst_iterator operator--(int)
                {
                    bst_iterator _tmp_it = *this;
                    operator--;
                    return _tmp_it;
                }
            };

        public:
            typedef _tp                value_type;
            typedef _tp &              reference;
            typedef bst_node<_tp>      node_type;
            typedef bst_iterator<_tp>  iterator;
            typedef unsigned int       size_type;

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

    template<class _tp>
    void bstree<_tp>::destroy_node(bstree<_tp>::iterator _rm_iter)
    {
        if(_rm_iter == 0) return;
        destroy_node(_rm_iter->left);
        destroy_node(_rm_iter->right);
        delete _rm_iter;
    }

    template<class _tp>
    bstree<_tp>::~bstree()
    {
        destroy_node(_root);
    }

    template<class _tp>
    bstree<_tp> & bstree<_tp>::operator=(bstree<_tp> & _opr)
    {
        this->_root = _opr._root;
        _size = _opr._size;
        isempty = _opr.isempty;
    }

    template<class _tp>
    typename bstree<_tp>::iterator bstree<_tp>::begin()
    {
        iterator _iter = _root;
        while(_iter->left != 0) _iter = _iter->left;
        return _iter;
    }

    template<class _tp>
    typename bstree<_tp>::iterator bstree<_tp>::end()
    {
        iterator _iter = _root;
        while(_iter->right != 0) _iter = _iter->right;
        return _iter;
    }

}

#endif
