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

#ifndef FISHCODE_FILE_HPP
#define FISHCODE_FILE_HPP

#include <filesystem>
#include <fstream>
#include <cstddef>
#include <cstdint>
#include "block.hpp"
#include "key.hpp"

namespace fc {
  class InputFile {
  public:
    InputFile(const std::filesystem::path& fsPath, bool isEncrypted);
  public:
    std::size_t GetBlocksNumber() const noexcept;
    std::size_t GetPartialBlockSize() const noexcept;
    bool HasPartialBlock() const noexcept;
    Block ReadBlock(const std::size_t bytesToRead = Block::SIZE);
    Key ReadKey();
  private:
    std::ifstream stream;
    std::size_t blocksNumber;
    std::size_t partialBlockSize;
    bool hasPartialBlock;
  };

  class OutputFile {
  public:
    OutputFile(const std::filesystem::path& fsPath);
  public:
    void WriteBlock(const Block& block);
    void WriteKey(const Key& key);
  private:
    std::ofstream stream;
  };
}

#endif // FISHCODE_FILE_HPP
