#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED
#include <stdlib.h>
#include <assert.h>
#include <stdexcept>
#pragma push_macro("new")
#pragma push_macro("delete")
#undef new
#undef delete



	//
	// SingletonHolder
	// Reference 'Loki'
	// See loki-0.1.7\include\loki\Singleton.h
	// See "Modern C++ Design"
	//

	#define SINGLETON_HOLDER_INLINE __inline

	template <class _Type>
	class SingletonHolder
	{
	public:
		static _Type* Instance(void);

	private:
		static bool bDestroyed_;
		static _Type* pInstance_;

		SingletonHolder<_Type>(void) {}
		SingletonHolder& operator = (const SingletonHolder& single){}

		static _Type* Create()
		{
			return new _Type;
		}

		static void Destroy()
		{
			assert(!bDestroyed_);
			bDestroyed_ = true;
			delete pInstance_;
			pInstance_ = NULL;
		}

		static void OnDeadReference (void) {
			throw std::logic_error("Dead Reference Detected (Singleton)");
		}

	};

	template <class _Type>
	_Type* SingletonHolder<_Type>::pInstance_ = NULL;

	template <class _Type>
	bool SingletonHolder<_Type>::bDestroyed_ = false;

	template <class _Type>
	SINGLETON_HOLDER_INLINE _Type* SingletonHolder<_Type>::Instance()
	{
		if (!pInstance_)
		{
			if (bDestroyed_)
			{
				OnDeadReference();
			}
			pInstance_ = Create();
			atexit(&Destroy);
		}
		return pInstance_;
	}


#define Singleton SingletonHolder
#pragma pop_macro("delete")
#pragma pop_macro("new")


#endif // SINGLETON_H_INCLUDED
