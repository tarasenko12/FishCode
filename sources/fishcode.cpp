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

#include <exception>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <wx/aboutdlg.h>
#include <wx/button.h>
#include <wx/event.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/gauge.h>
#include <wx/gdicmn.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
#include "block.hpp"
#include "error.hpp"
#include "file.hpp"
#include "fishcode.hpp"
#include "key.hpp"
#include "password.hpp"
#include "strings.hpp"

// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(fc::FishCode);

bool fc::FishCode::OnInit() try {
  // Create the main window (frame).
  frame = new wxFrame(nullptr, wxID_ANY, STR_NAME0);

  // Create a new menu bar for the frame.
  menuBar = new wxMenuBar();

  // Initialize menu bar menu(s).
  menuMore = new wxMenu();

  // Initialize menuMore items and append them to the menu.
  menuMore->Append(wxID_ABOUT, STR_NAME2, STR_PROMPT0);
  menuMore->Append(wxID_HELP, STR_NAME3, STR_PROMPT1);

  // Append menu(s) to the menu bar.
  menuBar->Append(menuMore, STR_NAME1);

  // Connect menu bar to the frame.
  frame->SetMenuBar(menuBar);

  // Create a new status bar for the frame.
  statusBar = new wxStatusBar(frame);

  // Set the default status.
  statusBar->SetStatusText(STR_STATUS0);

  // Add this status bar to the frame.
  frame->SetStatusBar(statusBar);

  // Configure the about dialog.
  aboutDialogInfo.SetName(STR_NAME0);
  aboutDialogInfo.SetVersion(STR_VERSION);
  aboutDialogInfo.SetDescription(STR_DESCRYPTION);
  aboutDialogInfo.SetCopyright(STR_COPYRIGHT);
  aboutDialogInfo.AddDeveloper(STR_DEVELOPER);

  // Initialize new sizer for the main window.
  mainSizer = new wxBoxSizer(wxVERTICAL);

  // Configure grid sizers layout.
  const wxSize gridLayout(5, 5);

  // Configure sizers (using flags).
  const auto mainSizerFlags = wxSizerFlags()
    .Expand()
    .Border(wxALL, 5);
  const auto gridSizerFlags = wxSizerFlags()
    .Expand()
    .Border(wxALL, 10);
  const auto gridLabelSizerFlags = wxSizerFlags()
    .Center()
    .Right()
    .Border(wxALL, 2);

  // Set layout for the fields.
  const wxSize fieldSize(400, 45);

  // Create sizer for the input file chooser.
  inputFileSizer = new wxFlexGridSizer(1, 3, gridLayout);

  // Create context for this sizer.
  inputFileLabel = new wxStaticText(frame, wxID_ANY, STR_LABEL0);
  inputFileLine = new wxTextCtrl(frame, wxID_ANY);
  inputFileChooser = new wxButton(frame, ID_CHOOSE, STR_LABEL2);

  // Configure input file line layout.
  inputFileLine->SetMinSize(fieldSize);

  // Add context to the sizer.
  inputFileSizer->Add(inputFileLabel, gridLabelSizerFlags);
  inputFileSizer->Add(inputFileLine, gridSizerFlags);
  inputFileSizer->Add(inputFileChooser, gridSizerFlags);

  // Set growable columns for this sizer.
  inputFileSizer->AddGrowableCol(1);
  inputFileSizer->AddGrowableCol(2);

  // Connect main sizer with this sizer.
  mainSizer->Add(inputFileSizer, mainSizerFlags);

  // Create sizer for the output file setter.
  outputFileSizer = new wxFlexGridSizer(1, 3, gridLayout);

  // Create context for this sizer.
  outputFileLabel = new wxStaticText(frame, wxID_ANY, STR_LABEL1);
  outputFileLine = new wxTextCtrl(frame, wxID_ANY);
  outputFileSetter = new wxButton(frame, ID_SET, STR_LABEL3);

  // Configure output file line layout.
  outputFileLine->SetMinSize(fieldSize);

  // Add context to the sizer.
  outputFileSizer->Add(outputFileLabel, gridLabelSizerFlags);
  outputFileSizer->Add(outputFileLine, gridSizerFlags);
  outputFileSizer->Add(outputFileSetter, gridSizerFlags);

  // Set growable columns for this sizer.
  outputFileSizer->AddGrowableCol(1);
  outputFileSizer->AddGrowableCol(2);

  // Connect main sizer with this sizer.
  mainSizer->Add(outputFileSizer, mainSizerFlags);

  // Create sizer for password listener.
  passwordSizer = new wxFlexGridSizer(1, 2, gridLayout);

  // Create context for this sizer.
  passwordLabel = new wxStaticText(frame, wxID_ANY, STR_LABEL4);
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
  passwordLine->SetMinSize(fieldSize);

  // Add context to the sizer.
  passwordSizer->Add(passwordLabel, gridLabelSizerFlags);
  passwordSizer->Add(passwordLine, gridSizerFlags);

  // Set growable column for this sizer.
  passwordSizer->AddGrowableCol(1);

  // Connect main sizer with this sizer.
  mainSizer->Add(passwordSizer, mainSizerFlags);

  // Create a progress bar (0% - 100%).
  progressBar = new wxGauge(
    frame,
    wxID_ANY,
    100,
    wxDefaultPosition,
    wxDefaultSize,
    wxGA_HORIZONTAL | wxGA_TEXT | wxGA_PROGRESS
  );

  // Configure progress bar size.
  progressBar->SetMinSize(wxSize(400, 15));

  // Add progress bar to the main sizer.
  mainSizer->Add(progressBar, mainSizerFlags);

  // Create sizer for the main control buttons.
  buttonsSizer = new wxGridSizer(1, 2, gridLayout);

  // Create main control buttons.
  encryptButton = new wxButton(frame, ID_ENCRYPT, STR_LABEL5);
  decryptButton = new wxButton(frame, ID_DECRYPT, STR_LABEL6);

  // Add buttons to the sizer.
  buttonsSizer->Add(encryptButton, gridSizerFlags);
  buttonsSizer->Add(decryptButton, gridSizerFlags);

  // Connect this sizer to the main sizer.
  mainSizer->Add(buttonsSizer, mainSizerFlags);

  // Connect main window (frame) with sizer.
  frame->SetSizerAndFit(mainSizer);

  // Configure timer.
  readyTimer.SetOwner(frame, ID_READY);

  // Configure event handlers.
  frame->Bind(wxEVT_MENU, &fc::FishCode::OnAbout, this, wxID_ABOUT);
  frame->Bind(wxEVT_MENU, &fc::FishCode::OnHelp, this, wxID_HELP);
  inputFileChooser->Bind(wxEVT_BUTTON, &fc::FishCode::OnChoose, this, ID_CHOOSE);
  outputFileSetter->Bind(wxEVT_BUTTON, &fc::FishCode::OnSet, this, ID_SET);
  encryptButton->Bind(wxEVT_BUTTON, &fc::FishCode::OnEncrypt, this, ID_ENCRYPT);
  decryptButton->Bind(wxEVT_BUTTON, &fc::FishCode::OnDecrypt, this, ID_DECRYPT);
  frame->Bind(wxEVT_TIMER, &fc::FishCode::OnReadyTimer, this, ID_READY);

  // Show the window.
  frame->Show();

  // Start the application.
  return true;
} catch (const std::exception& ex) {
  // Display GUI error message.
  wxMessageBox(ex.what(), STR_CAPTION3, wxOK | wxCENTRE | wxICON_ERROR);

  // Print error message to the terminal.
  std::cerr << ex.what() << std::endl;

  // Do not start the application.
  return false;
}

