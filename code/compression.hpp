#pragma once

#include <vector>
#include <string>
#include "util.hpp"

namespace ctc {
	std::vector<u16> &lzw_encode(u16 dict_size, std::string &text);
	std::string &lzw_decode(u16 dict_size, std::vector<u16> &comp_text);

	std::vector<u16> &lzw_encode_8192(std::string &text);
	std::vector<u16> &lzw_encode_4096(std::string &text);
	std::vector<u16> &lzw_encode_2048(std::string &text);
	std::string &lzw_decode_8192(std::vector<u16> &comp_text);
	std::string &lzw_decode_4096(std::vector<u16> &comp_text);
	std::string &lzw_decode_2048(std::vector<u16> &comp_text);
}
