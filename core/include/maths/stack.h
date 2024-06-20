
#include <vector>
#include <array>
#include <stdexcept>

namespace core
{

#include <array>
#include <stdexcept>

    template<typename T, std::size_t Size>
    class FixedStack {
    private:
        std::array<T, Size> data;
        std::size_t top;

    public:
        FixedStack() : top(0) {}

        void push(const T& value) {
            if (top >= Size) {
                throw std::overflow_error("Stack overflow");
            }
            data[top++] = value;
        }

        void pop() {
            if (top == 0) {
                throw std::underflow_error("Stack underflow");
            }
            --top;
        }

        T& front() {
            if (top == 0) {
                throw std::underflow_error("Stack is empty");
            }
            return data[top - 1];
        }

        bool isEmpty() const {
            return top == 0;
        }

        bool isFull() const {
            return top >= Size;
        }

        std::size_t size() const {
            return top;
        }
        auto capacity()
        {
            return data.size();
        }

    };


    template<typename T>
    class DynamicStack {
    private:
        std::vector<T> data;

    public:
        void push(const T& value) {
            data.push_back(value);
        }

        void pop() {
            if (data.empty()) {
                throw std::underflow_error("Stack underflow");
            }
            data.pop_back();
        }

        T& front() {
            if (data.empty()) {
                throw std::underflow_error("Stack is empty");
            }
            return data.back();
        }

        bool isEmpty() const {
            return data.empty();
        }

        std::size_t size() const {
            return data.size();
        }
    };


}
   
    
    