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

#ifndef FISHCODE_MESSAGES_HPP
#define FISHCODE_MESSAGES_HPP

namespace fc {
  constexpr const auto MSG_COPYRIGHT =
    "FishCode (fishcode) is a program for encrypting and decrypting files.\n"
    "Copyright (C) 2024 Vitaliy Tarasenko.\n"
    "This program comes with ABSOLUTELY NO WARRANTY.\n"
    "This is free software, and you are welcome to redistribute it\n"
    "under certain conditions.";
  constexpr const auto MSG_VERSION = "FishCode (fishcode) v1.2";
  constexpr const auto MSG_SYSTEM_EXCEPTION =
    "Error: system exception!\n"
    "Method \"what()\" has returned such string:\n";
}

#endif // FISHCODE_MESSAGES_HPP

