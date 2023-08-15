#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

#include <wrl/client.h>
#include <DirectXMath.h>
#include <d3d11.h>

/**
 * \brief Include the user's header files
 */
#include "Types.h"
#include "Utils.h"

using namespace Microsoft::WRL;
using namespace DirectX;
using namespace std;