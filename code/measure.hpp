#pragma once

#include <string>
#include <functional>

#include "util.hpp"

namespace ctc {
	using measure_type = float;
	using lzw_encode_functional = std::function<std::vector<u16>&(std::string&)>;	
	
	measure_type lzw_measure(std::string &text, lzw_encode_functional lzw);
	measure_type lzw_distance(std::string &a, std::string &b, lzw_encode_functional lzw);
	measure_type lzw_similarity(std::string &a, std::string &b, lzw_encode_functional lzw);
}
