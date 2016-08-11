
auto   test_internal_system::utilities::printData(_In_ const float* data, _In_ const int dataSize)->void {

	/*
	No input checking
	*/
	
	std::cout << "Begining dump of memory at address: " << &data << std::endl;
	for (int i{ 0 }; i != dataSize; ++i)
		std::cout << "data[" << i << "] " << data[i] << " at address " << &data[i] << std::endl;
	std::cout << "End of memory dump" << std::endl;
}