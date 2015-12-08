#ifndef _SQUARE_WAVE_MODULATED_H_
#define _SQUARE_WAVE_MODULATED_H_

#include "WaveformInterface.h"
#include "../MathLib/MathConstants.h"
#include "LibExceptions.h"
#include "Polarization.h"

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
 Square Wave Modulated signal class - declaration.
@author: Bernard Gingold
@version:  1.0  25/09/2015

*/
namespace  radiolocation
{

	class SquareWaveMSignal : public  Waveform
	{

      
	public:

		SquareWaveMSignal() = default;
		/*
		@Brief: "Main" Class Constructor. Invokes create_signal setup function.
		*/
	_Raises_SEH_exception_	 SquareWaveMSignal(_In_ std::function<double(double)> &, _In_ const double, _In_ const double, _In_ const double, _In_ const double,
			_In_ const double, _In_ const double, _In_ const double, _In_ const std::size_t, _In_ const int);

	_Raises_SEH_exception_   SquareWaveMSignal(_In_  struct SquareWaveMParams const&);

	                        /*
	                        @Brief:  Copy-Constructor.
							*/
	                         SquareWaveMSignal(_In_ const SquareWaveMSignal &);

							 /*
							 @Brief:  Move-Constructor.
							 */
							 SquareWaveMSignal(_In_ SquareWaveMSignal &&);

							 /*
							 @Brief:  Destructor - explicitly default.
							 */
							 ~SquareWaveMSignal() {} // weird error appears when default initialization is in use.
							 

							 

							 /*
							 @Brief: Accessor functions.
							 */
							 
							 /*
							 @Brief: Returns this->m_square_wave.
							 */
							 _Outptr_opt_result_buffer_(m_samples)					 __forceinline  std::vector<std::pair<double, double>>  get_m_square_wave() const;

							 /*
							 @Brief: Returns this->m_envelope.
							 */
							 _Outptr_opt_result_buffer_(m_samples)                   __forceinline  std::vector<double>                     get_envelope() const;

							 /*
							 @Brief: Returns  this->m_phase
							 */
							 _Outptr_opt_result_buffer_(m_samples)                   __forceinline  std::vector<double>                     get_phase() const;

							 /*
							 @Brief: Returns this->m_samples.
							 */
							 __forceinline            std::size_t                    get_samples() const;

							 /*
							 @Brief:  Returns this->m_sfrequency.
							 */
							 __forceinline             double                         get_sfrequency() const;

							 /*
							 @Brief:  Returns this->m_envfrequency
							 */
							 __forceinline              double                        get_envfrequency() const;

							 /*
							 @Brief:  Returns this->m_init_phase
							 */
							 __forceinline              double                        get_init_phase() const;

							 /*
							 @Brief:  Returns this->m_sinit_time.
							 */
							 __forceinline              double                        get_sinit_time() const;

							 /*
							 @Brief:  Returns this->m_einit_time.              
							 */
							 __forceinline              double                        get_einit_time() const;

							 /*
							 @Brief:  Returns this->m_sinterval.
							 */
							 __forceinline              double                        get_sinterval() const;

							 /*
							 @Brief:  Returns  this->m_einterval
							 */
							 __forceinline              double                        get_einterval() const;

							 /*
							 @Brief:
							 */
							 __forceinline             std::function<double(double)>  get_gen_function() const;

							 /*
							 @Brief: Applies 3 functors to each of the vector components of SquareWaveMSignal object.
							 Uses variadic templates and forwarding.Modifies *this in place.
							 */
							 _Raises_SEH_exception_  template<typename _Fx1, typename _Fx2, typename _Fx3, typename... _Ty> __forceinline void  apply(_In_ _Fx1, _In_ _Fx2, _In_ _Fx3,
								 _In_ _Ty&&...);

							 /*
							 @Brief: Applies 3 functors to each of the vector components of SquareWaveMSignal object.
							 incorporates std::for_each.
							 */
							 _Raises_SEH_exception_  template<typename _Fx1, typename _Fx2, typename _Fx3, typename _Ty> __forceinline  void  apply(_In_ _Fx1, _In_ const _Ty&,
								 _In_ _Fx2, _In_ const _Ty&, _In_ _Fx3, _In_ const _Ty&);

							 /*
							 @Brief:  Applies lambda functor to each of the vector components of SquareWaveMSignal.
							 */
							 template<typename _Fx>  __forceinline  static void  apply(_Inout_ SquareWaveMSignal &, _In_ _Fx);

