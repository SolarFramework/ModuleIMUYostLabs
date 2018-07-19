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

#include <iostream>

#include "xpcf/module/ModuleFactory.h"

#include "IMUYostLabs.h"
#include "IMUYostLabsStream.h"

namespace xpcf=org::bcom::xpcf;

XPCF_DECLARE_MODULE("0241ec6e-10d0-11e8-b642-0ed5f89f718b", "ModuleIMUYostLabs")


extern "C" XPCF_MODULEHOOKS_API xpcf::XPCFErrorCode XPCF_getComponent(const boost::uuids::uuid& componentUUID,SRef<xpcf::IComponentIntrospect>& interfaceRef)
{
     xpcf::XPCFErrorCode errCode = xpcf::XPCFErrorCode::_FAIL;
     errCode = xpcf::tryCreateComponent<SolAR::MODULES::IMUYOSTLABS::IMUYostLabs>(componentUUID,interfaceRef);
     if (errCode != xpcf::XPCFErrorCode::_SUCCESS)
     {
         errCode = xpcf::tryCreateComponent<SolAR::MODULES::IMUYOSTLABS::IMUYostLabsStream>(componentUUID,interfaceRef);
     }
    return errCode;
}

XPCF_BEGIN_COMPONENTS_DECLARATION
XPCF_ADD_COMPONENT(SolAR::MODULES::IMUYOSTLABS::IMUYostLabs)
XPCF_ADD_COMPONENT(SolAR::MODULES::IMUYOSTLABS::IMUYostLabsStream)
XPCF_END_COMPONENTS_DECLARATION
