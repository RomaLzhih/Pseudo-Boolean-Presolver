#include "runRoundingSat.hpp"

namespace pre
{

void
runRoundingSat::runRS( std::string& infile )
{
   double time = 0.0;
   strpair rsSol = runRoundingSat::runforSAT( infile, time );
   //* filename solStat solVal time
   std::cout << "@ " << infile.substr( infile.find_last_of( "//" ) + 1 );
   std::cout << ( rsSol.first == "UNSATISFIABLE" ? " 0" : " 1" );
   std::cout << " " << ( rsSol.second.size() ? rsSol.second : "-" );
   std::cout << " " << time;
   std::cout << std::endl;
   return;
}

strpair
runRoundingSat::runforPaPILO( std::string& preInfo, std::string infile,
                              double& time )
{
   papilo::Timer* timer = new papilo::Timer( time );
   namespace bp = boost::process;
   std::string roundingSat = "../build/roundingsat";
   std::string command = roundingSat + " --print-sol=1 --verbosity=0 ";

   // std::ofstream out( newInsPath );
   // out << preInfo;
   // out.close();

   bp::ipstream pipout;
   bp::opstream pipin;
   bp::child c( command, bp::std_in<pipin, bp::std_out> pipout );
   pipin << preInfo;
   pipin.flush();
   pipin.pipe().close();

   std::string line;
   std::string sol = "";
   std::string status = "";
   while( pipout && std::getline( pipout, line ) )
   {
      if( line.empty() || line[0] == 'c' )
         continue;
      else if( line[0] == 's' )
         status = line.substr( 2 );
      else if( line[0] == 'v' )
         sol = line.substr( 2 );
      else
         continue; // may print other information
   }
   c.wait();
   delete timer;

   return std::make_pair( status, sol );
}

strpair
runRoundingSat::runforPaPILO( const std::string& infile, double& time )
{
   papilo::Timer* timer = new papilo::Timer( time );
   namespace bp = boost::process;
   std::string roundingSat = "../build/roundingsat";
   std::string command = roundingSat + " --print-sol=1 --verbosity=0 " + infile;
   bp::ipstream pipout;
   bp::opstream pipin;
   bp::child c( command, bp::std_out > pipout );
   std::string line;
   std::string sol = "";
   std::string status = "";
   while( pipout && std::getline( pipout, line ) && !line.empty() )
   {
      // std::cout << '\t' << line << std::endl;
      if( line.empty() || line[0] == 'c' )
         continue;
      else if( line[0] == 's' )
         status = line.substr( 2 );
      else if( line[0] == 'v' )
         sol = line.substr( 2 );
      else
         continue; // may print other information
   }
   c.wait();
   delete timer;
   return std::make_pair( status, sol );
}

std::string
runRoundingSat::runforRedundancy( std::string& preInfo, std::string infile )
{
   namespace bp = boost::process;

   std::string roundingSat = "../build/roundingsat";
   std::string command = roundingSat + " --print-sol=1 --verbosity=0 ";

   bp::ipstream pipout;
   bp::opstream pipin;
   bp::child c( command, bp::std_in<pipin, bp::std_out> pipout );
   pipin << preInfo;
   pipin.flush();
   pipin.pipe().close();

   std::string line;
   std::string status = "";
   while( pipout && std::getline( pipout, line ) && !line.empty() )
   {
      if( line[0] == 's' )
         status = line.substr( 2 );
   }
   c.wait();
   return status;
}

strpair
runRoundingSat::runforSAT( const std::string& preInfo, std::string& infile,
                           double& time )
{
   papilo::Timer* timer = new papilo::Timer( time );
   namespace bp = boost::process;

   std::string roundingSat = "../build/roundingsat";
   std::string command = roundingSat + " --verbosity=0 ";

   bp::ipstream pipout;
   bp::opstream pipin;

   bp::child c( command, bp::std_in<pipin, bp::std_out> pipout );
   pipin << preInfo;

   pipin.flush();
   pipin.pipe().close();

   std::string line;
   std::string obj = "";
   std::string status = "";
   while( pipout && std::getline( pipout, line ) )
   {
      std::cout << '\t' << line << std::endl;
      if( line.empty() || line[0] == 'c' )
         continue;
      else if( line[0] == 's' )
         status = line.substr( 2 );
      else if( line[0] == 'o' )
         obj = line.substr( 2 );
      else
         continue; // may print other information
   }
   c.wait();
   delete timer;
   return std::make_pair( status, obj );
}

strpair
runRoundingSat::runforSAT( const std::string& infile, double& time )
{
   papilo::Timer* timer = new papilo::Timer( time );

   namespace bp = boost::process;
   std::string roundingSat = "../build/roundingsat";
   std::string command = roundingSat + " --print-sol=1 --verbosity=0 " + infile;
   bp::ipstream pipout;
   bp::opstream pipin;
   bp::child c( command, bp::std_out > pipout );

   std::string line;
   std::string obj = "";
   std::string status = "";
   while( pipout && std::getline( pipout, line ) && !line.empty() )
   {
      // std::cout << '\t' << line << std::endl;
      if( line.empty() || line[0] == 'c' )
         continue;
      else if( line[0] == 's' )
         status = line.substr( 2 );
      else if( line[0] == 'o' )
         obj = line.substr( 2 );
      else
         continue; // may print other information
   }
   c.wait();
   delete timer;
   return std::make_pair( status, obj );
}
} // namespace pre