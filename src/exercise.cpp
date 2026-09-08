#include "project/exercise.hpp"
#include <algorithm>
#include <utility>
#include <stdexcept>

// TODO: Implement default constructor.
DynamicBuffer::DynamicBuffer() : data_(nullptr), size_(0) {
}

// TODO: Implement allocation and initialization.
// Use a C++ array allocated with new[] and zero-initialize the contents.
DynamicBuffer::DynamicBuffer(size_t capacity) : data_(nullptr), size_(0) {
    if (capacity == 0) {
        return;
    }

    data_ = new int[capacity]();
    size_ = capacity;
}

// TODO: Implement deep-copy constructor.
DynamicBuffer::DynamicBuffer(const DynamicBuffer& other) : data_(nullptr), size_(0) {
    copyFrom(other);
}

// TODO: Implement move constructor.
DynamicBuffer::DynamicBuffer(DynamicBuffer&& other) noexcept : data_(nullptr), size_(0) {
    data_ = other.data_;
    size_ = other.size_;

    other.data_ = nullptr;
    other.size_ = 0;
}

// TODO: Implement destructor with proper cleanup.
DynamicBuffer::~DynamicBuffer() {
    release();
}

// TODO: Implement copy assignment with self-assignment protection.
DynamicBuffer& DynamicBuffer::operator=(const DynamicBuffer& other) {
    if (this != &other) {
        DynamicBuffer temp(other);
        swap(temp);
    }

    return *this;
}

// TODO: Implement move assignment.
DynamicBuffer& DynamicBuffer::operator=(DynamicBuffer&& other) noexcept {
    if (this != &other) {
        release();
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    }

    return *this;
}

// TODO: Return the current managed size.
size_t DynamicBuffer::size() const noexcept {
    return size_;
}

// TODO: Return true if the buffer is empty.
bool DynamicBuffer::empty() const noexcept {
    return size_ == 0;
}

// TODO: Implement resize with resource ownership and exception safety.
// Keep all existing values up to the minimum of old and new sizes.
void DynamicBuffer::resize(size_t newSize) {
    if (newSize == size_) {
        return;
    }

    int* newData = (newSize == 0) ? nullptr : new int[newSize]();
    const size_t copyCount = std::min(size_, newSize);

    if (newData != nullptr && data_ != nullptr) {
        std::copy(data_, data_ + copyCount, newData);
    }

    delete[] data_;
    data_ = newData;
    size_ = newSize;
}

// TODO: Fill all elements with the given value.
void DynamicBuffer::fill(int value) {
    if (data_ != nullptr) {
        std::fill(data_, data_ + size_, value);
    }
}

// TODO: Validate index and assign the value.
void DynamicBuffer::setAt(size_t index, int value) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    data_[index] = value;
}

// TODO: Return element at index with bounds checking.
int DynamicBuffer::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    return data_[index];
}

// TODO: Return a reference without bounds checking.
int& DynamicBuffer::operator[](size_t index) {
    return data_[index];
}

// TODO: Return const reference without bounds checking.
const int& DynamicBuffer::operator[](size_t index) const {
    return data_[index];
}

// TODO: Compare size and elements.
bool DynamicBuffer::operator==(const DynamicBuffer& other) const {
    if (size_ != other.size_) {
        return false;
    }

    if (data_ == other.data_) {
        return true;
    }

    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }

    return true;
}

// TODO: Implement inequality comparison.
bool DynamicBuffer::operator!=(const DynamicBuffer& other) const {
    return !(*this == other);
}

// TODO: Return true when the buffer owns valid memory.
DynamicBuffer::operator bool() const noexcept {
    return data_ != nullptr;
}

// TODO: Delete allocated memory and reset state.
void DynamicBuffer::release() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
}

// TODO: Deep-copy the other object's contents.
void DynamicBuffer::copyFrom(const DynamicBuffer& other) {
    if (this == &other) {
        return;
    }

    release();

    if (other.size_ == 0) {
        return;
    }

    data_ = new int[other.size_]();
    size_ = other.size_;
    std::copy(other.data_, other.data_ + other.size_, data_);
}

// TODO: Swap the resources of two buffers.
void DynamicBuffer::swap(DynamicBuffer& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
}
