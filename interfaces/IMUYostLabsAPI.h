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

#ifndef IMU_YOSTLABS_API_H
#define IMU_YOSTLABS_API_H

#if _WIN32
#ifdef ModuleIMUYostLabs_API_DLLEXPORT
#define IMUYOSTLABS_EXPORT_API __declspec(dllexport)
#else //IMUYOSTLABS_API_DLLEXPORT
#define IMUYOSTLABS_EXPORT_API __declspec(dllimport)
#endif //IMUYOSTLABS_API_DLLEXPORT
#else //_WIN32
#define IMUYOSTLABS_EXPORT_API
#endif //_WIN32
#include "ModuleIMUYostLabs_traits.h"
#endif //IMU_YOSTLABS_API_H
