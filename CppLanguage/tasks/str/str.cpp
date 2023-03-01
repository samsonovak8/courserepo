#include "str.hpp"

String::String() : size_(0), cap_(0), data(nullptr) {}

String::String(size_t size, char a) : size_(size), cap_(size), data(new char[size + 1]) {
    memset(data, a, sizeof(a) * size);
    data[size] = '\0';
} 

String::String(const char* src, size_t size) : size_(size), cap_(size), data(new char[size + 1]) {
    if (src) {
        memcpy(data, src, sizeof(*src) * size);
        data[size] = '\0';
    }
}

String::String(const char* src) : size_(strlen(src)), cap_(size_), data(new char[cap_ + 1]) {
    if (src) {
        memcpy(data, src, sizeof(*data) * (size_ + 1));
    }
}

String::String(const String& src) : size_(src.size_), cap_(src.cap_), data(new char[cap_ + 1]) {
    if (src.data) {
        memcpy(data, src.data, sizeof(*src.data) * (size_ + 1));
    }
}

String& String::operator=(const String& src) {
    size_ = src.size_;
    cap_  = src.cap_;
    if (src.data == data) {
        return *this;
    }

    char* new_data = new char[cap_ + 1];
    if (src.data) {
        memcpy(new_data, src.data, sizeof(*src.data) * (cap_ + 1));
    }
    delete[] data;
    data = new_data;
    return *this;

}

//================================

char& String::operator[](size_t i) {
    if (size_ == 0) {
        throw std::range_error("Accessing an element outside of bounds");
    }
    return data[i];
}

const char& String::operator[](size_t i) const {
    if (size_ == 0) {
        throw std::range_error("Accessing an element outside of bounds");
    }
    return data[i];
}

//================================

char& String::Front() {
    if (size_ == 0) {
        throw std::range_error("Accessing Front element of empty string");
    }
    return data[0];
}

const char& String::Front() const {
    if (size_ == 0) {
        throw std::range_error("Accessing Front element of empty string");
    }
    return data[0];
}

char& String::Back() {
    if (size_ == 0) {
        throw std::range_error("Accessing Back element of empty String");
    }
    return data[size_ - 1];
}

const char& String::Back() const {
    if (size_ == 0) {
        throw std::range_error("Accessing Back element of empty String");
    }
    return data[size_ - 1];
}
    

//================================

const char* String::CStr() const noexcept {
  return (size_) ? data : nullptr;
}

const char* String::Data() const noexcept {
    return (size_) ? data : nullptr;
}

//================================

bool String::Empty() const noexcept {
    return (size_ == 0);
}

//================================

size_t String::Size() const noexcept {
    return size_;
}

size_t String::Length() const noexcept {
    return size_;
}

//================================

size_t String::Capacity() const noexcept {
    return cap_;
}

//================================

void String::Clear() noexcept {
    if (size_ > 0) {
        data[0] = '\0';
        size_ = 0;
    }
}

//================================

void String::Swap(String& other) noexcept {
    std::swap(cap_, other.cap_);
    std::swap(size_, other.size_);
    std::swap(data, other.data);
}

//================================

void String::PopBack() {
    if (size_ == 0) {
        throw std::range_error("PopBack of empty string");
    }
    data[size_] = '\0';
    --size_;
}

//================================

void String::PushBack(char a) {
    if (size_ == cap_) {
        size_t new_cap = (cap_ == 0) ? 1 : (cap_ << 1);

        Reserve(new_cap);
    }
    data[size_++] = a;
    data[size_] = '\0';
}

//================================

String& String::operator+=(const String& other) {
    size_t new_size = size_ + other.size_;
    if (new_size > cap_) {
        size_t new_cap = (new_size == 0) ? 1:(new_size << 1);
        ReallocateMem(new_cap);
    }
    strncpy(data + size_, other.data, other.size_);
    size_ = new_size;
    data[new_size] = '\0';
    return *this;
}

//================================

void String::Resize(size_t new_size, char a) {
    if (size_ > new_size) {
        size_ = new_size;
        data[size_] = '\0';
    }

    if (size_ == new_size) {
        return;
    }

    ReallocateMem(new_size);
    memset(data + size_, a, (new_size - size_) * sizeof(*data) );
    size_ = new_size;
    data[size_] = '\0';
}

//================================

void String::Reserve(size_t capacity) {
    if (capacity > cap_) {
        ReallocateMem(capacity);
    }
}

//================================

void String::ShrinkToFit() {
    if (cap_ > size_) {
        ReallocateMem(size_);
    }
}

//================================

String operator+(const String& first, const String& second) {
    String sum(first.size_ + second.size_, 0);
    strncpy(sum.data, first.data, first.size_);
    strncpy(sum.data + first.size_, second.data, second.size_);
    sum.data[sum.size_] = '\0';
    return sum;
}

//================================

bool operator==(const String& first, const String& second) {
    if (first.size_ != second.size_) {
        return false;
    }

    const char* s1 = first.CStr();
    const char* s2 = second.CStr();
    
    for(size_t i = 0; i < first.Size(); ++i) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}

std::strong_ordering operator<=>(const String& first, const String& second) {
    if (first.size_ != 0 && second.size_ != 0) {
        auto answer = strcmp(first.data, second.data);
        return answer <=> 0;
    }
    return first.size_ <=> second.size_;
}

//================================

std::ostream& operator<<(std::ostream& stream, const String& str) {
    return (str.Size() == 0) ? stream : (stream << str.data);
}

std::istream& operator>>(std::istream& stream, String& str) {
    str.Clear();
    char buff[2] = "";
    stream.get(*buff);
    while(!(stream.eof() || isspace(*buff))) {
        str += buff;
        stream.get(*buff);
    }
    return stream;
}

//======== Additional ========

char* String::AllocateMem(size_t capacity) {
    if (capacity > 0) {
        return new char[capacity + 1];
    }
    return nullptr;
}

void String::ReallocateMem(size_t new_cap) {
    auto new_data = AllocateMem(new_cap);
    if (new_data && data) {
        strncpy(new_data, data, size_ + 1);
    }
    cap_ = new_cap;
    DeletePointer(data);
    data = new_data;
} 

void String::DeletePointer(std::nullptr_t) {}
void String::DeletePointer(char* ptr) {
    delete[] ptr;
}

String::~String() {
    delete[] data;
}
