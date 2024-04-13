#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

namespace ctc {
	std::vector<std::string> &read_sentences_from_text_file(std::string filename);
}

