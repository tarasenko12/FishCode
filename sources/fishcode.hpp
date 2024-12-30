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

#include <wx/wx.h>

namespace fc {
  enum ControlItemID {
    ID_CHOOSE = 1,
    ID_SET,
    ID_ENCRYPT,
    ID_DECRYPT
  };

  class FishCode : public wxApp {
  public:
    FishCode() = default;
    FishCode(const FishCode& otherFishCode) = delete;
    FishCode(FishCode&& otherFishCode) = delete;

    FishCode& operator=(const FishCode& otherFishCode) = delete;
    FishCode& operator=(FishCode&& otherFishCode) = delete;

    bool OnInit() override;
    void OnAbout(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);
    void OnChoose(wxCommandEvent& event);
    void OnSet(wxCommandEvent& event);
    void OnEncrypt(wxCommandEvent& event);
    void OnDecrypt(wxCommandEvent& event);
  private:
    wxFrame* frame = nullptr;
    wxMenuBar* menuBar = nullptr;
    wxMenu* menuMore = nullptr;
    wxMenuItem* menuMoreAbout = nullptr;
    wxMenuItem* menuMoreHelp = nullptr;
    wxBoxSizer* mainSizer = nullptr;
    wxBoxSizer* inputFileSizer = nullptr;
    wxBoxSizer* outputFileSizer = nullptr;
    wxBoxSizer* passwordSizer = nullptr;
    wxBoxSizer* buttonsSizer = nullptr;
    wxStaticText* inputFileLabel = nullptr;
    wxStaticText* outputFileLabel = nullptr;
    wxStaticText* passwordLabel = nullptr;
    wxTextCtrl* inputFileLine = nullptr;
    wxTextCtrl* outputFileLine = nullptr;
    wxButton* inputFileChooser = nullptr;
    wxButton* outputFileSetter = nullptr;
    wxTextCtrl* passwordLine = nullptr;
    wxGauge* progressBar = nullptr;
    wxButton* encryptButton = nullptr;
    wxButton* decryptButton = nullptr;
    wxStatusBar* statusBar = nullptr;
  };
}

#endif // FISHCODE_HPP

