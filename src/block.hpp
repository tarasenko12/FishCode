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
#include "types.hpp"

namespace fc
{
    class Block {
    public:
        static constexpr const Size MIN_SIZE = 1;
        static constexpr const Size MAX_SIZE = 16;

        using Vector = std::vector<Byte>;
        using Iterator = Vector::iterator;
        using ConstIterator = Vector::const_iterator;

        Block();

        Block(const Vector& bytes);

        Block(const Block& block) = default;
        Block(Block&& block) noexcept = default;

        virtual ~Block() noexcept = default;

        Block& operator =(const Block& block) = default;
        Block& operator =(Block&& block) noexcept = default;

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

        inline void push(Byte byte)
        {
            bytes.push_back(byte);
        }

        inline void pop()
        {
            bytes.pop_back();
        }

        void encrypt(const Key& key);
        void decrypt(const Key& key);
    protected:
        Vector bytes;
    };
}

#endif // FISHCODE_BLOCK_HPP
