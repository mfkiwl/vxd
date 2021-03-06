// This is bbasd/bgld/algo/bgld_eulerspiral.h

#ifndef bgld_eulerspiral_h_
#define bgld_eulerspiral_h_

// **** SEE ALSO: vxl/.../bvgl/algo/bvgl_eulerspiral.h
//:
// \file
// \brief Euler spiral - a curve with linear curvature
// \ k(s) = k0 + gamma * s;
// \author Based on original code by  Nhon Trinh ( @lems.brown.edu)
// \date 2/06/05
//
// \verbatim
//  The original code was written by Amir Tamrakar (@lems.brown.edu)
//  Modifications:
//    3/2/2005. Nhon Trinh: added levenberg_marquardt algorithm for optimization.
//    1/3/2007: Nhon Trinh: moved declaration of bgld_eulerspiral_optimization_function
//              to the .cxx file to reduce include files in bgld_eulerspiral.h
//    2/5/2007: Ozge Can Ozcanli: added average_curvature() method -- curvature at the midpoint
// \endverbatim


#include <vcl_ostream.h>
#include <vgl/vgl_point_2d.h>
#include <vcl_string.h>
#include <bgld/bgld_eulerspiral_base.h>

// declaration of bgld_eulerspiral_optimization_function;
class bgld_eulerspiral_optimization_function;

//: bgld_eulerspiral: a class to represent an Euler spiral curve
// which has linear curvature k(s) = k0 + k1 * s
class bgld_eulerspiral : public bgld_eulerspiral_base
{
public:
  
  //: optimization function, need to access compute_end_pt(...) function
  friend class bgld_eulerspiral_optimization_function;
  
  // -------------- INITIALIZERS/CONSTRUCTORS/DESTRUCTORS ----------------------------
  
  //: Constructor - default
  bgld_eulerspiral(): start_(vgl_point_2d< double >(0, 0)){};
  
  //: Constructor - from intrinsic parameters
  bgld_eulerspiral(vgl_point_2d<double > start, double start_angle, double k0, double gamma, double len);
  
  //: Constructor - from 2 point-tangents
  bgld_eulerspiral( vgl_point_2d< double > start, double start_angle, 
    vgl_point_2d< double > end, double end_angle );
  
  //: Copy Constructor
  bgld_eulerspiral(const bgld_eulerspiral & eulerspiral );
  
  //: Set the core parameters of the eulerspiral
  void init(const vgl_point_2d<double >& start, double start_angle, double k0, double gamma, double len);
  
  //: Destructor
  virtual ~bgld_eulerspiral(){};

  //----------------- TYPE ----------------------------
  static const vcl_type_info& type_id()
  { return typeid(bgld_eulerspiral); }

  virtual bool is_type( const vcl_type_info& type ) const { 
    return (typeid(bgld_eulerspiral) == type) != 0 || 
      this->bgld_eulerspiral_base::is_type(type); 
  }

  bgld_param_curve *clone() const { return new bgld_eulerspiral(*this); }


  // ------------ ACCESS MEMBER VARIABLES ----------------------------------
  //: Return the starting point of the eulerspiral
  vgl_point_2d< double > start() const { return this->start_; }

  //: Return the ending point of the eulerspiral
  vgl_point_2d< double > end() const { return this->end_; }
  
  //: Set the starting point of the eulerspiral - type 1
  void set_start( double x_start, double y_start ){ this->start_.set(x_start, y_start); } 
  //: Set the starting point of the eulerspiral - type 2
  void set_start( const vgl_point_2d< double > & start ){ this->start_ = start; }

  //: Return the starting angle of the eulerspiral in the range [0, 2*pi)
  double start_angle() const { return this->start_angle_; }
  //: Set the start angle, converted to the range [0, 2*pi)
  void set_start_angle( double start_angle );
  
  //: Return initial curvature of the eulerspiral
  double k0() const { return this->k0_; }
  //: Set the initial curvature of the eulerspiral
  void set_k0( double k0 ){ this->k0_ = k0; }

  
  //: Return linear factor (gamma) of curvature function
  double gamma() const { return this->gamma_; }
  //: Set linear factor (gamma) of curvature function
  void set_gamma( double gamma ){ this->gamma_ = gamma; }

