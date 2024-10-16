#pragma once
//-----------------------------------------------------------------------
// CGame
// 
// Erkl�rung : Eine weitestgehend leere Klasse, 
//             sinnf�llig in eine Windows-Applikation eingebettet,
//             um ein Spiel bzw. eine 3D-Simulation zu erzeugen
// Autor     : Prof. Dr. Tobias Breiner
// Ort       : Pfungstadt
// Zeit      : seit Aug. 2011 (mit seitdem st�ndigen Verbesserungs-Updates)
// Copyright : Tobias Breiner  
// Disclaimer: Nutzung auf eigene Gefahr, keine Gew�hr, no warranty!
//------------------------------------------------------------------------


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#endif
#endif


#include "Vektoria\Root.h"

using namespace Vektoria;


class CGame
{
public:
	// Wird vor Begin einmal aufgerufen (Konstruktor):
	CGame(void);																				

	// Wird nach Ende einmal aufgerufen (Destruktor):
	~CGame(void);																				

	// Wird zu Begin einmal aufgerufen:
	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	

	// Wird w�hrend der Laufzeit bei jedem Bildaufbau aufgerufen:
	void Tick(float fTime, float fTimeDelta);						

	// Wird am Ende einmal aufgerufen:
	void Fini();																				

	// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergr��e ver�ndert hat:
	void WindowReSize(int iNewWidth, int iNewHeight);											

	// Holt das minimale Zeitdelta zur eventuellen Frame-Rate-Beschr�nkung:
	float GetTimeDeltaMin();																	

	// Holt die Versionsnummer:
	float GetVersion();


private:

	// Die Wurzel des Szenengrafen: 
	CRoot m_zr; 

	// Hier ist Platz f�r Deine weiteren Vektoriaobjekte:
	CScene m_zs;
	CFrame m_zf;
	CViewport m_zv;
	CCamera m_zc;
	CDeviceKeyboard m_zdk;
	CPlacement m_zpCamera;
	CGeoTerrain m_zgTerrainOri; // Gesamtes Terrain
	CGeoTerrain m_zgTerrain; // Inselausschnitt
	CGeoTerrain m_zgWater; // Wasserausschnitt
	CPlacement m_zpLandscape; // Insel- & Wasserplacement

	CPerlin* m_pperlin = nullptr;// Perlin Noise

	CBlob* m_pblob = nullptr; // Erhebung aus dem Meer
	CBlob* m_pblob2 = nullptr; // Erhebung aus dem Meer
	CBlob* m_pblob3 = nullptr; // Erhebung aus dem Meer
	CBlob* m_pblob4 = nullptr; // Erhebung aus dem Meer
	CBlob* m_pblob5 = nullptr; // Erhebung aus dem Meer
	
	CCut m_cutUnderSea; // Schnitt unter N.N.
	CMaterial m_zmWater; // Wellenmaterial
	CMaterial m_zmEarth; // Erdmaterial
	CGeos m_zgsCollision, m_zgsHeight; // Kollisionscontainer
	CGeoTerrains m_zgsTerrain; // Terrainkollisionscontainer


};


