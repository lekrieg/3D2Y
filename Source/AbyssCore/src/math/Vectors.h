#ifndef VECTORS_H
#define VECTORS_H

namespace core
{
	namespace abyss_math
	{
#define RAD2DEG(x) ((x) * 57.295754f)
#define DEG2RAD(x) ((x) * 0.0174533f)

		template <typename T>
		struct Vec2
		{
			union
			{
				struct
				{
					T x;
					T y;
				};
				T asArray[2];
			};

			T& operator[] (int i)
			{
				return asArray[i];
			}

			Vec2() : x(0.0f), y(0.0f)
			{

			}

			Vec2(T x, T y) : x(x), y(y)
			{

			}
		};

		template<typename T>
		Vec2<T> operator+ (const Vec2<T>& l, const Vec2<T>& r)
		{
			return { l.x + r.x, l.y + r.y };
		}

		template<typename T>
		Vec2<T> operator- (const Vec2<T>& l, const Vec2<T>& r)
		{
			return { l.x - r.x, l.y - r.y };
		}

		template<typename T>
		Vec2<T> operator* (const Vec2<T>& l, const Vec2<T>& r)
		{
			return { l.x * r.x, l.y * r.y };
		}

		template<typename T>
		Vec2<T> operator* (const Vec2<T>& l, float r)
		{
			return { l.x * r, l.y * r };
		}

		template<typename T>
		bool operator== (const Vec2<T>& l, const Vec2<T>& r)
		{
			return CMP(l.x, r.x) && CMP(l.y, r.y);
		}

		template<typename T>
		bool operator!= (const Vec2<T>& l, const Vec2<T>& r)
		{
			return !(l == r);
		}

		template<typename T>
		float Dot(const Vec2<T>& l, const Vec2<T>& r)
		{
			return l.x * r.x + l.y * r.y;
		}

		template<typename T>
		float Magnitude(const Vec2<T>& v)
		{
			return sqrtf(Dot(v, v));
		}

		template<typename T>
		float MagnitudeSq(const Vec2<T>& v)
		{
			return Dot(v, v);
		}

		template<typename T>
		void Normalize(Vec2<T>& v)
		{
			v = v * (1.0f / Magnitude(v));
		}

		template<typename T>
		Vec2<T> Normalized(const Vec2<T>& v)
		{
			return v * (1.0f / Magnitude(v));
		}

		template<typename T>
		float Cross(const Vec2<T>& a, const Vec2<T>& b)
		{
			return a.x * b.y - a.y * b.x;
		}

		template<typename T>
		float Angle(const Vec2<T>& l, const Vec2<T>& r)
		{
			Vec2 d = r - l;
			return atan2f(d.y, d.x);

			float m = sqrtf(MagnitudeSq(l) * MagnitudeSq(r));
			return acos(Dot(l, r) / m);
		}
	}
}

#endif // !VECTORS_H
