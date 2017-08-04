#pragma  once
//2005.4.16 ����߽�����ڴ�





#ifndef YSS_ASSERT
#define YSS_ASSERT
#endif // !YSS_ASSERT


//�ڴ����......Head+(�߽�)Block
inline void* aligned_new(size_t size, size_t alignment)
{
	// ���alignment�Ƿ���2^N  
	YSS_ASSERT((alignment & (alignment - 1)));
	// �����һ������offset��sizeof(void*)��Ϊ�˴洢ԭʼָ���ַ  
	size_t offset = sizeof(void*)+(--alignment);

  
	//u_char* p =(u_char*) malloc(offset + size);
	unsigned char * p = (unsigned char *)new unsigned char[offset + size];
	if (!p) return nullptr;

	// ͨ��& alignment�Ĳ���õ�����ı߽��ַ
	void* r = (void *)(((size_t)(p + offset)) & (~alignment));
	// ��r����һ��ָ��void*��ָ�룬��r��ǰ��ַǰ�����ԭʼ��ַ  
	((void **)r)[-1] = p;
	// ���ؾ���������ڴ��ַ  
	return r;
}

inline void aligned_delete(void* p)
{
	// ��ԭ��ԭʼ��ַ����free  
	//free(((void **)p)[-1]);
	delete p;
}

#ifdef _USE_HEAPMEM_CACHE_LINE_
inline void* operator new(size_t size)
{
	//void*   tmp=malloc(size);   
	//memset(tmp,0,size);   
	//return   tmp;   

	return aligned_new(size, __CACHE_LINE__);
}


/*
inline void *__cdecl operator new(size_t, void *_P)
{
return (_P);
}
*/


inline void operator delete(void * ptr)
{
	//free(ptr);   
	aligned_free(ptr);
}

inline void* operator new[](size_t size)
{
	return aligned_new(size, __CACHE_LINE__);
}

inline void operator delete[](void * ptr)
{
	aligned_delete(ptr);
}

#endif



class CAlignedMemory
{
public:
	
	inline void* operator new(size_t size)
	{
		 
		return aligned_new(size, __CACHE_LINE__);
	}


	inline void operator delete(void * ptr)
	{
		//free(ptr);   
		aligned_delete(ptr);
	}

	inline void* operator new[](size_t size)
	{
		return aligned_new(size, __CACHE_LINE__);
	}

	inline void operator delete[](void * ptr){
		
		aligned_delete(ptr);
	}

	CAlignedMemory(){};
	~CAlignedMemory(){};

protected:
	
private:
};


#define USING_ALIGNEDMEM  inline void* operator new(size_t size)\
{\
	return aligned_new(size, __CACHE_LINE__);\
}\
inline void operator delete(void * ptr)\
{\
	aligned_delete(ptr);\
}\
	inline void* operator new[](size_t size)\
{\
	return aligned_new(size, __CACHE_LINE__); \
}\
inline void operator delete[](void * ptr)\
{\
	aligned_delete(ptr); \
}\


#define USING_PAGE_ALIGNEDMEM  inline void* operator new(size_t size)\
{\
	return aligned_new(size, __PAGE_SIZE__);\
}\
inline void operator delete(void * ptr)\
{\
	aligned_delete(ptr);\
}\
	inline void* operator new[](size_t size)\
{\
	return aligned_new(size, __PAGE_SIZE__); \
}\
inline void operator delete[](void * ptr)\
{\
	aligned_delete(ptr); \
}\

/*



*/

