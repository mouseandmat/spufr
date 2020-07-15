// windows shit
#include <windows.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>

// obfuscation stuff
#include "xorstr.hpp"
#include "obfy.hpp"
#include "lazy_importer.hpp"

// define error for easier typing
#define ERROR(msg) LI_FIND(MessageBoxA)(0, msg, xorstr_("spot1fy spoofer"), MB_OK | MB_ICONERROR); RETURN(N(0));

// from stackoverflow, thanks! :-D
auto random_string(size_t length) -> std::string
{
	OBF_BEGIN

	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - N(1));
		return charset[LI_FIND(rand)() % max_index];
	};
	std::string str(length, N(0));
	std::generate_n(str.begin(), length, randchar);

	RETURN(str);
	OBF_END
}

// really cringe function
auto hackerlike_print(std::string prefix, std::string message, int dots) -> int
{
	OBF_BEGIN

	// print message
	std::cout << prefix << " " << message;

	// loop through dots
	int i;
	V(i) = N(0);
	FOR (V(i), V(i) < dots, V(i) = V(i) + N(1))
	{
		// print a dot
		std::cout << xorstr_(".");

		// sleep for half a sec
		LI_FIND(Sleep)(N(250));
	}
	ENDFOR

	// padding
	std::cout << xorstr_("\n");

	// return cause int
	RETURN(N(0));

	OBF_END
}

auto spoof(int seed) -> int
{
	OBF_BEGIN

	// create seed message
	std::string seed_message = xorstr_("applying seed value: ");
	seed_message.append(std::to_string(seed));

	// print seed message (hacker-like look, man!)
	hackerlike_print(xorstr_("[~]"), seed_message, N(3));

	// loop 2345 times (hacker-like look, man!)
	int i;
	V(i) = N(1);
	FOR (V(i), V(i) < N(2345), V(i) = V(i) + N(1))
	{
		// print shit
		std::cout << xorstr_("[") << V(i) << xorstr_("/2345] rewriting value '") << random_string(LI_FIND(rand)() % N(32)) << xorstr_("' to '") << random_string(LI_FIND(rand)() % N(32)) << xorstr_("'\n");

		// sleep
		LI_FIND(Sleep)(N(4));
	}
	ENDFOR

	// post spoof messages (hacker-like look, man!)
	hackerlike_print(xorstr_("[~]"), xorstr_("re-checking values"), N(3));
	hackerlike_print(xorstr_("[~]"), xorstr_("bypassing windows security"), N(3));
	hackerlike_print(xorstr_("[~]"), xorstr_("applying changes"), N(3));
	hackerlike_print(xorstr_("[~]"), xorstr_("cleaning traces"), N(3));

	// now do the actual spoof lol
	HKEY key;

	// open register
	LI_FIND(RegOpenKeyA)(HKEY_LOCAL_MACHINE, xorstr_("SYSTEM\\ControlSet001\\Control\\IDConfigDB\\Hardware Profiles\\0001\\"), &key);

	// define and set value
	std::string value = random_string(N(12));
	LI_FIND(RegSetValueExA)(key, xorstr_("HwProfileGuid"), N(0), REG_SZ, (LPBYTE)value.c_str(), LI_FIND(strlen)(value.c_str()) * sizeof(char));

	// close register
	LI_FIND(RegCloseKey)(key);

	// inform user 
	std::cout << xorstr_("\n[!] everything seems correct! done!\n\n");

	// pause with trash method
	LI_FIND(system)(xorstr_("pause"));

	RETURN(N(0));
	OBF_END
}

auto main(int argc, char** argv) -> int
{
	OBF_BEGIN

	// set random seed by time
	LI_FIND(srand)(time(0));

	// change title
	LI_FIND(SetConsoleTitleA)(xorstr_("spot1fy spoofer [v 0.1a] ~ premium version"));

	// first input variable for sections
	int section;

	// print sections and ask user for input
	std::cout << xorstr_("[1] automatic spoof (recommended)\n");
	std::cout << xorstr_("[2] manual spoof\n[+] choose (1/2): ");
	std::cin >> section;

	// check for automatic spoof
	IF (section == 1)
	{
		// run automatic spoof
		std::cout << xorstr_("\n[!] automatic spoof is running;\n");
		spoof(LI_FIND(rand)());
	}
	ENDIF

	// check for manual spoof
	IF (section == 2)
	{
		// define seed variable
		int seed;

		// ask user for seed input
		std::cout << xorstr_("[+] input manual spoofing seed (0-2147483647): ");
		std::cin >> seed;

		// check for seed validity
		IF (V(seed) >= N(0) && V(seed) <= N(2147483647))
		{
			// spoof
			std::cout << xorstr_("\n[!] manual spoof is running;\n");
			spoof(seed);			
		}

		// invalid spoof seed value
		ELSE
		{
			// inform user 
			ERROR("invalid spoof seed value");
		}
		ENDIF
	}
	ENDIF

	// invalid section
	IF(V(section) != N(1) || V(section) != N(2))
	{
		// inform user 
		ERROR("invalid section selection");
	}
	ENDIF

	// end
	RETURN(N(0));

	OBF_END
}