﻿/*! @file */
/*
	Copyright (C) 2018-2022, Sakura Editor Organization

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

		1. The origin of this software must not be misrepresented;
		   you must not claim that you wrote the original software.
		   If you use this software in a product, an acknowledgment
		   in the product documentation would be appreciated but is
		   not required.

		2. Altered source versions must be plainly marked as such,
		   and must not be misrepresented as being the original software.

		3. This notice may not be removed or altered from any source
		   distribution.
*/
#include "StdAfx.h"
#include "CConvert_ZenkataToHankata.h"
#include "convert_util.h"
#include "mem/CNativeW.h"

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                     インターフェース                        //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //

//!全角カナ→半角カナ
bool CConvert_ZenkataToHankata::DoConvert(CNativeW* pcData)
{
	//全角カタカナ→半角カタカナ
	wchar_t* pBuf = new wchar_t[pcData->GetStringLength()*2+1]; //濁点等の影響で、最大2倍にまで膨れ上がる可能性があるので、2倍のバッファを確保
	int nBufLen = 0;
	Convert_ZenkataToHankata(pcData->GetStringPtr(), pcData->GetStringLength(), pBuf, &nBufLen);
	pcData->SetString(pBuf, nBufLen);
	delete[] pBuf;

	return true;
}
