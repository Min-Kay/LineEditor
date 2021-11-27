#pragma once

#define		WINCX	800
#define		WINCY	600	
#define		PURE	= 0

#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1

#define		PI		3.141592f

#define		VK_MAX		0xff

#define		LINE_SAVE	L"../Save/SaveFile.dat"


#define		VK_DRAW		VK_LBUTTON
#define		VK_RESETPOS	VK_RBUTTON
#define		VK_UNDO		'Z'		 
#define		VK_REDO		'X'
#define		VK_SETTARGET	VK_SHIFT
#define		VK_UNDOTARGET	'C'
#define		VK_SAVE		'S'
#define		VK_LOAD		'A'


#define		VK_SCROLL VK_SPACE

extern		HWND	g_hWnd;
extern		HDC		g_hdc;
extern		float   g_Wheel;