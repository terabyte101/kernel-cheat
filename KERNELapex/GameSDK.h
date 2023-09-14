struct ClrColor { BYTE r, g, b, a; };



#define OFFSET_TEAM    0x0448 
#define OFFSET_HEALTH 0x438
#define OFFSET_SHIELD 0x0170 
#define m_shieldHealthMax 0x0174
#define OFFSET_VIEWANGLES 0x2594       //ammoPoolCapacity
#define OFFSET_BREATH_ANGLES (OFFSET_VIEWANGLES - 0x10)
#define OFFSET_AIMPUNCH  0x2498 //m_vecPunchWeapon_Angle Cplayer m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
#define OFFSET_CAMERAPOS 0x1f40 // camera_origin



#define OFFSET_CURRENT_WEAPON 0x1a6c //m_latestPrimaryWeapons
#define OFFSET_BULLET_SPEED    0x1f28//m_flProjectileSpeed
#define OFFSET_BULLET_SCALE 0x1f30 //m_flProjectileScale
#define OFFSET_BULLET_GRAVITY (OFFSET_BULLET_SPEED + 0x8)


#define GLOW_FADE 0x388
#define GLOW_DISTANCE 0x3B4
#define GLOW_CONTEXT 0x3C8
#define GLOW_LIFE_TIME 0x3A4
#define GLOW_VISIBLE_TYPE 0x3D0
#define GLOW_TYPE 0x2C0
#define GLOW_COLOR 0x1D0
#define GLOW_COLOR2 0x1D4 // GLOW_COLOR + 0x4
#define GLOW_COLOR3 0x1D8 // GLOW_COLOR + 0x8


struct visibleTime
{
	float lastTime[100]; // last visible time in float
	bool lastState[100]; // last visibility state
	uintptr_t lastCheck[100]; // last visibility check time
} lastVis;


class LocalEntity {
public:

	UINT64 Entity;



	explicit LocalEntity()
	{
		Entity = Read<UINT64>(M::modBase + 0x1dd15e8);// LocalPlayer  =0x1dac9c8
		DbgPrint("\n Entity 0x%p", Entity);
	}

	Vector3 Position() {
		return Read<Vector3>(Entity + 0x014c);
	}

	Vector3 BonePosition(int boneIndex)
	{
		Bone bone = {};
		Vector3 vec_bone = Vector3();
		Vector3 pos = Position();

		ULONG64 bone_array = Read<ULONG64>(Entity + 0xf38);
		ULONG64 bone_location = (boneIndex * 0x30);

		bone = Read<Bone>(bone_array + bone_location);
		vec_bone.x = bone.x + pos.x;
		vec_bone.y = bone.y + pos.y;
		vec_bone.z = bone.z + pos.z;
		return vec_bone;
	}

	Vector3 getCamPosition() {
		return *(Vector3*)(Entity + OFFSET_CAMERAPOS);
	}
	//Vector3 getViewAngles() {
	//	return Read<Vector3>(Entity + OFFSET_VIEWANGLES);
	//}



	//void setViewAnglesRec(Vector2 angles) {
	//	Write<Vector2>(Entity + OFFSET_VIEWANGLES, angles);
	//}




	//Vector3 getCamPosition() {
	//	return *(Vector3*)(Entity + OFFSET_CAMERAPOS);
	//}

	Vector3 getViewAngles() {
		return Read<Vector3>(Entity + OFFSET_VIEWANGLES); // 0x259c
	}

	void setViewAnglesRec(Vector2 angles) {
		Write<Vector2>(Entity + OFFSET_VIEWANGLES	, angles);
	}

	Vector3 getAimPunch() {
		return Read<Vector3>(Entity + OFFSET_AIMPUNCH);
	}
	Vector3 getBreathAngles() {
		return Read<Vector3>(Entity + OFFSET_BREATH_ANGLES);
	}

	int iHealth() {
		return Read<int>(Entity + OFFSET_HEALTH);
	}

	int iShield() {
		return Read<int>(Entity + OFFSET_SHIELD);
	}

	int iTeam() {
		return Read<int>(Entity + OFFSET_TEAM);
	}
};



class BaseEntity {
private:
	DWORD64 EntityList;
//	DWORD64 BaseEnt;
	DWORD64 EntityHandle;


	DWORD64 atIndex(int index)
	{
		return Read<DWORD64>(EntityList + (index << 5)); //Returns Entity Address
	}

public:

	DWORD64 Entity;

	glowMode glowStyle = { 0, 102, 100, 255 }; //Default Glow is Outline


