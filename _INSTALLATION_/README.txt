Guide to install this Project

1.Run the mingw-get-setup excecutable as an admin (important!)
2.Click next untill you installed the installer (inception).
3.When given the option to choose your packages, go to the basics tab on the left and right click on all available packages and select them.
4.When all basic packages are selected (around 6 a 7 packages), hit the options button on the top left and hit apply.
5.Press continue to install all packages.

6.Install an IDE of your choice (This tutorial is written for CLion) https://www.jetbrains.com/clion/
7.Follow all the steps in the installer, and open the project folder with CLion
8.When the project is opened, hit file>Settings> Build, Excecution, Deployment>Toolchains.
9.Under Environments, choose MinGW. If it doesn't autodetect it, select C:\MinGW
10.It will detect the nessecary CMake files, and then hit Apply.

11.Select the 4 folders in the SDL2 folder and copy them over to C:\MinGW to merge their contents.
12.Select the 3 folders in the SDL2_mixer folder and copy them over to C:\MinGW to merge their contents.
13.Reload the CMake file in CLion, and then build the project.
14.If everything went right, it should built succesfully, and you'll be able to run the project!
If not, don't bother Corne & Maarten! ;)