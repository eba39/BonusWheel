/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Null_Item.cpp
*     Description:
*
*
*
*/


#include<iostream>
#include "Null_Item.h"
#include "Definitions.h"

bool Null_Item::use(Player player) {
	player.addLife(-1000000);
	return false;
}

Null_Item::Null_Item()
	:ItemDrop("Null_Item :(", 0, IMG_CLOSE_NORMAL, 0) {

}