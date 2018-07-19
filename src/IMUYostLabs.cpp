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
#include "IMUYostLabs.h"
#include "core/Log.h"

namespace xpcf  = org::bcom::xpcf;
XPCF_DEFINE_FACTORY_CREATE_INSTANCE(SolAR::MODULES::IMUYOSTLABS::IMUYostLabs);

namespace SolAR {
namespace MODULES {
namespace IMUYOSTLABS {

    IMUYostLabs::IMUYostLabs():ComponentBase(xpcf::toUUID<IMUYostLabs>())
    {
        addInterface<api::input::devices::IIMU>(this);
    }

    FrameworkReturnCode IMUYostLabs::start()
    {
        if (tss_getComPorts(&comport, 1, 0, TSS_FIND_ALL_KNOWN^TSS_FIND_DNG)) {
            device = tss_createTSDeviceStr(comport.com_port, TSS_TIMESTAMP_SENSOR);
            if (device == TSS_NO_DEVICE_ID) {
                LOG_ERROR ("IMUYostLabs::start: Failed to create a sensor on {}", comport.com_port)
                return FrameworkReturnCode::_ERROR_;
            }
        }
        else {
            LOG_ERROR ("IMUYostLabs::start: No sensor found")
            return FrameworkReturnCode::_ERROR_;
        }

        tss_error = tss_setAxisDirections(device, TSS_XYZ, NULL);
        if(tss_error){
            LOG_ERROR("IMUYostLabs::start: Failed to set axis directions");
            return FrameworkReturnCode::_ERROR_;
        }

        tss_error = tss_setFilterMode(device, TSS_FILTER_IMU, NULL);
        if(tss_error){
            LOG_ERROR("IMUYostLabs::start: Failed to set filter mode");
            return FrameworkReturnCode::_ERROR_;
        }

        return FrameworkReturnCode::_SUCCESS;
    }

    FrameworkReturnCode IMUYostLabs::getGyroscopeData(Vector3f & gyroData)
    {
        tss_error = tss_getCorrectedGyroRate(device, &gyroData[0], NULL);
        if (tss_error) {
            LOG_ERROR ("IMUYostLabs::getGyroscopeData: Error while trying to read sensor data (API error code: {})", TSS_Error_String[tss_error])
            return FrameworkReturnCode::_ERROR_;
        }

        return FrameworkReturnCode::_SUCCESS;
    }

    FrameworkReturnCode IMUYostLabs::getAccelerometerData(Vector3f & accelData)
    {
        tss_error = tss_getCorrectedAccelerometerVector(device, &accelData[0], NULL);
        if (tss_error) {
            LOG_ERROR ("IMUYostLabs::getAccelerometerData: Error while trying to read sensor data (API error code: {})", TSS_Error_String[tss_error])
            return FrameworkReturnCode::_ERROR_;
        }

        accelData *= gravity; //Convert values from units of g to metre per second squared

        return FrameworkReturnCode::_SUCCESS;
    }

    FrameworkReturnCode IMUYostLabs::getMagnetometerData(Vector3f & magData)
    {
        tss_error = tss_getCorrectedCompassVector(device, &magData[0], NULL);
        if (tss_error) {
            LOG_ERROR ("IMUYostLabs::getMagnetometerData: Error while trying to read sensor data (API error code: {})", TSS_Error_String[tss_error])
            return FrameworkReturnCode::_ERROR_;
        }

        return FrameworkReturnCode::_SUCCESS;
    }

    FrameworkReturnCode IMUYostLabs::getAllSensorsData(Vector3f & gyroData, Vector3f & accelData, Vector3f & magData)
    {
        tss_error = tss_getAllCorrectedComponentSensorData(device, &gyroData[0], &accelData[0], &magData[0], NULL);
        if (tss_error) {
            LOG_ERROR ("IMUYostLabs::getAllSensorsData: Error while trying to read sensor data (API error code: {})", TSS_Error_String[tss_error])
            return FrameworkReturnCode::_ERROR_;
        }

        accelData *= gravity; //Convert values from units of g to metre per second squared

        return FrameworkReturnCode::_SUCCESS;
    }

    bool IMUYostLabs::isGyroscopeAvailable()
    {
        return true;
    }

    bool IMUYostLabs::isAccelerometerAvailable()
    {
        return true;
    }

    bool IMUYostLabs::isMagnetometerAvailable()
    {
        return true;
    }

}
}
}
