#pragma once
//MIT License
//
//Copyright(c) 2021 Jaf932074323 ������
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
����:������
ʱ��:2020-12-09
����:�����л����ݰ���������
**************************************************************************/
#include <functional>
#include <memory>
#include "PackBase.h"

namespace jaf
{
	// Ԥ���崴�����ĺ���
	typedef std::function<std::shared_ptr<CPackBase>(char* pData, size_t nLen)> CreatePackageFun;

	// �����л����ݰ�����
	class CPackFactBase
	{
	public:
		CPackFactBase() {};
		virtual ~CPackFactBase() {};
		// ע�ᴴ�����ĺ���
		// nPackageType ������
		// createFun �������ĺ���
		virtual void RegisterCreateFun(unsigned int nPackageType, CreatePackageFun createFun) = 0;

		// �ð����ͺ��ֽ����鴴����
		// nPackageType ������
		// pData ���ڴ�����������
		// nLen pData���ݵĳ���
		virtual std::shared_ptr<CPackBase> Create(unsigned int nPackageType, char* pData, size_t nLen) = 0;
	};

} // namespace jaf