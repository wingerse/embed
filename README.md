# Embed
Tool used to create object files and header files of resources so they can be embedded in C executables. I use this in my Makefiles.

## Usage:  

	embed [-h] <input>  

`<input>` is a path. When creating the C identifier for the resource, special characters such as `.`, `/` will be converted to `_`. For example, embed `res/harry.png` will be `res_harry_png`.

## Return
Outputs the C `unsigned char` array (with C syntax) of of the resource file to standard output. If `-h` option is given, header file is output instead. This extern variable also contains the size of the array so `sizeof(identifier)` works.  
