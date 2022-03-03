#include "runRoundingSat.hpp"

namespace pre {

int runRoundingSat::run(std::string& preInfo, std::string& infile) {
	std::cout << preInfo << std::endl;

	namespace bp = boost::process;

	while (*infile.rbegin() != '.') infile.pop_back();
	infile.pop_back();

	std::cout << infile << std::endl;

	std::string newInsPath = infile + "_solved.opb";
	std::string roundingSat = "/mnt/d/aMain/0-RoundingSat/roundingsat-master/build/roundingsat";
	std::string command = roundingSat + " --print-sol=1 --verbosity=0 " + newInsPath;

	std::ofstream out(newInsPath);
	out << preInfo;
	out.close();

	bp::ipstream pipout;
	bp::opstream pipin;

	bp::child c(command, bp::std_out > pipout);
	// bp::child c(testpath, bp::std_in < pipin, bp::std_out > pipout);
	// bp::child c(command, bp::std_out > pipout);

	pipin << preInfo;

	std::string line;

	std::cout << "retrive information .. " << std::endl;
	while (pipout && std::getline(pipout, line) && !line.empty())
		std::cout << line << std::endl;

	c.wait();
	return c.exit_code();
}

} // namespace pre