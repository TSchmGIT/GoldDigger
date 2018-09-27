#pragma once
#include <iostream>

#define CC_WHITE	15
#define CC_YELLOW	14
#define CC_RED		12

#define SET_CONSOLE_TEXT_COLOR(cc_color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cc_color)

#define LOG_INFO(text)		SET_CONSOLE_TEXT_COLOR(CC_WHITE);	std::cout << text << std::endl;
#define LOG_WARNING(text)	SET_CONSOLE_TEXT_COLOR(CC_YELLOW);	std::cout << text << std::endl;
#define LOG_ERROR(text)		SET_CONSOLE_TEXT_COLOR(CC_RED);		std::cout << text << std::endl;