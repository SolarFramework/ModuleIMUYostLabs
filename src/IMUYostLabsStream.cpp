/**
 * @copyright Copyright 1998-2018, Yost Labs Corporation
 *
 * The Yost 3-Space API is released under the Yost 3-Space Open Source License, which allows for both
 * non-commercial use and commercial use with certain restrictions.
 *
 * For Non-Commercial Use, your use of Covered Works is governed by the GNU GPL v.3, subject to the Yost 3-Space Open
 * Source Licensing Overview and Definitions.
 *
 * For Commercial Use, a Yost Commercial/Redistribution License is required, pursuant to the Yost 3-Space Open Source
 * Licensing Overview and Definitions. Commercial Use, for the purposes of this License, means the use, reproduction
 * and/or Distribution, either directly or indirectly, of the Covered Works or any portion thereof, or a Compilation,
 * Improvement, or Modification, for Pecuniary Gain. A Yost Commercial/Redistribution License may or may not require
 * payment, depending upon the intended use.
 *
 * Full details of the Yost 3-Space Open Source License can be found in LICENSE
 * License also available online at https://yostlabs.com/support/open-source-license/
 */

#include "xpcf/component/ComponentFactory.h"
#include "IMUYostLabsStream.h"
#include "core/Log.h"

namespace xpcf  = org::bcom::xpcf;
XPCF_DEFINE_FACTORY_CREATE_INSTANCE(SolAR::MODULES::IMUYOSTLABS::IMUYostLabsStream);

namespace SolAR {
namespace MODULES {
namespace IMUYOSTLABS {

    IMUYostLabsStream::IMUYostLabsStream():ComponentBase(xpcf::toUUID<IMUYostLabsStream>())
    {
        addInterface<api::input::devices::IIMU>(this);
    }

    FrameworkReturnCode IMUYostLabsStream::start()
    {
        if (tss_getComPorts(&comport, 1, 0, TSS_FIND_ALL_KNOWN^TSS_FIND_DNG)) {
            device = tss_createTSDeviceStr(comport.com_port, TSS_TIMESTAMP_SENSOR);
            if (device == TSS_NO_DEVICE_ID) {
                LOG_ERROR ("IMUYostLabsStream::start: Failed to create a sensor on {}", comport.com_port)
                return FrameworkReturnCode::_ERROR_;
            }
        }
        else {
            LOG_ERROR ("IMUYostLabsStream::start: No sensor found")
            return FrameworkReturnCode::_ERROR_;
        }

        tss_error = tss_setAxisDirections(device, TSS_XYZ, NULL);
        if(tss_error){
            LOG_ERROR("IMUYostLabsStream::start: Failed to set axis directions");
            return FrameworkReturnCode::_ERROR_;
        }

        tss_error = tss_setFilterMode(device, TSS_FILTER_IMU, NULL);
        if(tss_error){
            LOG_ERROR("IMUYostLabsStream::start: Failed to set filter mode");
            return FrameworkReturnCode::_ERROR_;
        }

        tss_error = tss_setStreamingTiming(device, 0, TSS_INFINITE_DURATION, 0, NULL);
        if(tss_error){
            LOG_ERROR("IMUYostLabsStream::start: Failed to set streaming timing");
            return FrameworkReturnCode::_ERROR_;
        }

        TSS_Stream_Command stream_slots[8] = { TSS_GET_ALL_CORRECTED_COMPONENT_SENSOR_DATA, TSS_NULL,
                                                TSS_NULL, TSS_NULL,TSS_NULL,TSS_NULL,TSS_NULL,TSS_NULL};

        tss_error = tss_setStreamingSlots(device, stream_slots, NULL);
        if(tss_error){
            LOG_ERROR("IMUYostLabsStream::start: Failed to set streaming slots");
            return FrameworkReturnCode::_ERROR_;
        }

        tss_error = tss_startStreaming(device,NULL);
        if(tss_error){
            LOG_ERROR("IMUYostLabsStream::start: Failed to start streaming");
            return FrameworkReturnCode::_ERROR_;
        }

        return FrameworkReturnCode::_SUCCESS;
    }

    FrameworkReturnCode IMUYostLabsStream::getGyroscopeData(Vector3f & gyroData)
    {
        readStreamData();

        if(tss_error){
            LOG_ERROR("IMUYostLabsStream::getGyroscopeData: Error while trying to read sensor data (API error code: {})", TSS_Error_String[tss_error])
            return FrameworkReturnCode::_ERROR_;
        }

        gyroData = Vector3f(packet.gyro);

        return FrameworkReturnCode::_SUCCESS;
    }

    FrameworkReturnCode IMUYostLabsStream::getAccelerometerData(Vector3f & accelData)
    {
        readStreamData();

        if(tss_error){
            LOG_ERROR("IMUYostLabsStream::getAccelerometerData: Error while trying to read sensor data (API error code: {})", TSS_Error_String[tss_error])
            return FrameworkReturnCode::_ERROR_;
        }

        accelData = Vector3f(packet.accel);

        accelData *= gravity; //Convert values from units of g to metre per second squared

        return FrameworkReturnCode::_SUCCESS;
    }

    FrameworkReturnCode IMUYostLabsStream::getMagnetometerData(Vector3f & magData)
    {
        readStreamData();

        if(tss_error){
            LOG_ERROR("IMUYostLabsStream::getMagnetometerData: Error while trying to read sensor data (API error code: {})", TSS_Error_String[tss_error])
            return FrameworkReturnCode::_ERROR_;
        }

        magData = Vector3f(packet.mag);

        return FrameworkReturnCode::_SUCCESS;
    }

    FrameworkReturnCode IMUYostLabsStream::getAllSensorsData(Vector3f & gyroData, Vector3f & accelData, Vector3f & magData)
    {
        readStreamData();

        if(tss_error){
            LOG_ERROR("IMUYostLabsStream::getAllSensorsData: Error while trying to read sensor data (API error code: {})", TSS_Error_String[tss_error])
            return FrameworkReturnCode::_ERROR_;
        }

        gyroData = Vector3f(packet.gyro);
        accelData = Vector3f(packet.accel);
        magData = Vector3f(packet.mag);

        accelData *= gravity; //Convert values from units of g to metre per second squared

        return FrameworkReturnCode::_SUCCESS;
    }

    bool IMUYostLabsStream::isGyroscopeAvailable()
    {
        return true;
    }

    bool IMUYostLabsStream::isAccelerometerAvailable()
    {
        return true;
    }

    bool IMUYostLabsStream::isMagnetometerAvailable()
    {
        return true;
    }

    void IMUYostLabsStream::readStreamData()
    {
        tss_error = tss_getLatestStreamData(device, (char*)&packet, sizeof(packet), 1000, NULL);
    }

}
}
}
