#ifndef AL_MALLOC_H
#define AL_MALLOC_H

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

#include "pragmadefs.h"


void al_free(void *ptr) noexcept;
[[gnu::alloc_align(1), gnu::alloc_size(2), gnu::malloc]]
void *al_malloc(size_t alignment, size_t size);
[[gnu::alloc_align(1), gnu::alloc_size(2), gnu::malloc]]
void *al_calloc(size_t alignment, size_t size);


#define DISABLE_ALLOC()                                                       \
    void *operator new(size_t) = delete;                                      \
    void *operator new[](size_t) = delete;                                    \
    void operator delete(void*) noexcept = delete;                            \
    void operator delete[](void*) noexcept = delete;

#define DEF_NEWDEL(T)                                                         \
    void *operator new(size_t size)                                           \
    {                                                                         \
        static_assert(&operator new == &T::operator new,                      \
            "Incorrect container type specified");                            \
        if(void *ret{al_malloc(alignof(T), size)})                            \
            return ret;                                                       \
        throw std::bad_alloc();                                               \
    }                                                                         \
    void *operator new[](size_t size) { return operator new(size); }          \
    void operator delete(void *block) noexcept { al_free(block); }            \
    void operator delete[](void *block) noexcept { operator delete(block); }

#define DEF_PLACE_NEWDEL()                                                    \
    void *operator new(size_t /*size*/, void *ptr) noexcept { return ptr; }   \
    void *operator new[](size_t /*size*/, void *ptr) noexcept { return ptr; } \
    void operator delete(void *block, void*) noexcept { al_free(block); }     \
    void operator delete(void *block) noexcept { al_free(block); }            \
    void operator delete[](void *block, void*) noexcept { al_free(block); }   \
    void operator delete[](void *block) noexcept { al_free(block); }

enum FamCount : size_t { };

#define DEF_FAM_NEWDEL(T, FamMem)                                             \
    static constexpr size_t Sizeof(size_t count) noexcept                     \
    {                                                                         \
        static_assert(&Sizeof == &T::Sizeof,                                  \
            "Incorrect container type specified");                            \
        return std::max(decltype(FamMem)::Sizeof(count, offsetof(T, FamMem)), \
            sizeof(T));                                                       \
    }                                                                         \
                                                                              \
    void *operator new(size_t /*size*/, FamCount count)                       \
    {                                                                         \
        if(void *ret{al_malloc(alignof(T), T::Sizeof(count))})                \
            return ret;                                                       \
        throw std::bad_alloc();                                               \
    }                                                                         \
    void *operator new[](size_t /*size*/) = delete;                           \
    void operator delete(void *block, FamCount) { al_free(block); }           \
    void operator delete(void *block) noexcept { al_free(block); }            \
    void operator delete[](void* /*block*/) = delete;


namespace al {

template<typename T, std::size_t Align=alignof(T)>
struct allocator {
    static constexpr std::size_t alignment{std::max(Align, alignof(T))};

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using is_always_equal = std::true_type;

    template<typename U>
    struct rebind {
        using other = allocator<U, Align>;
    };

    constexpr explicit allocator() noexcept = default;
    template<typename U, std::size_t N>
    constexpr explicit allocator(const allocator<U,N>&) noexcept { }

    T *allocate(std::size_t n)
    {
        if(n > std::numeric_limits<std::size_t>::max()/sizeof(T)) throw std::bad_alloc();
        if(auto p = al_malloc(alignment, n*sizeof(T))) return static_cast<T*>(p);
        throw std::bad_alloc();
    }
    void deallocate(T *p, std::size_t) noexcept { al_free(p); }
};
template<typename T, std::size_t N, typename U, std::size_t M>
constexpr bool operator==(const allocator<T,N>&, const allocator<U,M>&) noexcept { return true; }
template<typename T, std::size_t N, typename U, std::size_t M>
constexpr bool operator!=(const allocator<T,N>&, const allocator<U,M>&) noexcept { return false; }


template<typename T>
constexpr T *to_address(T *p) noexcept
{
    static_assert(!std::is_function<T>::value, "Can't be a function type");
    return p;
}

template<typename T>
constexpr auto to_address(const T &p) noexcept
{
    return ::al::to_address(p.operator->());
}


template<typename T, typename ...Args>
constexpr T* construct_at(T *ptr, Args&& ...args)
    noexcept(std::is_nothrow_constructible<T, Args...>::value)
{ return ::new(static_cast<void*>(ptr)) T{std::forward<Args>(args)...}; }


/* Storage for flexible array data. This is trivially destructible if type T is
 * trivially destructible.
 */
template<typename T, size_t alignment, bool = std::is_trivially_destructible<T>::value>
struct FlexArrayStorage {
    const size_t mSize;
    union {
        char mDummy;
        alignas(alignment) T mArray[1];
    };

