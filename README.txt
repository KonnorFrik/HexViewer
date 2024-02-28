+------------------------------------------------------------------------------+
|                                 Hex viewer                                   |
|  Programm for print byte's from file as hexadecimal number in stdout         |
|------------------------------------------------------------------------------|
|                                   Build                                      |
| run "make" or "make hexviewer" for compile                                   |
|------------------------------------------------------------------------------|
|                                   Flags                                      |
|                                                                              |
| --upper-byte              - Print bytes in upper case                        |
| --byte-type <type>        - Print bytes in given type                        |
|                                     (default: c-type)                        |
|                                                                              |
| --byte-delimiter <symb>   - Print given symbol between bytes                 |
|                                               (default: ' ')                 |
|                                                                              |
| --address-len <number>    - Print address with given length                  |
|                                 min/max printable - address in hex           |
|                                 min/max valid - 1 - 255                      |
|                                                                              |
| --address-type <type>     - Print address in given type                      |
|                                          (default: hex)                      |
|                                                                              |
| --non-decode <symb>       - Print given symbol as non-decoding byte          |
|                                                                              |
| --row-len <number>        - Read and print given count of bytes              |
|                                   min/max: 1, 255 (default: 16)              |
|                                                                              |
| --strings                 - Print row only if any byte can be printed        |
|                                                             as symbol        |
|                                                                              |
| --offset <number>         - Start print file content from given offset       |
|                                  <number> - can be only decimal number       |
|                                                                              |
| --help                    - Show help page                                   |
|------------------------------------------------------------------------------|
