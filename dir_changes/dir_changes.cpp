// dir_changes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//
//	The MIT License
//
//	Copyright (c) 2010 James E Beveridge
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.


//	This sample code is for my blog entry titled, "Understanding ReadDirectoryChangesW"
//	http://qualapps.blogspot.com/2010/05/understanding-readdirectorychangesw.html
//	See ReadMe.txt for overview information.








//
// When the application starts, it immediately starts monitoring your home
// directory, including children, as well as C:\, not including children.
// The application exits when you hit Esc.
// You can add a directory to the monitoring list by typing the directory
// name and hitting Enter. Notifications will pause while you type.
//

#include "DirChange.h"

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{

	DirChange dirChange;
	dirChange.AddDirectory(_T("C:\\Users\\bbgonzaX\\AppData\\Local\\Intel Telemetry\\deadbeef\\deadbeef-dead-beef-dead-beefdeadbeef\\"), false, DirChange::dwNotificationFlags);;
	dirChange.Run();

	return EXIT_SUCCESS;
}

