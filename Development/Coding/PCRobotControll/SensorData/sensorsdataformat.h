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


class vect3D
{
public:
    vect3D();
    vect3D(qreal x,qreal y, qreal z);
    ~vect3D();

public:
   qreal  x;
   qreal  y;
   qreal  z;
};

class AccelerometerSensorFormat
{

public:
    AccelerometerSensorFormat();
    ~AccelerometerSensorFormat();

public:
   qreal  x;
   qreal  y;
   qreal  z;
   qreal  Lineracceleration;
   bool IsActive;
   bool IsVaildData;
};


class MagnetometerSensorFormat
{

public:
    MagnetometerSensorFormat();
    ~MagnetometerSensorFormat();

public:
   qreal  x;
   qreal  y;
   qreal  z;
   qreal  CalibrationLevel;
   bool IsActive;
   bool IsVaildData;
};


class CompassSensorFormat
{

public:
    CompassSensorFormat();
    ~CompassSensorFormat();

public:
   qreal  azimuth;
   qreal  CalibrationLevel;
   bool IsActive;
   bool IsVaildData;
};


class OrientationSensorFormat
{

public:
    OrientationSensorFormat();
    ~OrientationSensorFormat();

public:
   qreal  orientation;
   bool IsActive;
   bool IsVaildData;
};


class ProximitySensorFormat
{

public:
    ProximitySensorFormat();
    ~ProximitySensorFormat();

public:
   bool IsClose;// A SensorFilters.h -ban is át kell írni qreal-ról bool-ra
   bool IsActive;
   bool IsVaildData;
};


class AmbientLightSensorFormat
{

public:
    AmbientLightSensorFormat();
    ~AmbientLightSensorFormat();

public:
   qreal  LightLevel;// A SensorFilters.h -ban is át kell írni qreal-ról bool-ra
   bool IsActive;
   bool IsVaildData;
};

class LinearAccelerationSensorFormat
{

public:
    LinearAccelerationSensorFormat();
    ~LinearAccelerationSensorFormat();

public:
   qreal  LinearAcceleration;
   bool IsActive;
   bool IsVaildData;
};

class RotationVectorSensorFormat
{

public:
    RotationVectorSensorFormat();
    ~RotationVectorSensorFormat();

public:
   qreal Degree_RotationAroundAxisX;
   qreal Radian_RotationAroundAxisX;
   qreal Degree_RotationAroundAxisY;
   qreal Radian_RotationAroundAxisY;
   qreal Degree_RotationAroundAxisZ;
   qreal Radian_RotationAroundAxisZ;
   //qreal VerticalRotation_radian;
   //qreal HorisontalRotation_radian;
   //qreal VerticalRotation_degree;
   //qreal HorisontalRotation_degree;
   bool IsActive;
   bool IsVaildData;
};


class SpeedSensorFormat
{

public:
    SpeedSensorFormat();
    ~SpeedSensorFormat();

public:
   qreal Vx;
   qreal Vy;
   qreal Vz;
   qreal Speed;
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
   qreal  x;
   qreal  y;
   qreal  z;
   bool IsActive;
   bool IsVaildData;
};


class RotationSensorFormat
{

public:
    RotationSensorFormat();
    ~RotationSensorFormat();

public:
   qreal  x;
   qreal  y;
   qreal  z;
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
    OrientationSensorFormat Orientationsensor_RealSensor;
    AmbientLightSensorFormat Ambientlightsensor_RealSensor;
    ProximitySensorFormat Proximitysensor_RealSensor;

    GyroscopeSensorFormat Gyroscope_RealSensor;
    LinearAccelerationSensorFormat Lineracceleration_VirtualSensor;// Saját virtuális szenzor
    RotationVectorSensorFormat Rotationvector_VirtualSensor;// Saját virtuális szenzor


};


#endif // SENSORSDATAFORMAT_H
