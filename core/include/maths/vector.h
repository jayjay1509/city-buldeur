#ifndef COREMATHS_VECTOR_H
#define COREMATHS_VECTOR_H



#include <vector>
#include <stdexcept>


namespace core
{
    template<typename T, class Allocator = std::allocator<T>, std::size_t GrowthDividend = 3, std::size_t GrowthDivisor = 2 >
    class Vector {
    private:
        std::vector<T, Allocator> data_;

    public:
        // Constructeur par défaut
        Vector() = default;

        
        explicit Vector(typename std::vector<T, Allocator>::size_type count)
            : data_(count) {}

        
        Vector(typename std::vector<T, Allocator>::size_type count, const T& value)
            : data_(count, value) {}

        
        void push_back(const T& value) {
            data_.push_back(value);
            if (data_.size() == data_.capacity()) {
                data_.reserve(data_.capacity() * GrowthDividend/ GrowthDivisor);
            }
        }

        void pop_back() {
            if (data_.empty()) {
                throw std::out_of_range("Vector is empty");
            }
            data_.pop_back();
        }
        typename std::vector<T, Allocator>::reference at(typename std::vector<T, Allocator>::size_type index) {
            if (index >= data_.size()) {
                throw std::out_of_range("Index out of range");
            }
            return data_.at(index);
        }

        typename std::vector<T, Allocator>::const_reference at(typename std::vector<T, Allocator>::size_type index) const {
            if (index >= data_.size()) {
                throw std::out_of_range("Index out of range");
            }
            return data_.at(index);
        }

        std::size_t size() const {
            return data_.size();
        }

        std::size_t capacity() const {
            return data_.capacity();
        }
    };
}

#endif