

//각도별 바라보는 방향 

		if(m_fAngle <= 292.5 && m_fAngle > 247.5)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND1)
				return;
			m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND1;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 247.5 && m_fAngle > 202.5)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND2)
				return;
			m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND2;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 202.5 && m_fAngle > 157.5)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND3)
				return;
			m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND3;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 157.5 && m_fAngle > 112.5)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND4)
				return;
			m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND4;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 112.5 && m_fAngle > 67.5)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND5)
				return;
			m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND5;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 67.5 && m_fAngle > 22.5)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND6)
				return;
			m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND6;
			m_iMaxCnt = 8;
		}
		if(m_fAngle > 337.5 || m_fAngle <= 22.5)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND7)
				return;
			m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND7;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 337.5 && m_fAngle > 292.5)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND8)
				return;
			m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND8;
			m_iMaxCnt = 8;
		}
		





/////컬링 하다만거 동굴컬링/////
//	for( int i = 1; i < 2; ++i)
//	{
//		//내위치
//
//		D3DXMatrixTranslation(&matTrans, m_vecTile[m_iPlayerIdx]->iX
//			, m_vecTile[m_iPlayerIdx]->iY, 0.f);
//
//		m_Info.matWorld = matTrans;
//
//		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);
//
//		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
//		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[m_iPlayerIdx]->iDrawID)
//			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
//		
//		//위
//		int		iIndex = m_iPlayerIdx - (ACT1_TILEX * 2)*i;
//
//		D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->iX
//			, m_vecTile[iIndex]->iY, 0.f);
//
//		m_Info.matWorld = matTrans;
//
//		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);
//
//		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
//		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
//			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
//		
//		// 오른쪽위
//		iIndex = m_iPlayerIdx - (ACT1_TILEX - (m_iPlayerIdx / ACT1_TILEX) % 2)*i;
//		
//		D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->iX
//			, m_vecTile[iIndex]->iY, 0.f);
//
//		m_Info.matWorld = matTrans;
//
//		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);
//
//		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
//		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
//			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));			
//
//
//		// 오른쪽
//		iIndex = m_iPlayerIdx + i; //+ 1 
//		
//		D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->iX
//			, m_vecTile[iIndex]->iY, 0.f);
//
//		m_Info.matWorld = matTrans;
//
//		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);
//
//		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
//		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
//			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
//
//
//		// 오른쪽아래
//		iIndex = m_iPlayerIdx + (ACT1_TILEX + (m_iPlayerIdx / ACT1_TILEX) % 2)*i;
//
//		D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->iX
//			, m_vecTile[iIndex]->iY, 0.f);
//
//		m_Info.matWorld = matTrans;
//
//		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);
//
//		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
//		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
//			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
//
//		// 아래
//		iIndex = m_iPlayerIdx + (ACT1_TILEX * 2) * i;
//
//		D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->iX
//			, m_vecTile[iIndex]->iY, 0.f);
//
//		m_Info.matWorld = matTrans;
//
//		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);
//
//		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
//		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
//			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
//
//		// 왼쪽아래
//		iIndex = m_iPlayerIdx + (ACT1_TILEX - 1 + (m_iPlayerIdx / ACT1_TILEX) % 2) * i;
//
//		D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->iX
//			, m_vecTile[iIndex]->iY, 0.f);
//
//		m_Info.matWorld = matTrans;
//
//		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);
//
//		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
//		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
//			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
//		
//		// 왼쪽
//		iIndex = m_iPlayerIdx - i; // - 1;
//
//		D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->iX
//			, m_vecTile[iIndex]->iY, 0.f);
//
//		m_Info.matWorld = matTrans;
//
//		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);
//
//		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
//		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
//			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
//		
//		// 왼쪽위
//		iIndex = m_iPlayerIdx - (ACT1_TILEX + 1 - (m_iPlayerIdx / ACT1_TILEX) % 2) * i;
//		
//		D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->iX
//			, m_vecTile[iIndex]->iY, 0.f);
//
//		m_Info.matWorld = matTrans;
//
//		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);
//
//		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
//		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
//			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
//
//	}
//////////////////////////////////////////////////////////////////////////////////