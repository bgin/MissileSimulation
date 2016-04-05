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
      SUBROUTINE COSTB1(N,INC,X,WSAVE,WORK,IER)
      REAL       X(INC,*)       ,WSAVE(*)
      DOUBLE PRECISION           DSUM
      IER = 0
      NM1 = N-1
      NP1 = N+1
      NS2 = N/2
      IF (N-2) 106,101,102
  101 X1H = X(1,1)+X(1,2)
      X(1,2) = X(1,1)-X(1,2)
      X(1,1) = X1H
      RETURN
  102 IF (N .GT. 3) GO TO 103
      X1P3 = X(1,1)+X(1,3)
      X2 = X(1,2)
      X(1,2) = X(1,1)-X(1,3)
      X(1,1) = X1P3+X2
      X(1,3) = X1P3-X2
      RETURN
  103 X(1,1) = X(1,1)+X(1,1)
      X(1,N) = X(1,N)+X(1,N)
      DSUM = X(1,1)-X(1,N)
      X(1,1) = X(1,1)+X(1,N)
      DO 104 K=2,NS2
         KC = NP1-K
         T1 = X(1,K)+X(1,KC)
         T2 = X(1,K)-X(1,KC)
         DSUM = DSUM+WSAVE(KC)*T2
         T2 = WSAVE(K)*T2
         X(1,K) = T1-T2
         X(1,KC) = T1+T2
  104 CONTINUE
      MODN = MOD(N,2)
      IF (MODN .EQ. 0) GO TO 124
      X(1,NS2+1) = X(1,NS2+1)+X(1,NS2+1)
  124 LENX = INC*(NM1-1)  + 1
      LNSV = NM1 + INT(LOG(REAL(NM1))/LOG(2.)) + 4
      LNWK = NM1
C
      CALL RFFT1F(NM1,INC,X,LENX,WSAVE(N+1),LNSV,WORK,
     1            LNWK,IER1)
      IF (IER1 .NE. 0) THEN
        IER = 20
        CALL XERFFT ('COSTB1',-5)
        RETURN
      ENDIF
C
      FNM1S2 = FLOAT(NM1)/2.
      DSUM = .5*DSUM
      X(1,1) = FNM1S2*X(1,1)
      IF(MOD(NM1,2) .NE. 0) GO TO 30
      X(1,NM1) = X(1,NM1)+X(1,NM1)
   30 FNM1S4 = FLOAT(NM1)/4.
      DO 105 I=3,N,2
         XI = FNM1S4*X(1,I)
         X(1,I) = FNM1S4*X(1,I-1)
         X(1,I-1) = DSUM
         DSUM = DSUM+XI
  105 CONTINUE
      IF (MODN .NE. 0) RETURN
         X(1,N) = DSUM
  106 RETURN
      END
