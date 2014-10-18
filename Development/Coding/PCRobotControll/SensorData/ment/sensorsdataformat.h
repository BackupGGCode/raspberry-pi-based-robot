#ifndef SENSORSDATAFORMAT_H
#define SENSORSDATAFORMAT_H

#include <qglobal.h>

// Ez az osztály azért fontos, mert a többi osztály számára ez minden, amit a SensorHandler ad. Semmi mást nemlát(hat)nak belőle.(!)


typedef struct SensorsProperties// Ez tárolja, hogy mej szenzorok indúlhatnak el és melyek nem.
{
    SensorsProperties();
    ~SensorsProperties();

    bool Accelerometer_RealSensor;
    bool Lineracceleration_VirtualSensor;// Saját virtuális szenzor
    bool Rotationvector_VirtualSensor;// Saját virtuális szenzor
    bool Tapsensor_RealSensor;// Még, nem tudom mire való
    bool Magnetometer_RealSensor;
    bool Compass_sensor_RealSensor;
    bool Orientationsensor_RealSensor;
    bool Ambientlightsensor_RealSensor;
    bool Proximitysensor_RealSensor;
    bool Gyroscope_RealSensor;
    bool Rotationsensor_RealSensor;// Ez még nem működik necessitasban
    bool SpeedSensor_VirtualSensor;
}SensorsProperties;



class AccelerometerSensorFormat
{

public:
    AccelerometerSensorFormat();
    ~AccelerometerSensorFormat();

public:
   double  x;
   double  y;
   double  z;
   double  Lineracceleration;
   bool IsActive;
   bool IsVaildData;
};


class MagnetometerSensorFormat
{

public:
    MagnetometerSensorFormat();
    ~MagnetometerSensorFormat();

public:
   double  x;
   double  y;
   double  z;
   double  CalibrationLevel;
   bool IsActive;
   bool IsVaildData;
};


class CompassSensorFormat
{

public:
    CompassSensorFormat();
    ~CompassSensorFormat();

public:
   double  azimuth;
   double  CalibrationLevel;
   bool IsActive;
   bool IsVaildData;
};


class OrientationSensorFormat
{

public:
    OrientationSensorFormat();
    ~OrientationSensorFormat();

public:
   double  orientation;
   bool IsActive;
   bool IsVaildData;
};


class ProximitySensorFormat
{

public:
    ProximitySensorFormat();
    ~ProximitySensorFormat();

public:
   bool IsClose;// A SensorFilters.h -ban is át kell írni double-ról bool-ra
   bool IsActive;
   bool IsVaildData;
};


class AmbientLightSensorFormat
{

public:
    AmbientLightSensorFormat();
    ~AmbientLightSensorFormat();

public:
   double  LightLevel;// A SensorFilters.h -ban is át kell írni double-ról bool-ra
   bool IsActive;
   bool IsVaildData;
};

class LinearAccelerationSensorFormat
{

public:
    LinearAccelerationSensorFormat();
    ~LinearAccelerationSensorFormat();

public:
   double  LinearAcceleration;
   bool IsActive;
   bool IsVaildData;
};

class RotationVectorSensorFormat
{

public:
    RotationVectorSensorFormat();
    ~RotationVectorSensorFormat();

public:
   double Degree_RotationAroundAxisX;
   double Radian_RotationAroundAxisX;
   double Degree_RotationAroundAxisY;
   double Radian_RotationAroundAxisY;
   double Degree_RotationAroundAxisZ;
   double Radian_RotationAroundAxisZ;
   //double VerticalRotation_radian;
   //double HorisontalRotation_radian;
   //double VerticalRotation_degree;
   //double HorisontalRotation_degree;
   bool IsActive;
   bool IsVaildData;
};


class SpeedSensorFormat
{

public:
    SpeedSensorFormat();
    ~SpeedSensorFormat();

public:
   double Vx;
   double Vy;
   double Vz;
   double Speed;
   bool IsActive;
   bool IsVaildData;
};
// Ezeket még nem sikerült működésre bírni:

class GyroscopeSensorFormat
{

public:
    GyroscopeSensorFormat();
    ~GyroscopeSensorFormat();

public:
   double  x;
   double  y;
   double  z;
   bool IsActive;
   bool IsVaildData;
};


class RotationSensorFormat
{

public:
    RotationSensorFormat();
    ~RotationSensorFormat();

public:
   double  x;
   double  y;
   double  z;
   bool IsActive;
   bool IsVaildData;
};


class TapSensorFormat
{

public:
    TapSensorFormat();
    ~TapSensorFormat();

public:
   double  tap_direction;
   bool IsActive;
   bool IsVaildData;
};


class SensorsDataFormat
{
public:
    SensorsDataFormat();

public:
    AccelerometerSensorFormat Accelerometer_RealSensor;
    MagnetometerSensorFormat Magnetometer_RealSensor;
    CompassSensorFormat Compass_sensor_RealSensor;
    OrientationSensorFormat Orientationsensor_RealSensor;
    AmbientLightSensorFormat Ambientlightsensor_RealSensor;
    ProximitySensorFormat Proximitysensor_RealSensor;
    LinearAccelerationSensorFormat Lineracceleration_VirtualSensor;// Saját virtuális szenzor
    RotationVectorSensorFormat Rotationvector_VirtualSensor;// Saját virtuális szenzor
    SpeedSensorFormat SpeedSensor_VirtualSensor;

    // Ezek még nem sikerült működésre bírni:

    TapSensorFormat Tapsensor_RealSensor;// Még, nem tudom mire való
    GyroscopeSensorFormat Gyroscope_RealSensor;
    RotationSensorFormat Rotationsensor_RealSensor;// Ez még nem működik necessitasban
};



typedef struct ConstantGravityVector// Ez tárolja, hogy mej szenzorok indúlhatnak el és melyek nem.
{
    ConstantGravityVector();
    ~ConstantGravityVector();

    AccelerometerSensorFormat AvarageGravityAcceleration;
    MagnetometerSensorFormat MagneticStateAtCalibration;
    RotationVectorSensorFormat RotationStateAtCalibration;

    /*
    double x;
    double y;
    double z;
    double xRotation;
    double yRotation;
    double zRotation;
    */

}ConstantGravityVector;



#endif // SENSORSDATAFORMAT_H
