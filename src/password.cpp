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

#include "errors.hpp"
#include "password.hpp"

fc::Password::Password(const fc::Password::String& string)
: string(string)
{
    // Get length of the string (in bytes).
    const auto length = string.length();

    // Check password string length.
    if (length < MIN_LENGTH || length > MAX_LENGTH) {
        // Invalid password.
        throw errors::InvalidPassword();
    }

    // Check password string symbols.
    for (auto symbol : string) {
        // Only printable ASCII symbols (no spaces).
        if (symbol < '!' || symbol > '~') {
            // Invalid password.
            throw errors::InvalidPassword();
        }
    }

    // Convert each symbol into its binary representation and store it.
    for (unsigned index = 0; index < length; index++) {
        (*this)[index] = static_cast<Byte>(string[index]);
    }

    // Check if password string doesn't have maximal length.
    if (length < MAX_LENGTH) {
        // Append additional bytes from the beginning.
        for (unsigned counter = length, index = 0; counter < SIZE; counter++, index++) {
            (*this)[counter] = (*this)[index];
        }
    }
}
