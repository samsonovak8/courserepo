#pragma once

#include <cstring>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <compare>

class String {
 public:
    //1.
    String();
    String(size_t size, char a);
    String(const char* pointer, size_t size);
    String(const char* src);
    String(const String& src);

    String& operator=(const String& src);

    //3.
    char& operator[](size_t i);
    const char& operator[](size_t i) const;

    //4.
    char& Front();
    const char& Front() const;
    char& Back();
    const char& Back() const;

    //5.
    const char* CStr() const noexcept;
    const char* Data() const noexcept;
    
    //6.
    bool Empty() const noexcept;
    
    //7.
    size_t Size() const noexcept;
    size_t Length() const noexcept;

    //8.
    size_t Capacity() const noexcept;

    //9.
    void Clear() noexcept;

    //10.
    void Swap(String& other) noexcept;

    //11.
    void PopBack();

    //12.
    void PushBack(char a);

    //13.
    String& operator+=(const String& other);

    //14.
    void Resize(size_t new_size, char a);

    //15.
    void Reserve(size_t capacity);

    //16.
    void ShrinkToFit();

    //17.
   friend String operator+(const String& first, const String& second);

   //18.
   friend bool operator==(const String& first, const String& second);
   friend std::strong_ordering operator<=>(const String& first, const String& second);

   //19.
   friend std::ostream& operator<<(std::ostream& stream, const String& str);
   friend std::istream& operator>>(std::istream& stream, String& str);

    //======== Additional ========
    static char* AllocateMem(size_t capacity);
    void ReallocateMem(size_t new_cap);
    void DeletePointer(std::nullptr_t);
    void DeletePointer(char* ptr);

    ~String();

   
 private:
    size_t size_ = 0;
    size_t cap_  = 0;
    char* data   = nullptr;
};