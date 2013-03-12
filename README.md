gpu-blob-tracking
=================

Implementing video processing for blob tracking on the GPU.	

##Build Instructions
This page describes how to compile the gpuTracker project

##Linux
###Compiling
Run the folowing command to check out the sourcecode into a directory called gputracker:

svn checkout http://gputracker.googlecode.com/svn/trunk/ gputracker-read-only
To compile the project run make in the gputracker directory you checked out:

cd gputracker
make
You should now be able to run the program by typing './gpuTracker'

./gpuTracker
###Depenencies
The program links against GLUT, glew and OpenCV, so you have to install the development packages for these libraries on your distro or install them yourself (Currently only tested against standard packages in Ubuntu 8.04).

##OSX
###Compiling
You can setup the google code svn repository in XCode under SCM(source controll management). To check it out from the command line just type:

svn checkout http://gputracker.googlecode.com/svn/trunk/ gputracker-read-only
In the directory you checked out, there is a folder called osx. Inside the osx directory the is a XCode project that should be ready to compile and run the application. The application bundle contains all the files necessary to run the app and can be copied to other computers running OSX.

###Depenencies
Currently OpenCV is available for Mac as a private framework. The framework is uploaded to svn as well and will be included in any builds automatically.
