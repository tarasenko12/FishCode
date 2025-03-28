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

#include <chrono>
#include <exception>
#include <memory>
#include <thread>
#include <utility>
#include <cstdlib>
#include <wx/aboutdlg.h>
#include <wx/event.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include "errors.hpp"
#include "events.hpp"
#include "file.hpp"
#include "frame.hpp"
#include "progress.hpp"
#include "strings.hpp"
#include "task.hpp"

fc::Frame::Frame()
: wxFrame(nullptr, fc::events::ID_FRAME, strings::NAME0)
{
    // Create and configure new menu bar for the frame.
    auto menuBar = new wxMenuBar();
    auto menuMore = new wxMenu();
    menuMore->Append(wxID_ABOUT, strings::NAME2, strings::PROMPT0);
    menuMore->Append(wxID_HELP, strings::NAME3, strings::PROMPT1);
    menuBar->Append(menuMore, strings::NAME1);

    // Connect menu bar to the frame.
    SetMenuBar(menuBar);

    // Configure menu bar event handlers.
    Bind(wxEVT_MENU, &fc::Frame::onAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &fc::Frame::onHelp, this, wxID_HELP);

    // Create and set new status bar for the frame.
    SetStatusBar(CreateStatusBar());

    // Set the default status text.
    SetStatusText(strings::STATUS0);

    // Initialize new sizer (box) for the main window.
    auto boxSizer = new wxBoxSizer(wxVERTICAL);

    // Configure grid sizers layout.
    const wxSize gridLayout(5, 5);

    // Configure sizers (using flags).
    const auto boxSizerFlags = wxSizerFlags().Expand().Border(wxALL, 5);
    const auto gridSizerFlags = wxSizerFlags().Expand().Border(wxALL, 10);
    const auto gridLabelSizerFlags = wxSizerFlags().Center().Right().Border(wxALL, 2);

    // Set layout for the fields.
    const wxSize fieldSize(400, 45);

    // Configure UI (grid) sizers.
    wxFlexGridSizer* gridSizers[] = {
        new wxFlexGridSizer(1, 3, gridLayout),
        new wxFlexGridSizer(1, 3, gridLayout),
        new wxFlexGridSizer(1, 2, gridLayout),
        new wxFlexGridSizer(1, 2, gridLayout)
    };
    gridSizers[0]->AddGrowableCol(1);
    gridSizers[0]->AddGrowableCol(2);
    gridSizers[1]->AddGrowableCol(1);
    gridSizers[1]->AddGrowableCol(2);
    gridSizers[2]->AddGrowableCol(1);
    gridSizers[3]->AddGrowableCol(0);
    gridSizers[3]->AddGrowableCol(1);

    // Create and configure input fields.
    fields[0] = new Field(this);
    fields[1] = new Field(this);
    fields[2] = new PasswordField(this);
    fields[0]->SetMinSize(fieldSize);
    fields[1]->SetMinSize(fieldSize);
    fields[2]->SetMaxLength(Password::SIZE);
    fields[2]->SetMinSize(fieldSize);
    labels[0] = new Label(this, strings::LABEL0);
    labels[1] = new Label(this, strings::LABEL1);
    labels[2] = new Label(this, strings::LABEL4);
    gridSizers[0]->Add(labels[0], gridLabelSizerFlags);
    gridSizers[0]->Add(fields[0], gridSizerFlags);
    gridSizers[1]->Add(labels[1], gridLabelSizerFlags);
    gridSizers[1]->Add(fields[1], gridSizerFlags);
    gridSizers[2]->Add(labels[2], gridLabelSizerFlags);
    gridSizers[2]->Add(fields[2], gridSizerFlags);

    // Create buttons.
    buttons[0] = new Button(this, events::ID_CHOOSE, strings::LABEL2);
    buttons[1] = new Button(this, events::ID_SET, strings::LABEL3);
    buttons[2] = new Button(this, events::ID_ENCRYPT, strings::LABEL5);
    buttons[3] = new Button(this, events::ID_DECRYPT, strings::LABEL6);
    buttons[4] = new Button(this, events::ID_CANCEL, strings::LABEL7);

    // Disable "Cancel" button for now.
    buttons[4]->Disable();

    // Configure input control buttons.
    gridSizers[0]->Add(buttons[0], gridSizerFlags);
    gridSizers[1]->Add(buttons[1], gridSizerFlags);

    // Add grid with input fields and controls to the frame (using sizers).
    boxSizer->Add(gridSizers[0], boxSizerFlags);
    boxSizer->Add(gridSizers[1], boxSizerFlags);
    boxSizer->Add(gridSizers[2], boxSizerFlags);

    // Create a progress bar.
    progressBar = new ProgressBar(this);

    // Disable progress bar for now.
    progressBar->Disable();

    // Add progress bar to the frame.
    boxSizer->Add(progressBar, boxSizerFlags);

    // Configure main control buttons.
    gridSizers[3]->Add(buttons[2], gridSizerFlags);
    gridSizers[3]->Add(buttons[3], gridSizerFlags);

    // Add main control buttons to the frame (using sizer).
    boxSizer->Add(gridSizers[3], gridSizerFlags);

    // Configure "Cancel" button.
    boxSizer->Add(buttons[4], boxSizerFlags);

    // Set up button event handlers.
    buttons[0]->Bind(wxEVT_BUTTON, &fc::Frame::onChoose, this, events::ID_CHOOSE);
    buttons[1]->Bind(wxEVT_BUTTON, &fc::Frame::onSet, this, events::ID_SET);
    buttons[2]->Bind(wxEVT_BUTTON, &fc::Frame::onEncrypt, this, events::ID_ENCRYPT);
    buttons[3]->Bind(wxEVT_BUTTON, &fc::Frame::onDecrypt, this, events::ID_DECRYPT);
    buttons[4]->Bind(wxEVT_BUTTON, &fc::Frame::onCancel, this, events::ID_CANCEL);

    // Connect main window (frame) with its sizer.
    SetSizerAndFit(boxSizer);

    // Set up status update handlers.
    Bind(events::EVT_UPDATE_DONE, &fc::Frame::onDone, this, events::ID_FRAME);
    Bind(events::EVT_UPDATE_PROGRESS, &fc::Frame::onProgressUpdate, this, events::ID_FRAME);

    // Configure worker thread exception handler.
    Bind(events::EVT_TASK_EXCEPTION, &fc::Frame::onTaskException, this, events::ID_FRAME);

    // Configure timer event handler.
    Bind(events::EVT_READY_EVENT, &fc::Frame::onReady, this, events::ID_FRAME);

    // Configure frame closing handler.
    Bind(wxEVT_CLOSE_WINDOW, &fc::Frame::onClose, this, events::ID_FRAME);
}

