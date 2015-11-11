#include "main.hpp"

/** Main entry point
Where all shall begin
*/
int main(int argc, char* argv[]) {
	// Logger config
	el::Configurations conf("../../res/config/logger.conf");
	el::Loggers::reconfigureAllLoggers(conf);

	LOG(INFO) << "***";
	LOG(INFO) << "Fodus Started";
	LOG(INFO) << FODUS_NAME << " version " << FODUS_VERSION_MAJOR << "." << FODUS_VERSION_MINOR;
	
	srand(time(NULL));

	Bootstrap boot;
	
	boot.start();

	boot.run();

	LOG(INFO) << "Exiting now";
	LOG(INFO) << "Bye";
    return 0;
}
