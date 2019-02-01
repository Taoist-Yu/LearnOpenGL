#pragma once

class Timer
{
	friend class MainWindow;
	friend class GLMainWindow;

public:
	Timer();
	~Timer();

	float GetTime();
	float GetDeltaTime();
	float GetTimeScale();
	float GetUnscaledTime();
	float GetUnscaledDeltaTime();
	void SetTimeScale(float timeScale);

	void TimerUpdate();

private:
	float time;
	float timeScale;
	float deltaTime;

};

extern Timer Time;