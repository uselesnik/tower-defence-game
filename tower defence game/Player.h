#pragma once
class Player
{
	int health, money, placingMode, score, highscore;
public:
	Player();
	
	int getHealth();
	int getMoney();
	int getMode();

	void setHealth(int x);
	void setMoney(int x);
	void setMode(int x);

};

