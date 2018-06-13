#!/bin/bash
set -e

CURDIR=$(cd $(dirname "$0"); pwd)
# Get BUILDDIR and REAL_OACCOIND
. "${CURDIR}/tests-config.sh"

export OACCOINCLI=${BUILDDIR}/qa/pull-tester/run-oaccoin-cli
export OACCOIND=${REAL_OACCOIND}

#Run the tests

if [ "x${ENABLE_OACCOIND}${ENABLE_UTILS}${ENABLE_WALLET}" = "x111" ]; then
  ${BUILDDIR}/qa/rpc-tests/wallet.py --srcdir "${BUILDDIR}/src"
  ${BUILDDIR}/qa/rpc-tests/listtransactions.py --srcdir "${BUILDDIR}/src"
  ${BUILDDIR}/qa/rpc-tests/mempool_resurrect_test.py --srcdir "${BUILDDIR}/src"
  ${BUILDDIR}/qa/rpc-tests/txn_doublespend.py --srcdir "${BUILDDIR}/src"
  ${BUILDDIR}/qa/rpc-tests/txn_doublespend.py --mineblock --srcdir "${BUILDDIR}/src"
  ${BUILDDIR}/qa/rpc-tests/getchaintips.py --srcdir "${BUILDDIR}/src"
  ${BUILDDIR}/qa/rpc-tests/rest.py --srcdir "${BUILDDIR}/src"
  ${BUILDDIR}/qa/rpc-tests/mempool_spendcoinbase.py --srcdir "${BUILDDIR}/src"
  ${BUILDDIR}/qa/rpc-tests/httpbasics.py --srcdir "${BUILDDIR}/src"
  ${BUILDDIR}/qa/rpc-tests/mempool_coinbase_spends.py --srcdir "${BUILDDIR}/src"
  #${BUILDDIR}/qa/rpc-tests/forknotify.py --srcdir "${BUILDDIR}/src"
else
  echo "No rpc tests to run. Wallet, utils, and oaccoind must all be enabled"
fi
