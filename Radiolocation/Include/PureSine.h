#ifndef  _PURESINE_H_
#define  _PURESINE_H_



#include "WaveformInterface.h"
#include "LibExceptions.h"
#include "Polarization.h"
#include "../MathLib/MathConstants.h"

namespace  radiolocation
{

	class PureSineWave : public Waveform
	{

	public:

		
		PureSineWave() = default;

	_Raises_SEH_exception_  PureSineWave(_In_  struct PureSineParams const&);

	_Raises_SEH_exception_  PureSineWave(_In_ const double, _In_ const double, _In_ const double, _In_ const std::size_t);

		PureSineWave(_In_ PureSineWave const&);

		PureSineWave(_In_ PureSineWave &&);

		~PureSineWave()
		{

		}

		PureSineWave&              operator=(_In_ PureSineWave const&);

		PureSineWave&              operator=(_In_ PureSineWave &&);

	friend	std::ostream&              operator<<(_In_ std::ostream&, _In_ PureSineWave const&);

	template<typename _Fx, typename... _Ty> __forceinline PureSineWave&  apply(_In_ _Fx, _In_ _Ty&&...);

#if defined _DEBUG

	virtual           void           debug_print() const;
#endif

		_Field_size_(m_samples)	__forceinline  std::vector<std::pair<double, double>>  get_sine() const;

		_Field_size_(m_samples)	__forceinline  std::vector<double>                     get_phase() const;

		__forceinline  const double                           *get_phase_ptr() const;

		__forceinline        size_t                            get_samples() const;

		__forceinline        double                            get_init_time() const;

		__forceinline        double                            get_frequency() const;
		
		__forceinline        double                            get_interval() const;

		__forceinline        double                            get_amplitude() const;

		__forceinline        JonesVector                       polarization() const;

	//	virtual              void                              amplitude_modulation(const double, const double, const double);
		
	//	virtual              void                              phase_modulation(const double, const double, const double, std::function<double(double,double)>&);
			
		double                           n_cycles() const;

		double                           cycle_width() const;

		virtual              std::vector<std::pair<double, double>>     pulse_samples() const override;

		virtual              std::vector<double>                        pulse_phase() const override;

		virtual              std::size_t                                pulse_samples_count() const override;
	protected:

		_Field_size_(m_samples)	std::vector<std::pair<double, double>> m_sine;

		_Field_size_(m_samples) std::vector<double> m_phase;

		/*
		@Brief: number of sampling points.
		*/
		size_t m_samples;
		/*
		@Brief: Signal time step interval.
		*/
		double m_interval;
		/*
		@Brief: Signal starting time , t0.
		*/
		double m_init_time;
		/*
		@Brief: Bear in mind that this is not real signal frequency.
		*/
		double m_frequency;
		/*
		@Brief: Signal amplitude.
		*/
		double m_amplitude;

		/*
		@Brief: Signal linear vertical or horizontal polarization.
		*/
		JonesVector  m_polarization;

		const static double TWO_PI;

	

	_Raises_SEH_exception_  void  create_signal(_In_  struct PureSineParams const&);

	_Raises_SEH_exception_  void  create_signal(_In_ const double, _In_ const double, _In_ const double, _In_ const std::size_t);

		void  create_signal(_In_  PureSineWave const&);

		void  create_signal(_In_  PureSineWave &&);

		static    double    n_cycles(_In_ const std::size_t, _In_ const double);
	};

	/*
	@Brief Aggregated parameters structure.
	*/
	struct PureSineParams
	{
		_In_ double amplitude;
		_In_ double init_time;
		_In_ double interval;
		_In_ double freq;
		_In_ std::size_t n_samples;
		_In_ int n_threads;
	};

#include "PureSine.inl"
}
#endif /*_PURESINE_H_*/