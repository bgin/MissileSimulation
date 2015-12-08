__forceinline  DWORD  WINAPI  mathlib::MTBoolQdrtr::boole_qdrtr(LPVOID lpvoid)
{
	_ASSERT(nullptr != lpvoid);

	double h = 0.0L, sum = 0.0L, term;
	unsigned int start;
	Fx * fx = static_cast<Fx*>(lpvoid);

	if (1 >= fx->num_steps)
		throw std::runtime_error("Fatal Error in boole_qdrtr: 1 >= num_steps\n");

	start = *static_cast<unsigned int*>(fx->Workers);
	h = (fx->b - fx->a) / (4.0L * static_cast<double>(fx->num_steps));
	term = 0.022222222222L * (2.0L * h);
	sum = 7.0L * fx->fptr(fx->a) + 32.0L * (fx->fptr(fx->a + h) + fx->fptr(fx->a + 3.0L * h)) + 12.0L * fx->fptr(fx->a + 2.0L * h) +
		7.0L * fx->fptr(fx->b);

	for (auto i = start; i < fx->num_steps; i += fx->NWorkers)
	{
		double x = fx->a + 4.0L * h * static_cast<double>(i);
		sum += 14.0L * fx->fptr(x) + 32.0L * (fx->fptr(x + h) + fx->fptr(x + 3.0L * h)) + 12.0L * fx->fptr(x + 2.0L * h);
		
	}
	
	sum *= term;
	::EnterCriticalSection(&fx->cs);
	fx->result += sum;
	::LeaveCriticalSection(&fx->cs);

	return 0;
}

__forceinline  double   mathlib::MTBoolQdrtr::run_computation(mathlib::Fx * fx)
{
	_ASSERT(nullptr != fx);

	double qdrtr_approx = std::numeric_limits<double>::quiet_NaN();
	HANDLE * ThreadArray = new HANDLE[fx->NWorkers];
	::InitializeCriticalSection(&fx->cs);
	for (auto i = 0; i != fx->NWorkers; ++i)
	{
		fx->Workers[i] = i + 1;
		ThreadArray[i] = ::CreateThread(0, 0, static_cast<LPTHREAD_START_ROUTINE>(boole_qdrtr), fx, 0, &fx->ThIDArray[i]);
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