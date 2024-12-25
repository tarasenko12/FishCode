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

#ifndef FISHCODE_HPP
#define FISHCODE_HPP

#include <wx/app.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/gauge.h>
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

namespace fc {
  class FishCode : public wxApp {
  public:
    FishCode() noexcept;
    FishCode(const FishCode& otherFishCode) = delete;
    FishCode(FishCode&& otherFishCode) = delete;

    FishCode& operator=(const FishCode& otherFishCode) = delete;
    FishCode& operator=(FishCode&& otherFishCode) = delete;

    bool OnInit() override;
  private:
    wxFrame* frame;
    wxMenuBar* menuBar;
    wxMenu* menuMore;
    wxMenuItem* menuMoreAbout;
    wxMenuItem* menuMoreHelp;
    wxBoxSizer* mainSizer;
    wxBoxSizer* inputFileSizer;
    wxBoxSizer* outputFileSizer;
    wxBoxSizer* passwordSizer;
    wxBoxSizer* buttonsSizer;
    wxStaticText* inputFileLabel;
    wxStaticText* outputFileLabel;
    wxStaticText* passwordLabel;
    wxTextCtrl* inputFileLine;
    wxTextCtrl* outputFileLine;
    wxButton* inputFileChooser;
    wxButton* outputFileChooser;
    wxTextCtrl* passwordLine;
    wxGauge* progressBar;
    wxButton* encryptButton;
    wxButton* decryptButton;
  };
}

#endif // FISHCODE_HPP

