#pragma once

struct Inputs
{
	static const float CONTROLLER_DEAD_ZONE;

	Inputs();
	void reset();
	//Port�e analogue -100 � 100
	static float eliminateVibration(float analogInput);
	bool fireBullet;
	float moveFactorX;
	float moveFactorY;

	bool startGameSwitch;
	bool leaveGameSwitch;

	bool returnToMainMenuSwitch;

	bool shouldFire;

};

