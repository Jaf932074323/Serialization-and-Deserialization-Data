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
ʱ��:2020/11/12
����:�Բ���λ������л��ͷ����л�
**************************************************************************/
#include "SddItem/SddBitItem/SddBitInterface.h"

namespace jaf
{
	class CSddCharBit :public CSddBitInterface
	{
	public:
		CSddCharBit(char& rChar, size_t nBitIndex, size_t nBitSize);
		~CSddCharBit();

		// �ӻ������ж�ȡλ����
		// pBuff ������
		// nLength �������ܳ���
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(const char* pBuff, size_t nLength);
		// ��λ����д�뵽������
		// pBuff ������
		// nLength �������ܳ���
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool DataToBuffer(char* pBuff, size_t nLength);

	protected:
		// ����һ���ֽ���������λ����һ���ֽ���
		// pDst Ҫ��������Ŀ���ֽڵ�ַ
		// nDstIndex Ŀ���ֽڵĿ�ʼλ��
		// pSrc ��������Դ�ֽڵ�ַ
		// nSrcIndex Դ�ֽڵĿ�ʼλ��
		// nBitSize ������λ��
		// Դ�ֽں�Ŀ���ֽڶ����ܳ���һ���ֽڵķ�Χ
		void BitCopy(char* pDst, size_t nDstIndex, const char* pSrc, size_t nSrcIndex, size_t nBitSize);
	protected:
		char& m_rChar; // Ҫ���л��Ĳ���ֵ������
		size_t m_nBitIndex; // ���л�����λ�Ŀ�ʼ����
		size_t m_nBitSize; // Ҫ���л���λ���� 
	};

} // namespace jaf

