//========================================================================
//
// あたり判定 [Collision.cpp]
// Author : NAOYA OMORI
// 
//========================================================================

#include "collision.h"

//あたり判定どこでも用
bool isHit(float Ax, float Ay, float Awidth, float Aheight, float Bx, float By, float Bwidth, float Bheight) {

	if ((Ax < Bx + Bwidth) && (Ay < By + Bheight) && (Bx < Ax + Awidth) && (By < Ay + Aheight))
	{
		return true;
	}

	else

	{
		return false;
	}

}