void fc::FishCode::OnAbout(wxCommandEvent& event) {
  // Show about box.
  wxAboutBox(aboutDialogInfo, frame);
}

void fc::FishCode::OnHelp(wxCommandEvent& event) {
  // Display a message box with short documentation.
  wxMessageBox(
    STR_DOCUMENTATION,
    STR_CAPTION0,
    wxOK | wxCENTRE | wxICON_QUESTION,
    frame
  );
}

void fc::FishCode::OnChoose(wxCommandEvent& event) {
  // Open file selector.
  const auto filePath = wxFileSelector(
    STR_CAPTION1,
    wxEmptyString,
    wxEmptyString,
    wxEmptyString,
    wxFileSelectorDefaultWildcardStr,
    wxFD_OPEN,
    frame
  );

  // Check if user has chosen the file.
  if (!filePath.empty()) {
    // Insert file path to the input file line.
    inputFileLine->ChangeValue(filePath);
  }
}

void fc::FishCode::OnSet(wxCommandEvent& event) {
  // Open file selector.
  const auto filePath = wxFileSelector(
    STR_CAPTION2,
    wxEmptyString,
    wxEmptyString,
    wxEmptyString,
    wxFileSelectorDefaultWildcardStr,
    wxFD_SAVE,
    frame
  );

  // Check if user has set the file.
  if (!filePath.empty()) {
    // Insert file path to the output file line.
    outputFileLine->ChangeValue(filePath);
  }
}