							 /*
							 @Brief: operator copy - assignment
							 */
							 SquareWaveMSignal&      operator=(_In_ const SquareWaveMSignal &);

							 /*
							 @Brief: operator move - assignment.
							 */
							 SquareWaveMSignal&       operator=(_In_ SquareWaveMSignal &&);

							 /*
							 "Brief: operator<< 
							 */
							 friend  std::ostream&    operator<<(_In_ std::ostream&, _In_ const SquareWaveMSignal &);

							 /*
							 @Brief: inherited pure virtual functions implementations.
							 */
#if defined _DEBUG
							 /*
							 @ Pure virtual function implementation
							 */
							 virtual      void         debug_print() const override;
#endif

							 /*
							 @Brief: Class implementation of inherited pure virtual function Waveform::quadrature_components_extraction.
							 */
							 _Raises_SEH_exception_		 virtual      void         quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &, _In_ const int) override;

							 /*
							 @Brief: Class implementation of inherited pure virtual function Waveform::complex_envelope.
							 */
							 _Raises_SEH_exception_       virtual     void         complex_envelope(_In_ std::vector<std::pair<double, double>> &, _Out_ std::vector<double> &) override;

							 /*
							 @Brief: Class implementation of inherited pure virtual function Waveform::analytic_signal.
							 */
							 _Raises_SEH_exception_       virtual     void         analytic_signal(_In_ const std::vector<double> &, _In_ const int) override;

							 /*
							 @Brief: Class implementation pf inherited pure virtual function Waveform::instantaneous_frequency.
							 */
							 _Raises_SEH_exception_       virtual     void         instantaneous_frequency(_Inout_ std::vector<double> &) override;

							 virtual               std::vector<std::pair<double, double>>    pulse_samples() const override;

							 virtual               std::vector<double>                       pulse_phase() const override;

							 virtual               std::size_t                               pulse_samples_count() const override;

#if defined  MATHEMATICA_VISUALIZE
							 _Raises_SEH_exception_      virtual void                      save_to_file(_In_z_ const char*, _In_z_ const char*, _In_z_ const char*) const;
#endif
	protected:

		// SquareWaveMSignal itself.
		_Field_size_(m_samples) std::vector<std::pair<double, double>> m_square_wave;

		// phase component signal phi(t).
		_Field_size_(m_samples) std::vector<double> m_envelope;

		// modulating envelope signal r(t).
		_Field_size_(m_samples) std::vector<double> m_phase;

		    // number of samples
			std::size_t  m_samples;

			// signal frequency.
			double  m_sfrequency;

			// modulating envelope frequency, when m_envfrequency < m_sfrequency.
			double  m_envfrequency;
            
			// signal initial phase, ie. sine wave generating function initial phase.
			double  m_init_phase;

			// signal starting time.
			double  m_sinit_time;

			// modulating envelope starting time.
			double  m_einit_time;

			// signal time interval increment.
			double  m_sinterval;

			// modulating envelope time interval increment. This interval must be less than signal time step.
			double  m_einterval;

			// modualting envelope waveform generating function.
			std::function<double(double)> m_gen_function;

			// Polarization Vector
			JonesVector  m_polarization;

			// static TWO_PI.
			const static  double TWO_PI;

			/*
			@Brief: Create Signal  functions. Initializes object with user - passed arguments. Called from the Constructor.
			*/
			_Raises_SEH_exception_  void    create_signal(_In_ std::function<double(double)> &, _In_ const double, _In_ const double, _In_ const double,
				_In_ const double, _In_ const double, _In_ const double, _In_ const double, _In_ const std::size_t, _In_ const int);

			_Raises_SEH_exception_  void    create_signal(_In_  struct  SquareWaveMParams const&);

			/*
			@Brief:  Copies content of SquareWaveMSignal object. Called from the Copy-Constructor.
			*/
			void                            create_signal(_In_ const SquareWaveMSignal &);

			/*
			@Brief: Moves content of SquareWaveMSignal object. Called from the Move-Constructor.
			*/
			void                            create_signal(_In_ SquareWaveMSignal &&);
	};

	struct SquareWaveMParams
	{
		_In_  std::function<double(double)> gen_function;
		_In_  double sfreq;
		_In_  double envfreq;
		_In_  double init_phase;
		_In_  double sinit_time;
		_In_  double einit_time;
		_In_  double sinterval;
		_In_  double einterval;
		_In_  std::size_t n_samples;
		_In_  int n_threads;
	};


#include "SquareWaveModulated.inl"
}
#endif  /*_SQUARE_WAVE_MODULATED_H_*/