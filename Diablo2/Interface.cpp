#include "StdAfx.h"
#include "Interface.h"

CInterface::CInterface(void)
{
}

CInterface::~CInterface(void)
{
}

bool CInterface::SwitchSwap(bool bSwitch)
{
	if(bSwitch)
	{
		bSwitch = false;
	}
	else
	{
		bSwitch = true;
	}

	return bSwitch;
}