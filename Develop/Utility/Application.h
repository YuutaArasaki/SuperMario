#pragma once
#include "Singleton.h"
#include <string>
#include "../Scene/SceneManager.h"

#define D_SUCCESS		(0)		//成功
#define D_FAILURE		(-1)	//失敗
#define D_WIN_MAX_X		(672)	// スクリーンサイズ（幅）
#define D_WIN_MAX_Y		(864)	// スクリーンサイズ（高さ）
#define D_COLOR_BIT		(32)	// カラービット

class Application : public Singleton<Application>
{
private:
	float delta_second;
	LONGLONG start_time;
	LONGLONG now_time;
	int refresh_rate;
	class SceneManager* scene;

public:
	Application();
	~Application();
	bool WakeUp();
	void Run();
	void Shutdown();
	int ErrorThrow(std::string error_log);
private:
	void UpdateDeLtaTime();
};

