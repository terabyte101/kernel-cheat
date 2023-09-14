//
//

#include "ESPloot.h"
enum BoneId {
	head = 8,
	neck = 7,
	abdomen = 6,
	Left_shoulder = 11,
	Right_shoulder = 35,
	chest = 5,
	Spine = 3,
	Left_hand = 15,
	Right_hand = 39,
	Left_arm = 41,
	Right_arm = 16,
	Left_knee = 58,
	Right_knee = 63,
	Left_foot = 65,
	Right_foot = 60,
	Left_ElbowRoll = 13,
	Right_ElbowRoll = 37,
};
#include <map>

	
struct string
{
	wchar_t buffer[256];
};
void ESP(BaseEntity pEntity, LocalEntity pLocal, Matrix m)
{
	//esp


	Vector3 entHead = pEntity.BonePosition(8); // get head position
	Vector3 w2sHead = entHead.ScreenPosition(m) - Vector3(0.f ,10.f, 0.f ); if (w2sHead.z <= 0.f) return;
	

	Vector3 entPos = pEntity.Position();
	Vector3 w2sPos = entPos.ScreenPosition(m); if (w2sPos.z <= 0.f) return;

	

	float height = abs(abs(w2sHead.y) - abs(w2sPos.y));
	//float height = w2sHead.y - w2sPos.y;
	float width = height / 2.f;
	float middle = w2sPos.x - (width / 2.f);

	int health = (int)pEntity.iHealth();
	int armor = (int)pEntity.iShield();
	//int maxarmor = (int)pEntity.iMaxShield();

	float minheal = 100.f;
	float maxhil = 100.f;

	if (pEntity.iTeam() == pLocal.iTeam())
		rctx.Rectangle(middle, w2sHead.y , width, height, RGB(102, 255, 0));
	else
		rctx.Rectangle(middle, w2sHead.y, width, height, RGB(255, 255, 255));
	rctx.String(entHead.x, entHead.y, L"NIGGER", RGB(102, 255, 0));

		float HealthSize = (-height  * (health / 100.f));
		float ArmorSize = (-height  * (armor  / 125.f));
		////hp
		//float HealthSize = (Height * pEnt->Health()) / 100.f;
		rctx.Line(middle -3 ,( w2sPos.y + HealthSize ), middle - 3, w2sHead.y, RGB(255, 0, 0), 2.f);
		rctx.Line(middle -3, w2sPos.y, middle - 3, (w2sPos.y + HealthSize), RGB(0, 255, 0), 2.f);
		rctx.Line(middle -3, w2sPos.y, middle - 3, (w2sPos.y + ArmorSize) , RGB(0, 191, 255), 2.f);

		////name
		//wchar_t DistanceW[128];

		//for (int i = 0; ; i++) {
		//	DistanceW[i] = meters;
		//	if (!DistanceW[i]) break;
		//}
		float distance = pEntity.distanceToLocal(pLocal);
		int meters = distance / 20;
		//if (settings::visuals::skeleton)
		int dist = distance;

		rctx.String(w2sPos.x, w2sPos.y + 10, (const wchar_t*)dist, TA_CENTER, RGB(255, 0, 0));




		//	{
		//		BoneId Bones[16] = {
		//			/*LF*/Left_foot, Left_knee, Left_arm,
		//			/*RF*/Right_foot, Right_knee, Right_arm,
		//			/*BD*/Spine, neck, head,
		//			/*LH*/Left_shoulder, Left_ElbowRoll, Left_hand,
		//			/*RH*/Right_shoulder, Right_ElbowRoll, Right_hand
		//			, abdomen
		//		}; Vector2 BonesPos[16];


		//		Vector3 enthead = pEntity.BonePosition(head); // get head position
		//		Vector3 w2shead = enthead.ScreenPosition(m); if (w2shead.z <= 0.f) return;
		//		Vector3 entNeck = pEntity.BonePosition(neck); // get head position
		//		Vector3 w2sNeck = entNeck.ScreenPosition(m); if (w2sNeck.z <= 0.f) return;
		//		Vector3 entSpine = pEntity.BonePosition(Spine); // get head position
		//		Vector3 w2sSpine = entSpine.ScreenPosition(m); if (w2sSpine.z <= 0.f) return;	
		//		
		//		Vector3 entabdomen = pEntity.BonePosition(abdomen); // get head position
		//		Vector3 w2sabdomen = entabdomen.ScreenPosition(m); if (w2sabdomen.z <= 0.f) return;

		//		Vector3 entLeft_arm = pEntity.BonePosition(Left_arm); // get head position
		//		Vector3 w2sLeft_arm = entLeft_arm.ScreenPosition(m); if (w2sLeft_arm.z <= 0.f) return;
		//		Vector3 entLeft_knee = pEntity.BonePosition(Left_knee); // get head position
		//		Vector3 w2sLeft_knee = entLeft_knee.ScreenPosition(m); if (w2sLeft_knee.z <= 0.f) return;
		//		Vector3 entLeft_foot = pEntity.BonePosition(Left_foot); // get head position
		//		Vector3 w2sLeft_foot = entLeft_foot.ScreenPosition(m); if (w2sLeft_foot.z <= 0.f) return;

		//		Vector3 entRight_arm = pEntity.BonePosition(Right_arm); // get head position
		//		Vector3 w2sRight_arm = entRight_arm.ScreenPosition(m); if (w2sRight_arm.z <= 0.f) return;
		//		Vector3 entRight_knee = pEntity.BonePosition(Right_knee); // get head position
		//		Vector3 w2sRight_knee = entRight_knee.ScreenPosition(m); if (w2sRight_knee.z <= 0.f) return;
		//		Vector3 entRight_foot = pEntity.BonePosition(Right_foot); // get head position
		//		Vector3 w2sRight_foot = entRight_foot.ScreenPosition(m); if (w2sRight_foot.z <= 0.f) return;


		//		Vector3 entLeft_hand = pEntity.BonePosition(Left_hand); // get head position
		//		Vector3 w2sLeft_hand = entLeft_hand.ScreenPosition(m); if (w2sLeft_hand.z <= 0.f) return;
		//		Vector3 entLeft_ElbowRoll = pEntity.BonePosition(Left_ElbowRoll); // get head position
		//		Vector3 w2sLeft_ElbowRoll = entLeft_ElbowRoll.ScreenPosition(m); if (w2sLeft_ElbowRoll.z <= 0.f) return;
		//		Vector3 entLeft_shoulder = pEntity.BonePosition(Left_shoulder); // get head position
		//		Vector3 w2sLeft_shoulder = entLeft_shoulder.ScreenPosition(m); if (w2sLeft_shoulder.z <= 0.f) return;

		//		Vector3 entRight_hand = pEntity.BonePosition(Right_hand); // get head position
		//		Vector3 w2sRight_hand = entRight_hand.ScreenPosition(m); if (w2sRight_hand.z <= 0.f) return;
		//		Vector3 entRight_ElbowRoll = pEntity.BonePosition(Right_ElbowRoll); // get head position
		//		Vector3 w2sRight_ElbowRoll = entRight_ElbowRoll.ScreenPosition(m); if (w2sRight_ElbowRoll.z <= 0.f) return;
		//		Vector3 entRight_shoulder = pEntity.BonePosition(Right_shoulder); // get head position
		//		Vector3 w2sRight_shoulder = entRight_shoulder.ScreenPosition(m); if (w2sRight_shoulder.z <= 0.f) return;


		//		// rctx.Line(w2shead.x, w2shead.y , w2sNeck.x, w2sNeck.y , RGB(0, 255, 0));
		//		rctx.Line(w2sNeck.x, w2sNeck.y, w2sSpine.x, w2sSpine.y, RGB(0, 255, 0));
		//		rctx.Line(w2sSpine.x, w2sSpine.y, w2sabdomen.x, w2sabdomen.y, RGB(0, 255, 0));

		//	//	rctx.Line(w2sLeft_arm.x, w2sLeft_arm.y, w2sLeft_knee.x, w2sLeft_knee.y, RGB(0, 255, 0));
		//	//	rctx.Line(w2sLeft_knee.x, w2sLeft_knee.y, w2sLeft_foot.x, w2sLeft_foot.y, RGB(0, 255, 0));
		//	//	rctx.Line(w2s2.x, w2s2.y, w2s6.x, w2s6.y, RGB(0, 255, 0));

		////		rctx.Line(w2sRight_arm.x, w2sRight_arm.y, w2sRight_knee.x, w2sRight_knee.y, RGB(0, 255, 0));
		////		rctx.Line(w2sRight_knee.x, w2sRight_knee.y, w2sRight_foot.x, w2sRight_foot.y, RGB(0, 255, 0));
		//////		rctx.Line(w2s2.x, w2s2.y, w2s6.x, w2s6.y, RGB(0, 255, 0));

		////		rctx.Line(w2sLeft_hand.x, w2sLeft_hand.y, w2sLeft_ElbowRoll.x, w2sLeft_ElbowRoll.y, RGB(0, 255, 0));
		////		rctx.Line(w2sLeft_ElbowRoll.x, w2sLeft_ElbowRoll.y, w2sLeft_shoulder.x, w2sLeft_shoulder.y, RGB(0, 255, 0));
		////	//	rctx.Line(w2s2.x, w2s2.y, w2s6.x, w2s6.y, RGB(0, 255, 0));

		////		rctx.Line(w2sRight_hand.x, w2sRight_hand.y, w2sRight_ElbowRoll.x, w2sRight_ElbowRoll.y, RGB(0, 255, 0));
		////		rctx.Line(w2sRight_ElbowRoll.x, w2sRight_ElbowRoll.y, w2sRight_shoulder.x, w2sRight_shoulder.y, RGB(0, 255, 0));
		//////		rctx.Line(w2s2.x, w2s2.y, w2s6.x, w2s6.y, RGB(0, 255, 0));

		//	}


		


	//   auto PlayerNameA = pEntity.NameNew();
	   //for (int i = 0; ; i++) {
		  // PlayerNameW[i] = PlayerNameA[i];
		  // if (!PlayerNameW[i]) break;
	   //}

		
		//							//convert to wchar_t
		////name
		//wchar_t PlayerNameW[128];
		//for (int a = 0, u = 0;;)
		//{
		//	if (PlayerNameA[a] == '\\' && PlayerNameA[a + 1] == 'u') {
		//		PlayerNameW[u++] = DecodeUTF(&PlayerNameA[a + 2]);
		//		a += 6;
		//	}

		//	else {
		//		PlayerNameW[u++] = PlayerNameA[a];
		//		if (!PlayerNameA[a]) {
		//			break;
		//		} a++;
		//	}
		//}



	// rctx.String(w2sPos.x, w2sPos.y + 10, PlayerNameA, TA_CENTER, RGB(255, 0, 0));
	

		
	
}




