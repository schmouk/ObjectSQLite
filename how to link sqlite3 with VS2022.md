[C++ Linking SQLite to Visual Studio 2019 project](https://stackoverflow.com/questions/69336491/c-linking-sqlite-to-visual-studio-2019-project)

... You should include the sqlite3.h file and follow these instructions.

I found that I not only had to download the amalgmation files but also the dll files (for either x64 or x86 depending on your flavor). I used [https://sqlite.org/2021/sqlite-dll-win32-x86-3360000.zip](https://sqlite.org/2021/sqlite-dll-win32-x86-3360000.zip), which gave me a .dll and a .def file.

Copy them to your project directory and then open up a Visual Studio command prompt (terminal in the View menu).  
Browse to the directory that you've copied the files to and type LIB /DEF:sqlite3.def. This will create a library file for VS to use.  
Add this file to your project dependencies at Project Properties -> Configuration Properties -> Linker -> Input -> Additional Dependencies (you'll have to type it in manually as you can't browse).

Compiling in Visual Studio should now work successfully.

Notice:  
Add /MACHINE:x64 as well to the command line in VS terminal...  
Then, put sqlite3.def and sqlite3.dll in the root directory!
