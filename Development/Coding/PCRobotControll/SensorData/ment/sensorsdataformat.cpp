#include "sensorsdataformat.h"

SensorsDataFormat::SensorsDataFormat()
{
}


SensorsProperties::SensorsProperties()
{
    this->Accelerometer_RealSensor=false;
    this->Ambientlightsensor_RealSensor=false;
    this->Compass_sensor_RealSensor=false;
    this->Gyroscope_RealSensor=false;
    this->Lineracceleration_VirtualSensor=false;
    this->Magnetometer_RealSensor=false;
    this->Orientationsensor_RealSensor=false;
    this->Proximitysensor_RealSensor=false;
    this->Rotationsensor_RealSensor=false;
    this->Rotationvector_VirtualSensor=false;
    this->Tapsensor_RealSensor=false;
}



/////////////////////////////////////////////////////

AccelerometerSensorFormat::AccelerometerSensorFormat()
{
    x=0;
    y=0;
    z=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

AccelerometerSensorFormat::~AccelerometerSensorFormat()
{
}

/////////////////////////////////////////////////////

MagnetometerSensorFormat::MagnetometerSensorFormat()
{
    x=0;
    y=0;
    z=0;
    CalibrationLevel=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

MagnetometerSensorFormat::~MagnetometerSensorFormat()
{
}

/////////////////////////////////////////////////////

CompassSensorFormat::CompassSensorFormat()
{
    azimuth=0;
    CalibrationLevel=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

CompassSensorFormat::~CompassSensorFormat()
{
}

/////////////////////////////////////////////////////

OrientationSensorFormat::OrientationSensorFormat()
{
    orientation=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

OrientationSensorFormat::~OrientationSensorFormat()
{
}

/////////////////////////////////////////////////////

ProximitySensorFormat::ProximitySensorFormat()
{
    IsClose=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

ProximitySensorFormat::~ProximitySensorFormat()
{
}

/////////////////////////////////////////////////////

AmbientLightSensorFormat::AmbientLightSensorFormat()
{
    LightLevel=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

AmbientLightSensorFormat::~AmbientLightSensorFormat()
{
}

/////////////////////////////////////////////////////


LinearAccelerationSensorFormat::LinearAccelerationSensorFormat()
{
    LinearAcceleration=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

LinearAccelerationSensorFormat::~LinearAccelerationSensorFormat()
{
}

/////////////////////////////////////////////////////


RotationVectorSensorFormat::RotationVectorSensorFormat()
{
    Degree_RotationAroundAxisX=0;
    Radian_RotationAroundAxisX=0;
    Degree_RotationAroundAxisY=0;
    Radian_RotationAroundAxisY=0;
    Degree_RotationAroundAxisZ=0;
    Radian_RotationAroundAxisZ=0;
    //VerticalRotation_radian=0;
    //HorisontalRotation_radian=0;
    //VerticalRotation_degree=0;
    //HorisontalRotation_degree=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

RotationVectorSensorFormat::~RotationVectorSensorFormat()
{
}

/////////////////////////////////////////////////////


SpeedSensorFormat::SpeedSensorFormat()
{
    Vx=0;
    Vy=0;
    Vz=0;
    Speed=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

SpeedSensorFormat::~SpeedSensorFormat()
{
}

/////////////////////////////////////////////////////

// Ezeket még nem sikerült működésrebírni:----------------------------------------------------

GyroscopeSensorFormat::GyroscopeSensorFormat()
{
    x=0;
    y=0;
    z=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

GyroscopeSensorFormat::~GyroscopeSensorFormat()
{
}

/////////////////////////////////////////////////////

RotationSensorFormat::RotationSensorFormat()
{
    x=0;
    y=0;
    z=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

RotationSensorFormat::~RotationSensorFormat()
{
}

/////////////////////////////////////////////////////

TapSensorFormat::TapSensorFormat()
{
    tap_direction=0;
    IsActive=false;// Alapból nem igaz, csak ha már bizonyított
    IsVaildData=false;
}

TapSensorFormat::~TapSensorFormat()
{
}

/////////////////////////////////////////////////////




ConstantGravityVector::ConstantGravityVector()
{
    /*
    x=0;
    y=0;
    z=0;
    xRotation=0;
    yRotation=0;
    zRotation=0;
    */
}

ConstantGravityVector::~ConstantGravityVector()
{
}

