#pragma once
#include <iostream>
#include <cpr/cpr.h>
#include "json_parser.h"

namespace bot
{
	class Bot
	{
	private:
		std::string url = "https://api.telegram.org/bot6954596706:AAG_c9M3locrA91Zgbh-rEXquru6AjwnR2w/";
		std::vector <std::pair<int, std::vector<int>>> read_messages;

		// Метод проверяет, является ли сообщение прочитанным
		bool IsRead(int chat_id, int message_id);
		// Метод получает из текста ФИО человека
		std::optional<std::vector<std::string>> GetNameFromText(std::string& text);
	public:
		//Bot();
		//~Bot();

		// Метод возвращает последнее полученное сообщение
		std::optional<tg::Update> GetLastMessage();

		// Метод запускает обработку сообщений
		void Run();
	};
}