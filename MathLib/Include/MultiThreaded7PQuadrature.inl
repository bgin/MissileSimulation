__forceinline  DWORD  WINAPI  mathlib::MTNewtonCotes7P::nc7p_qdrtr(LPVOID lpvoid)
{
	_ASSERT(nullptr != lpvoid);
	double sum = 0.0L, h, term;
	unsigned int start;
	Fx * fx = static_cast<Fx*>(lpvoid);

	if (1 >= fx->num_steps)
		throw std::runtime_error("Fatal Error in nc7_qdrtr: 1 >= num_steps\n");

	//start = *static_cast<unsigned int*>(fx->Threads);
	start = *static_cast<unsigned int*>(fx->Workers);
	h = (fx->b - fx->a) / (6.0L * static_cast<double>(fx->num_steps));
	term = 0.00714285714L * h;
	sum = 41.0L * fx->fptr(fx->a) + 216.0L * (fx->fptr(fx->a + h) + fx->fptr(fx->a + 5.0L * h)) +
		27.0L * (fx->fptr(fx->a + 2.0L * h) + fx->fptr(fx->a + 4.0L * h)) +
		272.0L * fx->fptr(fx->a + 3.0L * h) + 41.0L * fx->fptr(fx->b);

	for (auto i = 0; i < fx->num_steps; i += fx->NWorkers)
	{
		double x = fx->a + 6.0L * h * static_cast<double>(i);
		sum += 82.0L * fx->fptr(x) + 216.0L * (fx->fptr(x + h) + fx->fptr(x + 5.0L * h)) +
			27.0L * (fx->fptr(x + 2.0L * h) + fx->fptr(x + 4.0L * h)) +
			272.0L * fx->fptr(x + 3.0L * h);
	}
	
	sum *= term;
	::EnterCriticalSection(&fx->cs);
	fx->result += sum;
	::LeaveCriticalSection(&fx->cs);

	return 0;
}

__forceinline  double  mathlib::MTNewtonCotes7P::run_computation(mathlib::Fx * fx)
{
	_ASSERT(nullptr != fx);
	double qdrtr_approx = std::numeric_limits<double>::quiet_NaN();
	HANDLE * ThreadArray = new HANDLE[fx->NWorkers];
	
	::InitializeCriticalSection(&fx->cs);
	for (auto i = 0; i != fx->NWorkers; ++i)
	{
		fx->Workers[i] = i + 1;
		ThreadArray[i] = ::CreateThread(0, 0, static_cast<LPTHREAD_START_ROUTINE>(nc7p_qdrtr), fx, 0, &fx->ThIDArray[i]);
		if (NULL == ThreadArray[i])
		{
			std::printf("::CreateThread failed with an error: %d\n", ::GetLastError());
			::ExitProcess(1);
		}

	}
	::WaitForMultipleObjects(fx->NWorkers, ThreadArray, TRUE, INFINITE);
	for (auto i = 0; i != fx->NWorkers; ++i) ::CloseHandle(ThreadArray[i]);

	delete[] ThreadArray;
	qdrtr_approx = fx->result;
	return qdrtr_approx;

}