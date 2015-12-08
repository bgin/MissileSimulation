


DWORD WINAPI mathlib::MTTrpzd::trpzd_qdrtr(LPVOID lpvoid)
{
	_ASSERT(lpvoid != nullptr);

	double h = 0.0L, term = 0.0L, sum = 0.0L;
	unsigned int start;
	Fx * fx = static_cast<Fx*>(lpvoid);

	if (1 >= fx->num_steps)
		throw std::runtime_error("Fatal Error in trpzd_qdrtr: 1 >= num_steps\n");

	start = *static_cast<unsigned int*>(fx->Workers);
	h = (fx->b - fx->a) / static_cast<double>(fx->num_steps);
	sum = 0.5L * (fx->b - fx->a) * (fx->fptr(fx->a) + fx->fptr(fx->b));
	
	for (auto i = start; i < fx->num_steps; i += fx->NWorkers)
	{
		double x = fx->a + h * static_cast<double>(i);
		sum += fx->fptr(x);
		//std::printf("sum=%.15f\n", sum);
		//std::printf("start=%d, num_steps=%d\n", start, fx->num_steps);
	}
	
	sum *= h;
	::EnterCriticalSection(&fx->cs);
	fx->result += sum;
	//std::printf("result=%.15f\n",qr1.result );
	::LeaveCriticalSection(&fx->cs);

	return 0;
}

double  __forceinline  mathlib::MTTrpzd::run_computation(Fx * fx)
{
	_ASSERT(fx != nullptr);
	double qdrtr_approx = std::numeric_limits<double>::quiet_NaN();
	
	HANDLE * ThreadArray = new HANDLE[fx->NWorkers];
	::InitializeCriticalSection(&fx->cs);
	for (auto i = 0; i != fx->NWorkers; ++i)
	{
		fx->Workers[i] = i + 1;
		ThreadArray[i] = ::CreateThread(0, 0, static_cast<LPTHREAD_START_ROUTINE>(trpzd_qdrtr), fx, 0, &fx->ThIDArray[0]);
		if (NULL == ThreadArray[i])
		{
			std::printf("::CreateThread failed with an error %d\n", ::GetLastError());
			::ExitProcess(1);
		}
	}
	::WaitForMultipleObjects(fx->NWorkers, ThreadArray, TRUE, INFINITE);
	for (auto i = 0; i != fx->NWorkers; ++i) ::CloseHandle(ThreadArray[i]);

	delete[] ThreadArray;
	qdrtr_approx = fx->result;
	return qdrtr_approx;
}