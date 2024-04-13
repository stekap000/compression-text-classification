#include <vector>
#include <string>
#include <functional>
#include <ctime>
#include <cmath>
#include <iostream> // TODO: Remove

#include "cluster.hpp"
#include "compression.hpp"

namespace ctc {
	std::ostream &operator<<(std::ostream &os, Cluster &c) {
		os << "(" << c.centroid << " ---> " << std::endl;
		for(std::string &s : c.strings)
			os << "\t+ " << s << " [" << lzw_similarity(c.centroid, s, lzw_encode_4096) << "]" << std::endl;
		os << ")" << std::endl;
		return os;
	}

	void replace_cluster_strings(std::vector<Cluster> &clusters, std::vector<std::string> &strings, lzw_encode_functional lzw) {
		for(Cluster &c : clusters)
			c.strings.clear();
		
		measure_type similarity_value;
		measure_type temp_measure;
		int chosen_cluster_index = 0;
		for(std::string &s : strings) {
			similarity_value = 0;

			for(int i = 0; i < clusters.size(); ++i) {
				Cluster c = clusters[i];
				temp_measure = lzw_similarity(s, c.centroid, lzw);
				if(temp_measure > similarity_value) {
					similarity_value = temp_measure;
					chosen_cluster_index = i;
				}
			}
			
			clusters[chosen_cluster_index].strings.push_back(s);
		}
	}

	void update_clusters_centroids(std::vector<Cluster> &clusters, std::unordered_map<std::string, measure_type> &string_measure_map) {
		int string_centroid_index = 0;
		measure_type measure_diff = 9999;
		measure_type cluster_measure = 0;
		for(Cluster &c : clusters) {
			string_centroid_index = 0;
			measure_diff = 9999;
			cluster_measure = 0;
			for(std::string &s : c.strings) {
				cluster_measure += string_measure_map[s];
			}
			
			cluster_measure /= c.strings.size();
			for(int i = 0; i < c.strings.size(); ++i) {
				measure_type temp_diff = abs(cluster_measure - string_measure_map[c.strings[i]]);
				if(temp_diff < measure_diff) {
					measure_diff = temp_diff;
					string_centroid_index = i;
				}
			}

			if(string_centroid_index < c.strings.size())
				c.centroid = c.strings[string_centroid_index];
		}
	}
	
	std::vector<Cluster> &lzw_k_means(std::vector<std::string> &strings, int n, lzw_encode_functional lzw, int iteration_count) {
		std::vector<Cluster> *clusters = new std::vector<Cluster>(3);
		if(n <= 0) return *clusters;
		
		std::unordered_map<std::string, measure_type> *string_measure_map = new std::unordered_map<std::string, measure_type>();
		for(std::string &s : strings)
			(*string_measure_map)[s] = lzw_measure(s, lzw);
			
		std::srand(time(0));

		// Take n random strings to be cluster centroids.
		for(Cluster &c : *clusters)
			c.centroid = strings[std::rand() % strings.size()];

		for(int i = 0; i < iteration_count; ++i) {
			// Place string into clusters such that they are most similar to centroid.
			replace_cluster_strings(*clusters, strings, lzw);

			// Update cluster centroid based on new string that they contain.
			update_clusters_centroids(*clusters, *string_measure_map);
		}
		
		return *clusters;
	}
}

