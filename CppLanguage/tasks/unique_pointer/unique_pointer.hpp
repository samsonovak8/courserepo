#pragma once

template <typename T>
class UniquePtr {
 public:
    UniquePtr() noexcept = default;

    UniquePtr(T* ptr_) noexcept : ptr(ptr_) {}

    UniquePtr(const UniquePtr<T>& uptr) = delete;
    T& operator=(const UniquePtr<T>& uptr) = delete;

    UniquePtr(UniquePtr<T>&& uptr) noexcept : ptr(uptr.ptr) {
        uptr.ptr = nullptr;
    }

    void operator=(UniquePtr<T>&& uptr) noexcept {
        if (ptr != uptr.ptr) {
            delete ptr;
            ptr = uptr.ptr;
        }

        uptr.ptr = nullptr;
    }

    template <typename U> 
    constexpr operator UniquePtr<U> () const {
        return UniquePtr<U>(ptr);
    }

    ~UniquePtr() {
        delete ptr;
    }

    T* Release() noexcept {
        T* saved_ptr = ptr;
        ptr = nullptr;
        return saved_ptr;
    }

    void Reset(T* ptr_ = nullptr) noexcept {
        delete ptr;
        ptr = ptr_;
    }

    constexpr void Swap(UniquePtr<T>& uptr) noexcept {
        std::swap(ptr, uptr.ptr);
    }

    constexpr T* Get() const noexcept {
        return ptr;
    }

    constexpr T& operator*() const {
        return *ptr;
    }

    constexpr T* operator->() const noexcept {
        return ptr;
    }

    constexpr operator bool () const noexcept {
        return ptr != nullptr;
    }

 private:
    T* ptr = nullptr;
};

template<typename T, typename... Args>
UniquePtr<T> MakeUnique(Args&&... args) {
    T* ptr = new T(std::forward <Args>(args)...);
    return UniquePtr(ptr);
}
