#pragma once
struct iPoint
{
	int x;
	int y;
};

struct fPoint
{
	float x;
	float y;

	fPoint()
	{
		x = 0;
		y = 0;
	}

	fPoint(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	fPoint operator+(const fPoint& other)
	{
		return fPoint(x + other.x, y + other.y);
	}

	fPoint& operator+=(const fPoint& other)
	{
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	fPoint operator-(const fPoint& other)
	{
		return fPoint(x - other.x, y - other.y);
	}

	fPoint& operator=(const fPoint& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	bool operator==(const fPoint& other)
	{
		return (x == other.x && y == other.y);
	}

	bool operator!=(const fPoint& other)
	{
		return *this == other;
	}

	template <typename T>
	fPoint operator*(const T value)
	{
		return fPoint(x * (float)value, y * (float)value);
	}

	template <typename T>
	fPoint operator/(const T value)
	{
		assert(value != 0);
		return fPoint(x / value, y / value);
	}

	fPoint& Normalize()
	{
		float r = (float)sqrt((double)x * x + (double)y * y);

		if (r == 0)
			return *this;

		this->x = x / r;
		this->y = y / r;

		return *this;
	}

	float Length()
	{
		return (float)sqrt((double)x * x + (double)y * y);
	}

	fPoint Right()
	{
		return fPoint(1.0f, 0.f);
	}
	fPoint Left()
	{
		return fPoint(-1.f, 0.f);
	}
	fPoint Up()
	{
		return fPoint(0.f, -1.f);
	}
	fPoint Down()
	{
		return fPoint(0.0f, 1.f);
	}
};

typedef iPoint iVector2D;
typedef fPoint fVector2D;