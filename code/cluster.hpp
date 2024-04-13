#pragma once

#include <ostream>
#include <vector>
#include <unordered_map>

#include "measure.hpp"

namespace ctc {
	struct Cluster {
		std::string centroid;
		std::vector<std::string> strings;
		//std::unordered_map<measure_type, std::string> string_map;

		friend std::ostream &operator<<(std::ostream &os, Cluster &c);
	};
	
	std::ostream &operator<<(std::ostream &os, Cluster &c);
	
	std::vector<Cluster> &lzw_k_means(std::vector<std::string> &strings, int n, lzw_encode_functional lzw, int iteration_count);
}
