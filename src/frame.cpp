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
#include <wx/timer.h>
#include "errors.hpp"
#include "events.hpp"
#include "frame.hpp"
#include "progress.hpp"
#include "strings.hpp"
#include "task.hpp"
#include "types.hpp"

fc::Frame::Frame()
: wxFrame(nullptr, events::ID_FRAME, STR_NAME0)
{
    // Create and configure new menu bar for the frame.
    auto menu_bar = new wxMenuBar();
    auto menu_more = new wxMenu();
    menu_more->Append(wxID_ABOUT, STR_NAME2, STR_PROMPT0);
    menu_more->Append(wxID_HELP, STR_NAME3, STR_PROMPT1);
    menu_bar->Append(menu_more, STR_NAME1);

    // Connect menu bar to the frame.
    SetMenuBar(menu_bar);

    // Configure menu bar event handlers.
    Bind(wxEVT_MENU, &fc::Frame::onAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &fc::Frame::onHelp, this, wxID_HELP);

    // Create and set new status bar for the frame.
    SetStatusBar(CreateStatusBar());

    // Set the default status text.
    SetStatusText(STR_STATUS0);

    // Initialize new sizer (box) for the main window.
    auto box_sizer = new wxBoxSizer(wxVERTICAL);

    // Configure grid sizers layout.
    const wxSize grid_layout(5, 5);

    // Configure sizers (using flags).
    const auto box_flags = wxSizerFlags().Expand().Border(wxALL, 5);
    const auto grid_flags = wxSizerFlags().Expand().Border(wxALL, 10);
    const auto label_grid_flags = wxSizerFlags().Center().Right().Border(wxALL, 2);

    // Set layout for the fields.
    const wxSize fieldSize(400, 45);

    // Configure UI (grid) sizers.
    wxFlexGridSizer* grid_sizers[] = {
        new wxFlexGridSizer(1, 3, grid_layout),
        new wxFlexGridSizer(1, 3, grid_layout),
        new wxFlexGridSizer(1, 2, grid_layout),
        new wxFlexGridSizer(1, 2, grid_layout)
    };
    grid_sizers[0]->AddGrowableCol(1);
    grid_sizers[0]->AddGrowableCol(2);
    grid_sizers[1]->AddGrowableCol(1);
    grid_sizers[1]->AddGrowableCol(2);
    grid_sizers[2]->AddGrowableCol(1);
    grid_sizers[3]->AddGrowableCol(0);
    grid_sizers[3]->AddGrowableCol(1);

    // Create and configure input fields.
    fields[0] = new Field(this);
    fields[1] = new Field(this);
    fields[2] = new PasswordField(this);
    fields[0]->SetMinSize(fieldSize);
    fields[1]->SetMinSize(fieldSize);
    fields[2]->SetMaxLength(Password::SIZE);
    fields[2]->SetMinSize(fieldSize);
    labels[0] = new Label(this, STR_LABEL0);
    labels[1] = new Label(this, STR_LABEL1);
    labels[2] = new Label(this, STR_LABEL4);
    grid_sizers[0]->Add(labels[0], label_grid_flags);
    grid_sizers[0]->Add(fields[0], grid_flags);
    grid_sizers[1]->Add(labels[1], label_grid_flags);
    grid_sizers[1]->Add(fields[1], grid_flags);
    grid_sizers[2]->Add(labels[2], label_grid_flags);
    grid_sizers[2]->Add(fields[2], grid_flags);

    // Create buttons.
    buttons[0] = new Button(this, events::ID_CHOOSE, STR_LABEL2);
    buttons[1] = new Button(this, events::ID_SET, STR_LABEL3);
    buttons[2] = new Button(this, events::ID_ENCRYPT, STR_LABEL5);
    buttons[3] = new Button(this, events::ID_DECRYPT, STR_LABEL6);
    buttons[4] = new Button(this, events::ID_CANCEL, STR_LABEL7);

    // Disable "Cancel" button for now.
    buttons[4]->Disable();

    // Configure input control buttons.
    grid_sizers[0]->Add(buttons[0], grid_flags);
    grid_sizers[1]->Add(buttons[1], grid_flags);

    // Add grid with input fields and controls to the frame (using sizers).
    box_sizer->Add(grid_sizers[0], box_flags);
    box_sizer->Add(grid_sizers[1], box_flags);
    box_sizer->Add(grid_sizers[2], box_flags);

    // Create a progress bar.
    progress_bar = new ProgressBar(this);

    // Disable progress bar for now.
    progress_bar->Disable();

    // Add progress bar to the frame.
    box_sizer->Add(progress_bar, box_flags);

    // Configure main control buttons.
    grid_sizers[3]->Add(buttons[2], grid_flags);
    grid_sizers[3]->Add(buttons[3], grid_flags);

    // Add main control buttons to the frame (using sizer).
    box_sizer->Add(grid_sizers[3], grid_flags);

    // Configure "Cancel" button.
    box_sizer->Add(buttons[4], box_flags);

    // Set up button event handlers.
    buttons[0]->Bind(wxEVT_BUTTON, &fc::Frame::onChoose, this, events::ID_CHOOSE);
    buttons[1]->Bind(wxEVT_BUTTON, &fc::Frame::onSet, this, events::ID_SET);
    buttons[2]->Bind(wxEVT_BUTTON, &fc::Frame::onEncrypt, this, events::ID_ENCRYPT);
    buttons[3]->Bind(wxEVT_BUTTON, &fc::Frame::onDecrypt, this, events::ID_DECRYPT);
    buttons[4]->Bind(wxEVT_BUTTON, &fc::Frame::onCancel, this, events::ID_CANCEL);

    // Connect main window (frame) with its sizer.
    SetSizerAndFit(box_sizer);

    // Create and configure timer.
    ready_timer = std::make_unique<wxTimer>(this, events::ID_READY);

    // Configure timer event handler.
    Bind(wxEVT_TIMER, &fc::Frame::onReadyTimer, this, events::ID_READY);

    // Set up status update handlers.
    Bind(events::EVT_UPDATE_DONE, &fc::Frame::onDoneUpdate, this, events::ID_FRAME);
    Bind(events::EVT_UPDATE_PROGRESS, &fc::Frame::onProgressUpdate, this, events::ID_FRAME);

    // Configure worker thread exception handler.
    Bind(events::EVT_TASK_EXCEPTION, &fc::Frame::onTaskException, this, events::ID_FRAME);

    // Configure frame closing handler.
    Bind(wxEVT_CLOSE_WINDOW, &fc::Frame::onClose, this, events::ID_FRAME);
}

