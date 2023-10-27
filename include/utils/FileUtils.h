#pragma once

#include "Logger.h"

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

namespace FileUtils {
	inline std::vector<std::string> getFiles(const std::string &path, const std::string &extension = "") {
		std::vector<std::string> files;

		for (const auto &entry: std::filesystem::directory_iterator(path)) {
			if (entry.path().extension() == extension || extension.empty()) {
				files.push_back(entry.path().string());
			}
		}

		return files;
	}

	inline bool fileExists(const std::string &path) {
		return std::filesystem::exists(path);
	}

	inline std::string readFile(const std::string &path) {
		std::ifstream file(path);
		if (!file.is_open()) {
			Logger::info(R"(Failed to open file "%s")", path.c_str());
			return nullptr;
		}

		std::stringstream stream;
		stream << file.rdbuf();

		file.close();
		return stream.str();
	}

	inline std::string getFileExtension(std::string basicString) {
		return basicString.substr(basicString.find_last_of('.'));
	}

	inline std::string getFileName(const std::string &path) {
		std::string fileName = path.substr(path.find_last_of('/') + 1);
		return fileName.substr(0, fileName.find_last_of('.'));
	}
}