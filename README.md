# QuickSoundSwitcher

[![Version](https://img.shields.io/github/v/release/odizinne/quicksoundswitcher)]()
[![Github All Releases](https://img.shields.io/github/downloads/odizinne/quicksoundswitcher/total.svg)]()
[![license](https://img.shields.io/github/license/odizinne/quicksoundswitcher)]()

Popup panel for controlling windows I/O audio devices.  
While default sound menu in quick access menu does the job, it does not support switching communication device nor input device.

![image](.assets/screenshot.png)

## Usage

Left click on the tray icon to reveal the panel.  
Click anywhere or press `ESC` to close the panel.

## Installation

### Using OPM

- Install OPM  
In windows terminal:
```
Invoke-Expression (New-Object System.Net.WebClient).DownloadString('https://raw.githubusercontent.com/Odizinne/opm/refs/heads/main/opm_install.ps1')
```

- Open a new windows terminal

- Install QuickSoundSwitcher  
In windows terminal:
```
opm update
opm install quicksoundswitcher
```

**QuickSoundSwitcher** will be available in your start menu.

### Manually

Download latest release, extract it, and run `QuickSoundSwitcher.exe`.

