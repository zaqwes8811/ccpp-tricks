#ifndef STD_OWN_EXT_H_
#define STD_OWN_EXT_H_

#include <map>
#include <string>

namespace std_own_ext {
template <typename K, typename V>
V at(const std::map<K, V> &param, const K &val) {
    // http://stackoverflow.com/questions/3311633/nested-templates-with-dependent-scope
    typename std::map<K, V>::const_iterator it = param.find(val);
    if (it != param.end())
        return it->second;
    else
        throw std::invalid_argument("at: Key not founded");
}

template <typename K, typename V>
V at(const std::map<K, V> &param, const char *const val) {
    typename std::map<K, V>::const_iterator it = param.find(std::string(val));
    if (it != param.end())
        return it->second;
    else
        throw std::invalid_argument("at: Key not founded");
}

template <typename K, typename V>
bool contain(const std::map<K, V> &param, const K &val) {
    typename std::map<K, V>::const_iterator it = param.find(val);
    if (it != param.end()) return true;
    return false;
}

template <typename K, typename V>
bool contain(const std::map<K, V> &param, const char *const val) {
    typename std::map<K, V>::const_iterator it = param.find(std::string(val));
    if (it != param.end()) return true;
    return false;
}

template <typename V>
struct cache {
public:
    explicit cache(const V &_value)
        : value(_value),
          stale(true)  // !!
    {}
    V value;

    void evict() { stale = true; }

    bool isStale() const { return stale; }

private:
    bool stale;
};
}  // namespace std_own_ext

#endif
