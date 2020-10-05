# BonusWheel Refactored

All child classes of ItemDrop have been removed and Items are now created directly within ItemDrop.

WheelMaker class was removed and it's functions have been moved to Wheel class.

The 1000 spins test and item creation test now print results to screen with a new showLog function added to the UnitTests class, which allows the developer to dynamically display messages on screen.
