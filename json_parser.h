#pragma once
#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include "tg_types.h"

namespace json
{
	tg::Update ParseToUpdate(std::string text);
}