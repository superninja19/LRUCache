#include <string>

#include "cache/lrucache.hpp"

int main(){
    cache::LRUCache<int,std::string> cache(5);
    return 0;
}
