

auto   test_internal_system::TEST_FastSSEMemCpyF32::test_sse_mem_cpy_f32()->void {

	std::cout << "***Acceptance test of sse_mem_cpy_f32 function***" << std::endl;
	std::cout << "TEST no. #1 -- Data caching in L1D Cache --." << std::endl;
	std::cout << "Allocating memory... ";
	constexpr int dataSize{ 4096 };
	float* pDataIn = new float[dataSize];
	float* pDataOut = new float[dataSize];
	std::cout << "Done" << std::endl;
	std::cout << "Allocated " << 2 * dataSize * sizeof(float) << " bytes of heap memory." << std::endl;
	std::cout << "pDataIn at: " << "0x" << &pDataIn << std::endl;
	std::cout << "pDataOut at: " << "0x" << &pDataOut << std::endl;
	std::cout << "Initializing arrays...  ";
	clock_t seed{ clock() };
	auto rand = std::bind(std::uniform_real_distribution<float>{}, std::default_random_engine(seed));
	
	std::fill(pDataOut, pDataOut + dataSize, 0.F);
	for (int i{ 0 }; i != dataSize; ++i) pDataIn[i] = rand();
	std::cout << "Done!!" << std::endl;
	std::cout << "Calling sse_mem_cpy_f32 function. " << std::endl;
	std::cout << "Copying " << 2 * dataSize * sizeof(float) << " bytes... ";
	internal_system::FastSSEMemCpy<float, 0>::sse_mem_cpy_f32(pDataIn, pDataOut, dataSize);
#if 0
	test_internal_system::utilities::printData(&pDataOut[0], dataSize);
#endif
	std::cout << "Done!!" << std::endl;
	std::cout << "Deallocating resources... ";
	delete[] pDataIn;
	delete[] pDataOut;
	std::cout << "Done " << std::endl;
	std::cout << "End of TEST no. #1" << std::endl;
	std::cout << std::endl;
	std::cout << "TEST no. #2 -- Data caching in L2 Cache --" << std::endl;
	std::cout << "Allocating memory... ";
	constexpr int dataSize2{ dataSize * 16 };
	float* pDataIn2 = new float[dataSize2];
	for (int i{ 0 }; i != dataSize2; ++i) pDataIn2[i] = rand();
	//float* pDataOut2 = new float[dataSize2];
	std::unique_ptr<float, void(*)(float*)> sptrIn(pDataIn2, [](float* p)->void {delete[]p; });
	std::unique_ptr<float, void(*)(float*)> sptrOut(new float[dataSize2], [](float* p)->void {delete[]p; });
	std::cout << "Done!!" << std::endl;
	std::cout << "Allocated: " << 2 * dataSize2 * sizeof(float) << " bytes of heap memory" << std::endl;
	std::cout << "Input pointer  at:" << &pDataIn2 << std::endl;
	std::cout << "Output pointer at:" << &sptrOut.get()[0] << std::endl;
	std::cout << "Initialization of std::unique_ptr pointed arrays... ";
	std::fill(&sptrOut.get()[0], &sptrOut.get()[0] + dataSize2, 0.F);
	std::cout << "Calling sse_mem_cpy_f32 function " << std::endl;
	std::cout << "Copying " << 2 * dataSize2 * sizeof(float) << " bytes... ";
	internal_system::FastSSEMemCpy<float, 0>::sse_mem_cpy_f32(&sptrIn.get()[0], &sptrOut.get()[0], dataSize2);
#if 0
	test_internal_system::utilities::printData(&sptrOut.get()[0], dataSize2);
#endif
	std::cout << "Done!!" << std::endl;
	std::cout << "End of TEST no. #2" << std::endl;
}

auto    test_internal_system::TEST_FastSSEMemCpyF32::test_sse_mem_cpy_f324x()->void {

	std::cout << "*** Acceptance Test of sse_mem_cpy_f324x function ***" << std::endl;
	std::cout << "TEST no. #1 -- Data caching in L1D Cache --." << std::endl;
	std::cout << "Allocating... ";
	constexpr int dataSize{ 1 << 12 };
	float* pDataIn = new float[dataSize];
	float* pDataOut = new float[dataSize];
	std::cout << "Done!!" << std::endl;
	std::cout << "Allocated: " << 2 * dataSize * sizeof(float) << " bytes of heap memory." << std::endl;
	std::cout << "pDataIn at: " << "0x" << &pDataIn << std::endl;
	std::cout << "pDataOut at:" << "0x" << &pDataOut << std::endl;
	std::cout << "Initializing arrays... ";
	clock_t seed{ clock() };
	auto rand = std::bind(std::uniform_real_distribution<float>{}, std::default_random_engine(seed));
	std::fill(pDataOut, pDataOut + dataSize, 0.F);
	for (int i{ 0 }; i != dataSize; ++i) pDataIn[i] = rand();
	std::cout << "Done!!" << std::endl;
	std::cout << "Calling sse_mem_cpy_f324x function. " << std::endl;
	std::cout << "Copying " << 2 * dataSize * sizeof(float) << " bytes... ";
	internal_system::FastSSEMemCpy<float, 0>::sse_mem_cpy_f324x(&pDataIn[0], &pDataOut[0], dataSize);
	std::cout << "Done!!" << std::endl;
#if 0
	test_internal_system::utilities::printData(&pDataOut[0], dataSize);
#endif
	
	std::cout << "Deallocating resources... ";
	delete[] pDataIn;
	delete[] pDataOut;
	std::cout << "Done " << std::endl;
	std::cout << "End of TEST no. #1" << std::endl;
	std::cout << std::endl;
	std::cout << "TEST no. #2 -- Data caching in L2 Cache --" << std::endl;
	std::cout << "Allocating memory... ";
	constexpr int dataSize2{ dataSize * 16 };
	float* pDataIn2 = new float[dataSize2];
	for (int i{ 0 }; i != dataSize2; ++i) pDataIn2[i] = rand();
	std::unique_ptr<float, void(*)(float*)> sptrIn(pDataIn2, [](float* ptr)->void {delete[]ptr; });
	std::unique_ptr<float, void(*)(float*)> sptrOut(new float[dataSize2], [](float* ptr)->void {delete[] ptr; });
	
	
	
	std::cout << "Done!!" << std::endl;
	std::cout << "Allocated: " << 2 * dataSize2 * sizeof(float) << " bytes of heap memory." << std::endl;
	std::cout << "pDataIn at: " << "0x" << &pDataIn << std::endl;
	std::cout << "pDataOut at:" << "0x" << &sptrOut.get()[0] << std::endl;
	std::cout << "Initializing std::uniue_ptr pointed array... ";
	std::fill(&sptrOut.get()[0], &sptrOut.get()[0] + dataSize2, 0.F);
	std::cout << "Calling sse_mem_cpy_f32 function " << std::endl;
	std::cout << "Copying " << 2 * dataSize2 * sizeof(float) << " bytes... ";
	internal_system::FastSSEMemCpy<float, 0>::sse_mem_cpy_f324x(&sptrIn.get()[0], &sptrOut.get()[0], dataSize2);
#if 0
	test_internal_system::utilities::printData(&sptrOut.get()[0], dataSize2);
#endif
	std::cout << "Done!!" << std::endl;
	std::cout << "End of TEST no. #2" << std::endl;

}