  //: Return the lengh of the eulerspiral
  // double len() const { return this->len_; }

  //: length of parametric curve from start point to end point (if any)
  virtual double length() const { return this->len_;};
  void set_len( double len ){ this->len_ = len; }

  // ---------------- GEOMETRY FUNCTIONS -----------------------
  
  //: Get the point at arclength s away from the starting point
  virtual vgl_point_2d< double > point_at_length( double s) const;

  //: Get the point at parameter s along the curve, s within [0,1] 
  virtual vgl_point_2d< double > point_at( double s) const;
  
  //: Get tangent of the point at arclength s away from starting point
  virtual vgl_vector_2d< double > tangent_at_length( double s) const;

  //: Get tangent of the point at parameter s within [0,1]
  virtual vgl_vector_2d< double > tangent_at( double s) const;
  
  //: Get tangent angle (in radian) in [0, 2PI) of the point 
  // at arclength s away from the starting point
  virtual double tangent_angle_at_length(double s) const;

  //: Get tangent angle (in radian) in [0, 2PI) at parameter s within [0,1]
  virtual double tangent_angle_at(double s) const;
  
  //: Get curvature of the point at s arclength away from starting point
  virtual double curvature_at_length ( double s) const ;

  //: Get curvature of the point at s within [0,1]
  virtual double curvature_at ( double s) const ;

  //: Get average curvature of the euler spiral
  double average_curvature() { return curvature_at_length(len_/2.0f); }

  //: compute extrinsic points of eulerspiral
  void compute_spiral(vcl_vector<vgl_point_2d<double> >& spiral, double ds=0, int npts=0);

  // ---------------- SUPPORT FUNCTIONS ---------------------------
  
  //: Set intrinsic core parameters of the eulerspiral
  void set_intrinsic_params(double k0, double gamma, double len);
  
  //: Set extrinsic core parameters of the eulerspiral
  void set_extrinsic_params(const vgl_point_2d< double >& start, double start_angle);
  
  //: set parameters at starting point
  void set_start_params( vgl_point_2d< double > start, double start_angle );
  
  //: set parameters at ending point
  void set_end_params( vgl_point_2d< double > end, double end_angle );
  
  //: set parameters at both starting point and end point
  void set_params( vgl_point_2d< double > start, double start_angle, 
    vgl_point_2d< double > end, double end_angle );
  
  //: Compute intrinsic parameters of eulerspiral using currently saved 
  // starting and ending point-tangents
  bool compute_es_params(bool use_lookup_table = true, bool use_levenberg_marquardt = true );
  
  //: Compute intrinsic parameters of eulerspiral given two point-tangents
  // this uses lookup table and levenberg_marquardt minimization algorithm
  bool compute_es_params( vgl_point_2d< double > start, double start_angle,
    vgl_point_2d< double > end, double end_angle );


  // ------------------- OPERATORS -------------------------
  //: comparison operator.
  //  Comparison is on the curve, two parametric curves are identical if their
  //  equations are equivalent
  virtual bool operator==(const bgld_eulerspiral& c) const; 
  inline bool operator!=(const bgld_eulerspiral &other) const {return ! this->operator==(other);}

  //: assignment operator 
  virtual bgld_eulerspiral& operator=( bgld_eulerspiral const& );


  // ---------------- MISCELLANEOUS ----------------------
  //: Print parameters of the eulerspiral
  void print(vcl_ostream &os );
  
  //: return number of times the function compute_end_pt(...) has been evaluated since it 
  // was last reset
  int num_evaluations(){ return this->num_evaluations_; }
  
  //: return number of iterations taken place in the last optimization
  int num_iterations(){ return this->num_iterations_; }

protected:
  // core member variables 
  //: starting point of euler spiral
  vgl_point_2d< double > start_;
  
  //: angle of tangent at the starting point
  double start_angle_;
  
