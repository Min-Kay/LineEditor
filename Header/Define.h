#pragma once

#define		WINCX	800
#define		WINCY	600	
#define		PURE	= 0

#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1

#define		PI		3.141592f

#define		VK_MAX		0xff

#define		LINE_SAVE	L"../Save/LineSaveFile.dat"
#define		BLOCK_SAVE	L"../Save/BlockSaveFile.dat"

//Line Ű 
#define		VK_DRAW_LINE			VK_LBUTTON
#define		VK_DRAG_LINE			VK_RBUTTON
#define		VK_RESETPOS				VK_SPACE
#define		VK_UNDO_LINE			'Z'		 
#define		VK_REDO_LINE			'X'
#define		VK_SETTARGET_LINE		VK_SHIFT
#define		VK_ERASETARGET_LINE		'A'
#define		VK_ERASEDRAG_LINE		'S'
#define		VK_SAVE_LINE			'Q'
#define		VK_LOAD_LINE			'W'

//BLOCK Ű
#define		VK_DEFAULT_BLOCK		'U'
#define		VK_ITEM_BLOCK			'I'
#define		VK_INVISIBLE_BLOCK		'O'
#define		VK_BREAKABLE_BLOCK		'P'
#define		VK_UNDO_BLOCK			'C'		 
#define		VK_REDO_BLOCK			'V'
#define		VK_SETTARGET_BLOCK		VK_CONTROL
#define		VK_ERASETARGET_BLOCK	'D'
#define		VK_ERASEDRAG_BLOCK		'F'
#define		VK_DRAG_BLOCK			VK_RBUTTON
#define		VK_SAVE_BLOCK			'E'
#define		VK_LOAD_BLOCK			'R'

extern		HWND	g_hWnd;
extern		HDC		g_hdc;
extern		float   g_Wheel;