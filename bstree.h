#ifndef BSTREE_H_
#define BSTREE_H_

#include<cstdlib>
#include<algorithm>
#include<memory>

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
            //bst_node * left, right;
            std::unique_ptr<bst_node> left, right;

            bst_node() {}
            bst_node(T & _val, bst_node * _pf = nullptr) : data(_val), father(_pf) {}
        };

        struct bst_iterator
        {
            bst_node * _ptr;

            bst_iterator(bst_node * _Ptr = 0) : _ptr(_Ptr) {}
            bst_iterator(bst_iterator & _it) : _ptr(_it.ptr) {}

            T & operator*()
            {
                return *_ptr->data;
            }

            bst_node * operator->()
            {
                return _ptr;
            }

            bst_iterator & operator++()
            {
                if ((*this)->right != 0)
                {
                    this->ptr = (*this)->right;
                    while ((*this)->left != 0)
                    {
                        this->ptr = (*this)->left;
                    }
                }
                else
                {
                    bst_node * prev = this->ptr;
                    this->ptr = (*this)->father;
                    while (prev == (*this)->right)
                    {
                        prev = this->ptr;
                        this->ptr = (*this)->father;
                    }
                }
                return *this;
            }

            bst_iterator operator++(int)
            {
                bst_iterator tmp_iter = *this;
                *(this)++;
                return tmp_iter;
            }

            bst_iterator & operator--()
            {
                if ((*this)->left != 0)
                {
                    this->ptr = (*this)->left;
                    while ((*this)->right != 0)
                    {
                        this->ptr = (*this)->right;
                    }
                }
                else
                {
                    bst_node * prev = this->ptr;
                    this->ptr = (*this)->father;
                    while (prev == (*this)->left)
                    {
                        prev = this->ptr;
                        this->ptr = (*this)->father;
                    }
                }
                return *this;
            }

            bst_iterator operator--(int)
            {
                bst_iterator tmp_iter = *this;
                *(this)--;
                return tmp_iter;
            }

            bool operator==(bst_iterator & _it)
            {
                return _ptr == _it._ptr;
            }

            bool operator!=(bst_iterator & _it)
            {
                return _ptr != _it._ptr;
            }
        };

    public:
        typedef T             value_type;
        typedef T &           reference;
        typedef bst_node      node_type;
        typedef bst_node *    pointer;
        typedef bst_iterator  iterator;
        typedef unsigned int  size_type;

    private:
        std::unique_ptr<node_type> _header;
        size_type _size;

    protected:
        iterator left_rotate(iterator _pos);
        iterator right_rotate(iterator _pos);

    public:
        //Con-/De-structors and operator=
        bstree() : _header(0), _size(0) {}
        explicit bstree(value_type & _val) : _header(0), _size(1)
        {
            _header->father = new node_type(_val, _header->_ptr);
            _header->left = _header->right = _header->father;
        }
        virtual ~bstree();
        bstree & operator=(bstree & _opr);

        //Capasity and element access
        size_type size() const { return _size; }
        bool empty() const { return (_header->father == 0); }
        iterator begin() { return iterator(_header->right); }
        iterator end() { return iterator(_header); }
        reference front() const { return _header->right->data; }
        reference back() const { return _header->left->data; }
        iterator find(reference _val);

        //Modifiers
        void insert(reference _val);
        void erase(iterator _pos);
        void remove(reference _val);
        void swap(bstree & _opr);
        void splice(bstree & _opr);
    };

    template<class T>
    bstree<T> & bstree<T>::operator=(bstree<T> & _opr)
    {
        //TODO
    }

    template<class T>
    typename bstree<T>::iterator bstree<T>::find(bstree<T>::reference _val)
    {
        pointer _ptr = _header->father;

        while (_ptr != 0)
        {
            if (_val == _ptr->data)
            {
                break;
            }
            else
            {
                _ptr = (_val < _ptr->data)
                    ? _ptr->left
                    : _ptr->right;
            }
        }

        if (_ptr == 0)
        {
            return end();
        }
        else
        {
            return iterator(_ptr);
        }
    }

}

#endif //BSTREE_H_
