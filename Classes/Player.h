/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Player.h
*     Description: The Player class exists to hold the total values
*     of the items collected. Items are added by calling the Player's
*     corresponding addX function and passing an int value to add.
*     Items may also be taken this way by passing a negative value to
*     these same functions.
*/


#ifndef __PLAYER_H__
#define __PLAYER_H__


#include<iostream>
#include<string>

class Player {

private: 
	std::string Name;
	int numCoins, numLife, numGems, numHammers, numBrushes;


public:
	Player(std::string str);

	std::string getName();
	int getCoins();
	int getLife();
	int getGems();
	int getHammers();
	int getBrushes();

	bool addCoins(int n);
	bool addLife(int n);
	bool addGems(int n);
	bool addHammers(int n);
	bool addBrushes(int n);

};


#endif //__PLAYER_H__