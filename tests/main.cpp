#include <cassert>
#include <iostream>

#include "cache/lrucache.hpp"

void testLruCache_GetCapacity()
{
    size_t capacity = 5;
    cache::LRUCache<int,int> cache(capacity);
    assert(cache.getCapacity() == capacity);
}

void testLruCache_EmptyCache_Insert(){
    size_t capacity = 3;
    cache::LRUCache<int,int> cache(capacity);

    auto val = cache.get(2);
    assert(val.has_value() == false && "get() should return no value");

    cache.put(2, 10);
    val = cache.get(2);
    assert(val.value() == 10 && "get() returned value should be 10");

    cache.put(3, 8);
    cache.put(5, 11);
    cache.put(14, 20);
    val = cache.get(2);
    assert(val.has_value() == false && "get() should return no value cause key '2' was evicted");

    cache.put(14, 11);
    cache.put(3, 16);
    cache.put(2, 99);

    val = cache.get(5);
    assert(val.has_value() == false && "get() should return no value cause key '5' was evicted");

    val = cache.get(3);
    assert(val.value() == 16 && "get() should return 16 as key '3' was updated with value 16");
}

void testLruCache_EmptyCache_AlternatePuts(){
    cache::LRUCache<int,int> cache(2);

    for (int i=0; i<1000; i++){
        cache.put(1,1);
        cache.put(2,2);
    }

    std::cout << "Hash map size: " << cache.getCacheSize() << "\n";
    std::cout << "List size: " << cache.getListSize() << "\n";
}

void testLruCache_EmptyCache_CapacityOne_Insert(){
    cache::LRUCache<int,int> cache(1);

    cache.put(1,1);
    cache.put(2,2);
    cache.put(3,3);

    auto val = cache.get(3);
    assert(val == 3 && "Only entry should be 3");
}


int main()
{
    testLruCache_GetCapacity();
    testLruCache_EmptyCache_Insert();
    testLruCache_EmptyCache_CapacityOne_Insert();
    testLruCache_EmptyCache_AlternatePuts();
    return 0;
}
