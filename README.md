# Automatic color filtering
Toggles on/off built-in Windows grayscale mode for better focus.

## What it does:

1. Sets HKCU registry value for color filter. However, Windows does not immediately update from this value.
2. So, send color filter shortcut key press (ctrl + windows + c) twice 
    1. Once so Windows reads registry value (does nothing from a user standpoint)
    2. Twice so that color filter state reflects registry value

My first project with C++. 