##########################################################################################################################
##########################################################################################################################
Author : Pranjal Kushwaha
Email : pranjalkushwaha@cse.iitb.ac.in
Course : CS293 (Project)
##########################################################################################################################
##########################################################################################################################

The executables in this project are generated on Ubuntu 20.04 LTS.

To view the animation run:
$ cd Executables
$ chmod +x queue
$ ./queue

To recompile the files, a Makefile has been included, run :
$ make 
from the base directory.

Also the .vscode folder has been included with the required settings for use with VSC.

There are three executables in this project : 
1. queue : Uses OpenGL. Runs the main animation and utilises queue data structure and 8 threads in total for better fps.
2. slow : Uses OpenGL. Single threaded. Included for comparison.
3. click : Uses the default X11 linux window manager. It is a click-to-zoom type interface.

Note : The opengl executables also depend on the glut library for window drawing. (http://freeglut.sourceforge.net/)