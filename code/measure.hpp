#pragma once

#include <string>
#include <functional>

#include "util.hpp"

namespace ctc {
	int lzw_measure(std::string &text, lzw_encode_functional lzw);
	int lzw_distance(std::string &a, std::string &b, lzw_encode_functional lzw);
	float lzw_similarity(std::string &a, std::string &b, lzw_encode_functional lzw);
}
