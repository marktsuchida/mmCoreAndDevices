// PROJECT:       Micro-Manager
// SUBSYSTEM:     MMCore
//
// DESCRIPTION:   Camera device instance wrapper
//
// COPYRIGHT:     Nenad Amodaj 2024
//                All Rights reserved
//
// LICENSE:       This file is distributed under the "Lesser GPL" (LGPL) license.
//                License text is included with the source distribution.
//
//                This file is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty
//                of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//                IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//                CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//                INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES.
//
// AUTHOR:        Nenad Amodaj

#include "StorageInstance.h"

int StorageInstance::Create(int handle, const char* path, const char* name, const std::vector<int>& shape, MM::StorageDataType pixType, const char* meta, int metaLength)
{
   RequireInitialized(__func__);

   int ret = GetImpl()->Create(handle, path, name, (int)shape.size(), &shape[0], pixType, meta, metaLength);
   if (ret != DEVICE_OK)
      return ret;
   
   return DEVICE_OK;
}

int StorageInstance::Close(int handle)
{
   RequireInitialized(__func__);

   return GetImpl()->Close(handle);
}

int StorageInstance::GetShape(int handle, std::vector<long>& shape)
{
   RequireInitialized(__func__);
   int numDim(0);
   int ret = GetImpl()->GetNumberOfDimensions(handle, numDim);
   if (ret != DEVICE_OK)
      return ret;
   int* shapeArray = new int[numDim];
   ret = GetImpl()->GetShape(handle, shapeArray);
   if (ret != DEVICE_OK)
      return ret;
   shape.clear();
   for (int i = 0; i < numDim; i++)
      shape.push_back(shapeArray[i]);

   return DEVICE_OK;
}

int StorageInstance::GetPixelType(int handle, MM::StorageDataType& dataType)
{
   RequireInitialized(__func__);
   int ret = GetImpl()->GetDataType(handle, dataType);
   if (ret != DEVICE_OK)
      return ret;

   return DEVICE_OK;
}

int StorageInstance::AppendImage(int handle, int sizeInBytes, unsigned char* pixels, const char* imageMeta, int metaLength)
{
   RequireInitialized(__func__);
   return GetImpl()->AppendImage(handle, sizeInBytes, pixels, imageMeta, metaLength);
}

int StorageInstance::GetNumberOfDimensions(int handle, int& numDim)
{
   RequireInitialized(__func__);
   return GetImpl()->GetNumberOfDimensions(handle, numDim);
}

int StorageInstance::GetPath(int handle, std::string& path)
{
	char cPath[MM::MaxStrLength];
	memset(cPath, 0, MM::MaxStrLength);
	int ret = GetImpl()->GetPath(handle, cPath, MM::MaxStrLength);
	path = cPath;
	return ret;
}
