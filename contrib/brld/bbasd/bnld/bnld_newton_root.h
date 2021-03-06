// This is bbasd/bnld/algo/bnld_newton_root.h

#ifndef bnld_newton_root_h_
#define bnld_newton_root_h_

//:
// \file
// \brief Newton root solver
// 
// \author Based on original code by  Nhon Trinh ( @lems.brown.edu)
// \date 2/13/05
//
// \verbatim
//  Modifications:
// \endverbatim

// Reference: book "Numerical Recipes in C" by William Press et.al.

//: Root finder combining Newton method and secant method
// Reference: William Press, et.al.,
// "Numerical Recipes in C: The Art of Scientific Computing"
// ISBN 0-521-43108-5


class bnld_newton_root_func
{
public:
  bnld_newton_root_func(){};
  virtual ~bnld_newton_root_func(){};
  virtual double f(double x){ return 0; };
  virtual double df( double x){ return 0; };
  void compute(double x, double *f, double *df){
    *f = this->f(x);
    *df = this->df(x);
  };
};


bool bnld_newton_secant_root( bnld_newton_root_func& funcd, 
                              double x1, double x2, double xacc, double *root);

#endif // bbasd/bnld/bnld_fresnel.h
