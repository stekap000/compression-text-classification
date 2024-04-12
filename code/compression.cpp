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
		for(std::string::iterator it = text.begin(); it != text.end(); ++it) {
			token_wide.push_back(*it);
			
			// If the wide token is not in the dictionary.
			if(dict->find(token_wide) == dict->end()) {
				out->push_back(dict->at(token));
				
				// If we did not exceed dictionary limit.
				if(next_code < dict_size) {
					(*dict)[token_wide] = next_code++;
					//std::cout << token_wide << " === " << (*dict)[token_wide] << std::endl;
				}
				
				token_wide = *it;
			}
			
			token = token_wide;
		}
	
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
		for(std::vector<u16>::iterator it = comp_text.begin(); it != comp_text.end(); ++it) {
			if(dict->find(*it) != dict->end())
				token = (*dict)[*it];

			if(next_code < dict_size && prev_token.size() != 0) {
				(*dict)[next_code++] = prev_token + token[0];
				//std::cout << next_code - 1 << " === " << (*dict)[next_code - 1] << std::endl;
			}
			
			*out = *out + dict->at(*it);
			//std::cout << dict->at(*it);
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
