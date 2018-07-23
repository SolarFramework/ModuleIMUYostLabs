# ModuleIMUYostLabs
This module contains a set of components that implements the SolAR IMU interface for the Yost Labs 3-SpaceTM Micro USB IMU [https://yostlabs.com/product/3-space-micro-usb/]

## IMUYostLabs
Implementation of an IMU using non-blocking methods that will immediately return data when called. This component should only be used when data is needed occasionally, as two consecutive calls in a short time window will return the same data.

## IMUYostLabsStream
Implementation of an IMU using blocking methods that will wait until new data is available. This component can be used when data is needed at high frequency, such as data logging.

## License
This module is licensed under the Yost Labs 3-Space™ Open Source Licensing - see the LICENSE file for details.