
template<typename _Ty> __forceinline mathlib::Array1D<_Ty>::Array1D()
{
	// this->m_data initialized to zero-size array.
	this->m_data = new _Ty[0];
}

template<typename _Ty> __forceinline mathlib::Array1D<_Ty>::Array1D(const int n)
{
#if defined _DEBUG
	_ASSERTE(0 < n);
#endif
	_ASSERT(0 < n);
	this->size = n;
	this->m_data = new _Ty[this->size];
}

template<typename _Ty> __forceinline mathlib::Array1D<_Ty>::Array1D(const int n, const _Ty _ty)
{
#if defined _DEBUG
	_ASSERTE(0 < n);
#endif
	_ASSERT(0 < n);
	this->size = n;
	this->m_data = new _Ty[this->size];
	std::fill(this->m_data, this->m_data + this->size, _ty);
}



template<typename _Ty> __forceinline mathlib::Array1D<_Ty>::Array1D(const _Ty * ptr, const int size_ptr)
{
#if defined _DEBUG
	_ASSERTE((nullptr != ptr) || (0 < size_ptr));
#endif
	_ASSERT((nullptr != ptr) || (0 < size_ptr));
	this->size = size_ptr;
	this->m_data = new _Ty[this->size];
	std::copy(ptr, ptr + size_ptr, this->m_data);
}

template<typename _Ty> __forceinline mathlib::Array1D<_Ty>::Array1D( mathlib::Array1D<_Ty> const &rhs)
{
#if defined _DEBUG
	_ASSERTE(0 < rhs.size);
#endif
	_ASSERT(0 < rhs.size);
	this->size = rhs.size;
	std::copy(rhs.m_data, rhs.m_data + rhs.size, this->m_data);

}

template<typename _Ty> __forceinline mathlib::Array1D<_Ty>::Array1D(mathlib::Array1D<_Ty> &&rhs)
{
#if defined _DEBUG
	_ASSERTE(0 < rhs.size);
#endif
	_ASSERT(0 < rhs.size);
	this->size = rhs.size;
	//std::copy(rhs.m_data, rhs.m_data + rhs.size, this->m_data);
	std::move(rhs.m_data, rhs.m_data + rhs.size, this->m_data);
	rhs.size = 0;
	rhs.m_data = nullptr;
}

template<typename _Ty> __forceinline mathlib::Array1D<_Ty>::~Array1D()
{
	if (this->m_data)
	{
		delete[] this->m_data;
	}
}

template<typename _Ty> __forceinline _Ty * mathlib::Array1D<_Ty>::get_m_data()
{
	return this->m_data;
}

template<typename _Ty> __forceinline const _Ty * mathlib::Array1D<_Ty>::get_m_data() const
{
	return this->m_data;
}

template<typename _Ty> __forceinline  const int  mathlib::Array1D<_Ty>::get_size() const
{
	return this->size;
}

#if defined _DEBUG

template<typename _Ty> __forceinline void mathlib::Array1D<_Ty>::debug_print(const mathlib::Array1D<_Ty> &obj)
{
	for (auto i = 0; i != obj.size; ++i) std::printf("Array1D[%d]=%.15f\n",i, obj.m_data[i]);
	
}
#endif
template<typename _Ty> template<typename Function> __forceinline void mathlib::Array1D<_Ty>::apply(Function f, const _Ty _ty)
{
	std::fill(this->m_data, this->m_data + this->size, f(_ty));
}

template<typename _Ty> template<typename... Function> __forceinline void mathlib::Array1D<_Ty>::apply(Function... f)
{
	std::fill(this->m_data, this->m_data + this->size, f()...);
}

template<typename _Ty> template<typename Function> __forceinline void mathlib::Array1D<_Ty>::apply(mathlib::Array1D<_Ty> &obj, Function f)
{
	_Ty * temp = f();
	for (auto i = 0; i != obj.get_size(); ++i)
	{ 
		
		obj.get_m_data()[i] = temp[i];
	}
	delete[]temp;
}

template<typename _Ty> __forceinline  _Ty * mathlib::AllocateVec1D<_Ty>::allocate1D(const int n)
{
#if defined _DEBUG
	_ASSERTE(0 < n);
#endif
	if (n <= 0) return nullptr;

	_Ty * vec1D;
	try
	{
		vec1D = new _Ty[n];
	}
	catch (std::bad_alloc &ba)
	{
		std::cerr << "Failed to Allocate Memory occurred in FILE " << __FILE__
			<< "in Function " << __FUNCTIONW__ << " at Line of Code # [" << __LINE__ << "]" << std::endl;
		deallocate1D(vec1D);
	}

	// return pointer to uninitialized array.
	return vec1D;

}

template<typename _Ty> __forceinline  void mathlib::AllocateVec1D<_Ty>::deallocate1D(_Ty * ptr)
{
	if (ptr)
	{
		delete[] ptr;
	}
}

