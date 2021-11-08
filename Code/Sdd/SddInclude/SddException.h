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
时间:2018/10/26 16:09
描述:异常类
**************************************************************************/
#include <exception>
#include <string>
#include <tchar.h>

namespace jaf
{
	// 异常位置
	struct SExceptionLocation
	{
		std::string m_strFile; // 出异常的文件
		size_t m_nLine = 0; // 出异常的行数
	};

	class CSddException :public std::exception
	{
	public:
		// 异常基类构造函数
		// strErr 异常描述
		// strExceptionFile 出现异常的文件
		// nExceptionLine 出现异常的行数
		CSddException(const std::string& strErr = ""
			, const std::string& strExceptionFile = ""
			, size_t nExceptionLine = 0)
			:m_strError(strErr)
		{
			m_exceptionLocation.m_strFile = strExceptionFile;
			m_exceptionLocation.m_nLine = nExceptionLine;
		}
		~CSddException(void) {}

		// 向异常中添加异常描述
		// strErr 添加的异常描述
		virtual CSddException& operator<< (const std::string& strErr)
		{
			m_strError += strErr;
			return *this;
		}

		// 获取错误内容
		virtual const std::string& GetErr()
		{
			return m_strError;
		}

		// 获取异常位置
		virtual const SExceptionLocation& GetExceptionLocation()
		{
			return m_exceptionLocation;
		}

	protected:
		std::string m_strError; // 错误描述
		SExceptionLocation m_exceptionLocation; // 出现异常的位置
	};

} // namespace jaf

