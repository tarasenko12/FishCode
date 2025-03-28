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

namespace fc
{
    class Password : public Key {
    public:
        using String = std::string;

        static constexpr unsigned MIN_LENGTH = 8;
        static constexpr unsigned MAX_LENGTH = SIZE;
    private:
        String string;
    public:
        Password() = default;

        Password(const String& string);

        Password(const Password& password) = default;
        Password(Password&& password) noexcept = default;

        virtual ~Password() noexcept override = default;

        Password& operator =(const Password& password) = default;
        Password& operator =(Password&& password) noexcept = default;
    };
}

#endif // FISHCODE_PASSWORD_HPP
