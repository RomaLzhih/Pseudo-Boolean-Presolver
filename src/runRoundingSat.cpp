#include "runRoundingSat.hpp"

namespace pre
{

strpair
runRoundingSat::runforPaPILO( std::string& preInfo, std::string infile )
{
   namespace bp = boost::process;

   while( *infile.rbegin() != '.' )
      infile.pop_back();

   // std::cout << infile << std::endl;

   std::string newInsPath = infile + "pre.opb";
   std::string roundingSat =
       "/home/mzy/thesis_project/roundingsat/build/roundingsat";
   std::string command =
       roundingSat + " --print-sol=1 --verbosity=0 " + newInsPath;

   std::ofstream out( newInsPath );
   out << preInfo;
   out.close();

   bp::ipstream pipout;
   bp::opstream pipin;
   bp::child c( command, bp::std_out > pipout );
   // bp::child c(testpath, bp::std_in < pipin, bp::std_out > pipout);
   // bp::child c(command, bp::std_out > pipout);

   //    pipin << preInfo;

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
   return std::make_pair( status, sol );
}

strpair
runRoundingSat::runforPaPILO( const std::string& infile )
{
   namespace bp = boost::process;
   std::string roundingSat =
       "/home/mzy/thesis_project/roundingsat/build/roundingsat";
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
   return std::make_pair( status, sol );
}

std::string
runRoundingSat::runforSAT( std::string& preInfo, std::string infile )
{
   while( *infile.rbegin() != '.' )
      infile.pop_back();
   std::string newInsPath = infile + "pre.opb";
   std::string roundingSat =
       "/home/mzy/thesis_project/roundingsat/build/roundingsat";
   std::string command =
       roundingSat + " --print-sol=1 --verbosity=0 " + newInsPath;

   std::ofstream out( newInsPath );
   out << preInfo;
   out.close();

   namespace bp = boost::process;
   bp::ipstream pipout;
   bp::opstream pipin;
   bp::child c( command, bp::std_out > pipout );
   pipin << preInfo;

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

} // namespace pre