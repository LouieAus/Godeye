#include "bot_http.h"

namespace bot
{
	bool Bot::IsRead(int chat_id, int message_id)
	{
		for (std::pair<int, std::vector<int>>& chat : read_messages)
		{
			if (chat.first == chat_id)
			{
				for (int id : chat.second)
					if (id == message_id)
						return true;
				break;
			}
		}

		return false;
	}

	std::optional<tg::Update> Bot::GetLastMessage()
	{
		try
		{
			cpr::Response resp = cpr::Get(cpr::Url{ url + "getUpdates?offset=-1" });
			if (resp.status_code == 200)
			{
				std::cout << "\n\n" << resp.text << '\n';
				tg::Update update = json::ParseToUpdate(resp.text);
				if (!IsRead(update.message.chat.id, update.message.message_id))
					return update;
			}
			return std::nullopt;
		}
		catch (...)
		{
			return std::nullopt;
		}
	}

	std::optional<std::vector<std::string>> Bot::GetNameFromText(std::string& text)
	{
		std::vector<std::string> result;

		int index = -1;
		std::string word = "";
		while (index != text.size())
		{
			index++;
			if (text[index] == ' ')
			{
				result.push_back(word);
				
				if (result.size() == 3)
					return result;

				word = "";
				continue;
			}

			word += text[index];
		}
		result.push_back(word);

		if (result.size() == 3)
			return result;

		return std::nullopt;
	}

	void Bot::Run()
	{
		while (true)
		{
			std::optional<tg::Update> res = GetLastMessage();
			if (res.has_value())
			{
				tg::Update update = res.value();
				std::optional<std::vector<std::string>> person_name = GetNameFromText(update.message.text);
				if (person_name.has_value())
				{

				}
			}

			Sleep(1000);
		}
	}
	
}