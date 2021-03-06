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

#ifndef MODULEIMUYOSTLABS_TRAITS_H
#define MODULEIMUYOSTLABS_TRAITS_H

#include "xpcf/api/IComponentManager.h"

namespace SolAR {
namespace MODULES {
namespace IMUYOSTLABS {
class IMUYostLabs;
class IMUYostLabsStream;
}
}
}

XPCF_DEFINE_COMPONENT_TRAITS(SolAR::MODULES::IMUYOSTLABS::IMUYostLabs,
                             "33249692-10d0-11e8-b642-0ed5f89f718b",
                             "SolAR::MODULES::IMUYOSTLABS::IMUYostLabs component")

XPCF_DEFINE_COMPONENT_TRAITS(SolAR::MODULES::IMUYOSTLABS::IMUYostLabsStream,
                             "92d64878-163a-11e8-b642-0ed5f89f718b",
                             "SolAR::MODULES::IMUYOSTLABS::IMUYostLabsStream component")





#endif // MODULEIMUYOSTLABS_TRAITS_H


