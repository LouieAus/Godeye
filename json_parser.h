#pragma once
#include <string>
#include <variant>
#include "tg_types.h"
#include "api_vk.h"

namespace json
{
	tg::Update ParseToUpdate(std::string text);

	//std::vector<vk::User> ParseToVkUser(std::string text);

	struct DataPair
	{
		std::string id;
		std::variant<std::string, std::vector<DataPair>, std::vector<std::vector<DataPair>>> value;
	};

	std::vector<DataPair> ParseToJson(std::string text);

	DataPair GetData(std::vector<int> ids, std::vector<DataPair>& vec);

	void PrintDataPair(std::vector<DataPair>& vec, int level);
}