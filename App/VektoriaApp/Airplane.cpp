#include "Airplane.h"
#include <cmath>

CAirplane::CAirplane()
{
}

CAirplane::~CAirplane()
{
}

void CAirplane::Init(float damage, unsigned planeID)
{
	m_HitboxGeo.Init(5, 7, NULL, 6);
	m_HitboxGeo.SetDrawingOff();
	CHMat mat;
	mat.RotateX(HALFPI);
	m_HitboxGeo.Transform(mat);
	AddGeo(&m_HitboxGeo);

	m_planeID = planeID;
	m_damage = damage;
	this->AddPlacement(&m_zpPlaneCenter);

	for (int i = 0; i < 7; i++)
	{
		m_planeModel[i].Init(i);
		m_zpPlaneCenter.AddPlacement(&m_planeModel[i]);
		m_planeModel[i].SwitchOff();
	}
	m_planeModel[m_planeID].SwitchOn();

	m_zaPlaneSound[0].Init3D("sounds\\propeller.wav", 20.0F);
	m_zaPlaneSound[1].Init3D("sounds\\P40.wav", 70.0F);
	m_zaPlaneSound[2].Init3D("sounds\\B17.wav", 300.0F);
	m_zaPlaneSound[3].Init3D("sounds\\F4.wav", 100.0F);
	m_zaPlaneSound[4].Init3D("sounds\\Afterburner.wav", 200.0F);
	m_zaPlaneSound[5].Init3D("sounds\\Afterburner.wav", 150.0F);
	m_zaPlaneSound[6].Init3D("sounds\\Stealth.wav", 300.0F);

	for (int i = 0; i < 7; i++)
	{
		m_zaPlaneSound[i].SetVolume(1);
	}

	switch (m_planeID)
	{
	case 0:
	{
		m_flySpeed = 40;
		m_minFlySpeed = 30;
		m_maxFlySpeed = 100;
		m_flySpeedChangeRate = 15;
		SetHealth(70);
		break;
	}
	case 1:
	{
		m_flySpeed = 50;
		m_minFlySpeed = 40;
		m_maxFlySpeed = 110;
		m_flySpeedChangeRate = 17;
		SetHealth(90);
		break;
	}
	case 2:
	{
		m_flySpeed = 50;
		m_minFlySpeed = 40;
		m_maxFlySpeed = 90;
		m_flySpeedChangeRate = 5;
		SetHealth(200);
		break;
	}
	case 3:
	{
		m_flySpeed = 110;
		m_minFlySpeed = 100;
		m_maxFlySpeed = 180;
		m_flySpeedChangeRate = 35;
		SetHealth(100);
		break;
	}
	case 4:
	{
		m_flySpeed = 150;
		m_minFlySpeed = 130;
		m_maxFlySpeed = 230;
		m_flySpeedChangeRate = 40;
		SetHealth(110);
		break;
	}
	case 5:
	{
		m_flySpeed = 160;
		m_minFlySpeed = 150;
		m_maxFlySpeed = 280;
		m_flySpeedChangeRate = 40;
		SetHealth(120);
		break;
	}
	case 6:
	{
		m_flySpeed = 120;
		m_minFlySpeed = 150;
		m_maxFlySpeed = 250;
		m_flySpeedChangeRate = 40;
		SetHealth(140);
		break;
	}

	}

	for (int i = 0; i < 7; i++)
	{
		m_zpPlaneCenter.AddAudio(&m_zaPlaneSound[i]);
		m_zaPlaneSound[i].SetVolume(1.0F);
	}

	m_zpPlaneTip.TranslateZDelta(-2);
	m_zpPlaneTip.RotateXDelta(-PI / 14.0f);

	m_zpPlaneCenter.AddPlacement(&m_zpPlaneTip);

	m_zpPlaneTip.AddPlacement(&m_BulletManager);
	m_BulletManager.Init(BULLETSPEED, m_damage);
	m_zaPlaneShot.Init3D("sounds\\PlaneShot.wav", 100.5F);
	m_zpPlaneTip.AddAudio(&m_zaPlaneShot);
}

