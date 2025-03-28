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
#include <cstddef>

namespace fc
{
    class Key {
    public:
        using Byte = std::byte;
        using Array = std::array<Byte, 16>;
        using Iterator = std::array<Byte, 16>::iterator;
        using ConstIterator = std::array<Byte, 16>::const_iterator;

        static constexpr unsigned SIZE = 16;
        static constexpr unsigned BYTE_MAX = 0xff;
    private:
        Array bytes;
    public:
        Key() = default;

        Key(const Key& key) = default;
        Key(Key&& key) noexcept = default;

        virtual ~Key() noexcept = default;

        Key& operator =(const Key& key) = default;
        Key& operator =(Key&& key) noexcept = default;

        static Key generate();

        Byte& operator [](unsigned index) noexcept
        {
            return bytes[index];
        }

        const Byte& operator [](unsigned index) const noexcept
        {
            return bytes[index];
        }

        Iterator begin()
        {
            return bytes.begin();
        }

        Iterator end()
        {
            return bytes.end();
        }

        ConstIterator begin() const
        {
            return bytes.begin();
        }

        ConstIterator end() const
        {
            return bytes.end();
        }

        Key getRoundKey(int round) const;

        void decrypt(const Key& key);
        void encrypt(const Key& key);
    };
}

#endif // FISHCODE_KEY_HPP
