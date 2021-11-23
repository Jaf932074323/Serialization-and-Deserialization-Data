#pragma once
//MIT License
//
//Copyright(c) 2021 Jaf932074323 姜安富
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
/**************************************************************************
作者:姜安富
时间:2020/10/25
描述:序列化和反序列化 头文件
**************************************************************************/
// 序列化和反序列化接口和基类相关
#include "ExportDefine.h"
#include "Sdd/SddInterface.h"
#include "SddInclude/Sdd/SddBase.h"

// 缓存和缓存读取器相关
#include "Buffer/BufferBase.h"
#include "Buffer/BuffReaderBase.h"
#include "Buffer/Buffer.h"
#include "Buffer/BuffReader.h"

// 端序相关
#include "SddEndian/SddEndianBase.h"
#include "SddEndian/SddEndianBig.h"
#include "SddEndian/SddEndianLittle.h"
#include "SddEndian/SddEndianNo.h"
#include "SddEndian/SddEndianManage.h"

// 序列化和反序列化单项相关
#include "SddInclude/Sdd/SddBase.h"
#include "Sdd/SddObject/SddInteger.h"
#include "Sdd/SddObject/SddDouble.h"
#include "Sdd/SddObject/SddFloat.h"
#include "Sdd/SddObject/SddString.h"
#include "Sdd/SddObject/SddVariLenString.h"
#include "Sdd/SddObject/SddChunk.h"
#include "Sdd/SddObject/SddPlaceholder.h"
// 序列化和反序列化单项中位相关
#include "Sdd/SddObject/SddBitObject/SddBitInterface.h"
#include "Sdd/SddObject/SddBitObject/SddBitItem.h"
#include "Sdd/SddObject/SddBitObject/SddBoolBit.h"
#include "Sdd/SddObject/SddBitObject/SddCharBit.h"

// 组包与解包相关
#include "ParsePackage/PackBase.h"
#include "ParsePackage/ParsePackBase.h"
#include "ParsePackage/PackFactBase.h"
#include "ParsePackage/PackFactory.h"
#include "ParsePackage/DealPackInterface.h"
// 固定头和尾类型的包相关
#include "ParsePackage/FixedHeadAndTail/ParsePackHeadTail.h"
#include "ParsePackage/SpecialPack/PackHeadBase.h"
#include "ParsePackage/SpecialPack/PackTailBase.h"

