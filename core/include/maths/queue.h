#ifndef COREMATHS_VEC2I_H
#define COREMATHS_VEC2I_H
#include <array>
#include <vector>
#include <stdexcept>

namespace core
{

    template <typename T, std::size_t Size>
    class FixedQueue {

    private:
        std::array<T, Size> data_;
        std::size_t front_index_;
        std::size_t back_index_;
        std::size_t count_;

    public:

        FixedQueue() : front_index_(0), back_index_(0), count_(0) {}

        void enqueue(const T& value) {
            if (count_ >= Size) {
                throw std::overflow_error("Queue overflow");
            }

            data_[back_index_] = value;
            back_index_ = (back_index_ + 1) % Size;
            ++count_;
        }

        void dequeue() {
            if (count_ == 0) {
                throw std::underflow_error("Queue underflow");
            }

            front_index_ = (front_index_ + 1) % Size;
            --count_;
        }

        T& front() {
            if (count_ == 0) {
                //todo: out of range
                throw std::underflow_error("Queue is empty");
            }

            return data_[front_index_];
        }

        [[nodiscard]] bool IsEmpty() const {

            return count_ == 0;
        }

        [[nodiscard]] bool IsFull() const {

            return count_ == Size;
        }

  
    };


        template <typename T>
        class Queue {
        public:
            void enqueue(const T& value) {
                if (size_ == data_.capacity()) {
                    // Double the capacity if full
                    size_t new_capacity = data_.capacity() ? data_.capacity() * 2 : 1;
                    std::vector<T> new_data(new_capacity);
                    for (size_t i = 0; i < size_; ++i) {
                        new_data[i] = std::move(data_[(front_ + i) % data_.capacity()]);
                    }
                    data_ = std::move(new_data);
                    front_ = 0;
                }
                data_[(front_ + size_) % data_.capacity()] = value;
                ++size_;
            }

            void dequeue() {
                if (IsEmpty()) {
                    throw std::underflow_error("Queue underflow");
                }
                front_ = (front_ + 1) % data_.capacity();
                --size_;
            }

            T& front() {
                if (IsEmpty()) {
                    throw std::underflow_error("Queue is empty");
                }
                return data_[front_];
            }

            [[nodiscard]] bool IsEmpty() const {
                return size_ == 0;
            }

            std::size_t size() const {
                return size_;
            }

            std::size_t capacity() const {
                return data_.capacity();
            }

        private:
            std::vector<T> data_;
            std::size_t front_ = 0;
            std::size_t size_ = 0;
        };

    } // namespace core

#endif // QUEUE_H