void ItemESP(BaseEntity pEntity, LocalEntity pLocal, Matrix m)
{


	Vector3 entHead = pEntity.BonePosition(8); // get head position
	Vector3 w2sHead = entHead.ScreenPosition(m) - Vector3(0.f, 10.f, 0.f); if (w2sHead.z <= 0.f) return;

	Vector3 entPos = pEntity.Position();
	Vector3 w2sPos = entPos.ScreenPosition(m); if (w2sPos.z <= 0.f) return;

	float height = abs(abs(w2sHead.y) - abs(w2sPos.y));
	//float height = w2sHead.y - w2sPos.y;
	float width = height / 2.f;
	float middle = w2sPos.x - (width / 2.f);


	//rctx.Rectangle(middle, w2sHead.y, width, height, RGB(255, 255, 255));




//	rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
//	if (Raritys::HEIRLOOM)
//	rctx.Rectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(255, 92, 219), 2.0f);
//	else
	
#define HEIRLOOM RGB(255, 0, 0)
#define LEGENDARY RGB(255, 255, 0)
#define COMMON RGB(0, 255, 255)
#define Purple RGB(255, 92, 219)

	if (pEntity.itemID() == 1  ) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Kraber", COMMON);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
		rctx.Rectangle(w2sPos.x, w2sHead.y, 15, 15, HEIRLOOM, 2.0f);
	}
	else if (pEntity.itemID() ==  37 ) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"G7 Scout", COMMON);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
		rctx.Rectangle(w2sPos.x, w2sHead.y, 15, 15, HEIRLOOM, 2.0f);
	}
	else if (pEntity.itemID() == 68 ) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Spitfire", COMMON);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
		rctx.Rectangle(w2sPos.x, w2sHead.y, 15, 15, HEIRLOOM, 2.0f);
	}
	else if (pEntity.itemID() == 2) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Mastiff", COMMON);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
	}
	else if (pEntity.itemID() == 7) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Lstar", COMMON);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
	}
	else if (pEntity.itemID() == 47) {
		rctx.String(w2sPos.x, w2sHead.y -20,  L"R99", COMMON);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
	}
	else if (pEntity.itemID() == 73) {
		rctx.String(w2sPos.x, w2sHead.y -20,  L"R301", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 58) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Longbow", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 57) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"VOLT", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 63) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Charge Rifle", COMMON);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
	}
	else if (pEntity.itemID() == 42) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Alternator", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 46) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Alternator", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 32) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Havoc", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 27) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Flatline", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 52) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Prowler", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 78) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Eva-8 Auto", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 83) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"PeaceKeeper", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}



	else if (pEntity.itemID() == 93) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Wingman", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}


	else if (pEntity.itemID() == 88) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Mozambique", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 98) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"P2020", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 103) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"RE45-AUTO", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 108) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Sentinel", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}	
	else if (pEntity.itemID() == 113) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Bocek Bow", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}	
	else if (pEntity.itemID() == 118) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Repeater 30/30 ", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}	
	else if (pEntity.itemID() == 17) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Devotion", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 22) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Triple Take", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}	
	else if (pEntity.itemID() == 26) {
		rctx.String(w2sPos.x, w2sHead.y - 20, L"Triple Take", COMMON);
		rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
		rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}


	else if (pEntity.itemID() == 135) {
	rctx.String(w2sPos.x, w2sHead.y - 20, L"C.A.R", COMMON);
	rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, COMMON, 2.0f);
	rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 130) {
	rctx.String(w2sPos.x, w2sHead.y - 20, L"Rampage", COMMON);
	rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
	rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}


	else if (pEntity.itemID() == 131) {
	rctx.String(w2sPos.x, w2sHead.y - 20, L"Chaos", COMMON);
	rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
	rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 132) {
	rctx.String(w2sPos.x, w2sHead.y - 20, L"Chaos", COMMON);
	rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
	rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 133) {
	rctx.String(w2sPos.x, w2sHead.y - 20, L"Chaos", COMMON);
	rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
	rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
	else if (pEntity.itemID() == 134) {
	rctx.String(w2sPos.x, w2sHead.y - 20, L"Chaos", COMMON);
	rctx.Rectangle(w2sPos.x, w2sHead.y, 16, 16, HEIRLOOM, 2.0f);
	rctx.FillRectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(24, 23, 28));
	}
