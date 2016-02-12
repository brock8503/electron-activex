REM Make sure that the powerpoint dir has the right read/write permissions for users
copy C:\Development\electron\out\D\electron.exe C:\Development\FreeActiveX\vendor\electron\debug\
copy C:\Development\FreeActiveX\vendor\electron\debug\electron.exe "C:\Program Files\Microsoft Office 15\root\office15\debug\"

copy C:\Development\electron\out\D\electron.exe C:\Development\FreeActiveX\vendor\electron\debug\electron_renderer.exe
copy C:\Development\FreeActiveX\vendor\electron\debug\electron_renderer.exe "C:\Program Files\Microsoft Office 15\root\office15\debug\"

copy C:\Development\electron\out\D\electron.lib C:\Development\FreeActiveX\vendor\electron\debug\lib
copy C:\Development\electron\out\D\obj\electron_lib.lib C:\Development\FreeActiveX\vendor\electron\debug\lib

copy C:\Development\FreeActiveX\vendor\electron\debug\FreeActiveX.dll "C:\Program Files\Microsoft Office 15\root\office15\debug\"
