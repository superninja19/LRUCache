#pragma once
#include <cassert>
#include <list>
#include <optional>
#include <unordered_map>

namespace cache {

template <typename KeyValue, typename ValueType>
class LRUCache{
public:
    LRUCache(size_t capacity) : capacity_(capacity) {
        assert(capacity > 0 && "capacity should be greater than 0");
    }

    size_t getCapacity() const { return capacity_; }

    // todo: should be const imo
    std::optional<ValueType> get(KeyValue key){
        if (auto search = hashMap_.find(key); search != hashMap_.end()){
            return search->second;
        }
        return std::nullopt;
    }

    void put(KeyValue key, ValueType value) {
        if (auto search = hashMap_.find(key); search != hashMap_.end()){
            updateLruList(key);
            search->second = value;
        }
        else if (hashMap_.size() < capacity_){
            updateLruList(key);
            hashMap_[key] = value;
        }
        else {
            evictLeastRecentlyUsed();
            hashMap_[key] = value;
        }
    }

private:
    void evictLeastRecentlyUsed(){
        auto key = lruList_.back();
        hashMap_.erase(key);
        lruList_.pop_back();
    }

    void updateLruList(KeyValue key){
        lruList_.push_front(key);
        while (lruList_.size() > 1 && lruList_.front() == lruList_.back()){
            lruList_.pop_back();
        }
    }

    size_t capacity_ = 1; // Since capacity is a fixed size not expected to change, using unfixed size int.
    std::unordered_map<KeyValue,ValueType> hashMap_;
    std::list<KeyValue> lruList_;
};

}
