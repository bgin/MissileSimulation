
__forceinline  void  mathlib::InitFx(mathlib::Fx * fx, std::function<double(double)> func, double aa, double bb, const unsigned int nWorkers,
	const unsigned int nSteps)
{
	_ASSERT((0 < nWorkers) && (nullptr != fx));
	_ASSERT(1 <= nSteps);
	fx->a = aa;
	fx->b = bb;
	fx->fptr = func;
	fx->NWorkers = nWorkers;
	fx->num_steps = nSteps;
	fx->ThIDArray = new DWORD[fx->NWorkers];
	fx->Workers = new unsigned int[fx->NWorkers];
}

__forceinline   void  mathlib::DeallocFx(mathlib::Fx * fx)
{
	if (fx->Workers && fx->ThIDArray)
	{
		delete[] fx->Workers;
		delete[] fx->ThIDArray;
	}
}