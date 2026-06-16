# Win32-kbd-hook

A small Win32 API project built to explore Windows keyboard hooks, keyboard state management, virtual key codes, and Unicode character translation.

## About

This project was created as a learning exercise to understand how Windows processes keyboard input internally using the Win32 API.

The implementation explores:

* Low-level keyboard hooks (`WH_KEYBOARD_LL`)
* Hook procedures and hook chains
* Virtual Key Codes (VK Codes)
* Keyboard state APIs
* Unicode character translation
* Windows message loops
* Win32 callback conventions

## Features

* Installs a low-level keyboard hook
* Processes keyboard events through a custom hook procedure
* Translates Virtual Key Codes into readable characters
* Tracks modifier key states (Shift, Caps Lock)
* Handles special keys such as:

  * Enter
  * Backspace
  * Tab
  * Space

## Concepts Learned

### Hooks

A hook allows an application to intercept events before they reach their destination.

### Hook Procedure

A callback function invoked by Windows whenever a hooked event occurs.

### Hook Chains

Windows maintains a chain of hook procedures for each hook type. Events pass through the chain until they reach their destination.

### Keyboard State

The project explores the following APIs:

```c
GetKeyboardState()
GetAsyncKeyState()
GetKeyState()
```

to understand how modifier keys affect character generation.

### Unicode Translation

Character translation is performed using:

```c
ToUnicode()
```

which converts keyboard events into their corresponding Unicode characters based on the current keyboard state.

## Technologies

* C
* Win32 API
* Windows Hooks
* Unicode APIs

## Building

Compile using GCC:

```bash
gcc main.c -o kl.exe
```

or using MSVC:

```bash
cl main.c user32.lib
```

## References

* Microsoft Win32 Documentation

## Disclaimer

This repository was created for educational purposes to study Windows internals, input processing, and Win32 programming concepts.
