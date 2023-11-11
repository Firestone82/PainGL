#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <optional>

class Path {
	private:
		std::string path;

	public:
		Path(const std::string &path) : path(path) {
			std::replace(this->path.begin(), this->path.end(), '\\', '/');
		}

		std::string getDirectory() const {
			return this->path.substr(0, this->path.find_last_of('/'));
		}

		std::string getFileName() const {
			return this->path.substr(this->path.find_last_of('/') + 1);
		}

		std::string getFileNameWithoutExtension() const {
			std::string fileName = this->getFileName();
			fileName = fileName.substr(0, fileName.find_last_of('.'));

			// Trim trailing and leading whitespaces
			fileName.erase(0, fileName.find_first_not_of(' '));
			fileName.erase(fileName.find_last_not_of(' ') + 1);

			return fileName;
		}

		std::string getExtension() const {
			return this->path.substr(this->path.find_last_of('.'));
		}

		bool exists() const {
			return std::filesystem::exists(this->path);
		}

		std::string toString() const {
			return this->path;
		}
};

class File : public Path {
	public:
		File(const Path &path) : Path(path) {}

		std::string content() {
			std::ifstream file(this->toString());
			if (!file.is_open()) {
				return nullptr;
			}

			std::stringstream stream;
			stream << file.rdbuf();

			file.close();
			return stream.str();
		}
};

namespace FileUtils {
	/**
	 * @brief Get all files in a directory and its subdirectories
	 * @param path to the directory
	 * @param extension to filter files by
	 * @return A vector of file paths
	 */
	inline std::vector<Path> getFiles(const Path &path, const std::string &extension = "") {
		std::vector<Path> files;

		for (const auto &entry: std::filesystem::directory_iterator(path.toString())) {
			if (std::filesystem::is_directory(entry.path())) {
				std::vector<Path> subFiles = FileUtils::getFiles(entry.path().string(), extension);
				files.insert(files.end(), subFiles.begin(), subFiles.end());
			} else {
				std::string file = entry.path().string();
				std::string ext = file.substr(file.find_last_of('.'));

				if (extension.empty() || ext == extension) {
					files.push_back(Path(file));
				}
			}
		}

		return files;
	}

	/**
	 * @brief Find a file in a folder
	 * @param folderPath where to look for the file
	 * @param fileName of the file
	 * @param extension of the file
	 * @return Path to the file
	 */
	inline std::optional<Path> findFileInFolder(const Path &folderPath, const std::string &fileName, const std::string &extension = "") {
		std::vector<Path> files = getFiles(folderPath, extension);

		for (const auto &file: files) {
			std::string ext = "";
			if (fileName.find_last_of('.') != std::string::npos) {
				if (file.getFileName() == fileName) {
					return file;
				}
			}

			if (file.getFileNameWithoutExtension() == fileName) {
				return file;
			}
		}

		return std::nullopt;
	}
}