void fc::Frame::onAbout([[maybe_unused]] wxCommandEvent& event)
{
    // Configure the about dialog.
    wxAboutDialogInfo aboutInfo;
    aboutInfo.SetName(strings::NAME0);
    aboutInfo.SetVersion(strings::VERSION);
    aboutInfo.SetDescription(strings::DESCRYPTION);
    aboutInfo.SetCopyright(strings::COPYRIGHT);
    aboutInfo.AddDeveloper(strings::DEVELOPER);

    // Show about box.
    wxAboutBox(aboutInfo, this);
}

void fc::Frame::onCancel([[maybe_unused]] wxCommandEvent& event)
{
    // Disable "Cancel" button.
    disableCancelButton();

    // Set task abortion flag.
    abortTask = true;

    // Wait for the task termination (if there is a task).
    if (taskThread) {
        if (taskThread->joinable()) {
            taskThread->join();
        }
    }

    // Unset task abortion flag (already aborted).
    abortTask = false;

    // Set new status in the status bar.
    SetStatusText(strings::STATUS2);

    // Join timer thread for replacing.
    if (timerThread) {
        if (timerThread->joinable()) {
            timerThread->join();
        }
    }

    // Start timer to the next status.
    timerThread = std::make_unique<std::thread>([this]() {
        using namespace std::chrono_literals;

        // Sleep for the specified time.
        std::this_thread::sleep_for(500ms);

        // Send an event about timer end.
        wxQueueEvent(this, events::ReadyEvent(events::ID_FRAME).Clone());
    });
}

