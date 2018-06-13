/**
 *  @file
 *  @copyright defined in oac/LICENSE.txt
 */
#include <oaclib/oac.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   oac_assert( sizeof(int64_t) == 8, "int64_t size != 8");
   oac_assert( sizeof(uint64_t) ==  8, "uint64_t size != 8");
   oac_assert( sizeof(uint32_t) ==  4, "uint32_t size != 4");
   oac_assert( sizeof(int32_t) ==  4, "int32_t size != 4");
   oac_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   oac_assert( sizeof(int128_t) == 16, "int128_t size != 16");
   oac_assert( sizeof(uint8_t) ==  1, "uint8_t size != 1");

   oac_assert( sizeof(account_name) ==  8, "account_name size !=  8");
   oac_assert( sizeof(table_name) ==  8, "table_name size !=  8");
   oac_assert( sizeof(time) ==  4, "time size !=  4");
   oac_assert( sizeof(oac::key256) == 32, "key256 size != 32" );
}

void test_types::char_to_symbol() {

   oac_assert( oac::char_to_symbol('1') ==  1, "oac::char_to_symbol('1') !=  1");
   oac_assert( oac::char_to_symbol('2') ==  2, "oac::char_to_symbol('2') !=  2");
   oac_assert( oac::char_to_symbol('3') ==  3, "oac::char_to_symbol('3') !=  3");
   oac_assert( oac::char_to_symbol('4') ==  4, "oac::char_to_symbol('4') !=  4");
   oac_assert( oac::char_to_symbol('5') ==  5, "oac::char_to_symbol('5') !=  5");
   oac_assert( oac::char_to_symbol('a') ==  6, "oac::char_to_symbol('a') !=  6");
   oac_assert( oac::char_to_symbol('b') ==  7, "oac::char_to_symbol('b') !=  7");
   oac_assert( oac::char_to_symbol('c') ==  8, "oac::char_to_symbol('c') !=  8");
   oac_assert( oac::char_to_symbol('d') ==  9, "oac::char_to_symbol('d') !=  9");
   oac_assert( oac::char_to_symbol('e') == 10, "oac::char_to_symbol('e') != 10");
   oac_assert( oac::char_to_symbol('f') == 11, "oac::char_to_symbol('f') != 11");
   oac_assert( oac::char_to_symbol('g') == 12, "oac::char_to_symbol('g') != 12");
   oac_assert( oac::char_to_symbol('h') == 13, "oac::char_to_symbol('h') != 13");
   oac_assert( oac::char_to_symbol('i') == 14, "oac::char_to_symbol('i') != 14");
   oac_assert( oac::char_to_symbol('j') == 15, "oac::char_to_symbol('j') != 15");
   oac_assert( oac::char_to_symbol('k') == 16, "oac::char_to_symbol('k') != 16");
   oac_assert( oac::char_to_symbol('l') == 17, "oac::char_to_symbol('l') != 17");
   oac_assert( oac::char_to_symbol('m') == 18, "oac::char_to_symbol('m') != 18");
   oac_assert( oac::char_to_symbol('n') == 19, "oac::char_to_symbol('n') != 19");
   oac_assert( oac::char_to_symbol('o') == 20, "oac::char_to_symbol('o') != 20");
   oac_assert( oac::char_to_symbol('p') == 21, "oac::char_to_symbol('p') != 21");
   oac_assert( oac::char_to_symbol('q') == 22, "oac::char_to_symbol('q') != 22");
   oac_assert( oac::char_to_symbol('r') == 23, "oac::char_to_symbol('r') != 23");
   oac_assert( oac::char_to_symbol('s') == 24, "oac::char_to_symbol('s') != 24");
   oac_assert( oac::char_to_symbol('t') == 25, "oac::char_to_symbol('t') != 25");
   oac_assert( oac::char_to_symbol('u') == 26, "oac::char_to_symbol('u') != 26");
   oac_assert( oac::char_to_symbol('v') == 27, "oac::char_to_symbol('v') != 27");
   oac_assert( oac::char_to_symbol('w') == 28, "oac::char_to_symbol('w') != 28");
   oac_assert( oac::char_to_symbol('x') == 29, "oac::char_to_symbol('x') != 29");
   oac_assert( oac::char_to_symbol('y') == 30, "oac::char_to_symbol('y') != 30");
   oac_assert( oac::char_to_symbol('z') == 31, "oac::char_to_symbol('z') != 31");

   for(unsigned char i = 0; i<255; i++) {
      if((i >= 'a' && i <= 'z') || (i >= '1' || i <= '5')) continue;
      oac_assert( oac::char_to_symbol((char)i) == 0, "oac::char_to_symbol() != 0");
   }
}

