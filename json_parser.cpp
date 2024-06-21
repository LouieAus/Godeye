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
}