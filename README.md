# Description
This repo is used to wrap other logger libraries into a very simple interface. With a simple interface in mind, the customizability of each logger has been limited to keep the simple design.

# How to use this project
Once linked appropriately to an existing project, the following are the ways to use the logger

## CMake build from source
The 3rd Party Libraries are not build directly in this repository. Using the `<-p|--cmake-prefix>` is the intended method of linking to the 3rd party libraries. See [CommonBuild](https://github.com/BakedGoods21/CommonBuild/tree/master) to easily build 3rd party libraries. This repo can be used in tandem with this project.
```
configure.sh <-c|--config> <-e|--external-dir> <-d|--debug>
build.sh <-j|--parallel>
install.sh
```
- `<-v|--verbose>`: Set the verbose flag for expanded output
- `<-c|--config>`: Can be `Debug` or `Release`
- `<-d|--debug>`: Short-hand for setting the configuration (`-c|--config`) to 'Debug'
- `<-p|--cmake-prefix>`: Specify CMake's CMAKE_PREFIX_PATH (semi-colon separated) variable to specify the external directories where the 3rd party libraries are installed
- `<-j|--parallel>`: Specify number of threads for build to use


## Functionality
Once linked correctly, SSLogWrapper has been built to be used right away without having to initialize any variables or sturctures. The functions below can be called right from the beginning (see "Example/main.cpp"). All trace and debug calls will print file, function, and line number of the calling unit.
```
// Recommended Way of Use
int main()
{
    SSLogger::PTRACE("This is the recommended TRACE Logging");
    SSLogger::PTRACE(); // Will print the file, function, and line number with no message
    SSLogger::PDEBUG("This is the recommended DEBUG Logging"); // Note this will not print unless "SSLogger::setLevel(SSLogger::logLevel::pDEBUG);" has been set
    SSLogger::PINFO("This is the recommended INFO Logging");
    SSLogger::PWARN("This is the recommended WARNING Logging");
    SSLogger::PERROR("This is the recommended ERROR Logging");
    SSLogger::PFATAL("This is the recommended FATAL Logging");

    return EXIT_SUCCESS;
}
```

### TRACE and DEBUG are Unique
All of the functions print a log to the screen with the various levels. The level of printing can be adjusted using the `SSLogger::setLevel(SSLogger::logLevel::<log_level>)` function.

The trace and debug log functions have additional functionality making them a bit unique. Debug will not print unless debug has been set by `setLevel` function. Trace is unique as it can be called without a message making it simply print the file, function, and line number of the calling object. 

### Sending logs to a file
In order to send the output to a log file, simply call `setLogFile(<filename>)` and all logs will start logging to the file specified. 

### Alternative log functions
```
SSLogger::PLOG()->info("Alternative log method");

(*SSLogger::PLOG())(SSLogger::logLevel::pINFO) << "Set the log level for THIS log output";
(*SSLogger::PLOG()) << "Yet another way to do it...\n"; // The log level in this case will use the default, what's been set by "setLevel", or the previous manually set log output above this line
```

