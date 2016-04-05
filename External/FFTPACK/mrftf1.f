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
      SUBROUTINE MRFTF1 (M,IM,N,IN,C,CH,WA,FAC)
      REAL       CH(M,*) ,C(IN,*)  ,WA(N)   ,FAC(15)
C
      NF = FAC(2)
      NA = 1
      L2 = N
      IW = N
      DO 111 K1=1,NF
         KH = NF-K1
         IP = FAC(KH+3)
         L1 = L2/IP
         IDO = N/L2
         IDL1 = IDO*L1
         IW = IW-(IP-1)*IDO
         NA = 1-NA
         IF (IP .NE. 4) GO TO 102
         IX2 = IW+IDO
         IX3 = IX2+IDO
         IF (NA .NE. 0) GO TO 101
	 CALL MRADF4 (M,IDO,L1,C,IM,IN,CH,1,M,WA(IW),WA(IX2),WA(IX3))
         GO TO 110
  101    CALL MRADF4 (M,IDO,L1,CH,1,M,C,IM,IN,WA(IW),WA(IX2),WA(IX3))
         GO TO 110
  102    IF (IP .NE. 2) GO TO 104
         IF (NA .NE. 0) GO TO 103
	 CALL MRADF2 (M,IDO,L1,C,IM,IN,CH,1,M,WA(IW))
         GO TO 110
  103    CALL MRADF2 (M,IDO,L1,CH,1,M,C,IM,IN,WA(IW))
         GO TO 110
  104    IF (IP .NE. 3) GO TO 106
         IX2 = IW+IDO
         IF (NA .NE. 0) GO TO 105
	 CALL MRADF3 (M,IDO,L1,C,IM,IN,CH,1,M,WA(IW),WA(IX2))
         GO TO 110
  105    CALL MRADF3 (M,IDO,L1,CH,1,M,C,IM,IN,WA(IW),WA(IX2))
         GO TO 110
  106    IF (IP .NE. 5) GO TO 108
         IX2 = IW+IDO
         IX3 = IX2+IDO
         IX4 = IX3+IDO
         IF (NA .NE. 0) GO TO 107
         CALL MRADF5(M,IDO,L1,C,IM,IN,CH,1,M,WA(IW),WA(IX2),
     1                      WA(IX3),WA(IX4))
         GO TO 110
  107    CALL MRADF5(M,IDO,L1,CH,1,M,C,IM,IN,WA(IW),WA(IX2),
     1                      WA(IX3),WA(IX4))
         GO TO 110
  108    IF (IDO .EQ. 1) NA = 1-NA
         IF (NA .NE. 0) GO TO 109
	 CALL MRADFG (M,IDO,IP,L1,IDL1,C,C,C,IM,IN,CH,CH,1,M,WA(IW))
         NA = 1
         GO TO 110
  109    CALL MRADFG (M,IDO,IP,L1,IDL1,CH,CH,CH,1,M,C,C,IM,IN,WA(IW))
         NA = 0
  110    L2 = L1
  111 CONTINUE
      SN = 1./N
      TSN = 2./N
      TSNM = -TSN
      MODN = MOD(N,2)
      NL = N-2
      IF(MODN .NE. 0) NL = N-1
      IF (NA .NE. 0) GO TO 120
      M2 = 1-IM
      DO 117 I=1,M
         M2 = M2+IM
         C(M2,1) = SN*CH(I,1)
  117 CONTINUE
      DO 118 J=2,NL,2
      M2 = 1-IM
      DO 118 I=1,M
         M2 = M2+IM
	 C(M2,J) = TSN*CH(I,J)
	 C(M2,J+1) = TSNM*CH(I,J+1)
  118 CONTINUE
      IF(MODN .NE. 0) RETURN
      M2 = 1-IM
      DO 119 I=1,M
         M2 = M2+IM
         C(M2,N) = SN*CH(I,N)
  119 CONTINUE
      RETURN
  120 M2 = 1-IM
      DO 121 I=1,M
         M2 = M2+IM
         C(M2,1) = SN*C(M2,1)
  121 CONTINUE
      DO 122 J=2,NL,2
      M2 = 1-IM
      DO 122 I=1,M
         M2 = M2+IM
	 C(M2,J) = TSN*C(M2,J)
	 C(M2,J+1) = TSNM*C(M2,J+1)
  122 CONTINUE
      IF(MODN .NE. 0) RETURN
      M2 = 1-IM
      DO 123 I=1,M
         M2 = M2+IM
         C(M2,N) = SN*C(M2,N)
  123 CONTINUE
      RETURN
      END
