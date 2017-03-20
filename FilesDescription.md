# Description of the files

## Basic rules
A GiD problemtype must have a name, and it's mandatory files must have this name.

In this example, the name is 'cmas2d_customlib', so all the files will have this name.

## Mandatory files
* cmas2d_customlib.xml
* cmas2d_customlib.tcl
* cmas2d_customlib_default.spd
* cmas2d_customlib.win.bat
* cmas2d_customlib.unix.bat

### xml file
This file contains basic information about the problemtype, such as the version number

### tcl file
This is the main tcl file. Here you can:
* Implement [GiD Events](http://www.gidhome.com/documents/customizationmanual/TCL+AND+TK+EXTENSION/Event+procedures)
* Load your own tcl files and namespaces
* Implement your custom tcl/tk windows

### spd file
This file defines the data tree shown in the left side of the GiD window.

This file must follow the [CustomLib rules](http://www.gidhome.com/documents/customizationmanual/PROBLEMTYPE+SYSTEM/Data+tree+fields). (The web documentation is hard to follow. It's easier to read the 4.3 section of the [PDF version](https://web.cimne.upc.edu/users/fjgarate/downloads/GiD_13_Customization_Manual.pdf#page=12))