void fc::FishCode::OnEncrypt(wxCommandEvent& event) try {
  // Disable controls.
  DisableControls();

  // Display new status in the status bar.
  statusBar->SetStatusText(STR_STATUS2);

  // Get pathes to input and output files.
  const auto inputFilePath = GetFilePath(inputFileLine);
  const auto outputFilePath = GetFilePath(outputFileLine);

  // Check output file path.
  if (!IsValidOutputFile(inputFilePath, outputFilePath)) {
    // Invalid output file.
    throw InvalidOutputFileError();
  }

  // Open the input file.
  InputFile inputFile(inputFilePath, false);

  // Create the output file.
  OutputFile outputFile(outputFilePath);

  // Generate encryption key.
  auto key = Key::Generate();

  // Get password.
  const Password password(passwordLine->GetValue().utf8_string());

  // Encrypt the key with password.
  key.Encrypt(password);

  // Store encrypted key to the output file.
  outputFile.WriteKey(key);

  // Decrypt the key.
  key.Decrypt(password);

  // Get number of blocks in the input file.
  const auto inputFileBlocks = inputFile.GetBlocksNumber();

  // Count 10% of blocks from the 100%.
  const auto tenPercents = inputFileBlocks / 10;

  // Encrypt the input file by blocks.
  for (
    std::size_t blockCounter = 0, percentCounter = 10, progressCounter = 0;
    blockCounter < inputFileBlocks;
    blockCounter++, progressCounter++
  ) {
    // Read one block from the file.
    auto block = inputFile.ReadBlock();

    // Encrypt the block.
    block.Encrypt(key);

    // Store block to the output file.
    outputFile.WriteBlock(block);

    // Check if there is valuable progress.
    if (progressCounter == tenPercents) {
      // Update the progress bar.
      progressBar->SetValue(percentCounter);

      // Update percent counter.
      percentCounter += 10;

      // Set progress counter to zero for the next 10%.
      progressCounter = 0;
    }
  }

  // Check if the input file has partial block.
  if (inputFile.HasPartialBlock()) {
    // Read partial block.
    auto block = inputFile.ReadBlock(inputFile.GetPartialBlockSize());

    // Encrypt the block.
    block.Encrypt(key);

    // Store block to the output file.
    outputFile.WriteBlock(block);
  }

  // Update the progress bar.
  progressBar->SetValue(100);

  // Set new status in the status bar.
  statusBar->SetStatusText(STR_STATUS1);

  // Start timer to the new status.
  readyTimer.StartOnce(3000);
} catch (const std::exception& ex) {
  // Display GUI error message.
  wxMessageBox(ex.what(), STR_CAPTION4, wxOK | wxCENTRE | wxICON_ERROR, frame);

  // Set progress bar to the default state.
  progressBar->SetValue(0);

  // Enable controls.
  EnableControls();

  // Set default status in the status bar.
  statusBar->SetStatusText(STR_STATUS0);
}

