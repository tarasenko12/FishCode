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

#ifndef FISHCODE_ERROR_HPP
#define FISHCODE_ERROR_HPP

namespace fc {
  class Error {
  public:
    virtual const char* What() const noexcept = 0;
    virtual int GetErrorCode() const noexcept = 0;
  };

  class InvalidPasswordError : public Error {
  public:
    const char* What() const noexcept override;
    int GetErrorCode() const noexcept override;
  };

  class InvalidInputFileError : public Error {
  public:
    const char* What() const noexcept override;
    int GetErrorCode() const noexcept override;
  };

  class InvalidOutputFileError : public Error {
  public:
    const char* What() const noexcept override;
    int GetErrorCode() const noexcept override;
  };

  class InvalidUsageError : public Error {
  public:
    const char* What() const noexcept override;
    int GetErrorCode() const noexcept override;
  };

  class InvalidSubcommandError : public Error {
  public:
    const char* What() const noexcept override;
    int GetErrorCode() const noexcept override;
  };
}

#endif // FISHCODE_ERROR_HPP

