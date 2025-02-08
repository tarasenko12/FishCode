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
**
** This program uses wxWidgets, a free and open-source cross-platform C++
** library for creating GUIs. wxWidgets is licensed under the wxWindows
** Library License, which is compatible with the GNU GPL.
** See <https://www.wxwidgets.org/about/licence/>.
*/

#ifndef FISHCODE_PROGRESS_HPP
#define FISHCODE_PROGRESS_HPP

#include <wx/gauge.h>
#include <wx/window.h>

namespace fc {
    class ProgressBar : public wxGauge {
    public:
        ProgressBar(wxWindow* parent);
        ProgressBar(const ProgressBar& otherProgressBar) = delete;
        ProgressBar(ProgressBar&& otherProgressBar) = delete;

        ProgressBar& operator=(const ProgressBar& otherProgressBar) = delete;
        ProgressBar& operator=(ProgressBar&& otherProgressBar) = delete;

        ~ProgressBar() noexcept override = default;
    };
}

#endif // FISHCODE_PROGRESS_HPP
