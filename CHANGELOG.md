*(All notable changes to this project will be documented in this file.)*


# **CHANGELOG**


## [v0.1.01-nightly] - 2019-03-05 :

### GENERAL :
 - New philosophy : tensor based library.
 - Updated the project website.
 - Updated the documentation.
 - Added a wiki on github.
 - Updated the README.md.

### CORE :
 - Fixed a bug with the error system.
 - Deleted String class, use std::string now.
 - Deleted File class, use std::fstream now.
 - Deleted Thread class, use std::thread.
 - Changed the log system to a C++ one.

### MLP : 
 - Deleted the module (replaced by the NeuralNet module).
 
### UTILITY :
 - Added a n-tensor system.
 - Added a tensor shape system.
 - Added an activator function struct (normalized).
 - Added an approximation function of derivative.
 - Added a gradient struct (old and actual gradient).
 - Added support for the Sigmoid activation function.
 
### NEURALNET :
 - Added a new module : NeuralNet. It will store all neural networks (as a toolkit).
 - Added a fully connect layer class.
 - Added a pure virtual layer class.
 - Added a pure virtual optimizer class (for gradient).
 - Added a pure virtual cost class (for cost function).
 - Added support to the Fully Connect Layer.
 - Added support to the Mean Squared Error cost function.
 - Added support to the Stochastic Gradient Descent method.
 - Added a Random Initializer.
 - Added an Uniform Initializer.
 - Added a Zero Initializer.
 - Added a convolutional layer class (3D and 2D).
 

## [v0.0.53-release] - 2019-02-26 :

### CORE :
 - Fixed log system.

### MLP :
 - Added new functions.


## [v0.0.52-release] - 2018-10-30 :

### CORE :
 - Added a new error type : ABORT.
 - Fixed the Error system.
 - Added flush of the log stream in the log system.
 - Added a new DEBUG option.


## [v0.0.51-release] - 2018-08-22 :

### GENERAL :
 - Fixed the Windows x86 version.

### CORE :
 - Fixed and added new features to the Log and Error system.



## [v0.0.5-release] - 2018-08-19 :

### GENERAL :
 - Github release.

### CORE :
 - Fixed the log system.
 - No more memory leak.
 
### MLP :
 - Added more options in the constructor.
