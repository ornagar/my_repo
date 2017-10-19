/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Singly Linked List.                        #################################
 *                                             ##########    ####       ########
 *  Or Nagar                                   ########  ####  ##  ###  ########
 *  26-07-2017                                 ########  ####  ##     ##########
 *  11:33:14                                   ########  ####  ##  ###  ########
 *                                             ##########    ####  ###  ########
 *                                             #################################
 *  The template class List manages a singly linked
 *  list, creating an instance of List will create an empty list.
 *  push_front() will push the desired data to the begining of the list.
 *  pop_front() will remove the data from the begining of the list.
 *                                    
 *                                    
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef LIST_HPP_
#define LIST_HPP_      
     
#include <cstddef>                      // size_t       

namespace ilrd
{

//template class to manage a singly linked list
template <class T>
class List
{
public:
   
    explicit List();
    ~List();
    List(const List& other);
    List& operator=(const List& other);
    bool push_front(T data);  
    bool pop_front();
    bool peek_front(T*) const;
    inline size_t size() const;
    inline bool is_empty() const;
    template <class K>
    bool for_each(bool (*act_func)(T* t, K args), K args);
   
private:
    void destroy();
    
    struct Node
    {
        Node(T data = 0);
        T data;
        Node *next;
    };

    Node *m_head;
    size_t m_elements_num;
};

/*********************************FUNCTION DEFINITION**************************/
template<class T>
List<T>::Node::Node(T data) : data(data), next(NULL) {}

template<class T>
List<T>::List(): m_head(NULL), m_elements_num(0) {}

template<class T>
List<T>::~List()
{
    destroy();
}

template<class T>
List<T>::List(const List& other)
{
    m_elements_num = 0;
    if (other.is_empty())
    {
        m_head = NULL;
        return;
    }
    
    Node *current = other.m_head;
    m_head = new (std::nothrow)Node;
    if (NULL == m_head)
    {
        return;
    }
    
    Node *copy_node = m_head;
    copy_node->data = current->data;
    current = current->next;
    
    while (current != NULL)
    {
        copy_node->next = new (std::nothrow)Node;
        if (NULL == copy_node->next)
        {
            destroy();
            return;
        }
        copy_node = copy_node->next;
        copy_node->data = current->data;
        current = current->next;
    }
    
    copy_node->next = NULL;
    m_elements_num = other.m_elements_num;
}

template<class T>
List<T>& List<T>::operator=(const List& other)
{
    List temp(other);
    if (temp.size() == other.size())
    {
        destroy();
        m_head = temp.m_head;
        m_elements_num = temp.m_elements_num;
        temp.m_head = NULL;
        temp.m_elements_num = 0;
    }
    
    return *this;
}

template<class T>
bool List<T>::push_front(T data)
{
    Node *new_node = new (std::nothrow)Node(data);
    if (NULL == new_node)
    {
        return false;
    }
    
    new_node->next = m_head;
    m_head = new_node;
    ++m_elements_num; 
    
    return true;
}

template<class T>
bool List<T>::pop_front()
{
    if (is_empty())
    {
        return false;
    }
    
    Node *to_remove = m_head;
    m_head = m_head->next;
    delete to_remove;
    --m_elements_num;
    
    return true;
}

template<class T>
bool List<T>::peek_front(T* data) const
{
    if (is_empty())
    {
        return false;
    }
    
    *data = m_head->data;
    return true;
}

template<class T>
size_t List<T>::size() const { return m_elements_num; }

template<class T>
bool List<T>::is_empty() const { return 0 == m_elements_num; }

template<class T>
template <class K>
bool List<T>::for_each(bool (*act_func)(T* t, K args), K args)
{
    Node *runner = m_head;
    
    while (NULL != runner)
    {
        if (false == act_func(&runner->data, args))
        {
            return false;
        }
        runner = runner->next;
    }
    
    return true;
}
/******************************************************************************/
/****************************PRIVATE FUNCTIONS*********************************/
template<class T>
void List<T>::destroy()
{
    while (!is_empty())
    {
        pop_front();
    }
}
/******************************************************************************/

} //namespace ilrd
#endif //LIST_HPP_

