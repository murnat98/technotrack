//!      cmd     num   args
DEFCMD (pushc ,   1,    1)
DEFCMD (pushr ,   2,    1)
DEFCMD (pop   ,   3,    0)
DEFCMD (popr  ,   4,    1)

DEFCMD (add   ,   7,    0)
DEFCMD (sub   ,   8,    0)
DEFCMD (mul   ,   9,    0)
DEFCMD (div   ,   10,   0)

DEFCMD (jmp   ,   13,   1)
DEFCMD (jmpf  ,   14,   1)
DEFCMD (call  ,   15,   1)
DEFCMD (ret   ,   16,	0)

DEFCMD (equal ,   20,	0)
DEFCMD (noteq ,   21,	0)
DEFCMD (boreq ,   22,	0)
DEFCMD (aoreq ,   23,	0)
DEFCMD (below ,   24,	0)
DEFCMD (above ,   25,	0)

DEFCMD (and   ,   26,	0)
DEFCMD (or    ,   27,	0)
DEFCMD (not   ,   28,   0)

DEFCMD (in    ,   30,   0)
DEFCMD (out   ,   31,   0)

DEFCMD (exit  ,   0,    0)