// This is bbasd/bnld/algo/bnld_brent_root.h

#ifndef bnld_brent_root_h_
#define bnld_brent_root_h_

//:
// \file
// \brief Brent root solver
// 
// \author Based on original code by  Nhon Trinh ( @lems.brown.edu)
// \date May 2, 2007
//
// \verbatim
//  Modifications:
// \endverbatim



#include <vnl/vnl_cost_function.h>
#include <vcl_cassert.h>



class bnld_brent_root
{
public:
  bnld_brent_root(vnl_cost_function& functor, double tol = 1e-12, int max_iter = 100):
      f_(&functor), tol_(tol), max_iter_(max_iter){ assert(tol > 0); }
  virtual ~bnld_brent_root(){};

  //: Main function: Find a root of the function in the range [ax, bx]
  // Required: f(ax) . f(bx) < 0
  bool solve(double ax, double bx, double& root);

  //: Evaluate the 1D function at x
  double f(double x);

  static double zeroin_f(double x);
protected:
  vnl_cost_function* f_;
  double tol_;
  int max_iter_;

};

#endif // bbasd/bnld/bnld_fresnel.h
