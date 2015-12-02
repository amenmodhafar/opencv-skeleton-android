# opencv-skeleton-android

This repository gives some example code to run native OpenCV code on Android. Using the Android camera interface will typically give much better frame rates than the OpenCV samples which uses a different interface.

Since native code is used, it is necessary to download the Android NDK as well as the OpenCV SDK. In order to run this project, the variable `OPENCV_SDK` that is used in `Android.mk` needs to be defined. This can be done in Eclipse by going to Preferences > C/C++ > Build > Environment. Then add a new variable with the name `OPENCV_SDK`. The value should be the full path to the OpenCV SDK, e.g.:
```sh
/Users/arthurdent/Android/OpenCV-2.X.X-android-sdk
```

The function `processFrame(cv::Mat&)` in `jni/native.cpp` can be used for custom image processing using the OpenCV functions. As an example, Canny edge detection is performed by default.
