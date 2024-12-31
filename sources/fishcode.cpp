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
#include <filesystem>
#include <iostream>
#include <wx/wx.h>
#include "block.hpp"
#include "error.hpp"
#include "file.hpp"
#include "fishcode.hpp"
#include "key.hpp"
#include "password.hpp"

// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(fc::FishCode);

bool fc::FishCode::OnInit() try {
  // Create the main window (frame).
  frame = new wxFrame(nullptr, wxID_ANY, "FishCode");

  // Create a new menu bar for the frame.
  menuBar = new wxMenuBar();

  // Connect menu bar to the frame.
  frame->SetMenuBar(menuBar);

  // Initialize menu bar menu(s).
  menuMore = new wxMenu();

  // Initialize "More..." menu items.
  menuMoreAbout = new wxMenuItem(
    menuMore,
    wxID_ABOUT,
    "About",
    "Get more information about the program."
  );
  menuMoreHelp = new wxMenuItem(
    menuMore,
    wxID_HELP,
    "Help",
    "Get user documentation."
  );

  // Append this menu to the menu bar.
  menuBar->Append(menuMore, "More...");

  // Append these items to the "More..." menu.
  menuMore->Append(menuMoreAbout);
  menuMore->Append(menuMoreHelp);

  // Create a new status bar for the frame.
  statusBar = new wxStatusBar(frame);

  // Set status to "Ready".
  statusBar->SetStatusText("Ready");

  // Add this status bar to the frame.
  frame->SetStatusBar(statusBar);

  // Set layout for the fields.
  const wxSize fieldSize(400, 45);

  // Initialize new sizer for the main window.
  mainSizer = new wxBoxSizer(wxVERTICAL);

  // Create sizer for the input file chooser.
  inputFileSizer = new wxBoxSizer(wxHORIZONTAL);

  // Create context for this sizer.
  inputFileLabel = new wxStaticText(frame, wxID_ANY, "Input file:");
  inputFileLine = new wxTextCtrl(frame, wxID_ANY);
  inputFileChooser = new wxButton(frame, ID_CHOOSE, "Choose...");

  // Configure input file line layout.
  inputFileLine->SetMinSize(fieldSize);

  // Add context to the sizer.
  inputFileSizer->Add(inputFileLabel, 0, wxALL | wxALIGN_CENTER, 10);
  inputFileSizer->Add(inputFileLine, 0, wxALL | wxALIGN_CENTER, 10);
  inputFileSizer->Add(inputFileChooser, 0, wxALL | wxALIGN_CENTER, 10);

  // Connect main sizer with this sizer.
  mainSizer->Add(inputFileSizer, 0, wxALL | wxALIGN_CENTER, 0);

  // Create sizer for the output file setter.
  outputFileSizer = new wxBoxSizer(wxHORIZONTAL);

  // Create context for this sizer.
  outputFileLabel = new wxStaticText(frame, wxID_ANY, "Output file:");
  outputFileLine = new wxTextCtrl(frame, wxID_ANY);
  outputFileSetter = new wxButton(frame, ID_SET, "Set...");

  // Configure output file line layout.
  outputFileLine->SetMinSize(fieldSize);

  // Add context to the sizer.
  outputFileSizer->Add(outputFileLabel, 0, wxALL | wxALIGN_CENTER, 10);
  outputFileSizer->Add(outputFileLine, 0, wxALL | wxALIGN_CENTER, 10);
  outputFileSizer->Add(outputFileSetter, 0, wxALL | wxALIGN_CENTER, 10);

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
  passwordLine->SetMinSize(fieldSize);

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

  // Configure progress bar size.
  progressBar->SetMinSize(wxSize(400, 15));

  // Add progress bar to the main sizer.
  mainSizer->Add(progressBar, 0, wxALL | wxALIGN_CENTER, 10);

  // Create sizer for the main control buttons.
  buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

  // Create main control buttons.
  encryptButton = new wxButton(frame, ID_ENCRYPT, "Encrypt");
  decryptButton = new wxButton(frame, ID_DECRYPT, "Decrypt");

  // Add buttons to the sizer.
  buttonsSizer->Add(encryptButton, 0, wxALL | wxALIGN_CENTER, 10);
  buttonsSizer->Add(decryptButton, 0, wxALL | wxALIGN_CENTER, 10);

  // Connect this sizer to the main sizer.
  mainSizer->Add(buttonsSizer, 0, wxALL | wxALIGN_CENTER, 0);

  // Connect main window (frame) with sizer.
  frame->SetSizerAndFit(mainSizer);

  // Configure timer.
  readyTimer.SetOwner(frame, ID_READY);

  // Configure event handlers.
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
  wxMessageBox(ex.what(), "Fatal error", wxOK | wxICON_ERROR);

  // Print error message to the terminal.
  std::cerr << ex.what() << std::endl;

  // Do not start the application.
  return false;
}

