#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap {
public:
    class Iterator {
    public:
        Iterator() : m_valid(false), index(0){}
        Iterator(std::vector<ValueType>* iterator) : m_valid(true), index(0)
        {
            m_iterator = iterator;
        }


        ValueType& get_value() const
        {
        
            return (*m_iterator)[index];
        }
        bool is_valid() const { return m_valid; }
        void advance()
        {
          index++;
          if  (index >= (*m_iterator).size())
            {
                m_valid = false;
            }
        }
    
    private:
        std::vector<ValueType>* m_iterator;
        int index;
        bool m_valid;
    };

    TreeMultimap() { m_root = nullptr;}
    ~TreeMultimap()
    {
        // delete all allocate new nodes
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr)
        { m_root = new Node(key, value); return; }
        
        Node *cur = m_root;
        for (;;)
        {
            if (key == cur->m_key)
            {
                cur->m_values.push_back(value);
                return; 
            }
            if (key < cur->m_key)
            {
                if (cur->left != nullptr)
                    cur = cur->left;
                else
                {
                    cur->left = new Node(key, value);
                    return;
                }
            }
            else if (key > cur->m_key)
            {
                if (cur->right != nullptr)
                    cur = cur->right;
                else
                {
                    cur->right = new Node(key, value);
                    return;
                }
            }
            
        }
       
    }

    Iterator find(const KeyType& key) const
    {
        Node *ptr = m_root;
        while (ptr != nullptr)
        {
            if (key == ptr->m_key)
                return Iterator(&(ptr->m_values));
            else if (key < ptr->m_key)
                ptr = ptr->left;
            else
            ptr = ptr->right;
        }
        return Iterator{};
    }

private:
    
    struct Node
   {
       Node(KeyType key,ValueType value)
       {
           m_key = key;
           m_values.push_back(value);
           left = right = nullptr;
       }

       KeyType m_key;
       std::vector<ValueType> m_values;
       Node *left,*right;
   };
    
    Node *m_root;
    
    
};


#endif // TREEMULTIMAP_INCLUDED
