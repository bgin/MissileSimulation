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
      SUBROUTINE MCSTB1(LOT,JUMP,N,INC,X,WSAVE,DSUM,WORK,IER)
      REAL       X(INC,*)       ,WSAVE(*)
      DOUBLE PRECISION           DSUM(*)
      IER = 0
      NM1 = N-1
      NP1 = N+1
      NS2 = N/2
      LJ = (LOT-1)*JUMP+1
      IF (N-2) 106,101,102
  101 DO 111 M=1,LJ,JUMP
         X1H = X(M,1)+X(M,2)
         X(M,2) = X(M,1)-X(M,2)
         X(M,1) = X1H
  111 CONTINUE
      RETURN
  102 IF (N .GT. 3) GO TO 103
      DO 112 M=1,LJ,JUMP
         X1P3 = X(M,1)+X(M,3)
         X2 = X(M,2)
         X(M,2) = X(M,1)-X(M,3)
         X(M,1) = X1P3+X2
         X(M,3) = X1P3-X2
  112 CONTINUE
      RETURN
 103  DO 118 M=1,LJ,JUMP
      X(M,1) = X(M,1)+X(M,1)
      X(M,N) = X(M,N)+X(M,N)
 118  CONTINUE
      M1 = 0
      DO 113 M=1,LJ,JUMP
         M1 = M1+1
         DSUM(M1) = X(M,1)-X(M,N)
         X(M,1) = X(M,1)+X(M,N)
  113 CONTINUE
      DO 104 K=2,NS2
         M1 = 0
         DO 114 M=1,LJ,JUMP
         M1 = M1+1
         KC = NP1-K
         T1 = X(M,K)+X(M,KC)
         T2 = X(M,K)-X(M,KC)
         DSUM(M1) = DSUM(M1)+WSAVE(KC)*T2
         T2 = WSAVE(K)*T2
         X(M,K) = T1-T2
         X(M,KC) = T1+T2
  114    CONTINUE
  104 CONTINUE
      MODN = MOD(N,2)
      IF (MODN .EQ. 0) GO TO 124
         DO 123 M=1,LJ,JUMP
         X(M,NS2+1) = X(M,NS2+1)+X(M,NS2+1)
  123    CONTINUE
 124  CONTINUE
      LENX = (LOT-1)*JUMP + INC*(NM1-1)  + 1
      LNSV = NM1 + INT(LOG(REAL(NM1))/LOG(2.)) + 4
      LNWK = LOT*NM1
C
      CALL RFFTMF(LOT,JUMP,NM1,INC,X,LENX,WSAVE(N+1),LNSV,WORK,
     1            LNWK,IER1)
      IF (IER1 .NE. 0) THEN
        IER = 20
        CALL XERFFT ('MCSTB1',-5)
        GO TO 106
      ENDIF
C
      FNM1S2 = FLOAT(NM1)/2.
      M1 = 0
      DO 10 M=1,LJ,JUMP
      M1 = M1+1
      DSUM(M1) = .5*DSUM(M1)
      X(M,1) = FNM1S2*X(M,1)
   10 CONTINUE
      IF(MOD(NM1,2) .NE. 0) GO TO 30
      DO 20 M=1,LJ,JUMP
      X(M,NM1) = X(M,NM1)+X(M,NM1)
   20 CONTINUE
 30   FNM1S4 = FLOAT(NM1)/4.
      DO 105 I=3,N,2
         M1 = 0
         DO 115 M=1,LJ,JUMP
            M1 = M1+1
            XI = FNM1S4*X(M,I)
            X(M,I) = FNM1S4*X(M,I-1)
            X(M,I-1) = DSUM(M1)
            DSUM(M1) = DSUM(M1)+XI
  115 CONTINUE
  105 CONTINUE
      IF (MODN .NE. 0) RETURN
      M1 = 0
      DO 116 M=1,LJ,JUMP
         M1 = M1+1
         X(M,N) = DSUM(M1)
  116 CONTINUE
  106 CONTINUE
      RETURN
      END
