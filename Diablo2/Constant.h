#pragma once

#include "Enum.h"

const int WINSIZEX = 800;
const int WINSIZEY = 600;

//액트1 타일갯수
const int ACT1_TILEX = 60;
const int ACT1_TILEY = 60;

const int ACT2_TILEX = 60;
const int ACT2_TILEY = 60;

//타일사이즈(고정)
const int TILESIZEX = 160;
const int TILESIZEY = 80;

//오브젝트 사이즈(고정)
const int OBJSIZEX = 512;
const int OBJSIZEY = 512;

//타일개수,오브젝트개수
const int OBJNUM = 46;
const int TILENUM = 187;

const float PLAYER_SPEED = 300.f;
const float ACTMON1_SPEED = 75.f;

const DWORD	KEY_LEFT	= 0x00000001; //	  0001
const DWORD	KEY_RIGHT	= 0x00000002; //	  0010
const DWORD	KEY_UP		= 0x00000004; //	  0100
const DWORD	KEY_DOWN	= 0x00000008; //	  1000
const DWORD	KEY_RETURN	= 0x00000010;  //0001 0000
const DWORD	KEY_SPACE	= 0x00000020;  //0010 0000 
const DWORD	KEY_LBUTTON	= 0x00000040; // 0100 0000
const DWORD	KEY_A		= 0x00000080; // 1000 0000
const DWORD KEY_RBUTTON = 0x00000100;
const DWORD KEY_F2		= 0x00000200;
const DWORD	KEY_F1		= 0x00000400;
const DWORD	KEY_I			= 0x00000800;
const DWORD	KEY_Q			= 0x00001000;
const DWORD	KEY_C			= 0x00002000;
const DWORD	KEY_K			= 0x00004000;
const DWORD	KEY_1			= 0x00008000;
const DWORD	KEY_2			= 0x00010000;
const DWORD	KEY_3			= 0x00020000;
const DWORD	KEY_4			= 0x00040000;