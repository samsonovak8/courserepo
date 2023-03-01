#pragma once

class Any {
 public:
    Any() = default;

    template<typename T>
    Any(const T& object_) : ptr(new Derived<T>(object_)) {}

    Any(const Any& any) {
        delete ptr;
        ptr = any.ptr->clone();
    }

    Any(Any&& any) : ptr(any.ptr) {
        any.ptr = nullptr;
    } 

    template<typename T>
    Any& operator=(const T& object_) {
        Any new_any(object_);
        Swap(new_any);
        return *this;
    }

    Any& operator=(const Any& any) {
        Any new_any(any);
        Swap(new_any);
        return *this;
    }

    Any& operator=(Any&& any) {
        Any new_any(std::forward<Any>(any));
        Swap(new_any);
        return *this;
    }

    void Reset() {
        if (ptr) {
            delete ptr;
        }
        ptr = nullptr;
    }

    void Swap(Any& any) {
        std::swap(ptr, any.ptr);
    }

    bool HasValue() {
        return (ptr != nullptr);
    }

    ~Any() {
        if (ptr) {
            delete ptr;
        }
    }

 private:
    struct Base {
        virtual Base* clone() = 0;
        virtual ~Base() = default;
    };
    
    template<typename T>
    struct Derived : Base {
        T object;

        Derived(const T& object_) : object(object_) {}

        Base* clone() override {
            return new Derived<T>(object);
        }
    };

    Base* ptr = nullptr;

    template<class T>
    friend T AnyCast(const Any& value);
};

template<typename T, typename... Args>
Any&& MakeAny(Args&&... args) {
    Any any;
    any.ptr = new Any::Derived<T>(std::forward(args)...);
    return std::forward<Any>(any);
}

struct bad_any_cast : public std::bad_cast {
    const char* what() const noexcept override {
        return "bad_any_cast";
    }
};

template<class T>
T AnyCast(const Any& value) {
    if(!value.ptr) {
        throw bad_any_cast();
    }

    try {
        return dynamic_cast<Any::Derived<T>&>(*value.ptr).object;
    }
    catch (const std::bad_cast& exception) {
        throw bad_any_cast();
    }
}

