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
ʱ��:2021/11/21
����:vector�����л��ͷ����л�����
**************************************************************************/
#include <vector>
#include <memory>
#include <functional>
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/SddEndian/SddEndianBase.h"

// ����double���������л������л�����
#define SDD_VECTOR(rLen, rVector, rSddElement, rElement) jaf::CSddVector::Creation(rLen,rVector,rSddElement,rElement)
namespace jaf
{
	template<typename ElementType, typename SddElementType>
	// vector�����л��ͷ����л�����
	// ElementType Ԫ������
	// SddElementType ���л������л�Ԫ�صĶ���
	class CSddVector :public CSddInterface
	{
	public:
		// vector�����л��ͷ����л�����Ĺ��캯��
		// rVector �����л���vector
		// pSddElement ���л�Ԫ�صĶ���
		// rElement ���л�ÿһ��ʱ�������л���Ԫ��
		// ע���������������л��ͷ����л���һֱû��ú���ʵ�ַ�ʽ������ʵ����ԱȽϸ��ӣ��и��õķ�ʽʱ���޸�
		CSddVector(std::vector<ElementType>& rVector, std::shared_ptr<SddElementType> pSddElement, ElementType& rElement)
			:m_rVector(rVector)
			, m_pSddElement(pSddElement)
			, m_rElement(rElement)
		{
		}

		~CSddVector()
		{

		}

		// ����vector�����л��ͷ����л�����
		// rVector �����л���vector
		// pSddElement ���л�Ԫ�صĶ���
		// rElement ���л�ÿһ��ʱ�������л���Ԫ��
		static std::shared_ptr< CSddVector< ElementType, SddElementType>> Creation(std::vector<ElementType>& rVector, std::shared_ptr<SddElementType> pSddElement, ElementType& rElement)
		{
			std::shared_ptr<CSddVector< ElementType, SddElementType>> pItem = std::make_shared<CSddVector< ElementType, SddElementType>>(rVector, pSddElement, rElement);
			if (pItem == nullptr)
			{
				throw CSddException("����double������ʧ��", __FILE__, __LINE__);
			}
			return pItem;
		}

		// �ӻ������ж�ȡ����
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			if (m_nLen < 0)
			{
				return false;
			}

			m_rVector.resize(m_nLen);
			for (size_t i = 0; i < m_nLen; ++i)
			{
				if (!m_pSddElement->BufferToData(rBuffReader))
				{
					return false;
				}
				m_rVector[i] = m_rElement;
			}

			return true;
		}

		// ������д�뵽������
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			m_nLen = m_rVector.size();

			for (size_t i = 0; i < m_nLen; ++i)
			{
				m_rElement = m_rVector[i];
				m_pSddElement->DataToBuffer(rBuffer);
			}
		}

		// ��ȡ���л������л�ʹ�õ��ֽ����г���
		virtual size_t GetBufferLength()
		{
			m_nLen = m_rVector.size();

			size_t nLen = m_pSddElement->GetBufferLength() * m_nLen;
			return nLen;
		}

		// ����vector�ĳ��ȣ��ڷ����л�ʱ����ȡ�����л�������
		void SetLen(size_t nLen)
		{
			m_nLen = nLen;
			m_rVector.resize(nLen);
		}

	public:
		size_t m_nLen = 0; // ��¼���ȵĶ���
		std::vector<ElementType>& m_rVector; // �����л���vector
		std::shared_ptr<SddElementType> m_pSddElement; // ���л�Ԫ�صĶ���
		ElementType& m_rElement; // ���л�ÿһ��ʱ�������л���Ԫ��
	};
}
