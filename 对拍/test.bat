@echo off
:loop
	rand.exe %random% > in.txt
	std.exe < in.txt > std.txt
	my.exe < in.txt > my.txt
	fc std.txt my.txt
if not errorlevel 1 goto loop
pause
goto loop