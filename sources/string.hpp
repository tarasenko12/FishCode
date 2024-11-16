/*
** Copyright (C) 2024 Vitaliy Tarasenko.
**
** This file is part of FishCode.
**
** FishCode is free software: you can redistribute it and/or modify it under
** the terms of the GNU General Public License as published by the Free
** Software Foundation, either version 3 of the License, or (at your option)
** any later version.
**
** FishCode is distributed in the hope that it will be useful, but WITHOUT
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
** FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
** more details.
**
** You should have received a copy of the GNU General Public License along
** with FishCode. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef FISHCODE_STRING_HPP
#define FISHCODE_STRING_HPP

#include <string>

namespace fc {
#if defined(_WIN32) || defined(_WIN64)
  // UTF-16.
  using string_t = std::wstring;
#else
  // UTF-8.
  using string_t = std::string;
#endif // UTF-16 or UTF-8 string.
}

#endif // FISHCODE_STRING_HPP

