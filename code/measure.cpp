#include <string>
#include <functional>
#include <cmath>
#include <algorithm>

#include "measure.hpp"
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

namespace ctc {
	measure_type lzw_measure(std::string &text, lzw_encode_functional lzw) {
		return lzw(text).size();
	}
	
	measure_type lzw_distance(std::string &a, std::string &b, lzw_encode_functional lzw) {
		return std::abs(lzw_measure(a, lzw) - lzw_measure(b, lzw));
	}

	measure_type lzw_similarity(std::string &a, std::string &b, lzw_encode_functional lzw) {
		std::string ab = a + b;
		measure_type a_measure = lzw_measure(a, lzw);
		measure_type b_measure = lzw_measure(b, lzw);
		measure_type min_measure = std::min(a_measure, b_measure);
		measure_type max_measure = std::max(a_measure, b_measure);
		return 1.0f - ((lzw_measure(ab, lzw) - min_measure) / max_measure - 0.5f)*2;
	}
}
