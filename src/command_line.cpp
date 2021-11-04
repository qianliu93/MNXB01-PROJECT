#include <iostream>
#include <cstdlib>
#include <string>
#include <regex>
#include "WeatherDataVec.h"
#include "avg_periodtemp.h"
#include "global_temperature_regression.h"

#include "project.h"
#include "command_line.h"

std::string filename;
WeatherDataVec weather_data{datavec(filename)};

std::string* fetch_command_list(std::string* argv) {
	std::string line;
	std::regex re {" {2,}"};
	getline(std::cin, line);

	line = std::regex_replace(line, re, " ");

	while (line.find(" ") <= line.length()) {
		int a = line.find(" ");
		if(line.find("'") == 0) {
			line=line.substr(1, line.length() - 1);
			a = line.find("'");

			*argv++ = line.substr(0, a);

			line = line.substr(a + 1, line.length() - (a + 1));

		}else {
			*argv++ = line.substr(0, a);
			line = line.substr(a + 1, line.length() - (a + 1));
		}
	}
	*argv++ = line;

	return argv;
}

std::string next_command(std::string*& i) {
	return *i++;
}

void print_command_line_error(int error) {
	std::cout << "Error: " << error << ". Exiting..." << std::endl;
}

void print_help() {
	std::cout << "\nTeam G MNXB01 Project: Command-Line Interface\n" << std::endl;
	std::cout << "The commands follow the format\n  (command name) (argument1) (argument2) ...\nwith no extra symbols." << std::endl;
	std::cout << "For example,\n  global temperature regression 1920 1950\nruns the command \"global temperature regression\" on the int inputs";
	std::cout << " 1920 and 1950\n" << std::endl;
	std::cout << "The following commands are available:" << std::endl;
	std::cout << "  help\n    Prints this help text." << std::endl;
	std::cout << "  exit\n    Exits the CLI." << std::endl;
	std::cout << "  clear\n    Clears the command-line" << std::endl;
	std::cout << "  filename (path)\n    Loads the data from (path)." << std::endl;
	std::cout << "  where\n    Prints the current data path." << std::endl;
	std::cout << "  temperature over two periods (year1fr) (year1to) (year2fr) (year2to)\n    Compares average temperatures for the periods";
	std::cout << " (year1fr)-(year1to)\n    and (year2fr-year2to)." << std::endl;
	std::cout << "  global temperature regression (yearfr) (yearto)\n    Fits a simple linear+sinusoidal function to data in the period";
	std::cout << "\n    (yearfr)-(yearto)" << std::endl;
	std::cout << "  projectQL (month) (city)\n    Runs a number of analysis functions analyzing monthly data and covid data\n    for (city)." << std::endl;
	std::cout << "    The input (city) can be one of:\n      Boras, Falun, Karlstad, Lulea, \n";
	std::cout << "      Lund, Umea, Visby" << std::endl;
}

int execute_command_list(Command_list command_list) {

	std::string t;
	std::string* it = command_list.begin();

	t = next_command(it);

	if (t == "") {
		return 1;
	}
	else if (t == "exit") {
		return 0;
	}
	else if (t == "clear") {
		system("clear");
		return 1;
	}
	else if (t == "help") {
		print_help();
		return 1;
	}
	else if (t == "filename") {
		t = next_command(it);
		if (t == "") {
			print_command_line_error(error::no_filename);
			return 0;
		}
		filename = t;

		std::cout << "Loading weather data from \"" << filename << "\"..." << std::endl;
		weather_data = WeatherDataVec(filename);

		std::cout << "Done." << std::endl;

		return 1;
	}
	else if (t == "where") {
		std::cout << filename << std::endl;
		return 1;
	}
	else if (t == "temperature") {
		t = next_command(it);
		if(t == "over") {
			if(t == "two") {
				t = next_command(it);
				if(t == "periods") {
					int a1 = std::stoi(next_command(it));
					int b1 = std::stoi(next_command(it));
					int a2 = std::stoi(next_command(it));
					int b2 = std::stoi(next_command(it));
					std::cout << "Running \"temperature over two periods " << a1 << " " << b1 << " " << a2 << " " << b2 << "\"..." << std::endl;
					temperature_over_two_periods(a1, b1, a2, b2, weather_data);
				}
			}
		}
	}
	else if (t == "global") {
		t = next_command(it);
		if (t == "temperature") {
			t = next_command(it);
			if(t == "regression") {
				int a1 = std::stoi(next_command(it));
				int b1 = std::stoi(next_command(it));
				std::cout << "Running \"global temperature regression " << a1 << " " << b1 << "\"..." << std::endl;
				global_temperature_regression(a1, b1, weather_data);
			}
		}
	}
	else if (t == "projectQL") {
		int a1 = std::stoi(next_command(it));
		std::string city = next_command(it);
		std::cout << "Running \"projectQL " << a1 << " " << city << "\"..." << std::endl;
		projectQL(a1, city, filename);
	} else {
		print_help();
	}
	return 1;
}



void command_line_loop() {
	while (execute_command_list(Command_list()));
}
