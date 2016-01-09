Corona renderer plugin for Maya

To run and compile you need the repository mayaToCommon. At the moment the repository should be called mayaToCorona and should be at the same level as mayaToCommon:

    SomeDir
        mayaToCommon
        mayaToCorona

I used Boost 1.55. There is a VisualStudio props file which contains some macros with the API/Boost locations, these should be set appropriatly.
At the moment you will need a working OSL distribution what means you have to compile all depedencies by yourself. Have a look at the VS props file to see which deps are needed.

To run the debug plugin from maya, maya needs some env variables:<br>

MAYA_MODULE_PATH should point to the module path of mayaToCorona. e.g.<br>
MAYA_MODULE_PATH=c:/SomeDir/mayaToCorona/mtco_devmodule<br>

The maya script path should contain the common scripts:

MAYA_SCRIPT_PATH=c:/SomeDir/mayaToCommon/python<br>

This can be done via Maya.env file or with a batch script (my preferred way).<br>
Then it should work. This is only necessary for the debug version. In the final deployment the common scripts will be copied to the module script path.