void fc::Frame::onAbout([[maybe_unused]] wxCommandEvent& event)
{
    // Configure the about dialog.
    wxAboutDialogInfo about_info;
    about_info.SetName(STR_NAME0);
    about_info.SetVersion(STR_VERSION);
    about_info.SetDescription(STR_DESCRYPTION);
    about_info.SetCopyright(STR_COPYRIGHT);
    about_info.AddDeveloper(STR_DEVELOPER);

    // Show about box.
    wxAboutBox(about_info, this);
}

void fc::Frame::onCancel([[maybe_unused]] wxCommandEvent& event)
{
    // Disable "Cancel" button.
    disableCancelButton();

    // Enable task abortion.
    abort_task = true;

    // Wait for the task termination (if there is a task).
    if (task_thread) {
        if (task_thread->joinable()) {
            task_thread->join();
        }
    }

    // Disable task abortion.
    abort_task = false;

    // Set new status in the status bar.
    SetStatusText(STR_STATUS2);

    // Start timer to the new status.
    ready_timer->StartOnce(3000);
}

void fc::Frame::onClose([[maybe_unused]] wxCloseEvent& event)
{
    // Abort the task (if it is running).
    abort_task = true;

    // Wait for the task termination (if there is a task).
    if (task_thread) {
        if (task_thread->joinable()) {
            task_thread->join();
        }
    }

    // Destroy window (frame) and all of its subwindows.
    Destroy();
}

void fc::Frame::onEncrypt([[maybe_unused]] wxCommandEvent& event) try {
    // Set frame to the "processing" mode.
    disableButtons();
    disableFields();
    enableCancelButton();
    enableProgressBar();

    // Display new status in the status bar.
    SetStatusText(STR_STATUS3);

    // Check user data.
    checkFileIO(getIFPathValue().utf8_string(), getOFPathValue().utf8_string());

    // Allocate memory for the task data.
    auto data = std::make_unique<TaskData>();

    // Store task data.
    data->setInputFile(File(Path(getIFPathValue().utf8_string()), FileType::input));
    data->setOutputFile(File(Path(getOFPathValue().utf8_string()), FileType::output));
    data->setPassword(Password(getPasswordValue().utf8_string()));

    // Create new thread for the encryption task.
    task_thread = std::make_unique<std::thread>(encrypt, this, std::move(data));
}
catch (const std::exception& ex) {
    // Send a message about the task abortion.
    wxPostEvent(buttons[4], wxCommandEvent(wxEVT_BUTTON, events::ID_CANCEL));

    // Display GUI error message.
    wxMessageBox(ex.what(), STR_CAPTION4, wxOK | wxCENTRE | wxICON_ERROR, this);
}

