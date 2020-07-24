#pragma once


#define ERRORCHK(sz) MessageBox(g_hWnd, sz, L"SYSTEM MESSAGE", MB_OK)
#define SAFE_DELETE(p) {if(p) {delete p; p = NULL;}}


#define PUSH_KEY(key) CKeyMgr::GetInstance()->PushKey(key)
