/* Copyright (C) 2012 Open Information Security Foundation
 *
 * You can copy, redistribute or modify this Program under the terms of
 * the GNU General Public License version 2 as published by the Free
 * Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

/**
 * \file
 *
 * \author Zoltan Herczeg <zherczeg@inf.u-szeged.hu>
 */

#include <stdlib.h>
#include <stdio.h>
#include "mpm.h"

static int test_failed = 0;

int test_mpm_add(mpm_re *re, char *pattern, int flags)
{
    int error_code = mpm_add(re, pattern, flags);
    if (error_code != MPM_NO_ERROR) {
        printf("mpm_add is failed: %s\n", mpm_error_to_string(error_code));
        test_failed = 1;
    }
}

int main()
{
    mpm_re *re;
    printf("Running MPM (multi=pattern matcher) tests\n\n");
    re = mpm_create();
    if (!re)
        return 1;

    test_mpm_add(re, "ab\\x00.", 0);
    test_mpm_add(re, "[^c][^\\x00][^\\x01][^\\xfe][^\\xff].", MPM_ADD_DOTALL);
    test_mpm_add(re, "ab[^c][^e]\\xff", MPM_ADD_CASELESS);
    test_mpm_add(re, " [a-z] [\\x00-\\x05x-\\xff] (?i)[c-fMX] ", MPM_ADD_EXTENDED);

    mpm_free(re);
    return test_failed;
}
