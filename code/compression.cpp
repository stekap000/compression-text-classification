#include <vector>
#include <unordered_map>
#include <iostream>

#include "compression.hpp"
#include "util.hpp"

namespace ctc {
	std::vector<u16> &lzw_encode(u16 dict_size, std::string &text) {
		std::vector<u16> *out = new std::vector<u16>();
		std::unordered_map<std::string, u16> *dict = new std::unordered_map<std::string, u16>();
	
		for(u16 i = 0; i < 256; ++i)
			(*dict)[std::string(1, (char)i)] = i;
	
		u16 next_code = 256;
		std::string token;
		std::string token_wide;
		
		// Loop through symbols until we form token that does not exist in the dictionary.
		// Then, spit out code for token that is current token minus last character and store
		// current token into dictionary.
		for(std::string::iterator it = text.begin(); it != text.end(); ++it) {
			token_wide.push_back(*it);
			
			if(dict->find(token_wide) == dict->end()) {
				out->push_back(dict->at(token));
				
				if(next_code < dict_size)
					(*dict)[token_wide] = next_code++;
				
				token_wide = *it;
			}
			
			token = token_wide;
		}

		// Handle edge case.
		if(!token.empty())
			out->push_back(dict->at(token));
	
		return *out;
	}

	std::string &lzw_decode(u16 dict_size, std::vector<u16> &comp_text) {
		std::string *out = new std::string();
		std::unordered_map<u16, std::string> *dict = new std::unordered_map<u16, std::string>();

		for(u16 i = 0; i < 256; ++i)
			(*dict)[i] = std::string(1, (char)i);

		u16 next_code = 256;
		std::string prev_token;
		std::string token;

		// Loop through codes and construct dictionary on the fly by merging current token's
		// first symbol with the previous token. Then spit out token for given code.
		// This is possible since we spit out code (during compression) for token minus last
		// symbol before storing token into dictionary.
		for(std::vector<u16>::iterator it = comp_text.begin(); it != comp_text.end(); ++it) {
			token = (*dict)[*it];

			// Construct dictionary entry.
			if(next_code < dict_size && prev_token.size() != 0)
				(*dict)[next_code++] = prev_token + token[0];
			
			*out = *out + dict->at(*it);
			prev_token = token;
		}

		return *out;
	}

	// TODO: Maybe do this with non-type template and move to non cpp file.
	std::vector<u16> &lzw_encode_8192(std::string &text) {
		return lzw_encode(8192, text);
	}
	
	std::vector<u16> &lzw_encode_4096(std::string &text) {
		return lzw_encode(4096, text);
	}
	
	std::vector<u16> &lzw_encode_2048(std::string &text) {
		return lzw_encode(2048, text);
	}

	std::string &lzw_decode_8192(std::vector<u16> &comp_text) {
		return lzw_decode(8192, comp_text);
	}
	
	std::string &lzw_decode_4096(std::vector<u16> &comp_text) {
		return lzw_decode(4096, comp_text);
	}
	
	std::string &lzw_decode_2048(std::vector<u16> &comp_text) {
		return lzw_decode(2048, comp_text);
	}
}
