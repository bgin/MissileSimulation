#ifndef _SQUARE_WAVE_H_
#define _SQUARE_WAVE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Square Wave signal class - declaration.
@author: Bernard Gingold
@version:  1.0  19/09/2015

*/

#include "WaveformInterface.h"
#include "../MathLib/MathConstants.h"
#include "LibExceptions.h"
#include "Polarization.h"

namespace  radiolocation
{


	class SquareWaveSignal : public  Waveform
	{

	public:

		SquareWaveSignal() = default;
		/*
		@Brief Square Wave Signal Constructor.
		*/
	//_Raises_SEH_exception_	SquareWaveSignal(_In_ const double, _In_ const double, _In_ const double, _In_ const size_t, _In_ const int);

	_Raises_SEH_exception_  SquareWaveSignal(_In_  struct SquareWaveParams const&);
		/*
		@Brief: Square Wave Signal Copy-Constructor.
		*/
		SquareWaveSignal(_In_ const SquareWaveSignal &);
		/*
		@Brief: Square Wave Signal Move Constructor.
		*/
		SquareWaveSignal(_In_ SquareWaveSignal &&);
		/*
		@Brief: Destructor explicitly default.
		*/
		~SquareWaveSignal() {}
		

		/*
		@Brief: Copy-Assignment operator=
		*/
		SquareWaveSignal&     operator=(_In_ const SquareWaveSignal &);

		/*
		@Brief: Move-Assignment operator=
		*/
		SquareWaveSignal&     operator=(_In_ SquareWaveSignal &&);
		/*
		@Brief: Ostream operator<<
		*/
		friend   std::ostream&            operator<<(_In_ std::ostream&, _In_ const SquareWaveSignal &);

		/*
		@Brief: "Getter" class member function: get_squarewave()const
		*/
		_Outptr_opt_result_buffer_(m_samples)	__forceinline   std::vector<std::pair<double, double>>  get_squarewave() const;

		/*
		@Brief: "Getter" class member function.
		*/
		_Outptr_opt_result_buffer_(m_samples)		__forceinline   std::vector<double>                     get_phase() const;

		/*
		@Brief: "Getter" returns C-style pointer to vector[0].
		*/
	  _Outptr_opt_result_buffer_(m_samples)	__forceinline  const  double                                 *get_phase_ptr() const;
		/*
		@Brief: "Getter"  class member function.
		*/
		__forceinline    double                                 get_init_time() const;

		/*
		@Brief: "Getter" class member function: get_interval() const.
		*/
		__forceinline    double                                 get_interval() const;

		/*
		@Brief:  "Getter" class member function: get_amplitude() const.
		*/
		__forceinline    double                                 get_amplitude() const;

		/*
		@Brief: "Getter" class member function: get_samples() const.
		*/
		__forceinline    std::size_t                            get_samples() const;

		/*
		@Brief: Getter returns polarization vector.
		*/
		__forceinline    JonesVector                            polarization() const;

#if defined _DEBUG
		/*
		@ Pure virtual function implementation
		*/
		virtual     void        debug_print() const override;
#endif

#if defined  MATHEMATICA_VISUALIZE
		/*
		@Brief: Writes content of SquareWaveSignal to file.
		*/
_Raises_SEH_exception_	virtual	void        save_to_file(_In_z_ const char*, _In_z_ const char*) const;
#endif
/*
@Brief:  Returns approximately number of SquareWave cycles.
*/
double                          num_of_cycles() const;
/*
@Brief: Applies single functor to each of the vector components of SquareWaveSignal object.
Uses variadic templates and forwarding.Modifies *this in place.
*/
_Raises_SEH_exception_    template<typename _Fx, typename... _Ty> __forceinline  void   apply(_In_ _Fx, _In_ _Ty&&...);


/*
@Brief: Implementation of class inherited pure virtual functions.
*/

/*
@Brief: Class implementation of inherited pure virtual function Waveform::quadrature_components_extraction.
*/
_Raises_SEH_exception_      virtual              void            quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &, _In_ const int) override;
/*
@Brief: Class implementation of inherited pure virtual function Waveform::complex_envelope.
*/
_Raises_SEH_exception_      virtual              void            complex_envelope(_In_ std::vector<std::pair<double, double>> &, _Out_ std::vector<double> &) override;
/*
@Brief: Class implementation of inherited pure virtual function Waveform::analytic_signal.
*/
_Raises_SEH_exception_      virtual              void            analytic_signal(_In_ const std::vector<double> &, _In_ const int) override;

/*
@Brief: Class implementation pf inherited pure virtual function Waveform::instantaneous_frequency.
*/
_Raises_SEH_exception_      virtual              void            instantaneous_frequency(_Inout_ std::vector<double> &) override;

virtual     std::vector<std::pair<double, double>>                pulse_samples() const override;

virtual     std::vector<double>                                   pulse_phase() const override;

virtual     std::size_t                                           pulse_samples_count() const override;


virtual     void    amplitude_modulation(const double, const double, const double) override;

virtual     void    frequency_modulation(double, size_t) override;

virtual     void    phase_modulation(const double, const double, const double, std::function<double(double, double)>&) override;

	protected:

		/*
		@Brief: Square Wave signal.
		*/
	_Field_size_(m_samples)	std::vector<std::pair<double, double>> m_squarewave;
	

	/*
	@Brief:  Square Wave signal phase.
	*/
	_Field_size_(m_samples)	std::vector<double> m_phase;

	/*
	@Brief: start point
	*/
		double m_init_time;
		/*
		@Brief: interval increment.
		*/
		double m_interval;
		/*
		@Brief: Amplitude scalar value.
		*/

		double m_amplitude;
		/*
		@Brief: number of samples.
		*/
		std::size_t m_samples;

		/*
		@Brief: Polarization vector.
		*/
		JonesVector  m_polarization;

		/*
		@Brief: Creates Square Wave signal. Called from Constructor.
		*/

	//	void   create_signal(_In_ const double, _In_ const double, _In_ const double, _In_ const size_t, _In_ const int);

	_Raises_SEH_exception_  void   create_signal(_In_  struct SquareWaveParams const&);
		/*
		@Brief: Copies Square Wave signal. Called from Copy-Constructor.
		*/
		void   create_signal(_In_ const SquareWaveSignal &);

		/*
		@Brief: "Moves" content of other Square Wave Signal to *this.
		*/
		void   create_signal(_In_ SquareWaveSignal &&);

		static const  double  TWO_PI;
	};

	struct SquareWaveParams
	{
		_In_ double amplitude;
		_In_ double init_time;
		_In_ double interval;
		_In_ std::size_t n_samples;
		_In_ int n_threads;
	};

#include "SquareWave.inl"
}
#endif /*_SQUARE_WAVE_H_*/