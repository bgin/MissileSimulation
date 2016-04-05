      subroutine xerrwv(messg,nmessg,nerr,level,ni,i1,i2,nr,r1,r2)
c
c     abstract
c        xerrwv processes a diagnostic message, in a manner
c        determined by the value of level and the current value
c        of the library error control flag, kontrl.
c        (see subroutine xsetf for details.)
c        in addition, up to two integer values and two real
c        values may be printed along with the message.
c
c     description of parameters
c      --input--
c        messg - the hollerith message to be processed.
c        nmessg- the actual number of characters in messg.
c        nerr  - the error number associated with this message.
c                nerr must not be zero.
c        level - error category.
c                =2 means this is an unconditionally fatal error.
c                =1 means this is a recoverable error.  (i.e., it is
c                   non-fatal if xsetf has been appropriately called.)
c                =0 means this is a warning message only.
c                =-1 means this is a warning message which is to be
c                   printed at most once, regardless of how many
c                   times this call is executed.
c        ni    - number of integer values to be printed. (o to 2)
c        i1    - first integer value.
c        i2    - second integer value.
c        nr    - number of real values to be printed. (0 to 2)
c        r1    - first real value.
c        r2    - second real value.
c
c     examples
c        call xerror(29hsmooth -- num (=i1) was zero.,29,1,2,
c    1   1,num,0,0,0.,0.)
c        call xerrwv(54hquadxy -- requested error (r1) less than minimum
c    1 (r2).,54,77,1,0,0,0,2,errreq,errmin)
c
c     written by ron jones, with slatec common math library subcommittee
c     latest revision ---  19 mar 1980
c
      dimension messg(nmessg),lun(5)
c     get flags
      lkntrl = j4save(2,0,.false.)
      maxmes = j4save(4,0,.false.)
c     check for valid input
      if ((nmessg.gt.0).and.(nerr.ne.0).and.
     1    (level.ge.(-1)).and.(level.le.2)) go to 10
         if (lkntrl.gt.0) call xerprt(17hfatal error in...,17)
         call xerprt(23hxerror -- invalid input,23)
         if (lkntrl.gt.0) call fdump
         if (lkntrl.gt.0) call xerprt(29hjob abort due to fatal error.,
     1   29)
         if (lkntrl.gt.0) call xersav(1h ,0,0,0,kdummy)
         call xerabt(23hxerror -- invalid input,23)
         return
   10 continue
c     record message
      junk = j4save(1,nerr,.true.)
      call xersav(messg,nmessg,nerr,level,kount)
c     let user override
      lfirst = messg(1)
      lmessg = nmessg
      lerr = nerr
      llevel = level
      call xerctl(lfirst,lmessg,lerr,llevel,lkntrl)
c     reset to original values
      lmessg = nmessg
      lerr = nerr
      llevel = level
      lkntrl = max0(-2,min0(2,lkntrl))
      mkntrl = iabs(lkntrl)
c     decide whether to print message
      if ((llevel.lt.2).and.(lkntrl.eq.0)) go to 100
      if (((llevel.eq.(-1)).and.(kount.gt.min0(1,maxmes)))
     1.or.((llevel.eq.0)   .and.(kount.gt.maxmes))
     2.or.((llevel.eq.1)   .and.(kount.gt.maxmes).and.(mkntrl.eq.1))
     3.or.((llevel.eq.2)   .and.(kount.gt.max0(1,maxmes)))) go to 100
         if (lkntrl.le.0) go to 20
            call xerprt(1h ,1)
c           introduction
            if (llevel.eq.(-1)) call xerprt
     1(57hwarning message...this message will only be printed once.,57)
            if (llevel.eq.0) call xerprt(13hwarning in...,13)
            if (llevel.eq.1) call xerprt
     1      (23hrecoverable error in...,23)
            if (llevel.eq.2) call xerprt(17hfatal error in...,17)
   20    continue
c        message
         call xerprt(messg,lmessg)
         call xgetua(lun,nunit)
         do 50 kunit=1,nunit
            iunit = lun(kunit)
            if (iunit.eq.0) iunit = i1mach(4)
            if (ni.ge.1) write (iunit,22) i1
            if (ni.ge.2) write (iunit,23) i2
            if (nr.ge.1) write (iunit,24) r1
            if (nr.ge.2) write (iunit,25) r2
   22       format (11x,21hin above message, i1=,i10)
   23       format (11x,21hin above message, i2=,i10)
   24       format (11x,21hin above message, r1=,e20.10)
   25       format (11x,21hin above message, r2=,e20.10)
            if (lkntrl.le.0) go to 40
c              error number
               write (iunit,30) lerr
   30          format (15h error number =,i10)
   40       continue
   50    continue
c        trace-back
         if (lkntrl.gt.0) call fdump
  100 continue
      ifatal = 0
      if ((llevel.eq.2).or.((llevel.eq.1).and.(mkntrl.eq.2)))
     1ifatal = 1
c     quit here if message is not fatal
      if (ifatal.le.0) return
      if ((lkntrl.le.0).or.(kount.gt.max0(1,maxmes))) go to 120
c        print reason for abort
         if (llevel.eq.1) call xerprt
     1   (35hjob abort due to unrecovered error.,35)
         if (llevel.eq.2) call xerprt
     1   (29hjob abort due to fatal error.,29)
c        print error summary
         call xersav(1h ,-1,0,0,kdummy)
  120 continue
c     abort
      if ((llevel.eq.2).and.(kount.gt.max0(1,maxmes))) lmessg = 0
      call xerabt(messg,lmessg)
      return
      end
