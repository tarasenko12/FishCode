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

#ifndef FISHCODE_FIELD_HPP
#define FISHCODE_FIELD_HPP

#include <wx/gdicmn.h>
#include <wx/textctrl.h>
#include <wx/window.h>
#include <wx/windowid.h>

namespace fc
{
    class Field : public wxTextCtrl {
    public:
        Field(wxWindow* parent);
        Field(
            wxWindow* parent,
            wxWindowID id,
            const wxString& value,
            const wxPoint& position,
            const wxSize& size,
            long style
        );

        Field(const Field& field) = delete;
        Field(Field&& field) noexcept = delete;

        Field& operator =(const Field& field) = delete;
        Field& operator =(Field&& field) noexcept = delete;

        virtual ~Field() noexcept override = default;
    };

    class PasswordField : public Field {
    public:
        PasswordField(wxWindow* parent);

        PasswordField(const PasswordField& field) = delete;
        PasswordField(PasswordField&& field) noexcept = delete;

        PasswordField& operator =(const PasswordField& field) = delete;
        PasswordField& operator =(PasswordField&& field) noexcept = delete;

        virtual ~PasswordField() noexcept override = default;
    };
}

#endif // FISHCODE_FIELD_HPP
