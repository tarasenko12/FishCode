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

#include <exception>
#include <iostream>
#include <wx/button.h>
#include <wx/gauge.h>
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include "fishcode.hpp"
#include "frame.hpp"
#include "password.hpp"

fc::FishCode::FishCode()
: frame(nullptr),
  mainSizer(nullptr),
  inputFileSizer(nullptr),
  outputFileSizer(nullptr),
  passwordSizer(nullptr),
  buttonsSizer(nullptr),
  inputFileLabel(nullptr),
  outputFileLabel(nullptr),
  passwordLabel(nullptr),
  inputFileLine(nullptr),
  outputFileLine(nullptr),
  inputFileChooser(nullptr),
  outputFileChooser(nullptr),
  passwordLine(nullptr),
  progressBar(nullptr),
  encryptButton(nullptr),
  decryptButton(nullptr)
{}

bool fc::FishCode::OnInit() try {
  // Create the main window (frame).
  frame = new Frame();

  // Initialize new sizer for the main window.
  mainSizer = new wxBoxSizer(wxVERTICAL);

  // Connect main window (frame) with sizer.
  frame->SetSizer(mainSizer);

  // Create sizer for the input file chooser.
  inputFileSizer = new wxBoxSizer(wxHORIZONTAL);

  // Create context for this sizer.
  inputFileLabel = new wxStaticText(frame, wxID_ANY, "Input file:");
  inputFileLine = new wxTextCtrl(frame, wxID_ANY);
  inputFileChooser = new wxButton(frame, wxID_ANY, "Choose...");

  // Add context to the sizer.
  inputFileSizer->Add(inputFileLabel, 0, wxALL | wxALIGN_CENTER, 10);
  inputFileSizer->Add(inputFileLine, 0, wxALL | wxALIGN_CENTER, 10);
  inputFileSizer->Add(inputFileChooser, 0, wxALL | wxALIGN_CENTER, 10);

  // Connect main sizer with this sizer.
  mainSizer->Add(inputFileSizer, 0, wxALL | wxALIGN_CENTER, 0);

  // Create sizer for the input file chooser.
  outputFileSizer = new wxBoxSizer(wxHORIZONTAL);

  // Create context for this sizer.
  outputFileLabel = new wxStaticText(frame, wxID_ANY, "Output file:");
  outputFileLine = new wxTextCtrl(frame, wxID_ANY);
  outputFileChooser = new wxButton(frame, wxID_ANY, "Set...");

  // Add context to the sizer.
  outputFileSizer->Add(outputFileLabel, 0, wxALL | wxALIGN_CENTER, 10);
  outputFileSizer->Add(outputFileLine, 0, wxALL | wxALIGN_CENTER, 10);
  outputFileSizer->Add(outputFileChooser, 0, wxALL | wxALIGN_CENTER, 10);

  // Connect main sizer with this sizer.
  mainSizer->Add(outputFileSizer, 0, wxALL | wxALIGN_CENTER);

  // Create sizer for password listener.
  passwordSizer = new wxBoxSizer(wxHORIZONTAL);

  // Create context for this sizer.
  passwordLabel = new wxStaticText(frame, wxID_ANY, "Password:");
  passwordLine = new wxTextCtrl(
    frame,
    wxID_ANY,
    wxEmptyString,
    wxDefaultPosition,
    wxDefaultSize,
    wxTE_PASSWORD
  );

  // Configure password listener.
  passwordLine->SetMaxLength(Password::SIZE);

  // Add context to the sizer.
  passwordSizer->Add(passwordLabel, 0, wxALL | wxALIGN_CENTER, 10);
  passwordSizer->Add(passwordLine, 0, wxALL | wxALIGN_CENTER, 10);

  // Connect main sizer with this sizer.
  mainSizer->Add(passwordSizer, 0, wxALL | wxALIGN_CENTER, 0);

  // Create a progress bar (0% - 100%).
  progressBar = new wxGauge(
    frame,
    wxID_ANY,
    100,
    wxDefaultPosition,
    wxDefaultSize,
    wxGA_HORIZONTAL | wxGA_TEXT | wxGA_PROGRESS
  );

  // Add progress bar to the main sizer.
  mainSizer->Add(progressBar, 0, wxALL | wxALIGN_CENTER, 10);

  // Create sizer for the main control buttons.
  buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

  // Create main control buttons.
  encryptButton = new wxButton(frame, wxID_ANY, "Encrypt");
  decryptButton = new wxButton(frame, wxID_ANY, "Decrypt");

  // Add buttons to the sizer.
  buttonsSizer->Add(encryptButton, 0, wxALL | wxALIGN_CENTER, 10);
  buttonsSizer->Add(decryptButton, 0, wxALL | wxALIGN_CENTER, 10);

  // Connect this sizer to the main sizer.
  mainSizer->Add(buttonsSizer, 0, wxALL | wxALIGN_CENTER, 0);

  // Show the window.
  frame->Show();

  // Start the application.
  return true;
} catch (const std::exception& ex) {
  // Display GUI error message.
  wxMessageBox(ex.what(), "Error", wxOK | wxICON_ERROR);

  // Print error message to the terminal.
  std::cout << ex.what() << std::endl;

  // Do not start the application.
  return false;
}

// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(fc::FishCode);

