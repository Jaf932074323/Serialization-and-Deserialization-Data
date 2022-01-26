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
时间:2020-12-13
描述:包头基类
**************************************************************************/
#include "SddInclude/Sdd/SddBase.h"

namespace jaf
{
	class CPackHeadBase :public CSddBase
	{
	public:
		CPackHeadBase() {};
		virtual ~CPackHeadBase() {};

		// 查找头所在位置
		// pData 要查找头的数据
		// rIndex 用于返回索引。如果找到则返回头第一个字节的位置索引；如果没有找，则这个索引之前的所有数据都是无效的
		// 返回头是否找到索引
		virtual bool SeekHead(const char* pData, size_t nLength, size_t& rIndex) = 0;
		// 获取包内容的长度
		virtual size_t GetContentLen() = 0;
		// 获取包类型
		virtual unsigned int GetType() = 0;
		// 检查包头是否正确
		virtual bool Check() = 0;

	protected:

	};

} // namespace jaf

