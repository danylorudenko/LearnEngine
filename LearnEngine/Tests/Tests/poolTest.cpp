#include <iostream>
#include <string>

#include <Engine/Util/Memory/ObjectPool.h>

struct Object
{
    std::string member_;
};

int main()
{
    constexpr size_t iterations = 10;

    Engine::ObjectPool<Object> pool;

    std::size_t * handles = new size_t[50];

    std::size_t* iter = handles;
    for (size_t i = 0; i < iterations; i++)
    {
        *iter = pool.Get();
        pool.AccessObj(*iter++).member_ = std::to_string(i);
    }

    iter = handles;

    for (size_t i = 0; i < iterations; i++)
    {
        std::cout << pool.AccessObj(*iter++).member_ << std::endl;
    }

    system("pause");
    return 0;
}