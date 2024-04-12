#include "compression.hpp"

/*
  Normalized Information Distance:

  max{K(x|y), K(y|x)}
  This is distance measure between two objects in the context of Kolmogorov complexity.
  Reason for taking "max" is the following:
  K(x|y) - Minimal complexity of the program that will move us from y to x.
  K(y|x) - Minimal complexity of the program that will move us from x to y.
  Additionally, if some complexity "K" is needed for movement from "a" to "b", then any
  complexity larger than "K" is also capable of moving us from "a" to "b".
  With this in mind, by taking "max", we guarantee that we will end up with the complexity
  capable of moving us in both directions ie. it is invariant under direction, which is needed
  for standard notion of distance d(x,y)=d(y,x). In other words we are finding length of minimal
  program capable of both translations.

  
  
  NID(x,y) = max{K(x|y), K(y|x)} / max{K(x), K(y)}
           = (K(y) - I(x:y)) / K(y), I(x:y) = K(y) - K(y|x)
*/

#include <vector>
#include <unordered_map>
#include <iostream>

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
				if(next_code < dict_size) 
					(*dict)[token_wide] = next_code++;
				
				token_wide = *it;
			}
			
			token = token_wide;
		}

		if(!token.empty())
			out->push_back(dict->at(token));

		return *out;
	}


}
