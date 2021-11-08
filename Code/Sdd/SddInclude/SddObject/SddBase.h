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
ʱ��:2018/10/25
����:���л��ͷ����л����ݶ��� Serialization and Deserialization Data ���ΪSDD
����༰�����������Ƿ���Ľ��ض������ݼ����л����ֽ�����(����������)��
�Լ����ֽ�����(����������)�з����л����ض������ݶ���
**************************************************************************/
#include <list>
#include <memory>
#include "SddInclude/SddObject/SddInterface.h"
#include "SddInclude/SddEndian/SddEndianBase.h"
#include "SddInclude/SddEndian/SddEndianBase.h"
#include "SddInclude/SddEndian/SddEndianNo.h"
#include "SddInclude/SddEndian/SddEndianLittle.h"
#include "SddInclude/SddEndian/SddEndianBig.h"

#define SDD_ADD_ITEM(CreationItemFun) AddChildItem(CreationItemFun);
namespace jaf
{
	class SDD_EXPORT CSddBase :public CSddInterface
	{
	public:
		CSddBase();
		CSddBase(E_ENDIAN eEndian);
		~CSddBase(void);

		// �ӻ������ж�ȡ����
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffer);
		// ������д�뵽������
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer);
		// ��ȡ���л������л�ʹ�õ��ֽ����г���
		virtual size_t GetBufferLength();

	protected:
		// �������
		void AddChildItem(std::shared_ptr<CSddInterface> pChildItem);

	protected:
		CSddEndianBase& m_rEndian; // ����

		void* m_pItems = nullptr;
		//std::list<std::shared_ptr<CSddInterface>> m_childItems; // �����б�
	};

} // namespace jaf

