#include <fstream>
#include <sstream>

#include "util.hpp"

namespace ctc {
	std::vector<std::string> &read_sentences_from_text_file(std::string filename) {
		std::vector<std::string> *sentences = new std::vector<std::string>();

		std::ifstream input;
		input.open(filename);
		if(input) {
			std::stringstream buffer;
			buffer << input.rdbuf();
			std::string text = buffer.str();
			input.close();

			sentences->push_back(std::string());
			for(std::string::iterator it = text.begin(); it != text.end(); ++it) {
				switch(*it) {
				case '.':
				case '?':
				case '!':
				case '\n':
				case '\r':
					sentences->push_back(std::string());
					break;
				default:
					(*sentences)[sentences->size() - 1].push_back(*it);
				}
			}
		}

		return *sentences;
	}
}

