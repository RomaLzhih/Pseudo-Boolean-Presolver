#include "headFiles.hpp"

namespace pre {
template<typename T>
class runRoundingSat
{
public:
	int run() {
		namespace bp = boost::process;

		std::string instancePath = "/mnt/d/aMain/0-RoundingSat/roundingsat-master/test/instances/opb/opt/bm23.opb";
		std::string roundingSat = "/mnt/d/aMain/0-RoundingSat/roundingsat-master/build/roundingsat";
		std::string command = roundingSat + " " + instancePath;
		//std::cout << command << std::endl;

		std::string testpath = "/mnt/d/aMain/4-pre/pre/test/a.out";
		const std::string input = "1\n2\n";

		bp::ipstream pipout;
		bp::opstream pipin;

		// bp::child c(testpath, bp::std_in < pipin, bp::std_out > pipout);
		bp::child c(command, bp::std_out > pipout);

		//pipin << input << std::endl;
		std::string line;

		std::cout << "retrive information .. " << std::endl;
		while (pipout && std::getline(pipout, line) && !line.empty())
			std::cerr << line << std::endl;

		c.wait();
		return c.exit_code();
	}

};
}// namespace pre