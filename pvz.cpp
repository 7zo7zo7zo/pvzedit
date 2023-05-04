#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

HANDLE hpro;

bool running;

BOOL WINAPI consoleHandler(DWORD signal) {
	switch(signal) {
		case CTRL_C_EVENT:
  		running = false;
			cout << endl << "Exiting..." << endl;
			CloseHandle(hpro);
			exit(0);
  	  return true;
	  default:
	    return false;
	}
}

void WriteMemory(DWORD val, DWORD size, DWORD base, int argnum, ...) {
	if (!hpro)
		return;
	if (size > 4)
		size = 4;
	if (argnum == 0) {
		if(WriteProcessMemory(hpro, LPVOID(base), &val, size, 0)) {
			//MessageBox(NULL, "WriteProcessMemory worked.", "Success", MB_OK + MB_ICONINFORMATION);
		cout << "Success!" << endl;
		}
		else {
			MessageBox(NULL, "Error cannot WriteProcessMemory!", "Error", MB_OK + MB_ICONERROR);
		}
	}
	else {
		DWORD temp;
		ReadProcessMemory(hpro, LPCVOID(base), &temp, 4, 0);
		va_list args;
		va_start(args, argnum);
		for (int i = 1; i < argnum; ++i) {
			ReadProcessMemory(hpro, LPCVOID(temp + va_arg(args, int)), &temp, 4, 0);
		}
		if(WriteProcessMemory(hpro, LPVOID(temp + va_arg(args, int)), &val, size, 0)) {
			//MessageBox(NULL, "WriteProcessMemory worked.", "Success", MB_OK + MB_ICONINFORMATION);
			cout << "Success!" << endl;
		}
		else {
			MessageBox(NULL, "Error cannot WriteProcessMemory!", "Error", MB_OK + MB_ICONERROR);
		}
		va_end(args);
  }
}

void mainLoop() {
	while(running) {
		cout << "What would you like to modify? ";
		string input;
		cin >> input;
		
		if(input == "exit" || input == "quit" || input == "q") {
			break;
		}
		if(input == "sun") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(newdata, 4, 0x6A9EC0, 2, 0x768, 0x5560);
		}
		else if(input == "money") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(newdata/10, 4, 0x6a9ec0, 2, 0x82c, 0x28);
		}
		else if(input == "fertilizer") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(1000 + newdata, 4, 0x6a9ec0, 2, 0x82c, 0x1f8);
		}
		else if(input == "bugspray") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(1000 + newdata, 4, 0x6a9ec0, 2, 0x82c, 0x1fc);
		}
		else if(input == "chocolate") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(1000 + newdata, 4, 0x6a9ec0, 2, 0x82c, 0x228);
		}
		else if(input == "treefood") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(1000 + newdata, 4, 0x6a9ec0, 2, 0x82c, 0x230);
		}
		else if(input == "pause") {
			WriteMemory(1, 4, 0x6a9ec0, 2, 0x768, 0x164);
			system("pause");
			WriteMemory(0, 4, 0x6a9ec0, 2, 0x768, 0x164);
		}
		else if(input == "adventure") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0x24);
		}
		else if(input == "slots" || input == "seedslots") {
			cout << "What would you like this value to be? (anything greater than 10 will crash)";
			int newdata;
			cin >> newdata;
			WriteMemory(newdata, 4, 0x6a9ec0, 3, 0x768, 0x144, 0x24);
		}
		else if(input == "limbo") {
			WriteMemory(144, 1, 0x42df5d, 0);
			WriteMemory(144, 1, 0x42df5e, 0);
			WriteMemory(144, 1, 0x42df5f, 0);
		}
		else if(input == "nolimbo") {
			WriteMemory(136, 1, 0x42df5d, 0);
			WriteMemory(89, 1, 0x42df5e, 0);
			WriteMemory(84, 1, 0x42df5f, 0);
		}
		else if(input == "tree" || input == "treeheight") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0xf4);
		}
		else if(input == "jack" || input == "jackperc" || input == "jackpercent") {
			cout << "What would you like this value to be? (don't use 0) ";
			float newdata;
			cin >> newdata;
			WriteMemory(100/newdata, 4, 0x522FE0, 0);
		}
		else if(input == "end" || input == "endlevel") {
			WriteMemory(1, 4, 0x6a9ec0, 2, 0x768, 0x5604);
		}
		else if(input == "times" || input == "timesbeaten" || input == "adventuretimesbeaten") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0x2c);
		}
		else if(input == "namelength" || input == "usernamelength") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0x14);
		}
		else if(input == "vasebreaker" || input == "vasebreakerrecord") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0x11c);
		}
		else if(input == "izombie" || input == "izombierecord") {
			cout << "What would you like this value to be? ";
			int newdata;
			cin >> newdata;
			WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0x144);
		}
		else if(input == "butter" || input == "butterperc" || input == "butterpercent") {
			cout << "What would you like this value to be? (don't use 0) ";
			float newdata;
			cin >> newdata;
			WriteMemory(100/newdata, 4, 0x45F1E1, 0);
		}
		else if(input == "wallnutperc" || input == "wallnutpercent" || input == "wallnutdownperc" || input == "wallnutdownpercent") {
			cout << "What would you like this value to be? (don't use 0) ";
			float newdata;
			cin >> newdata;
			WriteMemory(100/newdata, 4, 0x4630F0, 0);
		}
	}
}

int main() {
	if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
		printf("\nERROR: Could not set control handler"); 
		return 1;
	}
	HWND hWnd = FindWindow(0, "Plants Vs. Zombies");
	if(hWnd == 0) {
		MessageBox(0, "Error cannot find window.", "Error", MB_OK|MB_ICONERROR);
	}
	else {
			DWORD proccess_ID;
			GetWindowThreadProcessId(hWnd, &proccess_ID);
			hpro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proccess_ID);
			if(!hpro) {
	  			MessageBox(0, "Could not open the process!", "Error!", MB_OK|MB_ICONERROR);
			}
		else {
			running = true;
			mainLoop();
		}
		CloseHandle(hpro);
	}
	return 0;
}
