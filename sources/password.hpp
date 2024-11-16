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

#ifndef FISHCODE_PASSWORD_HPP
#define FISHCODE_PASSWORD_HPP

#include <cstddef>
#include "key.hpp"
#include "string.hpp"

namespace fc {
  class Password : public Key {
  private:
    static constexpr const std::size_t MIN_LENGTH = 8;
    static constexpr const std::size_t MAX_LENGTH = 16;
  public:
    Password(const fc::string_t& passwordString);
  };
}

#endif // FISHCODE_PASSWORD_HPP

