// Copyright (C) 2012 Jérôme Leclercq
// This file is part of the "Nazara Engine - Mathematics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/StringStream.hpp>
#include <algorithm>
#include <Nazara/Core/Debug.hpp>

#define F(a) static_cast<T>(a)

template<typename T>
NzRect<T>::NzRect()
{
}

template<typename T>
NzRect<T>::NzRect(T X, T Y, T Width, T Height)
{
	Set(X, Y, Width, Height);
}

template<typename T>
NzRect<T>::NzRect(const T vec[4])
{
	Set(vec);
}

template<typename T>
NzRect<T>::NzRect(const NzVector2<T>& vec1, const NzVector2<T>& vec2)
{
	Set(vec1, vec2);
}

template<typename T>
template<typename U>
NzRect<T>::NzRect(const NzRect<U>& rect)
{
	Set(rect);
}

template<typename T>
bool NzRect<T>::Contains(T X, T Y) const
{
	return X >= x && X < x+width &&
	       Y >= y && Y < y+height;
}

template<typename T>
bool NzRect<T>::Contains(const NzVector2<T>& point) const
{
	return Contains(point.x, point.y);
}

template<typename T>
bool NzRect<T>::Contains(const NzRect<T>& rect) const
{
	return Contains(rect.x, rect.y) &&
		   Contains(rect.x + rect.width, rect.y + rect.height);
}

template<typename T>
void NzRect<T>::ExtendTo(const NzVector2<T>& point)
{
	x = std::min(x, point.x);
	y = std::min(y, point.y);
	width = std::max(x+width, point.x)-x;
	height = std::max(y+height, point.y)-y;
}

template<typename T>
void NzRect<T>::ExtendTo(const NzRect& rect)
{
	x = std::min(x, rect.x);
	y = std::min(y, rect.y);
	width = std::max(x+width, rect.x+rect.width)-x;
	height = std::max(x+height, rect.y+rect.height)-y;
}

template<typename T>
NzVector2<T> NzRect<T>::GetCenter() const
{
	return NzVector2<T>((x+width)/F(2.0), (y+height)/F(2.0));
}

template<typename T>
bool NzRect<T>::Intersect(const NzRect& rect, NzRect* intersection) const
{
	T left = std::max(x, rect.x);
	T right = std::min(x+width, rect.x+rect.width);
	T top = std::max(y, rect.y);
	T bottom = std::min(y+height, rect.y+rect.height);

	if (left < right && top < bottom)
	{
		if (intersection)
		{
			intersection->x = left;
			intersection->y = top;
			intersection->width = right-left;
			intersection->height = bottom-top;
		}

		return true;
	}
	else
		return false;
}

template<typename T>
bool NzRect<T>::IsValid() const
{
	return width > F(0.0) && height > F(0.0);
}

template<typename T>
void NzRect<T>::Set(T X, T Y, T Width, T Height)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
}

template<typename T>
void NzRect<T>::Set(const T rect[4])
{
	x = rect[0];
	y = rect[1];
	width = rect[2];
	height = rect[3];
}

template<typename T>
void NzRect<T>::Set(const NzVector2<T>& vec1, const NzVector2<T>& vec2)
{
	x = std::min(vec1.x, vec2.x);
	y = std::min(vec1.y, vec2.y);
	width = (vec2.x > vec1.x) ? vec2.x-vec1.x : vec1.x-vec2.x;
	height = (vec2.y > vec1.y) ? vec2.y-vec1.y : vec1.y-vec2.y;
}

template<typename T>
template<typename U>
void NzRect<T>::Set(const NzRect<U>& rect)
{
	x = F(rect.x);
	y = F(rect.y);
	width = F(rect.width);
	height = F(rect.height);
}

template<typename T>
NzString NzRect<T>::ToString() const
{
	NzStringStream ss;

	return ss << "Rect(" << x << ", " << y << ", " << width << ", " << height << ')';
}

template<typename T>
NzRect<T>::operator NzString() const
{
	return ToString();
}

template<typename T>
T& NzRect<T>::operator[](unsigned int i)
{
	#if NAZARA_MATH_SAFE
	if (i >= 4)
	{
		NzStringStream ss;
		ss << __FILE__ << ':' << __LINE__ << ": Index out of range (" << i << " >= 4)";

		throw std::domain_error(ss.ToString());
	}
	#endif

	return *(&x+i);
}

template<typename T>
T NzRect<T>::operator[](unsigned int i) const
{
	#if NAZARA_MATH_SAFE
	if (i >= 4)
	{
		NzStringStream ss;
		ss << __FILE__ << ':' << __LINE__ << ": Index out of range (" << i << " >= 4)";

		throw std::domain_error(ss.ToString());
	}
	#endif

	return *(&x+i);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const NzRect<T>& rect)
{
	return out << rect.ToString();
}

#undef F

#include <Nazara/Core/DebugOff.hpp>