  //: coefficient k0 of curvature function k(s) = k0 + gamma * s
  double k0_;
  
  //: coefficient gamma of curvature function k(s) = k0 + gamma * s
  double gamma_;
  
  //: length of the shock
  double len_;
  
  // external member variables, used to compute core member variables
  //: ending point of the euler spiral
  vgl_point_2d< double > end_;
  
  //: angle of tangent at the end point
  double end_angle_;

  // some other useful params
  //: angle of vector from starting point to end point
  double psi_;
  
  //: total angle of the euler spiral turns to go from starting point to end point
  double turning_angle_;


  // -------------- INTERNAL SUPPORT FUNCTIONS ------------------
  
  //: set the end point of the eulerspiral
  void set_end(const vgl_point_2d< double > & end ){ this->end_ = end; }
  
  //: Return the ending angle of the eulerspiral
  double end_angle(){ return this->end_angle_; }
  
  //: Set end angle of the biarc - converted to the range [0, 2pi)
  void set_end_angle( double end_angle );
  
  //: Return error: euclidean distance between end-point of the Euler spiral with the given
  // intrinsic params and the desired end-point
  inline double compute_error(double k0, double len);
  
  //: Return end point of the Euler spiral with the given intrinsic paramters
  vgl_point_2d< double > compute_end_pt( double k0, double gamma, double len, bool normalized = false) const;
  
  //: store number of evaluations of the function compute_end_pt(...) - the most expensive function
  mutable int num_evaluations_;
  
  // OPTIMIZATION ALGORITHMS
  
  //: compute Euler spiral core intrinsic parameters from starting and ending point-tangent using
  // simple gradient descent algorithm
  bool compute_es_params_use_simple_gradient_descent(bool use_lookup_table = true);
  
  //: compute Euler spiral core intrinsic parameters from starting and ending point-tangent using
  // Levenberg - Marquardt nonlinear minimization algorithm
  bool compute_es_params_use_levenberg_marquardt(bool use_lookup_table = true);
  
  //: store number of iterations taken place in last optimization
  int num_iterations_;
  
  //: computation error of the spiral 
  // = euclidean distance between desired and computed end points
  double error_; 
private:

};


// ============ EULER SPIRAL LOOK-UP TABLE ==========================================

//: a class to contain a look-up table of initial values for euler spiral optimization
// there is ONLY ONE instance for the entire class
class bgld_eulerspiral_lookup_table {
public:
  //: Destructor
  ~bgld_eulerspiral_lookup_table();
  //: Return the pointer to the only instance of the class
  static bgld_eulerspiral_lookup_table* instance();
  //: Return whether the look-up table are created successfully
  bool has_table(){ return has_table_; }

  //: look up approximate values and their maximum errors for k0, gamma, and len
  // providing a starting angle and an ending angle
  void look_up(double start_angle, double end_angle, double* k0, double* gamma, double* len, 
    double *k0_max_error, double *gamma_max_error, double* len_max_error);
  //: delta theta values for the table (tells you about the accuracy of the lookup)
  double dt(); 

private:
  // ----------- SINGLETON approach ------------------------------
  //: Constructor - kept private so that only one instance can be created
  bgld_eulerspiral_lookup_table();
  //: hold the pointer to the only instance of the class
  static bgld_eulerspiral_lookup_table * instance_;
  
  static const vcl_string file_name; //("bgld_eulerspiral_lookup_table.bvl");
  static const vcl_string file_path; // (BRLD_LIB_DIR)

  // ----------- THE LOOK-UP TABLE ----------------------------------
  //: size of the lookup tables (npts_ x npts_) 
  // or number of data points between 0 and 2*pi
  int npts_; 
  vcl_vector< vcl_vector< double > > k0_table_;
  vcl_vector< vcl_vector< double > > gamma_table_;
  vcl_vector< vcl_vector< double > > len_table_;
  // : delta - difference between two consecutive sampled angles, = 2Pi / npts
  double dt_;
  //: indicate whether the table was created successfully
  bool has_table_;
};

#endif // bgld_eulerspiral_h_
