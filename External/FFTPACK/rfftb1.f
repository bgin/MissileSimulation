C     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
C     *                                                               *
C     *                  copyright (c) 2011 by UCAR                   *
C     *                                                               *
C     *       University Corporation for Atmospheric Research         *
C     *                                                               *
C     *                      all rights reserved                      *
C     *                                                               *
C     *                     FFTPACK  version 5.1                      *
C     *                                                               *
C     *                 A Fortran Package of Fast Fourier             *
C     *                                                               *
C     *                Subroutines and Example Programs               *
C     *                                                               *
C     *                             by                                *
C     *                                                               *
C     *               Paul Swarztrauber and Dick Valent               *
C     *                                                               *
C     *                             of                                *
C     *                                                               *
C     *         the National Center for Atmospheric Research          *
C     *                                                               *
C     *                Boulder, Colorado  (80307)  U.S.A.             *
C     *                                                               *
C     *                   which is sponsored by                       *
C     *                                                               *
C     *              the National Science Foundation                  *
C     *                                                               *
C     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
C
      SUBROUTINE RFFTB1 (N,IN,C,CH,WA,FAC)
      REAL       CH(*), C(IN,*), WA(N) ,FAC(15)
C
      NF = FAC(2)
      NA = 0
      DO 10 K1=1,NF
      IP = FAC(K1+2)
      NA = 1-NA      
      IF(IP .LE. 5) GO TO 10
      IF(K1 .EQ. NF) GO TO 10
      NA = 1-NA
   10 CONTINUE 
      HALF = .5
      HALFM = -.5
      MODN = MOD(N,2)
      NL = N-2
      IF(MODN .NE. 0) NL = N-1
      IF (NA .EQ. 0) GO TO 120
      CH(1) = C(1,1)
      CH(N) = C(1,N)
      DO 118 J=2,NL,2
	 CH(J) = HALF*C(1,J)
	 CH(J+1) = HALFM*C(1,J+1)
  118 CONTINUE
      GO TO 124
  120 DO 122 J=2,NL,2
	 C(1,J) = HALF*C(1,J)
	 C(1,J+1) = HALFM*C(1,J+1)
  122 CONTINUE
  124 L1 = 1
      IW = 1
      DO 116 K1=1,NF
         IP = FAC(K1+2)
         L2 = IP*L1
         IDO = N/L2
         IDL1 = IDO*L1
         IF (IP .NE. 4) GO TO 103
         IX2 = IW+IDO
         IX3 = IX2+IDO
         IF (NA .NE. 0) GO TO 101
         CALL R1F4KB (IDO,L1,C,IN,CH,1,WA(IW),WA(IX2),WA(IX3))
         GO TO 102
  101    CALL R1F4KB (IDO,L1,CH,1,C,IN,WA(IW),WA(IX2),WA(IX3))
  102    NA = 1-NA
         GO TO 115
  103    IF (IP .NE. 2) GO TO 106
         IF (NA .NE. 0) GO TO 104
	 CALL R1F2KB (IDO,L1,C,IN,CH,1,WA(IW))
         GO TO 105
  104    CALL R1F2KB (IDO,L1,CH,1,C,IN,WA(IW))
  105    NA = 1-NA
         GO TO 115
  106    IF (IP .NE. 3) GO TO 109
         IX2 = IW+IDO
         IF (NA .NE. 0) GO TO 107
	 CALL R1F3KB (IDO,L1,C,IN,CH,1,WA(IW),WA(IX2))
         GO TO 108
  107    CALL R1F3KB (IDO,L1,CH,1,C,IN,WA(IW),WA(IX2))
  108    NA = 1-NA
         GO TO 115
  109    IF (IP .NE. 5) GO TO 112
         IX2 = IW+IDO
         IX3 = IX2+IDO
         IX4 = IX3+IDO
         IF (NA .NE. 0) GO TO 110
         CALL R1F5KB (IDO,L1,C,IN,CH,1,WA(IW),WA(IX2),
     1                  WA(IX3),WA(IX4))
         GO TO 111
  110    CALL R1F5KB (IDO,L1,CH,1,C,IN,WA(IW),WA(IX2),
     1                  WA(IX3),WA(IX4))
  111    NA = 1-NA
         GO TO 115
  112    IF (NA .NE. 0) GO TO 113
	 CALL R1FGKB (IDO,IP,L1,IDL1,C,C,C,IN,CH,CH,1,WA(IW))
         GO TO 114
  113    CALL R1FGKB (IDO,IP,L1,IDL1,CH,CH,CH,1,C,C,IN,WA(IW))
  114    IF (IDO .EQ. 1) NA = 1-NA
  115    L1 = L2
         IW = IW+(IP-1)*IDO
  116 CONTINUE
      RETURN
      END
