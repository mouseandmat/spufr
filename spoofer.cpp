#include <windows.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>

// define error for easier typing
#define ERROR(msg) MessageBoxA(0, msg, "fotrousch spoofer", MB_OK | MB_ICONERROR); return 0;


std::string random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

auto hackerlike_print(std::string prefix, std::string message, int dots) -> void
{
	// print message
	std::cout << prefix << " " << message;

	// loop through dots
	for (int i = 0; i < dots; i++)
	{
		// print a dot
		std::cout << ".";

		// sleep for half a sec
		Sleep(250);
	}

	// padding
	std::cout << "\n";
}

auto spoof(int seed) -> int
{
	// create seed message
	std::string seed_message = "applying seed value: ";
	seed_message.append(std::to_string(seed));

	// print seed message (hacker-like look, man!)
	hackerlike_print("[~]", seed_message, 3);

	// loop 2345 times (hacker-like look, man!)
	for (int i = 1; i < 2345; i++)
	{
		// print shit
		std::cout << "[" << i << "/2345] rewriting value '" << random_string(rand() % 32) << "' to '" << random_string(rand() % 32) << "'\n";

		// sleep
		Sleep(5);
	}

	// post spoof messages (hacker-like look, man!)
	hackerlike_print("[~]", "re-checking values", 3);
	hackerlike_print("[~]", "bypassing windows security", 3);
	hackerlike_print("[~]", "applying changes", 3);
	hackerlike_print("[~]", "cleaning traces", 3);

	// now do the actual spoof lol
	HKEY key;

	// open register
	RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\ControlSet001\\Control\\IDConfigDB\\Hardware Profiles\\0001\\"), &key);

	// define and set value
	std::string value = random_string(12);
	RegSetValueEx(key, TEXT("HwProfileGuid"), 0, REG_SZ, (LPBYTE)value.c_str(), strlen(value.c_str()) * sizeof(char));

	// close register
	RegCloseKey(key);

	// inform user 
	std::cout << "\n[!] everything seems correct! done!\n\n";

	// pause with trash method
	system("pause");

	return 0;
}

auto main(int argc, char** argv) -> int
{
	// set random seed by time
	srand(time(0));

	// change title
	SetConsoleTitleA("fotrousch spoofer [v 0.1a] ~ premium version");

	// first input variable for sections
	int section;

	// print sections and ask user for input
	std::cout << "[1] automatic spoof (recommended)\n";
	std::cout << "[2] manual spoof\n[+] choose (1/2): ";
	std::cin >> section;

	// check for automatic spoof
	if (section == 1)
	{
		// run automatic spoof
		std::cout << "\n[!] automatic spoof is running;\n";
		spoof(rand());
	}

	// check for manual spoof
	else if (section == 2)
	{
		// define seed variable
		int seed;

		// ask user for seed input
		std::cout << "[+] input manual spoofing seed (0-2147483647): ";
		std::cin >> seed;

		// check for seed validity
		if (seed >= 0 && seed <= 2147483647)
		{
			// spoof
			std::cout << "\n[!] manual spoof is running;\n";
			spoof(seed);			
		}

		// invalid spoof seed value
		else
		{
			// inform user 
			ERROR("invalid spoof seed value");
		}
	}

	// invalid section
	else
	{
		// inform user 
		ERROR("invalid section selection");
	}

	// end
	return 0;
}