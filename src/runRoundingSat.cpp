#include "runRoundingSat.hpp"

namespace pre {

int runRoundingSat::run(std::string& info) {
	std::cout << info << std::endl;

	namespace bp = boost::process;

	std::string instancePath = "/mnt/d/aMain/0-RoundingSat/roundingsat-master/test/instances/opb/opt/diamond.opb";
	std::string roundingSat = "/mnt/d/aMain/0-RoundingSat/roundingsat-master/build/roundingsat";
	std::string command = roundingSat + " --print-sol=1 --verbosity=0 " + instancePath;
	// std::string command = roundingSat + " --print-sol=1 ";

	std::string testpath = "/mnt/d/aMain/4-pre/pre/test/a.out";
	const std::string input = "1\n2\n3\n";

	bp::ipstream pipout;
	bp::opstream pipin;

	// bp::child c(command, bp::std_in < pipin, bp::std_out > pipout);
	// bp::child c(testpath, bp::std_in < pipin, bp::std_out > pipout);
	bp::child c(command, bp::std_out > pipout);

	pipin << info << std::endl;

	std::string line;

	std::cout << "retrive information .. " << std::endl;
	while (pipout && std::getline(pipout, line) && !line.empty())
		std::cout << line << std::endl;

	c.wait();
	return c.exit_code();
}

} // namespace pre