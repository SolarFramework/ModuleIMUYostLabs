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

#ifndef IMUYOSTLABS_H
#define IMUYOSTLABS_H

#include <vector>
#include "xpcf/component/ComponentBase.h"
#include "yei_threespace_api.h"

#include "api/input/devices/IIMU.h"

#include "IMUYostLabsAPI.h"

namespace SolAR {
using namespace datastructure;
namespace MODULES {
namespace IMUYOSTLABS {

class IMUYOSTLABS_EXPORT_API IMUYostLabs : public org::bcom::xpcf::ComponentBase,
        public api::input::devices::IIMU {
public:
    IMUYostLabs();

    ~IMUYostLabs() = default;

    virtual FrameworkReturnCode start() override;

    virtual FrameworkReturnCode getGyroscopeData(Vector3f & gyroData) override;
    virtual FrameworkReturnCode getAccelerometerData(Vector3f & accelData) override;
    virtual FrameworkReturnCode getMagnetometerData(Vector3f & magData) override;

    virtual FrameworkReturnCode getAllSensorsData(Vector3f & gyroData, Vector3f & accelData, Vector3f & magData) override;

    virtual bool isGyroscopeAvailable() override;
    virtual bool isAccelerometerAvailable() override;
    virtual bool isMagnetometerAvailable() override;

    void unloadComponent () override final;

 private:
    TSS_Device_Id  device;
    TSS_Error tss_error;
    TSS_ComPort comport;

    float gravity = 9.80665f;

};

}
}
}

#endif // IMUYOSTLABS_H
