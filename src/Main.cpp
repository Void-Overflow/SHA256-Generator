#include "sha256.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <future>
#include <functional>
#include <chrono>

template <typename T>
std::string ConvertToString(T Number){
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}
void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

std::string coloredMSG(std::string MSG) { 
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	HANDLE hConsolec = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hConsolec, 3);
	std::cout << MSG << std::endl;
	return MSG;
}  

int main() {
	while (true) {
		auto WelcomeMSG = std::async(std::launch::async, coloredMSG,"Welcome to SHA256 Generator! Please enter the string you would like to convert to a hash:");
		std::string input;
		std::cin >> input;
		std::cout << "Hash - " << sha256(input);
		auto hash = ConvertToString(sha256(input));

		std::ofstream file;
		file.open("HashLog.txt", std::ios_base::app);
		file << input << "||" << hash << '\n' << "--------------------------" << '\n';
		file.close();

		std::cout << std::endl;
		std::cout << std::endl;
		bool autoConfirmation = true;
		std::string response;
		auto nextMSG = std::async(std::launch::async, coloredMSG, "Would you like to convert another hash? Please enter either yes or no for your respose.");
		std::cin >> response;
	
		if (response == "no")
			return 0;
		while (response != "yes") {
			if (response == "disable") {
				autoConfirmation = false;
				clear();
				break;
			}
			else {
				if (autoConfirmation == true) {
					std::cout << std::endl;
					auto repeatMSG = std::async(std::launch::async, coloredMSG, "Sorry I didn't get that. Can you try typing either yes or no again?");
					std::string responseRepeat;
					std::cin >> responseRepeat;
					if (responseRepeat == "yes" || responseRepeat == "no") {
						if (responseRepeat == "no")
							return 0;
						clear();
						break;
					}
				}
			}
			break;
		}
		clear();
	}
	return 0;
}