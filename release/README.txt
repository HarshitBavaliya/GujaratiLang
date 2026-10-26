GujaratiLang portable releases
==============================

This package includes the GujaratiLang interpreter and sample programs. No
compiler, CMake, or Git installation is needed to run it.
The LICENSE file contains the project's MIT license.

Run the included sample
-----------------------

Windows:
   .\gujarati.exe .\examples\hello.gj

To install GujaratiLang in your user PATH, open PowerShell in the extracted
folder and run:

   powershell -ExecutionPolicy Bypass -File .\install.ps1

The installer does not require administrator access. Open a new terminal after
installation, then run "gujarati --repl" or "gujarati C:\path\to\program.gj".

Linux or macOS:
   ./gujarati ./examples/hello.gj

To try interactive input instead, run:

Windows:
   .\gujarati.exe .\examples\input.gj

Linux or macOS:
   ./gujarati ./examples/input.gj

Type a response and press Enter when the program prompts you.

Start the interactive REPL
--------------------------

Windows:
   .\gujarati.exe --repl

Linux or macOS:
   ./gujarati --repl

Enter one complete statement or expression per line. Variables and functions
stay available for the session. Enter Ctrl+Z then Enter on Windows, or Ctrl+D
on Linux/macOS, to exit.

Run your own program
--------------------

Pass the path to a GujaratiLang source file ending in .gj:

Windows:
   .\gujarati.exe C:\path\to\your-program.gj

Linux or macOS:
   ./gujarati /path/to/your-program.gj

On macOS, these binaries are not signed or notarized, so macOS may display a
security warning.

You can download more examples and read the language guide at:
https://github.com/HarshitBavaliya/GujaratiLang

For your security, download releases only from the official project page:
https://github.com/HarshitBavaliya/GujaratiLang/releases

Start with the beginner tutorial:
https://github.com/HarshitBavaliya/GujaratiLang/blob/main/docs/tutorial.md

The release includes checksums.txt with SHA-256 checksums for all platform
packages.
