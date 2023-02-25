#include <cstddef>
#include <cstring>
#include <type_traits>
#include <stdexcept>

//WORK IN PROGRESS,
// TODO: ITERATORS, LIST INITILIZATION

template <typename T>
class vector {
    static_assert(std::is_trivially_constructible_v<T>);
    static_assert(std::is_trivially_destructible_v<T>);
    T * arr;
    std::size_t capacity;
    std::size_t numElts;

    public:

    constexpr vector() {
        arr = new T[1];
        capacity = 1;
        numElts = 0;
    }

    ~ vector() {
        delete [] arr;
    }

    void push(T datum) {
        if (numElts == capacity) {
            T * tmp = new T[capacity << 1];
            std::memcpy(tmp, arr, sizeof(T) * capacity);
            delete [] arr;
            arr = tmp;
            capacity <<= 2;

        }

        (arr + numElts++) = datum;

    }

    void push(T datum, std::size_t _idx) {
        if (_idx >= capacity) throw std::runtime_error("Inserting past range of vector\n");
        (arr + _idx) = datum;
    }

    [[nodiscard]] inline auto get(std::size_t _idx) -> T {
        if (_idx >= capacity) throw std::runtime_error("Accessing out of bounds of vector\n");
        return *(arr + _idx);
    }

    //default construct type. Behavior is non standard compient.
    inline void pop() {
        (arr + numElts--) = T();
    }

    [[nodiscard]] auto inline size() noexcept -> std::size_t  {
        return numElts;
    }

    [[nodiscard]] auto inline getCapacity() noexcept -> std::size_t  {
        return capacity;
    }


};