void fc::Frame::onChoose([[maybe_unused]] wxCommandEvent& event)
{
    // Use "global" home directory as default path.
    wxString defaultPath = "/home";

    // Try to use user's home as default file selector path.
    if (const auto homePath = std::getenv(strings::PATTERN0)) {
        // Use user's home directory.
        defaultPath = homePath;
    }

    // Open file selector.
    const auto filePath = File::Path(wxFileSelector(
        strings::CAPTION1,
        defaultPath,
        wxEmptyString,
        wxEmptyString,
        wxFileSelectorDefaultWildcardStr,
        wxFD_OPEN,
        this
    ).utf8_string());

    // Check if user has chosen the file.
    if (!filePath.empty()) {
        // Insert file path to the input field.
        setIFPath(filePath);
    }
}

void fc::Frame::onClose([[maybe_unused]] wxCloseEvent& event)
{
    // Abort the task (if it is running).
    abortTask = true;

    // Wait for the task termination (if there is a task).
    if (taskThread) {
        if (taskThread->joinable()) {
            taskThread->join();
        }
    }

    // Wait for the timer end (if there is a timer).
    if (timerThread) {
        if (timerThread->joinable()) {
            timerThread->join();
        }
    }

    // Destroy window (frame) and all of its subwindows.
    Destroy();
}

void fc::Frame::onDecrypt([[maybe_unused]] wxCommandEvent& event) try {
    // Set frame to the "processing" mode.
    disableButtons();
    disableFields();
    enableCancelButton();
    enableProgressBar();

    // Display new status in the status bar.
    SetStatusText(strings::STATUS4);

    // Get pathes to input and output files.
    const auto ifPath = getIFPath();
    const auto ofPath = getOFPath();

    // Check file I/O configuration.
    checkFileIO(ifPath, ofPath);

    // Allocate memory for the task data.
    auto task = std::make_unique<Task>();

    // Set up task data.
    task->setInputFile(File(ifPath, File::Type::input, true));
    task->setOutputFile(File(ofPath, File::Type::output));
    task->setPassword(Password(getPasswordString()));

    // Create new thread for the decryption task.
    taskThread = std::make_unique<std::thread>(decrypt, this, std::move(task));
}
catch (const std::exception& ex) {
    // Send a message about the task abortion.
    wxPostEvent(buttons[4], wxCommandEvent(wxEVT_BUTTON, events::ID_CANCEL));

    // Display GUI error message.
    wxMessageBox(ex.what(), strings::CAPTION4, wxOK | wxCENTRE | wxICON_ERROR, this);
}

void fc::Frame::onDone([[maybe_unused]] fc::events::DoneEvent& event)
{
    // Disable "Cancel" button.
    disableCancelButton();

    // Join task thread to replace it in the future.
    if (taskThread) {
        if (taskThread->joinable()) {
            taskThread->join();
        }
    }

    // Set new value in the progress bar (100%).
    progressBar->SetValue(100);

    // Set new status in the status bar.
    SetStatusText(strings::STATUS1);

    // Refresh the frame.
    Refresh();

    // Join timer thread for replacing.
    if (timerThread) {
        if (timerThread->joinable()) {
            timerThread->join();
        }
    }

    // Start timer to the next status.
    timerThread = std::make_unique<std::thread>([this]() {
        using namespace std::chrono_literals;

        // Sleep for the specified time.
        std::this_thread::sleep_for(3s);

        // Send an event about timer end.
        wxQueueEvent(this, events::ReadyEvent(events::ID_FRAME).Clone());
    });
}

