#pragma once

#include <string>
#include <functional>

#include "util.hpp"

namespace ctc {
	int lzw_measure(std::string &text, std::function<std::vector<u16>&(std::string&)> lzw);
	int lzw_distance(std::string a, std::string b, std::function<std::vector<u16>&(std::string&)> lzw);
}
