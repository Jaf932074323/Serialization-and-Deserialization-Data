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
ʱ��:2018-10-31 16:57
����:���������洢�ֽ�
�ṩ��һ��Ĭ��ջ���ֽ����ȴ洢��Ĭ��ջ�С�
��ʹ���߲�ָ���洢��ʽʱ����Ҫ�洢���ֽڴ�����С��Ĭ��ջ���ȣ�Ĭ�ϴ洢�����ջ�С�
������Ĭ��ջ����ʱ���洢�ڶ�̬�����ڴ��С�
**************************************************************************/
#include <memory.h>
#include "SddInclude/Buffer/BufferBase.h"
#include "SddInclude/SddException.h"

namespace jaf
{
	const size_t g_nAllotMemoryUnit = 32; // ����ռ�ʱ�������ֵ�ı�������
	const size_t g_nDefaultStackLen = 32; // Ĭ��ջ����

	// ������
	class SDD_EXPORT CBuffer :public CBufferBase
	{
	protected:
		// �ֽڴ洢λ��
		enum class E_STORE_SITE
		{
			E_STORE_SITE_STACK = 0, // �洢��Ĭ��ջ��
			E_STORE_SITE_DYNAMIC = 1 // �洢�ڶ�̬�ڴ���
		};
	public:
		CBuffer(void);
		~CBuffer(void);

		// ��� �ͷ��ڴ桢����Ѷ���д�ֽڵ�
		void Clear();

		// ԤԼnSize�ռ�,����д���ֽ� �û������ܹ���д��nSize���ֽ�
		// ������������ʱ�����·��������ڴ�ռ䣬���ܹ���ȡnSize���ֽ�
		// ��ʹ�ô洢���û��ṩ���ڴ�ʱ��������������������false
		// nSize ҪԤԼ�ռ�Ĵ�С
		void Reserve(size_t nSize);

		// ��չ�������ռ�
		// ��չ������������������nCapacity���ֽڴ�С��������������ʱ�����·��������ڴ�ռ䣬���ܹ��ٴ�ȡnSize���ֽ�
		// ��ʹ�ô洢���û��ṩ���ڴ�ʱ��������������������false
		// nCapacity Ҫ��չ��Ŀ���С��С
		void ExtendCapacity(size_t nCapacity);

		// ��ȡ��д���ֽ�����
		size_t GetWriteLength() const;

		// ��ȡ��������ַ
		const char* GetBuffer() const;

	public:
		// д�����ݵ���������
		// pData Ҫд�����ĵ�ַ ����Ϊ��
		// nLength Ҫд��ĳ���
		void Write(const char* pData, size_t nLength);

		// �ظ�д��ͬһ���ַ�����������
		// c Ҫд����ַ�
		// nLength Ҫд���ַ��ĸ���
		// return �ɹ�����true��ʧ�ܷ���false
		void WriteChar(char c, size_t nLength);

	public:
		// ɾ��ǰָ������
		// nLength Ҫɾ���ĳ���,������Ȳ�����ȫ��ɾ��
		virtual void PopFront(size_t nLength);
		// ɾ����ָ������
		// nLength Ҫɾ���ĳ���,������Ȳ�����ȫ��ɾ��
		virtual void PopBack(size_t nLength);

		// �������ڴ�
		// pSeekContent ���������ݵ��׵�ַ
		// nSeekcontentLength ���������ݵĳ���
		// rIndex ���ر����������ݵ�����
		// �����Ƿ�������
		virtual bool SeekFront(const char* pSeekContent, size_t nSeekContentLength, size_t& rIndex);

	private:
		// �ͷŶ�̬������ڴ�ռ� ������������ͷ����ڴ棬�������ֵ����������д�ֽڵȵȶ�û�������������������������
		void ReleaseAllotMemory();

	protected:
		// ������ָ��,ָ��洢�ֽڵ��׵�ַ
		// ��ʹ��Ĭ��ջʱ����ָ��Ĭ��ջ�׵�ַ
		// ��ʹ�ö�̬�ڴ�ռ�ʱ��ָ��̬�ڴ��׵�ַ
		char* m_pBuffer = nullptr;
		char m_arrBufferStack[g_nDefaultStackLen]; // Ĭ��ջ
		E_STORE_SITE m_eStoreSite = E_STORE_SITE::E_STORE_SITE_STACK; // �ֽڴ洢λ��

		size_t m_nCapacity = g_nDefaultStackLen; // ������
		size_t m_nWriteByteLen = 0; // �Ѿ�д���ֽڵĳ���
	};

} // namespace jaf
