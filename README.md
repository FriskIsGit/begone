# Begone
### Nukes specified files or directories without confirmation
This is a program for users who want to quickly remove files or directories owned by the Windows system (SIDs).
https://learn.microsoft.com/en-us/windows-server/identity/ad-ds/manage/understand-security-identifiers
<br>
Attempts to delete these files will fail with an "Access denied" or "Permission denied" message.
<br>
To get past that users have to type out lengthy commands every time

### Delete a directory and everything inside it
```sh
begone C:/Windows/System32/InternetExplorer
```

### Delete a file
```sh
begone C:/Windows/SysWOW64/Magnify.exe
```

### This is also allowed
```sh
begone /C/Windows/SysWOW64/Magnify.exe
```