template<typename _Ty> __forceinline _Ty ** mathlib::AllocateVec2D<_Ty>::allocate2D(const int m, const int n)
{
#if defined _DEBUG
	_ASSERTE((0 < m) && (0 < n));
#endif

	if ((m <= 0) || (n <= 0)) return nullptr;

	_Ty ** vec2D;

	try{
		vec2D = new _Ty*[m];
		for (auto i = 0; i != m; ++i) vec2D[i] = new _Ty[n];

	   }
	catch (std::bad_alloc &ba)
	{
		std::cerr << "Failed to Allocate Memory  in FILE " << __FILE__
			<< "in Function " << __FUNCTIONW__ << " at Line of Code # [" << __LINE__ << "]" << std::endl;
		deallocate2D(vec2D);
	}
	
	return vec2D;
	   
}

template<typename _Ty> __forceinline  void  mathlib::AllocateVec2D<_Ty>::deallocate2D(_Ty ** ptr)
{
	if (ptr)
	{
		delete[] ptr[0];
		delete[] ptr;
	}
}

template<typename _Ty> __forceinline _Ty ** mathlib::AllocateVec2D<_Ty>::allocate2D_fast(const int m, const int n)
{
#if defined _DEBUG
	_ASSERTE((0 < m) && (0 < n));
#endif

	if ((0 >= m) || (0 >= n)) return nullptr;

	_Ty ** vec2D;
	const int length = m * n;
	try{

		vec2D = new _Ty*[m];
		vec2D[0] = new _Ty[length];
	}
	catch (std::bad_alloc &ba)
	{
		std::cerr << "Failed to Allocate Memory  occurred in FILE " << __FILE__
			<< "in Function " << __FUNCTIONW__ << " at Line of Code # [" << __LINE__ << "]" << std::endl;
		deallocate2D(vec2D);
	}
	for (auto i = 0; i != m; ++i)
	{
		auto j0 = m * i;
		vec2D[i] = &vec2D[0][j0];
	}
	return vec2D;
}

template<typename _Ty> __forceinline _Ty *** mathlib::AllocateVec3D<_Ty>::allocate3D(const int l, const int m, const int n)
{
#if defined _DEBUG
	_ASSERTE((0 < l) && (0 < m) && (0 < n));
#endif

	if ((0 >= l) || (0 >= m) || (0 >= n)) return nullptr;

	_Ty *** vec3D;
	try{

		vec3D = new _Ty**[l];
		for (auto i = 0; i != l; ++i)
		{
			vec3D[i] = new _Ty*[m];
			for (auto j = 0; j != m)
			{
				vec3D[i][j] = new _Ty[n];
			}
		}
	  }
	catch (std::bad_alloc &ba)
	{
		std::cerr << "Failed to Allocate Memory occurred in FILE " << __FILE__
			<< "in Function " << __FUNCTIONW__ << " at Line of Code # [" << __LINE__ << "]" << std::endl;
		deallocate3D(vec3D);
	}
	return vec3D;
}

template<typename _Ty> __forceinline _Ty *** mathlib::AllocateVec3D<_Ty>::allocate3D_fast(const int l, const int m, const int n)
{
#if defined _DEBUG
	_ASSERTE((0 < l) && (0 < m) && (0 < n));
#endif
	if ((0 >= l) || (0 >= m) || (0 >= n)) return nullptr;

	_Ty ***vec3D;
	const int stride_y = m * n;
	const int stride_z = l * stride_y;
	try
	{
		vec3D = new _Ty**[n];
		vec3D[0] = new _Ty*[stride_y];
		vec3D[0][0] = new _Ty[stride_z];
	}
	catch (std::bad_alloc &ba)
	{
		std::cerr << "Failed to Allocate Memory  in FILE " << __FILE__
			<< "in Function " << __FUNCTIONW__ << " at Line of Code # [" << __LINE__ << "]" << std::endl;
		deallocate3D(vec3D);
	}

	for (auto i = 0; i != n; ++i)
	{
		auto j1 = m * i;
		vec3D[i] = &vec3D[0][j1];
		for (auto j = 0; i != m; ++i)
		{
			auto j0 = l * (j + j1);
			vec3D[i][j] = &vec3D[0][0][j0];
		}
	}
	return vec3D;
}

template<typename _Ty> __forceinline  void  mathlib::AllocateVec3D<_Ty>::deallocate3D(_Ty ***ptr)
{
	if (ptr)
	{
		delete[] ptr[0][0];
		delete[] ptr[0];
		delete[] ptr;
	}
}

__forceinline     void           mathlib::DisplayFPNumber(union FPNumber const& fp)
{
	for (int i{ 7 }; i >= 0; --i) std::printf("FP Number=%02x", fp.c[i]);
	std::printf("\n");
		
}