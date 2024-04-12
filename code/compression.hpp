#pragma once

#include <vector>
#include <string>
#include "util.hpp"

namespace ctc {
	std::vector<u16> &lzw_encode(u16 dict_size, std::string &text);
	std::string &lzw_decode(u16 dict_size, std::vector<u16> &comp_text);
}