	explicit BaseEntity(int index)
	{
		EntityList = M::modBase + 0x1a203b8; // cl_entitylist
		if (!EntityList) return;
		DWORD64 BaseEnt = Read<DWORD64>(EntityList);
	
		if (!BaseEnt) return;
		Entity = atIndex(index);
		if (!Entity) return;

		if (Entity != 0)
			EntityHandle = Read<DWORD64>(Entity + 0x589);
		if (!EntityHandle) return;

	}
	
	bool isPlayer()
	{
		return (EntityHandle == 125780153691248);
	}

	bool IsDummy()
	{
		uint64_t team = Read<uint64_t>(Entity + OFFSET_TEAM);
		return (team == 97);
	}

	Vector3 Position() {
		return Read<Vector3>(Entity + 0x014c);
	}



	Vector3 BonePosition(int boneIndex)
	{
		Bone bone = {};
		Vector3 vec_bone = Vector3();
		Vector3 pos = Position();

		ULONG64 bone_array = Read<ULONG64>(Entity + 0xf50/*0xf38*/);
		ULONG64 bone_location = (boneIndex * 0x30);

		bone = Read<Bone>(bone_array + bone_location);
		vec_bone.x = bone.x + pos.x;
		vec_bone.y = bone.y + pos.y;
		vec_bone.z = bone.z + pos.z;
		return vec_bone;
	}





	Vector3 getViewAngles() {
		return Read<Vector3>(Entity + OFFSET_VIEWANGLES); // 0x259c
	}

	void setViewAnglesRec(Vector2 angles) {
		Write<Vector2>(Entity + OFFSET_VIEWANGLES, angles);
	}


	Vector3 PredictPosition(LocalEntity pLocal, Vector3* bonePos)
	{
		uintptr_t actWeaponID = Read<uintptr_t>(pLocal.Entity + OFFSET_CURRENT_WEAPON) & 0xFFFF;
		uintptr_t currentWeapon = Read<uintptr_t>(EntityList + (actWeaponID << 5));

		if (currentWeapon != 0)
		{
			float bulletSpeed = Read<float>(currentWeapon + OFFSET_BULLET_SPEED);
			float bulletGravity = Read<float>(currentWeapon + OFFSET_BULLET_GRAVITY);

			if (bulletSpeed > 1.f)
			{
				Vector3 muzzle = Read<Vector3>(pLocal.Entity + OFFSET_CAMERAPOS);
				float time = bonePos->DistTo(muzzle) / bulletSpeed;
				bonePos->z += (700.f * bulletGravity * 0.5f) * (time * time);
				Vector3 velDelta = (Read<Vector3>(Entity + 0x014c - 0xC) * time);
				bonePos->x += velDelta.x;
				bonePos->y += velDelta.y;
				bonePos->z += velDelta.z;
			}
		}
		return Position();
	}



	Vector3 getAimPunch() {
		return Read<Vector3>(Entity + OFFSET_AIMPUNCH);
	}

	int iHealth() {
		return Read<int>(Entity + OFFSET_HEALTH);
	}

	int itemID()
	{
		return  Read<int>(Entity + 0x16a8); /// m_customScriptInt
	}

	int iShield() {
		return Read<int>(Entity + OFFSET_SHIELD);
	}

	int Index() {
		if (!this)
			return -1;
		return *(int*)(this + 0x38);
	}

	const wchar_t* NameNew()
	{
		if (!this)
			return nullptr;

		auto indx = Index();
		if (indx == -1)
			return nullptr;

		auto NameList = Read<ULONG64>(Entity + 0xb9f7e40); //NAMELIST
		if (!NameList) return 0;

		auto NamePtr = *(ULONG64*)(NameList + (2 * indx - 2));
		if (!NamePtr) return 0;

		return (wchar_t*)NamePtr;
	}

	int iMaxShield() {
		return Read<int>(Entity + m_shieldHealthMax);
	}

	int iTeam() {
		return Read<int>(Entity + OFFSET_TEAM);
	}

	int isKnocked() {
		return Read<int>(Entity + 0x2728);
	}

	float distanceToLocal(LocalEntity pLocal) {
		return Position().distance(pLocal.Position());
	}




