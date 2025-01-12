/*
** Copyright (C) 2024-2025 Vitaliy Tarasenko.
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

#include <filesystem>
#include <wx/aboutdlg.h>
#include <wx/app.h>
#include <wx/button.h>
#include <wx/event.h>
#include <wx/frame.h>
#include <wx/gauge.h>
#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/timer.h>

namespace fc {
  enum ControlItemID {
    ID_CHOOSE = 1,
    ID_SET,
    ID_ENCRYPT,
    ID_DECRYPT
  };

  enum TimerID {
    ID_READY = ID_DECRYPT + 1
  };

  class FishCode : public wxApp {
  public:
    FishCode() = default;
    FishCode(const FishCode& otherFishCode) = delete;
    FishCode(FishCode&& otherFishCode) = delete;

    FishCode& operator=(const FishCode& otherFishCode) = delete;
    FishCode& operator=(FishCode&& otherFishCode) = delete;

    ~FishCode() noexcept override = default;

    bool OnInit() override;
    void OnAbout(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);
    void OnChoose(wxCommandEvent& event);
    void OnSet(wxCommandEvent& event);
    void OnEncrypt(wxCommandEvent& event);
    void OnDecrypt(wxCommandEvent& event);
    void OnReadyTimer(wxTimerEvent& event);
  private:
    wxFrame* frame = nullptr;
    wxMenuBar* menuBar = nullptr;
    wxMenu* menuMore = nullptr;
    wxStatusBar* statusBar = nullptr;
    wxAboutDialogInfo aboutDialogInfo;
    wxBoxSizer* mainSizer = nullptr;
    wxFlexGridSizer* inputFileSizer = nullptr;
    wxFlexGridSizer* outputFileSizer = nullptr;
    wxFlexGridSizer* passwordSizer = nullptr;
    wxGridSizer* buttonsSizer = nullptr;
    wxStaticText* inputFileLabel = nullptr;
    wxStaticText* outputFileLabel = nullptr;
    wxStaticText* passwordLabel = nullptr;
    wxTextCtrl* inputFileLine = nullptr;
    wxTextCtrl* outputFileLine = nullptr;
    wxTextCtrl* passwordLine = nullptr;
    wxButton* inputFileChooser = nullptr;
    wxButton* outputFileSetter = nullptr;
    wxButton* encryptButton = nullptr;
    wxButton* decryptButton = nullptr;
    wxGauge* progressBar = nullptr;
    wxTimer readyTimer;

    void EnableControls();
    void DisableControls();
    std::filesystem::path GetFilePath(wxTextCtrl* fileLine);
    bool IsValidOutputFile(
      const std::filesystem::path& inputFilePath,
      const std::filesystem::path& outputFilePath
    );
  };
}

#endif // FISHCODE_HPP

