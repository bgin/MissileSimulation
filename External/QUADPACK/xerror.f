      subroutine xerror(messg,nmessg,nerr,level)
c
c     abstract
c        xerror processes a diagnostic message, in a manner
c        determined by the value of level and the current value
c        of the library error control flag, kontrl.
c        (see subroutine xsetf for details.)
c
c     description of parameters
c      --input--
c        messg - the hollerith message to be processed, containing
c                no more than 72 characters.
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
c
c     examples
c        call xerror(23hsmooth -- num was zero.,23,1,2)
c        call xerror(43hinteg  -- less than full accuracy achieved.,
c                    43,2,1)
c        call xerror(65hrooter -- actual zero of f found before interval
c    1 fully collapsed.,65,3,0)
c        call xerror(39hexp    -- underflows being set to zero.,39,1,-1)
c
c     written by ron jones, with slatec common math library subcommittee
c     latest revision ---  7 feb 1979
c
      dimension messg(nmessg)
      call xerrwv(messg,nmessg,nerr,level,0,0,0,0,0.,0.)
      return
      end
