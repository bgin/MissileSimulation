#ifndef _WAVEFORM_INTERFACE_H_
#define _WAVEFORM_INTERFACE_H_

#include "RadLibDefs.h"

namespace radiolocation
{

	// Abstract Waveform class.
	class Waveform
	{

	public:



		virtual  void  amplitude_modulation(const double, const double, const double) = 0;

		

		virtual  void  phase_modulation(const double, const double, const double, std::function<double(double,double)>&) = 0;

		

		virtual  void  frequency_modulation(double, size_t) = 0;

		
	_Raises_SEH_exception_	virtual  void  quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &, _In_ const int) = 0;


	_Raises_SEH_exception_	virtual  void  complex_envelope(_In_ std::vector<std::pair<double, double>> &, _Out_ std::vector<double> &) = 0;


	_Raises_SEH_exception_	virtual  void  analytic_signal(_In_ const std::vector<double> &, _In_ const int) = 0;


	_Maybe_raises_SEH_exception_	virtual  void  instantaneous_frequency(_Inout_ std::vector<double> &) = 0;


	virtual                    std::vector<std::pair<double, double>>  pulse_samples() const = 0;

	virtual                    std::vector<double>                     pulse_phase() const = 0;

	virtual                    std::size_t                             pulse_samples_count() const = 0;

#if defined _DEBUG
		  
	   virtual	void  debug_print() const = 0;
#endif

		virtual ~Waveform();
	};
}

#endif /*_WAVEFORM_INTERFACE_H_*/