void fc::Frame::onDecrypt([[maybe_unused]] wxCommandEvent& event) try {
    // Set frame to the "processing" mode.
    disableButtons();
    disableFields();
    enableCancelButton();
    enableProgressBar();

    // Display new status in the status bar.
    SetStatusText(STR_STATUS4);

    // Check user data.
    checkFileIO(getIFPathValue().utf8_string(), getOFPathValue().utf8_string());

    // Allocate memory for the task data.
    auto data = std::make_unique<TaskData>();

    // Store task data.
    data->setInputFile(File(Path(getIFPathValue().utf8_string()), FileType::input, true));
    data->setOutputFile(File(Path(getOFPathValue().utf8_string()), FileType::output));
    data->setPassword(Password(getPasswordValue().utf8_string()));

    // Create new thread for the decryption task.
    task_thread = std::make_unique<std::thread>(decrypt, this, std::move(data));
}
catch (const std::exception& ex) {
    // Send a message about the task abortion.
    wxPostEvent(buttons[4], wxCommandEvent(wxEVT_BUTTON, events::ID_CANCEL));

    // Display GUI error message.
    wxMessageBox(ex.what(), STR_CAPTION4, wxOK | wxCENTRE | wxICON_ERROR, this);
}

void fc::Frame::onDoneUpdate([[maybe_unused]] fc::events::UpdateDone& event) {
    // Disable "Cancel" button.
    disableCancelButton();

    // Join task thread to replace it in the future.
    if (task_thread) {
        if (task_thread->joinable()) {
            task_thread->join();
        }
    }

    // Set new value in the progress bar (100%).
    progress_bar->SetValue(100);

    // Set new status in the status bar.
    SetStatusText(STR_STATUS1);

    // Refresh the frame.
    Refresh();

    // Start timer to the new status.
    ready_timer->StartOnce(3000);
}

void fc::Frame::onHelp([[maybe_unused]] wxCommandEvent& event)
{
    // Display a message box with short documentation.
    wxMessageBox(STR_DOCUMENTATION, STR_CAPTION0, wxOK | wxCENTRE | wxICON_QUESTION, this);
}

void fc::Frame::onProgressUpdate(events::UpdateProgress& event)
{
    // Set new value in the progress bar.
    progress_bar->SetValue(event.getProgress());

    // Refresh the frame.
    Refresh();
}

void fc::Frame::onReadyTimer([[maybe_unused]] wxTimerEvent& event)
{
    // Set default status in the status bar.
    SetStatusText(STR_STATUS0);

    // Set progress bar to the default state (0%).
    progress_bar->SetValue(0);

    // Set frame to the default state.
    enableButtons();
    enableFields();
    disableProgressBar();
}

void fc::Frame::onChoose([[maybe_unused]] wxCommandEvent& event)
{
    // Open file selector.
    const auto path = wxFileSelector(
        STR_CAPTION1,
        std::getenv(STR_PATTERN0),
        wxEmptyString,
        wxEmptyString,
        wxFileSelectorDefaultWildcardStr,
        wxFD_OPEN,
        this
    );

    // Check if user has chosen the file.
    if (!path.empty()) {
        // Insert file path to the input field.
        setIFPathValue(path);
    }
}

void fc::Frame::onSet([[maybe_unused]] wxCommandEvent& event)
{
    // Open file selector.
    const auto path = wxFileSelector(
        STR_CAPTION2,
        std::getenv(STR_PATTERN0),
        wxEmptyString,
        wxEmptyString,
        wxFileSelectorDefaultWildcardStr,
        wxFD_SAVE,
        this
    );

    // Check if user has set the file.
    if (!path.empty()) {
        // Insert file path to the input field.
        setOFPathValue(path);
    }
}

void fc::Frame::onTaskException(events::TaskException& event)
{
    // Display GUI error message.
    wxMessageBox(event.what(), STR_CAPTION4, wxOK | wxCENTRE | wxICON_ERROR, this);
}

void fc::Frame::disableButtons()
{
    // Disable all buttons in the collection (except "Cancel" button).
    for (auto button : buttons) {
        // Check if it is not a "Cancel" button.
        if (button == buttons[4]) {
            // Skip.
            continue;
        }

        // Disable this button.
        button->Disable();
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

void fc::Frame::enableButtons()
{
    // Enable all buttons in the collection (except "Cancel" button).
    for (auto button : buttons) {
        // Check if it is not a "Cancel" button.
        if (button == buttons[4]) {
            // Skip.
            continue;
        }

        // Enable this button.
        button->Enable();
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
