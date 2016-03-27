
/*          *** Notice!! ***

             Unfortunately ICC do not fully support constexpr static array
			 so in this case these arrays were declared const and they are 
			 initialized out-of-class.
*/
template<typename T> const typename T atmosphere::PhysConsts<T>::htab[atmosphere::PhysConsts<T>::NTAB] = { T(0.0), T(11.0), T(20.0), T(32.0),
T(47.0), T(51.0), T(71.0), T(84.852) };

template<typename T> const typename T atmosphere::PhysConsts<T>::ttab[atmosphere::PhysConsts<T>::NTAB] = { T(288.15), T(216.65), T(216.65), T(228.65),
T(270.65), T(270.65), T(214.65), T(186.964) };

template<typename T> const typename T atmosphere::PhysConsts<T>::ptab[atmosphere::PhysConsts<T>::NTAB] = { T(1.0), T(2.2336110E-1), T(5.4032950E-2), T(8.5666784E-3),
T(1.0945601E-3), T(6.6063531E-4), T(3.9046834E-5), T(3.68501E-6) };

template<typename T> const typename T atmosphere::PhysConsts<T>::gtab[atmosphere::PhysConsts<T>::NTAB] = { T(-6.5), T(0.0), T(1.0), T(2.8), T(0.0), T(-2.8),
T(-2.0), T(0.0) };
