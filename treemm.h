#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <unordered_map>
#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap {
public:
    class Iterator {
    public:
        Iterator() : m_valid(false) {}
        explicit Iterator(typename std::vector<ValueType>::const_iterator it, typename std::vector<ValueType>::const_iterator end)
            : m_it(it), m_end(end), m_valid(true) {}

        ValueType& get_value() const {  return const_cast<ValueType&>(*m_it);  }
        bool is_valid() const { return m_valid; }
        void advance() {
            ++m_it;
            if (m_it == m_end) {
                m_valid = false;
            }
        }

    private:
        typename std::vector<ValueType>::const_iterator m_it;
        typename std::vector<ValueType>::const_iterator m_end;
        bool m_valid;
    };

    TreeMultimap() = default;
    ~TreeMultimap() = default;

    void insert(const KeyType& key, const ValueType& value) {
        auto it = m_map.find(key);
        if (it == m_map.end()) {
            std::vector<ValueType> vec{ value };
            m_map.emplace(key, std::move(vec));
        } else {
            it->second.push_back(value);
        }
    }

    Iterator find(const KeyType& key) const {
        auto it = m_map.find(key);
        if (it != m_map.end()) {
            return Iterator{ it->second.cbegin(), it->second.cend() };
        }
        return Iterator{};
    }

private:
    std::unordered_map<KeyType, std::vector<ValueType>> m_map;
};


#endif // TREEMULTIMAP_INCLUDED
