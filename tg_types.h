#pragma once
#include <string>

namespace tg
{
	struct Chat
	{
		int			id;
	};

	struct User
	{
		int			id;
		bool		is_bot;
		std::string	first_name;
		std::string	last_name;
		std::string	username;
	};

	struct Message
	{
		int			message_id;
		User		from;
		Chat		sender_chat;
		int			date;
		Chat		chat;
		std::string	text;
	};

	struct Update
	{
		int			update_id;
		Message		message;
	};

}