# Cmas2d problemtype for GiD

## First steps
### Install GiD
* This repository is a basic example for GiD problemtype developers. Download GiD from the website [Download](http://www.gidhome.com/download/)
* You can get up to 3 free [1 month GiD license](http://www.gidhome.com/purchase/passwords/?Licencetype=1&Periodtime=1)

### Test me!
* Create a folder called 'cmas2d_customlib.gid'
* Clone this repository inside
```
mkdir cmas2d_customlib.gid
cd cmas2d_customlib.gid
git clone https://github.com/jginternational/cmas2d-customlib.git
```
* Create a link to the project inside the GiD problemtype directory
    * Windows: A basic shortchut is enough
* Open GiD and go to Data -> Problemtype -> cmas2d_customlib

## Create your problemtype
* Fork this repository
* Follow the Basic rules
* Read the [documentation](http://www.gidhome.com/documents/customizationmanual/PROBLEMTYPE%20SYSTEM)

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

### bat files
This is the launch script that GiD will use to run your executable.
If you want your problemtype to run on windows and unix systems, you'll need a bat file for each system.
