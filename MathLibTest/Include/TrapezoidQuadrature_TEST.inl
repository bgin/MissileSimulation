
template<typename Function>  __forceinline  double test::TrapezoidQuadratureTest::Integral(Function integral, const double arg)
{
	return integral(arg);
}

