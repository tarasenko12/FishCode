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

#ifndef FISHCODE_PASSWORD_HPP
#define FISHCODE_PASSWORD_HPP

#include <string>
#include "key.hpp"
#include "types.hpp"

namespace fc
{
    class Password : public Key {
    public:
        static constexpr const Size MIN_LENGTH = 8;
        static constexpr const Size MAX_LENGTH = SIZE;

        Password() = default;

        Password(const std::string& password_string);

        Password(const Password& password) = default;
        Password(Password&& password) noexcept = default;

        virtual ~Password() noexcept override = default;

        Password& operator =(const Password& password) = default;
        Password& operator =(Password&& password) noexcept = default;
    protected:
        std::string password_string;
    };
}

#endif // FISHCODE_PASSWORD_HPP
