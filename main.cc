#include <iostream>
#include <fstream>
#include <complex>
#include <boost/array.hpp>

#include <boost/numeric/odeint.hpp>

using namespace std;
using namespace boost::numeric::odeint;

typedef boost::array<complex<double>, 2> state_type;


struct tdse {
  double w[2]={-0.5, -0.125};
  double Omega, wc, tc, sigma;

  tdse(double Omega=0.02, double wc=0.375, double tc=150., double sigma=60.):
    Omega(Omega), wc(wc), tc(tc), sigma(sigma) {}

  void operator()( const state_type &x , state_type &dxdt , double t ) const {

    const complex< double > I( 0.0 , 1.0 );
    double Ef = exp( - (t-tc)*(t-tc) / (sigma*sigma) );

    // Schroedinger picture
    dxdt[0] = - I * (w[0] * x[0] + Omega * Ef * cos(wc*t) * x[1]);
    dxdt[1] = - I * (Omega * Ef * cos(wc*t) * x[0] + w[1] * x[1]);

    // Interaction picture with RWA
    // double delta = w[1] - w[0] - wc;
    // dxdt[0] = - I * (0.5 * Omega * Ef * exp(-I * delta * t) * x[1]);
    // dxdt[1] = - I * (0.5 * Omega * Ef * exp(+I * delta * t) * x[0]);
  }
};

struct streaming_observer {
  std::ostream& m_out;
  streaming_observer( std::ostream &out ) : m_out( out ) { }

  template< class State >
  void operator()( const State &x , double t ) const {
    m_out << t;
    m_out << " " << x[0].real() << " " << x[0].imag() ;
    m_out << " " << x[1].real() << " " << x[1].imag() ;
    m_out << "\n";
  }
};

int main( int argc , char **argv )
{
  state_type x;
  x[0] = 1.;
  x[1] = 0.;
  const double dt = 0.2;

  typedef runge_kutta4< state_type > stepper_type;

  ofstream outfile("test.dat");
  integrate_const( stepper_type() , tdse(0.04) , x , 0.0 , 300.0 , dt , streaming_observer( outfile ) );
  outfile.close();
  return 0;
}
