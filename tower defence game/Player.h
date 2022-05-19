#pragma once
class Player
{
	int health, money, placingMode, score, highscore;
public:
	Player();
	
	void resetPlayer();
	
	int getHealth();
	int getMoney();
	int getMode();
	int getScore();
	int getHighscore();

	void setHealth(int x);
	void setMoney(int x);
	void setMode(int x);
	void setScore(int x);
	void setHighscore(int x);
};

