

template<typename Timer> __forceinline  mathlib::DatumMinMax<Timer>::DatumMinMax(_In_ Timer const& timer)
{
	this->m_iDataSize = timer.m_iNumRuns * timer.m_iDatumSize;
	_ASSERT(this->m_iDataSize == timer.m_iNumRuns * timer.m_iDatumSize);
	this->m_oTimeSamples = std::vector<unsigned long long>(this->m_iDataSize);
	
	// move content of timer.m_oTimes to *this
	this->m_oTimeSamples.operator=(std::move(timer.m_oTimes));
	//for (int i{ 0 }; i < this->m_iDataSize; ++i)std::printf("indx=%u,datum_max=%llu\n",i, timer.m_oTimes[i]);
	
	
}

template<typename Timer> __forceinline  int  mathlib::DatumMinMax<Timer>::DataSize() const
{
	return this->m_iDataSize;
}

template<typename Timer> __forceinline  unsigned long long  mathlib::DatumMinMax<Timer>::DataSetMax() const
{
	return this->m_uDataSetMax;
}

template<typename Timer> __forceinline  unsigned long long  mathlib::DatumMinMax<Timer>::DataSetMin() const
{
	return this->m_uDataSetMin;
}

template<typename Timer> __forceinline  double              mathlib::DatumMinMax<Timer>::DataSetMean() const
{
	return this->m_dMean;
}

template<typename Timer> __forceinline  double              mathlib::DatumMinMax<Timer>::DataSetErrorMean() const
{
	return this->m_dErrorMean;
}

template<typename Timer> __forceinline  std::vector<unsigned long long> mathlib::DatumMinMax<Timer>::TimeSamples() const
{
	return this->m_oTimeSamples;
}

template<typename Timer> __forceinline  const unsigned long long *mathlib::DatumMinMax<Timer>::CArray() const
{
	const unsigned long long* p_vTS = nullptr;
	p_vTS = this->m_oTimeSamples.operator[](0);
	return p_vTS;
}



template<typename Timer> __forceinline  mathlib::DatumMinMax<Timer> &  mathlib::DatumMinMax<Timer>::operator=(_In_ DatumMinMax const& rhs)
{
	if (this == &rhs) return (*this);
	this->m_iDataSize = rhs.m_iDataSize;
	this->m_uDataSetMax = rhs.m_uDataSetMax;
	this->m_uDataSetMin = rhs.m_uDataSetMin;
	this->m_dMean = rhs.m_dMean;
	this->m_dErrorMean = rhs.m_dErrorMean;
	this->m_oTimeSamples.operator=(rhs.m_oTimeSamples);
	return (*this);
}

template<typename Timer> __forceinline  mathlib::DatumMinMax<Timer>  &  mathlib::DatumMinMax<Timer>::operator=(_In_ DatumMinMax &&rhs)
{
	if (this == &rhs) return (*this);
	this->m_iDataSize = std::move(rhs.m_iDataSize);
	this->m_uDataSetMax = std::move(rhs.m_uDataSetMax);
	this->m_uDataSetMin = std::move(rhs.m_uDataSetMin);
	this->m_dMean = std::move(rhs.m_dMean);
	this->m_dErrorMean = std::move(rhs.m_dErrorMean);
	this->m_oTimeSamples.operator=(std::move(rhs.m_oTimeSamples));
	return (*this);
}


template<typename Timer> __forceinline  void mathlib::DatumMinMax<Timer>::compute_minmax()
{
	// generic for_each loop.
	this->m_oSamplesMaximum = std::for_each(this->m_oTimeSamples.begin(), this->m_oTimeSamples.end(), this->m_oSamplesMaximum);
	
	this->m_uDataSetMax = getMaximum();
	this->m_uDataSetMin = getMinimum();
	this->m_dMean = getMean();
	this->m_dErrorMean = getErrorMean();
}





template<typename Timer> __forceinline  unsigned long long mathlib::DatumMinMax<Timer>::getMaximum()
{
	return extract_result<tag::max>(this->m_oSamplesMaximum);
}

template<typename Timer> __forceinline  unsigned long long mathlib::DatumMinMax<Timer>::getMinimum()
{
	return extract_result<tag::min>(this->m_oSamplesMaximum);
}

template<typename Timer> __forceinline  double             mathlib::DatumMinMax<Timer>::getMean()
{
	return extract_result<tag::mean>(this->m_oSamplesMaximum);
}

template<typename Timer> __forceinline  double             mathlib::DatumMinMax<Timer>::getErrorMean()
{
	return extract_result<tag::error_of<tag::mean>>(this->m_oSamplesMaximum);
}