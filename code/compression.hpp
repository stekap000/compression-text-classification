#pragma once

#include <vector>
#include <string>
#include "util.hpp"

namespace ctc {
	std::vector<u16> &lzw_encode(u16 dict_size, std::string);
}
