#include <maths/vec2i.h>
#include <maths/vec2f.h>
#include <gtest/gtest.h>

struct Vec2iOperationFixture :
	public ::testing::TestWithParam<std::pair<core::Vec2i, core::Vec2i>>
{

};

TEST_P(Vec2iOperationFixture, Add)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 + v2;
	EXPECT_EQ(result.x, v1.x + v2.x);
	EXPECT_EQ(result.y, v1.y + v2.y);
}

TEST_P(Vec2iOperationFixture, Sub)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 - v2;
	EXPECT_EQ(result.x, v1.x - v2.x);
	EXPECT_EQ(result.y, v1.y - v2.y);

	const auto neg1 = -v1;
	const auto neg2 = -v2;
	EXPECT_EQ(neg1.x, -v1.x);
	EXPECT_EQ(neg1.y, -v1.y);
	EXPECT_EQ(neg2.x, -v2.x);
	EXPECT_EQ(neg2.y, -v2.y);
}

TEST_P(Vec2iOperationFixture, mutiplie)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 * v2.x;
	EXPECT_EQ(result.x, v1.x * v2.x);
	EXPECT_EQ(result.y, v1.y * v2.x);
}

TEST_P(Vec2iOperationFixture, divide)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 / v2.x;
	
	
	if (v2.x == 0)
	{
		EXPECT_EQ(result.x, 0);
		EXPECT_EQ(result.y, 0);
	}
	else
	{
		EXPECT_EQ(result.x, v1.x / v2.x);
		EXPECT_EQ(result.y, v1.y / v2.x);
	}
}

TEST_P(Vec2iOperationFixture, Dot)
{
	auto [v1, v2] = GetParam();
	const auto result = core::Vec2i::Dot(v1, v2);
	EXPECT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}

TEST_P(Vec2iOperationFixture, Perpendicular)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Perpendicular();
	const auto p2 = v2.Perpendicular();
	EXPECT_EQ(core::Vec2i::Dot(v1, p1), 0);
	EXPECT_EQ(core::Vec2i::Dot(v2, p2), 0);

	const auto r1 = v1.Perpendicular2();
	const auto r2 = v2.Perpendicular2();
	EXPECT_EQ(core::Vec2i::Dot(v1, r1), 0);
	EXPECT_EQ(core::Vec2i::Dot(v2, r2), 0);
}

INSTANTIATE_TEST_SUITE_P(AllNumbers,
	Vec2iOperationFixture,
	testing::Values(
		std::pair{ core::Vec2i{1,3}, core::Vec2i{2,-4} },
		std::pair{ core::Vec2i{-10, 15}, core::Vec2i{-25, -35} },
		std::pair{ core::Vec2i{}, core::Vec2i{} },
		std::pair{ core::Vec2i{1, 2}, core::Vec2i{} },
		std::pair{ core::Vec2i{}, core::Vec2i{1, 2} }
	)
);


struct Vec2fOperationFixture :
	public ::testing::TestWithParam<std::pair<core::Vec2f, core::Vec2f>>
{

};

TEST_P(Vec2fOperationFixture, Add)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 + v2;
	EXPECT_FLOAT_EQ(result.x, v1.x + v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y + v2.y);
}

TEST_P(Vec2fOperationFixture, Sub)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 - v2;
	EXPECT_FLOAT_EQ(result.x, v1.x - v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y - v2.y);

	const auto neg1 = -v1;
	const auto neg2 = -v2;
	EXPECT_FLOAT_EQ(neg1.x, -v1.x);
	EXPECT_FLOAT_EQ(neg1.y, -v1.y);
	EXPECT_FLOAT_EQ(neg2.x, -v2.x);
	EXPECT_FLOAT_EQ(neg2.y, -v2.y);
}

TEST_P(Vec2fOperationFixture, mutiplie)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 * v2.x;
	
	EXPECT_FLOAT_EQ(result.x, v1.x * v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y * v2.x);
	
}

TEST_P(Vec2fOperationFixture, divide)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 / v2.x;


	if (v2.x == 0)
	{
		EXPECT_FLOAT_EQ(result.x, 0);
		EXPECT_FLOAT_EQ(result.y, 0);
	}
	else
	{
		EXPECT_FLOAT_EQ(result.x, v1.x / v2.x);
		EXPECT_FLOAT_EQ(result.y, v1.y / v2.x);
	}
}



TEST_P(Vec2fOperationFixture, Dot)
{
	auto [v1, v2] = GetParam();
	const auto result = core::Vec2f::Dot(v1, v2);
	EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}

TEST_P(Vec2fOperationFixture, Perpendicular)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Perpendicular();
	const auto p2 = v2.Perpendicular();
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v1, p1), 0);
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v2, p2), 0);

	const auto r1 = v1.Perpendicular2();
	const auto r2 = v2.Perpendicular2();
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v1, r1), 0);
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v2, r2), 0);
}

TEST_P(Vec2fOperationFixture, lerp)
{

	auto [v1, v2] = GetParam();
	const auto p1 = v1.lerp(v2, 1);
	const auto p2 = v1.lerp(v2, 0);

	EXPECT_FLOAT_EQ(p1.x, v2.x);
	EXPECT_FLOAT_EQ(p2.x, v1.x);

	EXPECT_FLOAT_EQ(p1.y, v2.y);
	EXPECT_FLOAT_EQ(p2.y, v1.y);

}

TEST_P(Vec2fOperationFixture, magintude)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Magnitude();
	const auto p2 = v2.Magnitude();

	EXPECT_FLOAT_EQ(p1, sqrt(v1.x * v1.x + v1.y * v1.y));
	EXPECT_FLOAT_EQ(p2, sqrt(v2.x * v2.x + v2.y * v2.y));
}


TEST_P(Vec2fOperationFixture, squaredMagnitude)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.squaredMagnitude();
	const auto p2 = v2.squaredMagnitude();
	EXPECT_FLOAT_EQ(p1, v1.x * v1.x + v1.y * v1.y);
	EXPECT_FLOAT_EQ(p2, v2.x * v2.x + v2.y * v2.y);
		
}


TEST_P(Vec2fOperationFixture, normalized)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Normalized();
	const auto p2 = v2.Normalized();
	if (v1.x == 0 || v1.y == 0 )
	{
		EXPECT_FLOAT_EQ(p1.x, 0);
		EXPECT_FLOAT_EQ(p1.y, 0);
	}
	else
	{
		EXPECT_FLOAT_EQ(p1.Magnitude(), 1);

	}
	if (v2.x == 0 || v2.y == 0)
	{
		EXPECT_FLOAT_EQ(p2.x, 0);
		EXPECT_FLOAT_EQ(p2.y, 0);
	}
	else
	{
		EXPECT_FLOAT_EQ(p2.Magnitude(), 1);
	}
	

}


INSTANTIATE_TEST_SUITE_P(AllNumbers,
	Vec2fOperationFixture,
	testing::Values(
		std::pair{ core::Vec2f{1.4,3}, core::Vec2f{2,-4.4} },
		std::pair{ core::Vec2f{-10, 15}, core::Vec2f{-25, -35} },
		std::pair{ core::Vec2f{}, core::Vec2f{} },
		std::pair{ core::Vec2f{1, 2}, core::Vec2f{} },
		std::pair{ core::Vec2f{}, core::Vec2f{1.1, 2} }
	)
);