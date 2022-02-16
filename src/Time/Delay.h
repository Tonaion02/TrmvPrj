#pragma once





class Delay
{
public:
	Delay(float coolDown);

	void start();
	void update(float deltaTime);
	bool isEnd();

	float getCoolDown() { return mCoolDown; }

private:
	float mCoolDown;
	float mTimePassed;
};