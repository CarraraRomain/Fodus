#include "main.hpp"

/** Main entry point
Where all shall begin
*/
int main(int argc, char* argv[]) {
	// Logger config
	el::Configurations conf("../../res/config/logger.conf");
	el::Loggers::reconfigureAllLoggers(conf);

	LOG(DEBUG) << "***";
	LOG(DEBUG) << "Fodus Started";
	LOG(DEBUG) << FODUS_NAME << " version " << FODUS_VERSION_MAJOR << "." << FODUS_VERSION_MINOR;

	Bootstrap boot(argc, argv);
	
	boot.start();

	boot.run();
    
    return 0;
}
