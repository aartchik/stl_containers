#include <iostream>
#include <vector>

namespace hs {
template <typename Tp>
struct hash;

template <>
struct hash<int> {
    size_t operator()(int key) {
        return static_cast<size_t>(key);
    }
};

template <>
struct hash<std::string> {
    size_t operator()(const std::string& key) {
        size_t result = 0;
        const long long m = 10000000 + 7;
        long long p = 1;
        for (int i = 0; i < key.size(); ++i) {
            result = (result + (static_cast<unsigned char>(key[i]) * p % m)) % m;
            p = (p * 37) % m;
        }
        return result;
    }
};
}

template <typename T>
struct list {

    using reference = T&;
    using const_reference = const T&;


    int size_;
    
    struct base_Node {
        base_Node* prev;
        base_Node* next;
        base_Node(base_Node* prev, base_Node* next): prev(prev), next(next) {}
    };
    base_Node fakeNode;
    struct Node: base_Node {
        T value;

        Node(Node* prev, Node* next, const T& value): base_Node(prev, next), value(value) {}
        Node(const T& value): base_Node(nullptr, nullptr), value(value) {}
    };

    list(): size_(0), fakeNode(&fakeNode, &fakeNode) {}


    template <bool IsConst>
    class base_iterator
    {
        friend list<T>;
        using base_ptr = typename std::conditional<IsConst, const base_Node*, base_Node*>::type;
        using pointer_type = typename std::conditional<IsConst, const T*, T*>::type;
        using reference_type = typename std::conditional<IsConst, const T&, T&>::type;
    public:

        explicit base_iterator(const base_Node* ptr);

        reference_type operator*() const;
        pointer_type operator->() const;

        base_iterator& operator++() {
            current = current->next;
            return *this;
        }
        base_iterator operator++(int) {
            base_iterator copy = *this;
            ++(*this);
            return copy;

        }

        base_iterator& operator--() {
            current = current->prev;
            return *this;
        }

        base_iterator operator--(int) {
            base_iterator copy = *this;
            current = current->prev;
            return copy;
        }


        bool operator==(const base_iterator& other) const;
        bool operator!=(const base_iterator& other) const;

        operator base_iterator<true>() const { return base_iterator<true>(current); }
        //explicit operator Node*() const { return static_cast<Node*>(current);}

    private:
        base_Node* current;
    };

    using iterator = base_iterator<false>;
    using const_iterator = base_iterator<true>;

    iterator insert(const_iterator pos, T& value) {
        ++size_;
        Node* node = new Node(value);
        node->next = pos.current;
        node->prev = pos.current->prev;
        node->prev->next = node;
        pos.current->prev = node;
        return iterator(static_cast<base_Node*>(node));
    }

    iterator erase(const_iterator pos)
    {
        --size_;
        base_Node* node = pos.current;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        iterator ret(static_cast<base_Node*>(node->next));
        delete static_cast<Node*>(node);
        return ret;

    }

    //using reverse_iterator = std::reverse_iterator<iterator>;
    //using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    // Element access

    reference front();
    reference back();
    const_reference front() const;
    const_reference back() const;

    // Iterators
    iterator begin() const noexcept {
        return iterator(fakeNode.next);
    }
    iterator end()  const noexcept {
        return iterator(&fakeNode);
    }
    const_iterator cbegin() const noexcept {
        return const_iterator(fakeNode.next);
    }
    const_iterator cend() const noexcept {
        return const_iterator(&fakeNode);
    }

    // Capacity
    bool empty() const noexcept {
        return size_ == 0;
    }
    size_t size() const noexcept {
        return size_;
    }

    // Modifers
    void clear() noexcept;
    iterator erase(const_iterator first, const_iterator last);
};




template <typename Key, typename Tp, typename Hash = hs::hash<Key>>
struct unordered_map {
    const size_t m = 100000;

    struct Node {
        Key k;
        Tp t;
        u_int64_t hash;
        Node(const Key& k, const Tp& t): k(k), t(t) {
            hash = hs::hash(k);
        }
    };

    int size_;
    list<Node> lst;
    std::vector<typename list<Node>::iterator*> line;
    unordered_map(): size_(0) {
        line.resize(m);
    }

    void insert(const Key& k, const Tp& value) {
        Node node = Node(k, value);
        auto frst = line[node->hash % m];
            if (frst == nullptr) {
            auto fst = lst.insert(lst.begin, node);
            line[node->hash % m] = &fst;
        } else {
            auto x = *frst;
            while (x->hash == node->hash) {
                if (x->k == node->k) {
                    x->t = node->t;
                    return;
                }
                x = frst++;
            }
            lst.insert(x, node);
            return;

        }
    }
};

int main() {
    list<int> l;
    std::cout << l.size_;

}