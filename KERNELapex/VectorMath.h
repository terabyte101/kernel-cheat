int width = NULL;
int height = NULL;

float sqrtn(const float& x)
{
	union
	{
		int i;
		float x;
	} u;
	u.x = x;
	u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

	u.x = u.x + x / u.x;
	u.x = 0.25f * u.x + x / u.x;

	return u.x;
}



struct Matrix
{
	float matrix[16];
};
#define powFFFFFFFFFFFFFFFFFFFFFF(n) (n)*(n)
struct Vector3 {
	float x, y, z;

	float distance(Vector3 vec)
	{
		return sqrt(
			powFFFFFFFFFFFFFFFFFFFFFF(vec.x - x, 2) +
			powFFFFFFFFFFFFFFFFFFFFFF(vec.y - y, 2)
		);
	}

	Vector3 operator-(Vector3 ape)
	{
		return { x - ape.x, y - ape.y, z - ape.z };
	}
	Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator+(Vector3 ape)
	{
		return { x + ape.x, y + ape.y, z + ape.z };
	}

	Vector3 operator*(float ape)
	{
		return { x * ape, y * ape, z * ape };
	}

	Vector3 operator/(float ape)
	{
		return { x / ape, y / ape, z / ape };
	}

	Vector3 operator/=(float ape)
	{
		x /= ape;
		y /= ape;
		z /= ape;

		return *this;
	}

	Vector3 operator+=(Vector3 ape)
	{
		return { x += ape.x, y += ape.y, z += ape.z };
	}

	Vector3 operator-=(Vector3 ape)
	{
		return { x -= ape.x, y -= ape.y, z -= ape.z };
	}

	void Normalize()
	{
		while (x > 89.0f)
			x -= 180.f;

		while (x < -89.0f)
			x += 180.f;

		while (y > 180.f)
			y -= 360.f;

		while (y < -180.f)
			y += 360.f;


	}


	bool is_valid() const
	{
		return !(x == 0.f && y == 0.f && z == 0.f) || (x == -1.f && y == -1.f && z == -1.f);
	}
	float Length() {
		return sqrtf(x * x + y * y + z * z);
	}
	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}

	float DistTo(Vector3 ape)
	{
		return (*this - ape).Length();
	}

	float Dist2D(Vector3 ape)
	{
		return (*this - ape).Length2D();
	}


	struct Vector3 ScreenPosition(struct Matrix matrix) {
		struct Vector3 out;
		float _x = matrix.matrix[0] * x + matrix.matrix[1] * y + matrix.matrix[2] * z + matrix.matrix[3];
		float _y = matrix.matrix[4] * x + matrix.matrix[5] * y + matrix.matrix[6] * z + matrix.matrix[7];
		out.z = matrix.matrix[12] * x + matrix.matrix[13] * y + matrix.matrix[14] * z + matrix.matrix[15];

		_x *= 1.f / out.z;
		_y *= 1.f / out.z;

		 width;
		 height;

		out.x = width * .5f;
		out.y = height * .5f;

		out.x += 0.5f * _x * width + 0.5f;
		out.y -= 0.5f * _y * height + 0.5f;

		return out;
	}




};



struct Vector2 {
	float x, y;

	Vector2()
	{}
	Vector2(float x, float y)
		: x(x), y(y)
	{}

	Vector2 operator-(Vector2 ape)
	{
		return { x - ape.x, y - ape.y };
	}

	Vector2 operator+(Vector2 ape)
	{
		return { x + ape.x, y + ape.y };
	}

	float vec2distance(Vector2 b)
	{
		return sqrt(powFFFFFFFFFFFFFFFFFFFFFF(b.x - x, 2) + powFFFFFFFFFFFFFFFFFFFFFF(b.y - y, 2));
	}

	Vector2 operator*(float ape)
	{
		return { x * ape, y * ape };
	}

	Vector2 operator/(float ape)
	{
		return { x / ape, y / ape };
	}

	Vector2 operator/=(float ape)
	{
		x /= ape;
		y /= ape;

		return *this;
	}

	Vector2 operator+=(Vector2 ape)
	{
		return { x += ape.x, y += ape.y };
	}

	Vector2 operator-=(Vector2 ape)
	{
		return { x -= ape.x, y -= ape.y };
	}

	void Normalize()
	{
		if (x > 89.0f)
			x -= 180.f;

		if (x < -89.0f)
			x += 180.f;

		if (y > 180.f)
			y -= 360.f;

		if (y < -180.f)
			y += 360.f;
	}

	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}

	float Dist2D(Vector2 ape)
	{
		return (*this - ape).Length2D();
	}




};



#define M_PI 3.14159265358979323846f
#define M_RADPI	57.295779513082f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
__forceinline Vector3 CalcAngle(Vector3 src, Vector3 dst) {
	Vector3 origin = dst - src;
	float dist = sqrt(origin.x * origin.x + origin.y * origin.y + origin.z * origin.z);
	Vector3 angles = { 0.f, 0.f, 0.f };
	angles.x = -__asinf(origin.z / dist) * (180 / M_PI);
	angles.y = __atan2f(origin.y, origin.x) * (180 / M_PI);
	return angles;
}

inline void ClampAngles(Vector3& angle)
{
	if (angle.y > 180.0f)
		angle.y = 180.0f;
	else if (angle.y < -180.0f)
		angle.y = -180.0f;

	if (angle.x > 89.0f)
		angle.x = 89.0f;
	else if (angle.x < -89.0f)
		angle.x = -89.0f;

	angle.z = 0;
}




int __fpclassifyf(float f)
{
	union IEEEf2bits {
		float	f;
		struct {
			unsigned int	man : 23;
			unsigned int	exp : 8;
			unsigned int	sign : 1;
		} bits;
	};

	union IEEEf2bits u;
	u.f = f;
	if (u.bits.exp == 0) {
		if (u.bits.man == 0)
			return (FP_ZERO);
		return (FP_SUBNORMAL);
	}
	if (u.bits.exp == 255) {
		if (u.bits.man == 0)
			return (FP_INFINITE);
		return (FP_NAN);
	}
	return (FP_NORMAL);
}

bool isnanf(float a) {
	return bool(__fpclassifyf(a) == FP_NAN);
}

struct colorRGB
{
	float r, g, b;
};

struct glowMode
{
	BYTE GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
};

struct glowFade
{
	int a, b;
	float c, d, e, f;
};
struct Bone {
	BYTE thing[0xCC];
	float x;
	BYTE thing2[0xC];
	float y;
	BYTE thing3[0xC];
	float z;
};