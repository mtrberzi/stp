/***********
AUTHORS:   Murphy Berzish

BEGIN DATE: May, 2015

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
**********************/

#include <gtest/gtest.h>
#include "stp/c_interface.h"

TEST(array_extensionality, one)
{
  /* Make the following claims:
   *  A == B
   *  A[i] != B[i]
   * With correct knowledge of array extensionality,
   * this should be UNSAT.
   */
  VC vc = vc_createValidityChecker();

  Type bv8 = vc_bvType(vc, 8);
  Type arr_8_8 = vc_arrayType(vc, bv8, bv8);

  Expr A = vc_varExpr(vc, "A", arr_8_8);
  Expr B = vc_varExpr(vc, "B", arr_8_8);
  Expr i = vc_varExpr(vc, "i", bv8);
  Expr A_of_i = vc_readExpr(vc, A, i);
  Expr B_of_i = vc_readExpr(vc, B, i);
  Expr A_of_i_eq_B_of_i = vc_eqExpr(vc, A_of_i, B_of_i);
  
  Expr A_equals_B = vc_eqExpr(vc, A, B);
  Expr A_of_i_ne_B_of_i = vc_notExpr(vc, A_of_i_eq_B_of_i);

  vc_assertFormula(vc, A_equals_B);
  int query_result = vc_query(vc, A_of_i_ne_B_of_i);
  ASSERT_EQ(query_result, 1); // VALID
  
  vc_Destroy(vc);
}