//	else 
//		rctx.Rectangle(w2sPos.x, w2sHead.y, 15, 15, RGB(0, 0, 255), 2.0f);



}

Vector3 oldPunch = { 0.f, 0.f, 0.f };
void NoRecoil(LocalEntity pLocal) {

	if (GetAsyncKeyState(0x02)) 
	{
		Vector3 viewAngles = pLocal.getViewAngles();
		Vector3 punchAngle = pLocal.getAimPunch();

		Vector3 newAngle = viewAngles + (oldPunch - punchAngle);

		newAngle.Normalize();
		pLocal.setViewAnglesRec(Vector2(newAngle.x, newAngle.y));

		oldPunch = punchAngle;
	}
}

void Normalized(float& Yaw, float& Pitch) {
	if (Pitch < -89) Pitch = -89;
	else if (Pitch > 89) Pitch = 89;
	if (Yaw < -360) Yaw += 360;
	else if (Yaw > 360) Yaw -= 360;
}
float AimFov(BaseEntity pEntity, int bone)
{

	Vector2 screenMiddle = { Gbl::ScreenSize.x / 2.f, Gbl::ScreenSize.y / 2.f };
	Vector2 ScreenPos;
	if (!WorldToScreen(BonePosition(pEntity.Entity, bone), ScreenPos));
	return (Math::Calc2D_Dist(Vector2(Gbl::ScreenSize.x / 2.f, Gbl::ScreenSize.y / 2.f), ScreenPos));
}


