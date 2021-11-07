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
时间:2020-11-8
描述:端序管理
**************************************************************************/
#include "SddEndian/SddEndianNo.h"
#include "SddEndian/SddEndianBig.h"
#include "SddEndian/SddEndianLittle.h"

namespace jaf
{
	class SDD_EXPORT CSddEndianManage
	{
	public:
		// 设置默认端序
		static void SetDefaultEndian(E_ENDIAN eDefaultEndian);
		// 获取默认端序
		static CSddEndianBase& GetDefaultEndian();

		// 获取端序对象实例
		static CSddEndianBase& GetEndian(E_ENDIAN eEndian);
	private:
		// 端序
		static CSddEndianNo m_endianNo;
		static CSddEndianBig m_endianBig;
		static CSddEndianLittle m_endianLittle;
		static CSddEndianBase* m_pDefaultEdndian; // 默认端序
	};

} // namespace jaf

