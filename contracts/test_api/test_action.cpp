/**
 * @file action_test.cpp
 * @copyright defined in oac/LICENSE.txt
 */
#include <oaclib/action.hpp>
#include <oaclib/transaction.hpp>
#include <oaclib/chain.h>
#include <oaclib/db.h>
#include <oaclib/crypto.h>
#include <oaclib/privileged.h>
#include <oaclib/oac.hpp>
#include <oaclib/datastream.hpp>
#include <oaclib/print.hpp>
#include <oaclib/compiler_builtins.h>
#include "test_api.hpp"

void test_action::read_action_normal() {

   char buffer[100];
   uint32_t total = 0;

   oac_assert(action_data_size() == sizeof(dummy_action), "action_size() == sizeof(dummy_action)");

   total = read_action_data(buffer, 30);
   oac_assert(total == sizeof(dummy_action) , "read_action(30)" );

   total = read_action_data(buffer, 100);
   oac_assert(total == sizeof(dummy_action) , "read_action(100)" );

   total = read_action_data(buffer, 5);
   oac_assert(total == 5 , "read_action(5)" );

   total = read_action_data(buffer, sizeof(dummy_action) );
   oac_assert(total == sizeof(dummy_action), "read_action(sizeof(dummy_action))" );

   dummy_action *dummy13 = reinterpret_cast<dummy_action *>(buffer);

   oac_assert(dummy13->a == DUMMY_ACTION_DEFAULT_A, "dummy13->a == DUMMY_ACTION_DEFAULT_A");
   oac_assert(dummy13->b == DUMMY_ACTION_DEFAULT_B, "dummy13->b == DUMMY_ACTION_DEFAULT_B");
   oac_assert(dummy13->c == DUMMY_ACTION_DEFAULT_C, "dummy13->c == DUMMY_ACTION_DEFAULT_C");
}

void test_action::test_dummy_action() {
   char buffer[100];
   int total = 0;

   // get_action
   total = get_action( 1, 0, buffer, 0 );
   total = get_action( 1, 0, buffer, static_cast<size_t>(total) );
   oac_assert( total > 0, "get_action failed" );
   oac::action act = oac::get_action( 1, 0 );
   oac_assert( act.authorization.back().actor == N(testapi), "incorrect permission actor" );
   oac_assert( act.authorization.back().permission == N(active), "incorrect permission name" );
   oac_assert( oac::pack_size(act) == static_cast<size_t>(total), "pack_size does not match get_action size" );
   oac_assert( act.account == N(testapi), "expected testapi account" );

   dummy_action dum13 = act.data_as<dummy_action>();

   if ( dum13.b == 200 ) {
      // attempt to access context free only api
      get_context_free_data( 0, nullptr, 0 );
      oac_assert(false, "get_context_free_data() not allowed in non-context free action");
   } else {
      oac_assert(dum13.a == DUMMY_ACTION_DEFAULT_A, "dum13.a == DUMMY_ACTION_DEFAULT_A");
      oac_assert(dum13.b == DUMMY_ACTION_DEFAULT_B, "dum13.b == DUMMY_ACTION_DEFAULT_B");
      oac_assert(dum13.c == DUMMY_ACTION_DEFAULT_C, "dum13.c == DUMMY_ACTION_DEFAULT_C");
   }
}

void test_action::read_action_to_0() {
   read_action_data((void *)0, action_data_size());
}

void test_action::read_action_to_64k() {
   read_action_data( (void *)((1<<16)-2), action_data_size());
}