void CAirplane::ReInit(unsigned planeID)
{
	m_planeID = planeID;

	for (int i = 0; i < 7; i++)
	{
		m_planeModel[i].SwitchOff();
		if (m_planeID == i) {
			m_planeModel[i].SwitchOn();
		}
	}
	switch (m_planeID)
	{
	case 0:
	{
		m_flySpeed = 40;
		m_minFlySpeed = 30;
		m_maxFlySpeed = 100;
		m_flySpeedChangeRate = 15;
		SetHealth(70);
		break;
	}
	case 1:
	{
		m_flySpeed = 50;
		m_minFlySpeed = 40;
		m_maxFlySpeed = 110;
		m_flySpeedChangeRate = 17;
		SetHealth(90);
		break;
	}
	case 2:
	{
		m_flySpeed = 50;
		m_minFlySpeed = 40;
		m_maxFlySpeed = 90;
		m_flySpeedChangeRate = 5;
		SetHealth(200);
		break;
	}
	case 3:
	{
		m_flySpeed = 110;
		m_minFlySpeed = 100;
		m_maxFlySpeed = 180;
		m_flySpeedChangeRate = 35;
		SetHealth(100);
		break;
	}
	case 4:
	{
		m_flySpeed = 150;
		m_minFlySpeed = 130;
		m_maxFlySpeed = 230;
		m_flySpeedChangeRate = 40;
		SetHealth(110);
		break;
	}
	case 5:
	{
		m_flySpeed = 160;
		m_minFlySpeed = 150;
		m_maxFlySpeed = 280;
		m_flySpeedChangeRate = 40;
		SetHealth(120);
		break;
	}
	case 6:
	{
		m_flySpeed = 120;
		m_minFlySpeed = 150;
		m_maxFlySpeed = 250;
		m_flySpeedChangeRate = 40;
		SetHealth(140);
		break;
	}

	}
}

void CAirplane::Tick(float fTime, float fTimeDelta)
{
	m_planeModel[m_planeID].Tick(fTime, fTimeDelta);
	m_BulletManager.Tick(fTime, fTimeDelta);
	this->SetTranslationSensitivity(m_flySpeed);
	m_vDirection = m_zpPlaneTip.GetPosGlobal()-m_zpPlaneCenter.GetPosGlobal();
	m_vDirection.Normal();
}

float CAirplane::ClampValue(float value, float minValue, float maxValue) {
	return max(minValue, min(value, maxValue));
}

void CAirplane::MovePlane(float& x, float& y, float fTimeDelta)
{
	// minimizes the maximum rotation per tick
	m_Xrotation = ClampValue(x, m_Xrotation - MAX_ROTATION_SPEED * fTimeDelta, m_Xrotation + MAX_ROTATION_SPEED * fTimeDelta);
	m_Yrotation = ClampValue(y, m_Yrotation - MAX_ROTATION_SPEED * fTimeDelta, m_Yrotation + MAX_ROTATION_SPEED * fTimeDelta);

	m_planeModel[m_planeID].RotateY(-m_Xrotation / 2);
	m_planeModel[m_planeID].RotateZDelta(-m_Xrotation * 5);
	m_planeModel[m_planeID].RotateXDelta(-m_Yrotation);

	// Move Plane and Camera
	float RotationX = x * 15;
	float RotationY = -y * 15;
	float MoveAD = 0, MoveWS = -1, MoveUD = 0;
	MoveWithCollisionDetection(fTimeDelta, true, MoveAD, MoveWS, MoveUD, RotationX, RotationY, m_zgsCollisionObjects);
}

void CAirplane::Shoot(float randFac)
{
	CHVector vRand;
	vRand.RandomDir();
	m_BulletManager.Shoot(m_zpPlaneTip.GetDirectionGlobal() + vRand * randFac);

	// SOUNDS
	m_zaPlaneShot.Start();
}

void CAirplane::SetSpeed(float change)
{
	m_flySpeed = ClampValue(m_flySpeed + m_flySpeedChangeRate * change, m_minFlySpeed, m_maxFlySpeed);
}

void CAirplane::ReduceSpeedWhenOutOfFuel()
{
	m_flySpeed = ClampValue(m_flySpeed - 5, 40, 200);
}

void CAirplane::StopSounds()
{
	for (int i = 0; i < 7; i++)
		m_zaPlaneSound[i].Stop();
}

void CAirplane::StartSounds()
{
	for (int i = 0; i < 7; i++)
	{
		if (m_planeID == i)
		{
			m_zaPlaneSound[i].Loop();
		}
		else
			m_zaPlaneSound[i].Stop();
	}
}

void CAirplane::SelectSounds(int iSelected)
{
	for (int i = 0; i < 7; i++)
	{
		if (i == iSelected)
		{
			m_zaPlaneSound[i].Loop();
		}
		else
			m_zaPlaneSound[i].Stop();
	}
}
