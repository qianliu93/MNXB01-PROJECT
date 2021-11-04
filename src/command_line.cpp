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

		return 1;
	}
	else if (t == "filename") {
		t = next_command(it);
		if (t == "") {
			print_command_line_error(error::no_filename);
			return 0;
		}
		filename = t;

		weather_data = WeatherDataVec(datavec(filename));

		std::cout << "Done" << std::endl;

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
				global_temperature_regression(a1, b1, weather_data);
			}
		}
	}
	else if (t == "projectQL") {
		int a1 = std::stoi(next_command(it));
		std::string city = next_command(it);
		projectQL(a1, city, filename);
	}
	return 1;
}



void command_line_loop() {
	while (execute_command_list(Command_list()));
}