    static constexpr size_t Sizeof(size_t count, size_t base=0u) noexcept
    {
        const size_t len{sizeof(T)*count};
        return std::max(offsetof(FlexArrayStorage,mArray)+len, sizeof(FlexArrayStorage)) + base;
    }

    FlexArrayStorage(size_t size) : mSize{size}
    { std::uninitialized_default_construct_n(mArray, mSize); }
    ~FlexArrayStorage() = default;

    FlexArrayStorage(const FlexArrayStorage&) = delete;
    FlexArrayStorage& operator=(const FlexArrayStorage&) = delete;
};

template<typename T, size_t alignment>
struct FlexArrayStorage<T,alignment,false> {
    const size_t mSize;
    union {
        char mDummy;
        alignas(alignment) T mArray[1];
    };

    static constexpr size_t Sizeof(size_t count, size_t base) noexcept
    {
        const size_t len{sizeof(T)*count};
        return std::max(offsetof(FlexArrayStorage,mArray)+len, sizeof(FlexArrayStorage)) + base;
    }

    FlexArrayStorage(size_t size) : mSize{size}
    { std::uninitialized_default_construct_n(mArray, mSize); }
    ~FlexArrayStorage() { std::destroy_n(mArray, mSize); }

    FlexArrayStorage(const FlexArrayStorage&) = delete;
    FlexArrayStorage& operator=(const FlexArrayStorage&) = delete;
};

/* A flexible array type. Used either standalone or at the end of a parent
 * struct, with placement new, to have a run-time-sized array that's embedded
 * with its size.
 */
template<typename T, size_t alignment=alignof(T)>
struct FlexArray {
    using element_type = T;
    using value_type = std::remove_cv_t<T>;
    using index_type = size_t;
    using difference_type = ptrdiff_t;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using Storage_t_ = FlexArrayStorage<element_type,alignment>;

    Storage_t_ mStore;

    static constexpr index_type Sizeof(index_type count, index_type base=0u) noexcept
    { return Storage_t_::Sizeof(count, base); }
    static std::unique_ptr<FlexArray> Create(index_type count)
    {
        void *ptr{al_calloc(alignof(FlexArray), Sizeof(count))};
        return std::unique_ptr<FlexArray>{al::construct_at(static_cast<FlexArray*>(ptr), count)};
    }

    FlexArray(index_type size) : mStore{size} { }
    ~FlexArray() = default;

    [[nodiscard]] auto size() const noexcept -> index_type { return mStore.mSize; }
    [[nodiscard]] auto empty() const noexcept -> bool { return mStore.mSize == 0; }

    [[nodiscard]] auto data() noexcept -> pointer { return mStore.mArray; }
    [[nodiscard]] auto data() const noexcept -> const_pointer { return mStore.mArray; }

    [[nodiscard]] auto operator[](index_type i) noexcept -> reference { return mStore.mArray[i]; }
    [[nodiscard]] auto operator[](index_type i) const noexcept -> const_reference { return mStore.mArray[i]; }

    [[nodiscard]] auto front() noexcept -> reference { return mStore.mArray[0]; }
    [[nodiscard]] auto front() const noexcept -> const_reference { return mStore.mArray[0]; }

    [[nodiscard]] auto back() noexcept -> reference { return mStore.mArray[mStore.mSize-1]; }
    [[nodiscard]] auto back() const noexcept -> const_reference { return mStore.mArray[mStore.mSize-1]; }

    [[nodiscard]] auto begin() noexcept -> iterator { return mStore.mArray; }
    [[nodiscard]] auto begin() const noexcept -> const_iterator { return mStore.mArray; }
    [[nodiscard]] auto cbegin() const noexcept -> const_iterator { return mStore.mArray; }
    [[nodiscard]] auto end() noexcept -> iterator { return mStore.mArray + mStore.mSize; }
    [[nodiscard]] auto end() const noexcept -> const_iterator { return mStore.mArray + mStore.mSize; }
    [[nodiscard]] auto cend() const noexcept -> const_iterator { return mStore.mArray + mStore.mSize; }

    [[nodiscard]] auto rbegin() noexcept -> reverse_iterator { return end(); }
    [[nodiscard]] auto rbegin() const noexcept -> const_reverse_iterator { return end(); }
    [[nodiscard]] auto crbegin() const noexcept -> const_reverse_iterator { return cend(); }
    [[nodiscard]] auto rend() noexcept -> reverse_iterator { return begin(); }
    [[nodiscard]] auto rend() const noexcept -> const_reverse_iterator { return begin(); }
    [[nodiscard]] auto crend() const noexcept -> const_reverse_iterator { return cbegin(); }

    DEF_PLACE_NEWDEL()
};

} // namespace al

#endif /* AL_MALLOC_H */
