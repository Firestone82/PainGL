#pragma once

#include <string>
#include <vector>

namespace StringUtils {
	inline std::vector<std::string> split(const std::string &string, const std::string &delimiter) {
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		std::vector<std::string> res;

		while ((pos_end = string.find(delimiter, pos_start)) != std::string::npos) {
			token = string.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back (token);
		}

		res.push_back(string.substr(pos_start));
		return res;
	}

	inline bool startsWith(const std::string &string, const std::string &start) {
		return string.rfind(start, 0) == 0;
	}

	inline bool endsWith(const std::string &string, const std::string &end) {
		return string.rfind(end) == (string.size() - end.size());
	}
}