void aim(BaseEntity pEntity , LocalEntity pLocal, Matrix m)
// AIMBOT
{
	float smallest_distance = FLT_MAX;

		int boneKey = 0;


		static int boneArr[12] = {
		head,
		Left_arm,
		Left_shoulder,
		Right_shoulder,
		chest ,
		 Right_knee,
		Left_hand,
		Right_hand,
		Spine,
		Left_foot,
		neck,
		Right_ElbowRoll, };

		switch (1) {
		case 0:
			boneKey = BoneId::head;
			break;
		case 1: boneKey = BoneId(boneArr[int(rand() % 12)]);  break;
			break;
		}

	
		if (pEntity.iTeam() == pLocal.iTeam())
			return;
		Vector3 Aimedhead = pEntity.BonePosition(boneKey);


		Vector3 w2sPos = Aimedhead.ScreenPosition(m); if (w2sPos.z <= 0.f) return;

		
		//WorldToScreen(Aimedhead, targetHeadScreen);
		Vector3 localHead = pLocal.getCamPosition();
		Vector3 oldAngle = pLocal.getViewAngles();
		Vector3 punchAngle = pLocal.getAimPunch();
		Vector3 breathAngle = pLocal.getBreathAngles();

		Vector3 newAngles = CalcAngle(localHead, Aimedhead);

		Vector3 clampAngles = newAngles - punchAngle - oldAngle;
		//	clampAngles.Normalize();
		const	Vector3 screenMiddle = { Gbl::ScreenSize.x / 2.f, Gbl::ScreenSize.y / 2.f , 0.f };

		float distance = w2sPos.distance(screenMiddle);

		newAngles = newAngles - punchAngle;
	//	newAngles.Normalize();
		newAngles = oldAngle  + (clampAngles * (5 / 100.f));
		newAngles.Normalize();
		
	
		

		float fov_limit = 100.f;
	//	if (distance < smallest_distance && fov_limit > distance)
	//	{


			
			if (GetAsyncKeyState(0x02) && Aimedhead.is_valid() && distance < smallest_distance && fov_limit > distance) {
                smallest_distance = distance;	
				DbgPrintEx(0, 0, "AIMBOT\n");
				pLocal.setViewAnglesRec({ newAngles.x, newAngles.y });
			}
	//	}

	
}



void Glow(BaseEntity pEntity, LocalEntity pLocal)
{

		//pEntity.glowStyle = { 101,101,46,90 }; //Bright Glow, default is just outline


		if (pEntity.iTeam() == pLocal.iTeam()) // DON'T GLOW ALLIES
			return;


		//	pEntity.Glow(0.f, 255.f, 255.f); //cyan

	//	pEntity.Glow(0.f, 0.f, 0.f); //Turning off glow

	

		

	
}