void fc::FishCode::OnDecrypt(wxCommandEvent& event) try {
  // Disable controls.
  DisableControls();

  // Display new status in the status bar.
  statusBar->SetStatusText(STR_STATUS3);

  // Get pathes to input and output files.
  const auto inputFilePath = GetFilePath(inputFileLine);
  const auto outputFilePath = GetFilePath(outputFileLine);

  // Check output file path.
  if (!IsValidOutputFile(inputFilePath, outputFilePath)) {
    // Invalid output file.
    throw InvalidOutputFileError();
  }

  // Open the input file.
  InputFile inputFile(inputFilePath, true);

  // Create the output file.
  OutputFile outputFile(outputFilePath);

  // Read encryption key from the input file.
  auto key = inputFile.ReadKey();

  // Get password and decrypt the key.
  key.Decrypt(Password(passwordLine->GetValue().utf8_string()));

  // Get number of blocks in the input file.
  const auto inputFileBlocks = inputFile.GetBlocksNumber();

  // Count 10% of blocks from the 100%.
  const auto tenPercents = inputFileBlocks / 10;

  // Decrypt the input file by blocks.
  for (
    std::size_t blockCounter = 0, percentCounter = 10, progressCounter = 0;
    blockCounter < inputFileBlocks;
    blockCounter++, progressCounter++
  ) {
    // Read one block from the file.
    auto block = inputFile.ReadBlock();

    // Decrypt the block.
    block.Decrypt(key);

    // Store block to the output file.
    outputFile.WriteBlock(block);

    // Check if there is valuable progress.
    if (progressCounter == tenPercents) {
      // Update the progress bar.
      progressBar->SetValue(percentCounter);

      // Update percent counter.
      percentCounter += 10;

      // Set progress counter to zero for the next 10%.
      progressCounter = 0;
    }
  }

  // Check if the input file has partial block.
  if (inputFile.HasPartialBlock()) {
    // Read partial block.
    auto block = inputFile.ReadBlock(inputFile.GetPartialBlockSize());

    // Decrypt the block.
    block.Decrypt(key);

    // Store block to the output file.
    outputFile.WriteBlock(block);
  }

  // Update the progress bar.
  progressBar->SetValue(100);

  // Set new status in the status bar.
  statusBar->SetStatusText(STR_STATUS1);

  // Start timer to the new status.
  readyTimer.StartOnce(3000);
} catch (const std::exception& ex) {
  // Display GUI error message.
  wxMessageBox(ex.what(), STR_CAPTION4, wxOK | wxCENTRE | wxICON_ERROR, frame);

  // Set progress bar to the default state.
  progressBar->SetValue(0);

  // Enable controls.
  EnableControls();

  // Set default status in the status bar.
  statusBar->SetStatusText(STR_STATUS0);
}

void fc::FishCode::OnReadyTimer(wxTimerEvent& event) {
  // Set progress bar to the default state.
  progressBar->SetValue(0);

  // Enable controls.
  EnableControls();

  // Set default status in the status bar.
  statusBar->SetStatusText(STR_STATUS0);
}

void fc::FishCode::EnableControls() {
  // Enable all control items.
  inputFileLine->Enable();
  inputFileChooser->Enable();
  outputFileLine->Enable();
  outputFileSetter->Enable();
  passwordLine->Enable();
  encryptButton->Enable();
  decryptButton->Enable();
}

void fc::FishCode::DisableControls() {
  // Disable all control items.
  inputFileLine->Disable();
  inputFileChooser->Disable();
  outputFileLine->Disable();
  outputFileSetter->Disable();
  passwordLine->Disable();
  encryptButton->Disable();
  decryptButton->Disable();
}

std::filesystem::path fc::FishCode::GetFilePath(wxTextCtrl* fileLine) {
  if (fileLine) {
    // Get string from the field.
    const std::string pathString = fileLine->GetValue().utf8_string();

    // Check the string.
    if (pathString.empty()) {
      // Invalid path.
      if (fileLine == inputFileLine) {
        throw InvalidInputFileError();
      } else {
        throw InvalidOutputFileError();
      }
    }

    // Construct the new path object and return it.
    return std::filesystem::path(pathString);
  } else {
    // Invalid file line pointer.
    throw std::invalid_argument("Invalid pointer for GetFilePath()!");
  }
}

bool fc::FishCode::IsValidOutputFile(
  const std::filesystem::path& inputFilePath,
  const std::filesystem::path& outputFilePath
) {
  // Check if pathes are not equivalent.
  if (std::filesystem::exists(outputFilePath)) {
    if (std::filesystem::equivalent(inputFilePath, outputFilePath)) {
      // Invalid output file.
      return false;
    }
  }

  // Valid output file.
  return true;
}
