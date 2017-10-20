

typedef enum {
	AS,
	ZS,
	AN,
	ZN
} coordinate;

typedef enum { 
	CorrOn , CorrOff, SignOsP, SignOsM,
	FazOff , FazOn  , DisSlow, EnbSlow, SlowOn , SlowOff,
    FastOnP, FastOnM, FastOff, EnblVk1, EnblVk2, EnbStyk,
	DislVk1, DislVk2, DisStyk, ChkVk1 , ChkVk2 , ChStyk ,
	ChkLam
} commandmup;

// места нахождения модулей в корзине крейта соответственно координатам
//               AS  ZS  AN  ZN

int nIR[4]   = {  3,  3,  4,  4 }; // места модулей КАМАК: IR305
int nCorr[4] = {  9, 12, 15, 18 }; // места модулей КАМАК: корректор
int nSint[4] = { 10, 13, 16, 19 }; // места модулей КАМАК: синтезатор
int nMup[4]  = { 11, 14, 17, 20 }; // места модулей КАМАК: МУП

// режимы управления координатами телескопа: M -всеми, S -южной, N -северной
enum Regim {M, S, N, As, Zs, An, Zn}; //остальные отдельно каждой координатой

//   имена  станций
enum  Stan  { N1 = 1, N2,  N3,  N4,  N5,  N6,  N7,  N8,  N9, N10,\
              N11, N12, N13, N14, N15, N16, N17, N18, N19, N20, N21 };

//   имена  субадресов
enum  SuAd  { A0 = 0, A1, A2,  A3,  A4,  A5,  A6,  A7, \
              A8, A9, A10, A11, A12, A13, A14, A15 };

//   имена  функций
enum  Func  { F0 = 0,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  \
              F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, \
              F20, F21, F22, F23, F24, F25, F26, F27, F28, F29, \
              F30, F31 };

