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
**
** This program uses wxWidgets, a free and open-source cross-platform C++
** library for creating GUIs. wxWidgets is licensed under the wxWindows
** Library License, which is compatible with the GNU GPL.
** See <https://www.wxwidgets.org/about/licence/>.
*/

#ifndef FISHCODE_FRAME_HPP
#define FISHCODE_FRAME_HPP

#include <wx/frame.h>

namespace fc {
  class Frame : public wxFrame {
  public:
    Frame();
    Frame(const Frame& otherFrame) = delete;
    Frame(Frame&& otherFrame) = delete;

    Frame& operator=(const Frame& otherFrame) = delete;
    Frame& operator=(Frame&& otherFrame) = delete;
  };
}

#endif // FISHCODE_FRAME_HPP