using namespace std;
#define WINVER 0x0500
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <iostream>

void pressColorFilter();
void updateColorFilter();
void setColorFilter(boolean);
void setColorFilterRegistry(boolean);

int main()
{
	time_t currentTime;
	struct tm localTime;

	time(&currentTime);
	cout << currentTime;
	localtime_s(&localTime, &currentTime);

	int hour = localTime.tm_hour;

	// if time is less than 4:00, do black and white
	setColorFilter(hour < 16 ? true : false);

	return 0;
}

void setColorFilter(boolean mode)
{
	setColorFilterRegistry(mode);
	updateColorFilter();
}

void setColorFilterRegistry(boolean mode) {
	HKEY hKey;
	LPCTSTR sk = TEXT("SOFTWARE\\Microsoft\\ColorFiltering");

	LONG openRes = RegOpenKeyEx(HKEY_CURRENT_USER, sk, 0, KEY_ALL_ACCESS, &hKey);

	if (openRes == ERROR_SUCCESS) {
		printf("Success opening key.");
	}
	else {
		printf("Error opening key.");
		printf("%ld", openRes);
	}

	LPCTSTR value = TEXT("Active");
	DWORD data = mode;

	LONG setRes = RegSetValueEx(hKey, value, 0, REG_DWORD, (const BYTE*)&data, sizeof(data));

	if (setRes == ERROR_SUCCESS) {
		printf("Success writing to Registry.");
	}
	else {
		printf("Error writing to Registry.");
		printf("%ld", setRes);
	}

	LONG closeOut = RegCloseKey(hKey);

	if (closeOut == ERROR_SUCCESS) {
		printf("Success closing key.");
	}
	else {
		printf("Error closing key.");
		printf("%ld", closeOut);
	}

	return;
}

void updateColorFilter()
{
	pressColorFilter();
	pressColorFilter();

	return;
}

void pressColorFilter()
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "Ctrl" key
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Press the "Windows" key
	ip.ki.wVk = VK_LWIN;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Press the "C" key
	ip.ki.wVk = 'C';
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "C" key
	ip.ki.wVk = 'C';
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "Ctrl" key
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "Windows" key
	ip.ki.wVk = VK_LWIN;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	return;
}