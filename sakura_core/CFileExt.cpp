﻿/*!	@file
	@brief オープンダイアログ用ファイル拡張子管理

	@author MIK
	@date 2003.5.12
*/
/*
	Copyright (C) 2003, MIK
	Copyright (C) 2018-2021, Sakura Editor Organization

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
#include <string.h>
#include <stdlib.h>
#include "CFileExt.h"
#include "env/CDocTypeManager.h"

CFileExt::CFileExt()
{
	m_nCount = 0;
	m_vstrFilter.resize( 1 );
	m_vstrFilter[0] = L'\0';

//	//テキストエディタとして、既定でリストに載ってほしい拡張子
//	AppendExt( "すべてのファイル", "*" );
//	AppendExt( "テキストファイル", "txt" );
}

CFileExt::~CFileExt()
{
	m_nCount = 0;
}

bool CFileExt::AppendExt( const WCHAR *pszName, const WCHAR *pszExt )
{
	WCHAR	szWork[MAX_PATH];

	if( !CDocTypeManager::ConvertTypesExtToDlgExt( pszExt, NULL, szWork ) ) return false;
	return AppendExtRaw( pszName, szWork );
}

bool CFileExt::AppendExtRaw( const WCHAR *pszName, const WCHAR *pszExt )
{
	if( NULL == pszName || pszName[0] == L'\0' ) return false;
	if( NULL == pszExt  || pszExt[0] == L'\0' ) return false;

	SFileExtInfo info;
	info.m_sTypeName = pszName;
	info.m_sExt = pszExt;

	m_vFileExtInfo.push_back(std::move(info));
	m_nCount = static_cast<int>(m_vFileExtInfo.size());

	return true;
}

const WCHAR *CFileExt::GetName( int nIndex )
{
	if( nIndex < 0 || nIndex >= m_nCount ) return NULL;

	return m_vFileExtInfo[nIndex].m_sTypeName.c_str();
}

const WCHAR *CFileExt::GetExt( int nIndex )
{
	if( nIndex < 0 || nIndex >= m_nCount ) return NULL;

	return m_vFileExtInfo[nIndex].m_sExt.c_str();
}

const WCHAR *CFileExt::GetExtFilter( void )
{
	int		i;
	std::wstring work;

	/* 拡張子フィルタの作成 */
	m_vstrFilter.resize(0);

	for( i = 0; i < m_nCount; i++ )
	{
		// "%s (%s)\0%s\0"
		work = m_vFileExtInfo[i].m_sTypeName;
		work.append(L" (");
		work.append(m_vFileExtInfo[i].m_sExt);
		work.append(L")");
		work.append(L"\0", 1);
		work.append(m_vFileExtInfo[i].m_sExt);
		work.append(L"\0", 1);

		int i = (int)m_vstrFilter.size();
		m_vstrFilter.resize( i + work.length() );
		wmemcpy( &m_vstrFilter[i], &work[0], work.length() );
	}
	if( 0 == m_nCount ){
		m_vstrFilter.push_back( L'\0' );
	}
	m_vstrFilter.push_back( L'\0' );

	return &m_vstrFilter[0];
}
