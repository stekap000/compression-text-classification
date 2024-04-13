#pragma once

#include <cstdint>
#include <string>
#include <functional>

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

namespace ctc {
	using lzw_encode_functional = std::function<std::vector<u16>&(std::string&)>;	
}

