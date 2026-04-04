#ifndef	__VECTOR2_HPP__
#define	__VECTOR2_HPP__

#include	<iostream>

class	Vector2
{
	private:
		const float _x;
		const float _y;

	public:
		Vector2(float x, float y);
		~Vector2();

		float getX() const;
		float getY() const;

		bool operator>(const Vector2& other) const;
};

#endif