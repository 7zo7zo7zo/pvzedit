#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

HANDLE hpro;
bool running;
string info;
//DWORD base = 0x6a9ec0;

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
		}
		else {
			MessageBox(NULL, "Error cannot WriteProcessMemory!", "Error", MB_OK + MB_ICONERROR);
		}
		va_end(args);
  }
}

void mainLoop() {
	while(running) {
#ifdef __unix__
		system("clear");
#else
		system("cls");
#endif
		cout << "1. sun" << endl;
		cout << "2. money" << endl;
		cout << "3. fertilizer" << endl;
		cout << "4. bug spray" << endl;
		cout << "5. chocolate" << endl;
		cout << "6. tree food" << endl;
		cout << "7. pause the game" << endl;
		cout << "8. current adventure level" << endl;
		cout << "9. number of seed slots" << endl;
		cout << "10. enable the limbo page" << endl;
		cout << "11. disable the limbo page" << endl;
		cout << "12. wisdom tree height" << endl;
		cout << "13. early jack explosion chance" << endl;
		cout << "14. end the current level" << endl;
		cout << "15. number of times adventure mode finished" << endl;
		cout << "16. username length" << endl;
		cout << "17. vasebreaker endless record" << endl;
		cout << "18. izombie endless record" << endl;
		cout << "19. kernel-pult butter chance" << endl;
		cout << "20. wall-nut rolls downward chance (wall-nut bowling)" << endl << endl;

		cout << "Enter the number of what you wish to modify: (0 to to exit) ";
		int input;
		cin >> input;

		int newdata;
		float newdataf;
		switch (input) {
			default:
				MessageBox(NULL, "Please enter a valid number.", "Error", MB_OK + MB_ICONERROR);
				break;
			case 0:
				running = false;
				cout << "Exiting..." << endl;
				break;
			case 1:
				cout << "Enter the amount of sun you wish to have: ";
				cin >> newdata;
				WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x768, 0x5560);
				break;
			case 2:
				cout << "Enter the amoutn of money you wish to have: (will be truncated to the tens place) ";
				cin >> newdata;
				WriteMemory(newdata/10, 4, 0x6a9ec0, 2, 0x82c, 0x28);
				break;
			case 3:
				cout << "Enter the amount of fertilizer you wish to have: ";
				cin >> newdata;
				WriteMemory(1000 + newdata, 4, 0x6a9ec0, 2, 0x82c, 0x1f8);
				break;
			case 4:
				cout << "Enter the amount of bug spray you wish to have: ";
				cin >> newdata;
				WriteMemory(1000 + newdata, 4, 0x6a9ec0, 2, 0x82c, 0x1fc);
				break;
			case 5:
				cout << "Enter the amount of chocolate you wish to have: ";
				cin >> newdata;
				WriteMemory(1000 + newdata, 4, 0x6a9ec0, 2, 0x82c, 0x228);
				break;
			case 6:
				cout << "Enter the amount of tree food you wish to have: ";
				cin >> newdata;
				WriteMemory(1000 + newdata, 4, 0x6a9ec0, 2, 0x82c, 0x230);
				break;
			case 7:
				cout << "Game paused. (press enter to unpause)";
				WriteMemory(1, 4, 0x6a9ec0, 2, 0x768, 0x164);
				cin.ignore();
				cin.get();
				WriteMemory(0, 4, 0x6a9ec0, 2, 0x768, 0x164);
				break;
			case 8:
				cout << "What would you like your current adventure level to be: (e.g. enter 50 for level 5-10) ";
				cin >> newdata;
				WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0x24);
				break;
			case 9:
				cout << "Enter the amount of seed slots you wish to have: (anything greater than 10 will crash)";
				cin >> newdata;
				WriteMemory(newdata, 4, 0x6a9ec0, 3, 0x768, 0x144, 0x24);
				break;
			case 10:
				cout << "Limbo Page enabled.";
				WriteMemory(144, 1, 0x42df5d, 0);
				WriteMemory(144, 1, 0x42df5e, 0);
				WriteMemory(144, 1, 0x42df5f, 0);
				break;
			case 11:
				cout << "Limbo Page disabled.";
				WriteMemory(136, 1, 0x42df5d, 0);
				WriteMemory(89, 1, 0x42df5e, 0);
				WriteMemory(84, 1, 0x42df5f, 0);
				break;
			case 12:
				cout << "Enter the amount of tree food you wish to have: ";
				cin >> newdata;
				WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0xf4);
				break;
			case 13:
				cout << "Enter the desired early jack percentage: (don't use 0) ";
				cin >> newdataf;
				WriteMemory(100/newdataf, 4, 0x522FE0, 0);
				break;
			case 14:
				cout << "Current level ended.";
				WriteMemory(1, 4, 0x6a9ec0, 2, 0x768, 0x5604);
				break;
			case 15:
				cout << "Enter the desired amount of how many times adventure mode has been finished: ";
				cin >> newdata;
				WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0x2c);
				break;
			case 16:
				cout << "Enter your desired username length: ";
				cin >> newdata;
				WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0x14);
				break;
			case 17:
				cout << "Enter the desired vasebreaker endless record: ";
				cin >> newdata;
				WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0x11c);
				break;
			case 18:
				cout << "Enter the desired izombie endless record: ";
				cin >> newdata;
				WriteMemory(newdata, 4, 0x6a9ec0, 2, 0x82c, 0x144);
				break;
			case 19:
				cout << "Enter the desired kernel-pult butter percentage (don't use 0) ";
				cin >> newdataf;
				WriteMemory(100/newdataf, 4, 0x45F1E1, 0);
				break;
			case 20:
				cout << "Enter the desired wall-nut rolling downward percentage: (don't use 0) ";
				cin >> newdataf;
				WriteMemory(100/newdataf, 4, 0x4630F0, 0);
				break;
		}
	}
}

int main() {
	if (!SetConsoleCtrlHandler(consoleHandler, true)) {
		MessageBox(0, "Error could not set control handler.", "Error", MB_OK|MB_ICONERROR);
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
