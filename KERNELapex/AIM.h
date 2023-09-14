


void menu()
{
	float MenuPos = Gbl::ScreenSize.y / 2;
	if (set::Check)
	{
		if (GetAsyncKeyState(45))
		{
			set::menu = !set::menu;

		};

		if (GetAsyncKeyState(97))
		{
			set::PlayerESP = !set::PlayerESP;

		};

		if (GetAsyncKeyState(0x62))
		{
			set::ItemESP = !set::ItemESP;
		

		};

		if (GetAsyncKeyState(0x63))
		{
	
			set::AimBot = !set::AimBot;

		};
			if (GetAsyncKeyState(0x64))
		{
	
			set::NoRecoil = !set::NoRecoil;

		};



		if (set::menu) {

			rctx.FillRectangle(5, MenuPos - 5, 125, 160, RGB(24, 23, 28));
			rctx.Rectangle(5, MenuPos - 5, 126, 161, RGB(255, 92, 219), 2.f);


		};


		if (set::PlayerESP && set::menu)
		{

			rctx.String(15, MenuPos, L"Player ESP - ON", TA_LEFT, RGB(0, 255, 255));
		}

		else if (!set::PlayerESP && set::menu)
		{

			if (set::menu)
			{
				rctx.String(15, MenuPos, L"Player ESP - OFF", TA_LEFT, RGB(255, 0, 0));
			}

		}MenuPos += 15;
		if (set::ItemESP && set::menu)
		{

			rctx.String(15, MenuPos, L"ItemESP  - ON", TA_LEFT, RGB(0, 255, 255));
		}

		else if (!set::ItemESP && set::menu)
		{

			if (set::menu)
			{
				rctx.String(15, MenuPos, L"ItemESP - OFF", TA_LEFT, RGB(255, 0, 0));
			}

		}MenuPos += 15;

		if (set::AimBot && set::menu)
		{

			rctx.String(15, MenuPos, L"AimBot  - ON", TA_LEFT, RGB(0, 255, 255));
		}

		else if (!set::AimBot && set::menu)
		{

			if (set::menu)
			{
				rctx.String(15, MenuPos, L"AimBot - OFF", TA_LEFT, RGB(255, 0, 0));
			}

		}MenuPos += 15;

		if (set::NoRecoil && set::menu)
		{

			rctx.String(15, MenuPos, L"NoRecoil - ON", TA_LEFT, RGB(0, 255, 255));
		}

		else if (!set::NoRecoil && set::menu)
		{

			if (set::menu)
			{
				rctx.String(15, MenuPos, L"NoRecoil - OFF", TA_LEFT, RGB(255, 0, 0));
			}

		}MenuPos += 15;
	}

}



const size_t NUM_ENT_ENTRIES = 0x10000;

struct EntityInfo {
	uintptr_t EntityPtr;
	wchar_t Status[32];
	uint8_t a, b, c;
};
EntityInfo entitiesHeap[NUM_ENT_ENTRIES / 2];
EntityInfo ExitCachedArray[25];

void RenderCheat() 
{
	//Log("RenderCheat: 0x%p\n", 0);
	//Important Stuff		
	// 
	//DbgPrintEx(0, 0, "RenderCheat\n");

	M::viewRenderer = Read<uint64_t>(M::modBase + 0x75461d0); // view_render
	//DbgPrintEx(0, 0, "ViewRender: %p\n", M::viewRenderer);
	if (!M::viewRenderer)
	{
		M::viewMatrix = 0x0;
		return;
	}
	M::viewMatrix = Read<uint64_t>(M::viewRenderer + 0x11a210); // view_matrix
	//DbgPrintEx(0, 0, "viewMatrix: %p\n", M::viewMatrix);
	if (!M::viewMatrix)
	{
		M::viewRenderer = 0x0;
		return;
	}
	M::matr = Read<Matrix>(M::viewMatrix);
	//DbgPrintEx(0, 0, "matr: %p\n", M::matr);

	LocalEntity pLocal;






	//for (uintptr_t& player : GetPlayers())
	for (size_t i = 0; i < 100; i++)
	{
		

		BaseEntity pEntity(i);
		float distance = pEntity.distanceToLocal(pLocal);
		int meters = distance / 20;

	//	Log(" pEntity.iHealth() 0x%d\n", pEntity.iHealth());
	//	Log(" pEntity.isPlayer() 0x%d\n", pEntity.isPlayer());

	//	if (pEntity.itemID() >= 1&& pEntity.itemID() <= 250 && pEntity.Entity != pLocal.Entity && meters < 75)
	//		ItemESP(pEntity, pLocal, M::matr);

		if (set::NoRecoil)
			NoRecoil(pLocal);
		if (/*pEntity.IsDummy() || pEntity.isPlayer() &&*/ pEntity.iHealth() != 0 && pEntity.Entity != pLocal.Entity)
		{


			


		//	Aimbot(pEntity, pLocal, M::matr);
		

		//	Log(" loop \n", pEntity);
		//	Glow(pEntity, pLocal);
	

			//Glow ESP
		//	if (MenuSettings::glowEnabled)
		//		Modules::Glow(pEntity, pLocal);

	
			//Box ESP
		//	if (MenuSettings::espEnabled)
		static int cases = 0;
		static float r = 1.00f, g = 0.00f, b = 1.00f;
		switch (cases) {
		case 0: { r -= 0.0008f; if (r <= 0) cases += 1; break; }
		case 1: { g += 0.0008f; b -= 0.0008f; if (g >= 1) cases += 1; break; }
		case 2: { r += 0.0008f; if (r >= 1) cases += 1; break; }
		case 3: { b += 0.0008f; g -= 0.0008f; if (b >= 1) cases = 0; break; }
		default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
		}
		


		if (set::PlayerESP && meters < 1000)
		{
			ESP(pEntity, pLocal, M::matr);
		}


	


			if (set::AimBot && meters < 1000)
			{			
			rctx.Circle(Gbl::ScreenSize.x / 2, Gbl::ScreenSize.y / 2, RGB(r * 255, g * 255, b * 255), 100.f, 2.5f);
		
			aim(pEntity, pLocal, M::matr);
			}

			

		//	pEntity.Glow(0.f, 0.f, 0.f); //Turning off glow
			//Healthbar
		//	if (MenuSettings::healthbarEnabled)
			//	Modules::Healthbar(pEntity, m, distance, pLocal);


		}
	}

}
//auto EntityList;
//DWORD64 atIndex(int index)
//	{
//		return Read<DWORD64>(EntityList + (index << 5)); //Returns Entity Address
//	}


struct ExitCached
{
	wchar_t Name[256];
	wchar_t Status[32];
	Vector3 Location;
};
static int ExitCachedCount;
//ExitCached ExitCachedArray[256];

void RenderItems()
{


	LocalEntity pLocal;


	for (size_t i = 0; i < 13000; i++)
	{
	
	

		int Entity = Read<int>(M::modBase + 0x1a203b8/*0x19fbc18*/ + (i * 0x20));//0x1a203b8
		//DbgPrintEx(0, 0, "LootEnity: %p\n", Entity);
		if (Entity == NULL)
			continue;

		BaseEntity pEntity(i);
		
		
		float distance = pEntity.distanceToLocal(pLocal);
		int meters = distance / 20;

		if (pEntity.itemID() >= 1 && pEntity.itemID() <= 255 && pEntity.Entity != pLocal.Entity && meters < 75)
			ItemESP(pEntity, pLocal, M::matr);

	}

}