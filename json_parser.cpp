#include "json_parser.h"

namespace json
{
	std::string GetWord(int& index, std::string text)
	{
		std::string result = "";
		index++;
		while (text[index] != '"')
		{
			result += text[index];
			index++;
		}
		return result;
	}

	int GetInt(int& index, std::string text)
	{
		int begin_index = index;
		while ((text[index] != ',') && (text[index] != '}'))
			index++;
		std::string int_str = text.substr(begin_index, index - begin_index);
		return std::stoi(int_str);
	}

	bool GetBool(int& index, std::string text)
	{
		int begin_index = index + 1;
		while ((text[index] != ',') && (text[index] != '}'))
			index++;
		if (text[begin_index] == 't')
			return true;
		return false;
	}

	bool GetBeginState(std::string text)
	{
		if (text.substr(6, 4) == "true")
			return true;
		return false;
	}


	tg::Update ParseToUpdate(std::string text)
	{
		tg::Update new_update;
		new_update.message.text = "";

		bool state = GetBeginState(text);
		if (state == true && text[20] == '[')
		{
			int index = 21;
			int level = 0;

			std::string current_id = "";
			while (text[index] != ']')
			{
				if (text[index] == '{')
					level++;
				else if (text[index] == '"')
					current_id = GetWord(index, text);
				else if (text[index] == ':')
				{
					index++;
					if (current_id == "update_id")
						new_update.update_id = GetInt(index, text);
					else if (current_id == "message_id")
						new_update.message.message_id = GetInt(index, text);
					else if (current_id == "id" && level == 3)
						new_update.message.from.id = GetInt(index, text);
					else if (current_id == "is_bot")
						new_update.message.from.is_bot = GetBool(index, text);
					else if (current_id == "first_name")
						new_update.message.from.first_name = GetWord(index, text);
					else if (current_id == "last_name")
						new_update.message.from.last_name = GetWord(index, text);
					else if (current_id == "username")
						new_update.message.from.username = GetWord(index, text);
					else if (current_id == "id" && level == 4)
						new_update.message.chat.id = GetInt(index, text);
					else if (current_id == "date")
						new_update.message.date = GetInt(index, text);
					else if (current_id == "text")
						new_update.message.text = GetWord(index, text);
					else
					{
						while (text[index] != ',' && text[index] != '{' && text[index] != '}')
						{
							index++;
						}

						if (text[index] == '{')
							level++;
					}
				}

				index++;
			}
		}

		return new_update;
	}

	//std::vector<vk::User> json::ParseToVkUser(std::string text)
	//{
	//	// TODO
	//}

	std::string GetSubJson(int index, std::string& text, int& exit_index)
	{
		std::string result = "";

		int level = 0;
		for (auto i = index; i != text.size(); i++)
		{
			if (text[i] == '{')
				level++;
			else if (text[i] == '}')
				level--;

			result += text[i];

			if (level == 0)
			{
				exit_index = i;
				break;
			}
		}
		
		return result;
	}

	std::vector<DataPair> json::ParseToJson(std::string text)
	{
		std::vector<DataPair> result;

		text = text.substr(1, text.size() - 2);
		
		int state = 0;
		std::string id = "";
		std::string value = "";
		int exit_index = 0;

		for (auto i = 0; i != text.size(); i++)
		{
			if (state == 0)
			{
				if (text[i] == '"')
					state = 1;
			}
			else if (state == 1)
			{
				if (text[i] == '"')
					state = 2;
				else
					id += text[i];
			}
			else if (state == 2)
			{
				if (text[i] == ':')
					state = 3;
			}
			else if (state == 3)
			{
				if (text[i] == '"')
					state = 10;
				else if (text[i] == '{')
					state = 20;
				else if (text[i] == '[')
					state = 30;
				else
					state = 40;
			}
			else if (state == 4)
			{
				if (i == exit_index)
					state = 0;
			}
			else if (state == 10)
			{
				if (text[i] == '"')
				{
					value = '"' + value + '"';
					DataPair data = { id, value };
					result.push_back(data);
					id = "";
					value = "";
					state = 0;
				}
				else
				{
					value += text[i];
				}
			}
			else if (state == 30)
			{
				if (text[i] != ']')
				{
					std::vector<std::vector<DataPair>> vec;
					exit_index = i - 2;
					while (text[exit_index + 1] != ']')
					{
						std::string sub = GetSubJson(exit_index + 2, text, exit_index);
						std::vector<DataPair> subresult = ParseToJson(sub);
						vec.push_back(subresult);
					}
					DataPair data = { id, vec };
					result.push_back(data);
					id = "";
					value = "";
					state = 4;
				}
				else
				{
					DataPair data = { id, "" };
					result.push_back(data);
					id = "";
					value = "";
					state = 0;
				}
			}

			if (state == 20)
			{
				std::string sub = GetSubJson(i, text, exit_index);
				std::vector<DataPair> subresult = ParseToJson(sub);
				DataPair data = { id, subresult };
				result.push_back(data);
				id = "";
				value = "";
				state = 4;
			}
			else if (state == 40)
			{
				if (text[i] == ',' || text[i] == '}' || i == text.size() - 1)
				{
					DataPair data = { id, value };
					result.push_back(data);
					id = "";
					value = "";
					state = 0;
				}
				else
				{
					value += text[i];
				}
			}
		}

		return result;
	}

	DataPair json::GetData(std::vector<int> ids, std::vector<DataPair>& vec)
	{

	}

	void PrintDataPair(std::vector<DataPair>& vec, int level)
	{
		for (DataPair& data : vec)
		{
			for (int i = 0; i != level; i++)
				std::cout << '\t';

			std::cout << data.id << ':';
			try
			{
				std::string value = std::get<std::string>(data.value);
				std::cout << value << '\n';
			}
			catch (const std::bad_variant_access& ex)
			{
				try
				{
					std::cout << '\n';
					std::vector<DataPair> pair = std::get<std::vector<DataPair>>(data.value);
					PrintDataPair(pair, level + 1);
				}
				catch (const std::bad_variant_access& ex)
				{
					std::cout << '\n';
					std::vector<std::vector<DataPair>> vec = std::get<std::vector<std::vector<DataPair>>>(data.value);
					for (auto i = 0; i != vec.size(); i++)
					{
						PrintDataPair(vec[i], level + 1);
						std::cout << '\n';
					}
				}
			}
		}
	}
}