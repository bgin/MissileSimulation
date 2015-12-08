
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Range measurement class - inline accessors definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline   double   radiolocation::RangeToTarget::DeltaTime() const
{
	return this->m_dDeltaTime;
}

__forceinline   double   radiolocation::RangeToTarget::Range() const
{
	return this->m_dRange;
}