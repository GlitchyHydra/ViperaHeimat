#pragma once

namespace Vipera
{
	class GameTimer
	{
	public:
		GameTimer();

		//in seconds
		inline float TotalTime() const;
		inline float DeltaTime() const;

		void Reset();//Call before message loop
		void Start();// Call when unpaused
		void Stop();// call when paused
		void Tick();// Call every frame

	private:
		double mSecondsPerCount;
		double mDeltaTime;

		__int64 mBaseTime;
		__int64 mPausedTime;
		__int64 mStopTime;
		__int64 mPrevTime;
		__int64 mCurrTime;

		bool mStopped;
	};
}