	void Glow(float r, float g, float b)
	{
		if (r == 0.f && g == 0.f && b == 0.f) //Glow Off
		{
			float time = 5000.f;
			glowMode mode = { 0, 0, 0, 0 };
			colorRGB color = { 255, 0, 0 };
			Write<glowMode>(Entity + GLOW_TYPE, mode);
			Write<colorRGB>(Entity + GLOW_COLOR, color);
			Write<float>(Entity + GLOW_DISTANCE, 40000.f);
			Write<float>(Entity + GLOW_LIFE_TIME, time);
			time -= 1.f;
			Write<int>(Entity + GLOW_CONTEXT, 1);
			Write<int>(Entity + GLOW_VISIBLE_TYPE, 1);
			Write<glowFade>(Entity + GLOW_FADE, { 872415232, 872415232, time, time, time, time });
			return;
		}

		float time = 5000.f;

		colorRGB color = { r, g, b };
		Write<glowMode>(Entity + GLOW_TYPE, glowStyle);
		Write<colorRGB>(Entity + GLOW_COLOR, color);
		Write<float>(Entity + GLOW_DISTANCE, 40000.f);
		Write<float>(Entity + GLOW_LIFE_TIME, time);
		time -= 1.f;
		Write<int>(Entity + GLOW_CONTEXT, 1);
		Write<int>(Entity + GLOW_VISIBLE_TYPE, 1);
		Write<glowFade>(Entity + GLOW_FADE, { 872415232, 872415232, time, time, time, time });
	}
};

wchar_t DecodeUTF(const char* UTF)
{
	union wcharType {
		struct {
			UCHAR b1;
			UCHAR b2;
		}; wchar_t ch;
	};

	union charType {
		struct {
			UCHAR b1 : 4;
			UCHAR b2 : 4;
		}; UCHAR ch;
	};

	//1 byte
	charType b1;
	if ((UTF[0] >= '0') && (UTF[0] <= '9'))
		b1.b2 = UTF[0] - '0';
	else b1.b2 = UTF[0] - 'a' + 10;
	if ((UTF[1] >= '0') && (UTF[1] <= '9'))
		b1.b1 = UTF[1] - '0';
	else b1.b1 = UTF[1] - 'a' + 10;

	//2 byte
	charType b2;
	if ((UTF[2] >= '0') && (UTF[2] <= '9'))
		b2.b2 = UTF[2] - '0';
	else b2.b2 = UTF[2] - 'a' + 10;
	if ((UTF[3] >= '0') && (UTF[3] <= '9'))
		b2.b1 = UTF[3] - '0';
	else b2.b1 = UTF[3] - 'a' + 10;

	//build wchar
	wcharType wchar;
	wchar.b1 = b2.ch;
	wchar.b2 = b1.ch;

	//ret
	return wchar.ch;
}

Vector3 BonePosition(uintptr_t ent, int boneIndex)
{
	Bone bone = {};
	Vector3 vec_bone = Vector3();
	Vector3 pos = Read<Vector3>(ent + 0x014c);

	ULONG64 bone_array = Read<ULONG64>(ent + 0xf38);
	ULONG64 bone_location = (boneIndex * 0x30);

	bone = Read<Bone>(bone_array + bone_location);
	vec_bone.x = bone.x + pos.x;
	vec_bone.y = bone.y + pos.y;
	vec_bone.z = bone.z + pos.z;
	return vec_bone;
}


bool WorldToScreen(Vector3 world, Vector2& screen)
{
	float* m_vMatrix = M::matr.matrix;

	float w = m_vMatrix[12] * world.x + m_vMatrix[13] * world.y + m_vMatrix[14] * world.z + m_vMatrix[15];

	if (w < 0.01f) return false;

	screen.x = m_vMatrix[0] * world.x + m_vMatrix[1] * world.y + m_vMatrix[2] * world.z + m_vMatrix[3];
	screen.y = m_vMatrix[4] * world.x + m_vMatrix[5] * world.y + m_vMatrix[6] * world.z + m_vMatrix[7];

	float invw = 1.0f / w;
	screen.x = invw;
	screen.y = invw;

	float x = Gbl::ScreenSize.x / 2;
	float y = Gbl::ScreenSize.y / 2;

	x += 0.5 * screen.x * Gbl::ScreenSize.x + 0.5;
	y -= 0.5 * screen.y * Gbl::ScreenSize.y + 0.5;

	screen.x = x;
	screen.y = y;

	return true;
}
#define powFFFFFFFFFFFFFFFFFFFFFF(n) (n)*(n)



namespace Math
{

	__forceinline float Dist3D(const Vector3& Src, const Vector3& Dst) {
		return sqrt(powFFFFFFFFFFFFFFFFFFFFFF(Src.x - Dst.x, Src.x - Dst.x) + powFFFFFFFFFFFFFFFFFFFFFF(Src.y - Dst.y, Src.x - Dst.x) + powFFFFFFFFFFFFFFFFFFFFFF(Src.z - Dst.z, Src.z - Dst.z));
	}



	float Calc2D_Dist(const Vector2& Src, const Vector2& Dst) {
		return sqrt(powf(Src.x - Dst.x, 2) + powf(Src.y - Dst.y, 2));
	}
}






