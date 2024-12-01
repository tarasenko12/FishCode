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

#ifndef FISHCODE_RESULTS_HPP
#define FISHCODE_RESULTS_HPP

namespace fc {
  // Program exit codes.
  enum Results : int {
    SUCCESS,
    INVALID_PASSWORD,
    INVALID_INPUT_FILE,
    INVALID_OUTPUT_FILE,
    INVALID_USAGE,
    INVALID_SUBCOMMAND,
    SYSTEM_EXCEPTION
  };
}

#endif // FISHCODE_RESULTS_HPP

