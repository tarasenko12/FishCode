/*
** Copyright (C) 2025 Vitaliy Tarasenko.
**
** This file is part of FishCode (fishcode).
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

#ifndef FISHCODE_TYPES_HPP
#define FISHCODE_TYPES_HPP

#include <filesystem>
#include <ios>
#include <cstdint>
#include <cstddef>

namespace fc
{
    using Byte = std::uint8_t;
    using Size = std::size_t;
    using FileSize = std::streamsize;
    using Index = Size;
    using FileIndex = FileSize;
    using Round = int;
    using Path = std::filesystem::path;
}

#endif // FISHCODE_TYPES_HPP
