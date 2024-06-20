//#ifndef FIXED_VECTOR_H // Added include guard to prevent multiple inclusions.
//#define FIXED_VECTOR_H
//
//#include <vector>
//#include <initializer_list>
//#include <cstdlib>
//
//namespace core
//{
//    template<typename T, std::size_t Capacity>
//    class FixedVector
//    {
//    public:
//        FixedVector() noexcept
//        {
//            data_.reserve(Capacity); // Properly initialize the capacity.
//        }
//
//        FixedVector(std::initializer_list<T> list)
//        {
//            if (list.size() > Capacity)
//            {
//                std::terminate(); // Terminate if the list exceeds capacity.
//            }
//            data_.reserve(Capacity); // Reserve capacity.
//            data_.assign(list.begin(), list.end()); // Use assign to initialize the vector with the list.
//        }
//
//        auto begin() noexcept
//        {
//            return data_.begin(); // Return the begin iterator.
//        }
//
//        auto end() noexcept
//        {
//            return data_.end(); // Return the end iterator.
//        }
//
//        auto cbegin() const noexcept
//        {
//            return data_.cbegin(); // Return the const begin iterator.
//        }
//
//        auto cend() const noexcept
//        {
//            return data_.cend(); // Return the const end iterator.
//        }
//
//        void push_back(const T& value)
//        {
//            if (data_.size() == Capacity)
//            {
//                std::terminate(); // Terminate if the size exceeds capacity.
//            }
//            data_.push_back(value); // Add the value.
//        }
//
//        void push_back(T&& value)
//        {
//            if (data_.size() == Capacity)
//            {
//                std::terminate(); // Terminate if the size exceeds capacity.
//            }
//            data_.push_back(std::move(value)); // Add the value using move semantics.
//        }
//
//        void clear() noexcept
//        {
//            data_.clear(); // Clear the vector.
//        }
//
//        T& operator[](std::size_t pos)
//        {
//            return data_[pos]; // Access the element for modification.
//        }
//
//        const T& operator[](std::size_t pos) const
//        {
//            return data_[pos]; // Access the element for reading.
//        }
//
//        auto insert(typename std::vector<T>::const_iterator pos, const T& value)
//        {
//            if (data_.size() == Capacity)
//            {
//                std::terminate(); // Terminate if the size exceeds capacity.
//            }
//            return data_.insert(pos, value); // Insert the value.
//        }
//
//        auto insert(typename std::vector<T>::const_iterator pos, T&& value)
//        {
//            if (data_.size() == Capacity)
//            {
//                std::terminate(); // Terminate if the size exceeds capacity.
//            }
//            return data_.insert(pos, std::move(value)); // Insert the value using move semantics.
//        }
//
//        auto erase(typename std::vector<T>::iterator pos)
//        {
//            return data_.erase(pos); // Erase the element.
//        }
//
//        auto erase(typename std::vector<T>::const_iterator pos)
//        {
//            return data_.erase(pos); // Erase the element.
//        }
//
//        constexpr std::size_t capacity() const noexcept
//        {
//            if (data_.capacity() != Capacity)
//            {
//                std::terminate(); // Terminate if the capacity is incorrect.
//            }
//            return Capacity; // Return the capacity.
//        }
//
//        std::size_t size() const noexcept
//        {
//            return data_.size(); // Return the current size.
//        }
//
//    private:
//        std::vector<T> data_; // Use a vector to store the data.
//    };
//}
//
//#endif // FIXED_VECTOR_H
