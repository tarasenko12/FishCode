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

#ifndef FISHCODE_BLOCK_HPP
#define FISHCODE_BLOCK_HPP

#include <vector>
#include "key.hpp"

namespace fc
{
    class Block {
    public:
        using Byte = Key::Byte;
        using Vector = std::vector<Byte>;
        using Iterator = std::vector<Byte>::iterator;
        using ConstIterator = std::vector<Byte>::const_iterator;

        static constexpr unsigned MIN_SIZE = 1;
        static constexpr unsigned MAX_SIZE = 16;
    private:
        Vector bytes;
    public:
        Block();

        Block(const Block& block) = default;
        Block(Block&& block) noexcept = default;

        virtual ~Block() noexcept = default;

        Block& operator =(const Block& block) = default;
        Block& operator =(Block&& block) noexcept = default;

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

        void push(Byte byte)
        {
            bytes.push_back(byte);
        }

        void pop()
        {
            bytes.pop_back();
        }

        void decrypt(const Key& key);
        void encrypt(const Key& key);
    };
}

#endif // FISHCODE_BLOCK_HPP