void fc::FishCode::OnChoose(wxCommandEvent& event) {
  // Open file selector.
  const auto filePath = wxFileSelector(
    "Choose an input file",
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
    "Set an output file",
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
  // Generate encryption key.
  auto key = Key::Generate();

  // Get password.
  const Password password(passwordLine->GetValue().utf8_string());

  // Encrypt the key with password.
  key.Encrypt(password);

  // Get pathes to input and output files.
  const std::filesystem::path inputFilePath(
    inputFileLine->GetValue().utf8_string()
  );
  // Get pathes to input and output files.
  const std::filesystem::path outputFilePath(
    outputFileLine->GetValue().utf8_string()
  );

  // Open the input file.
  InputFile inputFile(inputFilePath, false);

  // Check if pathes are not equivalent.
  if (std::filesystem::exists(outputFilePath)) {
    if (std::filesystem::equivalent(inputFilePath, outputFilePath)) {
      // Invalid output file.
      throw InvalidOutputFileError();
    }
  }

  // Create the output file.
  OutputFile outputFile(outputFilePath);

  // Store encrypted key to the output file.
  outputFile.WriteKey(key);

  // Decrypt the key.
  key.Decrypt(password);

  // Get number of blocks in the input file.
  const auto inputFileBlocks = inputFile.GetBlocksNumber();

  // Display new status in the status bar.
  statusBar->SetStatusText("Encrypting...");

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
  statusBar->SetStatusText("All done");

  // Start timer to the new status.
  readyTimer.StartOnce(3000);
} catch (const std::exception& ex) {
  // Display GUI error message.
  wxMessageBox(ex.what(), "Error", wxOK | wxICON_ERROR);
}

void fc::FishCode::OnDecrypt(wxCommandEvent& event) try {
  // Get pathes to input and output files.
  const std::filesystem::path inputFilePath(
    inputFileLine->GetValue().utf8_string()
  );
  // Get pathes to input and output files.
  const std::filesystem::path outputFilePath(
    outputFileLine->GetValue().utf8_string()
  );

  // Open the input file.
  InputFile inputFile(inputFilePath, true);

  // Check if pathes are not equivalent.
  if (std::filesystem::exists(outputFilePath)) {
    if (std::filesystem::equivalent(inputFilePath, outputFilePath)) {
      // Invalid output file.
      throw InvalidOutputFileError();
    }
  }

  // Get password.
  const Password password(passwordLine->GetValue().utf8_string());

  // Read decryption key from the input file.
  auto key = inputFile.ReadKey();

  // Decrypt key with password.
  key.Decrypt(password);

  // Create the output file.
  OutputFile outputFile(outputFilePath);

  // Get number of blocks in the input file.
  const auto inputFileBlocks = inputFile.GetBlocksNumber();

  // Display new status in the status bar.
  statusBar->SetStatusText("Decrypting...");

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
  statusBar->SetStatusText("All done");

  // Start timer to the new status.
  readyTimer.StartOnce(3000);
} catch (const std::exception& ex) {
  // Display GUI error message.
  wxMessageBox(ex.what(), "Error", wxOK | wxICON_ERROR);
}

void fc::FishCode::OnReadyTimer(wxTimerEvent& event) {
  // Set progress bar to the default state.
  progressBar->SetValue(0);

  // Set default status in the status bar.
  statusBar->SetStatusText("Ready");
}
