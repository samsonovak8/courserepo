#pragma once

#include<memory>
#include<cstddef>

template<typename T>
class SharedPtr;

template<typename T>
class WeakPtr;

template<typename T>
class SharedPtr {
 public:
    SharedPtr() = default;

    SharedPtr(std::nullptr_t) noexcept : SharedPtr() {}

    SharedPtr(T* ptr_) noexcept : SharedPtr() {
        if (ptr_) {
            block = new ControlBlock(ptr_, 1, 0);
        }
        else {
            block = nullptr;
        }
    }

    SharedPtr(const SharedPtr<T>& sptr) noexcept : SharedPtr(sptr.block) {}

    SharedPtr& operator=(const SharedPtr<T>& sptr) noexcept {
        if (block == sptr.block) {
            return *this;
        }

        SharedPtr<T> tmp_block(sptr.block);
        Swap(tmp_block);
        return *this;
    }

    SharedPtr(const WeakPtr<T>& wptr) {
        if (wptr.Expired()) {
            throw std::bad_weak_ptr();
        }

        SharedPtr<T> tmp_block(wptr.block);
        Swap(tmp_block);
    }

    SharedPtr(SharedPtr&& sptr) noexcept : block(sptr.block) {
        sptr.block = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& sptr) noexcept {
        if (sptr.block == block) {
            sptr.block = nullptr;
            return *this;
        }
        SharedPtr<T> tmp(std::move(sptr));
        Swap(tmp);
        return *this;
    } 

    template<typename U>
    operator SharedPtr<U> () const noexcept {
        SharedPtr<U> sptr;
        sptr.block = block;
        return sptr;
    }

    void Reset(T* new_ptr = nullptr) {
        SharedPtr<T> tmp(new_ptr);
        Swap(tmp);
    }

    constexpr void Swap(SharedPtr<T>& sptr) noexcept {
        std::swap(block, sptr.block);
    }

    constexpr T* Get() const noexcept {
        return (block) ? block->ptr : nullptr;
    }

    constexpr size_t UseCount() const noexcept {
        return (block) ? block->shared_count : 0;
    }

    constexpr T& operator*() const {
        return *block->ptr;
    }

    constexpr T* operator->() const {
        return block->ptr;
    }

    constexpr operator bool() const noexcept {
        return (block != nullptr);
    }

    ~SharedPtr() noexcept {
        if (block) {
            if (block->shared_count == 1) {
                delete block->ptr;
                block->ptr = nullptr;
                block->shared_count = 0;
                
                if (block->weak_count == 0) {
                    delete block;
                }
            }
            else {
                --block->shared_count;
            }
        }
    }

 private:
    friend WeakPtr<T>;

    struct ControlBlock {
        T* ptr = nullptr;
        size_t shared_count = 0;
        size_t weak_count = 0;

        ControlBlock(T* ptr_, size_t shared_count_, size_t weak_count_) :
             ptr(ptr_), shared_count(shared_count_), weak_count(weak_count_) {}
    };

    ControlBlock* block = nullptr;

    SharedPtr(ControlBlock* new_block) noexcept : block(new_block) {
        if (new_block) {
            ++block->shared_count;
        }
    }
};


template<typename T>
class WeakPtr {
 public:
    WeakPtr() = default;

    WeakPtr(std::nullptr_t) noexcept : WeakPtr() {}

    WeakPtr(const WeakPtr<T>& wptr) noexcept : WeakPtr(wptr.block) {}

    WeakPtr& operator=(const WeakPtr<T>& wptr) noexcept {
        if (block == wptr.block) {
            return *this;
        }

        WeakPtr<T> tmp_block(wptr.block);
        Swap(tmp_block);
        return *this;
    }

    WeakPtr(const SharedPtr<T>& sptr) : WeakPtr(sptr.block) {}

    WeakPtr(WeakPtr&& wptr) noexcept : block(wptr.block) {
        wptr.block = nullptr;
    }

    WeakPtr& operator=(WeakPtr&& wptr) noexcept  {
        if (block == wptr.block) {
            wptr.block = nullptr;
            return *this;
        }

        WeakPtr<T> tmp(std::move(wptr));
        Swap(tmp);
        return *this;
    } 

    template<typename U>
    operator WeakPtr<U> () const noexcept {
        WeakPtr<U> wptr;
        wptr.block = block;
        return wptr;
    }

    void Reset() noexcept {
        this->~WeakPtr<T>();
        block = nullptr;
    }

    constexpr void Swap(WeakPtr<T>& wptr) noexcept {
        std::swap(wptr.block, block);
    }

    constexpr size_t UseCount() const noexcept {
        return (block) ? block->shared_count : 0;
    }

    constexpr bool Expired() const noexcept {
        if (block) {
            return block->shared_count == 0;
        }
        return true;
    }

    SharedPtr<T> Lock() const noexcept {
        SharedPtr<T> sptr;
        if (block) {
            if (block->shared_count == 0) {
                return sptr;
            }
            ++block->shared_count;
            sptr.block = block;
        }
        return sptr;
    }

    ~WeakPtr() noexcept {
        if (block) {
            if (block->weak_count <= 1) {
                block->weak_count = 0;
                if (!block->shared_count) {
                    delete block;
                }
            }
            else {
                --block->weak_count;
            }
        }
    }

 private:
    friend SharedPtr<T>;

    typename SharedPtr<T>::ControlBlock* block = nullptr;

    WeakPtr(typename SharedPtr<T>::ControlBlock* block_) : block(block_) {
        if (block_) {
            ++block->weak_count;
        }
    }
};

template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args) {
    T* ptr = new T(std::forward<Args>(args)...);
    return SharedPtr(ptr);
}
