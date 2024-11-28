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

#ifndef FISHCODE_COMMANDS_HPP
#define FISHCODE_COMMANDS_HPP

namespace fc {
#if defined(_WIN32) || defined(_WIN64)
  constexpr const auto CMD_COPYRIGHT = L"--copyright";
  constexpr const auto CMD_HELP = L"--help";
  constexpr const auto CMD_VERSION = L"--version";
  constexpr const auto CMD_ENCRYPT = L"--encrypt";
  constexpr const auto CMD_DECRYPT = L"--decrypt";
#else
  constexpr const auto CMD_COPYRIGHT = "--copyright";
  constexpr const auto CMD_HELP = "--help";
  constexpr const auto CMD_VERSION = "--version";
  constexpr const auto CMD_ENCRYPT = "--encrypt";
  constexpr const auto CMD_DECRYPT = "--decrypt";
#endif // UTF-16 or UTF-8 commands.
}

#endif // FISHCODE_COMMANDS_HPP

