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

		// ����� ���������, �������� �� ��������� �����������
		bool IsRead(int chat_id, int message_id);
		// ����� �������� �� ������ ��� ��������
		std::optional<std::vector<std::string>> GetNameFromText(std::string& text);
	public:
		//Bot();
		//~Bot();

		// ����� ���������� ��������� ���������� ���������
		std::optional<tg::Update> GetLastMessage();

		// ����� ��������� ��������� ���������
		void Run();
	};
}