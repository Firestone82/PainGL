#pragma once

#include <string>
#include <vector>
#include <functional>

class ConsoleCommand {
	private:
		std::string name;
		std::string description;
		std::string usage;

		int minArgs = 0;
		int maxArgs = 0;

		std::function<void(const std::vector<std::string>&)> callback;

		explicit ConsoleCommand(std::string name);

	public:
		std::string getName() const;
		std::string getDescription() const;
		std::string getUsage() const;
		int getMinArgs() const;
		int getMaxArgs() const;

		void execute(const std::vector<std::string> &args);

		class Builder {
			private:
				ConsoleCommand* consoleCommand;

			public:
				explicit Builder(const std::string &name);

				Builder* setDescription(const std::string &description);
				Builder* setUsage(const std::string &usage);
				Builder* setMinArgs(int minArgs);
				Builder* setMaxArgs(int maxArgs);
				Builder* setCallback(const std::function<void(const std::vector<std::string>&)> &callback);

				ConsoleCommand* build();
		};

		static Builder* createCommand(const std::string &name);
};