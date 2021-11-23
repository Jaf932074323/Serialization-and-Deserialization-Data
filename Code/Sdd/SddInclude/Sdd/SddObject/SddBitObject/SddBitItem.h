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
ʱ��:2020/11/5
����: ��λ���л��ͷ����л�����
**************************************************************************/
#include <vector>
#include <list>
#include <memory>
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/Sdd/SddObject/SddBitObject/SddBitInterface.h"

namespace jaf
{
	// ��λ���л��ͷ����л�����
	class SDD_EXPORT CSddBitItem :public CSddInterface
	{
	public:
		// ��λ���л��ͷ����л�����
		// nLength �ֽڳ���
		CSddBitItem(size_t nLength);
		~CSddBitItem();

		// �ӻ������ж�ȡ����
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader);
		// ������д�뵽������
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer);
		// ��ȡ���л������л�ʹ�õ��ֽڳ���
		virtual size_t GetBufferLength();

		// ���һ������
		virtual void AddChildBitItem(std::shared_ptr<CSddBitInterface> pChildBitItem);

	protected:
		size_t m_nLength; // ����
		char* m_pBuff = nullptr;  // �ڲ����棬������λ�����Ȼ��浽������һ�𿽱������������
		void* m_pBits = nullptr;  // �����б�

	};

} // namespace jaf