void test_action::test_cf_action() {

   oac::action act = oac::get_action( 0, 0 );
   cf_action cfa = act.data_as<cf_action>();
   if ( cfa.payload == 100 ) {
      // verify read of get_context_free_data, also verifies system api access
      int size = get_context_free_data( cfa.cfd_idx, nullptr, 0 );
      oac_assert( size > 0, "size determination failed" );
      oac::bytes cfd( static_cast<size_t>(size) );
      size = get_context_free_data( cfa.cfd_idx, &cfd[0], static_cast<size_t>(size) );
      oac_assert(static_cast<size_t>(size) == cfd.size(), "get_context_free_data failed" );
      uint32_t v = oac::unpack<uint32_t>( &cfd[0], cfd.size() );
      oac_assert( v == cfa.payload, "invalid value" );

      // verify crypto api access
      checksum256 hash;
      char test[] = "test";
      sha256( test, sizeof(test), &hash );
      assert_sha256( test, sizeof(test), &hash );
      // verify action api access
      action_data_size();
      // verify console api access
      oac::print("test\n");
      // verify memory api access
      uint32_t i = 42;
      memccpy(&v, &i, sizeof(i), sizeof(i));
      // verify transaction api access
      oac_assert(transaction_size() > 0, "transaction_size failed");
      // verify softfloat api access
      float f1 = 1.0f, f2 = 2.0f;
      float f3 = f1 + f2;
      oac_assert( f3 >  2.0f, "Unable to add float.");
      // verify compiler builtin api access
      __int128 ret;
      __divti3(ret, 2, 2, 2, 2);
      // verify context_free_system_api
      oac_assert( true, "verify oac_assert can be called" );


   } else if ( cfa.payload == 200 ) {
      // attempt to access non context free api, privileged_api
      is_privileged(act.name);
      oac_assert( false, "privileged_api should not be allowed" );
   } else if ( cfa.payload == 201 ) {
      // attempt to access non context free api, producer_api
      get_active_producers( nullptr, 0 );
      oac_assert( false, "producer_api should not be allowed" );
   } else if ( cfa.payload == 202 ) {
      // attempt to access non context free api, db_api
      db_store_i64( N(testapi), N(testapi), N(testapi), 0, "test", 4 );
      oac_assert( false, "db_api should not be allowed" );
   } else if ( cfa.payload == 203 ) {
      // attempt to access non context free api, db_api
      uint64_t i = 0;
      db_idx64_store( N(testapi), N(testapi), N(testapi), 0, &i );
      oac_assert( false, "db_api should not be allowed" );
   } else if ( cfa.payload == 204 ) {
      db_find_i64( N(testapi), N(testapi), N(testapi), 1);
      oac_assert( false, "db_api should not be allowed" );
   } else if ( cfa.payload == 205 ) {
      // attempt to access non context free api, send action
      oac::action dum_act;
      dum_act.send();
      oac_assert( false, "action send should not be allowed" );
   } else if ( cfa.payload == 206 ) {
      oac::require_auth(N(test));
      oac_assert( false, "authorization_api should not be allowed" );
   } else if ( cfa.payload == 207 ) {
      now();
      oac_assert( false, "system_api should not be allowed" );
   } else if ( cfa.payload == 208 ) {
      current_time();
      oac_assert( false, "system_api should not be allowed" );
   } else if ( cfa.payload == 209 ) {
      publication_time();
      oac_assert( false, "system_api should not be allowed" );
   } else if ( cfa.payload == 210 ) {
      send_inline( (char*)"hello", 6 );
      oac_assert( false, "transaction_api should not be allowed" );
   } else if ( cfa.payload == 211 ) {
      send_deferred( N(testapi), N(testapi), "hello", 6 );
      oac_assert( false, "transaction_api should not be allowed" );
   }

}

void test_action::require_notice(uint64_t receiver, uint64_t code, uint64_t action) {
   (void)code;(void)action;
   if( receiver == N(testapi) ) {
      oac::require_recipient( N(acc1) );
      oac::require_recipient( N(acc2) );
      oac::require_recipient( N(acc1), N(acc2) );
      oac_assert(false, "Should've failed");
   } else if ( receiver == N(acc1) || receiver == N(acc2) ) {
      return;
   }
   oac_assert(false, "Should've failed");
}

void test_action::require_auth() {
   prints("require_auth");
   oac::require_auth( N(acc3) );
   oac::require_auth( N(acc4) );
}

void test_action::assert_false() {
   oac_assert(false, "test_action::assert_false");
}

void test_action::assert_true() {
   oac_assert(true, "test_action::assert_true");
}

void test_action::assert_true_cf() {
   oac_assert(true, "test_action::assert_true");
}

void test_action::test_abort() {
   abort();
   oac_assert( false, "should've aborted" );
}

void test_action::test_publication_time() {
   uint64_t pub_time = 0;
   uint32_t total = read_action_data(&pub_time, sizeof(uint64_t));
   oac_assert( total == sizeof(uint64_t), "total == sizeof(uint64_t)");
   oac_assert( pub_time == publication_time(), "pub_time == publication_time()" );
}

void test_action::test_current_receiver(uint64_t receiver, uint64_t code, uint64_t action) {
   (void)code;(void)action;
   account_name cur_rec;
   read_action_data(&cur_rec, sizeof(account_name));

   oac_assert( receiver == cur_rec, "the current receiver does not match" );
}

void test_action::test_current_time() {
   uint64_t tmp = 0;
   uint32_t total = read_action_data(&tmp, sizeof(uint64_t));
   oac_assert( total == sizeof(uint64_t), "total == sizeof(uint64_t)");
   oac_assert( tmp == current_time(), "tmp == current_time()" );
}

void test_action::test_assert_code() {
   uint64_t code = 0;
   uint32_t total = read_action_data(&code, sizeof(uint64_t));
   oac_assert( total == sizeof(uint64_t), "total == sizeof(uint64_t)");
   oac_assert_code( false, code );
}
