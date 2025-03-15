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

#ifndef FISHCODE_KEY_HPP
#define FISHCODE_KEY_HPP

#include <array>
#include "types.hpp"

namespace fc
{
    class Key {
    public:
        static constexpr const Size SIZE = 16;
        static constexpr const Byte BYTE_MAX = 0xff;

        using Array = std::array<Byte, SIZE>;
        using Iterator = Array::iterator;
        using ConstIterator = Array::const_iterator;

        Key() = default;

        Key(const Array& bytes);

        Key(const Key& key) = default;
        Key(Key&& key) noexcept = default;

        virtual ~Key() noexcept = default;

        Key& operator =(const Key& key) = default;
        Key& operator =(Key&& key) noexcept = default;

        inline Byte& operator [](Index index) noexcept
        {
            return bytes[index];
        }

        inline const Byte& operator [](Index index) const noexcept
        {
            return bytes[index];
        }

        inline Iterator begin()
        {
            return bytes.begin();
        }

        inline Iterator end()
        {
            return bytes.end();
        }

        inline ConstIterator begin() const
        {
            return bytes.begin();
        }

        inline ConstIterator end() const
        {
            return bytes.end();
        }

        static Key generate();

        Key getRoundKey(Round round) const;

        void encrypt(const Key& key);
        void decrypt(const Key& key);
    protected:
        Array bytes;
    };
}

#endif // FISHCODE_KEY_HPP
