#include <Game.hpp>

#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <cstdlib>

void PrintVersion()
{
	std::cout << "9002Game version " << VERSION_GIT << std::endl;
}

void PrintHelp(const char* program_name)
{
	std::cout << "Usage: " << program_name << " [OPTIONS]\n"
	          << "Options:\n"
	          << "  -v, --version         Show version information\n"
	          << "  -h, --help           Show this help message\n"
	          << "  -i, --input VALUE    Set input value (integer)\n"
	          << "  -t, --toggle          Random toggle\n"
	          << std::endl;
}

int main(int argc, char* argv[])
{
	int exampleValue = 0;
	bool isToggled = false;

	// Defined options
	static struct option longOptions[] = {
		{"version", no_argument,       0, 'v'},
		{"help",    no_argument,       0, 'h'},
		{"input",   required_argument, 0, 'i'},
		{"toggle",   no_argument,      0, 't'},
		{0, 0, 0, 0}
	};

	int optionIndex = 0;
	int c;

	// Parsing of commands
	while ((c = getopt_long(argc, argv, "vhi:t", longOptions, &optionIndex)) != -1) {
		switch (c) {
			case 'v':
				PrintVersion();
				return 0;
			case 'h':
				PrintHelp(argv[0]);
				return 0;
			case 'i':
				exampleValue = std::atoi(optarg);
				std::cout << "Example input value set to: " << exampleValue << std::endl;
				break;
			case 't':
				isToggled = true;
				std::cout << "isToggled is toggled on (" << isToggled << ')' << std::endl;
				break;
			case '?':
				// Invalid option or missing argument
				std::cerr << "Use -h or --help for usage information." << std::endl;
				return 1;
			default:
				std::cerr << "Unknown option" << std::endl;
				return 1;
		}
	}

	// Print any remaining non-option arguments
	if (optind < argc) {
		std::cout << "Non-option arguments: ";
		while (optind < argc) {
			std::cout << argv[optind++] << " ";
		}
		std::cout << std::endl;
	}

	// NOTE: This little argument demo could become useful in future.
	// The only issue would be that Microsoft Windows does not have unistd.h.

	Game game;
	game.Run();

	return 0;
}
