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

                bst_iterator(bst_node * _Ptr = 0): _ptr(_Ptr) {}
                bst_iterator(bst_iterator & _it): _ptr(_it.ptr) {}

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
                    //TODO: increment unfinished
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
                    //TODO: decrement unfinished
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
            typedef bst_iterator  iterator;
            typedef unsigned int  size_type;

        private:
            iterator _header;
            size_type _size;

        protected:
            void destroy_node(node_type * _rm_ptr);
            iterator left_rotate(iterator _pos);
            iterator right_rotate(iterator _pos);

        public:
            //Con-/De-structors and operator=
            bstree(): _header(0), _size(0) {}
            explicit bstree(value_type & _val): _header(0), _size(1)
            {
                _header->father = new node_type(_val, _header._ptr);
                _header->left = _header->right = _header->father;
            }
            virtual ~bstree();
            bstree & operator=(bstree & _opr);

            //Capasity and element access
            size_type size() const {return _size;}
            bool empty() const {return (_header->father == 0);}
            iterator begin() {return iterator(_header->right);}
            iterator end() {return _header;} 
            reference front() const {return *(_header->right->data);}
            reference back() const {return *(_header->left->data);}
            iterator search(reference _val);

            //Modifiers
            void insert(reference _val);
            void erase(iterator _pos);
            void remove(reference _val);
            void swap(bstree & _opr);
            void splice(bstree & _opr);
    };

    template<class T>
    void bstree<T>::destroy_node(bstree<T>::node_type * _rm_ptr)
    {
        if(_rm_ptr == 0) return;
        destroy_node(_rm_ptr->left);
        destroy_node(_rm_ptr->right);
        delete _rm_ptr;
    }

    template<class T>
    bstree<T>::~bstree()
    {
        destroy_node(_header->father);
    }

    template<class T>
    bstree<T> & bstree<T>::operator=(bstree<T> & _opr)
    {
        this->_header = _opr._header;
        _size = _opr._size;
    }

}

#endif //BSTREE_H_
