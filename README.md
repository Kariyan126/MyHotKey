# MyHotKey
MyHotKey is an application that allows you to shutdown, sleep or restart your windows pc using hotkey.

#2 System requirements:
You need to Rregister this app in the registry to make it a startup application.
1. Open the registry
2. Move to this:

```
HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
```
3. Make a new value. The name is MyHotKey and the value is the path which you locate this app.
4. Completion

#2 HotKey
You can use following hotkey.
- Ctrl + F12 (shutdown)
- Ctrl + Shift + Alt + S (sleep)
- Ctrl + Shift + Alt + R (restart)
