///////////////////////////////////////////////////////////////////////////////
//
//  This is "Sample Code" and is distributable subject to the terms of the end 
//  user license agreement.
//
///////////////////////////////////////////////////////////////////////////////

// Table that holds info about currencies/

// This file is processed both by a Perl script
// and the C++ preprocessor so don't do anything
// you don't already see being done.

#ifndef CUR_UPD_YEAR
// Rates quoted are from 3/7/2002
#define CUR_UPD_YEAR 2002
#define CUR_UPD_MONTH 7
#define CUR_UPD_DAY 3
#endif

// TLA of the currency, full name, current rate in USD
DEFINE_CURRENCY(USD, "United States Dollars", 1.00000)
DEFINE_CURRENCY(EUR, "Euro", 1.13379)
DEFINE_CURRENCY(GBP, "United Kingdom Pounds", 0.700375)
DEFINE_CURRENCY(CAD, "Canada Dollars", 1.58269)
DEFINE_CURRENCY(JPY, "Japan Yen", 127.142)
DEFINE_CURRENCY(CHF, "Switzerland Francs", 1.66894)
DEFINE_CURRENCY(AFA, "Afghanistan Afghanis", 4750.00)
DEFINE_CURRENCY(ALL, "Albania Leke", 140.060)
DEFINE_CURRENCY(DZD, "Algeria Dinars", 75.8290)
DEFINE_CURRENCY(ARS, "Argentina Pesos", 2.18000)
DEFINE_CURRENCY(AUD, "Australia Dollars", 1.90512)
DEFINE_CURRENCY(BSD, "Bahamas Dollars", 1.00000)
DEFINE_CURRENCY(BBD, "Barbados Dollars", 1.99000)
DEFINE_CURRENCY(BMD, "Bermuda Dollars", 1.00000)
DEFINE_CURRENCY(BRL, "Brazil Reals", 2.35249)
DEFINE_CURRENCY(BGL, "Bulgaria Leva", 2.22353)
DEFINE_CURRENCY(CLP, "Chile Pesos", 664.300)
DEFINE_CURRENCY(CNY, "China Yuan Renminbi", 8.27712)
DEFINE_CURRENCY(COP, "Colombia Pesos", 2289.53)
DEFINE_CURRENCY(XOF, "CFA Francs BCEAO", 743.719)
DEFINE_CURRENCY(CRC, "Costa Rica Colones", 344.290)
DEFINE_CURRENCY(CYP, "Cyprus Pounds", 0.660851)
DEFINE_CURRENCY(CZK, "Czech Republic Koruny", 35.6270)
DEFINE_CURRENCY(DKK, "Denmark Kroner", 8.42138)
DEFINE_CURRENCY(XCD, "East Caribbean Dollars", 2.70000)
DEFINE_CURRENCY(EGP, "Egypt Pounds", 4.60250)
DEFINE_CURRENCY(FJD, "Fiji Dollars", 2.26431)
DEFINE_CURRENCY(XAU, "Gold Ounces", 0.00344828)
DEFINE_CURRENCY(HKD, "Hong Kong Dollars", 7.79910)
DEFINE_CURRENCY(HUF, "Hungary Forint", 277.336)
DEFINE_CURRENCY(ISK, "Iceland Kronur", 100.336)
DEFINE_CURRENCY(INR, "India Rupees", 48.7227)
DEFINE_CURRENCY(IDR, "Indonesia Rupiahs", 9982.05)
DEFINE_CURRENCY(XDR, "IMF Special Drawing Rights", 0.797888)
DEFINE_CURRENCY(ILS, "Israel New Shekels", 4.69228)
DEFINE_CURRENCY(JMD, "Jamaica Dollars", 47.2100)
DEFINE_CURRENCY(JOD, "Jordan Dinars", 0.704000)
DEFINE_CURRENCY(KWD, "Kuwait Dinars", 0.307126)
DEFINE_CURRENCY(LBP, "Lebanon Pounds", 1513.00)
DEFINE_CURRENCY(MYR, "Malaysia Ringgits", 3.79999)
DEFINE_CURRENCY(MTL, "Malta Liri", 0.456371)
DEFINE_CURRENCY(MXN, "Mexico Pesos", 9.07500)
DEFINE_CURRENCY(MAD, "Morocco Dirhams", 11.6260)
DEFINE_CURRENCY(NZD, "New Zealand Dollars", 2.32590)
DEFINE_CURRENCY(NGN, "Nigeria Nairas", 110.450)
DEFINE_CURRENCY(NOK, "Norway Kroner", 8.74526)
DEFINE_CURRENCY(PKR, "Pakistan Rupees", 60.1529)
DEFINE_CURRENCY(PHP, "Philippines Pesos", 50.8000)
DEFINE_CURRENCY(XPT, "Platinum Ounces", 0.00197628)
DEFINE_CURRENCY(PLN, "Poland Zlotych", 4.15129)
DEFINE_CURRENCY(ROL, "Romania Lei", 32008.80)
DEFINE_CURRENCY(RUR, "Russia Rubles", 31.0100)
DEFINE_CURRENCY(SAR, "Saudi Arabia Riyals", 3.75001)
DEFINE_CURRENCY(XAG, "Silver Ounces", 0.224215)
DEFINE_CURRENCY(SGD, "Singapore Dollars", 1.81698)
DEFINE_CURRENCY(SKK, "Slovakia Koruny", 47.6822)
DEFINE_CURRENCY(ZAR, "South Africa Rand", 11.4382)
DEFINE_CURRENCY(KRW, "South Korea Won", 1314.96)
DEFINE_CURRENCY(SDD, "Sudan Dinars", 258.700)
DEFINE_CURRENCY(SEK, "Sweden Kronor", 10.2724)
DEFINE_CURRENCY(TWD, "Taiwan New Dollars", 34.8500)
DEFINE_CURRENCY(THB, "Thailand Baht", 43.3222)
DEFINE_CURRENCY(TTD, "Trinidad and Tobago Dollars", 6.25642)
DEFINE_CURRENCY(TRL, "Turkey Liras", 1365000.03)
DEFINE_CURRENCY(AED, "United Arab Emirates Dirhams", 3.65487)
DEFINE_CURRENCY(VEB, "Venezuela Bolivares", 980.163)
DEFINE_CURRENCY(VND, "Vietnam Dong", 15059.00)
DEFINE_CURRENCY(ZMK, "Zambia Kwacha", 4527.25)

#undef DEFINE_CURRENCY

