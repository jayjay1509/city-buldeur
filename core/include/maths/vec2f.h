#ifndef CORE_MATHS_VEC2F_H_
#define CORE_MATHS_VEC2F_H_

#include <cmath>

namespace core
{
    /**
     * \brief Vec2f is a mathematical object represented
     */
    struct Vec2f
    {
        float x = 0, y = 0;

        constexpr Vec2f operator+(Vec2f other) const
        {
            return { x + other.x, y + other.y };
        }

        constexpr Vec2f operator-(Vec2f other) const
        {
            return { x - other.x, y - other.y };
        }

        constexpr Vec2f operator-() const
        {
            return { -x, -y };
        }

        constexpr Vec2f operator*(float scalar) const
        {
            return { scalar * x ,y * scalar };
        }

        constexpr Vec2f operator/(float scalar) const
        {
            if (scalar == 0)
            {
                return { 0, 0 };
            }
            else
            {
                return { x / scalar , y / scalar };
            }
        }

        constexpr Vec2f lerp( Vec2f b, float t) const
        {
            return { x + (b.x - x) * t , y + (b.y - y) * t };
        }

        [[nodiscard]] float squaredMagnitude() const
        {
             return  (x * x + y * y);
        }


        [[nodiscard]] float Magnitude() const
        {
            return  std::sqrt(squaredMagnitude());
        }



        [[nodiscard]] Vec2f Normalized() const
        {
	        if (x == 0 || y == 0)
	        {
                return { 0, 0 };
	        }
	        else
	        {
                return  { x / Magnitude() , y / Magnitude() };
	        }
            
        }

        static float Dot(const Vec2f& v1, const Vec2f& v2)
        {
            return (v1.x * v2.x) + (v1.y * v2.y);
        }

        constexpr Vec2f Perpendicular() const
        {
            return { -y, x };
        }
        constexpr Vec2f Perpendicular2() const
        {
            return { y, -x };
        }
    }; // struct Vec2f

    //Operator overload for multiplication
    constexpr Vec2f operator*(float scalar, const Vec2f& vec)
    {
        return { scalar * vec.x, scalar * vec.y };
    }

} // namespace core
#endif  // CORE_MATHS_VEC2F_H_
