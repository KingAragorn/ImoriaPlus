// Copyright (c) 1981-86 Robert A. Koeneke
// Copyright (c) 1987-94 James E. Wilson
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Headless stand-in for src/ui_io.cpp.
// The smoke test links this file instead of the curses front end, which is
// the same seam a future browser build would use.

#include "headers.h"

int eof_flag = 0;
bool panic_save = false;

bool terminalInitialize() {
    return true;
}
void terminalRestore() {
}
void terminalSaveScreen() {
}
void terminalRestoreScreen() {
}
ssize_t terminalBellSound() {
    return 0;
}
void putQIO() {
}
void flushInputBuffer() {
}
void clearScreen() {
}
void clearToBottom(int row) {
    (void) row;
}
void moveCursor(Coord_t coord) {
    (void) coord;
}
void addChar(char ch, Coord_t coord) {
    (void) ch;
    (void) coord;
}
void putString(const char *out_str, Coord_t coord) {
    (void) out_str;
    (void) coord;
}
void putStringClearToEOL(const std::string &str, Coord_t coord) {
    (void) str;
    (void) coord;
}
void eraseLine(Coord_t coord) {
    (void) coord;
}
void panelMoveCursor(Coord_t coord) {
    (void) coord;
}
void panelPutTile(char ch, Coord_t coord) {
    (void) ch;
    (void) coord;
}
void messageLinePrintMessage(std::string message) {
    (void) message;
}
void messageLineClear() {
}
void printMessage(const char *msg) {
    (void) msg;
}
void printMessageNoCommandInterrupt(const std::string &msg) {
    (void) msg;
}
char getKeyInput() {
    return ESCAPE;
}
bool getCommand(const std::string &prompt, char &command) {
    (void) prompt;
    command = ESCAPE;
    return false;
}
bool getMenuItemId(const std::string &prompt, char &command) {
    (void) prompt;
    command = ESCAPE;
    return false;
}
bool getTileCharacter(const std::string &prompt, char &command) {
    (void) prompt;
    command = ESCAPE;
    return false;
}
bool getStringInput(char *in_str, Coord_t coord, int slen) {
    (void) coord;
    if (in_str != nullptr && slen > 0) {
        in_str[0] = '\0';
    }
    return false;
}
bool getInputConfirmation(const std::string &prompt) {
    (void) prompt;
    return true;
}
int getInputConfirmationWithAbort(int column, const std::string &prompt) {
    (void) column;
    (void) prompt;
    return 1;
}
void waitForContinueKey(int line_number) {
    (void) line_number;
}
bool checkForNonBlockingKeyPress(int microseconds) {
    (void) microseconds;
    return false;
}
void getDefaultPlayerName(char *buffer) {
    if (buffer != nullptr) {
        std::strcpy(buffer, "Tester");
    }
}
bool checkFilePermissions() {
    return true;
}

#ifndef _WIN32
#undef fopen
#undef open

FILE *tfopen(const char *file, const char *mode) {
    return std::fopen(file, mode);
}
int topen(const char *file, int flags, int mode) {
    return ::open(file, flags, mode);
}
bool tilde(const char *file, char *expanded) {
    if (expanded != nullptr && file != nullptr) {
        std::strcpy(expanded, file);
    }
    return true;
}
#endif