void test_types::string_to_name() {

   oac_assert( oac::string_to_name("a") == N(a) , "oac::string_to_name(a)" );
   oac_assert( oac::string_to_name("ba") == N(ba) , "oac::string_to_name(ba)" );
   oac_assert( oac::string_to_name("cba") == N(cba) , "oac::string_to_name(cba)" );
   oac_assert( oac::string_to_name("dcba") == N(dcba) , "oac::string_to_name(dcba)" );
   oac_assert( oac::string_to_name("edcba") == N(edcba) , "oac::string_to_name(edcba)" );
   oac_assert( oac::string_to_name("fedcba") == N(fedcba) , "oac::string_to_name(fedcba)" );
   oac_assert( oac::string_to_name("gfedcba") == N(gfedcba) , "oac::string_to_name(gfedcba)" );
   oac_assert( oac::string_to_name("hgfedcba") == N(hgfedcba) , "oac::string_to_name(hgfedcba)" );
   oac_assert( oac::string_to_name("ihgfedcba") == N(ihgfedcba) , "oac::string_to_name(ihgfedcba)" );
   oac_assert( oac::string_to_name("jihgfedcba") == N(jihgfedcba) , "oac::string_to_name(jihgfedcba)" );
   oac_assert( oac::string_to_name("kjihgfedcba") == N(kjihgfedcba) , "oac::string_to_name(kjihgfedcba)" );
   oac_assert( oac::string_to_name("lkjihgfedcba") == N(lkjihgfedcba) , "oac::string_to_name(lkjihgfedcba)" );
   oac_assert( oac::string_to_name("mlkjihgfedcba") == N(mlkjihgfedcba) , "oac::string_to_name(mlkjihgfedcba)" );
   oac_assert( oac::string_to_name("mlkjihgfedcba1") == N(mlkjihgfedcba2) , "oac::string_to_name(mlkjihgfedcba2)" );
   oac_assert( oac::string_to_name("mlkjihgfedcba55") == N(mlkjihgfedcba14) , "oac::string_to_name(mlkjihgfedcba14)" );

   oac_assert( oac::string_to_name("azAA34") == N(azBB34) , "oac::string_to_name N(azBB34)" );
   oac_assert( oac::string_to_name("AZaz12Bc34") == N(AZaz12Bc34) , "oac::string_to_name AZaz12Bc34" );
   oac_assert( oac::string_to_name("AAAAAAAAAAAAAAA") == oac::string_to_name("BBBBBBBBBBBBBDDDDDFFFGG") , "oac::string_to_name BBBBBBBBBBBBBDDDDDFFFGG" );
}

void test_types::name_class() {

   oac_assert( oac::name{oac::string_to_name("azAA34")}.value == N(azAA34), "oac::name != N(azAA34)" );
   oac_assert( oac::name{oac::string_to_name("AABBCC")}.value == 0, "oac::name != N(0)" );
   oac_assert( oac::name{oac::string_to_name("AA11")}.value == N(AA11), "oac::name != N(AA11)" );
   oac_assert( oac::name{oac::string_to_name("11AA")}.value == N(11), "oac::name != N(11)" );
   oac_assert( oac::name{oac::string_to_name("22BBCCXXAA")}.value == N(22), "oac::name != N(22)" );
   oac_assert( oac::name{oac::string_to_name("AAAbbcccdd")} == oac::name{oac::string_to_name("AAAbbcccdd")}, "oac::name == oac::name" );

   uint64_t tmp = oac::name{oac::string_to_name("11bbcccdd")};
   oac_assert(N(11bbcccdd) == tmp, "N(11bbcccdd) == tmp");
}
