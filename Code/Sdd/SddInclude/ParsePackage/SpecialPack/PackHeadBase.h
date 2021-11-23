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
ʱ��:2020-12-13
����:��ͷ����
**************************************************************************/
#include "SddInclude/Sdd/SddBase.h"

namespace jaf
{
	class CPackHeadBase :public CSddBase
	{
	public:
		CPackHeadBase() {};
		virtual ~CPackHeadBase() {};

		// ����ͷ����λ��
		// pData Ҫ����ͷ������
		// rIndex ���ڷ�������������ҵ��򷵻�ͷ��һ���ֽڵ�λ�����������û���ң����������֮ǰ���������ݶ�����Ч��
		// ����ͷ�Ƿ��ҵ�����
		virtual bool SeekHead(const char* pData, size_t nLength, size_t& rIndex) = 0;
		// ��ȡ�����ݵĳ���
		virtual size_t GetContentLen() = 0;
		// ��ȡ������
		virtual unsigned int GetType() = 0;
		// ����ͷ�Ƿ���ȷ
		virtual bool Check() = 0;

	protected:

	};

} // namespace jaf

