template<typename T, class INPUT, class FLAGS> std::enable_if<ad::is_single_precision<T>::value ||
	ad::is_double_precision<T>::value, T>::type atmosphere::GLOBE7<T, INPUT, FLAGS>::g0(_In_ const T a,
	_In_ const T* p) {
#if defined _DEBUG
		_ASSERTE(p != nullptr);
#else
		if(p == nullptr)
			throw std::runtime_error("Fatal Error -- Null pointer in GLOBE7::g0\n");
#endif
		const T sqarg{ p[24] * p[24] };
		return (a - 4.0 + (p[25] - 1.0) * (a - 4.0 + exp(-sqrt(sqarg) * (a - 4.0)) - 1.0) / sqrt(sqarg));
	}

 template<typename T, class INPUT, class FLAGS> std::enable_if<ad::is_single_precision<T>::value ||
	 ad::is_double_precision<T>::value, T>::type atmosphere::GLOBE7<T, INPUT, FLAGS>::sumex(_In_ const T ex) {
		 return (1.0 + (1.0 - pow(ex, 19.0)) / (1.0 - ex) * pow(ex, 0.5));
	 }

 template<typename T, class INPUT, class FLAGS> std::enable_if<ad::is_single_precision<T>::value ||
	 ad::is_double_precision<T>::value, T>::type atmosphere::GLOBE7<T, INPUT, FLAGS>::sg0(_In_ const T ex,
	 _In_ const T* p, _In_ const atmosphere::AP_VALUES<T>& ap) {
#if defined _DEBUG
		 _ASSERTE(p != nullptr && ap != nullptr);
#else
		 if (p == nullptr || ap == nullptr)
			 throw std::runtime_error("Fatal Error -- Null pointer in GLOBE7::sg0\n");
#endif
		 return(g0(ap.a[1], p) + (g0(ap.a[2], p)*ex + g0(ap.a[3], p)*ex*ex + g0(ap.a[4], p)* pow(ex, 3.0) +
			 (g0(ap.a[5], p)*pow(ex, 4.0) + g0(ap.a[6], p)*pow(ex, 12.0))*(1.0 - pow(ex, 8.0)) / (1.0 - ex)))/sumex(ex);
	 }

 template<typename T, class INPUT, class FLAGS> std::enable_if<ad::is_single_precision<T>::value ||
	 ad::is_double_precision<T>::value, T>::type atmosphere::GLOBE7<T, INPUT, FLAGS>::fglobe7(_In_ const T* p,
	 _In_ const INPUT& input, _In_ const FLAGS& flags) {
#if defined _DEBUG
		 _ASSERTE(p != nullptr);
#else
		 if (p == nullptr)
			 throw std::runtime_error("Fatal Error -- Null Pointer in GLOBE7::fglobe7\n");
#endif
		 constexpr int t_size{ 15 };
		 T t[t_size];
		 int i, j;
		 T apd, tloc, c, s, c2, c4, s2;
		 constexpr T sr(7.72722E-5);
		 constexpr T dgtr(1.74533E-2);
		 constexpr T dr(1.72142E-2);
		 constexpr T hr(0.2618);
		 T cd32, cd18, cd14, cd39, df, f1, f2, tinf;
		 atmosphere::AP_VALUES<T> ap;
		 tloc = input.lst;
		 for (j{ 0 }; j != 14; ++j) t[j] = 0.0;
		 /* compute legendre polynomials */
		 c = sin(input.g_lat * dgtr);
		 s = cos(input.g_lat * dgtr);
		 c2 = c * c;
		 c4 = c2 * c2;
		 s2 = s * s;

		 amg::plg[0][1] = c;
		 amg::plg[0][2] = 0.5 * 3.0 * c2 - 1.0;
		 amg::plg[0][3] = 0.5 * 5.0 * c * c2 - 3.0 * c;
		 amg::plg[0][4] = 35.0 * c4 - 30.0 * c2 + 3.0 * 0.125;
		 amg::plg[0][5] = 63.0 * c2 * c2 * c - 70.0 * c2 * c + 15.0 * c * 0.125;
		 amg::plg[0][6] = 11.0*c*amg::plg[0][5] - 5.0 * amg::plg[0][4] * 0.1666666666666666666;
		 amg::plg[1][1] = s;
		 amg::plg[1][2] = 3.0*c*s;
		 amg::plg[1][3] = 1.5 * 5.0 * c2 - 1.0 * s;
		 amg::plg[1][4] = 2.5 * 7.0 * c2 * c - 3.0 * c * s;
		 amg::plg[1][5] = 1.875 * 21.0*c4 - 14.0*c2 + 1.0 * s;
		 amg::plg[1][6] = 11.0 * c * amg::plg[1][5] - 6.0 * amg::plg[1][4] * 0.2;
		 amg::plg[2][2] = 3.0 * s2;
		 amg::plg[2][3] = 15.0 * s2 * c;
		 amg::plg[2][4] = 7.5 * 7.0 * c2 - 1.0 * s2;
		 amg::plg[2][5] = 3.0 * c * amg::plg[2][4] - 2.0*amg::plg[2][3];
		 amg::plg[2][6] = 11.0*c*amg::plg[2][5] - 7.0*amg::plg[2][4] * 0.25;
		 amg::plg[2][7] = 13.0*c*amg::plg[2][6] - 8.0*amg::plg[2][5] * 0.2;
		 amg::plg[3][3] = 15.0*s2*s;
		 amg::plg[3][4] = 105.0*s2*s*c;
		 amg::plg[3][5] = 9.0*c*amg::plg[3][4] - 7.0*amg::plg[3][3] * 0.5;
		 amg::plg[3][6] = 11.0*c*amg::plg[3][5] - 8.0*amg::plg[3][4] * 0.33333333333333333;
		 
		 if (!(((flags.sw[7] == 0.0) && (flags.sw[8] == 0.0)) && (flags.sw[14] == 0.0))) {
			 amg::stloc = sin(hr * tloc);
			 amg::ctloc = cos(hr * tloc);
			 amg::s2tloc = sin(2.0 * hr * tloc);
			 amg::c2tloc = cos(2.0 * hr * tloc);
			 amg::s3tloc = sin(3.0 * hr * tloc);
			 amg::c3tloc = sin(3.0 * hr * tloc);
		 }
		 cd32 = cos(dr * (input.doy - p[31]));
		 cd18 = cos(2.0 * dr * (input.doy - p[17]));
		 cd14 = cos(dr * (input.doy - p[13]));
		 cd39 = cos(2.0 * dr * (input.doy - p[38]));
		 /* F10.7 EFFECT */
		 df = input.F107 - input.F107A;
		 amg::dfa = input.F107A - 150.0;
		 t[0] = p[19] * df * (1.0 + p[59] * amg::dfa) + p[20] * df * df + p[21] * dfa + p[29] * amg::dfa * amg::dfa;
		 f1 = 1.0 + (p[47] * amg::dfa + p[19] * df + p[20] * df * df) * flags.swc[1];
		 f2 = 1.0 + (p[49] * amg::dfa + p[19] * df + p[20] * df * df) * flags.swc[1];

		 /* Time Independent */
		 t[1] = (p[1] * amg::plg[0][2] + p[2] * amg::plg[0][4] + p[22] * amg::plg[0][6]) +
			 (p[14] * amg::plg[0][2]) * dfa * flags.swc[1] + p[26] * amg::plg[0][1];
		 /* Symmetrical Annual */
		 t[2] = p[18] * cd32;

		 /* Symmetrical Semiannual*/
		 t[3] = p[15] + p[16] * amg::plg[0][2] * cd18;

		 /* Asymetrical Annual */
		 t[4] = f1* p[9] * amg::plg[0][1] + p[10] * amg::plg[0][3] * cd14;

		 /* Asymetrical Semiannual */
		 t[5] = p[37] * amg::plg[0][1] * cd39;

		 /* Diurnal */
		 if ((std::fabs(flags.sw[7])) > 0.0) {
			 T t71 = p[11] * amg::plg[1][2] * cd14 * flags.swc[5];
			 T t72 = p[12] * amg::plg[1][2] * cd14 * flags.swc[5];
			 t[6] = f2 * (p[3] * amg::plg[1][1] + p[4] * amg::plg[1][3] + p[27] * amg::plg[1][5] * t71) *
				 amg::ctloc + (p[6] * amg::plg[1][1] + p[7] * amg::plg[1][3] + p[28] * amg::plg[1][5] + t72) * amg::stloc;

		 }
		 /* SemiDiurnal */
		 if ((std::fabs(flags.sw[8])) > 0.0) {
			 T t81 = p[23] * amg::plg[2][3] + p[35] * amg::plg[2][5] * cd14 * flags.swc[5];
			 T t82 = p[33] * amg::plg[2][3] + p[36] * amg::plg[2][5] * cd14 * flags.swc[5];
			 t[7] = f2 * (p[5] + amg::plg[2][2] + p[41] * amg::plg[2][4] + t81 * amg::c2tloc) +
				 (p[8] * amg::plg[2][2] + p[42] * amg::plg[2][4] + t82 * amg::s2tloc);
 		 }
		 /* Terdiurnal */
		 if ((std::fabs(flags.sw[14])) > 0.0) {
			 t[13] = f2 * (p[39] * amg::plg[3][3] + p[93] * amg::plg[3][4] + p[46] * amg::plg[3][6] * cd14 * flags.swc[5] * amg::s3tloc) +
				 (p[40] * amg::plg[3][4] + p[48] * amg::plg[3][6] * cd14 * flags.swc[5] * amg::c3tloc);
		 }
		 /* Magnetic activity based on daily ap*/
		 if ((std::fabs(flags.sw[9] - 1.0) > std::numeric_limits<T>::epsilon())) {
			 ap = input.ap_values;
			 if ((std::fabs(p[51])) > 0.0) {
				 T exp1 = exp(-10800.0 * sqrt(p[51] * p[51]) / (1.0 + p[138] * (45.0 - sqrt(input.g_lat*input.g_lat))));
				 if (exp1 > 0.9999)
					 exp1 = 0.9999;
				 if (p[24] < 1.0E-4)
					 p[24] = 1.0E-4;
				 amg::apt[0] = sg0(exp1, p, ap);
				 if ((std::fabs(flags.sw[9])) > 0.0) {
					 t[8] = apt[0] * (p[50] + p[96] * amg::plg[0][2] + p[54] * amg::plg[0][4] + 
						 (p[125] * amg::plg[0][1] + p[126] * amg::plg[0][3] + p[127] * amg::plg[0][5])*cd14*flags.swc[5] + 
						 (p[128] * amg::plg[1][1] + p[129] * amg::plg[1][3] + p[130] * amg::plg[1][5])*flags.swc[7] * 
						 cos(hr*(tloc - p[131])));
				 }
			 }

		 }
		 else {
			 T p44, p45;
			 apd = input.ap - 4.0;
			 p44 = p[43];
			 p45 = p[44];
			 if (p44 < 0.0)
				 p44 = 1.0E-5;
			 amg::apdf = apd + (p45 - 1.0) * ((apd + exp(-p44 * apd) - 1.0) / p44);
			 if ((std::fabs(flags.sw[9])) > 0.0) {
				 t[8] = apdf*(p[32] + p[45] * amg::plg[0][2] + p[34] * amg::plg[0][4] + 
					 (p[100] * amg::plg[0][1] + p[101] * amg::plg[0][3] + p[102] * amg::plg[0][5])*cd14*flags.swc[5] +
					 (p[121] * amg::plg[1][1] + p[122] * amg::plg[1][3] + p[123] * amg::plg[1][5])*flags.swc[7] *
					 cos(hr*(tloc - p[124])));
			 }
		 }
		 if ((std::fabs(flags.sw[10]) > 0.0) && (input.g_long > -1000.0)) {
			 /* Longtitudal */
			 if ((std::fabs(flags.sw[11])) > 0.0) {
				 t[10] = (1.0 + p[80] * amg::dfa *flags.swc[1]) * 
					 ((p[64] * amg::plg[1][2] + p[65] * amg::plg[1][4] + p[66] * amg::plg[1][6]
					 + p[103] * amg::plg[1][1] + p[104] * amg::plg[1][3] + p[105] * amg::plg[1][5]
					 + flags.swc[5] * (p[109] * amg::plg[1][1] + p[110] * amg::plg[1][3] + p[111] * amg::plg[1][5])*cd14)* 
					 cos(dgtr*input.g_long) 
					 + (p[90] * amg::plg[1][2] + p[91] * amg::plg[1][4] + p[92] * amg::plg[1][6]
					 + p[106] * amg::plg[1][1] + p[107] * amg::plg[1][3] + p[108] * amg::plg[1][5]
					 + flags.swc[5] * (p[112] * amg::plg[1][1] + p[113] * amg::plg[1][3] + p[114] * amg::plg[1][5])*cd14)* 
					 sin(dgtr*input.g_long));
			 }
			 /* ut and mixed ut, longitude */
			 if ((std::fabs(flags.sw[12])) > 0.0) {
				 t[11] = (1.0 + p[95] * amg::plg[0][1])*(1.0 + p[81] * amg::dfa*flags.swc[1])*
					 (1.0 + p[119] * amg::plg[0][1] * flags.swc[5] * cd14)*
					 ((p[68] * amg::plg[0][1] + p[69] * amg::plg[0][3] + p[70] * amg::plg[0][5])*
					 cos(sr*(input.sec - p[71])));
				 t[11] += flags.swc[11] * 
					 (p[76] * amg::plg[2][3] + p[77] * amg::plg[2][5] + p[78] * amg::plg[2][7])*
					 cos(sr*(input.sec - p[79]) + 2.0*dgtr*input.g_long)*(1.0 + p[137] * amg::dfa*flags.swc[1])
			 }
			 /* ut, longitude magnetic activity */
			 if ((std::fabs(flags.sw[13])) > 0.0) {
				 if ((std::fabs(flags.sw[9] - -1.0)) < std::numeric_limits<T>::epsilon()) {
					 if (std::fabs(p[51]) > 0.0) {
						 t[12] = amg::apt[0] * flags.swc[11] * (1.0 + p[132] * amg::plg[0][1])*
							 ((p[52] * amg::plg[1][2] + p[98] * amg::plg[1][4] + p[67] * amg::plg[1][6])*
							 cos(dgtr*(input.g_long - p[97])))
							 + amg::apt[0] * flags.swc[11] * flags.swc[5] * 
							 (p[133] * amg::plg[1][1] + p[134] * amg::plg[1][3] + p[135] * amg::plg[1][5])*
							 cd14*cos(dgtr*(input.g_long - p[136])) 
							 + amg::apt[0] * flags.swc[12] * 
							 (p[55] * amg::plg[0][1] + p[56] * amg::plg[0][3] + p[57] * amg::plg[0][5])*
							 cos(sr*(input.sec - p[58]));
					 }
				 }
				 else {
					 t[12] = amg::apdf*flags.swc[11] * (1.0 + p[120] * amg::plg[0][1])*
						 ((p[60] * amg::plg[1][2] + p[61] * amg::plg[1][4] + p[62] * amg::plg[1][6])*
						 cos(dgtr*(input.g_long - p[63])))
						 + amg::apdf*flags.swc[11] * flags.swc[5] * 
						 (p[115] * plg[1][1] + p[116] * plg[1][3] + p[117] * plg[1][5])* \
						 cd14*cos(dgtr*(input.g_long - p[118])) 
						 + amg::apdf*flags.swc[12] * 
						 (p[83] * amg::plg[0][1] + p[84] * amg::plg[0][3] + p[85] * amg::plg[0][5])* 
						 cos(sr*(input.sec - p[75]));
				 }
			 }
		 }
		 /* parms not used: 82, 89, 99, 139-149 */
		 tinf = p[30];
		 for (i{ 0 }; i != 14; ++i)
			 tinf += std::fabs(flags.sw[i + i]) * t[i];
		 return tinf;
	 }

	 template<typename T, class INPUT, class FLAGS> std::enable_if<ad::is_single_precision<T>::value || 
		 ad::is_double_precision<T>::value, T>::type atmosphere::GLOBE7S<T, INPUT, FLAGS>::fglobe7s(_In_ T* p, _In_ const INPUT &input, _In_ const FLAGS &flags) {
#if defined _DEBUG
			 _ASSERTE(p != nullptr);
#else
			 if(p == nullptr)
				 throw std::runtime_error("Fatal Error -- Null pointer in: GLOBE7S::fglobe7s\n");
#endif
			 constexpr T pset(2.0);
			 constexpr T dr(1.72142E-2);
			 constexpr T dgtr(1.74533E-2);
			 constexpr T neg_one(-1.0);
			 constexpr int t_size{ 14 };
			 T t[t_size];
			 T tt(0.0), cd32, cd18, cd14, cd39;
			 int i, j;
			 /* Confirm parameter set */
			 if (p[99] == 0.0)
				 p[99] = pset;
			 if ((std::fabs(p[99] - pset)) > std::numeric_limits<T>::epsilon())
				 throw std::runtime_error("Fatal Error -- wrong parameter set for GLOBE7S::fglobe7s\n");
			 for (j{ 0 }; j != t_size; ++j) t[j] = 0.0;
			 cd32 = cos(dr * (input.doy - p[31]));
			 cd18 = cos(2.0 * dr * (input.doy - p[17]));
			 cd14 = cos(dr * (input.doy - p[13]));
			 cd39 = cos(2.0 * dr * (input.doy - p[38]));
			 /* F10.7 */
			 t[0] = p[21] * amg::dfa;
			 /* time independent */
			 t[1] = p[1] * amg::plg[0][2] + p[2] * amg::plg[0][4] + p[22] * amg::plg[0][6] + p[26] * amg::plg[0][1] + p[14] * amg::plg[0][3] + p[59] * amg::plg[0][5];
			 /* SYMMETRICAL ANNUAL */
			 t[2] = (p[18] + p[47] * amg::plg[0][2] + p[29] * amg::plg[0][4])*cd32;
			 /* SYMMETRICAL SEMIANNUAL */
			 t[3] = (p[15] + p[16] * amg::plg[0][2] + p[30] * amg::plg[0][4])*cd18;
			 /* ASYMMETRICAL ANNUAL */
			 t[4] = (p[9] * amg::plg[0][1] + p[10] * amg::plg[0][3] + p[20] * amg::plg[0][5])*cd14;
			 /* ASYMMETRICAL SEMIANNUAL */
			 t[5] = (p[37] * amg::plg[0][1])*cd39;
			 /* DIURNAL */
			 if ((std::fabs(flags.sw[7])) > 0.0) {

				 T t71 = p[11] * amg::plg[1][2] * cd14*flags.swc[5];
				 T t72 = p[12] * amg::plg[1][2] * cd14*flags.swc[5];
				 t[6] = ((p[3] * amg::plg[1][1] + p[4] * amg::plg[1][3] + t71) * amg::ctloc + (p[6] * amg::plg[1][1] + p[7] * amg::plg[1][3] + t72) * amg::stloc);
			 }
			 /* SEMIDIURNAL */
			 if ((std::fabs(flags.sw[8])) > 0.0) {

				 T t81 = (p[23] * amg::plg[2][3] + p[35] * amg::plg[2][5])*cd14*flags.swc[5];
				 T t82 = (p[33] * amg::plg[2][3] + p[36] * amg::plg[2][5])*cd14*flags.swc[5];
				 t[7] = ((p[5] * amg::plg[2][2] + p[41] * amg::plg[2][4] + t81) * amg::c2tloc + (p[8] * amg::plg[2][2] + p[42] * amg::plg[2][4] + t82) * amg::s2tloc);
			 }
			 /* TERDIURNAL */
			 if ((std::fabs(flags.sw[14])) > 0.0)
				 t[13] = p[39] * amg::plg[3][3] * amg::s3tloc + p[40] * amg::plg[3][3] * amg::c3tloc;

			 /* MAGNETIC ACTIVITY */
			 if ((std::fabs(flags.sw[9])) > 0.0) {
				 if ((std::fabs(flags.sw[9] - 1.0)) <= std::numeric_limits<T>::epsilon())
					 t[8] = amg::apdf * (p[32] + p[45] * plg[0][2] * flags.swc[2]);
				 if ((std::fabs(flags.sw[9] - neg_one)) <= std::numeric_limits<T>::epsilon())
					 t[8] = (p[50] * amg::apt[0] + p[96] * amg::plg[0][2] * amg::apt[0] * flags.swc[2]);
			 }
			 /* LONGITUDINAL */
			 if (!((flags.sw[10] == 0) || (flags.sw[11] == 0) || (input.g_long <= -1000.0))) {
				 t[10] = (1.0 + amg::plg[0][1] * (p[80] * flags.swc[5] * cos(dr*(input.doy - p[81]))
					 + p[85] * flags.swc[6] * cos(2.0*dr*(input.doy - p[86])))
					 + p[83] * flags.swc[3] * cos(dr*(input.doy - p[84]))
					 + p[87] * flags.swc[4] * cos(2.0*dr*(input.doy - p[88])))
					 *((p[64] * amg::plg[1][2] + p[65] * amg::plg[1][4] + p[66] * amg::plg[1][6]
					 + p[74] * amg::plg[1][1] + p[75] * amg::plg[1][3] + p[76] * amg::plg[1][5]
					 )*cos(dgtr*input.g_long)
					 + (p[90] * amg::plg[1][2] + p[91] * amg::plg[1][4] + p[92] * amg::plg[1][6]
					 + p[77] * amg::plg[1][1] + p[78] * amg::plg[1][3] + p[79] * amg::plg[1][5]
					 )*sin(dgtr*input.g_long));
			 }
			 for (i{ 0 }; i != t_size; ++i)
				 tt += std::fabs(flags.sw[i + 1]) * t[i];
			 return tt;
		 }
		 
	