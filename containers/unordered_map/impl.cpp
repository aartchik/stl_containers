#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>


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
        const long long m = 10000000+7;
        long long p = 1;
        for (int i = 0; i< key.size(); ++i) {
            result = (result + (static_cast<unsigned char>(key[i]) * p % m)) % m;
            p = (p * 37)%m;
        }
        return result;
    }
};


template <typename Key, typename Tp, typename Hash = hash<Key>>
struct hash_map {
    using pair = std::pair<Key, Tp>;
    Hash hash;
    const size_t m = 100000;
    std::vector<std::list<pair>> line;
    
    hash_map() {
        line.resize(m);
    }

    void add(const Key& key, Tp value) {
        auto res = hash_func(key);
        line[res].push_back({key, value });
    }

    Tp find(const Key& key) {
        for (auto& x: line[hash_func(key)]) {
            if (x.first == key) {
                return x.second;
            }
        }
        return 0;
    }
    void hs(const Key& key) {
        for (auto& x : line[hash_func(key)]) {
            if (x.first == key) {
                std::cout << hash_func(key) << std::endl;
            }
        }
    }

    void del(const Key& key) {
        auto& bucket = line[hash_func(key)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it ) {
            if (it->first == key) {
                bucket.erase(it);
                return;
            }
        }
    }

private:
    long long hash_func(const Key& key) {
        return hash(key) % m; 
    }
};

int main() {

    hash<std::string> hh;

    std::unordered_map<std::string, int> mp;
    hash_map<std::string, int> hash;
    hash.add("a", 42);
    hash.add("abcdef", 424);
    hash.add("aklasdfjasdfasdf", 55);

    hash.hs("aklasdfjasdfasdf");




    return 0;
}