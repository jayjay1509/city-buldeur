
#define COREMATHS_BASICVECTOR_H

#include <algorithm>
#include <vector>
#include <array>
#include <stdexcept>
#include <iostream>
#include <variant>

namespace core
{
    template <typename T, size_t N>
    class BasicVector {
    private:
        std::variant<std::array<T, N>, std::vector<T>> data_;

        bool is_small() const {
            return N > 0;
        }

    public:
        BasicVector() {
            if (is_small()) {
                data_ = std::array<T, N>();
            }
            else {
                data_ = std::vector<T>();
            }
        }

        void push_back(const T& value) {
            if (is_small()) {
                auto& arr = std::get<std::array<T, N>>(data_);
                auto it = std::find(arr.begin(), arr.end(), T());
                if (it != arr.end()) {
                    *it = value;
                }
                else {
                    throw std::overflow_error("Array is full");
                }
            }
            else {
                std::get<std::vector<T>>(data_).push_back(value);
            }
        }

        void pop_back() {
            if (is_small()) {
                auto& arr = std::get<std::array<T, N>>(data_);
                for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
                    if (*it != T()) {
                        *it = T();
                        return;
                    }
                }
                throw std::underflow_error("Array is empty");
            }
            else {
                auto& vec = std::get<std::vector<T>>(data_);
                if (vec.empty()) {
                    throw std::underflow_error("Vector is empty");
                }
                vec.pop_back();
            }
        }

        T& at(size_t index) {
            if (is_small()) {
                if (index >= N) {
                    throw std::out_of_range("Index out of range");
                }
                return std::get<std::array<T, N>>(data_)[index];
            }
            else {
                auto& vec = std::get<std::vector<T>>(data_);
                if (index >= vec.size()) {
                    throw std::out_of_range("Index out of range");
                }
                return vec[index];
            }
        }

        const T& at(size_t index) const {
            if (is_small()) {
                if (index >= N) {
                    throw std::out_of_range("Index out of range");
                }
                return std::get<std::array<T, N>>(data_)[index];
            }
            else {
                const auto& vec = std::get<std::vector<T>>(data_);
                if (index >= vec.size()) {
                    throw std::out_of_range("Index out of range");
                }
                return vec[index];
            }
        }

        size_t size() const {
            if (is_small()) {
                const auto& arr = std::get<std::array<T, N>>(data_);
                return std::count_if(arr.begin(), arr.end(), [](const T& val) { return val != T(); });
            }
            else {
                return std::get<std::vector<T>>(data_).size();
            }
        }

        bool empty() const {
            if (is_small()) {
                const auto& arr = std::get<std::array<T, N>>(data_);
                return std::all_of(arr.begin(), arr.end(), [](const T& val) { return val == T(); });
            }
            else {
                return std::get<std::vector<T>>(data_).empty();
            }
        }

        void clear() {
            if (is_small()) {
                auto& arr = std::get<std::array<T, N>>(data_);
                std::fill(arr.begin(), arr.end(), T());
            }
            else {
                std::get<std::vector<T>>(data_).clear();
            }
        }

        /*friend std::ostream& operator<<(std::ostream& os, const BasicVector& vec) {
            if (vec.is_small()) {
                const auto& arr = std::get<std::array<T, N>>(vec.data_);
                for (const auto& elem : arr) {
                    if (elem != T()) {
                        os << elem << " ";
                    }
                }
            }
            else {
                const auto& vec_data = std::get<std::vector<T>>(vec.data_);
                for (const auto& elem : vec_data) {
                    os << elem << " ";
                }
            }
            return os;
        }*/
    };
}
