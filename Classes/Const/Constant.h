#pragma once
#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include"cocos2d.h"
#include <vector>
#include<string>

//space type
#define V_CORI 0
#define H_CORI 1
#define ROOM 2

//space exit info
#define NONE 0
#define E_UNAPPENDED 1
#define E_APPENDED 2

#define DOWN 1
#define RIGHT 2
#define UP 3
#define LEFT 4


extern std::vector<std::string> exitRightMaps;
extern std::vector<std::string> exitLeftMaps;
extern std::vector<std::string> exitUpMaps;
extern std::vector<std::string> exitDownMaps;
extern std::vector<std::string>  corridors;

//enum Direction { Centre, DOWN, RIGHT, UP, LEFT };

#endif