void fc::Frame::onEncrypt([[maybe_unused]] wxCommandEvent& event) try {
    // Set frame to the "processing" mode.
    disableButtons();
    disableFields();
    enableCancelButton();
    enableProgressBar();

    // Display new status in the status bar.
    SetStatusText(strings::STATUS3);

    // Get pathes to input and output files.
    const auto ifPath = getIFPath();
    const auto ofPath = getOFPath();

    // Check file I/O configuration.
    checkFileIO(ifPath, ofPath);

    // Allocate memory for the task data.
    auto task = std::make_unique<Task>();

    // Set up task data.
    task->setInputFile(File(ifPath, File::Type::input));
    task->setOutputFile(File(ofPath, File::Type::output));
    task->setPassword(Password(getPasswordString()));

    // Create new thread for the encryption task.
    taskThread = std::make_unique<std::thread>(encrypt, this, std::move(task));
}
catch (const std::exception& ex) {
    // Send a message about the task abortion.
    wxPostEvent(buttons[4], wxCommandEvent(wxEVT_BUTTON, events::ID_CANCEL));

    // Display GUI error message.
    wxMessageBox(ex.what(), strings::CAPTION4, wxOK | wxCENTRE | wxICON_ERROR, this);
}

void fc::Frame::onHelp([[maybe_unused]] wxCommandEvent& event)
{
    // Display a message box with short documentation.
    wxMessageBox(strings::DOCUMENTATION, strings::CAPTION0, wxOK | wxCENTRE | wxICON_QUESTION, this);
}

void fc::Frame::onProgressUpdate(events::UpdateProgress& event)
{
    // Set new value in the progress bar.
    progressBar->SetValue(event.GetProgress());

    // Refresh the frame.
    Refresh();
}

void fc::Frame::onReady([[maybe_unused]] events::ReadyEvent& event)
{
    // Set default status in the status bar.
    SetStatusText(strings::STATUS0);

    // Set default value in the progress bar.
    progressBar->SetValue(0);

    // Enable controls.
    enableButtons();
    enableFields();

    // Disable progress bar and "Cancel" button.
    disableProgressBar();
    disableCancelButton();
}

void fc::Frame::onSet([[maybe_unused]] wxCommandEvent& event)
{
    // Use "global" home directory as default path.
    wxString defaultPath = "/home";

    // Try to use user's home as default file selector path.
    if (const auto homePath = std::getenv(strings::PATTERN0)) {
        // Use user's home directory.
        defaultPath = homePath;
    }

    // Open file selector.
    const auto filePath = File::Path(wxFileSelector(
        strings::CAPTION2,
        defaultPath,
        wxEmptyString,
        wxEmptyString,
        wxFileSelectorDefaultWildcardStr,
        wxFD_SAVE,
        this
    ).utf8_string());

    // Check if user has set the file.
    if (!filePath.empty()) {
        // Insert file path to the output field.
        setOFPath(filePath);
    }
}

void fc::Frame::onTaskException(events::TaskException& event) {
    // Display GUI error message.
    wxMessageBox(event.what(), strings::CAPTION4, wxOK | wxCENTRE | wxICON_ERROR, this);
}

void fc::Frame::disableCancelButton()
{
    // Find "Cancel" button in the collection.
    for (auto button : buttons) {
        if (button->GetLabelText() == strings::LABEL7) {
            // Disable it.
            button->Disable();
        }
    }
}

void fc::Frame::disableButtons()
{
    // Disable all buttons in the collection (except "Cancel" button).
    for (auto button : buttons) {
        // Check if it is not a "Cancel" button.
        if (button->GetLabelText() != strings::LABEL7) {
            // Disable this button.
            button->Disable();
        }
    }
}

void fc::Frame::disableFields()
{
    // Disable all input fields.
    for (auto field : fields) {
        // Disable this field.
        field->Disable();
    }
}

void fc::Frame::enableCancelButton()
{
    // Find "Cancel" button in the collection.
    for (auto button : buttons) {
        if (button->GetLabelText() == strings::LABEL7) {
            // Enable it.
            button->Enable();
        }
    }
}

void fc::Frame::enableButtons()
{
    // Enable all buttons in the collection (except "Cancel" button).
    for (auto button : buttons) {
        // Check if it is not a "Cancel" button.
        if (button->GetLabelText() != strings::LABEL7) {
            // Disable this button.
            button->Enable();
        }
    }
}

void fc::Frame::enableFields()
{
    // Enable all input fields.
    for (auto field : fields) {
        // Enable this field.
        field->Enable();
    }
}
