#ifndef CORE_MATHS_VEC2I_H_
#define CORE_MATHS_VEC2I_H_

namespace core 
{
	/**
	 * \brief Vec2i is a mathematical object represented
	 */
	struct Vec2i
    {
        int x = 0, y = 0;

        constexpr Vec2i operator+(Vec2i other) const
        {
            return { x + other.x, y + other.y };
        }

        constexpr Vec2i operator-(Vec2i other) const
        {
            return { x - other.x, y - other.y };
        }

        constexpr Vec2i operator-() const
        {
            return { -x, -y };
        }
        static constexpr int Dot(Vec2i v1, Vec2i v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        constexpr Vec2i Perpendicular() const
        {
            return { -y, x };
        }
        constexpr Vec2i Perpendicular2() const
        {
            return { y, -x };
        }

        constexpr Vec2i operator*(int scalar) const
        {
            return { scalar * x ,y * scalar };
        }

        constexpr Vec2i operator/(int scalar) const
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


    }; // struct Vec2i
    
} // namespace core





#endif  //CORE_MATHS_VEC2I.H_