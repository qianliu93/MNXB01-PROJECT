#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <string>


namespace error {
	enum Error {
		none, space, no_filename
	};
}


std::string* fetch_command_list(std::string* argv);

struct Command_list {
	Command_list() : last(fetch_command_list(command_list)){}
	std::string* begin() { return command_list; }
	std::string* end() { return last; }

	int size() { return last-command_list; }

private:
	std::string command_list[16], * last;
};

void command_line_loop();





#endif
