
template<typename T> std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value,void>::type
atmosphere::GLATF<T>::operator()(_In_ const T lat, _In_ T* gv, _In_ T* reff){

	constexpr T dgtr (1.74533E-2);
	T c2 = cos(2.0 * dgtr * lat);
	*gv = 980.616 * (1.0 - 0.0026373 * c2);
	*reff = 2.0 * (*gv) / (3.085462E-6 + 2.27E-9 * c2) * 1.0E-5;
}

