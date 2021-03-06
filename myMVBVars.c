#include "myWrapper.h"

UINT16 LINEVOLT1;
UINT16 LINECUR1;
UINT16 RETCUR1;
UINT16 FBPRESS1;
UINT16 T1BATVLT;
UINT16 T1CURREF;
UINT16 T1GAINFC;
UINT16 T1STTB;
UINT16 INV2DXIN;
UINT16 INV2DXSTAT;
UINT16 INV1DIIN;
UINT16 INV1DISTAT;
UINT16 INV3DXIN;
UINT16 INV3DXSTAT;
UINT16 LINEVOLT2;
UINT16 LINECUR2;
UINT16 RETCUR2;
UINT16 FBPRESS2;
UINT16 T2BATVLT;
UINT16 T2CURREF;
UINT16 T2GAINFC;
UINT16 T2STTB;
UINT16 D1VWDCNTR01;
UINT16 D1VTREFTDEL;
UINT16 D1VSPDAXL1;
UINT16 D1VSPDAXL2;
UINT16 D1VSPDAXL3;
UINT16 D1VSPDAXL4;
UINT16 D1VBKCPCNTL;
UINT16 D1VSTAWORD1;
UINT16 D1VSPARE999;
UINT16 D2VWDCNTR01;
UINT16 D2VTREFTDEL;
UINT16 D2VSPDAXL1;
UINT16 D2VSPDAXL2;
UINT16 D2VSPDAXL3;
UINT16 D2VSPDAXL4;
UINT16 D2VBKCPCNTL;
UINT16 D2VSTAWORD1;
UINT16 D2VSPARE999;
UINT16 FB1CMD;
UINT16 AX320P9;
UINT16 T1SETCUR;
UINT16 T1SETFC;
UINT16 INV2DXOUT;
UINT16 INV1DIOUT;
UINT16 INV3DXOUT;
UINT16 FB2CMD;
UINT16 AX370P9;
UINT16 T2SETCUR;
UINT16 T2SETFC;
UINT16 CHARTCHN3;
UINT16 CHARTCHN4;
UINT16 CHARTCHN5;
UINT16 CHARTCHN6;
UINT16 CHARTCHN7;
UINT16 CHARTCHN8;
UINT16 CHARTCHN1;
UINT16 CHARTCHN2;
UINT16 AX520P8;
UINT16 AX520P9;
UINT16 HVSETCUR;
UINT16 HVSETFC;
UINT16 VD1WDCNTR01;
UINT16 VD1TREFTREQ;
UINT16 VD1TEREQREL;
UINT16 VD1TRAINVEL;
UINT16 VD1SPARE001;
UINT16 VD1ACTGNPWR;
UINT16 VD1SIMLINKV;
UINT16 VD1VLINEVOL;
UINT16 VD1CTLWORD1;
UINT16 VD1CTLWORD2;
UINT16 VD2WDCNTR01;
UINT16 VD2TREFTREQ;
UINT16 VD2TEREQREL;
UINT16 VD2TRAINVEL;
UINT16 VD2SPARE001;
UINT16 VD2ACTGNPWR;
UINT16 VD2SIMLINKV;
UINT16 VD2VLINEVOL;
UINT16 VD2CTLWORD1;
UINT16 VD2CTLWORD2;
UINT16 Standbytoken;
UINT16 StandbyWD;
UINT16 StandbyAdd;
UINT16 StandbyWord1;
UINT16 Maintoken;
UINT16 MainWD;
UINT16 MainAdd;
UINT16 MainWord1;
UINT16 D1VWDCNTR02;
UINT16 D1VMOTPWR;
UINT16 D1VVLINKVOL;
UINT16 D1VILINKCUR;
UINT16 D1VTEDELFIC;
UINT16 D1VDCUSTATE;
UINT16 D1VAVLDBABS;
UINT16 D1VAVLDBREL;
UINT16 D1VBRKCPWR;
UINT16 D1VSTRMSCUR;
UINT16 D1VMCMSYSTM;
UINT16 D1VSPARE001;
UINT16 D1VLINKPWR;
UINT16 D1VTESTNUM;
UINT16 D1VSTAWORD2;
UINT16 D1VSTAWORD3;
UINT16 D2VWDCNTR02;
UINT16 D2VMOTPWR;
UINT16 D2VVLINKVOL;
UINT16 D2VILINKCUR;
UINT16 D2VTEDELFIC;
UINT16 D2VDCUSTATE;
UINT16 D2VAVLDBABS;
UINT16 D2VAVLDBREL;
UINT16 D2VBRKCPWR;
UINT16 D2VSTRMSCUR;
UINT16 D2VMCMSYSTM;
UINT16 D2VSPARE001;
UINT16 D2VLINKPWR;
UINT16 D2VTESTNUM;
UINT16 D2VSTAWORD2;
UINT16 D2VSTAWORD3;
UINT16 VD1WDCNTR02;
UINT16 VD1TRNWTCOR;
UINT16 VD1TESTREQ;
UINT16 VD1REFLINKV;
UINT16 VD1AUXCNPWR;
UINT16 VD1REFBKCHP;
UINT16 VD1SELMCMSY;
UINT16 VD1SPARE002;
UINT16 VD1SPARE003;
UINT16 VD1SPARE004;
UINT16 VD1SPARE005;
UINT16 VD1TCNTIME1;
UINT16 VD1TCNTIME2;
UINT16 VD1TCNTIME3;
UINT16 VD1CTLWORD3;
UINT16 VD1CTLWORD4;
UINT16 VD2WDCNTR02;
UINT16 VD2TRNWTCOR;
UINT16 VD2TESTREQ;
UINT16 VD2REFLINKV;
UINT16 VD2AUXCNPWR;
UINT16 VD2REFBKCHP;
UINT16 VD2SELMCMSY;
UINT16 VD2SPARE002;
UINT16 VD2SPARE003;
UINT16 VD2SPARE004;
UINT16 VD2SPARE005;
UINT16 VD2TCNTIME1;
UINT16 VD2TCNTIME2;
UINT16 VD2TCNTIME3;
UINT16 VD2CTLWORD3;
UINT16 VD2CTLWORD4;
UINT16 LWPRESS1;
UINT16 LWPRESS2;
UINT16 MRPRESS;
UINT16 AX520P4;
UINT16 HVBATVLT;
UINT16 HVCURREF;
UINT16 HVGAINFC;
UINT16 HVSTTB;
UINT16 D1VWDCNTR03;
UINT16 D1VTESTMODE;
UINT16 D1VINVTEMP;
UINT16 D1VMOT1TEMP;
UINT16 D1VMOT2TEMP;
UINT16 D1VAPPWD1;
UINT16 D1VAPPWD2;
UINT16 D1VAIRTEMP;
UINT16 D1VCHGRTEMP;
UINT16 D1VBRKRTEMP;
UINT16 D1VOSWD1;
UINT16 D1VOSWD2;
UINT16 D1VBLWD1;
UINT16 D1VBLWD2;
UINT16 D1VSPARE002;
UINT16 D1VSTAWORD4;
UINT16 D1VWDCNTR04;
UINT16 D1VDIAWORD1;
UINT16 D1VDIAWORD2;
UINT16 D1VDIAWORD3;
UINT16 D1VDIAWORD4;
UINT16 D1VDIAWORD5;
UINT16 D1VDIAWORD6;
UINT16 D1VDIAWORD7;
UINT16 D1VDIAWORD8;
UINT16 D1VDIAWORD9;
UINT16 D1VDIAWORD10;
UINT16 D1VDIAWORD11;
UINT16 D1VDIAWORD12;
UINT16 D1VDIAWORD13;
UINT16 D1VDIAWORD15;
UINT16 D1VISOWORD1;
UINT16 D1VWDCNTR05;
UINT16 D1VDCUOVR12;
UINT16 D1VDCUOVR34;
UINT16 D1VDCUFVR12;
UINT16 D1VDCUFVR34;
UINT16 D1VDCUDVR12;
UINT16 D1VDCUDVR34;
UINT16 D1VDCUMVR12;
UINT16 D1VDCUMVR34;
UINT16 D2VWDCNTR03;
UINT16 D2VTESTMODE;
UINT16 D2VINVTEMP;
UINT16 D2VMOT1TEMP;
UINT16 D2VMOT2TEMP;
UINT16 D2VAPPWD1;
UINT16 D2VAPPWD2;
UINT16 D2VAIRTEMP;
UINT16 D2VCHGRTEMP;
UINT16 D2VBRKRTEMP;
UINT16 D2VOSWD1;
UINT16 D2VOSWD2;
UINT16 D2VBLWD1;
UINT16 D2VBLWD2;
UINT16 D2VSPARE002;
UINT16 D2VSTAWORD4;
UINT16 D2VWDCNTR04;
UINT16 D2VDIAWORD1;
UINT16 D2VDIAWORD2;
UINT16 D2VDIAWORD3;
UINT16 D2VDIAWORD4;
UINT16 D2VDIAWORD5;
UINT16 D2VDIAWORD6;
UINT16 D2VDIAWORD7;
UINT16 D2VDIAWORD8;
UINT16 D2VDIAWORD9;
UINT16 D2VDIAWORD10;
UINT16 D2VDIAWORD11;
UINT16 D2VDIAWORD12;
UINT16 D2VDIAWORD13;
UINT16 D2VDIAWORD14;
UINT16 D2VISOWORD1;
UINT16 D2VWDCNTR05;
UINT16 D2VDCUOVR12;
UINT16 D2VDCUOVR34;
UINT16 D2VDCUFVR12;
UINT16 D2VDCUFVR34;
UINT16 D2VDCUDVR12;
UINT16 D2VDCUDVR34;
UINT16 D2VDCUMVR12;
UINT16 D2VDCUMVR34;
UINT16 VD1WDCNTR03;
UINT16 VD1SPARE;
UINT16 VD1MXHSTEMP;
UINT16 VD1MXINTEMP;
UINT16 VD1REFWDIAM;
UINT16 VD1RFAXLNUM;
UINT16 VD1TESTMODE;
UINT16 VD1CARIDENT;
UINT16 VD1WHELDIA1;
UINT16 VD1WHELDIA2;
UINT16 VD1WHELDIA3;
UINT16 VD1WHELDIA4;
UINT16 VD1SPARE006;
UINT16 VD1SPARE007;
UINT16 VD1CTLWORD5;
UINT16 VD1CTLWORD6;
UINT16 VD2WDCNTR03;
UINT16 VD2SPARE;
UINT16 VD2MXHSTEMP;
UINT16 VD2MXINTEMP;
UINT16 VD2REFWDIAM;
UINT16 VD2RFAXLNUM;
UINT16 VD2TESTMODE;
UINT16 VD2CARIDENT;
UINT16 VD2WHELDIA1;
UINT16 VD2WHELDIA2;
UINT16 VD2WHELDIA3;
UINT16 VD2WHELDIA4;
UINT16 VD2SPARE006;
UINT16 VD2SPARE007;
UINT16 VD2CTLWORD5;
UINT16 VD2CTLWORD6;
