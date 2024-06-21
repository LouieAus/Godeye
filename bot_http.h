#pragma once
#include <iostream>
#include <cpr/cpr.h>
#include "json_parser.h"

namespace bot
{
	class Bot
	{
	private:
		std::string url = "https://api.telegram.org/";
		std::vector <std::pair<int, std::vector<int>>> read_messages;

		// Ìåòîä ïðîâåðÿåò, ÿâëÿåòñÿ ëè ñîîáùåíèå ïðî÷èòàííûì
		bool IsRead(int chat_id, int message_id);
		// Ìåòîä ïîëó÷àåò èç òåêñòà ÔÈÎ ÷åëîâåêà
		std::optional<std::vector<std::string>> GetNameFromText(std::string& text);
	public:
		//Bot();
		//~Bot();

		// Ìåòîä âîçâðàùàåò ïîñëåäíåå ïîëó÷åííîå ñîîáùåíèå
		std::optional<tg::Update> GetLastMessage();

		// Ìåòîä çàïóñêàåò îáðàáîòêó ñîîáùåíèé
		void Run();
	};
}
