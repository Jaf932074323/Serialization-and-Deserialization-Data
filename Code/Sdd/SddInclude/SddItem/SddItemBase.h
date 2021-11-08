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
ʱ��:2020/10/24
����:���л��ͷ����л�һ��
**************************************************************************/
#include "SddInclude/TypeDefine.h"
#include "SddInclude/SddObject/SddInterface.h"
#include "SddInclude/SddEndian/SddEndianBase.h"
#include "SddInclude/SddEndian/SddEndianManage.h"

namespace jaf
{
	class SDD_EXPORT CSddItemBase :public CSddInterface
	{
	public:
		CSddItemBase() : m_rEndian(CSddEndianManage::GetDefaultEndian())
		{};
		CSddItemBase(E_ENDIAN eEndian) :m_rEndian(CSddEndianManage::GetEndian(eEndian))
		{};

		virtual ~CSddItemBase(void) {};

		// �ӻ������ж�ȡ����
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader) = 0;
		// ������д�뵽������
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer) = 0;

		// ��ȡ���л������л�ʹ�õ��ֽڳ���
		virtual size_t GetBufferLength() = 0;

	protected:
		CSddEndianBase& m_rEndian; // ����
	};

} // namespace jaf

