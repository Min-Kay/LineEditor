#pragma once


///////////////////////////////////////////////////////////////////////////
// 최초 1회만 추가한다! 메인 첨에 정해진 코드 1회만 입력
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
///////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

#endif // _DEBUG
///////////////////////////////////////////////////////////////////////////

#include  "Define.h"
#include  "Enum.h"
#include  "Struct.h"