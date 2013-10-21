/*********************************************************************
 *
 * registry.c: Riak C Unit testing registration
 *
 * Copyright (c) 2007-2013 Basho Technologies, Inc.  All Rights Reserved.
 *
 * This file is provided to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License.  You may obtain
 * a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include "riak.h"

void
test_build_binary() {
    riak_context *ctx;
    riak_error   err = riak_context_new_default(&ctx, "localhost", "1");
    riak_binary *bin = riak_binary_new(ctx, 6, (riak_uint8_t*)"abcdef");
    riak_int32_t len = riak_binary_len(bin);
    CU_ASSERT_EQUAL(len,6);
    riak_uint8_t *data = riak_binary_data(bin);
    CU_ASSERT_EQUAL(memcmp(data, "abcdef", 6), 0);
    riak_binary_free(ctx, &bin);
    CU_PASS("test_build_binary passed")
}

int
main(int   argc,
     char *argv[])
{
    CU_ErrorCode cuerr = CU_initialize_registry();
    if (cuerr != CUE_SUCCESS) {
        fprintf(stderr, "Could not initialize cuint testing registry\n");
        exit(1);
    }
    CU_InitializeFunc init_fn = NULL;
    CU_CleanupFunc cleanup_fn = NULL;
    CU_pSuite basic_suite = CU_add_suite("basic", init_fn, cleanup_fn);
    CU_pTest test = CU_add_test(basic_suite, "build_binary", test_build_binary);
    CU_basic_run_tests();

    void CU_cleanup_registry();
}