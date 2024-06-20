#include <maths/queue.h>
#include <gtest/gtest.h>

class QueueFixture : public ::testing::TestWithParam<std::pair<core::Queue<int>, std::vector<int>>>
{

};

//Test case for push and front functions
TEST_P(QueueFixture, PushAndFront) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.enqueue(value);
    }

    //Ensure front() throws an exception on an empty vector
    if (!vector.empty()) {
        EXPECT_EQ(queue.front(), vector.front());
    }
    else {
        EXPECT_THROW(queue.front(), std::underflow_error);
    }
}

//Test case for pop function
TEST_P(QueueFixture, Pop) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.enqueue(value);
    }

    //Ensure pop() throws an exception on an empty queue
    if (!vector.empty()) {
        queue.dequeue();
        vector.erase(vector.begin());

        //Ensure front() throws an exception on an empty vector
        if (!vector.empty()) {
            EXPECT_EQ(queue.front(), vector.front());
        }
        else {
            EXPECT_THROW(queue.front(), std::underflow_error);
        }
    }
    else {
        EXPECT_THROW(queue.dequeue(), std::underflow_error);
    }
}


INSTANTIATE_TEST_SUITE_P(Numbers, QueueFixture,
    testing::Values(
        std::make_pair(core::Queue<int>(), std::vector<int>{1, 4, 5, 123, 0, 3, -1}),
        std::make_pair(core::Queue<int>(), std::vector<int>{5, 123, 3, -1}),
        std::make_pair(core::Queue<int>(), std::vector<int>{})
    )
);


class QueueFix : public ::testing::TestWithParam<std::pair<core::FixedQueue<int,4>, std::vector<int>>>
{

};

//Test case for push and front functions
TEST_P(QueueFix, PushAndFront) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.enqueue(value);
    }

    //Ensure front() throws an exception on an empty vector
    if (!vector.empty()) {
        EXPECT_EQ(queue.front(), vector.front());
    }
    else {
        EXPECT_THROW(queue.front(), std::underflow_error);
    }
}

//Test case for pop function
TEST_P(QueueFix, Pop) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.enqueue(value);
    }

    //Ensure pop() throws an exception on an empty queue
    if (!vector.empty()) {
        queue.dequeue();
        vector.erase(vector.begin());

        //Ensure front() throws an exception on an empty vector
        if (!vector.empty()) {
            EXPECT_EQ(queue.front(), vector.front());
        }
        else {
            EXPECT_THROW(queue.front(), std::underflow_error);
        }
    }
    else {
        EXPECT_THROW(queue.dequeue(), std::underflow_error);
    }
}


INSTANTIATE_TEST_SUITE_P(Numbers, QueueFix,
    ::testing::Values(
        std::make_pair(core::FixedQueue<int, 4>(), std::vector<int>{1, 4, 5, 123}),
        std::make_pair(core::FixedQueue<int, 4>(), std::vector<int>{5, 123, 3, -1}),
        std::make_pair(core::FixedQueue<int, 4>(), std::vector<int>{})
    )
);