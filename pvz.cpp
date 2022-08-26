#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

HANDLE hpro;

void WriteMemory(DWORD val, DWORD size, DWORD base, int argnum, ...) {
    if (!hpro)
        return;
    if (size > 4)
        size = 4;
    if (argnum == 0) {
        WriteProcessMemory(hpro, LPVOID(base), &val, size, 0);
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
	for(int i = 0; i < 5; i++) {
    	cout << "What would you like to modify? ";
    	string input;
		cin >> input;
		
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
	}
}

int main() {
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
			mainLoop();
		}
		CloseHandle(hpro);
	}
	return 0;
}
