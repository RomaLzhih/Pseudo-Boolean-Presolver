#include "runRoundingSat.hpp"

namespace pre {

std::string runRoundingSat::run(std::string& preInfo, std::string& infile) {
	// std::cout << preInfo << std::endl;

	namespace bp = boost::process;

	while (*infile.rbegin() != '.') infile.pop_back();
	infile.pop_back();

	// std::cout << infile << std::endl;

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
	std::string sol;

	std::cout << "retrive information .. " << std::endl;
	while (pipout && std::getline(pipout, line) && !line.empty()) {
		std::cout << line << std::endl;
		if (line.empty() || line[0] == 'c' || line[0] == 's')  continue;
		else if (line[0] == 'v') sol = line.substr(2);
		else continue; // may print other information
	}

	c.wait();
	// return c.exit_code();
	return sol;
}

} // namespace pre